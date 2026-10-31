#include <assert.h>
#include <stdio.h>
#include "lab.c"

int main(void)
{
    /* Smoke test only. Add three original test groups:
       1. Integer min/max heap, duplicates, boundary and mode-switch traces.
       2. Dual heaps, changed keys, and inverse-position maps.
       3. Earliest common closed time, repeated epochs, and exhaustion.
       Keep size within 0..10; remove only when nonempty. Supply 1..5
       ordered, disjoint intervals for every one of the ten IDs. */
    init_heap();
    add(7);
    add(3);
    assert(remove_root() == 3);
    assert(remove_root() == 7 && size == 0);
    for (int id = 0; id < 10; ++id) {
        interval_size[id] = 1;
        toggle_info[id][0] = id;
        toggle_info[id][1] = 12;
    }
    assert(all_on_time() == 9);
    puts("Module 10 student smoke test passed; add three original groups.");
    return 0;
}
