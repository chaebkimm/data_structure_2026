# Module 2 — Evidence Record

Name:

Date:

Use numbered prose instead of tables if preferred. Preserve predictions,
record observed results separately, and explain each correction.

## 1. Representation and input contract

For `1+2*3`, give the root index, `size`, `pos`, and all five nodes' data and
child indices. Draw the hierarchy or describe every left/right connection.

Explain:

- the difference between a node index, a stored digit character, and a
  returned integer answer;
- why 0 can identify a node while -1 means no child;
- the roles of `size`, `pos`, and the final `\0`;
- the single-root, single-parent, and no-cycle rules;
- the input grammar, length limit, and integer-result assumption.

Response:

## 2. Coding plan

Give a short plan for each function. Identify the state it reads, the state
it changes, and its return value.

1. `new_node(char data)`:
2. `term(void)`:
3. `terms(void)`:
4. `eval_tree(int node)`:

Explain why a new operator becomes the parent of the old root, why an entire
term must become an operand of `'+'`, and why evaluation must not overwrite
operator characters.

Response:

## 3. Construction trace

Trace `terms()` on `1+2*3` from fresh state. Include the returned root from
each `term()` call, the new operator index, child links, `size`, `pos`, and
the next unread character.

Then show `2*3*4` or `1+2+3`. Explain how its links prove left association,
even when an answer-only test cannot distinguish association.

Response:

## 4. Evaluation trace and operation costs

For `1+2*3`, record each call's node index, its children's returned values
when applicable, and its own return value. State the final contents of the
operator nodes and the shared parser state.

Count or justify the work and storage for:

- reserving and initializing one node;
- assigning one child link;
- building an expression of `n` characters/nodes;
- evaluating a tree of `n` nodes and height `h`;
- the fixed 20-node array compared with its occupied slots;
- the parser's two function levels compared with recursive evaluation depth.

Response:

## 5. Test evidence

Use valid expressions and initialized trees. Do not turn invalid inputs,
cycles, shared children, or invalid indices into ordinary runtime tests.

| Claim | Expected result | Actual result | Pass? |
|---|---|---|---|
| Node creation returns the reserved index and sets both links to -1 | | | |
| A digit-only expression can have root index 0 | | | |
| term stops before the next '+' | | | |
| terms consumes the full valid input and preserves multiplication precedence | | | |
| Repeated operators produce the required left-associated links | | | |
| Digit '0' evaluates as zero and remains an ordinary node | | | |
| Mixed terms evaluate to the expected answer | | | |
| Repeated evaluation preserves every node member and shared variable | | | |
| Independent builds reset size and pos and use their own current roots | | | |

### Three student-authored tests

For each test, record its valid expression or creation sequence, the new
claim beyond supplied tests, expected observations, and the result. Explain
how each independent build starts from fresh shared state.

1. Node creation:
2. Construction, precedence, or association:
3. Evaluation and nonmutation:

## 6. Precedence autopsy

- prediction before running:
- first decision that groups addition before multiplication:
- observed root character and answer, with source-traced indices, links, and grouping:
- why the general tree invariants still hold:
- why the evaluator is correct for the tree it receives:
- repair using term boundaries:
- regression-test idea and expected correct answer:

## 7. Tool evidence

Warning-enabled build command and supplied core-test result:

```text
paste output here
```

Student-test command and result:

```text
paste output here
```

Sanitizer, debugger, or approved instructor-CI evidence:

```text
paste output here
```

A clean diagnostic run alone cannot prove precedence is correct. Identify
the assertion or trace that establishes the expression's meaning.

## 8. Correction and transfer

My initial misconception:

The evidence that changed or confirmed my reasoning:

How the Chapter 1 distinction between occupied and unused array slots applies:

One rule that must change if a later relationship model allows shared items:
