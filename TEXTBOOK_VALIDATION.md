# Korean Textbook Validation Record

The validation date is August 14, 2026. The targets are the introductory textbook and the student textbooks from Chapters 1 to 16.

## Module 1 Revision Note — August 27, 2026

Chapter 1 and Module 1 now use a fixed integer array with separate size and
capacity. Access/update, linear search, append, insertion, and removal are
core. A full or invalid mutation leaves the array and count unchanged.
Allocation, release, dynamic growth, and their failure-injection tests are
not part of this module. Earlier dynamic-ArrayList observations in
`textbook_pilot/` remain historical records, not validation of this revision.

The reference implementation passes 8 core and 5 extension tests with
warning-as-error checks, AddressSanitizer, and UndefinedBehaviorSanitizer.
The four Chapter 1 C blocks compile and run together with assertions for
the textbook trace. The guarded bounds autopsy also runs without sanitizer
errors while demonstrating the intended broken logical bound. The starter
compiles cleanly and intentionally fails 7 of the 8 core tests.

PowerShell build and packaging files were inspected, not executed, because
PowerShell is unavailable on this host. No student ZIPs were published.
A fresh beginner reading pilot is still required; these technical checks do
not establish an actual human-validation pass.

Chapter 2's current array-indexed expression-tree alignment is recorded below.

## Module 2 Revision Note — September 9, 2026

Module 2 now follows both `student/textbook.md` and
`student/textbook_korean.md`: `char data`, integer child indices, `nodes[20]`,
`size`, `eq[20]`, and `pos`. Students implement `new_node`, `term`, `terms`,
and `eval_tree`. The canonical expression is `1+2*3`, with root index 1 and
result 7; the Stage C transfer is `2*3+4*5`, with root index 3 and result 26.
The parser uses loops for terms and sums; evaluation is recursive and does
not mutate nodes or parser state.

Both editions now state the same valid-input assumptions: nonempty single
digits alternating with `+` or `*`, no spaces or parentheses, at most 19
characters plus the terminator, and every intermediate/final value within
`int`. Korean wording about stored evaluation results and multiplication
grouping was corrected, and translation-editorial sentences were removed.

The reference passes 8 core and 5 extension tests under Clang with
warnings as errors, AddressSanitizer, and UndefinedBehaviorSanitizer. Tests
cover creation, term boundaries, precedence, left grouping, digit conversion,
nonmutation, maximum-length inputs, and repeated builds. The lecture prints
`1+2*3 = 7`. The standalone precedence autopsy produces the intended faulty
9 and correct 7 using finite trees, with no sanitizer diagnostic.

Both textbooks' six C blocks compile as programs under the same strict
checks and print `1+2*3 = 7`. Their executable code matches after comments
and whitespace are removed. The incomplete starter safely fails all 8 core
and 5 extension tests; the 3 student-test placeholders fail intentionally.

Release manifests have 3, 4, 3, 4, and 15 unique existing source-entry pairs
for Stages A through E. Stage D includes both textbook editions. Stage E
includes `test_helpers.h` and the standalone autopsy, and excludes reference
solutions, lecture code, instructor materials, and extension tests. An
isolated temporary Stage E copy compiles with its student Makefile: starter
core and student placeholders fail as expected, the autopsy runs independently,
and substituting the completed implementation makes all 8 core tests pass.

PowerShell scripts were inspected but not executed because PowerShell is
unavailable on this host. No release ZIP archives were created or published.
The older Module 2 notes and `textbook_pilot/` records below remain historical;
these technical checks do not establish a human beginner-reading validation.

## Superseded Module 2 Revision Note — August 29, 2026

Chapter 2 and Module 2 now carry the expression `(3 + 5) * 2` through the
canonical diagram, local-node construction, recursive search trace, branch
clearance, tests, and evidence. Its five live local nodes store `'*'`, `'+'`,
`3`, `5`, and `2`; the character constants are portable integer labels, not
an expression-evaluation interface. The fresh Stage C transfer fixture is
`(8 - 3) * (4 + 2)`.

The underlying contract remains a generic binary tree: `struct TreeNode`
contains `data`, `left`, and `right`, and only `tree_find` and `tree_clear`
are public library functions. Initialization, guarded attachment, and
explicit detachment are direct field operations. A generic node may have
zero, one, or two children; a completed binary expression additionally
requires two operands per operator and none below a numeric operand. The
library does not evaluate or validate that semantic expression rule.

The reference implementation passes 8 core and 5 extension tests with
warning-as-error checks, AddressSanitizer, and UndefinedBehaviorSanitizer.
The six Chapter 2 C blocks compile in a composed strict-C11 check covering
the canonical construction, search, selected-branch clearance, opposite-side
preservation, and still-live cleared objects. The standalone shared-operand
autopsy also runs without sanitizer errors: clearing one branch changes the
fields observed through another invalid shared link, but no object's lifetime
ends. The starter compiles cleanly and intentionally fails 7 of 8 core tests.

Student activities, instructor guides, diagrams, release source paths,
question banks, and course references use the same expression fixture and
generic-tree boundary. The five-stage release keeps vocabulary in Stage B
and worked autopsy results out of student prediction materials. PowerShell
build and packaging files were inspected, not executed, because PowerShell
is unavailable on this host. No student ZIPs were published.

Earlier Chapter 2 records in `textbook_pilot/` and the superseded note
below are historical, not validation of this revision. A fresh beginner
reading pilot is still required; technical checks do not establish an
actual human-validation pass.

## Superseded Module 2 Revision Note — August 26, 2026

Chapter 2 was redesigned after the original validation date. That version
taught a dynamically allocated, five-child general tree with parent links,
recursive preorder search, checked shared-root comparison, and cascading
deletion. It was replaced by the August 27 local binary-tree revision above.
The former Chapter 2 binary-tree, fixed-arena, and BST observations in
`textbook_pilot/` remain historical records.

At that time, the extracted C blocks compiled with warning-as-error checks
and ran successfully. Its reference suite passed 9 core and 7 extension
tests, including AddressSanitizer and UndefinedBehaviorSanitizer runs.
Those results do not validate the current code or chapter.

## Module 3 Revision Note — August 28, 2026

Chapter 3 and Module 3 now use a fixed directed, unweighted integer
adjacency matrix. The representation is an explicit `struct DirectedGraph`
with `vertex_count` and a 16 by 16 `grid`. Only `graph_init`,
`graph_add_edge`, `graph_remove_edge`, and `graph_out_degree` are public
library functions. Guarded matrix lookup remains direct caller code.
Undirected mutation, Boolean storage, graph-kind and status enums,
whole-graph validation, neighbor containers, graph search, and dynamic
adjacency lists are not part of this implementation.

The reference implementation passes 8 core and 5 extension tests with
warning-as-error checks, AddressSanitizer, and UndefinedBehaviorSanitizer.
The five Chapter 3 C blocks compile and run together with assertions for
full-grid initialization, the Web/App/Database matrix, directed removal,
and the final out-degree. The standalone ghost-connection autopsy also runs
without sanitizer errors while demonstrating the logical inactive-cell
defect. The starter compiles cleanly and intentionally fails 7 of the 8
core tests.

Student activities, instructor guides, diagrams, release paths, the Week 3
question bank, and later DFS prerequisites now use the same boundary. The
five-stage release keeps vocabulary in Stage B and the exact autopsy outcome
out of Stage D. PowerShell build and packaging files were inspected, not
executed, because PowerShell is unavailable on this host. No student ZIPs
were published.

Earlier Chapter 3 observations in `textbook_pilot/` are historical records,
not validation of this revision. A fresh beginner reading pilot is still
required; technical checks do not establish an actual human-validation pass.

## Module 4 Revision Note — August 29, 2026

Chapter 4 and Module 4 now use a caller-owned fixed integer array with
separate size and capacity. Valid metadata satisfies `0 <= size <= capacity`,
and a nonempty Stack's top is `stack[size - 1]`. The public library contains
checked `int_stack_push`, `int_stack_peek`, and `int_stack_pop` operations.
Rejected operations preserve the complete array and any checked output; pop
decreases the logical size without erasing the newly inactive cell.

The canonical trace pushes function IDs 100, 200, and 300. The transfer
application evaluates the textbook expression `1+2*3` with fixed ten-position
number and operator Stacks. Its grammar permits only alternating single digits
and the operators `+` and `*`, with normal precedence and left associativity.
Input length is not separately capped; every live push is checked. Malformed
input, an internal capacity failure, or a result outside the C `int` range
leaves the caller's result unchanged.

The reference implementation passes 8 core and 5 extension tests with both
Clang and GCC warning-as-error builds. Clang AddressSanitizer and
UndefinedBehaviorSanitizer runs also pass. The composed textbook Stack and
`1+2*3` code runs with strict C11 checks. The isolated, memory-safe top-index
autopsy reports correct top 20 and faulty inactive value 777 without a
sanitizer error. The starter compiles cleanly and intentionally fails 4 of 8
core tests; its three student-test placeholders also fail intentionally.

Student activities, instructor materials, diagrams, course references, active
Chapter 4 pilot questions, and the five-stage release now use the same fixed
Stack boundary. Release stages contain 3, 4, 3, 3, and 16 unique existing
source-entry pairs. Stage A contains no formal Stack vocabulary, Stage D
contains no autopsy answer, and Stage E excludes solutions, instructor files,
and extension tests. The Week 4 bank contains 44 vocabulary placements, 40
required questions, and 4 optional questions with matching consolidated
question text.

PowerShell build and packaging files were inspected, not executed, because
PowerShell is unavailable on this host. No student ZIPs were published. Old
delimiter, growable-Stack, and `CharStack` observations under
`textbook_pilot/simulation/` are superseded historical records, not validation
of this revision. A fresh beginner reading pilot is still required; technical
checks do not establish an actual human-validation pass.

## Beginner Reading Validation

We read through the text by dividing into three reader roles.

* For Chapters 1–5, we assumed the reader only knows C variables, functions, arrays, loops, and conditionals.
* For Chapters 6–10, we assumed the reader has completely understood Chapters 1–5.
* For Chapters 11–16, we assumed the reader has completely understood Chapters 1–10.

We re-read each chapter following the five steps used in Chapter 1: understanding the problem, efficiency, vocabulary, coding plan, and C code. If an idea suddenly appeared without being explained in an earlier step, or if the plan and the code were different, we marked it as a failure. After fixing the failed sentences and examples, we read them again using a different reader role.

## Code and Document Validation

* We made sure that each chapter's public headers, provided tests, and baseline code matched the textbook's rules for limits, states, and keeping the exact state after a failure.
* The `solution-core` tests of the baseline code all passed for the rewritten chapters from 2 to 16. During each cross-review, the required `solution-extension` tests and the compilation of the main C examples also passed.
* We checked the main examples of each chapter and the exact order of visiting, taking out, and selecting items.
* We checked if all chapters from 1 to 16 had the five core sections in the exact same order.
* We checked the pairs of code blocks and the links in the table of contents.
* We checked that no banned old terms or overly formal ending styles were left in the text.
* We checked that explanations used short, plain sentences, and that question sentences and question-style titles asked directly.
* We checked that the subtitles for "Thinking Logically" and "Calculating Efficiency" were short questions or clear answer titles, just like in Chapter 1.
* We checked that we explained the ideas first before giving them formal names, and that the coding plan and C code followed the same order of actions.
* `git diff --check` passed successfully.

## Vocabulary Rules

We use the vocabulary boundary table and the fixed vocabulary list in the [Korean Textbook Style Guide](https://www.google.com/search?q=KOREAN_TEXTBOOK_STYLE_GUIDE.md) as our strict standard. For any future edits, we will not just use new names right away; we will update this table first before applying them.

## Actual Validation Status

This current validation was a mock (practice) beginner reading. We have prepared the [Actual Beginner Pilot Package](https://www.google.com/search?q=textbook_pilot/README.md), but we do not have actual test responses from real students yet.

We will only change the status to an "actual pass" after we record how much time real participants took to explain things in their own words, which exact sentences they got stuck on, and their reasons for giving wrong answers. Until we have those real records, we will not add any more content or widen the scope.
