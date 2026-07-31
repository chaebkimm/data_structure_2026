#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum {
    TRAINING_CAPACITY = 3
};

typedef struct {
    int data[TRAINING_CAPACITY];
    size_t head;
    size_t size;
} TrainingQueue;

/*
 * This bounded standalone program contains one intentional Queue-state
 * defect. Every physical index is checked before use.
 */
static bool training_enqueue(TrainingQueue *queue, int value)
{
    size_t insertion_index;

    if (queue->size == (size_t)TRAINING_CAPACITY) {
        return false;
    }

    insertion_index = queue->head + queue->size;
    if (insertion_index >= (size_t)TRAINING_CAPACITY) {
        return false;
    }

    queue->data[insertion_index] = value;
    queue->size += 1U;
    return true;
}

int main(void)
{
    TrainingQueue queue = {{10, 20, 30}, 1U, 2U};
    bool accepted;

    printf("before: %d,%d\n", queue.data[1], queue.data[2]);
    accepted = training_enqueue(&queue, 40);
    printf("enqueue 40 accepted: %s\n", accepted ? "yes" : "no");
    printf("size after attempt: %zu\n", queue.size);
    printf("after: %d,%d\n", queue.data[1], queue.data[2]);
    return 0;
}
