/*
 * INTENTIONALLY FAULTY, SOLUTION-INDEPENDENT TRAINING PROGRAM.
 *
 * The wrong logical index remains inside this four-element array, making the
 * observation deterministic and memory-safe.
 */

#include <stdio.h>

enum {
    TRAINING_CAPACITY = 4
};

/* Intentional defect: the top is stack[size - 1], not stack[size]. */
static int faulty_top(const int stack[], int size)
{
    return stack[size];
}

int main(void)
{
    int stack[TRAINING_CAPACITY] = { 10, 20, 777, 888 };
    int size = 2;

    (void)printf("size: %d\n", size);
    (void)printf("capacity: %d\n", TRAINING_CAPACITY);
    (void)printf("correct top stack[size - 1]: %d\n", stack[size - 1]);
    (void)printf("faulty top stack[size]: %d\n", faulty_top(stack, size));
    (void)printf(
        "faulty read selected the next inactive slot: %s\n",
        faulty_top(stack, size) == 777 ? "yes" : "no"
    );
    return 0;
}
