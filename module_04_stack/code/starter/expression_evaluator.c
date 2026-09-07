#include "expression_evaluator.h"

#include "int_stack.h"

#include <stddef.h>

int expression_evaluate(const char expression[], int *out_result)
{
    if (expression == NULL || out_result == NULL) {
        return 0;
    }

    /*
     * TODO(core): Evaluate the expression with a 10-slot integer stack and a
     * 10-slot operator stack. Accept only alternating single digits and the
     * binary operators '+' and '*'. Apply normal precedence and left
     * associativity, check every push and arithmetic operation, and assign
     * *out_result only after the complete expression succeeds.
     */
    return 0;
}
