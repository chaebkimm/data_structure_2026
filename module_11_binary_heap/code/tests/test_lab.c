#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/* Keep the example available alongside the test driver's own main. */
#define main heap_example_main
#include "lab.c"
#undef main

static void assert_heap_order(void)
{
    for (int child = 1; child < size; ++child) {
        assert(pq[(child - 1) / 2] <= pq[child]);
    }
}

static void assert_heap_state(const int expected[], int count)
{
    assert(size == count);
    for (int i = 0; i < count; ++i) {
        assert(pq[i] == expected[i]);
    }
}

static void test_worked_example(void)
{
    pq[0] = 9;
    pq[1] = 6;
    pq[2] = 5;
    size = 3;
    heapify();
    assert_heap_state((int[]){5, 6, 9}, 3);

    enqueue(3);
    assert_heap_state((int[]){3, 5, 9, 6}, 4);
    enqueue(1);
    assert_heap_state((int[]){1, 3, 9, 6, 5}, 5);

    int sorted[CAPACITY];
    const int expected[] = {1, 3, 5, 6, 9};
    heap_sort(sorted);
    assert(size == 0);
    for (int i = 0; i < CAPACITY; ++i) {
        assert(sorted[i] == expected[i]);
    }
}

static void test_child_selection(void)
{
    init_pqueue();
    enqueue(1);
    assert(priority_child(0) == -1);

    enqueue(4);
    assert(priority_child(0) == 1);
    enqueue(4);
    assert(priority_child(0) == 1);  /* Equal children favor the left. */
    pq[2] = 3;
    assert(priority_child(0) == 2);
    assert(priority_child(1) == -1);

    init_pqueue();
    assert(size == 0);
}

static int ascending(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static void check_build_methods(const int input[], int count)
{
    int expected[CAPACITY];
    init_pqueue();
    for (int i = 0; i < count; ++i) {
        expected[i] = input[i];
        enqueue(input[i]);
        assert(size == i + 1);
        assert_heap_order();
    }
    qsort(expected, (size_t)count, sizeof(expected[0]), ascending);

    for (int i = 0; i < count; ++i) {
        int root = dequeue();
        assert(root == expected[i]);
        assert(size == count - i - 1);
        assert_heap_order();
    }

    for (int i = 0; i < count; ++i) {
        pq[i] = input[i];
    }
    size = count;
    heapify();
    assert(size == count);
    assert_heap_order();

    /* Check the first unused output slot even for a full or empty heap. */
    int sorted[CAPACITY + 1];
    sorted[count] = 42;
    heap_sort(sorted);
    assert(size == 0);
    for (int i = 0; i < count; ++i) {
        assert(sorted[i] == expected[i]);
    }
    assert(sorted[count] == 42);
}

static void check_all_inputs(int input[], int count)
{
    const int values[] = {INT_MIN, -1, 0, 1, INT_MAX};
    check_build_methods(input, count);
    if (count == CAPACITY) {
        return;
    }
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        input[count] = values[i];
        check_all_inputs(input, count + 1);
    }
}

int main(void)
{
    int input[CAPACITY];
    test_worked_example();
    test_child_selection();
    check_all_inputs(input, 0);
    puts("Module 11 core tests passed.");
    return 0;
}
