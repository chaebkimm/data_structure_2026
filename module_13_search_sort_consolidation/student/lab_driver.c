#include <assert.h>
#include <stdio.h>
#include "lab.c"

int main(void) {
    int values[] = {31, 23, 17, 8, 17, 42};
    int insertion[] = {31, 23, 17, 8, 17, 42};
    int scratch[6];
    assert(linear_search(values, 6, 17) == 2);
    printf("Original first index of 17: %d\n", linear_search(values, 6, 17));
    insertion_sort(insertion, 6);
    merge_sort(values, scratch, 6);
    const int expected[] = {8, 17, 17, 23, 31, 42};
    printf("Sorted:");
    for (int i = 0; i < 6; ++i) {
        assert(values[i] == expected[i] && insertion[i] == expected[i]);
        printf(" %d", values[i]);
    }
    printf("\nSorted first index of 17: %d\n", binary_search_first(values, 6, 17));
    assert(binary_search_first(values, 6, 17) == 1);
    assert(binary_search_first(values, 6, 99) == -1);
    puts("PASS: canonical searches and both sorts");
    return 0;
}
