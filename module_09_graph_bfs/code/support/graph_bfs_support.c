#include "graph_bfs.h"

GraphBfsStatus graph_bfs_result_validate(
    const GraphBfsResult *result
)
{
    bool in_order[GRAPH_MAX_VERTICES] = {false};
    size_t position[GRAPH_MAX_VERTICES];
    size_t discovered_count = 0U;
    size_t index;
    size_t vertex;

    if (result == NULL) {
        return GRAPH_BFS_INVALID_ARGUMENT;
    }
    if (result->vertex_count == 0U ||
        result->vertex_count > (size_t)GRAPH_MAX_VERTICES ||
        result->source >= result->vertex_count ||
        result->visit_count == 0U ||
        result->visit_count > result->vertex_count) {
        return GRAPH_BFS_INVALID_RESULT;
    }

    for (index = 0U;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        position[index] = GRAPH_BFS_NO_VERTEX;
    }

    for (index = 0U; index < result->visit_count; ++index) {
        vertex = result->visit_order[index];
        if (vertex >= result->vertex_count || in_order[vertex]) {
            return GRAPH_BFS_INVALID_RESULT;
        }
        in_order[vertex] = true;
        position[vertex] = index;
    }
    for (index = result->visit_count;
         index < (size_t)GRAPH_MAX_VERTICES;
         ++index) {
        if (result->visit_order[index] != GRAPH_BFS_NO_VERTEX) {
            return GRAPH_BFS_INVALID_RESULT;
        }
    }

    if (result->visit_order[0] != result->source ||
        !result->discovered[result->source] ||
        result->distance[result->source] != 0U ||
        result->predecessor[result->source] != GRAPH_BFS_NO_VERTEX) {
        return GRAPH_BFS_INVALID_RESULT;
    }

    for (vertex = 0U;
         vertex < (size_t)GRAPH_MAX_VERTICES;
         ++vertex) {
        if (vertex >= result->vertex_count) {
            if (result->discovered[vertex] ||
                result->distance[vertex] != GRAPH_BFS_NO_DISTANCE ||
                result->predecessor[vertex] != GRAPH_BFS_NO_VERTEX) {
                return GRAPH_BFS_INVALID_RESULT;
            }
            continue;
        }

        if (!result->discovered[vertex]) {
            if (in_order[vertex] ||
                result->distance[vertex] != GRAPH_BFS_NO_DISTANCE ||
                result->predecessor[vertex] != GRAPH_BFS_NO_VERTEX) {
                return GRAPH_BFS_INVALID_RESULT;
            }
            continue;
        }

        discovered_count += 1U;
        if (!in_order[vertex] ||
            result->distance[vertex] >= result->vertex_count) {
            return GRAPH_BFS_INVALID_RESULT;
        }

        if (vertex != result->source) {
            size_t predecessor = result->predecessor[vertex];

            if (result->distance[vertex] == 0U ||
                predecessor >= result->vertex_count ||
                !result->discovered[predecessor] ||
                result->distance[predecessor] >= result->vertex_count ||
                result->distance[predecessor] + 1U !=
                    result->distance[vertex] ||
                position[predecessor] >= position[vertex]) {
                return GRAPH_BFS_INVALID_RESULT;
            }
        }
    }

    if (discovered_count != result->visit_count) {
        return GRAPH_BFS_INVALID_RESULT;
    }

    for (index = 1U; index < result->visit_count; ++index) {
        size_t previous = result->visit_order[index - 1U];
        size_t current = result->visit_order[index];

        if (result->distance[previous] > result->distance[current]) {
            return GRAPH_BFS_INVALID_RESULT;
        }
    }

    return GRAPH_BFS_OK;
}

const char *graph_bfs_status_name(GraphBfsStatus status)
{
    switch (status) {
        case GRAPH_BFS_OK:
            return "ok";
        case GRAPH_BFS_INVALID_ARGUMENT:
            return "invalid argument";
        case GRAPH_BFS_OUT_OF_RANGE:
            return "source or destination vertex out of range";
        case GRAPH_BFS_INVALID_GRAPH:
            return "graph does not satisfy required representation rules";
        case GRAPH_BFS_LIMIT:
            return "vertex Queue limit reached or requested limit too large";
        case GRAPH_BFS_UNREACHABLE:
            return "destination is unreachable from the source";
        case GRAPH_BFS_INVALID_RESULT:
            return "BFS result is invalid";
        default:
            return "unknown GraphBfsStatus";
    }
}
