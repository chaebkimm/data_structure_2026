#ifndef DELIMITER_VALIDATOR_H
#define DELIMITER_VALIDATOR_H

#include <stddef.h>

/*
 * A delimiter is a character that marks a boundary. This validator recognizes
 * the opening delimiters (, [, { and their closing partners ), ], }.
 */
typedef enum {
    DELIMITER_OK = 0,
    DELIMITER_INVALID_ARGUMENT,
    DELIMITER_UNMATCHED_CLOSE,
    DELIMITER_MISMATCH,
    DELIMITER_UNCLOSED_OPEN,
    DELIMITER_DEPTH_LIMIT,
    DELIMITER_ALLOCATION
} DelimiterStatus;

/*
 * Checks delimiter nesting in a null-terminated C string.
 *
 * depth_limit is the greatest permitted number of simultaneously unclosed
 * opening delimiters. It may be zero and may not exceed
 * CHAR_STACK_MAX_LIMIT from char_stack.h.
 *
 * On DELIMITER_OK, out_error_index receives SIZE_MAX. On a delimiter error it
 * receives:
 * - the closing-delimiter index for UNMATCHED_CLOSE or MISMATCH;
 * - the string length for UNCLOSED_OPEN; or
 * - the opening-delimiter index that would exceed DEPTH_LIMIT.
 *
 * Other characters are ignored. Invalid arguments and allocation failure
 * leave *out_error_index unchanged.
 */
DelimiterStatus delimiter_validate(
    const char *text,
    size_t depth_limit,
    size_t *out_error_index
);

const char *delimiter_status_name(DelimiterStatus status);

#endif
