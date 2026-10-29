#include <string.h>
#include "lab_test_support.h"

static void expect_partition(const int *owned, int owned_count)
{
    int seen[CAPACITY] = {0};
    for (int i = 0; i < owned_count; ++i) {
        CHECK(owned[i] >= 0 && owned[i] < CAPACITY && !seen[owned[i]]);
        seen[owned[i]] = 1;
    }
    int count = owned_count;
    for (int node = free_head; node != -1; node = lnodes[node].next) {
        CHECK(node >= 0 && node < CAPACITY && !seen[node]);
        seen[node] = 1;
        ++count;
    }
    CHECK(count == CAPACITY);
}

static void expect_state(const struct Linked_Node saved[CAPACITY],
                         int saved_free, int saved_head, int saved_tail)
{
    CHECK(free_head == saved_free && qhead == saved_head && qtail == saved_tail);
    for (int i = 0; i < CAPACITY; ++i) {
        CHECK(lnodes[i].data == saved[i].data);
        CHECK(lnodes[i].next == saved[i].next);
    }
}

static void test_pool_exhaustion_and_one_time_init(void)
{
    expect_clean_lab();
    int owned[CAPACITY];
    for (int i = 0; i < CAPACITY; ++i) {
        CHECK(lnodes[i].data == 0); /* Static initial storage, not an allocator promise. */
        CHECK(lnodes[i].next == (i == CAPACITY - 1 ? -1 : i + 1));
        owned[i] = allocate_value(100 + i);
        CHECK(owned[i] == i);
    }
    expect_partition(owned, CAPACITY);
    struct Linked_Node saved[CAPACITY];
    memcpy(saved, lnodes, sizeof saved);
    int exhausted = new_lnode();
    CHECK(exhausted == -1);
    expect_state(saved, -1, -1, -1);
    free_lnode(-1); /* Only the -1 sentinel has a defined no-op contract. */
    enqueue_lnode(-1);
    init_lnodes_pool(); /* Cannot reset an allocated pool or erase its values. */
    expect_state(saved, -1, -1, -1);

    int recycled = owned[4];
    free_lnode(recycled);
    CHECK(free_head == recycled && lnodes[recycled].next == -1);
    int reused = new_lnode();
    CHECK(reused == recycled && lnodes[reused].data == 104);
    CHECK(lnodes[reused].next == -1); /* Allocation does not initialize data. */
    for (int i = 0; i < CAPACITY; ++i) free_lnode(owned[i]);
    expect_clean_lab();
}

static void test_insertion_detachment_and_shared_reuse(void)
{
    expect_clean_lab();
    int first = allocate_value(17), middle = allocate_value(23);
    int last = allocate_value(31), other = allocate_value(90);
    int owned[] = {first, middle, last, other};
    simple_link_lnode_to_prev(first, last);
    simple_link_lnode_to_prev(first, middle);
    CHECK(lnodes[first].next == middle && lnodes[middle].next == last);
    CHECK(lnodes[last].next == -1 && lnodes[other].next == -1);
    expect_partition(owned, 4);
    int saved_free = free_head;
    int detached = simple_delink_next_lnode_from_prev(first);
    CHECK(detached == middle && lnodes[first].next == last);
    CHECK(lnodes[detached].next == -1 && free_head == saved_free);
    free_lnode(detached);
    int reused = allocate_value(8);
    CHECK(reused == middle);
    simple_link_lnode_to_prev(other, reused); /* The other list shares the pool. */
    CHECK(lnodes[other].next == reused && lnodes[reused].next == -1);
    CHECK(lnodes[first].next == last && lnodes[last].data == 31);
    expect_partition(owned, 4);

    struct Linked_Node saved[CAPACITY];
    memcpy(saved, lnodes, sizeof saved);
    int absent = simple_delink_next_lnode_from_prev(last);
    CHECK(absent == -1);
    expect_state(saved, saved_free, -1, -1);
    detached = simple_delink_next_lnode_from_prev(first);
    CHECK(detached == last && lnodes[first].next == -1);
    free_lnode(detached);
    free_lnode(first);
    detached = simple_delink_next_lnode_from_prev(other);
    CHECK(detached == reused);
    free_lnode(detached);
    free_lnode(other);
    expect_clean_lab();
}

static void test_caller_owned_stack(void)
{
    expect_clean_lab();
    int first = -1;
    const int values[] = {17, 23, 31};
    for (int i = 0; i < 3; ++i) {
        int node = allocate_value(values[i]);
        lnodes[node].next = first;
        first = node;
    }
    for (int i = 2; i >= 0; --i) {
        CHECK(first != -1);
        int removed = first;
        int value = lnodes[removed].data;
        first = lnodes[removed].next;
        lnodes[removed].next = -1; /* Isolate before passing to free_lnode. */
        free_lnode(removed);
        CHECK(value == values[i]);
    }
    CHECK(first == -1);
    expect_clean_lab();
}

static void test_index_queue_and_recycling(void)
{
    expect_clean_lab();
    struct Linked_Node saved[CAPACITY];
    memcpy(saved, lnodes, sizeof saved);
    int saved_free = free_head;
    int empty = dequeue_lnode();
    CHECK(empty == -1);
    expect_state(saved, saved_free, -1, -1);
    int slots[CAPACITY];
    for (int i = 0; i < CAPACITY; ++i) {
        slots[i] = allocate_value(i == 0 ? -1 : 100 + i);
        enqueue_lnode(slots[i]);
        CHECK(qhead == slots[0] && qtail == slots[i]);
        CHECK(lnodes[qtail].next == -1);
    }
    expect_partition(slots, CAPACITY);
    memcpy(saved, lnodes, sizeof saved);
    init_lnodes_pool();
    expect_state(saved, -1, slots[0], slots[CAPACITY - 1]);
    int exhausted = new_lnode();
    CHECK(exhausted == -1);
    enqueue_lnode(exhausted);
    expect_state(saved, -1, slots[0], slots[CAPACITY - 1]);
    for (int i = 0; i < CAPACITY; ++i) {
        int node = dequeue_lnode();
        CHECK(node == slots[i] && lnodes[node].next == -1);
        CHECK(lnodes[node].data == (i == 0 ? -1 : 100 + i));
        CHECK(free_head == (i == 0 ? -1 : slots[i - 1]));
        if (i + 1 < CAPACITY) CHECK(qhead == slots[i + 1]);
        else CHECK(qhead == -1 && qtail == -1);
        free_lnode(node); /* Dequeue returns an index and does not recycle it. */
    }
    expect_clean_lab();
    for (int i = 0; i < 30; ++i) {
        int node = allocate_value(i);
        enqueue_lnode(node);
        CHECK(qhead == node && qtail == node);
        int removed = dequeue_lnode();
        CHECK(removed == node && lnodes[removed].data == i);
        CHECK(is_empty_queue() && qhead == -1 && qtail == -1);
        free_lnode(removed);
        expect_clean_lab();
    }
}

int main(void)
{
    test_pool_exhaustion_and_one_time_init();
    test_insertion_detachment_and_shared_reuse();
    test_caller_owned_stack();
    test_index_queue_and_recycling();
    puts("Week 7 linked-list core tests passed.");
    return 0;
}
