#ifndef INT_STACK_H
#define INT_STACK_H

/*
 * These operations treat stack[0] through stack[size - 1] as the active
 * values of a fixed-capacity integer stack. The top is stack[size - 1].
 * Metadata is valid exactly when 0 <= size <= capacity.
 */

/*
 * Pushes value when the metadata is valid, space remains, and stack is not
 * NULL. Returns size + 1 on success. Every rejection returns the original
 * size and leaves the supplied array unchanged.
 */
int int_stack_push(int stack[], int size, int capacity, int value);

/*
 * Copies the top value without removing it. Returns 1 on success and 0 for
 * invalid metadata, an empty stack, or a NULL required pointer. On failure,
 * out_value is unchanged. out_value must point to storage separate from the
 * stack array.
 */
int int_stack_peek(
    const int stack[],
    int size,
    int capacity,
    int *out_value
);

/*
 * Copies the top value and logically removes it. Returns size - 1 on success.
 * Every rejection returns the original size and leaves out_value unchanged.
 * The array itself is never modified by this operation. out_value must point
 * to storage separate from the stack array.
 */
int int_stack_pop(
    const int stack[],
    int size,
    int capacity,
    int *out_value
);

#endif
