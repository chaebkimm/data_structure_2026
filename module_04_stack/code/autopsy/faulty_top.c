/*
 * INTENTIONALLY FAULTY, SOLUTION-INDEPENDENT TRAINING PROGRAM.
 *
 * The wrong logical index remains inside this ten-element array, making the
 * observation deterministic and memory-safe.
 */

#include <stdio.h>

enum {
    TRAINING_CAPACITY = 10
};

/* Intentional defect: this representation reads stack[size - 1], not size. */
static char faulty_top(const char stack[], int size)
{
    return stack[size];
}

int main(void)
{
    char stack[TRAINING_CAPACITY] = {
        '+', '*', '?', '?', '?', '?', '?', '?', '?', '?'
    };
    int size = 2;

    (void)printf("size: %d\n", size);
    (void)printf("capacity: %d\n", TRAINING_CAPACITY);
    (void)printf("correct top stack[size - 1]: %c\n", stack[size - 1]);
    (void)printf("faulty top stack[size]: %c\n", faulty_top(stack, size));
    (void)printf(
        "faulty read selected the next inactive slot: %s\n",
        faulty_top(stack, size) == '?' ? "yes" : "no"
    );
    return 0;
}
