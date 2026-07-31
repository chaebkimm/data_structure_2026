/*
 * INTENTIONALLY FAULTY, SOLUTION-INDEPENDENT TRAINING PROGRAM.
 *
 * This file does not include or link the student's CharStack. It keeps one
 * extra physical array cell so the demonstrated wrong logical index remains
 * inside allocated memory and produces a deterministic result.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum {
    TRAINING_LIMIT = 4,
    TRAINING_STORAGE = 5
};

typedef struct {
    char data[TRAINING_STORAGE];
    size_t size;
} TrainingStack;

typedef enum {
    TRAINING_VALID = 0,
    TRAINING_MISMATCH,
    TRAINING_UNCLOSED
} TrainingResult;

static void training_init(TrainingStack *stack)
{
    size_t index;

    for (index = 0U; index < (size_t)TRAINING_STORAGE; ++index) {
        stack->data[index] = '?';
    }
    stack->size = 0U;
}

static bool training_push(TrainingStack *stack, char value)
{
    if (stack->size == (size_t)TRAINING_LIMIT) {
        return false;
    }

    stack->data[stack->size] = value;
    stack->size += 1U;
    return true;
}

/*
 * Intentional defect: the top is data[size - 1], not data[size].
 * The demo's extra physical cell keeps this read inside the array, but the
 * read still selects a position outside the logical stack.
 */
static char faulty_peek(const TrainingStack *stack)
{
    return stack->data[stack->size];
}

static bool delimiters_match(char opening, char closing)
{
    return (opening == '(' && closing == ')') ||
        (opening == '[' && closing == ']') ||
        (opening == '{' && closing == '}');
}

static TrainingResult faulty_validate(
    const char *text,
    size_t *out_index
)
{
    TrainingStack stack;
    size_t index = 0U;

    training_init(&stack);
    while (text[index] != '\0') {
        char current = text[index];

        if (current == '(' || current == '[' || current == '{') {
            if (!training_push(&stack, current)) {
                *out_index = index;
                return TRAINING_UNCLOSED;
            }
        } else if (current == ')' || current == ']' || current == '}') {
            char opening;

            if (stack.size == 0U) {
                *out_index = index;
                return TRAINING_MISMATCH;
            }

            opening = faulty_peek(&stack);
            if (!delimiters_match(opening, current)) {
                *out_index = index;
                return TRAINING_MISMATCH;
            }
            stack.size -= 1U;
        }

        index += 1U;
    }

    *out_index = index;
    return stack.size == 0U ? TRAINING_VALID : TRAINING_UNCLOSED;
}

int main(void)
{
    TrainingStack demonstration;
    TrainingResult result;
    size_t error_index = 999U;

    training_init(&demonstration);
    (void)training_push(&demonstration, '(');
    (void)training_push(&demonstration, '[');

    (void)printf("size: %zu\n", demonstration.size);
    (void)printf(
        "correct top data[size - 1]: %c\n",
        demonstration.data[demonstration.size - 1U]
    );
    (void)printf(
        "faulty top data[size]: %c\n",
        faulty_peek(&demonstration)
    );

    result = faulty_validate("([])", &error_index);
    (void)printf(
        "faulty validator says valid: %s\n",
        result == TRAINING_VALID ? "yes" : "no"
    );
    (void)printf("reported index: %zu\n", error_index);
    return 0;
}
