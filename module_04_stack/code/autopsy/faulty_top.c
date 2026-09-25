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

/* Intentional defect: this representation reads stack[top], not top - 1. */
static char faulty_top(const char stack[], int top)
{
    return stack[top - 1];
}

int main(void)
{
    char stack[TRAINING_CAPACITY] = {
        '?', '?', '?', '?', '?', '?', '?', '?', '*', '+'
    };
    int top = 8;

    (void)printf("top: %d\n", top);
    (void)printf("capacity: %d\n", TRAINING_CAPACITY);
    (void)printf("correct top stack[top]: %c\n", stack[top]);
    (void)printf("faulty top stack[top - 1]: %c\n", faulty_top(stack, top));
    (void)printf(
        "faulty read selected the next inactive slot: %s\n",
        faulty_top(stack, top) == '?' ? "yes" : "no"
    );
    return 0;
}
