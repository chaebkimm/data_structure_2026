#include "delimiter_validator.h"

#include "char_stack.h"

#include <stdbool.h>
#include <stdint.h>

static bool delimiter_is_opening(char value)
{
    return value == '(' || value == '[' || value == '{';
}

static bool delimiter_is_closing(char value)
{
    return value == ')' || value == ']' || value == '}';
}

static bool delimiters_match(char opening, char closing)
{
    return (opening == '(' && closing == ')') ||
        (opening == '[' && closing == ']') ||
        (opening == '{' && closing == '}');
}

DelimiterStatus delimiter_validate(
    const char *text,
    size_t depth_limit,
    size_t *out_error_index
)
{
    CharStack stack;
    DelimiterStatus result = DELIMITER_OK;
    size_t result_index = SIZE_MAX;
    size_t index = 0U;

    if (text == NULL || out_error_index == NULL ||
        depth_limit > (size_t)CHAR_STACK_MAX_LIMIT) {
        return DELIMITER_INVALID_ARGUMENT;
    }

    if (char_stack_init(&stack, depth_limit) != STACK_OK) {
        return DELIMITER_INVALID_ARGUMENT;
    }

    while (text[index] != '\0') {
        char current = text[index];

        if (delimiter_is_opening(current)) {
            StackStatus stack_status;

            stack_status = char_stack_push(&stack, current);
            if (stack_status == STACK_LIMIT) {
                result = DELIMITER_DEPTH_LIMIT;
                result_index = index;
                break;
            }
            if (stack_status == STACK_ALLOCATION) {
                result = DELIMITER_ALLOCATION;
                break;
            }
            if (stack_status != STACK_OK) {
                result = DELIMITER_INVALID_ARGUMENT;
                break;
            }
        } else if (delimiter_is_closing(current)) {
            char opening = '\0';
            StackStatus stack_status;

            stack_status = char_stack_peek(&stack, &opening);
            if (stack_status == STACK_UNDERFLOW) {
                result = DELIMITER_UNMATCHED_CLOSE;
                result_index = index;
                break;
            }
            if (stack_status != STACK_OK) {
                result = DELIMITER_INVALID_ARGUMENT;
                break;
            }

            if (!delimiters_match(opening, current)) {
                result = DELIMITER_MISMATCH;
                result_index = index;
                break;
            }

            stack_status = char_stack_pop(&stack, &opening);
            if (stack_status != STACK_OK) {
                result = DELIMITER_INVALID_ARGUMENT;
                break;
            }
        }

        index += 1U;
    }

    if (result == DELIMITER_OK) {
        char opening = '\0';
        StackStatus stack_status = char_stack_peek(&stack, &opening);

        if (stack_status == STACK_OK) {
            result = DELIMITER_UNCLOSED_OPEN;
            result_index = index;
        } else if (stack_status != STACK_UNDERFLOW) {
            result = DELIMITER_INVALID_ARGUMENT;
        }
    }

    char_stack_destroy(&stack);

    if (result != DELIMITER_ALLOCATION &&
        result != DELIMITER_INVALID_ARGUMENT) {
        *out_error_index = result_index;
    }

    return result;
}

const char *delimiter_status_name(DelimiterStatus status)
{
    switch (status) {
        case DELIMITER_OK:
            return "ok";
        case DELIMITER_INVALID_ARGUMENT:
            return "invalid argument";
        case DELIMITER_UNMATCHED_CLOSE:
            return "closing delimiter has no opening delimiter";
        case DELIMITER_MISMATCH:
            return "closing delimiter does not match the latest opening";
        case DELIMITER_UNCLOSED_OPEN:
            return "one or more opening delimiters remain unclosed";
        case DELIMITER_DEPTH_LIMIT:
            return "delimiter nesting exceeds the configured depth limit";
        case DELIMITER_ALLOCATION:
            return "allocation failed";
        default:
            return "unknown DelimiterStatus";
    }
}
