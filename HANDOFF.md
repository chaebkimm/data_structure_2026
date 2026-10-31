# Course materials and textbook website handoff

Updated: 2026-10-30.

## Six textbook review repairs — 2026-10-30

Chapter 5's canonical lab now includes the documented temporary `capacity`
rename when importing the Stack lab. It matches the existing website download.
Lecture and all seven lab tests pass normally and under ASan/UBSan, including
the assembled standalone Stage E release layout.

The active beginner pilot now has a participant check-question sheet with
four required questions per chapter, one transfer exercise per chapter, and
matching facilitator criteria. Its 56 check pairs, 14 transfer pairs, and
43 prerequisite/stage pairs follow the current fixed ArrayList, indexed
trees, undirected BCC, raw linked-node pool, Module 8 value adapters,
integer/schedule Heaps, indexed Dijkstra, character AVL, and required Week 14
DSU/Kruskal lesson. New concepts are checked after their introduction.
README and response/log templates use the same four-question protocol.
Historical simulations and actual-pilot status are unchanged; no beginner
responses were collected.

Chapter 9 now explains automatic first-use pool initialization and later
no-ops. Both Chapter 10 editions include the exact current lab plus the
ordinary value-update explanation. Chapter 0 counts work before notation,
separates time and storage, and distinguishes input cases; Chapter 2 defines
depth/height and `O(h + 1)` call storage. The retained Chapter 14 reference's
exchange proof handles equal weights without claiming a lower total cost.

Local website Chapter 0/2 content and glossary are synchronized. Its 75 tests,
TypeScript check, and production build pass. Browser checks cover both
languages' corrected explanations. Transfer fixture results were checked
against the actual sources; all 89 active-pilot local links resolve.
Changes remain local in the course and separate website checkouts; no
commit, push, or deployment was performed. PowerShell release wrappers
received static inspection because PowerShell is unavailable.

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

## Module 7 revised-slide alignment — 2026-10-27

The updated `module_07_linked_list/student/ppt_material.md` now drives the
lesson: acyclic chains and a saved first index, safe predecessor rewiring,
shared-pool benefits and costs, recycling hazards, linked Stack, and linked
Queue. Both textbooks, student activities, instructor guidance, models,
assessment, current question banks, pilot prompts, and course maps follow
that sequence. The Stack is caller-side use of existing node primitives;
no Stack API was added to `student/lab.c`. The lesson still has one artifact,
three original test groups, 180 contact minutes, and the 100-point rubric.

The concept slides and supplied C source are unchanged. The lab-slide file
deleted in the slide update remains deleted; current source and packaged
entry points now link to the lab instead. Raw queue append explicitly
requires `next == -1`; pool resets require that no active or detached
allocation remains owned. Module 8 continues to import the existing queue.

Verification covers 41 current Markdown sources and 287 resolving local
links. Both textbooks retain the five-section structure, exact full lab
code, and three identical caller programs across languages. Those programs
pass normal, `NDEBUG`, and sanitizer builds. Core/student suites pass normal
and AddressSanitizer/UndefinedBehaviorSanitizer builds. A fresh 24-entry
student archive has exact canonical bytes, the exact inventory/manifest,
36 resolving local links, a passing standalone build, and overwrite refusal.
Weekly/consolidated Week 7 banks agree on 42 prompts and 36 vocabulary
entries. Technical checks do not replace a beginner reading pilot.

Lab SHA256: `99145b95e45840ee519019c9c788313740f20516489a6e87cd297a0e6b8b6739`.
Slides SHA256: `1bf745bcaccf606b6de4a6a2554b183187475026a12beaceb619b10360548d5c`.
These edits remain local; no course site was published.

## Module 11 current-lab alignment — 2026-10-25

Week 11 now follows the unchanged `module_11_graph_dijkstra/student/lab.c`:
ten-node adjacency lists from Module 3, a separate positive `int` weight
matrix, `-1` distances, and an indexed minimum Heap of node IDs. Improvements
repair a queued node through its live inverse position. Student materials,
models, instructor guides, question banks, course maps, and release tooling
match the actual source. Required work is one focused original regression,
state traces, and a supplied BFS/linear-selection/Heap comparison in the sole
180-minute Practical 2 artifact. The older lazy-duplicate API is optional.

Current targets are `lab-compile`, `core`, `student-tests`, and `comparison`.
Core checks cover live-map/order invariants, both repair directions, ties,
singletons, capacity, repeated runs, disconnected/nonzero sources, and 80
positive-weight graphs against an independent repeated-relaxation oracle.
The supplied comparison separately implements BFS and linear-minimum-selection
Dijkstra. Exact-source compiler instrumentation verified the canonical
`[0,5,2,4,6,-1]` result, heap states, A,C,D,B,E order, five adds/removals,
two updates, eight adjacency inspections, and peak pending size three.
Normal and AddressSanitizer/UndefinedBehaviorSanitizer runs pass, including
an independently extracted archive. Retained optional library core,
extension, and unsigned autopsy checks also pass. The supplied old-style
prototypes and Module 3 label conversion still produce six warnings.

`release/prepare_student_release.py` creates the standalone
`dist/module_11_graph_dijkstra.zip` with 28 entries, including the exact
Module 3 dependency and three current-source drivers. Inventory, source bytes,
manifest hashes, deterministic regeneration, overwrite refusal, and
32 packaged local links pass. The source-document audit checks 224 resolving
links across 34 current documents; standard/linear worksheets have 31 matching
prompts, the pause has three targets, and the rubric totals 100 points.
PowerShell scripts received static inspection; PowerShell is unavailable here.
The lab SHA256 remains
`85884ccd5a99fb827e177d10cd608670b650c7544399f33f735e41a08f623703`.
The archive SHA256 is
`506bc2340e3156e3364048443b89d08817f0c63c4d12d51d0e77e81ca742d275`.
Earlier uncommitted repository work is preserved. This entry supersedes the
older required-lazy-frontier and path-scaffold descriptions below.

## Module 10 current-lab alignment — 2026-10-25

Week 10 now follows `module_10_binary_heap/student/lab.c`: a ten-integer
min/max Heap, bottom-up construction, and ten-device common-on-time search
with max-on/min-off ID Heaps, epochs, comparator/swap callbacks, and inverse
position maps. The English and Korean textbooks, workbook, concept/lab slide
outlines, student support, diagrams, instructor keys/plans, assessment,
question banks, and current course maps match this source. One submission
contains an assertion driver, three original test groups, and trace evidence.
The alert-record Heap and linear baseline remain optional references.
Dijkstra guidance now distinguishes the ten-value lab, optional 64-record
alert library, and its own 241-entry frontier; stable frontier ties belong
to the supplied Dijkstra support rather than this integer lab.

The default module build tests the supplied lab. Run
`make -C module_10_binary_heap/code lab-compile core student-tests`.
Seven core groups include 1,000 deterministic interval-oracle cases,
min/max operations, mode rebuild, missing-child/singleton cases, both
indexed repair directions and map invariants, closed endpoints including
`[5,5]`, repeated calls, and exhaustion through all five intervals.
Normal and AddressSanitizer/UndefinedBehaviorSanitizer builds pass.
Optional scan-baseline core and Heap core/extension/autopsy checks pass.
The unchanged lab retains six inherited no-prototype warnings.

`release/prepare_student_release.py` creates one standalone archive,
`dist/module_10_binary_heap.zip`, with 25 entries. The PowerShell entry
point delegates to it; A–E readmes are optional classroom checkpoints.
Byte equality, exact inventory, deterministic regeneration, overwrite
refusal, 59 packaged local links, and extracted standalone compile/core/
student runs pass. Source/document QA checks 58 current documents and
301 resolving local links; both textbook C blocks exactly match the lab.
PowerShell is unavailable, so its wrappers received static inspection only.
The lab SHA256 remains
`2d2885728d2825fa749a8669f4ea3dca74fd29821b7b93dbe9a59b3907e5791a`.
The archive SHA256 is
`d343f9cbbd139a4cfd9855704d8633c996757e77a65296b0ac1700af4f223f72`.
These local changes preserve the earlier uncommitted repository work.

## Module 09 current-lab alignment — 2026-10-24

Week 9 now follows `module_09_hash_table/student/lab.c`: ten bucket heads,
Module 07's ten-node pool, separate chaining, and two sum. Textbook, activities,
instructor answers, rubric, questions, course maps, and active pilot prompts
match the actual source. Required work is one assertion driver and evidence,
with three original groups: hashing/chains, pool lifecycle, and two sum.
The two supplied lab sources are unchanged; the old open-addressed library
and deletion demo remain optional.

The default module build runs current-source tests. Use
`make -C module_09_hash_table/code lab-compile core student-tests`.
Normal and sanitizer tests pass, including an 81-target oracle and repeated
calls. Clang still reports the supplied sources' old-style declarations and
shadowed names. The retained optional map core/extension suites also pass.

`release/prepare_student_release.py` creates five A–E ZIPs with 3/4/3/3/12
entries; the PowerShell entry point calls it. The Stage E layout includes
sibling Module 09 and Module 07 directories so the exact include works.
Reproducibility, byte equality, overwrite refusal, and an independent extracted
build were verified in temporary directories. Stage C is hand prediction;
source inspection/execution begins in Stage E. The former strict 38-file
inventory and older Stage E contents below are superseded by this entry.

## Consecutive module numbering — 2026-10-24

The thirteen teaching packages and chapters now run consecutively from
1 to 13. Binary Heap is `module_10_binary_heap/`, Dijkstra is
`module_11_graph_dijkstra/`, BST/AVL is `module_12_bst_avl/`, and
Prim/Kruskal is `module_13_prim_kruskal/`. Their instructor guides are
`chapter_10.md` through `chapter_13.md`. Course maps, vocabulary boundaries,
question banks, staged release names, test output labels, and active pilot
templates use this numbering.

Existing core and extension suites pass for Heap, its supplied linear
baseline, Dijkstra, AVL, and MST. The Week 13 reference tests and starter
build pass using the renamed repository dependencies. Checks of 289 local
document links and all 26 staged/opening release maps pass. Test builds
used temporary directories, preserving existing repository build artifacts.

This entry supersedes earlier numbering and retired-number claims below.
Dated historical narratives retain their original module numbers;
actionable package paths use the current directory names. Historical
simulation responses preserve their assessed editions.

## Hash Table renumbered to Module 9 — 2026-10-24

Renamed `module_10_hash_table/` to `module_09_hash_table/` and the teaching
guide to `instructor_guide/chapter_09.md`. Hash Table is now Module/Chapter 9
in Week 9. Course indexes, curriculum references, vocabulary boundaries,
question banks, and staged release filenames follow the new numbering.
There are thirteen teaching packages: 1–9, 11–12, and 15–16; numbers 10,
13, and 14 are unused. Earlier dated entries retain their historical numbering.

The existing Hash Table core and extension suites pass from the new
directory. The C implementation and public API are unchanged. All 199 local
links checked in changed or moved documents resolve, and the strict 38-file
source inventory and five staged release maps pass static validation.

## Module 7 directory consolidation — 2026-10-24

Removed the redundant `module_07_linked_list/week_07/` subtree. The current
lab and rubric are `student/lab.md` and `student/rubric.md`; the 180-minute
plan is `instructor/lesson_plan.md`. The unique test harness now lives in
`code/tests/test_lab_core.c`, `test_lab_student.c`, and `lab_test_support.h`.
Run `make -C module_07_linked_list/code core student-tests` from the repository
root. The default module build also runs these current-lab tests.

The packager is `release/prepare_student_release.py`, producing the module's
`dist/module_07_linked_list.zip`. It packages the canonical `student/` and
`code/` layout. Course and release references use these paths. The actual
`student/lab.c`, optional library, and DSU paths used by Module 16 are
preserved. Earlier entries below describe the superseded weekly layout.

Current core/student tests, sanitizer builds, and the optional library core
pass. The extracted 25-entry release builds and passes, matches all 24 mapped
source files, has an exact manifest and 42 resolving local document links,
and refuses overwrite without changing the archive. PowerShell is unavailable;
its wrappers were reviewed statically. These changes remain local.

## Module 8 Graph BFS replacement — 2026-10-24

Removed the standalone Tree BFS package and renamed `module_09_graph_bfs/`
to `module_08_graph_bfs/`. Graph DFS remains Module 6. The Graph BFS teaching
guide is now `instructor_guide/chapter_08.md`; its former Chapter 9 path is
retired. There are thirteen teaching packages: 1–8, 10–12, and 15–16.

Week 8 retrieves Week 7's FIFO rule directly and teaches graph discovery,
minimum-hop distance, predecessors, and path reconstruction in one 180-minute
unit with one submission. The former required tree bridge is removed.
Course maps, vocabulary boundaries, question banks, dependent-module
references, and staged release names follow the new numbering. Historical
pilot records retain their original chapter identities and identify retired
editions explicitly. Current verification is recorded in `TEXTBOOK_VALIDATION.md`.

## Module 7 lab synchronization — 2026-10-23 (directory layout superseded)

The current required source is `module_07_linked_list/student/lab.c`, unchanged
in this revision. It uses `nodes[10]` with integer `data`/`next`, `-1` as the
ending marker, and a free chain. Allocation removes a free slot; list
removal detaches a successor; recycling is a separate caller action.
Linked FIFO uses `head`/`tail`. The linear array queue initially fits ten
values, while the circular convention reserves one slot and fits nine.
Queue array mutations are unchecked and require matching caller predicates.
The older `LinkedList`/DSU code under `module_07_linked_list/code/` remains
an optional, distinct library. DSU is still introduced in Week 13.

Current reading starts at `module_07_linked_list/student/textbook.md` or
`textbook_korean.md`. Both follow the five-section textbook style and
reproduce the full current lab code in order. The same student directory
contains a bilingual `class_material.md`, `ppt_material.md`, and
`ppt_lab_material.md`, plus updated inquiry, pause, investigation, evidence,
rubric, vocabulary, and index-link autopsy materials. Weekly entry points,
instructor guides, diagrams, course maps, and Week 7 question banks use
this scope. Week 8 reuses FIFO for BFS rather than introducing it.

Week 7 now asks for traces, guarded callers, and three original safe test
groups; the supplied code has no implementation TODO or `main`. The five
core test cases and student smoke driver include the actual lab. The
canonical rubric totals 100: pool20, list20, linked FIFO20, arrays25,
tests/cost/revision15. The contact plan remains 180 minutes.

`week_07/prepare_release.py` preserves the `student/` and `week_07/` layout
in a self-contained 16-entry archive. It includes the unchanged lab,
bilingual textbook, workbook, both slide manuscripts, lab/rubric and tests.
`release/prepare_student_release.ps1` delegates to it; the historic five
combined List/DSU ZIPs are superseded. Stage readmes are now facilitation
checkpoints, not additional release products. Release Make/PowerShell
helpers target the current weekly tests.

Verification: normal and AddressSanitizer/UndefinedBehaviorSanitizer runs
pass all five core groups and the smoke test. An independently extracted
archive also builds and passes; manifest, exact source/document bytes,
relative links, exclusion of faculty/legacy code, and overwrite refusal
were checked. Both textbook C sections match the lab exactly; 52 changed
or directly related Markdown files contain 271 resolving local links.
The source retains nine Clang non-prototype warnings; no source was altered
to suppress them. PowerShell is unavailable, so its wrappers received
static inspection only. Technical/editorial checks do not replace a human
beginner reading pilot.

For this Mac, use real CLT binaries and an explicit SDK if the system
shims report an Xcode license problem:

```sh
/Library/Developer/CommandLineTools/usr/bin/make -C module_07_linked_list/week_07/code core student-tests CC=/Library/Developer/CommandLineTools/usr/bin/clang CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk'
```

For sanitizers choose a separate `BUILD_DIR` and add
`-fsanitize=address,undefined -fno-omit-frame-pointer` to those flags.
Use the bundled Python/Git paths documented below when their system shims
fail. Lab SHA256:
`46985a83c37e60471324a7afbb73aa8e279f4861cb7a08905341c4f6d0f1d6ac`.
These changes are local and uncommitted. No website was changed or published;
the existing web implementation currently covers Chapters 0–6 only.

## Historical Module 7 replacement — 2026-10-23 (superseded by the lab synchronization above)

The user requested deleting the Queue package, renumbering the former Module 14
linked-list package as Module 7, fixing both review findings, and verification.
The current package is `module_07_linked_list/`. The old `module_07_queue/` and
`module_14_linked_list_dsu/` directories are removed. Chapters 13 and 14 are
retired; Chapters 15 and 16 retain their numbers. There are fourteen teaching
packages across thirteen instructional weeks.

Week 7 now uses `module_07_linked_list/week_07/README.md` and one linked-list
artifact: front insertion, first-match deletion, destruction, ownership traces,
and failure tests. The original combined List/DSU resources remain in this
renamed package as optional faculty material. DSU is first taught and assessed
with Kruskal in Week 13, whose reference build points to the renamed package.
FIFO is introduced with the supplied Tree BFS Queue in Week 8, followed by
Graph BFS. No replacement Queue implementation is assigned.

The legacy Module 16 release inventory excludes its separate `week_13/` subtree
and still validates the original 47-file package. The Tree BFS README describes
its actual borrowed node-pointer/depth records; Graph BFS stores vertex IDs.
The Week 13 DSU header also includes the full caller-output and API contracts.
The course maps, vocabulary boundaries, teaching guides, question banks, and
release names follow the new package numbering. Earlier entries below describe
previous editions and may cite their historical paths or assignment scope.

Reproduce the current bounded releases and core checks from the repository root:

```sh
python module_07_linked_list/week_07/prepare_release.py
python module_13_prim_kruskal/week_13/prepare_release.py
make -C module_07_linked_list/week_07/code solution-core starter-compile
make -C module_13_prim_kruskal/week_13/code solution-core starter-compile
```

The archives are `dist/week_07_linked_list.zip` and
`dist/week_13_dsu_kruskal.zip` inside their respective weekly directories.
The linked-list packager refuses overwrite; use its `--output PATH` option
for repeat checks. Both extracted releases pass strict C11/sanitizer checks
when only their three advertised TODO bodies are completed. Tree/Graph BFS
core checks, original package inventory/maps, all 581 local links and nine
anchors, calendar budgets, and question-bank totals also pass. PowerShell
itself is unavailable; its release maps/inventory were verified statically.

Verification results are recorded in `TEXTBOOK_VALIDATION.md`. These changes
are local and uncommitted; this request does not publish the separate website.

## Historical repository handoff — 2026-10-23 (superseded by the Module 7 replacement above)

The user explicitly requested saving the completed curriculum work to this
handoff, committing all changes, and pushing the course repository to GitHub.
This supersedes the earlier local-only instruction for this course-repository
update. Target: `main` at `https://github.com/chaebkimm/data_structure_2026.git`.
The separate website repository and Sites deployment are outside this request.

### Materials and decisions to preserve

Weeks 1–6 are complete. The accepted upcoming sequence is:

| Week | Required focus |
|---:|---|
| 7 | Linked lists through a linked Queue; supplied circular-array comparison |
| 8 | Tree-to-graph BFS, distances, predecessors, and path reconstruction |
| 9 | Hash tables with probing, tombstones, and scaffolded resizing |
| 10 | Priority Queue contract and Binary Heap |
| 11 | Dijkstra, assessed through Practical 2 only |
| 12 | Combined BST-to-AVL; deletion remains optional |
| 13 | Introduce Union-Find, then apply it immediately in Kruskal; Prim demonstration |

Each week retains the 180-minute limit and one programming submission.
There are eleven lab artifacts and two practicals. Capstone integration is
incremental and folds into Week 13; the defense uses the separate final period.
Original module numbers remain unchanged. Full package labs omitted from the
weekly path remain optional resources, not additional required homework.

The current schedule and entry points are `COURSE_MANUSCRIPT.md`,
`Data_Structures_Course_2026_13_Week_Delivery_Guide.md`, and
`Data_Structures_Course_2026_Spiral_Curriculum.md`. The old 14-week guide and
renamed question-bank pages retain compatibility pointers. Instructor plans,
student scope notices, assessment counts, capstone milestones, weekly vocabulary,
and consolidated question banks have been reconciled with the new calendar.

Week 7 has a new lesson, lab/rubric, instructor plan, linked-Queue starter,
faculty reference, supplied lifecycle helpers, and core/student tests.
Students implement enqueue and dequeue; destruction is supplied and explained.
Week 8 explicitly supplies its circular-array BFS Queue backend, preserving
the FIFO contract without requiring another Queue implementation.

Week 13 has a new combined lesson, lab/rubric, instructor plan, bounded DSU
starter and tests, and a build that combines DSU with the existing Kruskal
starter. Exactly three TODOs are required: find, union by size, and Kruskal
edge selection. Make-set, graph loading, sorting, checked totals, validation,
and complete Prim are supplied. A C11 array-qualifier mismatch in the shared
MST validator was corrected so warnings-as-errors builds pass.

### Reproducing student releases and checks

From the repository root:

```sh
python module_07_queue/week_07/prepare_release.py
python module_13_prim_kruskal/week_13/prepare_release.py
make -C module_07_queue/week_07/code solution-core starter-compile
make -C module_13_prim_kruskal/week_13/code solution-core starter-compile
make -C module_12_bst_avl/code solution-core
```

The release scripts generate `dist/week_07_linked_queue.zip` and
`dist/week_13_dsu_kruskal.zip` inside their respective weekly directories.
Archives and build outputs follow the repository's existing ignore rules;
tracked sources and scripts reproduce them. Student archives exclude faculty
solutions; complete Prim is intentionally included as supplied comparison code.
Unfinished starters compile but are expected to fail behavioral tests.

Both releases were extracted into independent temporary directories and
checked without repository-relative dependencies. Replacing only the advertised
TODO source files with faculty references made both release suites pass with
C11 warnings as errors and AddressSanitizer/UndefinedBehaviorSanitizer.
Existing AVL core tests also passed. The calendar, minute-budget, local-link,
anchor, and whitespace results are recorded below. No tests need rerunning
solely for this handoff update.

Website content remains at its previously published state described below;
the new curriculum has not been published to Sites. No pending curriculum
implementation work remains from this request.

## Historical curriculum revision — local repository, 2026-10-22

The current course has 13 instructional weeks. The authoritative schedule is
[the 13-week delivery guide](Data_Structures_Course_2026_13_Week_Delivery_Guide.md).
Week 7 combines linked lists and Queue, Week 12 combines BST and AVL,
and Week 13 introduces DSU immediately before Kruskal. Prim is a supplied
demonstration; capstone defense remains in the separate final period.

New required lessons, labs, reference/starter code, tests, and release scripts
are in `module_07_queue/week_07/` and `module_13_prim_kruskal/week_13/`.
Existing full packages remain optional resources. The course map, instructor
entry points, question banks, and assignment boundaries follow this revision.
No website source or publication was changed by this curriculum update.

Validation: both new student releases were generated and extracted independently.
Untouched starters compile and fail the intended behavioral tests; completing
only the advertised TODO files passes the supplied suites. Linked Queue and
the combined DSU/MST reference pass C11 warnings-as-errors and ASan/UBSan.
The existing AVL core suite passes. Both calendars contain Weeks 1–13 exactly
once; new weekly budgets total 180 minutes. All 315 local links and six heading
anchors in changed/new Markdown resolve; whitespace checks pass.


## Current state

Chapter 6 is the default homepage at https://data-structures.chaebinkim.chatgpt.site/ and https://data-structures.chaebinkim.chatgpt.site/en. `/ko` also opens Chapter 6. Explicit `/chapter-6`, `/en/chapter-6`, and `/ko/chapter-6` URLs remain available. Chapter 5 now uses `/chapter-5` and `/en/chapter-5` in navigation and language switches. Explicit Chapter 0–6 routes remain available; canonical URLs and language alternates follow the new homepage mapping.

- Sites project: `appgprj_6a955240a2d0819191a05a6f72a08e8f`; audience remains public.
- Published version: 199.
- Published and local website source commit: `0772f4c2b8b9e0ff8948d546e7f3c8eb333ba66c`.
- Historical website instruction: keep separate website GitHub commits local unless requested. On 2026-10-23 the user explicitly authorized committing and pushing the course-repository curriculum update; see the repository handoff above.
- Deployment: `appgdep_6ad4b64b177c819194d532a81966a5bf`, succeeded.
- Website checkout: `/Users/cbk/Documents/GitHub/data_structure_2026/student-textbook-web` (its own Git repository). Its working tree was clean when this note was saved.
- Local preview servers started for verification have been stopped.

## Chapter 6

### Revised lab-slide synchronization — 2026-10-18

Reviewed the latest supplied `student/lab.c`, `ppt_material.md`, and
`ppt_lab_material.md`. The executable lab and conceptual slides are
unchanged; the lab slides now introduce preorder → neighbor loop →
postorder, separate `init_visit()` preparation from edge recording, and
explain why the boundary pop yields one BCC. Both textbooks, the class
workbook, module overview, and instructor materials follow that sequence.
The compact proof distinguishes an ancestor visited before the parent
from the parent itself, preserving the equality case and inclusive pop.

Website content and all source downloads match the current teaching
files, including the revised lab slides. All eleven ZIP entries match
their standalone files. The new textbook link opens the downloadable lab
slides. Version 199 also publishes the previously local postorder revision
described below, with the incoming edge, older prefix, and pending suffix
visible in the stack player.

All 61 website tests, TypeScript, and the production build pass. Nine C lab
checks and both supplied drivers pass under AddressSanitizer and
UndefinedBehaviorSanitizer, with documented output and empty final stacks.
All 65 local links in the eight changed teaching documents resolve;
fences and whitespace checks pass. Independent review found no substantive
correctness issue. Desktop/mobile browser checks confirm bilingual content,
the slide link, postorder/root states, no document overflow, and stable
player/following-content positions. The live English page and postorder
panel were inspected after the successful version 199 deployment.

Proof: `student-textbook-web/outputs/chapter-6-oct18-sync.jpg` and
`student-textbook-web/outputs/chapter-6-oct18-postorder.jpg`.
GitHub commits remain local; the separate Sites source was pushed to
publish the requested webpage update.

### Postorder parent-edge invariant — 2026-10-17 (published in version 199)

The textbooks and course notes now state the stronger BCC invariant at the
end of a non-root call, before it returns and before its parent's decision.
All edges handled in the finished branch are assigned or pending. The
pending suffix from the incoming parent edge through the top contains only
edges in the same eventual BCC as that edge. Older entries below it can
belong to other BCCs; the suffix need not be the whole eventual block.
The root has no incoming edge and finishes with an empty edge stack.

Visit 4's postorder has older prefix `1–2, 2–3, 1–3` and suffix
`3–4, 4–5, 5–6, 3–6, 4–6`. Its parent then closes that suffix.
Visit 3's postorder has prefix `1–2` and suffix `2–3, 1–3, 3–7, 2–7`;
all five share a BCC, illustrating that the suffix can be partial.

`postorderStack()` splits only return snapshots. The stack player shows
the incoming edge, older prefix, and branch suffix at that checkpoint;
return captions explicitly precede the parent's keep/close test. Both
manuscripts, the workbook, downloads, and eleven ZIP members are in sync.
All 61 website tests, TypeScript, production build, 47 local Markdown
links, and whitespace checks pass. Browser QA confirms visit 4/3/root
snapshots, bilingual desktop/mobile layout, no main-content lists/tables,
no overflow, and stable panel/following-content positions. An additional
read-only model check covered all 1,098 simple graphs on 2–5 vertices and
3,651 non-root postorder frames without a violation.

This follow-up was initially kept local in website commit `23f7c4f`.
It is now included in version 199. GitHub pushes remain stopped at the
user's request. Original local proof:
`student-textbook-web/outputs/chapter-6-postorder-local.jpg`.

### Edge-stack invariant — 2026-10-17

The Chapter 6 stack topic now contains an explicit invariant subsection in
both languages: after a push or complete pop-and-store step, each handled
edge appears exactly once, either pending or assigned. Assigned edges
include a forming result row. Initialization, maintenance, and termination
use the same slide graph. The explanation distinguishes accounting from
the low-link boundary rule, the unassigned branch suffix from nested blocks
already emitted, and the edge stack from the recursive call stack. The C
subsection explains the temporary local edge, `pos`, early `current_bcc`
increment, and delayed `bcc_size` publication.

The class workbook and teaching guides include matching prompts and
checkpoints. The website's existing stack playback shows a live invariant
panel: 0=0+0 initially, 8=7+1 during the first pop, and 10=0+10 at completion.
`edgeStackInvariant()` derives handled identities independently from prefix
push events and validates exact-once membership. Its tests reject missing,
duplicate, replaced, and future edges. The partial row counts as assigned.
The same five sections and 7/3/10 topic layout remain.

All 59 website tests, TypeScript, and production build pass; 47 local links
in the invariant materials resolve. The bilingual manuscripts, downloads,
workbook, and eleven ZIP entries match. Desktop/mobile checks confirm the
partial-row equation, completion/reset, no overflow or main-content
lists/tables, and stable panel/following-content positions. An independent
read-only review found no correctness issues. Published version 198.
Proof: `student-textbook-web/outputs/chapter-6-invariant.jpg`.

### Updated lab/PPT synchronization — 2026-10-17

Both textbook editions, the bilingual class workbook, instructor guides,
representation notes, and Stage D descriptions now match the updated
`student/lab.c` and `student/ppt_lab_material.md`. The input lab and slide
files are preserved. The source has `edges[45]`, `bcc[9][45]`, and
`bcc_size[9]`; the integer stack still has ten entries. The textbooks
explain the 45-pair/nine-block bounds, separate stack limit, and the review
slide's `back` abbreviation versus the source's `back_num` name.

After `_find_bcc(adj)` returns, the parent compares `back_num[adj]` with
`visit_num[node]`. Strictly smaller values keep edges pending and `continue`
the neighbor loop. Otherwise `close_bcc(tree_edge)` pops through the
boundary inclusively. Root children use this same parent-side check.
The website extraction frames, captions, active vertex, and call path now
show that exact timing. Every child return has its own frame before its
parent's decision. Extraction/storage playback has 40 states and the
pipeline 103. The first traversal/low-link/recording counts remain
20/26/36. Block colors, per-edge pops, first-entry numbering, and the
original A–J and slide outputs are preserved.

All website manuscripts/downloads, the workbook, lab/PPT sources and
dependencies are synchronized. The eleven-file `sources.zip` was rebuilt
and every entry checked against its standalone download. Both extracted
drivers compile and run under AddressSanitizer/UndefinedBehaviorSanitizer.
The nine new array-lab checks in `code/tests/test_lab.c` pass normally and
under both sanitizers. `make lab-tests` runs them; plain `make` now runs
`lecture`. Legacy matrix targets remain explicitly available.

All 57 website tests, TypeScript, and production build pass. Browser QA
covers parent-side extraction, active root highlighting during the second
block, completed blocks, reset/completion, no main-content tables/lists,
English/Korean mobile overflow, and stable panel/following-content positions
once all-state measurement completes. Desktop and mobile verification used
1440/390-pixel viewports; the override was reset afterward. Version 197
was published successfully and inspected. Proof:
`student-textbook-web/outputs/chapter-6-updated-lab.jpg`.

### Earlier Chapter 6 website refinements

Each back-edge encounter has its own step, including encounters that do not
lower the current low-link value. `traversalFrames()` shares the frame selection
between traversal, recording, and pipeline players. The first traversal has
20 states, low-link playback 26, classification/recording remain 36, and the
pipeline has 97. Every pass separately exposes 3→1, 6→3, 6→4, and 7→2.
Inspection precedes a separate value-update frame when needed; 6→4 explicitly
keeps low 3. All encounters highlight one edge and its canonical endpoint roles.

Twenty-four targeted model/content tests, TypeScript, and production build
pass. Browser checks confirm distinct 6→3/6→4 steps, unchanged-low narration,
pipeline parity, bilingual/mobile layouts, stable following content, correct
completion, and reset without future edges/numbers. Version 196 was published
and inspected. Proof: `student-textbook-web/outputs/chapter-6-back-edge-steps.jpg`.

Graph DFS animations distinguish straight solid tree arrows (parent to child)
from straight dashed back arrows (descendant to ancestor). Focused connections
label both endpoint roles beside their circles. Arrow orientation follows the
recorded DFS relationship even on a reverse neighbor scan or endpoint query;
arrows describe relationships in the undirected graph. Accessible descriptions
bind roles to actual visit numbers, keeping the child unnumbered before entry.

`graphEdgesAt()` reveals only the selected traversal prefix or extraction's
pending/found records; `focusedEdgeAt()` identifies scans, low-link updates,
pushes, latest pops, and incoming tree edges on pending returns. Completed
block colors apply to both paths and arrowheads. Badges avoid focused shafts
and arrowheads. Twenty-three targeted model/content tests, TypeScript, and the
production build pass. Browser checks cover reversed parent/descendant scans,
the six tree/four back result, blank child numbering, both languages, mobile
and desktop overflow, stable measured sizing, and retained found-block colors.
Published proof: `student-textbook-web/outputs/chapter-6-edge-roles.jpg`.

Version 195 straightens back-edge paths and the legend. Arrows, role labels,
and found-block colors are preserved. Low-link values at visits 1, 2, and 4
sit beside their circles to clear the vertical and incoming arrows. TypeScript,
production build, and desktop/mobile browser checks pass. The live result was
inspected; proof: `student-textbook-web/outputs/chapter-6-straight-back-edges.jpg`.

Found blocks remain visible in stable, distinct colors throughout extraction.
The first completed block is green and the second blue; forming edges retain
the active color until their boundary pop completes the block. Completed
color takes precedence over current-edge highlighting and stays fully opaque
through later branches and the final frame. Text legends and card borders
match those colors. This applies to Stack, block overview, pipeline, and
storage playback. The shared vertex remains neutral/active. The explicit
vertex-removal demonstration still represents the removed vertex accurately.

`completedBlocks()` excludes only the partial last group of a close frame;
rewind/reset recomputes colors from the selected snapshot. Twenty targeted
model/content tests, TypeScript, and production build pass. Browser checks
confirm the first five green edges persist after the next push and partial
second closure, all ten remain green/blue at completion, reset clears future
colors, related players match, and panel/following-content sizing remains
stable with no mobile overflow. Published proof:
`student-textbook-web/outputs/chapter-6-found-block-colors.jpg`.

Use animations throughout the Chapter 6 webpage instead of static example
tables or walkthrough lists. All seven Thinking topics and three Efficiency
topics have playback. Glossary definitions, coding-plan/review steps, C
storage mappings, and text-output examples advance one item at a time;
actual C/shell source excerpts remain readable. The published page has zero
HTML tables or lists in its main content. Printable manuscripts/downloads
retain their reference examples.

Low-links appear near reached graph circles. Stack extraction uses live
visit-number snapshots and moves one edge per frame into a forming block.
Blocks replay the same pop sequence, then show removing visit 3. The workflow
replays preparation, recording, low-link calculation, and extraction.
Efficiency panels animate three-pass counts (21 entries/60 inspections),
49 lookup cells then 20 scans, and current/peak call and pending-edge use
(peaks 6/8). Lookup representations focus on one neighbor entry, one
browsable recorded edge, or two symmetric matrix cells.

Shared UI lives in `chapter-six-animation-ui.tsx`; all-state measurements
reserve the real maximum at the current panel width/language. Efficiency
figures use container width for side-by-side layout so labels remain legible
inside narrow desktop columns. `chapter-six-efficiency.tsx` implements cost
playback, and `chapter-six-step-cards.tsx` implements 4-second prose playback.
All 51 website tests, TypeScript, production build, and independent review
pass. Browser checks cover final values, per-pop conservation, first-entry
numbers, every playback topic, zero tables/lists, stable following content,
and no panel/document overflow at 390/1440 pixels. Published proof:
`student-textbook-web/outputs/chapter-6-all-animations.jpg`.

The third conceptual webpage topic replaces its static ten-row edge-record
table with an integrated recording replay and endpoint lookup. Playback has
36 states (steps 0–35), builds ten unique records, and explains reverse
entries without adding records. Browsable recorded-edge cards expose direction and
tree/back type. `recordedEdge()` gates lookup by the selected frame's count;
existing-but-unrecorded and absent connections have distinct results.
Graph circles use live discovery numbers; pair references use completed
visit numbers. The default representation focuses on one recorded edge; the
adjacency-list review and new adjacency-matrix views remain available.
The print/download table stays intact. Fifteen targeted model/content tests,
TypeScript, production build, and independent review pass. Browser checks
cover first-entry timing, symmetric lookup, ten-record completion, automatic
playback stop, all representation views, stable following content, and
390/1440-pixel layouts. Proof:
`student-textbook-web/outputs/chapter-6-record-edges.jpg`.

The neighbor-classification visual now supports all seven nodes. Visit-number
buttons jump to each node's first entry in the unchanged fixed DFS replay.
Categories follow the active node and retain each neighbor's actual case
at its inspection, with unexamined entries pending. The current neighbor is
highlighted; a processed tree child stays a child after returning. The old
fixed visit-3 caption is removed. `neighborEncounters()` supplies this history
view. Eight model tests and four content tests, TypeScript, and production
build pass. Browser checks cover all selectors, encounter-time categories,
first-entry numbering, active highlighting, stable following content, and
390/1440-pixel layouts. Published proof:
`student-textbook-web/outputs/chapter-6-all-neighbors.jpg`.

The first conceptual webpage example uses the animation instead of a static
ten-edge list or neighbor-order table. Their introductory prose is omitted
or replaced with a short animation instruction in both languages. The first
animation also omits its duplicate visit-number row and unfinished-path
chips. Keep its short representation-comparison prose, graph, controls, current-step
explanation, and discovered count. Later edge-record, low-link, stack, and
block teaching remains. Printable textbooks/downloads retain their reference
lists. This display change passed four content/parser tests, TypeScript,
the production build, first-entry/completed-state browser checks, and a
390-pixel overflow check. Published proof:
`student-textbook-web/outputs/chapter-6-animation-only.jpg`.

Chapter 3 taught adjacency lists only. Chapter 6 reviews adjacency lists
and introduces edge lists and adjacency matrices. Both textbook editions,
the bilingual workbook, teaching guides, and website comparison controls
now explicitly mark this progression. The latest wording correction passed
four content/parser tests, the production build, and mobile browser QA.
Proof: `student-textbook-web/outputs/chapter-6-representations.jpg`.

The current PPT (`258b8e3`) uses numbers 1–7 as completed DFS visit
numbers. They are not fixed vertex labels. Both textbooks, class/support
materials, website, and downloads now follow that interpretation.
During replay, circles remain blank until first entry assigns a number.
Completed visit numbers identify the endpoints in conceptual records,
stacks, lookup tables, and blocks. The replay uses the fixed slide order;
alternative-root controls have been removed so references stay consistent.

The neighbor example is at visit 3: ancestor 1, parent 2, children 4/7,
and descendant 6. Visit 6 has low-link value 3. The full low-link sequence
is 1/1/1/3/3/3/2. Each block has five edges; they share visit 3. Their pop
orders are `4–6, 3–6, 5–6, 4–5, 3–4` and
`2–7, 3–7, 1–3, 2–3, 1–2`. The mini-quiz completion/submission prompt
appears in Coding Plan and the bilingual class workbook.

Preserve the conceptual/C split: C names, internal vertex/edge indices,
source data characters, reset/capacity contracts, and execution details
belong in C Code. The original A–J lab remains a separate coding exercise.
The removed introductory paragraphs and excluded edge topic remain absent.

- `components/textbook/chapter-six.tsx`: five-section shell, shared topic
  hashes, source downloads, and first-topic display filtering for lists
  replaced by the animation. It preserves seven thinking/three efficiency/ten C topics.
- `content/chapter-six.en.md` and `.ko.md`, with
  `lib/chapter-six-content.ts`: mirrored bilingual module textbooks.
- `lib/graph-dfs-lab-model.ts`: separate original/slide graph inputs;
  `visitNumbers` is computed from `slideTrace.discovery`.
- `components/textbook/chapter-six-visuals.tsx`: first-entry visit numbering,
  neighbor classes, timing, three representations, symmetric lookup,
  low-link propagation, pair blocks/stacks, and preparation/cost views.
- `components/textbook/chapter-six.css`: fixed diagram bounds and actual
  all-state maximum heights, measured at current width/language, without
  dynamic internal scrolling or following-content movement.
- `public/chapter-6/`: updated textbooks/workbook/PPT, unchanged lab and
  dependencies, original/slide drivers, bilingual instructions, and the
  eleven-file source ZIP. Copies of both PPT inputs match the repository.
- `code/lecture/ppt_demo.c`: internal indices 0–6 with A–G source characters;
  diagram/output numbers come from computed `visit_num`. The table prints
  `vertex_index visit_number parent_index low`, followed by raw edge-index
  rows and resolved visit-number endpoint pairs. `make lecture-ppt` runs it;
  `make lecture` keeps the original A–J example.

Earlier synchronization validation: all 41 Node tests, TypeScript, and the production build passed.
The HTTP audit passes 24 routes, 679 local links, 384 anchors, and 15
assets. Seventy-seven current repository Markdown links resolve. Both
extracted drivers reproduce expected output under ASan/UBSan; source
C excerpts and lab/PPT inputs are unchanged. Slide peaks remain eight
pending edges/six active recursive calls, with twenty neighbor inspections
per pass and forty-nine active lookup initialization cells.

Browser QA verified blank initial circles, assignment of visit 1 on entry,
completed numbers 1–7, exact pair blocks, stable following content, no
panel/document overflow at 390/1440 pixels, and preservation of the lesson
hash during language switching. The published page was inspected. The
viewport override was reset and the owned preview server stopped. Proof:
`student-textbook-web/outputs/chapter-6-visit-numbers.jpg` (ignored).

## User requirements to preserve

**Size the interactive visual to its tallest animation state.** Measure all states at the current width and language, reserve only their maximum height, and keep that height stable throughout playback. Recalculate when text wrapping or layout changes. Do not use an oversized arbitrary fixed height. Do not introduce an internal scrollbar when an empty node/card appears. Following textbook content must not move as cards are added or removed.

For the first Thinking Logically subsection, `트리의 연결을 어떻게 따라갈까?`:

- Use only the complete A–G binary tree: A has B/C; B has D/E; C has F/G.
- Explain conceptually; no C syntax, function names, or H/I/J examples in Thinking Logically.
- Distinguish moving through the tree from processing data. Use “processing data” rather than “visiting the node.”
- Do not include “이처럼 더 작은 서브트리에 같은 규칙을 적용하는 방식이 재귀다.”
- Keep the webpage's ASCII tree snippet hidden because the interactive diagram already shows the tree. Retain the ASCII example in textbook Markdown/downloads.
- New rule cards stack downward; parents retain their paused progress; the bottom card is active.
- Place the current explanation above the rule stack.
- Keep the tree diagram height stable by reserving the empty-child row during every step.
- Nodes outside the active subtree remain fully opaque. Active subtree/node highlighting still applies.
- Empty-node explanation is exactly “없는 노드이므로 탐색을 종료한다.”
- Removed both captions: “새 작업은 아래에 쌓인다. 맨 아래가 현재 작업이고, 위의 작업은 기다린다.” and “진하게 표시한 부분은 현재 서브트리다. ∅는 없는 자식을 나타낸다.” Their English counterparts were removed too.

The four conceptual rules are:

1. 노드가 없으면 탐색을 조기 종료한다.
2. 왼쪽 자식 트리에 같은 규칙을 적용한다.
3. 오른쪽 자식 트리에 같은 규칙을 적용한다.
4. 탐색을 종료한다.

## Implementation

- `student-textbook-web/components/textbook/chapter-five-visuals.tsx`: `SubtreeRules`, shared `Tree`, animation controls, descriptions, and rule cards.
- `student-textbook-web/components/textbook/chapter-five.css`: animation styling and reserved-height layout.
- `student-textbook-web/lib/tree-dfs-lab-model.ts`: `subtreeRuleFrames()`, 36 frames with independent parent/child progress snapshots; deepest stack contains four cards including an empty subtree.
- `SubtreeRules` uses a hidden, inert, accessibility-hidden measurement container rendering every frame. `useLayoutEffect` and `ResizeObserver` measure the maximum frame height and assign it to the visible wrapper. The visible panel fills that height. Measurements use the same rendering helper and width as the visible panel.
- Measurement container is absolute, zero-height, hidden, and clipped so it adds no document space. It observes its frame wrappers for layout/font/wrapping changes.
- Play/Pause/Replay advances every 1100 ms. Manual stepping pauses playback. Playback stops at the final frame. Cards and highlights transition in 220 ms; reduced-motion preferences are respected.
- `Tree` uses fixed compact bounds based on the deepest node plus the empty-child row, independent of the current frame.
- `student-textbook-web/components/textbook/chapter-five.tsx`: first-topic text-code filtering and conceptual visual selection.
- `student-textbook-web/lib/chapter-five-content.ts`: eight Thinking Logically visual topics.

Textbook sources: `module_05_tree_dfs/student/textbook.md` and `textbook_korean.md`. Website copies: `student-textbook-web/content/chapter-five.en.md`, `chapter-five.ko.md`, and downloads under `student-textbook-web/public/chapter-5/`.

Chapter 5 now has a separate bilingual Full C Code Explanation appendix with 15 topics, every current lab function, C syntax and dependency storage, the full 118-line lab, a runnable lecture driver, exact output, reset behavior, and capacity limits. Sources are `student-textbook-web/content/chapter-five-explanation.en.md` and `.ko.md`, parsed through `lib/chapter-five-explanation.ts` and rendered with the existing shared `FullCCodeExplanation` component. Shared topic hashes `full-c-code-explanation-1` through `-15` auto-expand the appendix and survive language switches. The main manuscript remains six sections and 22 topics.

Code-related visuals and current downloads match the updated module lab and `ppt_lab_material.md`: traversal hooks are comments, writer grouping is implemented, `infix` has twenty slots, and each public writer call resets its cursor. Stack traversal still requires a caller reset of progress. Conceptual Thinking Logically material and its reserved-height animation layout are preserved.

## Verification

The default-page update passed TypeScript checking, 16 Stack/Tree DFS tests, and the production build. The link audit covered all 21 routes, 496 rendered links including 315 anchors, 56 bilingual glossary destinations, 18 public assets, and all 12 Markdown links in nine downloadable documents, with no failures. Browser checks verified both homepage languages, preservation of Chapter 5 appendix hashes during language switching, and deep-link auto-expansion in Chapters 1, 2, and 5. The published homepage was confirmed to show Chapter 5.

Four broken references in downloads were repaired: the Chapter 4 lab links to the published `textbook.ko.md` filename and now has its `stack_autopsy.md` companion; both Chapter 5 textbooks link to their adjacent `lab_demo.c`. Module-source Markdown links remain unchanged, and the existing Chapter 4 synchronization test accounts for its publication filename rewrite.

The preceding Chapter 5 content change passed TypeScript checking, six Tree DFS tests, the production build, and a compiled C driver output comparison. Browser checks covered expand/collapse, topic links, language switching, mobile width, grouped writer output, and repeated-call state. Published English content was confirmed to contain all 15 topics and the complete 118-line lab.

Earlier animation verification showed the measured panel height was 1230 px at the preview width, reduced from 1758 px. At the four-card state, scrollHeight equaled clientHeight; the following section's document position stayed at 1727 px before and after reset. Playback and pause were verified earlier; that layout was preserved in this update.

## Continuing work

Use Sites building/hosting skills for website edits and publishing. Open the existing Site's source with the bundled workflow before editing. Preserve project ID, audience, current architecture, and unrelated user changes. Obtain fresh source credentials as needed; never save tokens in this handoff or files.

The system Git requires an unaccepted Xcode license; use the bundled executables:

- Node: `/Users/cbk/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/bin/node`
- Git: `/Users/cbk/.cache/codex-runtimes/codex-primary-runtime/dependencies/bin/fallback/git`
- Python: `/Users/cbk/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3`
- Sites scripts: `/Users/cbk/.codex/plugins/cache/openai-curated-remote/sites/1.0.1/scripts/`

For the workflow process, prepend bundled Node and fallback Git directories to PATH, launch `site-workflow.mjs --project-id <existing project ID>` in the website checkout with a PTY, and send credentials through hidden stdin. First run without an archive to open source; retain the returned source object. After changes, run again with that source, necessary checks/build commands, and an absolute archive path. Save the exact pushed commit/archive through Sites, then deploy the returned saved version. Confirm deployment succeeded before reporting publication. The normal build command is `node <Sites scripts>/build-site.mjs`; the TypeScript command is `node node_modules/typescript/bin/tsc --noEmit`.

This handoff is a local repository note; it does not require another website publication.


## 2026-10-26 — Module 7 linked lists; Module 8 queues and BFS

This entry records the initial split. The linked-queue revision below supersedes its placement and BFS queue choices.

The requested teaching split is now linked lists only in Module 7, followed by
queues → tree BFS → graph BFS in Module 8. The delivery guide, spiral map,
manuscript/index, vocabulary sequence, instructor guides, question banks,
and current textbook-pilot prompts agree. Each week retains one artifact and
180 contact minutes. Week 7 uses 20/35/40/35/30/20 minutes; Week 8 uses
60 minutes for queues, 30 for tree BFS, 60 for graph/maze BFS, and 30 for
checks, costs, and synthesis.

Module 7's `student/lab.c` retains the existing ten-record `lnodes` pool and
its exact `init_lnodes`, `new_lnode(data,next)`, `free_lnode`, `link_lnode`,
and `delete_next_lnode` implementation. Its former queue tail moved intact
to `module_08_graph_bfs/student/queue.c`. The linear queue permits 25 total
writes per reset; the circular convention permits 24 waiting values.
Module 7's bilingual teaching/release materials and tests now assess only
lists, detachment, recycling, and reuse. The optional pointer-list/DSU
library is retained; DSU teaching remains in Week 13.

Module 8 adds `student/tree_bfs.c` using Module 2's indexed tree. The F-root
fixture processes F,A,G,B,C,D,E. The maze lab imports its local queue and
no longer imports the unused DFS lab. `student/lab_driver.c` checks queues,
tree order/empty/single-node cases, all maze mappings and shortest
predecessors, canonical distance 8 and three routes, independent searches,
and an isolated-start unreachable-passage case. Default builds run this
combined driver. Its Python release packager supplies the exact Module 2
and Module 7 dependencies with repository-relative paths. The older checked
graph library and staged reference exercises remain optional.

Verification: Module 7 core/student tests and textbook demos passed; its
extracted release passed. Module 8 combined/default and extracted-release
checks passed ASan/UBSan. An independent sanitizer harness also verified
all valid maze starts, repeated circular wraparound, and an open 25-passage
interior. Module 9 core/student tests passed after the queue relocation.
The final repository audit checked 464 local links across 84 current files
without a broken destination. Existing old-style C prototype and Module 2
unused-demo-variable warnings remain. Use direct CLT clang with
`-isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk` on this host;
the system compiler shim still requires the Xcode license.


## 2026-10-26 — Linked queue as the Module 7 example and Module 8 worklist

The follow-up restores the linked queue as a required application of linked
lists in Module 7. Module 7's guarded `student/lab.c` contains the original
pool and original `head`, `tail`, `enqueue_lnode`, `dequeue_lnode`, and
`is_empty_lnode` implementation. The queue example traces allocation,
endpoint transitions, FIFO order, reading a returned slot's payload, and
separate recycling. Array queue comparisons and BFS remain in Module 8.

Module 8 imports this exact linked implementation through `student/queue.c`.
Both `tree_bfs.c` and maze `lab.c` now use it. Each pop returns a pool slot;
BFS copies its payload ID and recycles the slot before adding children or
neighbors. Callers initialize the otherwise unowned pool and reset
`head = tail = -1` before an independent traversal; maze callers also reset
`info`. Array `front/rear` resets apply only to array comparisons.

The ten-slot pool bounds pending work, not total discoveries. Peaks are
three for the supplied tree, four for canonical maze start {1,1}, six over
all starts on the supplied maze, and ten over all starts on the optional
fully open 5-by-5 interior. Completed searches restore all ten free slots.
Allocation assertions expose violated initialization/capacity preconditions.

Bilingual teaching materials, assessments, course maps, question banks, and
current pilot prompts follow this sequence. Week 7 uses
20/35/35/30/35/25 minutes; Week 8 uses 60/30/60/30. Each retains one artifact.
Module 7 core/student tests, four textbook callers, and extracted release
passed. Module 8 actual BFS/driver and extracted release passed ASan/UBSan;
its exact-once/FIFO/live-free partition checks cover current and open-maze
starts. Independent pilot checks also exercised both uninstrumented BFS
functions. Module 9 core/student tests passed with the restored queue/pool.
All 464 local links across 84 current files resolve. PowerShell scripts
were not executed; original C warning style is preserved.


## 2026-10-26 — Module 13 searching/sorting/consolidation; MST moved to Module 14

The course now has 14 teaching modules/weeks. The authoritative schedule is
`Data_Structures_Course_2026_14_Week_Delivery_Guide.md`; the former 13-week
filename is a compatibility redirect. Earlier linked-queue decisions remain:
Module 7 teaches the list example and Module 8 reuses it for both BFS loops.

`module_13_search_sort_consolidation/` is the new bounded lesson. It supplies
linear search, first-match binary search, stable insertion sort, and stable
merge sort for up to 64 integers with caller-owned disjoint scratch. The
common input [31,23,17,8,17,42] distinguishes original first-match index 2
from sorted first-match index 1. Consolidation selects earlier structures
from their workload, invariant, costs, and capacity. Students trace/test
supplied code and submit one artifact with a selection memo. The plan is
35/55/25/45/20 minutes, 180 total. Bilingual textbooks, class/PPT/lab materials,
assessment, instructor guide, tests, and a self-contained release are present.

The former `module_13_prim_kruskal/` is now `module_14_prim_kruskal/`; its
bounded `week_13/` unit is `week_14/`. Chapter guide 14, internal labels,
archive names/scripts, all current cross-references, question-bank aggregates,
and current pilot materials follow that move. DSU find/union and Kruskal
remain student TODOs; Prim remains a supplied comparison. Algorithms are
preserved. Module 14 retains one 180-minute artifact and final integration;
the capstone defense remains in the separate final-assessment period.

Verification: Module 13 core/student/demo and extracted 18-file release pass
ASan/UBSan and warning-as-error checks; source excerpts, manifest fidelity,
local links, and overwrite protection pass. Independent oracle/canary tests
also pass. Module 14 full reference core/extension and bounded/reference
checks pass ASan/UBSan; extracted starter scaffold compiles and passes after
temporary reference injection. Original student-authored test placeholders
are intentionally unfinished, not reported as passing. PowerShell inventory
checks pass, but PowerShell runners were not executed. Final audit resolves
521 local links in 114 current files and verifies calendar/index rows 1–14.


## 2026-10-26 — User value-based queue API

The latest user-edited Module 7 lab is authoritative and remains guardless.
It now uses `struct Linked_Node`, `init_lnodes_pool(void)`,
`is_empty_queue(void)`, `enqueue_lnode`, and `dequeue_lnode(void)`.
Raw helpers exchange pool indices; raw empty dequeue returns -1. Public
`bool enqueue(value)` owns allocation and reports exhaustion without mutation.
Public `int dequeue(void)` returns the payload and recycles its node. It
requires a nonempty queue; its assertion disappears under NDEBUG. Payload
-1 is valid data. Never free a public dequeue result as if it were a node.

Both Module 8 BFS loops now call the public value API, with enqueue calls
outside assertions. Array comparisons use distinct `*_linear` names and
unchanged `*_circular` names. Module 9 continues using the raw pool interface;
its tests/docs use the new struct and initializer names. Single-inclusion
protection lives around the Module 7 imports in Modules 8/9 using
`MODULE_07_LINKED_LIST_SOURCE_IMPORTED`, preserving the user's source body.
The combined Module 8 driver imports queue.c before observer macros.

Bilingual materials, assessments, root curriculum/style rules, question
banks, and current pilot examples are synchronized. Module 7 tests/demos
and release pass sanitizers/-Werror, including NDEBUG value callers.
Module 8 combined driver, NDEBUG valid-caller harness, and extracted release
pass sanitizers. Module 9 core/student tests and fresh Stage E release pass.
A combined tree-BFS/hash/maze-BFS harness passes both source-include orders
with ASan/UBSan in debug and NDEBUG builds. Final archive copies for Modules
7/8/9 exactly match the latest user source; 672 local links across
155 current files resolve. PowerShell runners were not executed.
The 14-module sequence and both weekly submission/time budgets are retained.

## 2026-10-30 — Anonymous website visitor analytics

Published Sites version 202 at https://data-structures.chaebinkim.chatgpt.site,
website source commit `044215ba1079f9fa2dfbe7bb154cbd7ca2fc208f`.
The instructor dashboard is `/analytics`; access is restricted by the
server-side `ANALYTICS_ADMIN_EMAILS` runtime secret and platform ChatGPT identity.
Production sign-in and live reports/session timeline were verified in Safari.
The in-app browser's OpenAI account chooser returned an auth error; Safari's
ordinary Google sign-in completed successfully.

`.openai/hosting.json` now binds D1 as `DB`. Generated migration
`drizzle/0000_familiar_jigsaw.sql` creates `analytics_events` and indexes.
Global recording mounts from `app/root-document.tsx`, assigns anonymous browser
and tab session IDs, and batches page views, clicks, input-change activity
without values, navigation, disclosure state, section views, scroll checkpoints,
and visible active time to `/api/analytics/events`. Sessions expire after
30 minutes idle; visitor IDs rotate after 90 days. The bilingual footer explains
recording and supports opt-out; browser DNT/GPC is respected. Names, emails,
IP addresses, URL queries, typed input values, keystrokes, and DOM replay are not
stored by the analytics feature. Platform infrastructure logs are separate.

Reports cover 7/30/90 days, show the newest 100 sessions, and display/export up
to 2,000 events for a selected session. Events older than 90 days are omitted
from reports and removed during subsequent ingestion/report activity. API
validation caps requests at 64 KiB and 50 events, enforces same-origin JSON,
uses idempotent event UUIDs, and applies best-effort anonymous traffic limits.

Verification: 87 website tests passed, including actual route/SQLite ingestion,
authorization, idempotence, retention cleanup, rate limits, CSV, and privacy
cases. TypeScript and production build passed. Local browser tests verified
recorded events, no stored sentinel input values, and unchanged event counts
after opting out and visiting another chapter. Production DB records,
anonymous report HTTP 403, authorized Safari dashboard, and session timeline
were verified. Dashboard screenshot from local QA is
`student-textbook-web/outputs/analytics-dashboard-preview.jpg`.

Publication used a clean checkout at the ignored
`student-textbook-web/outputs/analytics-publication` to exclude pre-existing
unpublished chapter edits. The original website repository now points at the
published commit; its five pre-existing modified files were preserved
byte-for-byte. The local preview server was stopped. Root course source
changes were not published or committed by this task.

## 2026-10-31 — Subsection GPT tutor (local; secure API setup pending)

Implemented an English/Korean `Ask GPT` button at every textbook h2/h3/h4,
including conditional code explanation topics, glossary headings, and visual
subsections. The shared React heading preserves existing anchors; a shared
nonmodal panel selects the clicked subsection, previews the included visible
text, and keeps conversation history only in memory. Glossary term labels are
preserved in context; form values, hidden/inert animation copies, and tutor
controls are excluded. All tutor controls and the panel opt out of visitor
analytics. The panel sends the current subsection snapshot when submitting.

Added `/api/tutor`, server-only Responses API support with `store:false`, a
30-second provider timeout, bounded context/history/output, and atomic D1
request counters. Defaults: `gpt-6-luna`, 3 requests/client/minute,
10/client/UTC-day, 100/site/UTC-day. Client limits are best effort; the global
daily cap remains atomic. No question, answer, excerpt, or IP is stored in the
app database. `drizzle/0001_tutor_usage.sql` and `TUTOR_SETUP.md` document setup.

Work was prepared from published commit `044215ba` through the Sites source
workflow in `student-textbook-web/outputs/gpt-subsection-publication`, then
merged into the primary website checkout. Its five pre-existing modified files
were preserved, including a reverse-merge byte check for overlapping files.
Unrelated course repository changes remain uncommitted.

Verification: all 94 tests pass in both checkouts; TypeScript and the production
build pass. Browser checks found buttons on all visible subsection headings in
Chapters 0–7, no duplicate heading IDs or page overflow, and coverage in all 11
expanded Chapter 1 code topics. Korean phone layout, question-field focus,
glossary context, current animation text, section reset, mocked successful
answers, and mocked request-limit handling were checked. Actual missing-key
behavior is an honest unavailable state; no live OpenAI call was made. Preview:
`student-textbook-web/outputs/gpt-subsection-preview.jpg`.

Publication is pending because production has no `OPENAI_API_KEY`. OpenAI
Developers is now installed. The user explicitly chose secure creation of a new
key, and `open_codex_api_key_setup({})` opened its target-selection flow. Await
the widget follow-up with the selected organization/project before continuing
the API-key skill's local-destination confirmation and encrypted creation. No
key has been created or written. Do not publish the unavailable tutor. After secure key setup, configure the
Sites runtime secret, package this clean publication checkout, save/deploy the
existing public Site, and verify a live answer. No commit, push, saved Site
version, deployment, audience change, or production environment change occurred
for this task.

## 2026-10-31 — Subsection feedback (local; combined publication pending)

Added Helpful / Needs work buttons to every subsection, with clear-on-second-
click, saved-state acknowledgement, and shared state across language switches.
The shared heading now has authored, language-neutral `cN.*` subsection keys;
scopes preserve original HTML elements and anchors. All 16 chapter/language
routes were audited: 797 visible headings, no missing/invalid/overlong keys or
duplicate visible keys. Home aliases share Chapter 7 keys. Existing language-
specific lessons retain their own keys. The original checkout's extra unpublished
Chapter 0 storage-growth lesson also has feedback, while its rewritten bilingual
prose is preserved exactly.

Ten accumulated foreground, active seconds on a subsection count as implicit
positive feedback. Hidden/inert measurement copies, hidden tabs, idle time, and
open dialogs do not count. A successful GPT answer also records an implicit
positive signal using only the subsection key. The latest retained direct rating
overrides implicit positives; clearing it restores in-window implicit feedback.
The instructor dashboard separates effective signals, direct ratings, watches,
and GPT askers, deduplicated by anonymous visitor and subsection across aliases
and languages. Public heading labels are bundled in `lib/subsection-labels.json`;
no visitor-supplied labels or question/answer text enter feedback analytics.

The existing analytics table, authorization, 90-day retention, and opt-out are
reused. Analytics opt-out, DNT, and GPC disable both direct/implicit feedback.
An in-memory preference also handles blocked browser Storage. No additional
production migration is needed for feedback. The tutor's separate migration
remains pending as noted above.

Verification: 101 tests pass in both checkouts, TypeScript passes, and production
build passes. Real local-D1 browser checks verified rating save/replacement/
clear, translation persistence, implicit watching, GPT-question metadata using
an explicitly marked local mock reply, opt-out, and absence of the typed sentinel
in analytics storage. Instructor dashboard rows and readable bilingual titles
were checked with local QA identity only; the temporary local admin configuration
was removed afterward. Korean 375px layout has no horizontal overflow and all
24 Chapter 7 headings have both feedback controls. Preview screenshot:
`student-textbook-web/outputs/subsection-feedback-preview.jpg`.

Changes exist in the primary website checkout and the clean publication checkout
`student-textbook-web/outputs/gpt-subsection-publication`; the original five
unpublished files were preserved. No commit/push, Site save/deploy, production
secret change, or audience change was performed. Complete the already-open
API-key target selection, then finish secure setup and publish the combined
subsection tutor/feedback update using the existing Site's workflow.

The clean checkout's local D1 database already has the analytics schema from
`drizzle/0000_familiar_jigsaw.sql`; the local tutor migration has not been applied.
Both owned preview servers were stopped after QA. TypeScript excludes ignored
publication checkouts/generated outputs, so stale archived components are not
checked against the active checkout's new subsection-key props.
