# Korean Textbook Validation Record

The validation date is August 14, 2026. The targets are the introductory textbook and the student textbooks from Chapters 1 to 16.

## Chapter 4 Bilingual Webpage — September 24, 2026

The existing student textbook site now includes Chapter 4 at `/chapter-4`
in Korean and `/en/chapter-4` in English, with `/ko/chapter-4` as a Korean
alias. Chapter navigation, language switching, metadata, and the previous
chapter pager include the new chapter. The homepage remains Chapter 3.

Both web manuscripts and downloadable editions match their textbook files
exactly. The page preserves the opening paragraph, seven main sections,
36 subsections, twelve tables, and nine C blocks. The new syntax section
and all eleven full-code explanation subsections are included. Downloadable
`lab.c` and `lab_demo.c` match the module sources.

Three bilingual activities demonstrate the character stack, conversion,
and evaluation. They retain inactive cells, distinguish downward `top`
from upward `pos`, expose both precedence pops for incoming `+`, and pop
the right operand before the left. Repeated conversions preserve old
operator and output cells while resetting the output count and terminator.
The evaluator shows uninitialized local cells and the final return with
`pos == 0`; expired operand locals are cleared. Input guards are identified
as webpage behavior, separate from the C source's assumptions.

The sixteen existing webpage tests and six new stack/manuscript tests pass.
The six new tests also pass after review corrections. TypeScript checking,
the production build, and whitespace checks pass. Browser checks cover
Korean/English switching with preserved anchors, full and empty stack
operations, canonical conversion, shorter repeat conversion, zero-divisor
rejection, and integer evaluation. Mobile and desktop layouts have no page
width overflow. Final browser log checks report no errors or warnings.
The development server recorded an early dependency-optimization hook
error followed by a reload, and context warnings during hot replacement;
these are distinguished from the successful final interactive checks.
A separate local check served the built production worker and confirmed
stack insertion, canonical postfix conversion, and integer evaluation
(`7/2 == 3`). Browser error/warning logs were empty, and the production
server recorded no React errors. The existing missing favicon returned
404; the chapter and all requested application assets returned 200.

Sites version 136, source commit `48e5a37f086c55acf901c1db25ae13fe9d7e5bdc`,
published successfully with the existing public audience. The Korean page
is available at `https://data-structures.chaebinkim.chatgpt.site/chapter-4`.
Publication was confirmed by the deployment result. This is technical and
editorial validation, not a new human beginner-reading pilot.

## Chapter 4 Korean Edition — September 24, 2026

`module_04_stack/student/textbook_korean.md` now translates the complete
current English chapter, including New C Syntax Explained and all eleven
Full C Code Explanation subsections. Both editions have seven main
sections, matching levels across all 46 headings, and matching dimensions
across all twelve tables. Korean review checked completeness, terminology,
state changes, caller assumptions, and operand order.

All nine C blocks, shell commands, input grammar, and expected output match
the English edition byte for byte. The six blocks in the Korean C Code
section reproduce the lab and driver after normalizing blank lines and
trailing whitespace. Their concatenation compiles with direct Command Line
Tools Clang, C11, the existing warning flags, AddressSanitizer, and
UndefinedBehaviorSanitizer. It prints the expected infix, postfix, size 7,
and result -1 with no sanitizer findings. The six existing prototype
warnings remain. English manuscript and C sources are unchanged by this
translation.

The module README links both editions. Stage D's manifest, README, and
packaging source list now include the Korean chapter. Static checks find
unique source and destination paths and all sources present. Stage counts
are A: 3, B: 4, C: 3, D: 4, E: 13. The release gates remain unchanged.
PowerShell archive creation was not executed. This is translation and
technical validation, not a new human beginner-reading pilot.

## Chapter 4 C Syntax and Full Explanation — September 24, 2026

The English Chapter 4 textbook now includes `New C Syntax Explained`
between Coding Plan and C Code, followed by `Full C Code Explanation`
after the code. These additions follow the reference format in Chapters
1–3. The five existing core sections remain in order; the two additions
bring the chapter to seven main sections.

The syntax section covers characters and strings, logical conditions,
index updates, switch cases, integer arithmetic, external declarations,
function prototypes, and printing. The full explanation follows every
declaration and function in the six implementation/driver blocks. Worked
traces distinguish downward character `top`, postfix `size`, and local
integer `pos`, including operand order, repeated conversion, and the
documented input assumptions. Review found no actionable discrepancies
with the supplied source.

All prior textbook content and all nine existing C blocks are preserved.
The five implementation blocks still match `student/lab.c` after ignoring
blank lines and trailing whitespace; the sixth C Code block matches
`code/lab_demo.c`. The earlier three storage illustrations are excerpts,
not additional definitions to concatenate into the program.

The six-block extracted program compiles as C11 and exactly matches the
documented output: infix `1-2*3+4`, postfix `123*-4+`, size 7, and result -1.
Independent builds of the existing driver and lab tests pass all six test
groups. Builds use direct Command Line Tools Clang with an explicit SDK,
`-Wall -Wextra -Wpedantic -Wconversion -Wshadow`, AddressSanitizer,
UndefinedBehaviorSanitizer, and `-fno-sanitize-recover=all`. There are no
sanitizer findings. Each build reports the six existing empty-parameter-list
prototype warnings. Chapter section order, balanced fences, and whitespace
checks pass. This is an explanation-only update; the C source is unchanged.

## Module 4 Character-Stack Alignment — September 23, 2026

The current Module 4 teaching model follows
`module_04_stack/student/lab.c`: global `char stack[10]`, empty `top == 10`,
full `top == 0`, active suffix `top..9`, and character count `10 - top`.
Push decrements before writing; peek reads `stack[top]`; pop reads then
increments. Full push is a silent no-op. Empty peek and pop return the null
character while preserving the array and `top`. The canonical character
trace uses A, B, C; abstract function IDs remain only in the initial story.

Expression work now separates conversion from evaluation:
`1-2*3+4 -> 123*-4+ -> -1`. Global `size` is postfix length seven, excluding
the terminator; local `pos` counts integers in `values[10]`. The right
operand is popped into `num2` before the left into `num1`. Conversion resets
`size` and writes a fresh terminator for repeated and shorter inputs.

The teaching boundary assumes nonempty text of at most seven characters,
single digits alternating with `+ - * / %`, no spaces, parentheses, unary
operators, or multi-digit operands, nonzero divisors, and representable
integer intermediates. The source lacks general grammar, output-bound, and
arithmetic validation. Those checks are described as extensions, not as
existing safe-rejection behavior. The older checked caller-owned integer API
remains optional legacy material.

Instructor guidance, the Stage D diagram models, Week 4 question references,
and active curriculum/calendar descriptions use this model. The five release
gates, exactly three Cognitive Pause targets, standard/linear alternatives,
and preserve-before-calibrate sequence remain. The Week 4 page has 44
vocabulary placements, 40 core prompts, and four optional prompts; its
consolidated question section matches. The diagram release omits the autopsy
fixture and its answer. The current isolated autopsy instead uses a
character active suffix to distinguish physical bounds from logical top.

Fresh verification compiled the current source through `make lab-demo`,
`make lab-tests`, and the isolated autopsy with the direct Command Line Tools
Clang compiler, C11, `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`,
AddressSanitizer, UndefinedBehaviorSanitizer, and
`-fno-sanitize-recover=all`. The demo printed infix `1-2*3+4`, postfix
`123*-4+`, size 7, and result -1. All six current lab test groups passed;
the autopsy reported correct `'*'` and faulty `'?'` without sanitizer
findings. The six existing empty-parameter-list prototype warnings remain;
`student/lab.c` was not edited during alignment.

The textbook retains the five-section course flow. Its five implementation
blocks match `lab.c` after ignoring blank lines and trailing whitespace;
the sixth C block matches the separate demonstration driver. Concatenating
these six blocks also compiled and produced the documented output under
AddressSanitizer and UndefinedBehaviorSanitizer. Chapter 4's vocabulary row
in the style guide now matches the same character/postfix model.

An exact temporary Stage E extraction also built and passed all six lab test
groups. The current release manifest has 3, 4, 3, 3, and 13 files across
Stages A–E. PowerShell was unavailable, so its build/packaging scripts were
inspected rather than executed. These results concern the current lab and
release, not the optional legacy checked evaluator.

This dated entry supersedes the August 29 Module 4 model for active teaching.
The older entry and pilot observations below remain historical records;
their checked-library test counts and rejection guarantees do not validate
this source. This is a technical/editorial alignment, not evidence of a new
human beginner-reading pilot.

## Chapter 3 Class Lecture and Web Alignment — September 20, 2026

Reviewed the updated lecture source `module_03_graph/student/ppt_day_c_code.md`
against `lab.c`. Both textbooks now explain array-list storage at the graph
and neighbor-list levels, arrays of arrays, traversal-dependent tree and back
edges, and the child/parent/ancestor/descendant cases. An additional D-rooted
example shows why the same edge can change roles. The lecture's `back` and
`save_back` names are mapped to `back_num` and `save_back_num`. Split versus
chained entry assignment and combined versus nested conditions are explained
as equivalent forms. Low values are defined by reachable discovery numbers;
cut-vertex and bridge tests remain separate deductions.

After normalizing the lecture's nonbreaking spaces, its code and `lab.c`
produce identical discovery, component, and A-rooted/D-rooted back-number
results in warning-as-error C11 builds with AddressSanitizer and
UndefinedBehaviorSanitizer. Both textbook editions retain eight sections and
six C blocks: five canonical source excerpts and one supplemental driver.
The extracted programs match their expected output under sanitizers, and
their C blocks match each other byte for byte. The canonical source is unchanged.

The webpage manuscripts match the textbooks exactly. All 100 translated
subsections retain an interactive activity. A new bilingual activity walks
through the 16 neighbor-list encounters from A: five children, five parents,
three ancestors, and three descendants. Early classification uses discovery
and parent records; the later back-number activity explains why descendant
comparisons cannot lower a value. All 16 webpage tests, TypeScript checking,
the production build, and whitespace checks pass. Local browser checks cover
both languages, navigation, state selection, parent skipping, and ancestor
and descendant explanations.

This is technical and editorial validation of the lecture-aligned chapter,
not a new beginner reading pilot. The lecture source and separate matrix-based
module package are unchanged.

## Chapter 3 Entry-Marking Lab and Web Alignment — September 20, 2026

Both graph textbooks now reproduce the current `module_03_graph/student/lab.c`
in five C blocks, followed by the same supplemental driver. The eight-section
structure and hand-worked cut-vertex, bridge, block, and forest explanations
are preserved. The Chapter 3 vocabulary boundary is updated accordingly.

Discovery numbers now begin at 1, with zero serving as the unvisited marker.
Each recursive helper marks its own entry. `mark_group` and `mark_all_groups`
produce component labels 1–4, and `save_back_num` assigns discovery and back
numbers in the same traversal. The driver explicitly resets shared discovery
state before each independent pass, resets `current_group` before grouping,
and initializes all back numbers to zero and parents to -1 before the final
A-rooted search. The reset helper belongs to the textbook driver, not `lab.c`.
A–F finish with visits `1 2 3 4 5 6` and back numbers `1 2 3 2 2 2`; G–J
retain zero visit/back numbers and reset parents -1. Group labels survive.

The English and Korean code blocks and expected output match byte for byte.
Both extracted programs compile as C11 with warnings enabled and produce the
expected output under AddressSanitizer and UndefinedBehaviorSanitizer. The
unchanged source has three existing empty-parameter-list warnings; this is
not a warnings-as-errors check. Independent C review also checked all 32,768
simple six-vertex graphs across every starting root against removal-based
component, bridge, and articulation checks, including repeated reset passes.
No algorithm defect was found within the stated input and caller-state contract.

The webpage content matches both manuscripts exactly, and its downloadable
`lab.c` matches the source. The discovery animation, component labels, syntax
exercises, work counts, driver output, and section mapping now use the same
contracts. All 98 translated subsections retain an interactive activity.
The 14 webpage tests, TypeScript check, production build, and whitespace
checks pass. Local browser checks confirm English and Korean rendering,
entry numbering at 1, final visit/back tables, and component labels 1–4
without browser console errors.

This validates the standalone graph lab, textbooks, and webpage. The separate
matrix-based module package and release materials were not changed or rerun.
It is technical and editorial validation, not a new beginner reading pilot.

## Superseded Chapter 3 lab.c Textbook Alignment — September 19, 2026

Both Chapter 3 textbooks now use `module_03_graph/student/lab.c`.
The first six C blocks reproduce its code, apart from trailing whitespace;
a seventh block adds a driver for one fresh execution from A. Both editions
contain identical C blocks and identical expected output.

The expanded editions add Invariant, a revised Coding Plan, New C Syntax
Explained, and Full C Code Explanation in the Chapter 2 section order.
The source excerpts follow the latest caller-marking implementation: recursive
callers mark new vertices, the group and numbering wrappers mark their roots,
and `save_back_nums` explicitly resets the root parent. Direct
`graph_recursion` examples mark A before the first call. The explanations
distinguish discovery from completion, completed edge insertions from
intermediate writes, and each helper's results at its return point.

The latest source names are `visit_num`, `visit_time`, `save_visit_num`,
`save_visit_nums`, and local neighbor index `adj`. The textbooks use the
fixed array lengths directly for capacity and loop bounds, matching the
removal of the capacity fields and separate edge-count variable. The syntax
sections distinguish implicit zero initialization of global arrays from
uninitialized ordinary local arrays. Only `group` has ten explicit `-1`
initializers; the starting vertex's parent is assigned `-1` by its wrapper.

The examples keep A–J at indices 0–9, store nine undirected edges in eighteen
neighbor entries, and label four connected groups. The discovery and back-number
passes visit only A–F. Their results are `0 1 2 3 4 5` and `0 1 2 1 1 1`;
G–J retain zero in the visit, back, and parent arrays. The driver and result
tables include the final `Visited` flag: zero identifies those untouched
entries, whose values are not computed results. Cut vertices, bridges, blocks, and the
block-cut forest are explained as hand-worked extensions of the same graph.
The storage discussion counts all 100 reserved neighbor slots.

The extracted C11 program compiles with warning flags and runs successfully
under AddressSanitizer and UndefinedBehaviorSanitizer. Standard output matches
the documented output exactly. The unchanged source produces warnings for
empty parameter lists, the integer-to-character assignment, and unused
`data_read`; this was not a warnings-as-errors check. Both manuscripts contain
eight main sections and balanced code fences. Source and output parity checks
pass. Validation covers the standalone textbook example.

## Webpage-to-Textbook Synchronization — September 16, 2026

Chapters 0–3 were compared with the current English and Korean webpage
sources. Chapter 0 already matches the webpage's explanations and glossary.
Chapter 1's main explanations and five C examples also match; the two
textbooks now include the webpage's revised Full C Code Explanation
introductions. Their complete appendices match the web content files
exactly.

Both Chapter 2 textbooks now match `chapter-two.en.md` and
`chapter-two.ko.md` in `student-textbook-web/content/`. The chapter uses
ten array-backed alphabet nodes, with `F` at root index 5 and seven
reachable nodes, followed by the addition-only expression `1+2+3`.
The addition tree ends at root index 3 and evaluates to 6. The current
addition-tree preparation steps and full code explanation are included.
The older `1+2*3` parser lesson is no longer the Chapter 2 textbook.

Both Chapter 3 textbooks already match the current web content files,
including the eight-account follower network, adjacency-list storage,
the Nuri–Mina–Yuna route, and the revised connected-group explanations.
Interactive editing controls and layout remain in the webpage.

Exact source comparisons pass for the Chapter 1 appendices and the full
Chapter 2–3 textbooks. Chapter 2 retains eight sections and seven C blocks;
Chapter 3 retains five sections and seven C blocks. Code fences are
balanced, and the English and Korean C snippets match within each of
Chapters 2 and 3.

This entry records manuscript synchronization. The module implementation,
release-package, and runtime checks below apply to the versions named in
those earlier entries; they were not rerun or realigned in this update.

## Modules 1–2 Textbook Companion Alignment — September 10, 2026

The supporting packages now point beginners to the English and Korean
**Full C Code Explanation** appendices as optional references for individual
lines. The original four textbooks remain unchanged. Module and course
instructor guides preserve the existing release gates, core operations,
three student-authored tests, and rubrics; appendix practice adds no
required reading or submission. The labs explain the extra syntax used by
their function interfaces, headers, placeholders, and supplied test runners.

Module 1's lecture now exactly matches the complete Chapter 1 program,
using five initial values in a plain fixed array. GNU Make and the
instructor PowerShell build script expose a `lecture` target. The existing
textbook-trace test now follows that five-item sequence, and the revised
day-two plan covers the same fixed-array lab. Guidance distinguishes the
textbook search loop's `index == size` absence result from the lab function's
`-1` result. Smaller inquiry fixtures remain separate practice examples.
Module 2's implementation and four-function contract already matched the
textbooks and did not need code changes.

Both reference implementations pass 8 core and 5 extension tests each
under Clang with C11, warnings as errors, AddressSanitizer, and
UndefinedBehaviorSanitizer. Both lectures and standalone autopsies run with
the same checks. All four complete textbook programs compile and produce
their documented output; their executable code agrees across languages.

Release source mappings contain 3, 4, 3, 5, and 16 unique existing entries
for Module 1 Stages A–E, and 3, 4, 3, 4, and 15 for Module 2. Module 1 Stage D
now includes the Korean textbook, and Stage E includes the revised day-two
plan. Both Stage D copies retain the textbooks byte for byte. Isolated
temporary Stage E copies compile using their student Makefiles: incomplete
starter/core and student-test placeholders fail as expected, autopsies run
independently, and completed implementations pass the supplied core tests
(plus Module 1's released extension tests). Solutions, instructor files,
and lecture sources remain excluded from student releases.

PowerShell scripts were reviewed but not executed because PowerShell is
unavailable on this host. No release ZIPs were created or published. These
checks verify technical consistency; they are not a new student-reading
pilot.

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

## Module 3 SNS Package Alignment — September 10, 2026

The full module now uses the textbooks' seven-account follower network.
Inquiry, representation reveal, standard and linear investigations, lab,
evidence, instructor answers, diagrams, and the canonical core test share
the six follows and the `2 -> 3` unfollow. This replaces the temporary
separate three-vertex teaching fixture described in the textbook-only note
below. General API boundary tests and the four-to-three-to-four vertex
autopsy retain their own fixtures.

The five-minute pause keeps three targets and requests only rows 0, 2, and
6 in its orientation task. Component and feed reasoning follows the saved
Stage C attempt. Both textbook languages are Stage D reading alternatives.
The four library functions, three student-authored tests, two 90-minute
meetings, and 100-point rubric remain the implementation and delivery scope.

The reference passes 8 core and 5 extension tests under strict C11 with
warnings as errors, AddressSanitizer, and UndefinedBehaviorSanitizer. The
revised canonical test compares the full matrix before and after removal.
The standalone autopsy produces its intended output without sanitizer errors.
The incomplete starter safely fails 7 of 8 core tests, and all three student
placeholders fail as intended.

Release mappings contain 3, 4, 3, 4, and 14 distinct existing entries for
Stages A through E. Stage D includes both textbook editions unchanged.
Isolated copies built with the student Makefile show the expected starter
and placeholder failures, run the autopsy, and pass all 8 core tests when
the completed implementation is substituted. Instructor, solution, and
extension-test files remain excluded from releases. PowerShell is unavailable
on this host, so the packaging script was inspected and its mappings checked
through temporary copies; the script itself was not executed. No ZIPs were
created or published.

Matrix checks confirm the representation reveal, answer key, and diagrams
agree with the textbooks before and after the unfollow. English and Korean
executable C still match after comments are removed. The Week 3 question
pages agree on 49 prompts, and their index totals and curriculum references
reflect this revision. These are technical and editorial checks, not a new
beginner reading pilot.

## Module 3 SNS Textbook Revision — September 10, 2026

Chapter 3 now follows seven SNS accounts, with arrows from follower to
followed account. The chapter explains maximal connected groups, weak and
strong connectivity, singleton components, and a hypothetical use of
component labels in feed candidate selection. Ranking and post eligibility
remain separate decisions. Removing Sora's follow of Dae splits a weak
component without changing the strong components.

The seven textbook C blocks compile and run together under strict C11 with
warnings as errors, AddressSanitizer, and UndefinedBehaviorSanitizer.
Assertions verify full-grid initialization, the initial and final 16-by-16
matrix states, the unchanged active count, and Sora's out-degree changing
from 2 to 1. Output matches the textbook. Independent reachability checks
confirm the strong and weak component partitions before and after removal.
The account edges, Mermaid diagram, textbook matrix, and instructor-guide
matrix agree. The structure still matches the public header, and the five
core textbook sections appear in the prescribed order.

The teaching guide and companion concept notes now distinguish this
seven-account example from the existing three-vertex lab practice fixture.
The four C functions, lab tests, and release scripts are unchanged. These
checks validate the revised example; they are not a new beginner reading
pilot or a rerun of the earlier implementation and packaging checks.

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
