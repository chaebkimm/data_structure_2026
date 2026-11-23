#include <assert.h>
#include <stdio.h>

#define main heap_example_main
#include "lab.c"
#undef main

int main(void)
{
    init_pqueue();
    enqueue(7);
    enqueue(3);
    int first = dequeue();
    assert(first == 3);
    assert(size == 1 && pq[0] == 7);

    enqueue(5);
    int sorted[CAPACITY];
    heap_sort(sorted);
    assert(sorted[0] == 5 && sorted[1] == 7);
    assert(size == 0);

    /* Add the three original cases from the handout here. */
    puts("Module 11 student smoke test passed.");
    return 0;
}
