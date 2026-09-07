#include "expression_evaluator.h"

#include "int_stack.h"

#include <limits.h>
#include <stddef.h>

enum {
    EXPRESSION_STACK_CAPACITY = 10
};

static int expression_operator_precedence(char value)
{
    if (value == '*') {
        return 2;
    }
    if (value == '+') {
        return 1;
    }
    return 0;
}

static int expression_calculate(
    char operator_value,
    int left,
    int right,
    int *out_value
)
{
    int result;

    if (left < 0 || right < 0 || out_value == NULL) {
        return 0;
    }

    if (operator_value == '+') {
        if (left > INT_MAX - right) {
            return 0;
        }
        result = left + right;
    } else if (operator_value == '*') {
        if (left != 0 && right > INT_MAX / left) {
            return 0;
        }
        result = left * right;
    } else {
        return 0;
    }

    *out_value = result;
    return 1;
}

static int expression_apply_top(
    int numbers[],
    int *number_size,
    const char operators[],
    int *operator_size
)
{
    int working_size;
    int right;
    int left;
    int result;
    int pushed_size;
    char operator_value;

    if (numbers == NULL || number_size == NULL || operators == NULL ||
        operator_size == NULL || *number_size < 2 || *operator_size < 1) {
        return 0;
    }

    operator_value = operators[*operator_size - 1];
    working_size = int_stack_pop(
        numbers,
        *number_size,
        EXPRESSION_STACK_CAPACITY,
        &right
    );
    if (working_size != *number_size - 1) {
        return 0;
    }

    working_size = int_stack_pop(
        numbers,
        working_size,
        EXPRESSION_STACK_CAPACITY,
        &left
    );
    if (working_size != *number_size - 2 ||
        !expression_calculate(operator_value, left, right, &result)) {
        return 0;
    }

    pushed_size = int_stack_push(
        numbers,
        working_size,
        EXPRESSION_STACK_CAPACITY,
        result
    );
    if (pushed_size != working_size + 1) {
        return 0;
    }

    *number_size = pushed_size;
    *operator_size -= 1;
    return 1;
}

int expression_evaluate(const char expression[], int *out_result)
{
    int numbers[EXPRESSION_STACK_CAPACITY];
    char operators[EXPRESSION_STACK_CAPACITY];
    int number_size = 0;
    int operator_size = 0;
    int expecting_number = 1;
    size_t index = 0U;
    int result;

    if (expression == NULL || out_result == NULL) {
        return 0;
    }

    while (expression[index] != '\0') {
        char current = expression[index];

        if (expecting_number) {
            int next_size;

            if (current < '0' || current > '9') {
                return 0;
            }

            next_size = int_stack_push(
                numbers,
                number_size,
                EXPRESSION_STACK_CAPACITY,
                current - '0'
            );
            if (next_size != number_size + 1) {
                return 0;
            }
            number_size = next_size;
            expecting_number = 0;
        } else {
            int current_precedence = expression_operator_precedence(current);

            if (current_precedence == 0) {
                return 0;
            }

            while (operator_size > 0 &&
                   expression_operator_precedence(
                       operators[operator_size - 1]
                   ) >= current_precedence) {
                if (!expression_apply_top(
                        numbers,
                        &number_size,
                        operators,
                        &operator_size
                    )) {
                    return 0;
                }
            }

            if (operator_size == EXPRESSION_STACK_CAPACITY) {
                return 0;
            }
            operators[operator_size] = current;
            operator_size += 1;
            expecting_number = 1;
        }

        index += 1U;
    }

    if (index == 0U || expecting_number) {
        return 0;
    }

    while (operator_size > 0) {
        if (!expression_apply_top(
                numbers,
                &number_size,
                operators,
                &operator_size
            )) {
            return 0;
        }
    }

    if (number_size != 1 ||
        !int_stack_peek(
            numbers,
            number_size,
            EXPRESSION_STACK_CAPACITY,
            &result
        )) {
        return 0;
    }

    *out_result = result;
    return 1;
}
