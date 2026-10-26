#include "lab_test_support.h"

static void expect_free_count(int expected)
{
    int seen[10] = {0};
    int count = 0;
    for (int node = free_head; node != -1; node = lnodes[node].next) {
        assert(node >= 0 && node < 10);
        assert(!seen[node]);
        seen[node] = 1;
        ++count;
        assert(count <= 10);
    }
    assert(count == expected);
}

static void expect_nodes_equal(const struct Linked_Node saved[10],
                               int saved_free_head)
{
    assert(free_head == saved_free_head);
    for (int i = 0; i < 10; ++i) {
        assert(lnodes[i].data == saved[i].data);
        assert(lnodes[i].next == saved[i].next);
    }
}

static void test_pool_exhaustion_and_reuse(void)
{
    struct Linked_Node saved[10];
    reset_lab();
    expect_free_count(10);
    for (int i = 0; i < 10; ++i) {
        assert(lnodes[i].data == 0);
        assert(lnodes[i].next == (i == 9 ? -1 : i + 1));
        int node = new_lnode(100 + i, -1);
        assert(node == i);
        assert(lnodes[node].data == 100 + i);
        assert(lnodes[node].next == -1);
    }
    expect_free_count(0);
    for (int i = 0; i < 10; ++i) {
        saved[i] = lnodes[i];
    }
    assert(new_lnode(999, -1) == -1);
    expect_nodes_equal(saved, -1);
    free_lnode(-1);
    free_lnode(10);
    expect_nodes_equal(saved, -1);

    /* All ten allocated slots are detached; returning slot 4 is valid. */
    free_lnode(4);
    assert(free_head == 4 && lnodes[4].next == -1);
    expect_free_count(1);
    assert(new_lnode(-7, -1) == 4);
    assert(lnodes[4].data == -7 && lnodes[4].next == -1);
    expect_free_count(0);
    for (int i = 0; i < 10; ++i) {
        free_lnode(i);
    }
    expect_free_count(10);
}

static void test_insertion_detachment_and_reuse(void)
{
    reset_lab();
    int first = new_lnode(17, -1);
    int middle = new_lnode(23, -1);
    int last = new_lnode(31, -1);
    assert(first == 0 && middle == 1 && last == 2);
    link_lnode(first, last);
    link_lnode(first, middle);
    assert(lnodes[first].next == middle);
    assert(lnodes[middle].next == last);
    assert(lnodes[last].next == -1);
    assert(lnodes[first].data == 17 && lnodes[middle].data == 23);
    assert(lnodes[last].data == 31);

    int detached = delete_next_lnode(first);
    assert(detached == middle && lnodes[first].next == last);
    assert(lnodes[detached].next == last); /* Detach does not clear the link. */
    assert(free_head == 3);              /* Detach does not free a slot. */
    expect_free_count(7);
    free_lnode(detached);
    assert(free_head == middle && lnodes[middle].next == 3);
    assert(new_lnode(8, -1) == middle);
    assert(lnodes[middle].data == 8 && lnodes[middle].next == -1);

    struct Linked_Node saved[10];
    for (int i = 0; i < 10; ++i) {
        saved[i] = lnodes[i];
    }
    assert(delete_next_lnode(last) == -1);
    expect_nodes_equal(saved, 3);
    assert(delete_next_lnode(first) == last);
    assert(lnodes[first].next == -1);
    free_lnode(last);
    free_lnode(first);
    free_lnode(middle);
    expect_free_count(10);
}

static void test_supplied_successor_and_first_removal(void)
{
    reset_lab();
    int first = new_lnode(31, -1);
    int added = new_lnode(23, first);
    assert(added != -1 && lnodes[added].next == first);
    first = added;
    added = new_lnode(17, first);
    assert(added != -1 && lnodes[added].next == first);
    first = added;
    assert(lnodes[first].data == 17);
    int removed = first;
    first = lnodes[first].next;
    free_lnode(removed);
    assert(lnodes[first].data == 23 && free_head == removed);
    assert(lnodes[removed].next == 3);
    expect_free_count(8);
}

static void test_linked_queue_example(void)
{
    struct Linked_Node saved[10];
    reset_lab();
    assert(is_empty_queue() && head == -1 && tail == -1);
    int empty_slot = dequeue_lnode();
    assert(empty_slot == -1);
    expect_free_count(10);
    for (int i = 0; i < 10; ++i) {
        bool added = enqueue(100 + i);
        assert(added);
        assert(head == 0 && tail == i && lnodes[tail].next == -1);
    }
    for (int i = 0; i < 10; ++i) saved[i] = lnodes[i];
    int saved_head = head, saved_tail = tail;
    bool added = enqueue(999);
    assert(!added && head == saved_head && tail == saved_tail);
    expect_nodes_equal(saved, -1);
    int value = dequeue();
    assert(value == 100 && head == 1 && tail == 9 && free_head == 0);
    added = enqueue(999);
    assert(added && head == 1 && tail == 0 && lnodes[9].next == 0);
    for (int i = 1; i < 10; ++i) {
        assert(!is_empty_queue());
        value = dequeue();
        assert(value == 100 + i);
    }
    assert(head == 0 && tail == 0);
    value = dequeue();
    assert(value == 999 && is_empty_queue() && head == -1 && tail == -1);
    expect_free_count(10);

    /* A payload of -1 is valid; only the raw helper uses -1 for no slot. */
    added = enqueue(-1);
    assert(added && !is_empty_queue());
    value = dequeue();
    assert(value == -1 && is_empty_queue());
    expect_free_count(10);

    /* The raw helper detaches but does not recycle its index. */
    int first = new_lnode(17, -1), second = new_lnode(23, -1);
    assert(first != -1 && second != -1);
    enqueue_lnode(first);
    enqueue_lnode(second);
    int removed = dequeue_lnode();
    assert(removed == first && lnodes[removed].data == 17);
    assert(head == second && tail == second && lnodes[removed].next == second);
    expect_free_count(8);
    free_lnode(removed);
    value = dequeue();
    assert(value == 23 && is_empty_queue());
    expect_free_count(10);

    for (int i = 0; i < 30; ++i) {
        added = enqueue(i);
        assert(added && head == tail);
        value = dequeue();
        assert(value == i && is_empty_queue() && head == -1 && tail == -1);
        expect_free_count(10);
    }
}

int main(void)
{
    test_pool_exhaustion_and_reuse();
    test_insertion_detachment_and_reuse();
    test_supplied_successor_and_first_removal();
    test_linked_queue_example();
    puts("Week 7 linked-list core tests passed.");
    return 0;
}
