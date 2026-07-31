#ifndef CHAR_STACK_H
#define CHAR_STACK_H

#include <stddef.h>

/*
 * A stack is a last-in, first-out collection. "Last-in, first-out" means
 * that the most recently pushed value is the first value later removed.
 *
 * This stack owns a growable array of characters. A character is one C
 * `char` value. The top character is stored at data[size - 1] when size is
 * positive.
 */
#define CHAR_STACK_MAX_LIMIT 1024U

typedef struct {
    char *data;
    size_t size;
    size_t capacity;
    size_t limit;
} CharStack;

/*
 * A status is a named result returned by an operation.
 */
typedef enum {
    STACK_OK = 0,
    STACK_INVALID_ARGUMENT,
    STACK_LIMIT,
    STACK_UNDERFLOW,
    STACK_ALLOCATION,
    STACK_INVALID_STATE
} StackStatus;

/*
 * Creates an empty stack with the requested maximum number of characters.
 * limit may be zero and may not exceed CHAR_STACK_MAX_LIMIT.
 * A larger requested limit returns STACK_LIMIT.
 *
 * Call only for an uninitialized or previously destroyed CharStack.
 * Failure leaves the object unchanged.
 */
StackStatus char_stack_init(CharStack *stack, size_t limit);

/*
 * Checks the visible representation rules. It cannot prove that a non-NULL
 * pointer is live, that the allocation is large enough, or that ownership is
 * unique.
 */
StackStatus char_stack_validate(const CharStack *stack);

/*
 * Adds one value at the top. Growth begins at capacity four, doubles
 * geometrically, and is clipped to limit. Failure leaves the stack unchanged.
 */
StackStatus char_stack_push(CharStack *stack, char value);

/*
 * Removes the top value and copies it to out_value. An empty stack reports
 * STACK_UNDERFLOW. The output changes only when STACK_OK is returned.
 * Pop does not shrink the allocation. out_value must not point into this
 * stack's character storage.
 */
StackStatus char_stack_pop(CharStack *stack, char *out_value);

/*
 * Copies the top value without removing it. The output changes only when
 * STACK_OK is returned. out_value must not point into this stack's character
 * storage.
 */
StackStatus char_stack_peek(
    const CharStack *stack,
    char *out_value
);

/*
 * Releases owned storage and resets every field to zero/NULL. Passing NULL
 * is a no-op. A non-NULL argument must be an initialized or already destroyed
 * CharStack, not arbitrary uninitialized storage.
 */
void char_stack_destroy(CharStack *stack);

const char *stack_status_name(StackStatus status);

#ifdef CHAR_STACK_TESTING
/*
 * Public-test seam: the next allocation attempt fails. Normal builds do not
 * expose this function.
 */
void char_stack_test_fail_next_allocation(void);
#endif

#endif
