# Instructor Technical Notes — Module 2

## Scope and exact public contract

The header is `code/include/binary_tree.h`. The implementations are
`code/starter/binary_tree.c` and `code/solution/binary_tree.c`.

```c
struct TreeNode {
    char data;
    int left;
    int right;
};

extern struct TreeNode nodes[20];
extern int size;
extern char eq[20];
extern int pos;

int new_node(char data);
int term(void);
int terms(void);
int eval_tree(int node);
```

All four function bodies are student TODOs. The implementation owns the
global definitions; it starts with `size = 0`, `pos = 0`, and
`eq[20] = "1+2*3"`. The header's `extern` declarations refer to that shared
state rather than defining another copy.

Use the explicit `struct TreeNode` spelling. Root and child links are
integer indices into `nodes`, with `-1` for no child. Index `0` is valid.
No additional reset API, wrapper, status type, or structural validator is
required.

## Relationship to the full C companion

Both textbooks' **Full C Code Explanation** sections explain the same four
functions in 15 corresponding topics. The complete program in topic 13
combines the chapter's six code blocks; its initial expression is still
`1+2*3`, and its output is still `1+2*3 = 7`. The companion is optional
reference material released at Stage D, with the chapter's worked code.

The lab keeps these definitions in separate files: the header declares
the shared interface, the starter or solution defines the objects and
functions, and each test or lecture driver supplies `main`. The lab's
syntax bridge explains the added file-layout and test-harness notation.
Do not ask students to paste the complete standalone program into the
starter or add a second `main` to the test build.

The lecture's `(void)printf(...)` explicitly discards `printf`'s return
value; the textbook simply ignores that return value. Both calls
produce the same output. The cast is not a new expression-tree operation.
Reference code, starter contracts, and assessment scope remain the same.

## Input and tree preconditions

Each complete input is:

1. nonempty, starting and ending with a digit;
2. alternating single-digit operands and `+` or `*` operators;
3. free of whitespace and parentheses;
4. at most 19 characters, followed by the terminating `\0` in `eq[20]`; and
5. guaranteed to have every intermediate and final result fit in `int`.

The parser does not check these conditions. Input such as an empty string,
`12+3`, `1 + 2`, `1++2`, or a product exceeding the range of `int` is outside
the assignment contract. Do not turn these examples into required
rejection tests.

`new_node` requires `0 <= size < 20` before reservation. One complete
expression consumes one node per input character, so the valid input bound
uses at most 19 slots after a fresh reset. Direct creation tests must also
stay within capacity.

For `eval_tree(node)`, the starting index must identify an initialized,
completed expression subtree. Every child link used by an operator must
be in `[0, size)`. Digits are leaves; each operator has two operands. The
reachable structure is finite, acyclic, and unshared, with one root and
exactly one incoming child link per other reachable node. Do not call
`eval_tree(-1)` as an empty-tree case.

The struct can represent general binary-tree shapes, including a node with
only one child. Such a shape is not a completed operator expression for
this evaluator. The four functions assume their contracts; they do not
certify arbitrary member assignments.

## Array state and independent runs

`size` is both the used-node count and the next unused slot. Array elements
outside `[0, size)` are not active nodes, even if C initialized their
storage to zero. A newly reserved node explicitly receives two `-1` members.

An independent valid fixture may be set up directly in a test:

```c
#include <string.h> /* Declares strcpy for this bounded literal. */

/* Inside the test function, before parsing this new expression. */
size = 0;
pos = 0;
strcpy(eq, "2*3+4*5"); /* The literal and its terminator fit in eq[20]. */
int root = terms();
```

The array has program-long storage duration. Local root variables merely
hold indices; returning an index does not return an address of a temporary
node. Resetting `size` makes slots available for reuse without requiring
every byte to be erased. Once reused, those slots describe the new tree,
so a saved old root must not be used as if the previous tree were retained.
Reset both `size` and `pos` for each independent full parse.

## Reserving and initializing a node

`new_node(data)` writes the character into `nodes[size]`, sets both links
to `-1`, increments `size`, and returns the old index. The textbook's
`return size++;` returns the position just reserved, not the next slot.

Reservation alone does not attach a parent or decide the whole-expression
root. The first creation returns `0`; it must not be rejected as an empty
or false result. Character data uses `'0'` through `'9'`, not integer data
`0` through `9`.

## Building a term

`term()` consumes a digit to establish its initial root. For each following
`*` it reserves an operator, reserves the next digit, gives the operator
the old root on its left and the fresh digit on its right, and makes the
operator the new root.

`eq[pos++]` reads at the old position and then advances `pos`. A condition
such as `eq[pos] == '*'` examines the next character without consuming it.
At return, `term()` leaves a `+` or `\0` unread for its caller. It does not
reset the shared state on entry.

For `2*3*4`, the first `*` subtree becomes the second `*` node's left
child. The tree therefore encodes `(2*3)*4`. Avoid tests that infer this
shape only from the answer: multiplication returns the same result for
both associations when all intermediates fit.

## Building a sum of terms

`terms()` first calls `term()`. For each following `+`, it reserves a plus
node, calls `term()` for the complete next term, links the previous root
on the left and that term's root on the right, and updates the current
root to the plus index.

The multiplication loop is inside each `term()` call. This construction
gives multiplication higher precedence. Repeated additions associate to
the left through the same old-root/new-parent pattern. On a complete
valid input, `terms()` returns with `eq[pos] == '\0'`.

### Canonical trace

For `1+2*3`, reservation order is index `0` for `'1'`, `1` for `'+'`, `2`
for `'2'`, `3` for `'*'`, and `4` for `'3'`. The first `term()` stops with
`pos == 1`. `terms()` consumes `+`, then the second `term()` consumes
`2*3` and returns root `3` with `pos == 5`. The outer call returns root
`1`, with children `0` and `3`; node `3` has children `2` and `4`.

Root index, allocation order, and evaluation result are different facts.
The root need not be the first or last allocated slot.

## Recursive evaluation

At a digit, `eval_tree` returns `nodes[node].data - '0'`. C guarantees
consecutive digit character codes; this conversion needs no ASCII-specific
integer constant. The digit case returns before following its `-1` links.

At an operator, the textbook evaluates the left child and then the right
child in separate declarations. Each recursive call keeps its own local
results. Applying `+` or `*` returns a numeric answer without modifying
the node's character or either child link. Evaluation also leaves
`eq`, `pos`, and `size` unchanged.

For the canonical tree, calls begin at indices `1, 0, 3, 2, 4`; the
completed subtree results are `1`, `2`, `3`, `6`, and `7`. The `*` node
still stores `'*'` after returning `6`, and the root still stores `'+'`
after returning `7`. Distinguish the order of call entry from the order
of completed results.

The textbook's `-1` fallback for an unsupported data character is not
input or tree validation: bad indices, missing children, or cycles are
not made safe by that check. No handling of those cases is required.

## Complexity and limits

Let `n` be the number of characters/nodes in the whole valid expression,
`k` the number of characters in one term, and `h` the longest downward
path measured in child links.

| Operation | Time | Additional working space |
|---|---:|---:|
| reserve and initialize one node | `O(1)` | `O(1)` |
| attach one known child index | `O(1)` | `O(1)` |
| `term()` | `O(k)` | `O(1)` beyond reserved nodes |
| `terms()` for the complete expression | `O(n)` | `O(1)` beyond reserved nodes |
| evaluate the complete tree | `O(n)` | `O(h + 1)` recursive call stack |

Construction uses loops; the `terms()` to `term()` calls do not add one
stack frame per expression node. Evaluation is recursive and can encounter
a skewed tree from repeated operators. Each node contains one character
and two integer members; padding means `sizeof(struct TreeNode)` need not
equal the simple sum of member sizes. The program reserves a fixed
20-element array; conceptually its used node storage grows with `n`.
State these costs in terms of expression size even though the classroom
program has a fixed small capacity.

## Safe precedence autopsy

`code/autopsy/faulty_precedence.c` is standalone. Its defective builder
treats every following operator as a new parent of the accumulated
expression and the next digit. For `1+2*3`, it constructs the grouping
`(1+2)*3` and obtains `9`.

All node indices and operands are valid, and the tree has no sharing or
cycles. The defect is expression grouping. A correct evaluator faithfully
evaluates the wrong structure. Repair the construction policy by building
complete multiplication terms before combining them with plus nodes.

The instructor answer key holds the worked index table, prediction, and
repair. Students record a prediction before running. Strong warnings and
memory checks can remain silent because this semantic defect need not
perform an invalid memory or arithmetic operation.

## Toolchain and release validation

Preferred GCC/Clang flags:

```text
-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
```

Supported runtime checks:

```text
-fsanitize=address,undefined -fno-omit-frame-pointer
```

Microsoft C uses `/nologo /std:c11 /W4 /Zi`. Provide instructor CI or a
debugger/state-inspection alternative when local runtime checks are
unavailable.

Before release, verify:

- all four reference functions and supplied tests compile without warnings;
- creation covers index zero, new-slot identity, and initialized children;
- valid parsing covers single digits, repeated operators, mixed precedence,
  left-associated links, and the 19-character boundary;
- independent runs reset both counters and use bounded valid inputs;
- evaluation returns the right value and preserves members and shared state;
- the standalone autopsy produces a deterministic semantic discrepancy;
- the starter compiles with exactly four implementation TODOs;
- all release paths use the current header, implementation, and autopsy names;
- the three authored-test categories align with the 100-point rubric;
- vocabulary appears only from Stage B onward;
- Stage D includes both complete textbooks with their optional C companions
  and no worked autopsy prediction; and
- Stage E excludes the solution, instructor extension tests, and answer key.
