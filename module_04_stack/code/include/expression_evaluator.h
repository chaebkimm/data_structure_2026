#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

/*
 * Evaluates a nonempty, null-terminated expression with this grammar:
 *
 *     expression := digit (('+' | '*') digit)*
 *     digit      := '0' | '1' | ... | '9'
 *
 * Multiplication has higher precedence than addition, and operators with the
 * same precedence associate from left to right. The evaluator uses fixed
 * internal stacks with 10 slots each. It imposes no separate token-count
 * limit; a capacity failure occurs only when an internal push has no slot.
 *
 * Returns 1 and writes the result on success. Returns 0 for a NULL pointer,
 * malformed input, stack failure, or any intermediate or final int overflow.
 * Every failure leaves out_result unchanged.
 */
int expression_evaluate(const char expression[], int *out_result);

#endif
