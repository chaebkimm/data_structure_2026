#include <assert.h>
#include <stdio.h>
#include "lab.c"

/* Tests include the supplied source once; it has no main function. */
static void assert_integer_order(void)
{
    for (int i = 1; i < size; ++i) {
        assert(comp(parent(i), i));
    }
}

static void assert_full_order(struct Heap_Full *h, int *positions)
{
    int seen[10] = {0};
    for (int i = 0; i < 10; ++i) {
        int id = h->array[i];
        assert(id >= 0 && id < 10);
        assert(!seen[id]);
        seen[id] = 1;
        assert(positions[id] == i);
        if (i > 0) {
            assert(h->comp(h->array[_parent(i)], id));
        }
    }
}

static void assert_both_orders(void)
{
    assert_full_order(&max_on_heap, _max_heap_pos);
    assert_full_order(&min_off_heap, _min_heap_pos);
}

static void fill_wide_intervals(void)
{
    for (int id = 0; id < 10; ++id) {
        interval_size[id] = 1;
        toggle_info[id][0] = 0;
        toggle_info[id][1] = 100;
    }
}

static void test_indexes_and_ties(void)
{
    init_heap();
    assert(size == 0 && is_min_heap == 1);
    assert(parent(0) == -1 && parent(-1) == -1);
    assert(left(0) == -1 && right(0) == -1);
    assert(proper_parent(-1, -1) == -1);
    assert(proper_parent(-1, 0) == 0);
    assert(proper_parent(0, -1) == 0);
    add(7);
    add(7);
    assert(comp(0, 1) && comp(1, 0));
    assert(proper_parent(0, 1) == 0);
    assert(proper_parent(1, 0) == 1);
    assert(left(0) == 1 && right(0) == -1);
    assert(remove_root() == 7 && size == 1);
    assert(remove_root() == 7 && size == 0);
    /* Do not remove from empty storage: the source has no guard. */
}

static void test_add_remove_min_max(void)
{
    const int input[10] = {7, 3, 8, 1, 4, 6, 2, 9, 5, 3};
    const int sorted[10] = {1, 2, 3, 3, 4, 5, 6, 7, 8, 9};
    for (int mode = 0; mode <= 1; ++mode) {
        init_heap();
        is_min_heap = mode;
        for (int i = 0; i < 10; ++i) {
            add(input[i]);
            assert(size == i + 1);
            assert_integer_order();
        }
        assert(left(4) == 9 && right(4) == -1);
        for (int i = 0; i < 10; ++i) {
            int expected = mode ? sorted[i] : sorted[9 - i];
            assert(remove_root() == expected);
            assert_integer_order();
        }
        assert(size == 0);
    }
}

static void test_bottom_up_and_mode_switch(void)
{
    const int input[7] = {7, 3, 8, 1, 4, 6, 2};
    const int expected[7] = {1, 3, 2, 7, 4, 6, 8};
    init_heap();
    heapify();
    assert(size == 0);
    size = 7;
    for (int i = 0; i < size; ++i) { heap[i] = input[i]; }
    heapify();
    assert_integer_order();
    for (int i = 0; i < size; ++i) { assert(heap[i] == expected[i]); }
    is_min_heap = 0;
    heapify();
    assert_integer_order();
    assert(heap[0] == 8);
    int previous = remove_root();
    while (size > 0) {
        int next = remove_root();
        assert(previous >= next);
        previous = next;
    }
    add(-4);
    heapify();
    assert(remove_root() == -4 && size == 0);
}

static void test_teaching_fixture(void)
{
    const int input[6] = {7, 3, 5, 1, 9, 4};
    const int built[6] = {1, 3, 4, 7, 9, 5};
    const int removed[5] = {3, 5, 4, 7, 9};
    const int rebuilt[6] = {9, 7, 5, 1, 3, 4};
    init_heap();
    for (int i = 0; i < 6; ++i) { add(input[i]); }
    for (int i = 0; i < 6; ++i) { assert(heap[i] == built[i]); }
    assert(remove_root() == 1);
    for (int i = 0; i < 5; ++i) { assert(heap[i] == removed[i]); }
    size = 6;
    for (int i = 0; i < 6; ++i) { heap[i] = input[i]; }
    heapify();
    for (int i = 0; i < 6; ++i) { assert(heap[i] == built[i]); }
    is_min_heap = 0;
    heapify();
    for (int i = 0; i < 6; ++i) { assert(heap[i] == rebuilt[i]); }

    fill_wide_intervals();
    interval_size[0] = interval_size[1] = 2;
    toggle_info[0][0] = 1; toggle_info[0][1] = 3;
    toggle_info[0][2] = 7; toggle_info[0][3] = 10;
    toggle_info[1][0] = 2; toggle_info[1][1] = 5;
    toggle_info[1][2] = 8; toggle_info[1][3] = 12;
    for (int id = 2; id < 10; ++id) {
        toggle_info[id][0] = 4;
        toggle_info[id][1] = 9;
    }
    _init_heaps();
    assert(get_on_time(_get_root(&max_on_heap)) == 4);
    assert(get_off_time(_get_root(&min_off_heap)) == 3);
    assert(all_on_time() == 8);
    assert(epoch[0] == 1 && epoch[1] == 1);
    assert_both_orders();
    toggle_info[1][2] = 9;
    assert(all_on_time() == 9);
    assert_both_orders();
}

static void test_full_indexes_maps_and_repairs(void)
{
    for (int id = 0; id < 10; ++id) {
        interval_size[id] = 2;
        toggle_info[id][0] = id;
        toggle_info[id][1] = 20 + id;
        toggle_info[id][2] = 40 + id;
        toggle_info[id][3] = 60 + id;
    }
    _init_heaps();
    assert(_parent(0) == -1 && _left(4) == 9 && _right(4) == -1);
    assert(_left(5) == -1 && _right(5) == -1);
    assert(_proper_parent(&min_off_heap, -1, -1) == -1);
    assert(_proper_parent(&min_off_heap, -1, 0) == 0);
    assert(_proper_parent(&min_off_heap, 0, -1) == 0);
    assert_both_orders();
    assert(_get_root(&max_on_heap) == 9);
    assert(_get_root(&min_off_heap) == 0);

    /* One later interval makes the on key move up, and the off key down. */
    epoch[0] = 1;
    _reheapify(&min_off_heap, _min_heap_pos[0]);
    _reheapify(&max_on_heap, _max_heap_pos[0]);
    assert_both_orders();
    assert(_get_root(&max_on_heap) == 0);
    assert(_get_root(&min_off_heap) == 1);

    /* General key-update repair also supports a decrease. */
    epoch[0] = 0;
    _reheapify(&min_off_heap, _min_heap_pos[0]);
    _reheapify(&max_on_heap, _max_heap_pos[0]);
    assert_both_orders();
    assert(_get_root(&max_on_heap) == 9);
    assert(_get_root(&min_off_heap) == 0);

    _swap_max(2, 7);
    for (int i = 0; i < 10; ++i) {
        assert(_max_heap_pos[max_on_heap.array[i]] == i);
    }
    _swap_max(2, 7);
    _swap_min(4, 9);
    for (int i = 0; i < 10; ++i) {
        assert(_min_heap_pos[min_off_heap.array[i]] == i);
    }
    _swap_min(4, 9);
    assert_both_orders();
}

static void test_common_times_and_exhaustion(void)
{
    fill_wide_intervals();
    toggle_info[0][0] = 5;
    toggle_info[1][1] = 5;
    assert(all_on_time() == 5); /* Closed intervals include the endpoint. */
    assert(check_all_on());
    assert_both_orders();

    for (int id = 0; id < 10; ++id) {
        toggle_info[id][0] = 5;
        toggle_info[id][1] = 5;
    }
    assert(all_on_time() == 5); /* A closed interval may have zero duration. */
    assert_both_orders();

    fill_wide_intervals();
    interval_size[0] = 3;
    toggle_info[0][0] = 0; toggle_info[0][1] = 1;
    toggle_info[0][2] = 4; toggle_info[0][3] = 5;
    toggle_info[0][4] = 8; toggle_info[0][5] = 12;
    toggle_info[1][0] = 7;
    assert(all_on_time() == 8);
    assert(epoch[0] == 2);
    assert_both_orders();
    assert(all_on_time() == 8); /* Initialization resets epochs each call. */

    fill_wide_intervals();
    toggle_info[0][0] = 0; toggle_info[0][1] = 1;
    toggle_info[1][0] = 2; toggle_info[1][1] = 3;
    assert(all_on_time() == -1);
    assert(epoch[0] == interval_size[0]);
    /* The exhausted epoch is one-past-last: do not read its interval. */

    fill_wide_intervals();
    interval_size[0] = 5;
    for (int e = 0; e < 5; ++e) {
        toggle_info[0][2 * e] = 2 * e;
        toggle_info[0][2 * e + 1] = 2 * e + 1;
    }
    toggle_info[1][0] = 10;
    toggle_info[1][1] = 20;
    assert(all_on_time() == -1);
    assert(epoch[0] == 5);
    /* The return must precede a getter at column 10, outside the row. */
    fill_wide_intervals();
    assert(all_on_time() == 0);
    assert_both_orders();
}

static unsigned int random_state = 2026U;
static unsigned int next_random(void)
{
    random_state = random_state * 1664525U + 1013904223U;
    return random_state;
}

static int brute_force_time(void)
{
    for (int time = 0; time <= 80; ++time) {
        int all = 1;
        for (int id = 0; id < 10; ++id) {
            int on = 0;
            for (int e = 0; e < interval_size[id]; ++e) {
                if (toggle_info[id][2 * e] <= time &&
                    time <= toggle_info[id][2 * e + 1]) {
                    on = 1;
                }
            }
            if (!on) { all = 0; break; }
        }
        if (all) { return time; }
    }
    return -1;
}

static void test_differential_common_times(void)
{
    int successes = 0;
    int misses = 0;
    for (int trial = 0; trial < 1000; ++trial) {
        for (int id = 0; id < 10; ++id) {
            int cursor = (int)(next_random() % 9U);
            interval_size[id] = 1 + (int)(next_random() % 5U);
            for (int e = 0; e < interval_size[id]; ++e) {
                int duration = 1 + (int)(next_random() % 8U);
                toggle_info[id][2 * e] = cursor;
                toggle_info[id][2 * e + 1] = cursor + duration;
                cursor += duration + 1 + (int)(next_random() % 3U);
            }
        }
        int expected = brute_force_time();
        int actual = all_on_time();
        assert(actual == expected);
        if (actual == -1) { ++misses; }
        else { ++successes; assert_both_orders(); }
    }
    assert(successes > 0 && misses > 0);
}

int main(void)
{
    test_indexes_and_ties();
    test_add_remove_min_max();
    test_bottom_up_and_mode_switch();
    test_teaching_fixture();
    test_full_indexes_maps_and_repairs();
    test_common_times_and_exhaustion();
    test_differential_common_times();
    puts("Module 10 lab: 7 test groups passed (1000 differential cases).");
    return 0;
}
