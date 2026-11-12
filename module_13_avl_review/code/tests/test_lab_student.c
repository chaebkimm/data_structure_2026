#include <assert.h>
#include <stdio.h>
#include "lab.c"

int main(void) {
    int values[] = {31, 23, 17, 8, 17, 42};
    int scratch[6];
    assert(linear_search(values, 6, 17) == 2);
    merge_sort(values, scratch, 6);
    assert(binary_search_first(values, 6, 17) == 1);
    assert(binary_search_first(values, 6, 99) == -1);
    /* Add the three original groups described in student/lab.md. */
    puts("PASS: student smoke checks; add original search, sorting, and boundary groups");
    return 0;
}
