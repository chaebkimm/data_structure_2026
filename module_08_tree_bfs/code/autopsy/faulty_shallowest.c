#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum {
    AUTOPSY_CAPACITY = 5
};

typedef struct DemoNode {
    char label;
    int key;
    struct DemoNode *left;
    struct DemoNode *right;
} DemoNode;

typedef struct {
    const DemoNode *node;
    size_t depth;
} PendingItem;

typedef struct {
    PendingItem data[AUTOPSY_CAPACITY];
    size_t head;
    size_t size;
} PendingQueue;

static bool add_pending(
    PendingQueue *queue,
    const DemoNode *node,
    size_t depth
)
{
    size_t tail;

    if (node == NULL) {
        return true;
    }
    if (queue->size == (size_t)AUTOPSY_CAPACITY) {
        return false;
    }

    tail = (queue->head + queue->size) % (size_t)AUTOPSY_CAPACITY;
    queue->data[tail].node = node;
    queue->data[tail].depth = depth;
    queue->size += 1U;
    return true;
}

static bool take_pending(PendingQueue *queue, PendingItem *out_item)
{
    if (queue->size == 0U) {
        return false;
    }

    *out_item = queue->data[queue->head];
    queue->size -= 1U;
    queue->head = queue->size == 0U
        ? 0U
        : (queue->head + 1U) % (size_t)AUTOPSY_CAPACITY;
    return true;
}

static bool observe_search(
    const DemoNode *root,
    int target,
    const DemoNode **out_match,
    size_t *out_depth
)
{
    PendingQueue queue = {0};
    PendingItem item;

    if (!add_pending(&queue, root, 0U)) {
        return false;
    }

    while (take_pending(&queue, &item)) {
        printf("%c ", item.node->label);

        if (item.node->key == target) {
            *out_match = item.node;
            *out_depth = item.depth;
            return true;
        }

        if (!add_pending(
                &queue,
                item.node->right,
                item.depth + 1U
            ) ||
            !add_pending(
                &queue,
                item.node->left,
                item.depth + 1U
            )) {
            return false;
        }
    }

    return false;
}

static void observe_complete(const DemoNode *root)
{
    PendingQueue queue = {0};
    PendingItem item;

    if (!add_pending(&queue, root, 0U)) {
        puts("setup refused");
        return;
    }

    while (take_pending(&queue, &item)) {
        printf("%c ", item.node->label);
        if (!add_pending(
                &queue,
                item.node->right,
                item.depth + 1U
            ) ||
            !add_pending(
                &queue,
                item.node->left,
                item.depth + 1U
            )) {
            puts("observation refused");
            return;
        }
    }
    putchar('\n');
}

int main(void)
{
    DemoNode nodes[5];
    const DemoNode *match = NULL;
    size_t depth = 0U;

    nodes[0] = (DemoNode){'A', 42, &nodes[1], &nodes[2]};
    nodes[1] = (DemoNode){'B', 17, &nodes[3], NULL};
    nodes[2] = (DemoNode){'C', 68, NULL, &nodes[4]};
    nodes[3] = (DemoNode){'D', 44, NULL, NULL};
    nodes[4] = (DemoNode){'E', 44, NULL, NULL};

    fputs("complete observation: ", stdout);
    observe_complete(&nodes[0]);

    fputs("search observation:   ", stdout);
    if (observe_search(&nodes[0], 44, &match, &depth)) {
        printf("\nmatch: %c at depth %zu\n", match->label, depth);
    } else {
        puts("\nno result");
    }

    return 0;
}
