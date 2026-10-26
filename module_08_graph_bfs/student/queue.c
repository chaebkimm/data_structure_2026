/* Module 8: compare array queues and reuse Module 7's linked queue.
 * Callers check full/empty conditions and reset independent queue runs.
 */
#ifndef MODULE_08_QUEUE_C
#define MODULE_08_QUEUE_C
#ifndef MODULE_07_LINKED_LIST_SOURCE_IMPORTED
#define MODULE_07_LINKED_LIST_SOURCE_IMPORTED
#include "module_07_linked_list/student/lab.c"
#endif

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
