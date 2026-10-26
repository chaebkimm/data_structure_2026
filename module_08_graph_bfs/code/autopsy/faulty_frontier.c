#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum {
    AUTOPSY_VERTEX_COUNT = 5,
    AUTOPSY_QUEUE_CAPACITY = 8
};

typedef struct {
    size_t data[AUTOPSY_QUEUE_CAPACITY];
    size_t head;
    size_t size;
} PendingQueue;

static bool add_pending(PendingQueue *queue, size_t vertex)
{
    size_t tail;

    if (vertex >= (size_t)AUTOPSY_VERTEX_COUNT ||
        queue->size >= (size_t)AUTOPSY_QUEUE_CAPACITY) {
        return false;
    }

    tail = (queue->head + queue->size) %
        (size_t)AUTOPSY_QUEUE_CAPACITY;
    queue->data[tail] = vertex;
    queue->size += 1U;
    return true;
}

static bool take_pending(PendingQueue *queue, size_t *out_vertex)
{
    size_t new_size;

    if (out_vertex == NULL || queue->size == 0U) {
        return false;
    }

    *out_vertex = queue->data[queue->head];
    new_size = queue->size - 1U;
    queue->head = new_size == 0U
        ? 0U
        : (queue->head + 1U) %
            (size_t)AUTOPSY_QUEUE_CAPACITY;
    queue->size = new_size;
    return true;
}

static void print_pending(const PendingQueue *queue)
{
    size_t offset;

    putchar('[');
    for (offset = 0U; offset < queue->size; ++offset) {
        size_t index = (queue->head + offset) %
            (size_t)AUTOPSY_QUEUE_CAPACITY;

        if (offset > 0U) {
            fputs(", ", stdout);
        }
        printf("%zu", queue->data[index]);
    }
    puts("]");
}

static bool observe(
    const bool edges[AUTOPSY_VERTEX_COUNT][AUTOPSY_VERTEX_COUNT]
)
{
    PendingQueue queue = {{0U}, 0U, 0U};
    bool handled[AUTOPSY_VERTEX_COUNT] = {false};
    size_t distance[AUTOPSY_VERTEX_COUNT];
    size_t predecessor[AUTOPSY_VERTEX_COUNT];
    size_t removal_order[AUTOPSY_QUEUE_CAPACITY];
    size_t removal_count = 0U;
    size_t vertex;

    for (vertex = 0U;
         vertex < (size_t)AUTOPSY_VERTEX_COUNT;
         ++vertex) {
        distance[vertex] = (size_t)AUTOPSY_VERTEX_COUNT;
        predecessor[vertex] = (size_t)AUTOPSY_VERTEX_COUNT;
    }

    if (!add_pending(&queue, 0U)) {
        return false;
    }
    distance[0] = 0U;

    while (take_pending(&queue, &vertex)) {
        size_t neighbor;

        if (removal_count >= (size_t)AUTOPSY_QUEUE_CAPACITY) {
            return false;
        }
        removal_order[removal_count] = vertex;
        removal_count += 1U;

        printf("remove %zu; pending ", vertex);
        print_pending(&queue);

        if (handled[vertex]) {
            continue;
        }
        handled[vertex] = true;

        for (neighbor = 0U;
             neighbor < (size_t)AUTOPSY_VERTEX_COUNT;
             ++neighbor) {
            if (edges[vertex][neighbor] && !handled[neighbor]) {
                if (!add_pending(&queue, neighbor)) {
                    return false;
                }
                distance[neighbor] = distance[vertex] + 1U;
                predecessor[neighbor] = vertex;
                printf(
                    "  schedule %zu from %zu; pending ",
                    neighbor,
                    vertex
                );
                print_pending(&queue);
            }
        }
    }

    fputs("removal order: ", stdout);
    for (vertex = 0U; vertex < removal_count; ++vertex) {
        if (vertex > 0U) {
            fputs(", ", stdout);
        }
        printf("%zu", removal_order[vertex]);
    }
    putchar('\n');

    printf(
        "predecessors: 0:%zu 1:%zu 2:%zu 3:%zu 4:%zu\n",
        predecessor[0],
        predecessor[1],
        predecessor[2],
        predecessor[3],
        predecessor[4]
    );
    return true;
}

int main(void)
{
    const bool edges
        [AUTOPSY_VERTEX_COUNT][AUTOPSY_VERTEX_COUNT] = {
        {false, true,  true,  false, false},
        {false, false, false, true,  true},
        {false, false, false, true,  true},
        {true,  false, false, false, false},
        {false, false, false, false, false}
    };

    if (!observe(edges)) {
        puts("bounded observation refused");
        return 1;
    }
    return 0;
}
