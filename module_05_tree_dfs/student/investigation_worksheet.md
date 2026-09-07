# Stage C — Investigation Worksheet

## Quick reference

The expression tree is `(3+5)*2`. The pool holds 100 nodes. Digits are leaves;
`+` and `*` are operators with two children.

## A. Trace the orders

1. Preorder sequence: ____________________________________________
2. Inorder sequence before parentheses: __________________________
3. Required printed expression: _________________________________
4. Postorder sequence: __________________________________________
5. Evaluation values as they return: _____________________________

## B. Explain saved work

While the call for `3` is active, what does each older call still need to do?

________________________________________________________________

Why does a `NULL` subtree return immediately?

________________________________________________________________

## C. Apply the contracts

What does `NodePool.used` mean? __________________________________

Why must a failed copy restore it? _______________________________

Why must `*out_copy` and `*out_value` change only on success?

________________________________________________________________

## D. Parentheses

Explain why `3+5*2` does not represent the supplied tree.

________________________________________________________________

Create a different valid tree whose output needs parentheses on the right.

________________________________________________________________

## E. Test design

Describe one test for copy independence, one for a small output buffer, and
one for an invalid expression shape.

________________________________________________________________

## F. Efficiency

Explain why time is `O(n)` and call space is `O(h)`.

________________________________________________________________
