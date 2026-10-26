#include "graph_bfs.h"
#include "vertex_queue.h"

static void initialize_result(
    GraphBfsResult *result,
    size_t vertex_count,
    size_t source
)
{
    size_t vertex;

    result->vertex_count = vertex_count;
    result->source = source;
    result->visit_count = 0U;

    for (vertex = 0U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        result->visit_order[vertex] = GRAPH_BFS_NO_VERTEX;
        result->discovered[vertex] = false;
        result->distance[vertex] = GRAPH_BFS_NO_DISTANCE;
        result->predecessor[vertex] = GRAPH_BFS_NO_VERTEX;
    }
}

static void initialize_path(GraphBfsPath *path)
{
    size_t index;

    path->count = 0U;
    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        path->vertices[index] = GRAPH_BFS_NO_VERTEX;
    }
}

static GraphBfsStatus map_queue_failure(VertexQueueStatus status)
{
    if (status == VERTEX_QUEUE_LIMIT) {
        return GRAPH_BFS_LIMIT;
    }
    return GRAPH_BFS_INVALID_ARGUMENT;
}

static GraphBfsStatus validate_matrix(const Graph *graph)
{
    GraphStatus status = graph_validate(graph);

    if (status == GRAPH_OK) {
        return GRAPH_BFS_OK;
    }
    if (status == GRAPH_ERR_INVALID_ARGUMENT) {
        return GRAPH_BFS_INVALID_ARGUMENT;
    }
    return GRAPH_BFS_INVALID_GRAPH;
}

static GraphBfsStatus validate_list(const GraphAdjList *graph)
{
    GraphAdjListStatus status = graph_adj_list_validate(graph);

    if (status == GRAPH_ADJ_LIST_OK) {
        return GRAPH_BFS_OK;
    }
    if (status == GRAPH_ADJ_LIST_INVALID_ARGUMENT) {
        return GRAPH_BFS_INVALID_ARGUMENT;
    }
    return GRAPH_BFS_INVALID_GRAPH;
}

static GraphBfsStatus begin_search(
    size_t vertex_count,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *candidate,
    VertexQueue *queue
)
{
    VertexQueueStatus queue_status;

    if (source_vertex >= vertex_count) {
        return GRAPH_BFS_OUT_OF_RANGE;
    }

    queue_status = vertex_queue_init(queue, queue_limit);
    if (queue_status != VERTEX_QUEUE_OK) {
        return map_queue_failure(queue_status);
    }

    initialize_result(candidate, vertex_count, source_vertex);
    queue_status = vertex_queue_enqueue(queue, source_vertex);
    if (queue_status != VERTEX_QUEUE_OK) {
        return map_queue_failure(queue_status);
    }

    candidate->discovered[source_vertex] = true;
    candidate->distance[source_vertex] = 0U;
    return GRAPH_BFS_OK;
}

static GraphBfsStatus discover_vertex(
    VertexQueue *queue,
    size_t from_vertex,
    size_t to_vertex,
    GraphBfsResult *candidate
)
{
    VertexQueueStatus queue_status = vertex_queue_enqueue(
        queue,
        to_vertex
    );

    if (queue_status != VERTEX_QUEUE_OK) {
        return map_queue_failure(queue_status);
    }

    candidate->discovered[to_vertex] = true;
    candidate->distance[to_vertex] =
        candidate->distance[from_vertex] + 1U;
    candidate->predecessor[to_vertex] = from_vertex;
    return GRAPH_BFS_OK;
}

GraphBfsStatus graph_bfs_matrix(
    const Graph *graph,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *out_result
)
{
    GraphBfsResult candidate;
    VertexQueue queue = {{0U}, 0U, 0U, 0U};
    GraphBfsStatus status;

    if (out_result == NULL) {
        return GRAPH_BFS_INVALID_ARGUMENT;
    }

    status = validate_matrix(graph);
    if (status != GRAPH_BFS_OK) {
        return status;
    }

    status = begin_search(
        graph->vertex_count,
        source_vertex,
        queue_limit,
        &candidate,
        &queue
    );
    if (status != GRAPH_BFS_OK) {
        return status;
    }

    for (;;) {
        size_t vertex = 0U;
        size_t neighbor;
        VertexQueueStatus queue_status = vertex_queue_dequeue(
            &queue,
            &vertex
        );

        if (queue_status == VERTEX_QUEUE_UNDERFLOW) {
            break;
        }
        if (queue_status != VERTEX_QUEUE_OK) {
            return map_queue_failure(queue_status);
        }

        candidate.visit_order[candidate.visit_count] = vertex;
        candidate.visit_count += 1U;

        for (neighbor = 0U;
             neighbor < graph->vertex_count;
             ++neighbor) {
            if (graph->adjacency[vertex][neighbor] &&
                !candidate.discovered[neighbor]) {
                status = discover_vertex(
                    &queue,
                    vertex,
                    neighbor,
                    &candidate
                );
                if (status != GRAPH_BFS_OK) {
                    return status;
                }
            }
        }
    }

    *out_result = candidate;
    return GRAPH_BFS_OK;
}

GraphBfsStatus graph_bfs_reconstruct_path(
    const GraphBfsResult *result,
    size_t destination_vertex,
    GraphBfsPath *out_path
)
{
    GraphBfsPath candidate;
    size_t reverse[GRAPH_MAX_VERTICES];
    size_t reverse_count = 0U;
    size_t current;
    size_t index;
    GraphBfsStatus status;

    if (out_path == NULL) {
        return GRAPH_BFS_INVALID_ARGUMENT;
    }

    status = graph_bfs_result_validate(result);
    if (status == GRAPH_BFS_INVALID_ARGUMENT) {
        return GRAPH_BFS_INVALID_ARGUMENT;
    }
    if (status != GRAPH_BFS_OK) {
        return GRAPH_BFS_INVALID_RESULT;
    }

    if (destination_vertex >= result->vertex_count) {
        return GRAPH_BFS_OUT_OF_RANGE;
    }
    if (!result->discovered[destination_vertex]) {
        return GRAPH_BFS_UNREACHABLE;
    }

    current = destination_vertex;
    for (;;) {
        if (reverse_count >= result->vertex_count) {
            return GRAPH_BFS_INVALID_RESULT;
        }
        reverse[reverse_count] = current;
        reverse_count += 1U;

        if (current == result->source) {
            break;
        }

        current = result->predecessor[current];
        if (current >= result->vertex_count) {
            return GRAPH_BFS_INVALID_RESULT;
        }
    }

    initialize_path(&candidate);
    candidate.count = reverse_count;
    for (index = 0U; index < reverse_count; ++index) {
        candidate.vertices[index] =
            reverse[reverse_count - index - 1U];
    }

    *out_path = candidate;
    return GRAPH_BFS_OK;
}

GraphBfsStatus graph_bfs_list(
    const GraphAdjList *graph,
    size_t source_vertex,
    size_t queue_limit,
    GraphBfsResult *out_result
)
{
    GraphBfsResult candidate;
    VertexQueue queue = {{0U}, 0U, 0U, 0U};
    GraphBfsStatus status;

    if (out_result == NULL) {
        return GRAPH_BFS_INVALID_ARGUMENT;
    }

    status = validate_list(graph);
    if (status != GRAPH_BFS_OK) {
        return status;
    }

    status = begin_search(
        graph->vertex_count,
        source_vertex,
        queue_limit,
        &candidate,
        &queue
    );
    if (status != GRAPH_BFS_OK) {
        return status;
    }

    for (;;) {
        size_t vertex = 0U;
        size_t index;
        VertexQueueStatus queue_status = vertex_queue_dequeue(
            &queue,
            &vertex
        );

        if (queue_status == VERTEX_QUEUE_UNDERFLOW) {
            break;
        }
        if (queue_status != VERTEX_QUEUE_OK) {
            return map_queue_failure(queue_status);
        }

        candidate.visit_order[candidate.visit_count] = vertex;
        candidate.visit_count += 1U;

        for (index = 0U;
             index < graph->neighbors[vertex].size;
             ++index) {
            size_t neighbor = graph->neighbors[vertex].data[index];

            if (!candidate.discovered[neighbor]) {
                status = discover_vertex(
                    &queue,
                    vertex,
                    neighbor,
                    &candidate
                );
                if (status != GRAPH_BFS_OK) {
                    return status;
                }
            }
        }
    }

    *out_result = candidate;
    return GRAPH_BFS_OK;
}
