/*
 * INTENTIONALLY BROKEN LOGICAL-BOUNDARY TRAINING PROGRAM.
 *
 * The array has eleven physical slots but only ten usable list slots. The
 * extra slot is an observation guard, not a production fix. Writing the
 * guard is inside this array, so the demonstration has no out-of-bounds
 * memory access even though the list invariant becomes false.
 */

#include <stdio.h>

static int broken_append(int array[], int size, int capacity, int value)
{
    /* The equality case incorrectly accepts an already full list. */
    if (size <= capacity) {
        array[size] = value;
        return size + 1;
    }
    return size;
}

int main(void)
{
    int array[11] = {
        100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, -999
    };
    int size = 10;
    int capacity = 10;

    (void)printf(
        "before: size=%d capacity=%d guard=%d\n",
        size,
        capacity,
        array[10]
    );

    size = broken_append(array, size, capacity, 1100);

    (void)printf(
        "after faulty append: size=%d capacity=%d guard=%d\n",
        size,
        capacity,
        array[10]
    );
    (void)printf(
        "0 <= size <= capacity: %s\n",
        size >= 0 && size <= capacity ? "true" : "false"
    );
    (void)printf("The guard changed; the usable list was already full.\n");
    return 0;
}
