#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab.c"

static int compare_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y); /* Subtraction would overflow for extreme keys. */
}

static int oracle_first(const int values[], int n, int key) {
    for (int i = 0; i < n; ++i) if (values[i] == key) return i;
    return -1;
}

static void check_fixture(const int input[], int n) {
    int a[SEARCH_SORT_CAPACITY + 2], b[SEARCH_SORT_CAPACITY + 2];
    int scratch[SEARCH_SORT_CAPACITY + 2], expected[SEARCH_SORT_CAPACITY];
    int saved[SEARCH_SORT_CAPACITY];
    for (int i = 0; i < SEARCH_SORT_CAPACITY + 2; ++i) {
        a[i] = b[i] = scratch[i] = 123456789;
    }
    for (int i = 0; i < n; ++i) a[i+1] = b[i+1] = expected[i] = saved[i] = input[i];
    for (int key = -9; key <= 9; ++key)
        assert(linear_search(input, n, key) == oracle_first(input, n, key));
    for (int i = 0; i < n; ++i)
        assert(linear_search(input, n, input[i]) == oracle_first(input, n, input[i]));
    assert(memcmp(input, saved, (size_t)n * sizeof(int)) == 0);
    qsort(expected, (size_t)n, sizeof(int), compare_int);
    insertion_sort(a + 1, n);
    merge_sort(b + 1, scratch + 1, n);
    for (int i = 0; i < n; ++i) assert(a[i+1] == expected[i] && b[i+1] == expected[i]);
    assert(a[0] == 123456789 && b[0] == 123456789 && scratch[0] == 123456789);
    for (int i = n + 1; i < SEARCH_SORT_CAPACITY + 2; ++i)
        assert(a[i] == 123456789 && b[i] == 123456789 && scratch[i] == 123456789);
    for (int key = -9; key <= 9; ++key)
        assert(binary_search_first(b + 1, n, key) == oracle_first(expected, n, key));
    for (int i = 0; i < n; ++i)
        assert(binary_search_first(b + 1, n, expected[i]) == oracle_first(expected, n, expected[i]));
    assert(memcmp(b + 1, expected, (size_t)n * sizeof(int)) == 0);
    /* Repeated sorting is safe, including scratch left by the previous run. */
    merge_sort(b + 1, scratch + 1, n);
    insertion_sort(a + 1, n);
    for (int i = 0; i < n; ++i) assert(a[i+1] == expected[i] && b[i+1] == expected[i]);
}

int main(void) {
    assert(linear_search(NULL, 0, 17) == -1);
    assert(binary_search_first(NULL, 0, 17) == -1);
    insertion_sort(NULL, 0);
    merge_sort(NULL, NULL, 0);
    const int canonical[] = {31, 23, 17, 8, 17, 42};
    const int extremes[] = {INT_MAX, 0, INT_MIN, INT_MAX, -1, INT_MIN};
    check_fixture(canonical, 6);
    check_fixture(extremes, 6);
    int values[SEARCH_SORT_CAPACITY];
    uint32_t state = UINT32_C(130014);
    for (int n = 0; n <= SEARCH_SORT_CAPACITY; ++n) {
        for (int i = 0; i < n; ++i) values[i] = i;
        check_fixture(values, n);
        for (int i = 0; i < n; ++i) values[i] = n - i;
        check_fixture(values, n);
        for (int i = 0; i < n; ++i) values[i] = 17;
        check_fixture(values, n);
        for (int repeat = 0; repeat < 8; ++repeat) {
            for (int i = 0; i < n; ++i) {
                state = state * UINT32_C(1664525) + UINT32_C(1013904223);
                values[i] = (int)(state % UINT32_C(17)) - 8;
            }
            check_fixture(values, n);
        }
    }
    puts("PASS: first-match search and insertion/merge oracle checks (n=0..64)");
    return 0;
}
