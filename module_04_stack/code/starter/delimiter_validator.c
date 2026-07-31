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
    /*
     * TODO(core): Return true only for (), [], and {} in that order.
     */
    (void)opening;
    (void)closing;
    return false;
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
            /*
             * TODO(core):
             * 1. Push current through the public Stack API.
             * 2. Map STACK_LIMIT to DEPTH_LIMIT at this index.
             * 3. Map STACK_ALLOCATION to DELIMITER_ALLOCATION.
             * 4. Continue only after STACK_OK.
             */
            (void)current;
            result = DELIMITER_INVALID_ARGUMENT;
            break;
        } else if (delimiter_is_closing(current)) {
            /*
             * TODO(core):
             * 1. Peek at the latest opening delimiter.
             * 2. Map empty-stack underflow to UNMATCHED_CLOSE at this index.
             * 3. Report MISMATCH at this index when the pair does not match.
             * 4. Pop only a matching opening delimiter.
             */
            (void)delimiters_match;
            (void)current;
            result = DELIMITER_INVALID_ARGUMENT;
            break;
        }

        index += 1U;
    }

    /*
     * TODO(core): If scanning reached the string end, use char_stack_peek to
     * distinguish an empty stack (UNDERFLOW, so the text is valid) from an
     * unclosed opening delimiter (OK). For UNCLOSED_OPEN, use the string
     * length (index) as result_index. Do not read stack fields directly.
     */

    char_stack_destroy(&stack);

    /*
     * Invalid arguments returned before this point. Allocation failure must
     * also leave the caller's output unchanged.
     */
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
