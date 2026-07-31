#include "dijkstra.h"

#include <stdbool.h>
#include <stdint.h>

static bool is_ascii_space(char character)
{
    return character == ' ' ||
        character == '\t' ||
        character == '\n' ||
        character == '\r' ||
        character == '\f' ||
        character == '\v';
}

WeightedGraphStatus weighted_graph_parse_weight(
    const char *text,
    size_t *out_weight
)
{
    const char *cursor;
    size_t candidate = 0U;
    bool saw_digit = false;

    if (out_weight == NULL) {
        return WEIGHTED_GRAPH_INVALID_ARGUMENT;
    }
    if (text == NULL) {
        return WEIGHTED_GRAPH_INVALID_ARGUMENT;
    }

    cursor = text;
    while (is_ascii_space(*cursor)) {
        cursor += 1;
    }

    if (*cursor == '-') {
        return WEIGHTED_GRAPH_NEGATIVE_WEIGHT;
    }
    if (*cursor == '+') {
        cursor += 1;
    }

    while (*cursor >= '0' && *cursor <= '9') {
        size_t digit = (size_t)(*cursor - '0');

        saw_digit = true;
        if (candidate > (SIZE_MAX - digit) / 10U) {
            return WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE;
        }
        candidate = candidate * 10U + digit;
        cursor += 1;
    }

    if (!saw_digit) {
        return WEIGHTED_GRAPH_INVALID_WEIGHT_TEXT;
    }
    while (is_ascii_space(*cursor)) {
        cursor += 1;
    }
    if (*cursor != '\0') {
        return WEIGHTED_GRAPH_INVALID_WEIGHT_TEXT;
    }
    if (candidate == SIZE_MAX) {
        return WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE;
    }

    *out_weight = candidate;
    return WEIGHTED_GRAPH_OK;
}

static void initialize_dijkstra_result(
    DijkstraResult *result,
    const WeightedGraph *graph,
    size_t source
)
{
    size_t vertex;
    size_t event_index;

    *result = (DijkstraResult){0};
    result->vertex_count = graph->vertex_count;
    result->arc_count = graph->arc_count;
    result->source = source;

    for (vertex = 0U;
         vertex <
             (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
         ++vertex) {
        result->distance[vertex] = DIJKSTRA_INF;
        result->predecessor[vertex] =
            DIJKSTRA_NO_VERTEX;
        result->finalized[vertex] = false;
        result->finalized_order[vertex] =
            DIJKSTRA_NO_VERTEX;
    }
    for (event_index = 0U;
         event_index <
             (size_t)DIJKSTRA_MAX_POP_EVENTS;
         ++event_index) {
        result->pop_trace[event_index].vertex =
            DIJKSTRA_NO_VERTEX;
        result->pop_trace[event_index].snapshot_distance =
            DIJKSTRA_INF;
        result->pop_trace[event_index].insertion_sequence =
            DIJKSTRA_NO_SEQUENCE;
        result->pop_trace[event_index].stale = false;
    }

    result->distance[source] = 0U;
}

static DijkstraStatus map_frontier_failure(
    DijkstraFrontierStatus status
)
{
    if (status == DIJKSTRA_FRONTIER_ALLOCATION) {
        return DIJKSTRA_ALLOCATION;
    }
    if (status == DIJKSTRA_FRONTIER_FULL ||
        status == DIJKSTRA_FRONTIER_SEQUENCE_EXHAUSTED ||
        status == DIJKSTRA_FRONTIER_OUT_OF_RANGE) {
        return DIJKSTRA_LIMIT;
    }
    return DIJKSTRA_INVALID_RESULT;
}

static DijkstraStatus fail_after_frontier(
    DijkstraFrontier *frontier,
    DijkstraStatus status
)
{
    dijkstra_frontier_destroy(frontier);
    return status;
}

DijkstraStatus dijkstra_shortest_paths(
    const WeightedGraph *graph,
    size_t source_vertex,
    DijkstraResult *out_result
)
{
    DijkstraResult candidate;
    DijkstraFrontier frontier = {0};
    WeightedGraphStatus graph_status;
    DijkstraFrontierStatus frontier_status;

    if (out_result == NULL) {
        return DIJKSTRA_INVALID_ARGUMENT;
    }
    if (graph == NULL) {
        return DIJKSTRA_INVALID_ARGUMENT;
    }

    graph_status = weighted_graph_validate(graph);
    if (graph_status != WEIGHTED_GRAPH_OK) {
        return DIJKSTRA_INVALID_GRAPH;
    }
    if (source_vertex >= graph->vertex_count) {
        return DIJKSTRA_OUT_OF_RANGE;
    }

    initialize_dijkstra_result(
        &candidate,
        graph,
        source_vertex
    );

    frontier_status = dijkstra_frontier_init(
        &frontier,
        graph->arc_count + 1U
    );
    if (frontier_status != DIJKSTRA_FRONTIER_OK) {
        return map_frontier_failure(frontier_status);
    }

    frontier_status = dijkstra_frontier_push(
        &frontier,
        source_vertex,
        0U
    );
    if (frontier_status != DIJKSTRA_FRONTIER_OK) {
        return fail_after_frontier(
            &frontier,
            map_frontier_failure(frontier_status)
        );
    }
    candidate.push_count = 1U;
    candidate.frontier_peak = 1U;

    while (frontier.size > 0U) {
        DijkstraFrontierEntry entry;
        DijkstraPopEvent *event;
        const WeightedEdgeArray *row;
        size_t edge_index;

        frontier_status = dijkstra_frontier_pop(
            &frontier,
            &entry
        );
        if (frontier_status != DIJKSTRA_FRONTIER_OK ||
            candidate.pop_count >=
                (size_t)DIJKSTRA_MAX_POP_EVENTS) {
            return fail_after_frontier(
                &frontier,
                frontier_status ==
                    DIJKSTRA_FRONTIER_OK
                    ? DIJKSTRA_LIMIT
                    : map_frontier_failure(
                        frontier_status
                    )
            );
        }

        event =
            &candidate.pop_trace[candidate.pop_count];
        event->vertex = entry.vertex;
        event->snapshot_distance = entry.distance;
        event->insertion_sequence =
            entry.insertion_sequence;
        event->stale =
            entry.distance !=
                candidate.distance[entry.vertex];
        candidate.pop_count += 1U;

        if (event->stale) {
            candidate.stale_pop_count += 1U;
            continue;
        }
        if (candidate.finalized[entry.vertex] ||
            candidate.finalized_count >=
                candidate.vertex_count) {
            return fail_after_frontier(
                &frontier,
                DIJKSTRA_INVALID_RESULT
            );
        }

        candidate.finalized[entry.vertex] = true;
        candidate.finalized_order[
            candidate.finalized_count
        ] = entry.vertex;
        candidate.finalized_count += 1U;

        row = &graph->outgoing[entry.vertex];
        for (edge_index = 0U;
             edge_index < row->size;
             ++edge_index) {
            const WeightedEdge *edge =
                &row->data[edge_index];
            size_t relaxed_distance;

            candidate.relaxation_attempt_count += 1U;

            if (!(candidate.distance[entry.vertex] !=
                        DIJKSTRA_INF &&
                  edge->weight <=
                        DIJKSTRA_INF -
                            candidate.distance[
                                entry.vertex
                            ])) {
                return fail_after_frontier(
                    &frontier,
                    DIJKSTRA_COST_RANGE
                );
            }
            relaxed_distance =
                candidate.distance[entry.vertex] +
                edge->weight;
            if (relaxed_distance == DIJKSTRA_INF) {
                return fail_after_frontier(
                    &frontier,
                    DIJKSTRA_COST_RANGE
                );
            }

            if (relaxed_distance <
                candidate.distance[edge->to]) {
                frontier_status =
                    dijkstra_frontier_push(
                        &frontier,
                        edge->to,
                        relaxed_distance
                    );
                if (frontier_status !=
                    DIJKSTRA_FRONTIER_OK) {
                    return fail_after_frontier(
                        &frontier,
                        map_frontier_failure(
                            frontier_status
                        )
                    );
                }

                candidate.distance[edge->to] =
                    relaxed_distance;
                candidate.predecessor[edge->to] =
                    entry.vertex;
                candidate.successful_relaxation_count +=
                    1U;
                candidate.push_count += 1U;
                if (frontier.size >
                    candidate.frontier_peak) {
                    candidate.frontier_peak =
                        frontier.size;
                }
            }
        }
    }

    candidate.heap_comparison_count =
        frontier.comparison_count;
    dijkstra_frontier_destroy(&frontier);

    if (dijkstra_result_validate(&candidate) !=
        DIJKSTRA_OK) {
        return DIJKSTRA_INVALID_RESULT;
    }

    *out_result = candidate;
    return DIJKSTRA_OK;
}

DijkstraStatus dijkstra_reconstruct_path(
    const DijkstraResult *result,
    size_t destination_vertex,
    DijkstraPath *out_path
)
{
    DijkstraPath candidate = {
        {DIJKSTRA_NO_VERTEX},
        0U,
        0U
    };
    size_t reverse_vertices[
        WEIGHTED_GRAPH_MAX_VERTICES];
    size_t reverse_count = 0U;
    size_t current;
    size_t index;
    DijkstraStatus status;

    if (out_path == NULL) {
        return DIJKSTRA_INVALID_ARGUMENT;
    }

    status = dijkstra_result_validate(result);
    if (status != DIJKSTRA_OK) {
        return status;
    }
    if (destination_vertex >= result->vertex_count) {
        return DIJKSTRA_OUT_OF_RANGE;
    }
    if (result->distance[destination_vertex] ==
        DIJKSTRA_INF) {
        return DIJKSTRA_UNREACHABLE;
    }

    for (index = 0U;
         index <
             (size_t)WEIGHTED_GRAPH_MAX_VERTICES;
         ++index) {
        candidate.vertices[index] =
            DIJKSTRA_NO_VERTEX;
    }

    current = destination_vertex;
    for (;;) {
        if (reverse_count >= result->vertex_count) {
            return DIJKSTRA_INVALID_RESULT;
        }
        reverse_vertices[reverse_count] = current;
        reverse_count += 1U;

        if (current == result->source) {
            break;
        }
        current = result->predecessor[current];
        if (current >= result->vertex_count) {
            return DIJKSTRA_INVALID_RESULT;
        }
    }

    candidate.count = reverse_count;
    candidate.total_cost =
        result->distance[destination_vertex];
    for (index = 0U; index < reverse_count; ++index) {
        candidate.vertices[index] =
            reverse_vertices[
                reverse_count - index - 1U
            ];
    }

    *out_path = candidate;
    return DIJKSTRA_OK;
}
