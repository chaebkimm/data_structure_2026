# Stage A — Initial Inquiry: Linear Accessible Format

This version has the same targets as the standard inquiry without tables or
drawing requirements. Use a screen reader, keyboard, speech input, or plain
text. Preserve each first answer and add labeled corrections later. Use only
this file during the initial inquiry.

Name:

Date:

A hierarchy arranges items in levels. An immediate relationship connects two
items with no item between them. Consider `1 + 2 * 3`. Multiplication happens
before addition. Each operation has a left operand and a right operand.

## A. Reconstruct the hierarchy

The symbols and numbers are stored characters. Sides record operand
positions, not a rule for sorting values.

- `'+'` is the starting item.
- `'1'` is the left item below `'+'`.
- `'*'` is the right item below `'+'`.
- `'2'` is the left item below `'*'`.
- `'3'` is the right item below `'*'`.

1. Describe every connection, including its side.
2. Which item gives access to the whole expression?
3. Which items have nothing below them?
4. Write the route from `'+'` to `'3'`.
5. Explain why the multiplication is below the addition.

Responses:

## B. Find rules that preserve the hierarchy

Consider each change separately, starting from the original arrangement.

1. The same item storing `'2'` is also placed below `'1'` on its empty left
   side. What changes when two different items lead to that one object?
2. The item storing `'3'` has its empty left side connected back to `'+'`.
   What happens if the program keeps following that route downward?
3. The left branch below `'+'` is removed. Should the `'*'` branch move from
   the right position to the left? Is the remaining shape a valid hierarchy
   with at most two children? Is it still a completed expression?
4. Write two rules that the original arrangement follows.

Responses:

## C. Calculate from the relationships

1. What result does the `'*'` operation produce? What result does `'+'`
   produce after receiving that result?
2. Which item finishes last, and why?
3. If someone groups the expression as `(1 + 2) * 3`, what answer results?
   Describe how that hierarchy differs. Parentheses here explain grouping;
   they are not part of the expression to be read by the program.

Responses:

## D. Storage brainstorm

An object is one stored thing that groups related information. Computer
memory is the working storage used by a running program. Do not write C code
or choose a representation yet.

1. What must each object remember to reach its left and right items?
2. How could the program show that one position has no item?
3. Must related objects occupy neighboring positions in memory? Explain.
4. If two different items both store `'2'`, are they the same object?
5. What question does your model not yet answer?

Responses:
