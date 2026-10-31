# Korean Textbook Validation Record

## Six review findings repaired — 2026-10-30

- Chapter 5: restored the documented `capacity` import adaptation in the
  canonical lab. Repository and website sources now agree. Lecture and all
  seven lab tests pass normally and with ASan/UBSan, both in the repository
  layout and the assembled 22-member Stage E layout. All 38 release source
  mappings resolve. PowerShell itself was not available.
- Active pilot: replaced obsolete dynamic-array, pointer-tree, directed
  iterative-DFS, linked-node, alert-Heap, and lazy-Dijkstra questions with
  current-source questions. The new participant check sheet has four required
  prompts per chapter. All 56 check and 14 transfer prompts match their keys;
  all 43 prerequisite/stage prompts match their criteria. Current-chapter
  concepts are checked only after introduction. Scoring requires requested
  results and reasons; unasked verification notes are not extra requirements.
  README and learner/facilitator templates follow the same protocol. All 89
  active-pilot local links resolve. Numeric transfer fixtures were executed
  against current sources, with independent traces/oracles where appropriate.
- Chapter 9: corrected first-allocation initialization, subsequent no-ops,
  caller payload assignment, and table-chain recycling. Source probes verify
  first use, repeated initialization, and exhaustion; current core/student
  suites pass.
- Chapter 10: both complete C blocks exactly match the current lab, including
  `update_value`. Added matching min/max-mode preconditions, repair directions,
  position meaning, examples, plan, and cost. Direct update probes and current
  core/student suites pass.
- Foundations: Chapter 0 English/Korean count concrete ID inspections before
  notation, separate work/input/extra storage, and distinguish best, average,
  and worst cases. Chapter 2 defines depth and edge height, explains four
  node calls plus a stopping call, and uses `O(h + 1)` extra storage. Source
  instrumentation confirms five peak calls and expression result 6. The
  stale Chapter 2 vocabulary row was corrected.
- Chapter 14 reference: the cut exchange removes another crossing edge of
  equal or greater weight; total cost does not increase, including ties.

The local website's Chapter 0 component/translations/glossary and Chapter 2
raw readings match the repaired texts. All 75 website tests, TypeScript, and
the production build pass. Browser checks verify both languages. Course and
website diff whitespace checks pass. These are local changes, not a new
published website version.

Historical simulation records and the actual-pilot status are unchanged.
These technical/editorial checks do not establish beginner reading success;
no actual participant responses were collected.

## Module 7 current-slide and webpage alignment — 2026-10-28

Homepage follow-up: `/`, `/ko`, and `/en` all open Chapter 7. The stale
`/ko` alias was corrected and published as Sites version 201, source commit
`aed3f377839c1e354bb076b055183dc1e7d01f44`. TypeScript, production build,
and browser verification of all three published routes pass.

All three slide Markdown files now align with the current node-index source.
The question outline's week label is corrected to Week 7 and a concept-slide
spacing typo is fixed; the lab-slide code and canonical `student/lab.c` are
unchanged. English/Korean textbooks, workbook, student activities, glossary,
instructor guides, diagrams, question banks, course contracts, and active
pilot prompts follow safe rewiring, shared-pool ownership, linked Stack,
and linked Queue. The lesson retains 180 minutes, one artifact, three test
groups, and the 100-point rubric.

The source allocates through `new_lnode(void)` and leaves payload assignment
to the caller. Initialization runs once through a static guard. Removal
isolates the returned node; raw FIFO uses `qhead`/`qtail`, returns indices,
and requires separate payload reads and recycling. Module 8 now defines its
own value adapters and Module 9 explicitly assigns fields after allocation.
Their consumers and explanations match the retained Module 7 source.

The bilingual website adds Chapter 7 and opens to it by default. It includes
stepwise safe/unsafe rewiring, recycling-hazard predictions, a shared ten-slot
list/Stack/Queue playground, live invariant checks, and a searchable 21-term
glossary. Physical slots and logical links are shown separately. Simulator
guards are distinguished from unchecked C preconditions. Downloads contain
26 exact release members; `release/sync_web.py` derives web prose and the
reproducible ZIP from canonical module files.

Validation: 75 website tests pass, including 12,000 transitions checked
against independent order/free-slot oracles; TypeScript and production build
pass. Browser checks cover both languages, insertion/detach/recycle, FIFO
payload -1, wrong-order cycle explanation, glossary search, anchors, and
control overflow at the available preview width. C core/student suites pass
normal, NDEBUG, and ASan/UBSan builds; the three matching bilingual caller
programs pass all three modes. Module 8/9 normal/sanitizer and both combined
include orders pass. Three web-sync regression tests pass. The student
archive has exact source/manifest bytes, 48 resolving packaged links,
reproducible regeneration, extracted sanitizer tests, and overwrite refusal.
The support-document audit covers 330 local targets across 57 changed
Markdown files with no missing targets. Technical checks do not replace a
beginner reading pilot. PowerShell wrappers were not executed.

Published through Sites as version 200, source commit
`ad03a93a1648bae728ada119f265eb9c8cb6d521`, at
https://data-structures.chaebinkim.chatgpt.site . Public access is preserved.
Course-repository changes remain local; the separate website repository is
committed and pushed. Canonical lab SHA256:
`420cb07fc204e138d5f5683f24a9d9ed4b1ae4b82e9218bafbbaefc14ba7bc97`.
Student archive SHA256:
`8744233f268e382a42f600e1ac0e309ae6e5933922e7a78ddad3f4831894c09f`.


The historical baseline validation date is August 14, 2026. Dated entries below
record later revisions; the current course has fourteen teaching packages
numbered consecutively 1–14, plus introductory Chapter 0.

## Module 7 aligned with the revised concept slides — October 27, 2026

The English and Korean textbooks follow the updated concept manuscript:
acyclic singly linked nodes with a saved first index, insertion/deletion
and write order, shared storage and costs, free-chain lifecycle, linked
Stack, then linked Queue. The Stack uses guarded caller-side first-node
changes with the supplied primitives. Shared-pool examples distinguish
disjoint active lists, detached allocations, and free slots. Missing/double
returns and stale accesses are explained through concrete state changes.
The original slides and `student/lab.c` remain unchanged.

Student workbook, inquiry, reveal, pause, investigation, evidence, rubric,
lab, vocabulary, and autopsy match the lesson. Instructor plans, answer
keys, models, question banks, active pilot materials, and global maps match
those activities. The deleted separate lab-slide manuscript remains absent
and current entry points no longer link to it. The required work stays one
180-minute artifact with three original test groups and A30/B25/C25/D20.

Checks passed:

- Both textbooks keep the exact five-section order and exact full lab code.
  Their three caller programs match across languages and pass normal,
  `NDEBUG`, and AddressSanitizer/UndefinedBehaviorSanitizer builds.
- Current core and student smoke suites pass normal and sanitizer builds.
  Shared-pool reuse, Stack LIFO, guarded first-node removal, full-allocation
  preservation, and the Queue state table were also checked against the source.
- Standard/linear inquiry and investigation files match. Delivery-guide and
  instructor timings agree on 20+30+35+25+35+35=180 minutes. The rubric totals
  100. Week 7's 36 vocabulary entries and 42 prompts match the consolidated bank.
- All 287 local links in 41 current Markdown sources resolve, accounting for
  release README installation paths. A new 24-entry student archive preserves
  source bytes and inventory/manifest, has 36 resolving links, passes its
  standalone core/student build, and refuses overwrite without changing bytes.
- Independent review clarified that pool reset requires no owned active or
  detached allocation, and raw `enqueue_lnode` requires `next == -1`.

These are technical and editorial checks. No beginner reading pilot was run.

## Module 12 aligned with the supplied lab — October 25, 2026

The required AVL lesson follows `module_12_bst_avl/student/lab.c` and its
exact Module 2 dependency. It uses ten character records, integer links,
separate cached edge heights, and four link-only rotation helpers. Height
updates remain in `_add`, with the promoted root refreshed last. Equal
labels on distinct IDs are accepted; rotations preserve nondecreasing
inorder. Callers initialize fresh IDs, respect the ten-slot capacity, and
retain returned roots. The 64-node allocated pointer API remains optional.

Student and instructor materials, models, lab slides, evidence/rubric,
Chapter 12 guidance, weekly/consolidated questions, and current course
delivery references now describe that source. The Korean textbook retains
its five required sections. Week 12 retains 45 required and 3 optional
vocabulary placements and 47 prompts in both question-bank views. The
required work is one 180-minute trace-and-test artifact, with no source
implementation TODOs.

Current-lab compilation, core, student smoke, and comparison targets pass
with AddressSanitizer and UndefinedBehaviorSanitizer. Core checks cover
four canonical repairs; nonempty transferred subtrees in every case;
empty, singleton, equal-label, and ten-ID builds; exact heights and
reachable IDs; the seven-label measurements; and all 5,040 permutations
of seven distinct labels, checking after every insertion. The exact
ascending/descending/mixed plain-BST heights are 6/6/2 and listed search
counts are 7/7/3. All three AVL builds finish at D with height 2 and three
comparisons for each specified present/missing probe. The optional
pointer-library core and extension suites also pass under both sanitizers.
Strict Clang flags retain six inherited Module 2 warnings about older
declarations, character conversion, and an unused local; no AVL-root
initialization warning remains. The textbook's complete driver also runs.

The deterministic student ZIP contains 30 entries, including both exact
lab sources, current tests, standalone build files, student documents,
and models. Inventory and source-byte equality, deterministic regeneration,
overwrite refusal with preservation, all extracted local links, and the
extracted compile/core/student/comparison targets pass. PowerShell scripts
received static inspection because PowerShell is unavailable. A scoped
audit of 31 current documents found 155 resolving local links, balanced
fences, correct textbook headings, and no trailing whitespace. These
technical checks do not replace a beginner reading pilot.

Lab SHA256:
`4be90edd58eb5e0657977ae6f2bc91dec1fd0b0767bae3defb36003e7b0b2cd2`.
Student archive SHA256:
`9718ca25de58d79be2be6eb170eb775458f454c1fa74f871ff35b511c2a45fd1`.
Earlier entries retain historical validation of the pointer representation.

## Module 10 aligned with the supplied lab — October 25, 2026

The required Heap lesson follows `module_10_binary_heap/student/lab.c`.
Its ordinary Heap reserves ten integer slots with a min/max mode flag,
unchecked add/remove preconditions, upward/downward repair, and bottom-up
construction. Its interval application maintains all ten IDs in max-on and
min-off Heaps, with per-ID epochs, comparator/swap callbacks, and separate
inverse position maps. Input assumptions are ten populated schedules,
one through five nonnegative, chronological disjoint closed intervals per
ID. Equal overlap endpoints succeed. Exhaustion returns before accessing
an unavailable interval and leaves a terminal epoch until reinitialization.
The separate alert-record API and baseline remain optional references.

English and Korean chapters retain the five required section headings and
embed the exact unchanged lab source. Both share the verified integer
fixture `[7,3,5,1,9,4]`, resulting min array `[1,3,4,7,9,5]`, first removal
array `[3,5,4,7,9]`, and max rebuild `[9,7,5,1,3,4]`. The common-on-time
fixture advances ID0 then ID1 and returns 8; its endpoint variant returns 9.
Student activities, diagrams, slides/workbook, autopsy, rubric, instructor
answers, weekly question bank, and course guidance follow those states.
Week 10 retains 47 questions with 40 detailed required and 5 optional
vocabulary entries. Dijkstra references distinguish the current ten-value
lab from the optional 64-record library and its own frontier support.

Warning-enabled compilation and seven core groups pass. Tests exercise
integer ties, min/max drain, mode rebuild, bottom-up construction, single
left child and singleton removal, ID permutations, both inverse maps,
upward and downward key repair, initialization, repeated calls, immediate
and delayed overlap, equality and zero-duration `[5,5]`, and exhaustion
at the fifth pair. A separate integer-time scan oracle agrees with 1,000
deterministically generated valid schedules containing successes and misses.
AddressSanitizer/UndefinedBehaviorSanitizer core and student runs pass.
The optional baseline's 10 core groups and Heap's 9 core plus 4 extension
groups and its autopsy also pass. The lab's six inherited no-prototype
warnings remain; the source was not edited to silence them.

The Python packager produces one deterministic 25-entry student ZIP.
All mapped source bytes and inventory match; faculty and optional library
implementations are excluded. Regeneration produces identical bytes.
A second creation refuses overwrite without changing the first archive.
All 59 packaged local document links resolve. An extracted standalone
release compiles and passes core and student runs. PowerShell wrappers
received static inspection only because PowerShell is unavailable.
A scoped source audit checks 58 current documents, 301 resolving local
links, balanced fences, and exact textbook C blocks. Four trailing-space
lines in the two textbooks are inherited from their verbatim source blocks;
prose has no trailing spaces. Technical checks do not replace a beginner
reading pilot.

Lab SHA256:
`2d2885728d2825fa749a8669f4ea3dca74fd29821b7b93dbe9a59b3907e5791a`.
Student archive SHA256:
`d343f9cbbd139a4cfd9855704d8633c996757e77a65296b0ac1700af4f223f72`.
Earlier entries below preserve validation of the older representation and
release model.

## Module 09 aligned with the supplied lab — October 24, 2026

The required hash-table lesson now follows `module_09_hash_table/student/lab.c`
and its exact `module_07_linked_list/student/lab.c` dependency. Student and
instructor materials, diagrams, assessment, course references, question banks,
and active pilot prompts teach normalized signed hashes, ten bucket heads,
pooled separate chains, recycling, and brute-force/hash-based two sum.
The supplied lab sources are unchanged. The older dynamic open-addressed map
is an optional reference, with its named build targets retained.

Current builds default to actual-source tests. `lab-compile`, `core`, and
`student-tests` work from the module code directory. The student driver
starts with a smoke test; the assignment still requires three original groups.
Core checks cover pool partition/exhaustion/reuse, collision and duplicate
payloads, an 81-target pair-existence oracle, no self-pair, duplicate input
values, and repeated runs. Normal and AddressSanitizer/UndefinedBehaviorSanitizer
runs pass. The optional reference's seven core and four extension groups pass.
Clang reports inherited empty-parameter-list and shadowed-name warnings;
the new drivers introduce no additional warnings.

The Python staged packager retains five A–E archive names. Entry counts are
3/4/3/3/12. Stage E preserves sibling Module 09/Module 07 paths and contains
both exact lab sources, current tests, and student-only build files. All 25
entries were checked byte for byte; deterministic regeneration and refusal
to overwrite were verified. An extracted Stage E builds and passes its tests
without the repository. PowerShell wrappers received static inspection;
PowerShell is unavailable on this host. Stage C now explicitly preserves hand
predictions, with source inspection and execution deferred to Stage E.

A scoped audit of 41 documents found 215 resolving local links and no
unbalanced fences or trailing whitespace. Week 9 has 28 required terms and
44 questions; the consolidated counts are updated. Earlier dated entries
below retain validation of the older representation and release inventory.

## Consecutive Module Numbering — October 24, 2026

Binary Heap is Module/Chapter 10, Dijkstra is 11, BST/AVL is 12, and
Prim/Kruskal is 13. Their package directories, instructor guides, current
course references, release filenames, and test output labels use these
numbers. The Heap's supplied Priority Queue baseline remains inside its
package. Active pilot templates follow Chapters 1–13.

Existing solution core and extension suites pass for all four renamed
packages and the supplied Priority Queue baseline. The Week 13 DSU/MST
reference suites and starter compilation pass with the renamed repository
dependencies. Builds use temporary directories and C11 warning flags.
All 289 local document links checked resolve. All 26 release maps retain
their entry counts and resolving source paths, including the Heap's shared
baseline entries; PowerShell packaging received static validation.
All existing C/header bytes are preserved except four test output labels.

Earlier dated validation entries preserve their historical module numbers;
actionable package paths use the current directory names. Historical
simulation responses retain the numbering of their assessed editions.

## Hash Table Renumbered to Module 9 — October 24, 2026

The Hash Table package moved from `module_10_hash_table/` to
`module_09_hash_table/`, and its instructor guide is now `chapter_09.md`.
Current textbook headings, indexes, course references, question banks,
vocabulary boundaries, and staged release names use Module/Chapter 9.
Week 9 remains the delivery week. Earlier dated entries and simulated
participant responses retain the numbering of their assessed editions.

All seven existing Hash Table solution core groups and four extension
groups pass from the renamed directory under C11 with warning flags.
No C implementation or public API change was required. All 199 local links
in changed or moved documents resolve. The strict 38-file source inventory
and five release maps retain their 3/4/3/3/14 entries with Module 09 archive
names; PowerShell packaging was checked statically. Active pilot templates
identify Hash Table as Chapter 9 without duplicate chapter headings;
historical simulation responses remain unchanged.

## Module 7 Directory Consolidation — October 24, 2026

Removed the redundant `week_07/` subtree. Canonical lab, rubric, and lesson
plan remain in `student/` and `instructor/`. The current test harness moved
to `code/tests/test_lab_core.c`, `test_lab_student.c`, and `lab_test_support.h`;
the normal build now defaults to the supplied lab. Existing optional library
targets remain available. The Python release packager moved to
`release/prepare_student_release.py` and emits `dist/module_07_linked_list.zip`
using the canonical `student/` and `code/` layout. All active course and
release links use this structure.

The supplied `student/lab.c`, DSU header/implementation, and Module 16's DSU
reference path match the pre-change snapshot. Current core and student smoke
tests pass normally and under AddressSanitizer/UndefinedBehaviorSanitizer;
the optional library core passes. The unchanged lab retains its nine
non-prototype warnings. An extracted standalone release passes the current
core/student tests. Its 25 entries match all 24 mapped sources byte for byte,
its manifest is exact, all 42 local document links resolve, and it excludes
faculty/optional implementations. Overwrite is refused without changing the
existing archive. PowerShell wrappers received static review only because
the runtime is unavailable.

The canonical rubric retains 100 points and the lesson retains 180 minutes.
Independent review found no loss of unique required lesson content. Earlier
validation entries preserve their historical directory layouts.

## Module 8 Graph BFS Replacement — October 24, 2026

Removed the Tree BFS teaching package and renamed the Graph BFS package from
Module 9 to Module 8. The Graph BFS instructor guide replaces the former
Tree BFS Chapter 8 guide. Course maps, style/vocabulary boundaries, question
banks, downstream references, and five staged archive names use the current
numbering. Week 8 is a single 180-minute Graph BFS unit retrieving FIFO from
Week 7, with matrix BFS and path reconstruction as required student code and
supplied adjacency-list comparison. The required Tree BFS bridge is removed.

Reference solution core tests pass all eight groups and extension tests pass
all seven groups under real CLT Clang with C11 warning flags and an explicit
macOS SDK. The student-test template compiles and reports the expected three
unfinished TODO failures; it is not a completed student submission. All
fourteen existing Graph BFS C/header files and every Graph DFS file match
the pre-change snapshot byte for byte.

The five Module 8 release maps contain 3/4/3/3/21 entries; all 34 sources
exist and exclude instructor files, solutions, and private extension tests.
PowerShell packaging received static verification, not execution. Checks of
467 Markdown files found balanced fences and no new broken local links
across 640 file-link occurrences. The existing Module 4 Stage E README link
is valid in its extracted-archive context. All thirteen weekly question
lists match their consolidated banks: 249 course-wide plus 575 weekly
prompts remain (824 total), with 505 required and 26 optional vocabulary
placements. Independent review found no substantive integration gap.

Historical pilot records preserve their original chapter identities and
identify retired editions explicitly. Changes remain local and uncommitted.

## Module 7 Updated lab.c Synchronization — October 23, 2026

The current required textbook and course materials now match the supplied
`module_07_linked_list/student/lab.c`. Its source is unchanged. The lab uses
a ten-slot index-linked node pool and free chain, known-predecessor insertion
and detachment, linked FIFO, linear array queues, and a circular array queue
with nine usable positions. No heap-list TODOs are required. Removal and
recycling are separate; array boundary enforcement belongs to the caller.
This entry supersedes the earlier same-day Week 7 ownership/heap-list scope.
The old pointer-list/DSU implementation remains an optional library, with
DSU introduced alongside Kruskal in Week 13.

Updated artifacts include English/Korean textbooks, a bilingual workbook,
concept and lab slide manuscripts, student activities/evidence/rubric,
instructor guides and models, weekly package/tests, course maps and
vocabulary boundaries, and question banks. Week 8/9 transfer descriptions
reuse FIFO from Week 7 without changing their supplied backend contracts.
The weekly and supporting rubrics share the same 100-point categories.
The instructor plan totals 180 minutes. Week 7 retains 36 vocabulary
placements and 36 questions; consolidated question text matches its page.

Both textbook C sections match the complete lab exactly and retain the five
required sections in order. Checks of 52 affected or directly linked
Markdown files found balanced fences and 271 resolving local links.
Five core cases cover pool exhaustion/reuse, list insertion/detachment,
linked FIFO with prepared reuse, linear exhaustion, and circular
wraparound/repeated cycles. Core and student smoke tests pass with real
CLT Clang under C11 warning flags, then AddressSanitizer and
UndefinedBehaviorSanitizer. The original lab produces nine deprecated
non-prototype declaration warnings; warnings were neither suppressed nor
misreported as a warnings-as-errors pass.

The current Python packager produces a 16-entry standalone archive with
one unchanged lab source. Its extracted build passes the same tests.
Canonical documents and lab bytes, complete manifest, local archive links,
exclusion of faculty/legacy implementations, and refusal to overwrite an
existing ZIP were checked. The old PowerShell staged packager now delegates
to this weekly release. The checkout Make wrapper passes; PowerShell is
unavailable, so the PowerShell wrappers were inspected but not executed.
No generated release is published by this revision.

An independent technical review checked code, arithmetic, predicates,
preconditions, navigation, and transfer descriptions. These checks do not
establish a human beginner-reading pilot pass. The textbook website has
no Chapter 7 implementation; it was not modified or published.

## Historical Module 7 Linked-List Replacement — October 23, 2026 (superseded for Week 7)

Removed the former Queue package and renamed the former Module 14 package to
`module_07_linked_list/`. The required Week 7 release contains only linked-list
front insertion, first-match deletion, destruction, and ownership evidence.
DSU reference code remains available there, but its first required teaching
and assessment is the combined Week 13 DSU/Kruskal unit. FIFO and supplied
Queue backends are introduced in Week 8. Chapters 13 and 14 are retired;
Chapters 15 and 16 retain their numbers.

Both review findings are fixed. The original Module 16 staged release ignores
the separately packaged `week_13/` subtree while retaining its strict 47-file
source inventory. Tree BFS documentation now describes borrowed node pointers
paired with depths; Graph BFS uses a supplied vertex-ID Queue. The full DSU
API/output non-aliasing contract is also included in the Week 13 header.

The required linked-list reference and optional combined List/DSU core and
extension tests pass C11 warnings-as-errors with ASan/UBSan. The safe linked
list autopsy passes. Both bounded student releases were generated and
extracted into independent temporary directories: untouched starters compile
and fail the intended behavioral tests; completing only the three advertised
function bodies in each release passes its core and student-template targets
under ASan/UBSan. The Week 7 archive has ten entries, excludes DSU and faculty
solutions, and refuses overwrite. The Week 13 archive includes supplied Prim
and excludes the DSU reference backend and faculty solutions.

Tree BFS and Graph BFS each pass all eight core test groups under the same
strict compiler/sanitizer configuration. The original MST extension tests
pass. Original linked-list staged maps retain 3/4/3/3/18 entries; original MST
maps retain 3/4/3/3/22 entries. Every mapped source exists, the original MST
inventory is exactly 47 files after exclusions, and extracted original Stage E
starters compile. PowerShell is unavailable: its generators were inspected
and their inventories/archive maps emulated, not executed.

Repository-wide checks cover 490 Markdown files, 581 local links (including
one README link in its extracted-archive context), and nine heading anchors.
All resolve. Both calendars contain Weeks 1–13 exactly once, new Week 7 and
Week 13 plans each total 180 minutes, and the course lists fourteen teaching
packages. Consolidated question text matches the weekly pages exactly:
299 + 276 = 575 weekly questions, plus 249 course-wide questions (824 total).
Vocabulary counts remain 515 required and 27 optional placements.
Deleted-package paths remain only in clearly historical records. Whitespace
checks pass. An independent review found no actionable issue in the new Week 7
release or its integration. These are technical/editorial checks, not a human
reading pilot. The separate website was not changed or published.

## Chapter 6 Revised Lab-Slide Synchronization — October 18, 2026

The supplied `lab.c` and conceptual PPT material are unchanged since the
previous alignment. The revised lab slides clarify preorder → neighbor
loop → postorder, introduce `init_visit()` before edge storage, and give
the stack-pop proof. Both textbook editions, the class workbook, module
overview, and instructor materials now follow that sequence. The proof
uses the inability to reach an ancestor visited before the parent while
retaining equality as a closing boundary. The postorder suffix invariant
and root exception remain precise.

All 61 website tests, TypeScript, and the production build pass. The nine
C lab checks and both original/slide drivers pass under AddressSanitizer
and UndefinedBehaviorSanitizer. The drivers reproduce their documented
rows and finish with an empty stack. All 65 local links in the eight
changed teaching documents resolve, code fences balance, and whitespace
checks pass. Independent final review found no substantive correctness
issue. The bilingual web manuscripts, standalone downloads, updated lab
slides, workbook, dependencies, and all eleven ZIP entries agree.

Desktop/mobile browser QA confirms the new preparation sequence and slide
link, English/Korean content, non-root postorder suffix, root empty stack,
no document overflow, and stable panel/following-content positions across
return states. Version 199, source
`0772f4c2b8b9e0ff8948d546e7f3c8eb333ba66c`, deployed successfully as
`appgdep_6ad4b64b177c819194d532a81966a5bf`. The live updated explanation
and postorder panel were inspected. It also publishes the previously local
postorder revision below. GitHub pushes remain stopped at the user's request.
Proof: `student-textbook-web/outputs/chapter-6-oct18-sync.jpg` and
`student-textbook-web/outputs/chapter-6-oct18-postorder.jpg`.
These are technical/editorial checks, not a human reading pilot.

## Chapter 6 Postorder Parent-Edge Invariant — October 17, 2026

The English/Korean textbooks and teaching materials now distinguish the
non-root postorder checkpoint from its parent's subsequent boundary test.
At that checkpoint all branch edges have been handled: they are assigned
or pending. The pending suffix starting at the incoming parent edge shares
that edge's eventual BCC. Earlier stack entries can belong to other BCCs;
the suffix may be only part of the whole BCC. The root has no incoming
edge and its postorder stack is empty. Visit 4 and visit 3 demonstrate the
different-prefix and partial-block cases respectively.

The website's `postorderStack()` derives this split from return snapshots.
Captions and the invariant panel expose the boundary, older prefix, and
branch suffix before the parent decides. Two regression tests check all
four-vertex simple graphs at every root in raw and per-pop traces, incoming
boundary presence, completed-subtree edge accounting, membership in the
parent edge's final BCC, prior nested block removal, and the root exception.
A triangle behind a single connecting edge prevents conflating the whole
stack with one BCC. A separate read-only model check covered 1,098 simple
graphs on 2–5 vertices and 3,651 non-root returns with no violation.

All 61 website tests, TypeScript, and production build pass. Bilingual
repository/web/download manuscripts, the workbook, and all eleven ZIP
entries agree. All 47 local links in affected materials resolve; fences
balance and whitespace checks pass. Browser QA at 1440/390 pixels covers
English/Korean return narration, prefix/suffix examples, root state, zero
main-content tables/lists, no overflow, and stable measured panel/following
content positions. Source C and PPT inputs are unchanged.

The revision was initially local in website commit
`23f7c4fb1eabbe5842b46b9be3c32616b7a5bade`; it is now included in
published version 199. GitHub pushes remain stopped at the user's
request. Original proof: `student-textbook-web/outputs/chapter-6-postorder-local.jpg`.
These are technical/editorial checks, not a human reading pilot.

## Chapter 6 Edge-Stack Invariant — October 17, 2026

Both textbook editions now explain the exact-once partition of handled
edges into pending and assigned edges at push or completed pop-and-store
checkpoints. Assigned edges include the forming block. Initialization,
maintenance, and termination use the existing completed visit numbers.
The suffix explanation excludes nested blocks already emitted; the
low-link comparison and inclusive boundary pop justify grouping, while
the accounting invariant rules out missing or duplicate edges. C guidance
explains the transient local edge, forming length `pos`, and delayed
`bcc_size` update. The workbook and instructor guides carry matching
questions and checkpoint counts. No lab/PPT input or algorithm changed.

The existing webpage stack player now displays independent handled-history
accounting and the current pending/assigned equation, including the partial
row note. Two regression tests cover every raw/per-pop prefix for the slide
and three original roots, reset, completion, and corrupted snapshots with
missing, duplicate, replaced, or future edges. All 59 website tests,
TypeScript, and production build pass. Both manuscripts, standalone
textbooks, the workbook, and all eleven source ZIP entries agree. All 47
local links in the invariant materials resolve and code fences balance.

Browser QA verifies 8=7+1 during the first pop, 10=0+10 at completion,
reset to 0=0+0, English/Korean rendering, desktop/mobile overflow, and
stable measured panel/following-content positions. The main content keeps
zero tables/lists. Independent review found no actionable correctness
issues. Version 198, source `d7115152677718d2fa49697c2ae80ecbcc0be351`,
deployed successfully. Proof:
`student-textbook-web/outputs/chapter-6-invariant.jpg`.

These technical/editorial checks do not establish a human reading pilot.

## Chapter 6 Updated Lab and PPT Alignment — October 17, 2026

The current lab/PPT source inputs are preserved. Both textbook editions,
the class workbook, teaching guides, diagrams, and release descriptions
now use the source's `edges[45]`, `bcc[9][45]`, `bcc_size[9]`, and separate
ten-entry stack limit. Explanations and code excerpts show the parent
checking a completed child immediately after the recursive call returns.
Strictly smaller low-links leave edges pending with `continue`; equality
or larger values call `close_bcc()` and include the boundary tree edge.
The slide's abbreviated `back` name is distinguished from `back_num`.
The conceptual visit-number example and separate A–J coding input remain.

The new `code/tests/test_lab.c` has nine passing checks: supplied alphabet
and slide results, isolated/self-loop scope, strict/equal child boundaries,
root branches, a ten-node path using all nine result rows, a complete
five-node graph using ten pending slots, and two root-sharing blocks using
twelve records while staying inside the stack limit. Normal and
AddressSanitizer/UndefinedBehaviorSanitizer runs pass. Both lecture drivers
reproduce their documented raw rows and final empty stack. The host's
system compiler/make shims require an unaccepted Xcode license, so these
checks used the installed Command Line Tools binaries directly with the
MacOSX SDK; inherited source warnings were not treated as errors.

The website model now ends each child call before recording the parent's
keep/close decision. Regression checks verify its active path, timing,
per-pop conservation, boundary inclusion, unchanged groups, and focused
edges. Extraction/storage playback has 40 states, pipeline 103, with the
other traversal counts unchanged. All 57 website tests, TypeScript, and
the production build pass. All eleven ZIP entries match standalone files;
both drivers compiled and ran from an isolated extracted ZIP under both
sanitizers. Seventy-four edited course-document links resolve.

Browser checks cover English/Korean, 1440/390-pixel layouts, completion,
reset, parent-side narration, root highlighting in second-block extraction,
zero main-content tables/lists, no document overflow, and stable measured
panel/following-content positions during replay after measurement. Version
197, source `82ed2f7e10cf46d7ae98d07df602b11201c3ed4b`, deployed successfully
and was inspected in the in-app browser. Direct unauthenticated HTTP asset
requests returned 403 and are not counted as a successful asset audit.
Proof: `student-textbook-web/outputs/chapter-6-updated-lab.jpg`.

These are technical/editorial checks, not a new human beginner-reading pilot.

## Chapter 6 Separate Back-Edge Encounters — October 14, 2026

The first traversal, low-link playback, and pipeline low-link phase now expose
every back-edge encounter as a distinct frame. A shared `traversalFrames()`
selector preserves classification/recording behavior and prevents filter drift.
First traversal/low-link/pipeline counts are 20/26/97 states. All four edges
appear separately in encounter order. Low-link updates have separate steps;
the 6→4 encounter explains why the current value 3 remains unchanged.

Twenty-four targeted model/content tests, TypeScript, and production build
pass. Tests cover all four focused encounters, no future records, no fictitious
lowering, unchanged final state, blocks/counters, and alternate trace input.
Browser checks confirm consecutive traversal encounters, inspection/update/
unchanged-value steps, matching pipeline focus, both languages, mobile overflow,
stable panel/following-section heights, completion, and reset. Published version
196 succeeded and the live result was inspected.
Proof: `student-textbook-web/outputs/chapter-6-back-edge-steps.jpg`.

## Chapter 6 Straight Back Edges — October 14, 2026

Back edges and their legend use straight dashed paths. Tree edges remain
solid, and canonical arrows, focused endpoint roles, and found-block colors
are preserved. Low-link labels at visits 1, 2, and 4 move beside their circles
to clear incoming and vertical arrows. TypeScript and production build pass;
browser checks confirm straight paths, retained dashes/roles, readable low
values, and no desktop/mobile overflow. Published version 195 succeeded;
the live result was inspected after reloading a transient page-load failure.
Proof: `student-textbook-web/outputs/chapter-6-straight-back-edges.jpg`.

## Chapter 6 DFS Edge Shapes and Endpoint Roles — October 14, 2026

All shared Graph DFS visuals use solid straight tree arrows and dashed curved
back arrows. Focused edges label parent/child or descendant/ancestor endpoints.
The stored DFS direction stays consistent through reverse encounters and
queries, while unreached child circles remain blank. Screen-reader descriptions
name each role and its live visit number. Shapes reveal the selected frame's
known records and persist after extraction; found-block colors apply to paths
and arrowheads together. Endpoint badges avoid the focused connections.

Twenty-three targeted model/content tests, TypeScript, and production build
pass. Browser checks cover tree-before-entry, reverse parent/descendant scans,
all six tree/four back edges, tricky badge placements, retained completed-block
colors, both languages, stable measured sizing, and no overflow at 390/1440
pixels. Published version 194 succeeded; the live result was inspected.
Proof: `student-textbook-web/outputs/chapter-6-edge-roles.jpg`.

## Chapter 6 Persistent Found-Block Colors — October 14, 2026

Completed blocks keep distinct green/blue edge colors through later branches
and completion in extraction, overview, pipeline, and storage animations.
Forming groups stay active-colored until the inclusive boundary pop finishes.
Legends and block-card borders use matching colors; selected-edge emphasis
changes width without overwriting found colors. Colors reflect each selected
snapshot, so rewind/reset hides future groups.

Twenty targeted model/content tests, TypeScript, and production build pass.
The timeline test covers persistence after later pushes and partial closes,
completion, rewind/reset, and unchanged snapshots. Browser checks confirm
five retained edges after first closure, ten retained edges in two colors at
completion, matching related players, stable following content, and no mobile
overflow. Published version 193 succeeded and the live result was inspected.
Proof: `student-textbook-web/outputs/chapter-6-found-block-colors.jpg`.

## Chapter 6 Animation Throughout the Webpage — October 14, 2026

Every Thinking/Efficiency topic now has playback. Static walkthrough tables
and lists are replaced with their visuals. Glossary definitions, coding
plans/review, C storage mappings, and text output advance through measured
cards; source C/shell excerpts remain intact. Both published languages have
zero HTML tables/lists in main content. Printable sources are unchanged.

The graph carries live low-link values. Extraction pops one edge per frame,
preserves first-entry visit numbering, and marks partial blocks as forming.
Block playback shows both groups and removal of their shared visit 3.
The pipeline animates all three actual passes. Efficiency playback counts
21 entries/60 inspections, 49 preparation cells then 20 scans, and peaks of
6 active calls/8 pending edges. Representation views inspect one entry,
record, or symmetric cell pair at a time.

All 51 website tests, TypeScript, production build, and independent review
pass. Browser checks cover all ten topic players, final low-links and block
sizes, empty/partial/full stack states, card progression, both languages,
stable following content, and no panel/document overflow at 390/1440 pixels.
Efficiency figures adapt to their container width to preserve legibility.
Published version 192 succeeded; the live page was inspected. Proof:
`student-textbook-web/outputs/chapter-6-all-animations.jpg`.

## Chapter 6 Interactive Edge Recording and Lookup — October 14, 2026

The third conceptual webpage topic replaces its static edge-record table
with DFS playback, a growing clickable edge list, and endpoint lookup.
Directions and tree/back types remain available by selecting records.
Lookup includes only the selected replay's recorded prefix. Both website
languages have coherent animation lead-ins; printable tables remain intact.

Eleven model tests and four content/parser tests, TypeScript, production
build, and independent review pass. Browser checks cover recording before
child entry, symmetric lookup, recorded/unrecorded/absent connections,
direction/type metadata, ten unique records, automatic completion, all
three representation views, stable following content, and 390/1440-pixel
layouts. Published version 191 succeeded; the live animation was inspected.
Proof: `student-textbook-web/outputs/chapter-6-record-edges.jpg`.

## Chapter 6 Neighbor Classification for All Nodes — October 14, 2026

The interactive classification visual has selectors for all seven completed
visit numbers. Each selector jumps to first entry in the same traversal.
Categories follow the active node and remember actual encounter cases;
unexamined entries remain pending. Current-neighbor highlighting replaces
the fixed visit-3 caption.

Eight model tests and four content/parser tests, TypeScript, and production
build pass. New model checks cover every node's final classifications,
entry states without future scan results, and visit 3's neighbor 6 becoming
a descendant when examined after the child branch. Browser checks cover all
selectors, bilingual categories, current-neighbor highlighting, stable
following content, and 390/1440-pixel overflow. Published version 190
succeeded and the live page was inspected. Proof:
`student-textbook-web/outputs/chapter-6-all-neighbors.jpg`.

## Chapter 6 Animation-Only Web Example — October 14, 2026

The first conceptual webpage example omits the static edge list and
neighbor-order table in both languages. Its animation omits duplicate
visit-number and active-path lists while retaining the numbered graph,
controls, current-step explanation, and discovered count. Lead-in prose
now refers to the animation. Later teaching examples and printable
textbook references retain their contents.

Four content/parser tests, TypeScript, and the production build pass.
Browser checks confirm first-entry and completed numbering, absence of
the duplicate lists, and no overflow at 390 pixels. Published version
189 succeeded; the live page was inspected and the preview stopped.
Proof: `student-textbook-web/outputs/chapter-6-animation-only.jpg`.

## Chapter 6 Representation Progression Correction — October 14, 2026

The English/Korean textbooks and teaching materials now identify adjacency
lists as Chapter 3 review. Edge lists and adjacency matrices are introduced
in Chapter 6. Website prose, comparison labels, textbook/workbook downloads,
and source ZIP match that progression. Visit-number examples and C excerpts
retain their validated contents.

The four website content/parser checks, production build, and whitespace
checks pass. Browser QA confirms the corrected published prose and comparison
labels, no mobile document/panel overflow, and the published version 188.

## Chapter 6 Visit-Number Diagram Synchronization — October 14, 2026

The latest concept PPT uses 1–7 as completed DFS visit numbers. Both
textbooks, seven class/support documents, slide driver, website, and
source downloads now use that interpretation. Replay vertices receive
numbers on first entry; numbered endpoints in explanations refer to the
completed traversal. Internal 0–6 indices and A–G source characters are
explained only in C Code. The supplied A–J lab example remains separate.

Validation completed:

- Visit 3's neighbor cases, visit 6's low-link value, full pair stacks,
  and both five-edge block orders match independent simulation and C.
  Low-links remain 1/1/1/3/3/3/2; the common vertex is identified by visit 3.
- The updated slide driver prints computed visit numbers at edge and block
  endpoints, alongside a separate index/visit/parent/low table. Both ZIP
  drivers pass exact-output checks under ASan/UBSan.
- Both editions retain five sections and 7/3/10 topics. Conceptual sections
  have no C identifiers or obsolete vertex labels. C fences match the
  unchanged sources. Current repository links and whitespace checks pass.
- All 41 website Node tests, TypeScript, and production build pass. The
  audit covers 24 routes, 679 links, 384 anchors, and 15 assets. Updated
  concept-slide downloads match the repository's 41 H2 headings.
- Browser checks pass first-entry numbering, completed 1–7 diagram,
  wrapping endpoint list, exact pair blocks, stable measured heights,
  390/1440-pixel layouts, and bilingual hash preservation. Mini-quiz
  prompts appear in both languages. Published version 187 succeeded.

## Chapter 6 Updated Concept Slides and Website — October 14, 2026

Both textbooks, the bilingual class workbook, instructor materials,
models, and website now follow the updated question-led concept slides.
The primary graph is vertices 0–6, ten undirected edges, start 0, and
ascending neighbors. Vertex labels and positive discovery numbers are
explicitly distinguished. The materials cover all four neighbor cases
at vertex 2, traversal timing, three representations, once-only recording,
symmetric lookup, low-link propagation, full endpoint-pair stack states,
two five-edge blocks sharing vertex 2, and the midterm review sequence.
C names, numeric edge indices, reset details, and capacities stay in C Code.

The original A–J lab and both PPT inputs are preserved. The additional
`code/lecture/ppt_demo.c` prepares the slide graph and calls the unchanged
lab implementation. `make lecture-ppt` runs it; the original lecture target
continues to run the alphabet example. Website downloads include both
drivers, the updated PPT, the class workbook, both textbooks, and a runnable
source archive. Chapter 6 remains the default homepage in both languages.

Validation completed:

- Independent simulation and native C execution agree on discovery 1–7,
  parents none/0/1/2/3/4/2, low-link 1/1/1/3/3/3/2, ten edge records,
  rows `[7,6,5,4,3]` and `[9,8,2,1,0]`, and an empty final stack.
- Each pass examines twenty neighbor entries; three passes make sixty
  inspections and twenty-one vertex entries. Lookup preparation covers
  49 active cells. Peak pending edges are eight; active recursion is six.
- Both source-archive drivers compile and reproduce exact expected output
  under AddressSanitizer and UndefinedBehaviorSanitizer. Original source
  excerpts remain unchanged and source-matching in both textbooks.
- All 41 website Node tests, TypeScript, and the production build pass.
  The HTTP audit passes 24 routes, 679 local links, 384 anchors, and 15
  download assets. Repository Markdown links and whitespace checks pass.
- Browser QA passes playback completion, final pair blocks, stable following
  content, no panel/document overflow at 390 and 1440 pixels, and a shared
  lesson hash across language switches. Published version 186 succeeded.

## Chapter 6 Lab and Both PPT Sources — October 14, 2026

The English textbook and new Korean companion now follow the current
`module_06_graph_dfs/student/lab.c`, `ppt_material.md`, and
`ppt_lab_material.md`. The source lab and both slide inputs remain
unchanged. The chapter includes `_edge_iteration_()` before its edge-list
and block-extraction specializations, the source's add-edge/parent/call
order, and the `start_node` wrapper signatures. It explains symmetric
edge lookup, internally vertex-disjoint paths, inclusive postorder
extraction, and preservation of saved low-link values between passes.

The new `student/class_material.md` supplies predictions, edge/low-link/
stack tables, exactly three retrieval-pause targets, runtime evidence,
cost/reset/capacity checks, and fresh-case transfer questions. The
instructor answer key covers those tasks. The chapter guide, lesson plan,
technical notes, models, module/code overviews, and course links follow
the same current teaching path.

Older matrix-DFS student materials are explicitly labeled. The release
manifest and Stage D README identify Stages A–C/E as the checked matrix
exercise and Stage D's current textbook/models as array/BCC enrichment.
Existing starter APIs, grading contracts, release scripts, and archives
retain their contents. This update is repository-only; the website
working tree remains unchanged.

Validation completed:

- Both textbooks preserve their five-section sequence. Their bilingual
  C blocks match each other. The Module 6 implementation excerpts reproduce
  the complete current lab modulo whitespace; the low-link excerpt matches
  the included Module 3 function.
- The lecture driver compiled directly with native Command Line Tools
  Clang, C11 warning flags, and an explicit macOS SDK. Its complete output
  matches the root-A reference: eight edge records; rows `[1]`,
  `[7,6,5,4,3,2]`, and `[0]`; empty final stack.
- A temporary harness passed six independent fresh-process cases under
  AddressSanitizer and UndefinedBehaviorSanitizer: supplied root A, root G,
  isolated root I, chain, triangle, and branching root. Root A also checks
  that `_edge_iteration_()` assigns discovery/parents without recording
  edges or blocks. The checks cover exact rows, symmetric edge indices,
  exactly-once edge membership, and final empty stacks.
- Markdown fences, all 76 local links/anchors across the revised teaching
  files, and changed-file whitespace passed. Both lab/slide inputs and the
  separate website working tree were checked for unintended changes.
- The unchanged included sources still emit 19 strict compiler warnings:
  11 empty-parameter-list warnings and eight integer-to-character
  conversions. The host's system Make/tool wrappers stop at an unaccepted
  Xcode license; direct native compilation verified the lecture recipe's
  source and output without changing the host license state.

## Chapter 6 Array DFS and Biconnected Components — October 10, 2026

The current `module_06_graph_dfs/student/lab.c` is the authority and was
left unchanged. The textbook, new Korean `ppt_material.md`, instructor
chapter/lesson/technical/answer materials, diagrams, and module overview
now use the included Module 3 adjacency-list graph, discovery numbers,
DFS edge indexing, saved low-link values, and an edge stack for postorder
biconnected-component extraction. The index and vocabulary boundary now
match this chapter. The matrix/typed-vertex-stack starter, assessment,
release, and Practical 1 materials remain a separate legacy track.

The example is A–J with the nine supplied undirected edges. Root A reaches
A–F and indexes eight edges. Its exact result rows are `[1]`,
`[7,6,5,4,3,2]`, and `[0]`, with sizes 1/6/1 and `top == -1`.
Explanations distinguish `>=` block closure from `>` bridge detection,
include the parent edge in each popped row, explain root short-circuit
behavior, and retain the one-component/one-call and unchecked-capacity
assumptions. No validation or failure-preservation API is attributed to
this source.

Validation completed:

- The new `code/lecture/lab_demo.c` includes the unchanged lab. The
  `make lecture` target built and produced the expected discovery, parent,
  low-link, edge, and block tables.
- A temporary verification harness passed six independent cases under
  AddressSanitizer and UndefinedBehaviorSanitizer: exact supplied root-A
  results, chain, triangle equality closure, branching root, root G, and
  isolated root I. It also checked symmetric edge indices, exactly-once
  edge membership, and an empty stack at completion.
- The textbook's four implementation C blocks reproduce `lab.c` modulo
  whitespace. Combining those blocks with the lecture entry point compiled
  under the sanitizers and produced output identical to the lecture driver.
- Required five-section textbook structure, Markdown fence pairing, local
  links in the revised teaching path, and changed-file whitespace passed.
- Strict C11 compilation reported 19 warnings in the unchanged included
  sources: 11 empty-parameter-list warnings and 8 integer-to-character
  conversion warnings. No warning-clean claim is made. Native toolchain
  binaries and an explicit SDK path were used because the system developer
  tool wrappers stopped at an unaccepted Xcode license.

No Chapter 6 webpage mirror exists in the current web source. Website
publication and legacy assessment/release migration were not part of this
revision.

## Chapter 4 Updated PPT Lab and Explicit Termination — September 30, 2026

The current `module_04_stack/student/lab.c` and `ppt_lab_material.md` were
checked and preserved. The English/Korean textbooks, lecture/support
materials, course summaries, and webpage now use `postfix`, conversion loops
guarded by `!is_empty()`, `switch` precedence, and explicit
`postfix[pos++] = '\0'` writes. There is no stack sentinel. Explanations
distinguish `return` from `break`, and the parentheses trace pops before
testing for `(`. Conversion guards do not validate expression grammar or
make the raw stack helpers safe for invalid calls.

The lecture implementation sequence follows the updated PPT lab: array
stack, precedence and `switch`, `while` and `&&`, conversion, then evaluation.
The parentheses converter remains a subsequent extension. Both worked
examples retain their results: `1-2*3+4 -> 123*-4+ -> -1` and
`1+(2+3) -> 123++ -> 6`. Their conversion peaks are two and three active stack
cells. Explicit termination leaves `top == -1` and advances `pos` to 8 and 6.

Validation completed:

- All eight C baseline groups passed, including AddressSanitizer and
  UndefinedBehaviorSanitizer checks. GNU Make lab-demo and lab-tests passed.
  Strict compilation reports seven empty-parameter-list warnings and seven
  int-to-char conversion warnings in the preserved source.
- Each textbook's six C blocks matches `lab.c` modulo whitespace. Both
  reconstructed sources compiled and produced the two expected demo results.
- Lecture review checked 24 count rows and 31 operator-stack rows. Module 4
  Markdown fences and changed-file whitespace checks passed. The webpage's
  `lab.c` download preserves the source's two existing trailing-space lines.
- All 26 web tests, TypeScript validation, and the production build passed.
  The affected mirror test also passed after adding the PPT lab download.
  Eight content/download mirrors match their sources; all six Chapter 4
  downloads match the production build bytes.
- All five release stage mappings contain unique, existing source/entry
  paths: A=3, B=4, C=3, D=4, E=14. Stage E now includes the unchanged PPT lab
  source so the lab guide's link resolves. Inquiry gates remain intact.
  PowerShell ZIP generation was not run on this host.
- The local preview returned HTTP 200. Visual browser QA could not run:
  the browser security policy blocked reloading the existing preview tab.
  No visual-verification claim is made for this revision.

Sites version 154 was published successfully at
[the Chapter 4 webpage](https://data-structures.chaebinkim.chatgpt.site/chapter-4)
from web source commit `6745ce77e37916b91e5a0d6c9f378dcdcdaa774f`.
This entry supersedes the earlier Chapter 4 sentinel and `eq_post` claims
below, which remain as historical records.

## Chapter 4 Top Index, Null-Terminated Scans, and Parentheses — September 29, 2026

The current `module_04_stack/student/lab.c` is the authority and was left
unchanged. The English/Korean textbooks, lecture notes, worksheets, diagrams,
instructor guides, assessment materials, release documentation, and Chapter 4
course summaries now use `top == -1` for empty, `stack[++top]` for push,
`stack[top]` for peek, and `stack[top--]` for pop. The item count is `top + 1`.
Full/empty predicates report state; the operations remain unchecked.

`convert_to_postfix()` reads `eq` and writes `eq_post`; both conversion and
evaluation scan to the null terminator. Shorter valid expressions now work
within the eight-character buffers. The dedicated
`infix_to_postfix_parentheses()` reads balanced groups from `eq_paren`.
The worked examples are `1-2*3+4 -> 123*-4+ -> -1` and
`1+(2+3) -> 123++ -> 6`. The sentinel becomes the output terminator at
index 7 or 5, leaving local `pos` at 8 or 6 and `top == -1`.

Both editions use the five required main sections. Their six C blocks
reproduce the current lab modulo whitespace. Combining each edition's blocks
with the updated demo driver compiled and produced both expected results.
The separate autopsy now contrasts correct `stack[top]` with faulty
`stack[top + 1]` at `top == 1`.

Validation completed:

- All eight C baseline test groups passed with Clang 21; the same groups
  passed with AddressSanitizer and UndefinedBehaviorSanitizer.
- The GNU Make lab-demo, lab-tests, and autopsy targets passed using the
  installed compiler and SDK directly. Strict compilation reported the
  source's existing seven empty-parameter-list and eleven int-to-char
  conversion warnings. No claim of warning-clean source is made.
- All five release stages contain existing, unique source/entry paths.
  PowerShell archive generation was not run in this macOS session.
- Chapter 4 Markdown structure, top/count trace rows, and whitespace checks
  passed. Inquiry release gates and the three-target Cognitive Pause remain.
- All 25 web tests, TypeScript validation, and the production build passed.
  The web model and activities cover shorter expressions, parentheses,
  sentinel writes, phase resets, operand order, and both demo outputs.
- All seven website content/download mirrors match the authoritative files.
  Local browser checks confirmed English and Korean rendering, `123++ -> 6`,
  `7/2 -> 3`, and safe webpage feedback for `1/(2-2)` while retaining the
  previous trace. The page explicitly distinguishes its validation from the
  unchecked C lab.

Sites version 153 was published successfully at
[the Chapter 4 webpage](https://data-structures.chaebinkim.chatgpt.site/chapter-4)
from web source commit `883328426a9a4817c8ca4c08c01e1fd105dc2492`.
This entry supersedes earlier Chapter 4 representation and fixed-length
claims below; those entries remain as historical records.

## Hash Table / Priority Queue / Binary Heap Reorganization — September 29, 2026

Module 10 now contains the former Hash Table package. Module 11 teaches the
Priority Queue contract, supplied unsorted-array baseline, and Binary Heap
in one chapter and one submission. The full baseline reference is preserved
inside `module_10_binary_heap/priority_queue_baseline`. Module 13 is retired;
Modules 14–16 retain their existing numbers, giving 15 teaching packages.

The teaching order is Week 9 Hash Table, Week 10 Priority Queue/Binary Heap,
and Week 11 Dijkstra with Practical 2. The manuscript indexes, vocabulary
progression, instructor guides, delivery calendar, question banks, and active
pilot materials follow that order. Historical validation and simulated
participant records below and in `textbook_pilot/simulation/` retain the
chapter numbers of the versions they assessed.

The Hash Table solution core and extension suites pass after the move.
The Heap's 9 core and 4 extension groups and the baseline's 10 core and 5
extension groups pass with warning flags, AddressSanitizer, and
UndefinedBehaviorSanitizer. The new textbook caller also runs successfully
against both backends with sanitizers. The student-test templates remain
incomplete until students fill their TODOs.

The Heap opening-baseline archive and five stage archives map to
9 / 3 / 4 / 3 / 3 / 18 entries. The opening and Stage E layouts were recreated
in temporary directories from those mappings, and each passed the supplied
baseline's 10 core tests. No Heap solution, private tests, or instructor files
are mapped into student releases. All 202 checked local Markdown file targets
resolve; 164 course-document links and anchors also pass. PowerShell is not
available on this host, so the packaging scripts themselves were not run.

## Chapter 4 Shared Integer Stack and Sentinel — September 25, 2026

The authoritative `module_04_stack/student/lab.c` now uses global
`int stack[10]` and `size` for both phases. Push uses `stack[size++]`;
peek reads `stack[size - 1]`; pop uses `stack[--size]`. None of these
operations has a full/empty guard. The predicates report state only.
This entry supersedes the guarded character Stack and separate local
value Stack described in the historical records below.

Conversion initializes local `pos`, resets `size`, and pushes a bottom
null sentinel. Both expression loops process exactly seven tokens.
The final drain writes the sentinel to `eq_re[7]`, leaving `pos == 8`
and `size == 0`. Evaluation resets `size` and reuses the global array;
it pops the right operand before the left and returns a final pop.
`1-2*3+4 -> 123*-4+ -> -1` remains the canonical example.

The demo and all six updated C lab test groups pass with AddressSanitizer
and UndefinedBehaviorSanitizer. Tests cover integer LIFO and inactive cells,
full/empty predicates using valid operations, sentinel termination,
precedence/operand order, phase-entry resets and repeated seven-token
conversions, and integer results through 6561. Shorter expressions and
unchecked out-of-bounds calls are excluded from runnable success tests.
The isolated autopsy still produces the expected inactive-cell observation.
Clang reports ten warnings from the unchanged instructional source: six
empty-parameter-list warnings and four implicit int-to-char conversions.
The demo reports infix, postfix, and result; it has no output-count line.

Both textbook editions and their web/download copies now agree. Each edition
retains seven main sections, the existing topic hierarchy, thirteen tables,
and eight C blocks overall. The six implementation/driver blocks in the C Code
section are identical across languages and match the authoritative sources
ignoring whitespace. Their combined program compiles and runs with both
sanitizers and produces the same three-line demo output.

The teaching package, PPT source, worksheets, diagrams, assessments, instructor
notes, release instructions, question banks, and related course references
use the new contract. The direct two-Stack calculation remains the conceptual
motivation; the lab's sequential reuse of one Stack is explicit.

All 24 webpage tests, TypeScript checking, changed-file lint, production build,
and whitespace checks pass. Browser checks cover integer push/peek/pop,
inactive cells, browser-only full/empty button guards, the real sentinel,
final `pos == 8`, shared-array evaluation to -1, rejection of shorter and
zero-divisor input by the webpage, English/Korean switching with retained
anchor, and absence of old identifiers in both rendered editions. Both
editions have no page-width overflow in the checked desktop viewport.
Browser logs report no errors or warnings.

Site version 139, built from source commit
`aa468f24e7ad3c24521fb371017f897c0b509959`, was successfully published at
`https://data-structures.chaebinkim.chatgpt.site` with its existing public
audience. The local Sites helper disappeared after source opening; native
source push, archive save, and deployment completed publication. The accepted
archive includes the matching build and downloadable manuscripts/C source.

## Chapter 4 PPT Alignment and Stack Counts — September 25, 2026

Reviewed the 13-slide source in `module_04_stack/student/ppt_material.md`.
Both textbook editions now introduce a Stack as a list used only at its
end, work through direct two-stack evaluation of `1-2*3+4`, derive the
postfix order, evaluate postfix, and then explain formal conversion.
The direct trace shows both reductions before saving the incoming `+`:
`2 * 3 = 6`, then `1 - 6 = -5`. The final addition gives `-1`.

The current representation uses global `size` for active characters,
`postfix_size` for output tokens, and local `value_size` for active
integers. Character push writes before incrementing; character pop saves
`stack[size - 1]` before decrementing. The integer evaluator's compact
`values[--value_size]` form selects the same last active item. This entry
supersedes the `pos` naming and pop sequencing in the earlier entry below.
Teaching notes, worksheets, diagrams, question banks, and course references
use the same names and behavior.

The six C lab test groups, demo, and autopsy pass with AddressSanitizer and
UndefinedBehaviorSanitizer. The demo reports postfix `123*-4+`,
`postfix_size: 7`, and result `-1`. The six existing empty-parameter-list
warnings remain; the previous shadow warning is gone. Embedded textbook
implementation blocks match the lab and driver.

The webpage adds an eleven-frame direct two-stack activity in both
languages. Its trace test checks valid stack transitions, arithmetic,
operand order, and agreement with the lab's postfix order and result.
Local browser checks verified the two reductions for incoming `+`, the
final `-1`, and the English and Korean activity text.

All 23 webpage tests, TypeScript checking, the final production build,
and whitespace checks pass. The web manuscripts and downloadable editions
match their source textbooks. A final browser check confirmed that the
activity links and lesson headings follow the slide sequence.

Site version 138, built from source commit
`351b05cf96f9cb6808dab56fed03da9b348168c8`, was successfully published at
`https://data-structures.chaebinkim.chatgpt.site` with the existing public
audience. This supersedes the publishing blocker in the earlier entry.

## Chapter 4 Forward-Growing Stack — September 25, 2026

The current lab now uses global `pos` as the next character insertion index
and item count. Empty is zero; full is `pos == capacity`. Push writes before
incrementing, peek reads `stack[pos - 1]`, and pop decrements before reading.
The evaluator retains its separate local `pos` with the same convention.
This representation supersedes the descending `top` convention described
in the historical entries below.

Both textbooks, their webpage/download copies, interactive activities,
diagrams, worksheets, instructor answers, and related course references
now agree on the forward representation. The isolated autopsy uses
`pos == 2`, with correct `stack[pos - 1]` returning `'*'` and faulty
`stack[pos]` returning the inactive marker `'?'`.

The six C lab test groups, demo, and autopsy pass with AddressSanitizer and
UndefinedBehaviorSanitizer. The C blocks extracted from both textbooks are
identical and match the lab plus driver; their combined program produces
`123*-4+`, size 7, and result -1. The compiler reports the six existing
empty-parameter-list warnings and one shadow warning for the intentionally
separate local `pos`.

All 22 webpage tests, TypeScript checking, the production build, and
whitespace checks pass. Local browser checks cover A/B/C pushes, peek,
pop and slot reuse, full/empty boundaries, canonical conversion/evaluation,
and Korean language switching. The activity labels distinguish the next
insertion boundary from the actual top item. Browser logs contain no
errors or warnings during these checks.
The development server reported context-provider warnings during hot
replacement; the subsequent page reloads and interaction checks succeeded.

Publishing was not completed: the Sites publishing scripts became
unavailable after the existing Site was opened. The updated source and
successful production build remain local; this entry does not claim a new
live version. Historical publication records below refer to earlier source.

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


## 2026-10-26 — Linked-list and BFS teaching split

This initial split is superseded by the linked-queue revision below.

- Module 7 is linked-list-only. Current bilingual textbook snippets, tests,
  pool lifecycle traces, assessment, and release follow the existing two-argument
  `new_lnode(data,next)` API. Pool implementation and Module 9 compatibility
  are preserved.
- Module 8 introduces linked/linear/circular FIFO queues, then required tree
  BFS, then the existing maze graph BFS. Queue storage is 25 linear writes
  or 24 circular values. Tree order is F,A,G,B,C,D,E. The maze retains all
  shortest predecessors, distance 8 to the canonical goal, and three routes.
- Both weeks keep 180 contact minutes and one submission. All course maps,
  current question banks, instructor/student supports, and pilot prompts
  use the same sequence. Historical pilot simulations remain historical.
- Module 7 core/student tests, both textbook demos, and extracted release
  passed; core/student checks also passed ASan/UBSan. Module 8 combined
  driver and extracted current release passed ASan/UBSan, including the
  valid-but-unreachable goal experiment. Independent checks covered repeated
  queue wraparound, every valid starting passage, and a fully open interior.
  Module 9 core and student smoke tests passed using the retained pool.
- Repository link audit: 464 local destinations in 84 current Markdown files,
  zero missing targets. Release templates were checked in extracted layouts.
  Existing no-prototype and unused demonstration-variable warnings are
  preserved rather than changing unrelated teaching source.


## 2026-10-26 — Linked-queue revision

Module 7 now includes the linked queue as a linked-list example. Module 8
imports that same implementation for both tree and maze graph BFS. The
linear/circular arrays remain queue-representation comparisons. Both BFS
loops copy each dequeued slot's payload and recycle it before expansion.
Pool-slot indices and stored tree/cell IDs are distinguished throughout.

Verified Module 7 core/student tests with ASan/UBSan, all four bilingual
textbook callers, exact source excerpts, and the extracted student release.
Verified Module 8's driver and regenerated extracted release with ASan/UBSan,
including exact-once IDs, FIFO, live/free disjointness, restored ten-slot
pool, shortest predecessors, unreachable goal, and repeated starts.
Measured pending peaks are tree 3, canonical maze 4, all supplied starts 6,
and all open-interior starts 10. Independent pilot examples exercised both
BFS functions directly. Module 9 core/student tests still pass.

Course scope and both 180-minute budgets agree. All 464 local Markdown
links in 84 current files resolve; question counts and aggregates agree.
Historical pilot simulations remain untouched. Existing C prototype/shadow
and demonstration-variable warnings are retained. PowerShell execution
was not available in this validation.


## 2026-10-26 — Fourteen-module sequence with searching/sorting/consolidation

Module 13 now covers first-match linear/binary search, stable insertion/merge
sorting, and workload-selection consolidation. Module 14 contains the moved
Prim/Kruskal package and Week 14 DSU/Kruskal scaffold. Current course maps,
style/dependency rules, guides, question banks, and pilot sequence agree.
The current 14-week delivery guide replaces the former 13-week path. There
are twelve weekly artifacts and two practicals, one submission per week.

Module 13: sanitizer core/student/demo and extracted release pass with no
compiler warnings under -Werror; exact source excerpts, first-duplicate and
missing-key behavior, n0..64, signed extremes, permutation/oracle checks,
canaries, tagged stability reasoning, source/manifest fidelity, links, and
overwrite protection verified. Independent review found no contract or cost
issues. Integer-only output is explicitly not treated as proof of stability.

Module 14: algorithms and three student TODO boundaries preserved during
renumbering. Reference core/extension and bounded/reference sanitizer tests
pass. Extracted original starters compile; a temporary reference-completed
copy passes DSU/MST tests. Student-authored TODO test templates remain
unfinished. PowerShell was inventory-checked rather than executed.

Final current-file audit: 521 local links across 114 Markdown files,
zero missing destinations; calendar and both indexes enumerate 1–14. Each
new/final module fits 180 minutes and one artifact. Historical pilot
simulations and earlier validation entries remain historical.


## 2026-10-26 — Value API and dependent consumer synchronization

Preserved the latest user Module 7 implementation: Linked_Node and
init_lnodes_pool; raw node helpers versus public Boolean enqueue(value)
and value-returning dequeue() with automatic recycling. Empty public
dequeue remains outside contract, and -1 remains a valid payload. Tests
cover exhaustion without mutation, FIFO, internal recycling, raw empty -1,
repeated reuse, and public payload -1. Enqueue effects occur outside assert.

Updated Module 8 BFS callers, distinct linear-array names, Module 9 type/
initializer references, canonical snippets, teaching materials, questions,
and pilot examples. Import guards live in consumers rather than the user's
source. Verified Module 7/8/9 sanitizer checks and extracted releases;
Module 7 callers/release also pass -Werror. NDEBUG valid-caller checks pass.
Combined tree/hash/maze execution passes in both include orders and both
assertion modes. All three released Module 7 copies match current source.
Final link audit: 672 destinations across 155 current files, none
missing. Existing unrelated compiler warnings remain; PowerShell unexecuted.
