#include "linked_queue.h"
#include <assert.h>
#include <stdio.h>

static void test_fifo_and_reuse(void)
{
    LinkedQueue q = {0};
    int out = -99;
    assert(lq_is_valid(&q));
    assert(lq_dequeue(&q, &out) == LQ_EMPTY && out == -99);
    assert(lq_peek(&q, &out) == LQ_EMPTY && out == -99);
    for (int cycle = 0; cycle < 3; ++cycle) {
        assert(lq_enqueue(&q, 31) == LQ_OK);
        assert(q.head == q.tail && q.size == 1 && q.tail->next == NULL);
        assert(lq_enqueue(&q, 8) == LQ_OK);
        assert(lq_enqueue(&q, 47) == LQ_OK);
        assert(lq_peek(&q, &out) == LQ_OK && out == 31 && q.size == 3);
        assert(lq_dequeue(&q, &out) == LQ_OK && out == 31);
        assert(lq_enqueue(&q, 19) == LQ_OK);
        assert(lq_dequeue(&q, &out) == LQ_OK && out == 8);
        assert(lq_dequeue(&q, &out) == LQ_OK && out == 47);
        assert(lq_dequeue(&q, &out) == LQ_OK && out == 19);
        assert(q.head == NULL && q.tail == NULL && q.size == 0);
        assert(lq_is_valid(&q) && lq_test_live_nodes() == 0);
    }
    lq_destroy(&q);
    lq_destroy(&q);
}

static void test_failure_and_cleanup(void)
{
    LinkedQueue q = {0};
    QueueNode *head;
    QueueNode *tail;
    int out = 777;
    lq_test_fail_next_allocation();
    assert(lq_enqueue(&q, 1) == LQ_ALLOCATION);
    assert(lq_is_valid(&q) && q.size == 0 && lq_test_live_nodes() == 0);
    assert(lq_enqueue(&q, 2) == LQ_OK);
    assert(lq_enqueue(&q, 3) == LQ_OK);
    head = q.head;
    tail = q.tail;
    lq_test_fail_next_allocation();
    assert(lq_enqueue(&q, 4) == LQ_ALLOCATION);
    assert(q.head == head && q.tail == tail && q.size == 2);
    assert(head->value == 2 && head->next == tail && tail->value == 3);
    assert(tail->next == NULL && lq_test_live_nodes() == 2);
    assert(lq_dequeue(&q, NULL) == LQ_ARGUMENT && q.size == 2);
    assert(lq_dequeue(NULL, &out) == LQ_ARGUMENT && out == 777);
    assert(lq_enqueue(NULL, 1) == LQ_ARGUMENT);
    lq_destroy(&q);
    assert(lq_is_valid(&q) && lq_test_live_nodes() == 0);
}

int main(void)
{
    test_fifo_and_reuse();
    test_failure_and_cleanup();
    puts("Linked Queue core tests passed");
    return 0;
}
