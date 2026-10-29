/* Module 8: compare array queues and reuse Module 7's linked node queue.
 * Value adapters below allocate/write/enqueue, then dequeue/read/recycle.
 * The imported pool initializes once; drain every owner between independent runs.
 */
#ifndef MODULE_08_QUEUE_C
#define MODULE_08_QUEUE_C
#include <assert.h>
#include <stdbool.h>
#ifndef MODULE_07_LINKED_LIST_SOURCE_IMPORTED
#define MODULE_07_LINKED_LIST_SOURCE_IMPORTED
#include "module_07_linked_list/student/lab.c"
#endif

/* Module 8 convenience interface, built on Module 7's index operations. */
bool enqueue(int value) {
    int node = new_lnode();
    if (node == -1) { return false; }
    lnodes[node].data = value;
    enqueue_lnode(node);
    return true;
}

/* Caller guarantees nonempty; a payload of -1 is valid. */
int dequeue(void) {
    assert(!is_empty_queue());
    int node = dequeue_lnode();
    int value = lnodes[node].data;
    free_lnode(node);
    return value;
}

int queue[25];
int front = 0;
int rear = -1;

void enqueue_linear(int data) {
    queue[++rear] = data;
}

int dequeue_linear() {
    return queue[front++];
}

int is_full_linear() {
    return rear + 1 == 25;
}

int is_empty_linear() {
    return front == rear + 1;
}

void enqueue_circular(int data) {
    rear = (rear + 1) % 25;
    queue[rear] = data;
}

int dequeue_circular() {
    int data = queue[front];
    front = (front + 1) % 25;
    return data;
}

int is_full_circular() {
    return front == (rear + 2) % 25;
}

int is_empty_circular() {
    return front == (rear + 1) % 25;
}

#endif
