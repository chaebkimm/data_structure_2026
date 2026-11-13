# Course materials and textbook website handoff

Updated: 2026-11-10.

## Module 12–13 folders renamed — 2026-11-10

The current folders are `module_12_binary_search_bst/` and
`module_13_avl_review/`. Both complete directories were moved, and active
documentation links, displayed include paths, and build commands now use
these names. Historical entries below retain their original paths.

Source files keep their previous module grouping: AVL source remains in
Module 12, and search/sort source remains in Module 13. Teaching-content
alignment is still pending. The approved time budgets and assessment scope
are unchanged. Protected labs and presentations moved byte-for-byte; the
Module 12 README supplies the replacement build command for the protected
lab slides. Existing ZIP filenames, archive contents, release-script defaults,
and website files remain unchanged.

## Modules 12–13 course plan revised — 2026-11-10

Module 12 is **Binary Search and BSTs**; Module 13 is **AVL Rotations and
Review**. The delivery guide, spiral curriculum, module descriptions,
instructor chapter summaries, course indexes, vocabulary order, and capstone
milestones now reflect this sequence. Each week remains 180 minutes with one
submission. Module 13 reserves its final 60 minutes for review, corrections,
and submission. Sorting instruction is optional; Week 14 supplies and explains
edge ordering without assuming insertion-sort or merge-sort instruction.

This update changes planning documents only. Module 12–13 textbooks,
worksheets, lab guides, detailed lesson plans, tests, releases, website pages,
and question content await alignment. Their links are labeled accordingly in
the revised planning documents. Keep existing directory names and source
locations: the AVL source is still in Module 12, and search/sort source is
still in Module 13. No protected lab or presentation file was changed.
BST deletion and AVL deletion remain outside required scope.

## Chapter 7 slot-reference visual published — 2026-11-06

Published Sites version **241**, source `40afc243e0f171ec72c07ae9697759a1d5a27d03`,
deployment `appgdep_6aee825059dc81919077df7ae34d8c83`.
Added the bilingual numbered-slot visual beneath `list-positions`. Fixed physical
slots 0, 1, 2 store next values 2, -1, 1 while their data compartments stay generic.
Selecting a Next field marks the source and destination and shows one arrow;
selecting -1 removes the destination and arrow and explains the absence marker.
Horizontal compartments remain intact in both desktop and stacked mobile layouts.
Native buttons expose source/value labels and pressed state, with one polite status.

TypeScript, 14 existing Chapter 7 tests, build, and whitespace checks passed.
Browser checks covered all selections in both languages, Enter/Space/Tab, forward
and backward arrow routes, and 390px/768px layouts with no horizontal overflow.
Prior visuals remain unchanged, as do all 171 captured manuscript, protected-file,
and download hashes. Only two website components changed; the main checkout has
the same focused patch while retaining other drafts. Production Korean verified.
Proof: `student-textbook-web/outputs/chapter-seven-slot-reference-published.png`.

## Chapter 7 slot-number explanation synchronized — 2026-11-06

Published Sites version **240**, source `efbf5e8232ba729f5ef86adf791748e071dddc5f`,
deployment `appgdep_6aee7fa9802481919d38b14f1a89e6e3`.
Translated the user's replacement second subsection into English: store the next
item's location as a slot number; numbering from zero leaves negative values
available, so -1 indicates no next item. Both website readings, heading labels,
textbook downloads, and the student ZIP match the canonical manuscripts. Preserved
the existing list-positions anchor. The replaced subsection's old numbered example
and diagram no longer render; the first subsection's interactive walkthrough stays.
Updated the existing content test's diagram expectation. Five content tests, build,
whitespace, bilingual preview, and published English verification passed. All 146
captured protected/untargeted files, including the Korean manuscript and visual
components, retained their hashes. Only two textbook members changed in the ZIP.
Proof: `student-textbook-web/outputs/chapter-seven-slot-location-published.png`.

## Chapter 7 first-subsection walkthrough published — 2026-11-06

Published Sites version **239**, source `4474f6fa935e130eb1616713cbbce3decd27ef9e`,
deployment `appgdep_6aee777503888191ab793b130c557e37`.
Added the bilingual Follow next walkthrough beneath `thinking-1`: three cards with
horizontal data/next compartments, visible first/current/last labels, two advances,
terminal stopping, and restart. No sample values or middle dots. Cards are arranged
horizontally from 768px and vertically below it, with connectors from each next
compartment to the following data compartment. Native 44px controls and one polite
status region support keyboard and screen-reader use.

TypeScript, all 14 existing Chapter 7 tests, build, and whitespace checks passed.
Browser checks covered Korean Enter/Space progression, Tab to Restart, English
click progression, terminal disabled state, restart, and layouts at 390/640/768px.
All 171 captured manuscript, protected-file, and download hashes stayed unchanged.
Only two website components changed; the main checkout received the same focused
patch while preserving other drafts. Production Korean rendering verified.
Proof: `student-textbook-web/outputs/chapter-seven-walkthrough-published.png`.

## Chapter 7 revised opening synchronized — 2026-11-06

Published Sites version **238**, source `81d6f3b021f35c03436beac8ca777847d1c9c0c2`,
deployment `appgdep_6aee7490355c8191945e7b82986b518b`.
Preserved the user's revised Korean title, overview, and first explanation;
translated them into English and defined a node at the start of the array-position
subsection in both languages. Synchronized website readings, navigation and page
titles, the first topic's bilingual labels, both textbook downloads, and sources.zip.
Only the two textbook members changed inside the ZIP. Five Chapter 7 content tests,
production build, whitespace checks, bilingual browser previews, and published
English verification passed. All 45 protected lab/presentation files in the chapter
and two website checkouts retained their hashes. Existing Chapter 7 layout remains.
Proof: `student-textbook-web/outputs/chapter-seven-opening-published.png`.

## Chapter 7 introduction layout aligned with Chapter 2 — 2026-11-06

Published Sites version **237**, source `08b8c8099ff7d57c98deaba7665b939deb3440a6`,
deployment `appgdep_6aee6c49350481918f5bf83fcbdbb03d`.
Removed Chapter 7's experiment, glossary, and invariant shortcut buttons in both
languages. The overview now precedes the short red rule with Chapter 2's spacing
(24px after the title, 32px before the 64px rule). Other shared-layout chapters
retain their existing default. TypeScript, production build, whitespace checks,
and bilingual browser layout checks passed. Only two website components changed;
no textbook, lab, presentation, or download files changed. Main website working
files received the same patch without committing unrelated drafts.
Proof: `student-textbook-web/outputs/chapter-seven-intro-layout-published.png`.

## Chapter 5 Korean, lecture guides, and website synchronized — 2026-11-06

Published Sites version **236**, source commit
`0cce1cbc01a34c681526a72d6cbea2e39868b836`.
Deployment `appgdep_6aede5c9226c81918fb6d8a2b7080275` succeeded at
https://data-structures.chaebinkim.chatgpt.site/chapter-5.
English is at `/en/chapter-5`; `/ko/chapter-5` also serves Korean.
Public access, runtime bindings, environment revision 2, and Chapter 8 homepage
routing remain unchanged. Publication incorporates the concurrent Chapter 6
and Chapter 7 updates before applying Chapter 5 changes.

The Korean manuscript and both website readings now match the revised English
textbook: seven sections, 50 topics, eight annotated C excerpts, and the
`F`-rooted alphabet example. Conceptual traversal and reconstruction animations
use that same tree; expression examples use `12+34-*` and `8-(3-2)`.
Existing semantic topic links remain, merged topics retain old anchors, and
the 15-topic Full C Code Explanation appendix is preserved. Downloaded readings
match the course manuscripts except their publication-specific links.

Updated the four editable instructor guides: `instructor_guide/chapter_05.md`
and Module 5's `lesson_plan.md`, `technical_notes.md`, and `answer_key.md`.
They lead from the revised textbook while retaining the existing worksheet
answers and actual demo output as clearly labeled supplements. The user
explicitly reaffirmed that all `lab.c`, `ppt_material.md`,
`ppt_lab_material.md`, `ppt.md`, and `ppt_lab.md` files must remain unchanged.
All 34 protected course files and 20 protected website files retain their
baseline hashes in both website checkouts.

Validation: 43 relevant content, traversal, feedback, analytics, tutor, and
concurrent-chapter tests, TypeScript, production build, links, code equivalence,
and whitespace checks pass. Browser checks covered both languages, all 50
topics, 390px mobile layout, F-root preorder, four pending stack records,
parentheses toggling, reconstruction, language-preserved legacy links, and
appendix deep-link expansion. Published Korean content was visually confirmed.
Local analytics storage was unavailable, so feedback was checked through tests
without sending submissions. The owned preview server was stopped and viewport
restored.

The main website HEAD matches publication; unrelated working-file contents and
non-Chapter-5 label values remain preserved. Course-manuscript and instructor
edits are local and uncommitted. Published screenshot:
`student-textbook-web/outputs/chapter-five-updated-published.jpg`.


## Chapter 7 Korean, teaching, and website editions updated — 2026-11-06

Published Sites version **234**, source commit
`e786ffde1ec5cc87ddf708f4e0dfc44500e41467`.
Deployment `appgdep_6aede490703881918bad9dce3bd67c39` succeeded at
https://data-structures.chaebinkim.chatgpt.site/chapter-7
and https://data-structures.chaebinkim.chatgpt.site/en/chapter-7.

The Korean textbook now follows the revised English chapter and Chapter 2's
seven-section style. The user's Korean title and opening paragraph are preserved.
The workbook, vocabulary, lab guide, lesson plan, answer key, technical notes,
module README, and instructor guide follow the updated sequence. The 180-minute
lesson and A30/B25/C25/D20 rubric remain in place.

Both web readings and textbook downloads match their canonical editions. The
reader supports seven sections, 55 topics, 18 searchable glossary entries, nine
commented C blocks, a responsive linked-sequence diagram, the existing interactive
exercises, and aliases for previous topic links. The 27-member student ZIP and
editable student downloads were refreshed; instructor materials are excluded.
No lab.c, ppt_material.md, ppt_lab_material.md, ppt.md, or ppt_lab.md was edited.
Existing protected website files and course references retain their hashes.

Validation: 34 relevant website tests, 3 synchronization tests, TypeScript,
strict C11 checks for both textbooks, source-equivalence checks, whitespace
checks, and production build passed. Browser checks covered Korean and English,
glossary search, queue enqueue/dequeue, empty endpoints, language switching with
anchor preservation, legacy anchors, nine code blocks, and 390px mobile layouts
without horizontal document overflow. Canonical/download tests passed again in
the main checkout. Production visibly renders the revised Korean chapter.
Local feedback submission and live GPT responses were not exercised.

Publication used an isolated checkout of version 233. The published Chapter 7
patch was applied to the main website working tree without committing or changing
its HEAD. All 15 other pre-existing dirty files and all non-Chapter-7 label values
were preserved. Public access and environment revision 2 are unchanged.
Proof: `student-textbook-web/outputs/chapter-seven-editions-published.png`.

## Chapter 8 interactive visuals improved — 2026-11-04

Published Sites version **233**, source commit
`f1873ad64becf2a87f82fc735cba58079902d480`.
Deployment `appgdep_6aeb3c16dc308191949466c2249896cd` succeeded at
https://data-structures.chaebinkim.chatgpt.site/chapter-8.
Public access, environment revision 2, runtime bindings, and Chapter 8 homepage
routing remain unchanged.

The Chapter 8 maze cards now place the maze, fixed 2×2 controls, single live
status, and stable-height queue in that order. Numeric queue indices remain
visible when empty, while first/last data are separately shown as absent.
Linear and circular empty relations use their respective rules. Route recovery
starts with the destination, reveals one parent cell per action, enables reversal
only at the start, and resets on destination changes. Walls and start==target
produce no-route and completed zero-move states.

Validation: 33 BFS/content/queue/route/feedback tests, TypeScript, whitespace
checks, and the production build passed. Korean and English were inspected at
390×844 and 320×844. Twenty consecutive BFS transitions at each language/width
kept identical button coordinates; cells measured at least 44.59px wide and 48px
high, controls 48px high, and each maze status had exactly one live region.
Maze, controls, and explanation remained visible together. Tested numeric
0/-1 → 0/0 → 1/0, drained linear front=6/rear=5, circular wrapping including
front=0/rear=5 and 0==(5+1)%6, parent stepping/reversal/reset/target changes,
walls, and zero moves. Desktop /ko/chapter-8, bilingual navigation, all 10
visuals, and 50 topics were checked. Published Korean BFS and English route
controls were exercised successfully. Local analytics storage was not configured;
feedback validation used its automated tests rather than local submissions.

Frozen Korean SHA-256 remains
`46e22caa51f82adf051aaca5a4ece403ebc81759eede90e448dd91abc0596960`.
Content/download/anchor tests pass. All 35 protected course references and all
16 pre-existing website working files retain their baseline hashes. Only eight
Chapter 8 display/helper/test files were published from an isolated version-232
checkout. Main website source was fast-forwarded with autostash, then all existing
working-file hashes were verified. Owned preview server was stopped and the
browser viewport restored.

Published mobile proof:
`student-textbook-web/outputs/chapter-eight-visual-improvements-published.jpg`.


## Chapter 8 made the default — 2026-11-04

Published Sites version **232**, source commit
`eeb7d52a508b47038aa17109bbb09edd055d6fcc`.
Deployment `appgdep_6aeae8085bc08191b5759db3955b7fa1` succeeded at
https://data-structures.chaebinkim.chatgpt.site.

The root, `/ko`, and `/en` now render Chapter 8. Navigation, language-specific
canonical URLs, and homepage feedback/analytics attribution use Chapter 8.
Chapter 7 remains at its explicit chapter URLs. Historical stored feedback
and analytics are unchanged; no data migration was needed.

Validation: all 21 relevant analytics, feedback, and tutor-contract tests,
TypeScript, production build, and changed-file whitespace checks pass. Browser
checks confirmed all three home routes render Chapter 8 with 50 topics, correct
canonical URLs, and working links to Chapter 7. The published root visibly
renders Chapter 8. Screenshot:
`student-textbook-web/outputs/chapter-eight-default-published.png`.

The isolated checkout began at version 231. Only ten routing, metadata,
feedback/analytics, and test files changed. The main website checkout was
fast-forwarded to the published source, preserving all 16 pre-existing working
changes byte-for-byte. Frozen Korean, course downloads, lab/PPT sources,
public access, runtime bindings, and environment revision 2 are unchanged.

## Chapter 8 frozen manuscript published — 2026-11-03

Published Sites version **231**, source commit
`9229502bb6c5ae1cda697b45b96cfa87428b45a0`, at
https://data-structures.chaebinkim.chatgpt.site/chapter-8.
Deployment `appgdep_6aeadfc488b48191806f27de262683b3` succeeded. Existing public
access, project identity, runtime bindings, and environment revision 2 remain.
The source was opened from version 230 in the isolated
`student-textbook-web/outputs/chapter-eight-freeze-publication` checkout, retaining
the recent arrival-queue fixes. The 20-file publication contains only Chapter 8
content, schema, visuals, labels, navigation/metadata, downloads, and tests.

Both languages now follow the frozen seven sections and 50 topics with counts
`[14, 2, 15, 4, 5, 3, 7]`. Three new topic IDs are `initial-values`,
`graph-queue-order`, and `graph-shortest-distance`; surviving semantic IDs remain.
Eight retired anchors resolve at their current explanatory topics. Historical
analytics labels remain, with active Chapter 8 labels updated. All ten demos
remain: circular reuse follows the linear-limit demo, and the full-search cost
experiment sits under queue memory with explicit distinction from O(1) queue
operations. Path-recovery copy now uses the Korean term '부모 칸'.

Web readings and public student downloads match the canonical course sources.
The 20-member ZIP excludes instructor material. Frozen Korean and every
protected lab/PPT source remain byte-identical. The primary website checkout
was fast-forwarded to the published commit with all 16 prior working changes
restored; all non-Chapter-8 label values and the other dirty files were verified
unchanged.

Validation: 43 relevant content/model/feedback/analytics/tutor-contract tests,
TypeScript, and the production build pass. Browser checks covered all three
language routes, retained/new/retired anchors, language switching, ten demo
placements, queue add/remove/reset, circular wrapping, BFS completion, path/cost
displays, mobile navigation and question-panel opening, and a byte-exact ZIP
download. Mobile and desktop had no horizontal document overflow. The local
preview lacks production analytics storage and tutor configuration, so actual
feedback writes and GPT responses were not exercised. These services were not
changed. Whitespace checks pass except for the three existing trailing spaces
in each exact frozen-Korean mirror, intentionally preserved.

The published page visibly has 50 topics, eight aliases, and ten demos.
Screenshots: `student-textbook-web/outputs/chapter-eight-freeze-published.png`
and `student-textbook-web/outputs/chapter-eight-freeze-mobile.png`.
The local preview was stopped and the temporary viewport override cleared.

## Chapter 8 Korean freeze and English/course synchronization — 2026-11-03

The user approved freezing `module_08_graph_bfs/student/textbook_korean.md`.
It already matched the latest approved pasted manuscript and was not changed.
Its SHA-256 is
`46e22caa51f82adf051aaca5a4ece403ebc81759eede90e448dd91abc0596960`.
`module_08_graph_bfs/AGENTS.md` records the freeze and makes the Korean manuscript
authoritative for chapter structure and prose. Revise it only when the user
explicitly requests a change to the frozen Korean textbook.

The English textbook, **Chapter 8. Processing data in stored order**, now follows
the frozen seven sections and 50 subsections, with subsection counts
`[14, 2, 15, 4, 5, 3, 7]`. The three new C topics are nested two-dimensional
array initialization, whole-structure copying/passing/returning, and logical OR
short-circuit evaluation. Previously introduced syntax is marked as review.
The seven C excerpts retain the protected lab's tokens. Predecessor recovery
remains a conceptual extension of the distance-only lab.

Student workbooks, lab guidance, evidence and rubric, vocabulary, instructor
plans and notes, diagrams, course indexes/guides, and release documentation now
align with the frozen Korean manuscript and the read-only PPT materials.
Week 8 retains 48 questions, with its consolidated copy synchronized exactly;
later weeks in that consolidated file are unchanged. The 180-minute class and
single-submission structure remain. All 710 protected lab/PPT files are
byte-identical to the start-of-task snapshot; no implementation code changed.

Generated student package:
`module_08_graph_bfs/dist/module_08_graph_bfs_2026-11-03.zip`.
SHA-256:
`2fc874c057dd80cb277211cc7762b0762f3d91c8f29677c48be893f7a6c48dee`.
Its 20 members match the intended source/template bytes. The extracted package
passes the strict Clang lecture harness with AddressSanitizer and
UndefinedBehaviorSanitizer, including 12,800 bordered-maze searches.

Markdown fences and changed-file whitespace checks pass. Of 309 local link
destinations checked across 40 Markdown files, 293 resolve; the remaining 16
are unchanged references to absent older Module 10/11 paths. Every Chapter 8
destination resolves, and this synchronization introduces no broken links.

These changes are local and uncommitted. No website source synchronization or
deployment was performed in this task. The previously published site remains
at version 226 described below; a later requested website update must reconcile
its older 55-subsection schema and visual mappings with the frozen 50-subsection
manuscript.

## Chapter 8 Korean headings and concept-first examples — 2026-11-02

Published Sites version **226**, source commit
`ea3d6ab925de40ed7ee8ace0d49909f457745d76`. Chapter 8 now uses Chapter 1's
Korean section labels and Korean subsection headings. Both manuscripts use
abstract explanations without worked numeric queue/tree/maze traces. Actual
C literals, symbolic formulas, and exercise data remain where needed.
For a nonempty queue, `front` identifies the first stored data and `rear` the
last; the implementation holds their indices. Empty queues have neither queued
endpoint, even when old values remain in memory.

Ten interactive examples now carry the concrete data: FIFO arrival, array
endpoints, linear capacity, circular reuse, tree BFS/DFS, maze representation,
neighbor iteration, BFS discovery/queue changes, predecessor recovery, and
workload counts. The neighbor iterator stops after all directions; the BFS
visual records discovery before enqueueing and distinguishes current, waiting,
and processed points. Predecessor recovery is labelled as an extension of the
distance-only C lab. Current supporting definitions, style guidance, downloads,
and the student package are synchronized. Stable bilingual topic IDs remain.

Validation: all 35 affected tests, TypeScript, production build, and whitespace
checks pass. Browser checks cover both languages, all 55 topics, ten examples,
singleton/empty endpoint markers, circular wraparound, BFS/DFS ordering,
discovery-before-enqueue, iterator termination, and narrow Korean layouts.
The live Korean revision is verified. Proof:
`student-textbook-web/outputs/chapter-eight-concepts-published.jpg`.
All 590 pre-existing protected lab/presentation copies retain their hashes.
The website checkout matches publication with all 16 unrelated working edits
preserved. Course documents and logs remain local and uncommitted.

## Chapter 8 Korean style, course synchronization, and website — 2026-11-02

The Korean textbook now follows the updated English textbook and Chapter 2's
style: seven manuscript sections, 55 matching topics, and seven annotated C
blocks. English prose and code remain unchanged. Current course indexes,
Chapter 8 student/instructor materials, release guidance, question-bank labels,
and neighboring-chapter references use the revised title and array-queue scope.

Published Sites version **225**, source commit
`c8bd75c6668b9798c3f1fb0b6542f5ff136c050b`, with the existing public audience.
Korean is at `/chapter-8` (also `/ko/chapter-8`), and English at `/en/chapter-8`.
The new reader preserves all manuscript topics and code, renders the six-node
tree, and includes shared language anchors, feedback/tutor identities, navigation,
metadata, and current downloads. The home page remains Chapter 7.
`module_08_graph_bfs/release/sync_web.py` refreshes the readings and student pack
while refusing changes to existing protected lab/presentation copies.

Validation: 39 affected website tests, TypeScript, production build, and
whitespace checks pass. Desktop English and mobile Korean checks cover all
55 topic identities, seven C blocks, language/anchor switching, tutor context,
and no page overflow. The published Korean page is verified. The 20-member
download package matches the current release inputs and passes strict C checks
with NDEBUG and 12,800 maze searches. All 546 preserved hashes (existing
lab/presentation files plus the English textbook) match. Proof:
`student-textbook-web/outputs/chapter-eight-published.jpg`.

The primary website HEAD matches publication. All 16 pre-existing working
changes are preserved, including the existing labels alongside the new Chapter 8
entries. Course manuscript/support/log changes remain local and uncommitted.


## Chapter 8 aligned with current PPTs — 2026-11-02

Both Chapter 8 textbooks and their supporting lab/workbook/instructor materials
now follow the current four PPT inputs and read-only maze lab. The lesson uses
linear array queues, conceptual circular wraparound and tree level order, then
5×5 maze BFS with `{y,x}` points stored directly in `queue[N*N]`. Each `bfs` resets
its queue and distances; first discovery writes distance before enqueue. The
canonical search reaches eight passages, gives `{3,3}` distance 4, and ends at
`front=8,rear=7`. Path predecessors are conceptual, not fields in the supplied lab.

Current course scope references, Week 8 question-bank mirrors/counts, and Chapter 8
pilot materials match. Deleted queue/tree/driver dependencies and former linked-
pool/7×7/predecessor-list claims were removed from current Chapter 8 materials.
A separate `code/tests/test_lecture.c` supports `make -C module_08_graph_bfs/code lecture`;
`core`/`student-tests` run the same current lab. The student packager now includes
20 self-contained members and copies all protected inputs byte-for-byte.

Verification: textbook C token fidelity, strict compiler warnings, ASan/UBSan,
12,800 bordered-maze searches against an independent oracle, final extracted
release with NDEBUG, all 33 packaged links, manifest, and overwrite guard pass.
Optional reference core/extension pass; existing optional student-test TODOs
remain. PowerShell was inspected only. All 545 protected source hashes match.
See the new Chapter 8 entry in `TEXTBOOK_VALIDATION.md` for scope and evidence.

Changes remain local and uncommitted. The separate website has no Chapter 8
route, and was not modified or published. Unrelated concurrent workspace changes
were preserved.

## Chapter 2 unread characters stay in the input row — 2026-11-01

Published Sites version **224**, source commit
`f591a63f45b454eaf93ad2ece2755e345334456a`. In the four-step addition-tree
construction, step 3 now keeps the unread second `+` and `3` at their
initial positions `(280,100)` and `(360,100)`. Only the consumed `1+2`
nodes rearrange. Step 4 retains the complete `(1+2)+3` layout and links.
Frame data, prose, controls, playback, and animation timings are unchanged.

TypeScript, production build, and whitespace checks pass. Browser checks
verify all four English states, the Korean third state (including computed
transforms), and the published English third state. Proof:
`student-textbook-web/outputs/chapter-two-unread-nodes.png`.
Primary website HEAD matches the publication; unrelated working files and
all 545 protected lab/presentation files are byte-preserved. These logs
remain local and uncommitted.

## Chapter 3 style and Korean synchronization — 2026-11-01

Updated the Korean textbook and both website readings to match the current
English manuscript and Chapter 2's seven-section style. Both editions contain
46 subsections and seven annotated C blocks. The chapter uses general graph
operations without a worked graph dataset, diagram, or fixed traversal trace.
The reader preserves the manuscript title and introduction, shared bilingual
anchors, feedback/tutor controls, and literal code indentation. Navigation,
metadata, analytics labels, and downloadable Markdown are synchronized.

Published Sites version **223**, source commit
`04a9fd00acd08d73b6c2b52a09f4ee52f94f2e94`, with public access preserved.
The publication merge includes the concurrent Chapter 2 version 222 update.
All 125 publication tests, TypeScript, production build, and whitespace checks
pass. Browser QA verified both languages, seven sections, 46 topics, seven C
blocks, section navigation, language switching, no duplicate IDs, and no page
overflow at the default viewport. The live Korean reading was verified.
Proof: `student-textbook-web/outputs/chapter-three-style-published.png`.

The primary website checkout matches the published commit, with unrelated
working edits preserved. All protected course lab/presentation sources remain
unchanged. Course manuscript and log changes remain local and uncommitted.

## Chapter 2 visuals focused on subsection ideas — 2026-11-01

Published Sites version **222**, source commit
`f780fc0d7e4df820fa9258ba14b04ec5fffa3a88`. The user prefers visuals
that teach the subsection's core idea over repeated generic classroom-tree
inspectors. Replaced the conceptual lesson routing with 38 focused bilingual
widgets. The existing addition-construction diagram and seven C-code tracers
remain specific to their respective lessons.

Hierarchy follows one parent chain; array links show a selected child index;
root access reveals reachable nodes; attachment preserves an old subtree;
operators highlight operand subtrees; evaluation receives left then right
values before returning 6. Glossary controls isolate the named relationship.
Invariant examples expose an invalid index, sharing, or a cycle, with explicit
repair/prevention actions. Efficiency widgets count reserved/initialized
slots, active calls, assignments, and reachable-node reads. Syntax widgets
focus on node members, array objects, member access, postfix values, separate
call state, stopping calls, and digit-character conversion. Compact recursion
uses the canonical B/D/E subtree rather than repeating the entire tree.

All 121 tests, TypeScript, production build, and whitespace checks pass.
Browser checks cover both languages, representative state transitions,
correct postorder/call completion and evaluation, stable subsection keys,
no duplicate IDs, all 38 concept widgets and seven C tracers, and no generic
inspector text. At a 390px viewport no concept card or page overflows; the
normal viewport was restored. No tutor question or feedback vote was sent.
The published English digit selector is verified. Proof:
`student-textbook-web/outputs/chapter-two-focused-visuals.png`.

Both website manuscripts are byte-preserved. All 515 protected lab and
presentation files match the pre-task snapshot. The primary website HEAD
matches the published commit, and all 315 unrelated tracked website files
are byte-preserved. Existing unrelated Chapter 0/3 edits remain local and
unpublished. These course handoff/validation log edits remain uncommitted.

## Chapter 2 current English synchronization — 2026-11-01

Updated the Korean manuscript and both website readings from the current
English manuscript. All editions now have seven sections, 46 subsections,
and seven C examples. The chapter introduction, evaluation walkthrough,
invariant benefits, digit-character conversion, compact efficiency text,
and removed Sibling entry follow the English source. Existing Korean C
blocks, comments, and eight-space indentation are byte-preserved.

Published Sites version **221**, source commit
`7b99536f9090592d614273b162d37cca3fb30d58`. The parser now retains the
chapter introduction above the first section. Renamed bilingual headings
keep their stable topic, animation, feedback, and tutor identities. New
invariant-benefit and digit-conversion topics reuse the tree inspector and
evaluation animation; analytics labels include their shared keys.

All 111 website tests, TypeScript, production build, and whitespace checks
pass. Browser checks verify both languages, 46 topics, seven C topics,
chapter introductions, digit-conversion advancement, tutor opening without
submitting a question, no duplicate IDs, and no page overflow. The published
Korean page is verified. Proof:
`student-textbook-web/outputs/chapter-two-editions-published.png`.

The primary website HEAD matches the published commit. Unrelated website
working files and non-Chapter-2 analytics labels are preserved and remain
unpublished. No protected lab or presentation source was edited by this
task. A final comparison observed concurrent changes to eight protected
paths in Modules 8/9 after the earlier 515-file check; these external changes
were left untouched. Course manuscript/log edits remain local and uncommitted.

## Standing user rule: never modify lab.c — 2026-11-01

All files named `lab.c` are user-maintained and read-only for agents. Never
edit, reformat, comment, fix, or synchronize them when updating textbooks,
materials, or webpages. The rule is also recorded in root `AGENTS.md`.

Restored `module_02_binary_tree/student/lab.c` byte-for-byte from the
snapshot immediately before our indentation/comment edit. The textbook
and webpage formatting/comments remain in place. No other lab files were
changed by this correction.

## Chapter 2 eight-space C indentation and comments — 2026-11-01

Published Sites version **220**, source commit
`86e5e6e099893fe00a57bae4fa794065ecdad505`. All seven C examples in the
English/Korean manuscripts and webpage now use eight literal spaces per
nesting level. Added 24 concise explanatory comments per language covering
node fields, missing-child links, root changes, traversal, index increments,
and returned values. The accompanying `student/lab.c` edit was subsequently
reverted at the user's instruction; lab files are now protected as read-only.
Executable C tokens and all prose outside the code fences are preserved.
Recent English prose revisions discussed in reviews are therefore still
pending separate Korean/web synchronization; this was a code-only request.

Classroom animation source selection now follows the page language so
Korean conceptual call-stack cards display Korean comments. Statement
matching uses trimmed line starts, avoiding comments that quote code.
Both languages retain all 154 trace frames and correct statement highlights.
Immediate playback and timing are unchanged.

All 107 website tests, TypeScript, production build, and whitespace checks
pass. Classroom C syntax compiles with existing empty-prototype and unused
`data_read` warnings. Browser checks confirm bilingual comments, eight-space
indentation, correct recursive-call highlights, immediate Play, and no page
overflow. Published Korean proof:
`student-textbook-web/outputs/chapter-two-indentation-comments.png`.
Primary website HEAD is synchronized with all unrelated working edits
preserved. Course edits remain uncommitted. Before snapshots are under
`student-textbook-web/outputs/indent-comments-before/`.

## Chapter 2 evaluation child-index explanations — 2026-11-01

Published Sites version **219**, source commit
`5c6c1baab6a628a0df0fd15356995a3841ad7bba`. Evaluation calls now show the
caller index and actual child-link value, e.g.
`nodes[i].left = nodes[3].left = 1 → eval(1)`, in the flow panel through
both call-site and child-entry snapshots. Left/right trace captions are
updated in Korean and English. Return/completion frames keep return-value
messages. Trace steps, C source, immediate Play, and movement speed are
unchanged.

Verified all four lookups across the 14-frame Korean trace, including
`nodes[1].left = 0`, all returns, and final result 6; English and published
Korean render correctly. All 107 tests, TypeScript, production build, and
whitespace checks pass. Proof:
`student-textbook-web/outputs/chapter-two-evaluation-arguments.png`.
The two published files and primary Git HEAD are synchronized; unrelated
working edits remain preserved and unpublished by this deployment.

## Immediate Play for all website animations — 2026-11-01

Published Sites version **218**, source commit
`883b26cbb9261e1f2ff428c9b0ce857cfaa86261`. All animation Play controls now
advance immediately on Play/resume/replay: enabled the shared tree and graph
behavior by default and updated the Chapter 5 and Chapter 6 controls.
Chapter 4 already advances immediately. Pause remains stationary and Reset
returns to the initial frame. Two-frame graph replays visibly reset first.
All timer effects, subsequent intervals, movement speed, CSS transitions,
and reduced-motion behavior are unchanged.

All 107 tests, TypeScript, production build, and whitespace checks pass.
Browser checks covered shared tree/graph/stack controls, all three Chapter 5
players, and all 16 Chapter 6 players, including pause/reset and completion.
The published Korean Chapter 2 player advanced within the Play click round
trip. Proof: `student-textbook-web/outputs/all-animations-immediate-start.png`.
The primary website checkout is advanced to the published commit with all
tracked working files byte-preserved. Unrelated Chapter 0 and concurrent
Chapter 3 changes remain local and unpublished by this deployment.

## Chapter 2 addition-tree immediate playback start — 2026-11-01

Published Sites version **217**, source commit
`dd752d3de2f0436856d4f1103ebc4678557e4f75`. The user clarified that the
addition-tree lesson's slow start meant the wait after pressing Play.
An opt-in `advanceOnPlay` on `TreeStepper`, enabled only by
`AdditionTreeDiagram`, advances immediately on Play/resume and Replay.
Reset still shows the initial disconnected nodes; Pause does not advance;
reaching the last frame stops playback. Later intervals, movement speed,
other lessons, and reduced-motion styling are unchanged.

All 107 tests, TypeScript, production build, and whitespace checks pass.
Browser checks verified Korean controls, English immediate advancement
and automatic completion, unchanged neighboring-stepper behavior, and
live Korean response within the click round trip (about 0.3 seconds).
Proof: `student-textbook-web/outputs/chapter-two-immediate-start.png`.
The primary website checkout matches the published commit; its three
unrelated Chapter 0 edits remain preserved and unpublished.

## Chapter 2 hierarchy introduction and materials alignment — 2026-11-01

Updated the Korean textbook to follow the user's revised hierarchy-first
English opening: one root and parent chains, indexed binary child links,
root-based traversal, attaching a node, operators with operand subtrees,
and explicit `-1` initialization before building `(1+2)+3`. Applied the
style guide's `data`/`root` terms. English prose and code are preserved;
only one trailing space was removed. Both editions have seven sections,
45 subsections, and seven byte-identical C blocks matching `student/lab.c`
apart from whitespace. The removed appendix stays removed.

Aligned module/instructor guidance, vocabulary, diagrams, lab bridges, and
release descriptions with the `nodes[10]` alphabet/addition lesson. The
existing `nodes[20]` four-function precedence lab remains a distinct
application with unchanged implementations, tests, grading, and release
gates. The weekly and consolidated question views add 20 classroom prompts
and retain all 40 parser prompts; the question-bank index counts match.

Published Sites version **216**, source commit
`68729886531094e7efc1ae1c53651be1209b2af1`. Both web readings exactly match
the manuscripts. Renamed heading mappings retain all 45 bilingual topic
identities, diagrams, animation assignments, and feedback keys. Updated
the nine affected analytics labels. All 107 website tests, TypeScript,
production build, and whitespace checks pass. Browser checks verified
both languages, seven code topics, matching keys, no duplicate IDs or
horizontal overflow, addition-step advancement, Korean tutor opening,
and the published Korean expression section. No GPT question or feedback
vote was submitted. Proof: `student-textbook-web/outputs/chapter-two-introduction-published.png`.

All 13 parser checks, the lecture example, and intentional faulty autopsy
pass. All 29 release sources and 20 local Markdown links resolve; release
ZIPs were not regenerated. The primary website checkout is advanced to
the published commit, with all 315 tracked working files byte-preserved;
its three pre-existing Chapter 0 edits remain unpublished. Course edits
remain local and uncommitted.

## Shared animation speed for Chapters 1–7 — 2026-11-01

Published Sites version **215**, source commit
`959a74d1b80c2ff8382f3ee7bd7a5c924217baa3`. Chapters 2–7 now share
Chapter 1's 960ms highlights, 1920ms movement, 2400ms copy, and 200ms copy
delay in both languages. Chapter markers scope these values to 1–7;
Chapter 0 keeps its previous timings. Chapter 5/6's separate CSS now uses
the same variables, including cursor arrival and playback timers. Playback
allows transitions to finish, retaining reading pauses and the 4-second
prose-card interval. Stack playback uses the shared interval while keeping
immediate first advancement. Stack diagram highlights and the Chapter 7
node array use shared highlight timing. Reduced-motion rules remain intact.

All 107 tests, TypeScript, production build, and whitespace checks pass.
Browser checks verified timings on all twelve English/Korean Chapter 2–7
pages, Chapter 5 traversal playback/pause/reset, Korean Chapter 6 playback
and reset, stack playback through completion/reset, Chapter 0 defaults,
and published Korean Chapter 6 timings. No GPT questions or feedback votes
were sent. The three unrelated Chapter 0 website edits remain unpublished.

## Faster Chapter 1 animations — 2026-11-01

Published Sites version **214**, source commit
`de7305aecfe81ab5ae76456519c0f833626d6ad0`. Chapter 1 now uses 20% shorter
teaching animation durations in both languages: highlight 960ms, movement
1920ms, copy 2400ms, and copy delay 200ms. A Chapter 1 main-element marker
activates root CSS variables, keeping the existing copy-control timers
synchronized. Other chapters retain their defaults; UI timing and
reduced-motion handling are unchanged.

The existing animation-timing test, TypeScript, production build, and
whitespace checks pass. Browser verification was unavailable because the
browser connection could not be recovered; the new pace was not visually
verified. The three unrelated Chapter 0 website edits remain unpublished.

## Array selection outline clipping — 2026-11-01

Published Sites version **213**, source commit
`f729552c3fa8054bc2bb23f255da3ad95dd8a03a`. Added 4px horizontal padding
inside the shared array grid so the 2px selection ring and its 2px offset
are contained within the scroll area. Chapter 1's first selected cell now
shows the full left border; the same gutter protects the final cell.
The array content, controls, and animation gaps are unchanged.

TypeScript, production build, and whitespace checks pass. Browser checks
confirmed the Korean visual, English selection advancement, and both edge
gutters at a 390px viewport (including the right scroll limit). The three
unrelated Chapter 0 website edits remain unpublished.

## Chapter 3 appendix removal alignment — 2026-11-01

Published Sites version **212**, source commit
`e55352e16a5a3356d6e135b4284bf430ef637798`. Removed the Korean Full C Code
Explanation appendix to match the user's English deletion. Both retained
manuscript bodies are unchanged and contain seven main sections and six
byte-identical C blocks. The supporting module documents and Chapter 3
instructor guide contain no references to the removed appendix, so they
required no edits; all 28 release source mappings resolve.

Both website readings exactly match the manuscripts. The graph outline
now lists the seven retained sections, preserving their topic IDs and
animations. The existing activity coverage test checks the 81 retained
English/Korean subsections and their section counts. All 106 tests,
TypeScript, build, and whitespace checks pass. Browser checks cover both
languages, six C topics, Korean animation advancement and tutor opening,
and the published Korean page. No GPT question or feedback vote was sent.
The three unrelated Chapter 0 website edits remain unpublished.

## Chapter 2 appendix removal alignment — 2026-11-01

Published Sites version **211**, source commit
`d82684e512f94d28cd74a061893254e8004acc79`. The user's English deletion of
Full C Code Explanation is mirrored in the Korean textbook. Both retain
seven main sections and seven identical C blocks; all pre-appendix
manuscript content is unchanged. Ten Chapter 2 supporting documents now
point to retained syntax/code sections and optional subsection Ask GPT
help. The Stage D description now identifies the alphabet/addition examples;
the separate four-function lab and its assessments remain unchanged.

Both website readings are exact copies of the current manuscripts,
including the already-saved depth/height and `O(h + 1)` clarification.
The optional appendix no longer renders or appears in navigation. Only
these two reading files changed in the publication; components and
animations are unchanged. All 106 tests, TypeScript, build, and whitespace
checks pass. Browser checks confirm seven sections/code topics in both
languages, Korean step advancement and tutor opening, and the published
Korean navigation. No GPT question or feedback vote was submitted.
All 29 release source mappings resolve; PowerShell archives were not
regenerated for this editorial update. The three unrelated Chapter 0
website edits and the user's Chapter 3 manuscript edit remain untouched.

## Readable C code in Ask GPT context — 2026-11-01

Published Sites version **210**, source commit
`05c364afd1ec3482c09256bd9522e53f29cf31e8`. The tutor context now preserves
line breaks, indentation, and blank rows in the CSS-grid C listings and
excludes decorative line numbers. Chapter 1's code tracers separate each
variable value and provide a localized array-memory summary with explicit
`array[index] = value` labels. The summary follows the current animation
frame. The shared tree and recursion listings also mark code rows.

The collector still excludes hidden copies, form values, and controls;
authored diagram summaries replace their visual descendants exactly once.
All 106 tests, TypeScript, production build, and diff checks pass. Browser
checks cover English/Korean Chapter 1, Korean animation-step refresh,
Chapter 2 recursion code formatting, and the published Korean tutor's
included-text preview. No GPT questions or feedback votes were submitted.
The five unrelated local website edits remain unpublished.

## Chapter 7 Korean section headings — 2026-11-01

Published Sites version **209**, source commit
`07e3b5f21175c5130926a2d148c166b964269b41`. The Korean chapter's five
section headings now read 논리적으로 생각해 보기, 효율 계산해 보기,
용어 정리, 코딩 계획, and C 코드, matching Chapter 1's terminology.
These labels also appear in the section navigation. Updated the canonical
`module_07_linked_list/student/textbook_korean.md`, webpage reading, direct
download, and the same textbook inside the source ZIP. Existing archive
membership was preserved; the full synchronizer's additional `ppt_lab.md`
was excluded from this narrow publication.

The three sync tests and production build pass. Archive CRCs and member
comparison confirm only the Korean textbook changed inside the ZIP; other
textbook lines are identical. Browser verification covers headings, section
links, mobile menu labels, and the published page. Section IDs, subsection
keys, content, and animations are unchanged. Unrelated local edits remain
unpublished.

## Subsection footer controls — 2026-11-01

Published Sites version **208**, source commit
`adc158eda973e8deac906967d550ff27d7deffdf`. In all chapters and both
languages, Helpful / Needs work now precede Ask GPT at the end of each
subsection or interactive activity. Headings contain no feedback/tutor
controls, and whole-section h2 headings still have no action footer.

`QuestionSection` provides the explicit content boundary, unique heading
identity, and footer. Existing `SubsectionScope` wrappers opt in using
`feedbackFor="heading"`. `QuestionBlocks` groups Markdown h4 headings with
their following blocks, retaining original indices and subsection keys.
The tutor reads the matching complete boundary, including nested examples,
while excluding controls, form values, and hidden measurement copies.
Content, animations, and analytics keys are preserved; hidden animation
copies keep identical footer geometry and distinct IDs.

All 104 tests, TypeScript, production build, and diff checks pass. Browser
coverage verified matching heading/footer ownership on all 16 Chapter
0–7 language routes. At 390px, Chapters 1–7 in both languages keep feedback
and Ask GPT on one row with no horizontal overflow. Appendix h4 boundaries,
the tutor's included text, tree/graph stable reserved heights after
initialization, and linked-list playback/reset were checked. Published
English/Korean Chapters 1 and 7 also passed footer checks. The five unrelated
local website edits remain unpublished.

## Chapters 5–7 title labels — 2026-11-01

Published Sites version **207**, source commit
`6c599feee0f766d3fe4e8ad86a74ee225325cc88`. The shared chapter layout now
removes the manuscript's `Chapter N.`, `제N장.`, or `N장.` prefix from its
display title. Main headings, sidebar titles, and mobile menu descriptions
show the topic alone; their separate chapter labels retain the number.
Manuscripts, content, and animations are unchanged. TypeScript and the
production build pass, and all six English/Korean Chapter 5–7 routes were
verified locally and after publication. Unrelated local edits remain
unpublished.

## Chapters 5–7 follow Chapter 1's layout — 2026-11-01

Published Sites version **206**, source commit
`92560aa4bae1986a005cbef411ad20dbfcbc8700`, at
https://data-structures.chaebinkim.chatgpt.site . The new shared
`components/textbook/chapter-layout.tsx` applies Chapter 1's header, mobile
menu, numbered active section navigation, 280px sidebar, centered 768px
reading column, serif headings, section counters, and spacing to Chapters
5–7 in English and Korean. Their outer text/animation layouts now stack
within that reading column. Future layout edits to these chapters should
use the shared shell and keep Chapter 1 as the visual reference.

Raw manuscripts, model/parsing code, downloads, animation sources and
measurement behavior, named lesson anchors, and subsection keys are
preserved. Chapter 7 retains glossary search, its shortcuts, and the
`#main`, `#invariants`, and `#pool-explorer` targets. Ask GPT and direct
feedback remain exclusive to subsections. Chapter 1 itself is unchanged.

All 102 tests, TypeScript, production build, and whitespace checks pass.
Browser comparisons at 1440px and 390px cover both languages of Chapters
1/5/6/7: heading sizes and reading widths match, all local anchors resolve,
and pages do not overflow horizontally. Tree/graph step/reset checks retain
reserved height and following-content position; mobile Korean playback and
linked rewiring also pass. Mobile section navigation and language switching
preserve the selected hash. All six published Chapter 5–7 routes were checked.
Screenshot: `student-textbook-web/outputs/chapter-layout-unified-live.png`.

Publication used `outputs/chapter-layout-publication` and excludes the five
pre-existing unpublished website edits. Public access and runtime environment
revision 2 are preserved. Course-repository changes remain uncommitted.

## Subsection-only GPT and feedback controls — 2026-11-01

Published Sites version **205**, source commit
`f5a2a2454aea7acd6e01b5aa1bfe2df27ecaa242`, at
https://data-structures.chaebinkim.chatgpt.site . The shared heading now
renders whole-section `h2` headings without Ask GPT, direct feedback, or
tutor/feedback target attributes. Subsection `h3`/`h4` headings retain both
controls. Section headings still bound reading spans, so the previous
subsection cannot accumulate watched time from the next section's preamble.
The tutor setup notes document this rule; historical analytics are retained.

All 102 website tests, TypeScript, production build, and whitespace checks
pass. A new regression covers the section/preamble gap between subsections.
Browser checks across all 16 English/Korean Chapter 0–7 routes confirm no
section controls/targets and matching subsection/control counts. Published
Chapter 1 has zero section controls and 39 subsection Ask GPT/feedback pairs.
Screenshot: `student-textbook-web/outputs/subsection-only-controls-live.png`.
Public access and runtime environment revision 2 are preserved. Publication
used the isolated `outputs/subsection-only-publication` checkout; the five
pre-existing unpublished website edits remain excluded and preserved.

## Chapter 1 shortened textbook and GPT support — 2026-11-01

The user's deletion of **Full C Code Explanation** from the English
Chapter 1 textbook is authoritative. The Korean textbook now ends after
the same five short C examples. Both retain seven main sections. Thirteen
Chapter 1 support documents now point detailed syntax/execution questions
to the webpage's **Ask GPT** controls instead of the removed appendix.
The standalone lecture remains an instructor companion; lab code,
assessment, release gates, and required operations are unchanged.

Published Sites version **204** at
https://data-structures.chaebinkim.chatgpt.site, source commit
`d80aa86b327b5a06be0b3698f67c14515cb784a1`. Chapter 1's appendix navigation,
rendered section, bilingual content copies, and exclusive loader are removed.
Other chapters still use the shared explanation renderer. The old Chapter 1
heading label is retained for historical analytics. Public access and runtime
environment revision 2 are preserved.

Verification: bilingual section/code parity, all 31 release source mappings,
local Markdown destinations, and whitespace checks pass. All 101 website
tests, TypeScript, and production build pass. Browser checks cover both
languages locally; the published Korean page has seven sections, five
code examples, and a ready GPT question panel. No provider question was
submitted. Screenshot: `student-textbook-web/outputs/chapter-one-gpt-update.png`.
Publication used `student-textbook-web/outputs/chapter-one-publication` to
exclude and preserve the five pre-existing unpublished website edits.
The primary website checkout now points at the published commit; all 313
tracked working-file states were preserved during synchronization, leaving
only those five unpublished edits. The local preview is stopped.
Course-repository edits remain uncommitted.

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

## 2026-10-31 — GPT tutor and subsection feedback published

Published Sites version **203** at
https://data-structures.chaebinkim.chatgpt.site using source commit
`ca691b2caa1fe4997741e2e198c1392c4893b427`.
Saved version: `appgprj_6a955240a2d0819191a05a6f72a08e8f~appgver_33592e6feccc8191827543b976fc9409`.
Deployment: `appgdep_6ae5b691ad488191a32012510fea10b5`, succeeded with environment
revision 2. Existing public audience and instructor analytics authorization are
preserved. The hosted tutor migration was applied successfully: its availability
check and real question both succeeded.

The user selected and explicitly approved creation of **Data Structures Website
Visitors** in the Personal organization / Default project, with a 30-day expiry.
The encrypted setup helper saved `OPENAI_API_KEY` to the approved
`student-textbook-web/.env.local` with permissions 0600; it is ignored by Git.
The key was configured as the Site's server-only `OPENAI_API_KEY` secret without
changing `ANALYTICS_ADMIN_EMAILS`. No plaintext key appears in source or chat.
Rotate this key before its selected 30-day expiration; no automatic renewal was
configured. Do not create another key merely to resume this completed setup.

The bundled Responses verification helper returned a successful GPT-6 Luna haiku.
Production browser QA then submitted a real question on `/en` about changing
`next` links without moving data. GPT returned the correct two-sentence answer.
The public feedback control acknowledged a saved Helpful vote, then its clear
operation succeeded to remove the test's direct rating. Browser console had no
errors/warnings. Prior 101 tests, TypeScript and production build passed for the
unchanged published source. Live proof screenshot:
`student-textbook-web/outputs/subsection-gpt-live.jpg`.

The optional API credit preview offered an estimated USD 66 expiring
2026-11-10, but no organization was linked and no credit grant was claimed:
the required native `confirm_api_credit_promo_org` form was unavailable. This did
not block the successful API verification or publication. Any future credit
claim must restart its current eligibility preview and receive native org-picker
approval; do not assume the API-key project authorizes that separate link.

The source helper committed, pushed, and packaged the clean publication checkout.
The primary website checkout was advanced to the published commit with a mixed
reset after verifying there were no staged changes. SHA checks confirmed all
313 source working files were preserved. Its only remaining tracked changes are
the same five pre-existing unpublished files (Chapter 0, glossary, translations,
and both Chapter 2 manuscripts). The approved local key remains ignored. Course
repository changes, including this handoff, remain local and uncommitted.


## 2026-11-08 — Chapter 9 bilingual website publication

Published Sites version 273 at https://data-structures.chaebinkim.chatgpt.site
(source commit `eb6a7c3b7abf2ac9ef7ac76f705540264cd2b5ba`). Chapter 9 is now the
Korean/English homepage; explicit Chapter 8 and Chapter 9 language aliases work.
Seven sections, 47 bilingual topics, signed-hash/chain/capacity/two-sum visuals,
and complete downloads follow current Module 9 lab.c. Lab/PPT bytes remain
unchanged, including published downloads. Legacy open-addressing is conceptual
or optional; the lab has ten key/data nodes and fifteen buckets, no Module 7
pool dependency. Both pair searches return {j,i}; target0 gives {4,5}, BF11/HT1.

Publication used an isolated checkout under
`student-textbook-web/outputs/chapter-nine-publication-20261108/.sites-checkout`
based on live version272 commit `6c81315ac963e0dfcd9cd0811e34e2b25dc97137`.
Only Chapter9 integrations plus a behavior-preserving existing TypeScript
traversal-end predicate fix were published. The feature patch was also applied
to the primary website checkout; unrelated dirty edits and existing label
values were preserved. The primary checkout HEAD was not reset or committed.
All179 website tests pass in both checkouts, TypeScript and production build
pass, and the ZIP's C tests pass. Browser QA covered EN/KO at390px/1280px,
integer bounds, misses, duplicates, exhaustion/reset, playback, stable heights,
and anchor-preserving language switches. Published route/download checks pass.
Verification JSON and live screenshot are in the publication output folder.


## 2026-11-08 — Chapter 9 concept-first teaching sequence

Published Sites version 274, commit `045db24d743d5372d40067f4c7445ec3992c5bd8`.
Chapter 9 is now titled Storing and Finding Data with a Hash Table /
해시테이블로 데이터 저장하고 찾기. It teaches array lookup → direct addressing
→ hash functions/tables → signed normalization → collision chains before
introducing two sum as an application. Existing anchors remain valid; two
new concept topics bring each language to 49 topics. Capacity visualization
uses ordinary stored records and does not assume a two-sum result.

Updated both web manuscripts/downloads, the Korean course copy, extended
English course textbook, indexes, teacher plans/answer key, and Stage A
standard/linear inquiries. ZIP includes updated handouts. All 179 website
tests, TypeScript, production build, and content/ZIP C checks passed. Local
primary website checkout received the published patch without resetting its
HEAD or unrelated edits. Lab and PPT files remain byte-identical. Proof and
verification are in the existing chapter-nine publication output folder.


## 2026-11-08 — Chapter 9 standalone explanations

Published Sites version 275, commit `c94caaa207b31e39c65f751cab4d15e8c0a866b3`.
Removed presentation-source attributions and smaller-example comparisons
from both Chapter 9 web manuscripts, course textbook copies, student handouts,
and the downloadable package. Generic slide download links and original files
remain available. Existing topic anchors are preserved; alternatives now uses
a standalone heading. All 180 tests, TypeScript, production build, and live
EN/KO wording checks pass. Protected source hashes are unchanged. The same
publication patch is applied to the primary website checkout.


## 2026-11-10 — User-authored Chapter 9 opening

Published Sites version 276, source `1815a10972cd2f96e90a8fb2b9e59c65262d759d`.
Applied the user's exact Korean title 키로 데이터 저장하고 찾기 and opening
paragraph to the website, metadata, navigation and textbook download. English
is Storing and Finding Data by Key with matching introductory meaning. Current
course index/title references were synchronized; the extended English course
introduction was updated without changing its body. The user's entire Korean
course file was preserved, including the separately edited first topic heading
메모리 공간에서 원하는 값을 어떻게 찾을까?; that unrequested heading change
was not copied into the web schema. All 9 targeted content/integration tests,
TypeScript, production build and live title/intro checks passed. Lab and slide
sources were unchanged. Publication patch also applied to primary checkout.


## 2026-11-10 — Chapter 9 first subsection wording

Published version 277, source `703df824840579fb72d76303392f55bafb6dcbb8`.
Applied the user's exact first heading 메모리 공간에서 원하는 값을 어떻게 찾을까?
and paragraph beginning 단순한 방법은 모든 데이터를 처음부터 하나씩 읽으면서
in Korean, with corresponding English How do we find a value in memory?.
Title/intro and all later topics remain unchanged. Updated root course files,
web manuscripts/schema label, individual downloads and ZIP. Existing array-search
anchor remains stable. Nine targeted tests, TypeScript, production build and
live bilingual text checks passed; primary website checkout is synchronized.


## 2026-11-10 — Chapter 9 lookup-table motivation

Published version 278, source `eee2bfecd2fd10b691a1fd411517e50c568483bc`.
Added the user's exact 더 쉽게 찾는 방법은 무엇일까? heading and paragraph
between memory lookup and direct addressing, with matching English How can
we find it more easily?. All earlier/later text is preserved. New stable ID
lookup-table brings both manuscripts to 50 topics. Updated course copies,
web schema/labels, downloads and ZIP. Nine targeted tests, TypeScript,
production build and live bilingual text/order checks passed. Publication
patch applied to the primary website checkout; protected sources unchanged.


## 2026-11-10 — Chapter 9 wider value ranges

Published version 279, source `8005bd543033a1d2514151ed7f471e3730f7cf55`.
Replaced the lookup-table motivation with the user's exact possible-values
wording and inserted 값의 범위가 넓을 때는 어떻게 할까? / What if the range
of values is wide? immediately afterward. Existing material follows intact.
New ID wide-key-range gives 51 matching bilingual topics. Course copies,
web manuscripts/schema/labels, downloads and ZIP are updated. Nine targeted
tests, TypeScript, production build and live text/order checks passed. Same
patch applied to primary website checkout; protected sources unchanged.


## 2026-11-10 — Chapter 9 same-index values and author-edited structure

Published version 280, source `838b8e98bc64ac85e6514e516f4e6a9238a3ae3e`.
Applied the user's exact 서로 다른 값의 번호가 같을 때는 어떻게 할까? and
list/linked-list explanation. During work the author updated the Korean course
file directly, deleting four superseded formal introduction topics. Preserved
that entire file byte-for-byte and used its current structure for the web copy
(trailing spaces normalized only on web); mirrored the removals in English.
There are now 48 topics, 11 in Thinking logically. Existing direct-addressing,
hashing, signed-hashing and collision-chains anchors remain one-hop aliases.
Hash visual is attached to wide-key-range; chain visual to same-index-values;
capacity/two-sum remain intact. Downloads/ZIP and primary checkout synchronized.
All 181 tests, TypeScript, production build, live bilingual order/text, all four
visuals and all four alias presence checks passed. Lab/slide sources unchanged.


## 2026-11-10 — Chapter 9 introductory linear-search visual

Published Sites version 281, source `95dbe65b5606e76eb3d59330859f764fa3ca3fc1`, through the existing public project. Deployment `appgdep_6af3d71e108081918c67111c8f167ab0` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

- Added the Korean/English “값을 하나씩 확인하며 찾기” / “Search one value at a time” visual under `thinking-logically-array-search`, using the current lab array without source changes.
- Pure linear-search frames start at zero checks and complete one equality comparison per step; successful/final unsuccessful comparisons directly produce the terminal result. First match wins; empty input and signed 32-bit boundaries are supported by the model.
- Added custom integer targets and −16/4/3 presets, previous/next/play/pause/restart and slider controls, visible index/value/current/visited/found distinctions, comparison counts, explicit comparison expressions and final results. Invalid input keeps the accepted trace.
- Reserved all wrapped status/result/expression/player sizes from the first frame with inert, accessibility-hidden alternatives. Browser checks confirmed constant panel height and unchanged document position of the following topic across ready/search/completion/error/restart and integer boundaries: English 893px desktop / 1359px mobile; Korean 869px desktop / 1293px mobile at the tested 1280px and 375px viewports. No internal scrolling; ten desktop columns and five mobile columns. Live Korean search confirmed index 7 after eight comparisons with height and following content position unchanged.
- Native keyboard Enter and range End, Previous, same-target restart, validation messages, playback completion and both language layouts verified. Browser console had no errors. Existing reduced-motion player handling is reused (media-change stops playback; manual reduced-motion playback uses the existing slower cadence); the browser reported the normal-motion preference during checks.
- All 184 Node tests passed, including the C oracle; TypeScript and production build passed. All 967 recorded protected source files retained their exact hashes. Synced only the five verified changed files into the dirty website checkout, preserving unrelated work. No manuscript/download changes were needed for this web-only interaction.
- Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-linear-search-live.png`. Publication archive: `chapter-nine-linear-search-site.tar` in the same output directory.


## 2026-11-10 — Simplified Chapter 9 memory-search visual

Published Sites version 282 from source `1b7d7f30d5e4cd93127a8006c8b246bbeb980868`. Public deployment `appgdep_6af3dd1938448191a17f2fcab5c13110` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Replaced the introductory numeric demonstration with six anonymous boxes, native Present/Absent scenario radios, one short localized status, and Check next/Restart controls. There are no visible values, indices, statistics, expressions, text inputs, slider, or playback. Present stops at the fourth box; Absent checks all six. Checked misses use × and a match uses ✓, with the latest checked box outlined. Scenario changes and Restart clear all marks. The pure memorySearchFrames model contains only phase and checked index; the obsolete numeric introductory model/tests were replaced. Other Chapter 9 visuals/models and manuscripts/downloads remain unchanged.

All 184 Node tests, TypeScript checks, production build, and diff whitespace checks passed. Browser-verified English and Korean, native keyboard Enter/Space/radio Arrow keys, both scenarios, completion disabling, restart and scenario resets. Six desktop columns / three mobile columns are correct. Panel height and following-topic document position stayed identical through every state at 1280px and 375px widths: desktop 401px in both languages, mobile English 501px / Korean 477px. Hidden sizing alternatives are inert and aria-hidden; no internal scrolling, numeric text or numeric inputs remain in this visual. Browser console had no errors. Live Korean search reached the fourth box with the following content position unchanged. All 967 recorded protected source hashes were preserved.

Only three verified changed files were synced back into the dirty website checkout; unrelated work was preserved. Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-simple-search-live.png`. Matching archive: `chapter-nine-simple-search-site.tar` in that output directory.


## 2026-11-10 — Chapter 9 symbolic direct-address visual

Published Sites version 283 from source `e82cd47abc05c65655944a5366dda98c04c31746`. Existing public deployment `appgdep_6af3e731bb6c819194ad0d6db55b64f7` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “표에 기록된 위치로 바로 찾기” / “Find the recorded location” under the existing `thinking-logically-lookup-table` topic, preserving its anchors and feedback/tutor scope. Four permanent symbolic key slots (○ △ □ ☆) act as accessible pressed-state buttons. The ready-built model maps circle to memory0, triangle3, square5, and star to null. The six-cell memory fixture has visibly unused slots; there are no visible numeric indices, values, counts, inputs or extra controls. Selecting a stored key highlights its table slot and memory destination with one decorative connector. The star retains its table slot and shows exactly “No stored location” / “저장된 위치가 없다”, with no connector or memory highlight. A caption identifies the complete example key universe.

Added the pure directAddressLookup model with frozen readonly key/memory fixtures. All 187 Node tests (including 14 model tests and the C oracle), TypeScript, production build and diff whitespace checks passed. Browser checked all four states in Korean and English at 1280px, 375px and 320px widths; native Enter/Space selection, state announcements and labels, correct four/six unwrapped columns and no internal scrolling/input fields. Connector horizontal endpoint error stayed below0.84px, with a1px source gap and2px destination gap; connector band remains48px even for star. Panel height and following-topic document position stayed identical across all selections at each width/language: both desktop489px; English mobile513px at375/561px at320; Korean mobile513px at375/537px at320. Sizing status variants are inert and aria-hidden. Browser console had no errors. Live Korean present/absent switching also preserved height and following content.

All 967 recorded protected source files retained their exact hashes. Only the five verified changed files were synced into the dirty website checkout; unrelated work, manuscripts and downloads were preserved. Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-direct-address-live.png`. Matching publication archive: `chapter-nine-direct-address-site.tar` in that directory.


## 2026-11-10 — Chapter 9 symbolic hashing and relocated signed hashing

Published Sites version 284 from source `d4a59e7e62378851bad54d6a6c339d238aec0ed9`. Existing public deployment `appgdep_6af40267a2888191b7f437ffbf6b1aeb` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

The `wide-key-range` introductory hash visual now uses four familiar symbols and three illustrative slots: circle/star→0, triangle→1, square→2. The fixed table retains circle/triangle/square. Selection updates the calculation block, one connector, selected slot and localized match/mismatch status only. Star shows exactly “Same slot, different stored value” / “같은 칸이지만 저장된 값은 다르다”; it never overwrites circle or claims absence. There is no input, stepping, playback, extra memory diagram or collision-resolution mechanism in this conceptual lesson. Added frozen fixtures and a separate pure symbolicHashLookup model.

The existing numeric SignedHashLesson moved intact to `new-c-syntax-explained-signed-remainder` with visual mode `signed-hash`. Source parity was verified against the previous commit after normalizing only the visual data-marker. Historical anchor `thinking-logically-signed-hashing` now resolves within that C syntax topic in both languages; general hashing anchors still resolve to `wide-key-range`. Historical labels/analytics and all other models remain unchanged.

All 190 Node tests, including 17 model tests and the fifteen-bucket C oracle, TypeScript, production build and diff whitespace checks passed. Browser-verified all symbolic mappings, fixed stored values and exact mismatch text in both languages at 1280/375/320px, native Enter/Space selection, one connector, no inputs/internal scrolling, and fixed following-topic document positions. Symbolic panel heights remained constant across all four states: desktop543px both languages, mobile375px567px both, mobile320px English627px/Korean567px. Connector horizontal error stayed below0.67px; its band remains48px, with0px source gap and2px destination gap.

The relocated numeric demo was browser-checked at desktop/mobile widths in both languages: fifteen positions; negative keys, zero, positive collisions, signed boundaries and negative multiples; rejected blank/fractional/out-of-range input preserved the accepted calculation. Its height and following content remained fixed, including errors (English320px969px/desktop649px; Korean320px917px/desktop649px). Historical anchors landed at approximately96px below the viewport top in both languages. Browser console had no errors. Live Korean numeric placement and symbolic star/circle mismatch were verified.

All 967 recorded protected source hashes were preserved. Only six verified changed files were synced into the dirty website checkout; unrelated work, manuscripts and downloads remain intact. Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-symbolic-hash-live.png`. Matching archive: `chapter-nine-symbolic-hash-site.tar` in that output directory.


## 2026-11-10 — Chapter 9 symbolic separate chaining

Published Sites version 285 from source `ce9f7a5e975d4bd61ae30273d3ad8c4c566f381b`. Existing public deployment `appgdep_6af4097aba208191a3376378cad7c316` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Replaced the numeric insertion/find UI under `thinking-logically-same-index-values` with “연결된 리스트에서 값 찾기” / “Search the linked list.” The three permanent chains are0→star→circle→End,1→triangle→End,2→square→End. Caption explains star is now stored too and circle is retained. Four shape buttons choose a search, resetting even when the same key is selected. Only Check next/Restart advance/reset progress. Every click checks one node; circle checks star× then circle✓, other keys stop at their first node. Stored glyphs stay visible, visited/found badges occupy reserved space, other chains remain untouched, and Next disables on a match. No missing-value fixture, numeric inputs, payloads or allocation controls appear in this introductory visual.

Added deeply frozen SYMBOLIC_CHAINS and pure symbolicChainFrames with a ready frame then one comparison per frame. Removed the numeric insertion/find branch completely, retaining its underlying models/C tests. Refactored the surviving capacity branch to CapacityLesson while preserving its initial five records, exact fillCapacity trace, initialize/reuse controls, board/readout helpers and all signed hashing/two-sum functions.

All 193 Node tests, including20 model tests and the C oracle, TypeScript, production build and diff whitespace checks passed. Browser-verified all four targets in Korean/English at1280/375/320px, same-key reset, restart, native Enter/Space, completion disabling, permanent glyphs, no numeric input, no internal scrolling or row overflow. Each width/language kept exactly one node-layout signature through every state; panel heights stayed651px desktop and699px at both mobile widths, with following-topic positions unchanged. Hidden status-sizing alternatives are inert and aria-hidden. Browser console had no errors. Live Korean ready→star mismatch→circle match preserved all glyphs and layout.

Capacity regression verified in English desktop and Korean320px: initial unused5/head0=4; filling ten yields unused10/head0=9 and eleventh insertion returns−1 with heads/counter/node fields identical to its preceding capacity-check state. initialize leaves old node fields unchanged while clearing all heads/counter. insert(7,70) reuses node0, sets bucket7=0 and unused1. Heights/following content were unchanged across these operations (English desktop1228px; Korean mobile1750px).

All 967 protected source hashes were preserved. Only three verified changed files were synced into the dirty website checkout; unrelated work, manuscripts/downloads, anchors and analytics labels remain intact. Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-symbolic-chain-live.png`. Matching archive: `chapter-nine-symbolic-chain-site.tar` in that output directory.


## 2026-11-10 — Chapter 9 alternative-solutions opening text

Published Sites version286 from source `0a4cb29bd7be17a9259997dc1f9b98485b90ce6d`. Existing public deployment `appgdep_6af40c1e32f48191ac226c1a77dedd8f` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Applied the user's exact Korean “다른 해결책은 무엇이 있을까?” heading and three-sentence probing explanation immediately after same-index-values. Replaced the superseded alternatives discussion, retained semanticID/anchor `thinking-logically-alternatives`, and updated the matching English heading “What other solutions are there?” and translation. Alternatives is now the fifth thinking topic, before key-and-data and allocation-and-reset. Updated the bilingual schema, existing heading label, web manuscript downloads and deterministic24-fileZIP. No duplicate old alternatives subsection remains.

The course agent changed only the corresponding target block and position in the two root course manuscripts, preserving all other bytes, Korean user trailing spaces, all C blocks and the entire later top-level-section tail. The website still has48 matching bilingual topics and all7 existing interactive visuals. Renderer/model code is unchanged. Historical subsection keys/labels and analytics records were retained; only the current alternatives heading wording changed.

All193 Node tests (including ZIP extraction/C build and annotated executable-token parity), TypeScript, production build and isolated diff whitespace checks passed. Independent review confirmed exact Korean wording, matching English probing explanation, correct order/schema/labels, download/ZIP copies and unchanged executable C tokens. Browser verified both published languages and updated tutor/feedback heading labels. Live HTTP checks confirmed48 topics/7 visuals and byte-identical downloadable EN/KO manuscripts andZIP.

All967 recorded protected source hashes were preserved. Only8 verified publication files were synced into the dirty website checkout; all unrelated labels/work were preserved. Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-alternative-solutions-live.png`. Matching archive: `chapter-nine-alternative-solutions-site.tar` in that output directory.


## 2026-11-11 — Guided open-addressing visual

Published Sites version 287 from source `ec55f60d01c2e890483b3dd95546dea17e3568bf`. Existing public deployment `appgdep_6af434b8c1788191a8f787de5c7cce68` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “표 안에서 저장하고 찾기” / “Store and search in the table” under the existing alternatives topic. The fixed four-slot story searches for absent star, stores star in the first empty slot, then searches again from slot 0. It has exactly 15 deeply frozen model frames: three ready states and twelve slot checks. Frames 4→5 and 9→10 use explicit Start storing/Search again actions that enter a ready state without checking a slot. Frame 9 alone changes slot 3 from empty to star; circle/triangle/square remain unchanged. Final lookup reaches star at slot 3 and disables Check next. Restart removes star and resets the full story. There are only two visible controls, with no selectors, inputs, counters, playback, wraparound, deletion or resizing.

All 196 Node tests, including 23 model tests and the existing C oracle, passed. Final TypeScript, production build and diff whitespace checks passed. Independent review confirmed transition semantics, immutable snapshots, per-probe announcements and sizing coverage; all pre-existing UI function bodies remain byte-identical. A narrow English button-sizing issue was corrected so visible controls fill the maximum reserved region while hidden alternatives retain intrinsic sizing.

Browser-verified every frame in Korean and English at 1280/375/320px, exact probe order, stored-table retention, fresh marks/indices on stage transitions, changing per-slot polite announcements, native Enter/Space, final disabling and complete restart. Each width/language retained one slot-layout signature, one final button-layout signature, and an unchanged following-topic document position across all frames. Heights: desktop 455px in both languages; English 375px 503px / 320px 517px; Korean 375px and 320px 503px. Hidden sizing variants are inert and aria-hidden. There are no inputs/internal scrollbars. Browser console had no errors. The entire published Korean story was replayed and verified through final match, including the two explicit ready-state transitions.

All 967 recorded protected source hashes were preserved. Existing lab models, source files, manuscripts, downloads, anchors and labels are unchanged. The website retains 48 bilingual topics and now has eight distinct visual attachments. Only five verified files were synced into the dirty website checkout; unrelated work was preserved. Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-open-addressing-live.png`. Matching archive: `chapter-nine-open-addressing-site.tar` in that directory.


## 2026-11-11 — Chapter 9 two-sum introduction and authored outline

Published Sites version 288 from source `b54f02389104d120170275cd098bcf5a852f173d`. Existing public deployment `appgdep_6af43fdc8bf48191808e73673e64a287` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Applied the user's exact Korean heading “합계가 목표값인 두 숫자를 어떻게 찾을까?” and four-sentence brute-force introduction directly after alternatives, retaining semantic ID `two-positions`. Updated its English translation and current bilingual heading label. Followed the author-owned Korean outline, which had already removed the two technical introductory key/data and allocation/reset topics. Both web editions now have 46 matching topics, including nine Thinking topics. Kept all eight visual modes by moving capacity/reset to `c-code-table-initialization`. Retired key/data and allocation anchors now resolve to node-storage and table-initialization; historical labels remain. Web manuscript downloads and deterministic 24-file ZIP match the rendered text.

All 196 Node tests, TypeScript, production build and diff whitespace checks passed. Independent review confirmed bilingual ordering, author-text parity (apart from trailing-whitespace normalization in web copies), aliases, all eight literal C blocks and actual-lab token parity, downloads and ZIP. Browser verified published EN/KO wording, mobile width without page overflow, capacity placement and historical anchor landing. All three live manuscript/ZIP downloads matched local build bytes. Current public audience retained.

All 967 recorded lab/presentation source hashes were preserved. Root Korean manuscript was never written by this task. During publication the author independently revised the following complement subsection to “각 숫자마다 어떤 숫자를 찾으면 될까?”; that new local edit remains intact and is not part of version 288. Its observed hash was `33937dd2166b22ba17fe38e8e8e6a1492b5454a39236a8aaf8e30e92d3211804`. The root English manuscript received only the requested introduction translation. Nine website publication files were synced using a checked binary patch; unrelated dirty work and all other primary analytics-label values were preserved.

Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-pair-introduction.png`. Matching archive: `chapter-nine-pair-introduction-site.tar` in that directory.


## 2026-11-11 — Chapter 9 complement and table application prose

Published Sites version 289 from source `1c633099948804e762454f7695bd2324a7bea2c6`. Existing public deployment `appgdep_6af444a80d408191ad87f30dcec8d2ee` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Replaced the complement heading/body with the author's “각 숫자마다 어떤 숫자를 찾으면 될까?” wording and added “숫자를 찾을 때 표를 어떻게 적용할까?” immediately afterward. The complement semantic ID remains unchanged; the new topic is `thinking-logically-table-application`. Added matching English translations and bilingual analytics/feedback labels, preserving every unrelated historical label and all existing anchors. Both web editions now have 47 topics / ten Thinking topics. All eight visual attachments and renderer/model files are unchanged. Updated public manuscripts and deterministic 24-file ZIP. Root English has the two requested translated conceptual introductions while retaining its existing technical paragraphs and examples; root Korean was already authored and was never written by this task.

All 196 Node tests, TypeScript, production build and diff whitespace checks passed. Independent review confirmed exact Korean parity (web copies trim trailing whitespace), bilingual order/schema/labels, all eight displayed C blocks' executable-token parity, unchanged aliases/visuals and all ZIP entries. Browser verified both published languages and matching tutor/feedback context for both topics, with 47 headings/eight visuals. Live manuscript/ZIP downloads match local publication bytes. Existing public audience retained.

All 967 recorded lab/presentation source hashes and the author Korean hash `50e4f04ca329eb59747fa5619efcf2ce2995cf76c53659dd74323f353607070e` remained unchanged. Eight verified website files were synced to the dirty primary checkout via a checked binary patch; unrelated work and other labels were preserved. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-table-application.png`. Matching archive: `chapter-nine-table-application-site.tar` in that directory.


## 2026-11-11 — Simple brute-force pair visual

Published Sites version 290 from source `0316bb67a149c3341993760758c36f92330d397d`. Existing public deployment `appgdep_6af44c07824c8191ba800c2f2c6cced3` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “숫자 쌍을 하나씩 확인하기” / “Try one pair at a time” under the existing two-positions topic. The explicitly small teaching fixture is [1,2,3,4], target6. Frozen model constants, readonly BruteForcePairFrame and pure bruteForcePairFrames generate exactly six deeply frozen frames: ready →2+1=3 →3+2=5 →3+1=4 →4+3=7 →4+2=6 found. One Check next pair click performs one comparison. Current/earlier numbers retain their values and receive localized role labels with solid/dashed outlines; no accumulated miss marks, numeric indices, counters, input, connectors or playback appear. Only Next pair/Restart controls are present; completion disables Next, and Restart restores the empty ready state. Each role label and every feedback variant reserves its actual wrapped height with inert, aria-hidden sizing copies. A dedicated matching Card header avoids adding an empty second live region.

All 199 Node tests, including26 model tests and the existing real-C oracle, TypeScript, production build and diff whitespace checks passed. Independent AST review confirmed all20 pre-existing model functions and30 visual/helper bodies byte-identical; only dispatcher gained its required branch. All eight old visual attachments remain; total now nine, with47 bilingual topics. No manuscript, download, label, anchor or protected source changed.

Browser-verified all six states in both languages at1280/375/320px viewport widths: exact pair order, first match stop, disabled completion button, restart, Enter/Space and visible focus, exactly two controls/one polite region/no inputs, four permanent cells in one row, no page overflow, inert sizing copies and fixed cell geometry. Every state retained the same panel height and following-topic position at its width/language. Heights: KO489px/EN513px desktop;553px both at375px; KO601px/EN615px at320px. Live Korean publication replay confirmed all five equations and completion with489px height retained.

All561 recorded protected source/manuscript/download reference hashes were preserved. Only five verified files were synced into the dirty primary website checkout using a checked binary patch; unrelated work and the existing public audience remain intact. Isolated source is clean; owned preview server stopped and viewport override reset. Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-brute-force-pairs-live.png`. Matching archive: `chapter-nine-brute-force-pairs-site.tar` in that directory.


## 2026-11-11 — Simple complement calculation visual

Published Sites version 291 from source `4b8182b1f3fbea465b91ab5cba2c261a38c63a35`. Existing public deployment `appgdep_6af44f03e028819190f641d9c20d3c0c` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “어떤 숫자가 필요할까?” / “Which number is needed?” under the existing complement topic. It reuses frozen [1,2,3,4] and target6, defaulting to4 selected and6−4=2. Four native number buttons immediately calculate needed5/4/3/2, with one pressed/outlined current number and localized fixed-space Current number labels. The needed result is neutral bold text under Number to look for; one polite region announces the subtraction and instruction to look among numbers already seen. There is no matching-cell highlight, found/absent claim, checkmark, input, index, counter, stepping, restart, table, connector or playback. Current-label and all four feedback sizing variants are inert and aria-hidden. Added derived ComplementExampleNumber and pure complementFor, without changing the fixture or prior algorithms.

All201 Node tests (including28 model tests and the real-C oracle), TypeScript, production build and diff whitespace checks passed. Independent AST review confirmed all21 existing model function bodies and34 existing visual/helper bodies byte-identical; only dispatcher gained its necessary branch. Existing nine visual attachments remain, total now ten; all47 topics, anchors, labels and downloadable files remain unchanged.

Browser-verified all four choices plus repeated3 selection in Korean/English at1280/375/320px: default4, exact arithmetic, Enter/Space and visible focus, single pressed selector, neutral self-complement display, one live region, four controls/no other inputs, one-row geometry, inert sizing variants, no page overflow, and stable panel/following-content positions. Heights:457px desktop in both languages; Korean457px at375px and481px at320px; English521px at both mobile widths. Published EN/KO defaults and all four live Korean calculations were verified, retaining457px height.

All560 recorded protected source/web-manuscript/download reference hashes remained unchanged. Root Korean was never written by this task: the author independently removed two later Thinking topics and started revising efficiency prose during publication; those local edits remain intact and are intentionally not included in this UI-only version. Observed author hash: `092d615137f9e295a335e0385defb68889d00034bc3659dbd41a4d7611cc7014`. Only five verified website files were synced via a checked binary patch; unrelated work/public audience preserved, isolated source clean, preview stopped, viewport reset. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-complement-live.png`; matching archive `chapter-nine-complement-site.tar` in that directory.


## 2026-11-11 — Guided two-sum table visual

Published Sites version292 from source `c0adfd20e997ac873924172a2197feecbea438be`. Existing public deployment `appgdep_6af453c7a6748191928ce29e09ed6adc` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “먼저 찾고 없으면 저장하기” / “Look up first, then store” under the existing table-application topic. Uses the existing four-number teaching fixture [1,2,3,4], target6, and a clearly labeled four-slot example with value%4 mapping. Pure twoSumTableFrames returns eight deeply frozen frames and separate immutable slot snapshots: ready1 →lookup5 miss →store1/advance2 →lookup4 miss →store2/advance3 →lookup3 miss →store3/advance4 →lookup2 found. Lookups compare stored keys with the complement; current3 is searched before storage and cannot match itself. Final table is[empty,1,2,3];4 is never inserted. Only dynamic Look for N/Store N and Restart controls are visible. Input/current and lookup labels, all feedback and all action labels reserve their actual wrapped space via inert, aria-hidden sizing variants. Store steps clear the lookup outline while advancing the input/calculation; final lookup retains slot2 and disables the primary control. One polite region announces each current/complement/action result. No indices on inputs, counters, editing, playback, connectors or separate modulo calculation appear.

All204 Node tests (31 model tests including the actual-C oracle), TypeScript, production build and diff whitespace checks passed. Independent review confirmed all22 existing model functions and36 prior non-dispatcher visual/helper bodies byte-identical; only dispatcher gained its necessary branch. All ten old visual attachments,47 topics, anchors, labels, manuscripts/downloads and fifteen-bucket lab models remain unchanged. Total visual attachments now eleven.

Browser-verified all eight frames in Korean/English at1280/375/320px: exact seven operations, retained table contents, key self-pair safeguard, no store4, one active lookup slot, clearing highlights on store, native Enter/Space with visible focus, final disabled action, completed/mid-story restart, two visible controls/one live region, inert variants, no other inputs, no page overflow, and fixed cells/buttons/following-topic positions. All eight announcements are distinct. Heights:657px desktop in both languages; Korean657px at375px /697px at320px; English697px at375px /713px at320px. Published EN/KO defaults and full Korean replay were verified through2+4=6, retaining657px height and final slot2 highlight.

All560 recorded protected source/web-manuscript/download reference hashes remained unchanged. Root Korean was never written by this task; independent author efficiency revisions remain intact (observed hash `abcdd1aacd434ed99d51c94fb8bd4423036a46d4d210bc0efec8b5432ac120df`) and were not imported into this UI-only version. Five verified files were synced into the dirty primary website checkout using a checked binary patch; unrelated work/public audience preserved. Isolated source clean, owned preview stopped, viewport reset. Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-two-sum-table-live.png`; matching archive `chapter-nine-two-sum-table-site.tar` in that directory.


## 2026-11-11 — Revised Chapter 9 opening and efficiency prose

Published Sites version293 from source `c580d7aad047f727049ebca4619b216a72e2ff99`. Existing public deployment `appgdep_6af460e6d45c8191abdae18190928dbc` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Applied the user's supplied Korean first two sections and matching English translations. Thinking now has eight topics, ending at table-application; Efficiency has four plain-language topics for linear search, direct addressing time/space, collision-chain degradation and brute-force/hash two-sum time/space. Bilingual schema now has45 topics with counts[8,4,12,4,4,5,8]. New semantic IDs are linear-search-cost and direct-address-cost; retained chain-work and pair-comparisons meanings/headings are updated. Preserved every historical analytics label key, adding the new two labels. Retired search-before-insert anchor redirects to table-application; pair-searches and expected-and-worst redirect to efficiency/pair-comparisons; reset-and-space redirects to C table initialization. All prior aliases remain, ten total.

Preserved all eleven visuals, moving only the detailed two-sum attachment to calculating-efficiency-pair-comparisons. Visual UI/model files and every existing function body remain byte-identical. Both web Glossary-and-later tails and all eight annotated C blocks are unchanged; C executable tokens match actual lab. Root English first two sections now match the translations, with its original Glossary-through-EOF preserved byte-for-byte. Root Korean was never written. Updated public EN/KO manuscripts and deterministic24-entry ZIP.

All204 Node tests (including31 model tests, C oracle, ZIP extraction/build, bilingual labels/structure and aliases), TypeScript, production build and diff whitespace checks passed. Independent review confirmed exact supplied Korean wording, bilingual order/labels, preserved historical keys/tails/models/UI, eleven attachments and every ZIP entry. Browser verified published EN/KO topic structure,45 topics/eleven visuals, desktop/mobile text without page overflow, all ten alias parent targets and the four newly retired anchor landings (~96px below viewport top). Relocated detailed demo completed via End on its slider: exact ordered answers{4,5} in both panels,11 brute-force comparisons versus1 hash-key comparison. Viewport override reset and live Korean efficiency page retained as deliverable.

All509 recorded protected source/model/UI reference hashes stayed unchanged. The author independently refined root Korean wording during the task (including 크기→용량 after the message was supplied); those local revisions were preserved rather than overwritten or published beyond the explicit request. Last observed author SHA `6da0d2700c9984b19b67f2372a25096a75560a6dc36c4aa20177803136c1ffdb`. All nine website publication files were synced via a checked binary patch into the dirty primary checkout; unrelated label values/work and public audience preserved. Three live downloads exactly match publication bytes; isolated source clean. No preview server was started for this prose/attachment update. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-efficiency-prose-live.png`; matching archive `chapter-nine-efficiency-prose-site.tar` in that directory.


## 2026-11-11 — Linear-search efficiency comparison

Published Sites version294 from source `fada5e233b260bd0ea438344582d206b576954cc`. Existing public deployment `appgdep_6af4734c12008191ae666a324f59eb12` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “데이터가 많아지면 확인도 늘어난다” / “More items, more checks” under calculating-efficiency/linear-search-cost. The fixed scenario explicitly states that the wanted value is absent from both four-item and eight-item groups. Anonymous cells carry only × marks; sizes and per-group check counts are the only visible numbers. One Check next click advances each unfinished group; the short group freezes after four checks, including its last-checked outline and Not found label, while the long group continues through eight. The final conditional caption says twice as many items means twice as many checks when the value is absent. Completion disables Next; Restart clears counts/marks/outlines/completion/final feedback. No selector, input, timer, playback, slider or additional scenario appears.

Added frozen sizes[4,8], readonly LinearSearchEfficiencyFrame and pure linearSearchEfficiencyFrames, producing nine deeply frozen snapshots. Check counts are[0,0]→[1,1]→[2,2]→[3,3]→[4,4]→[4,5]→[4,6]→[4,7]→[4,8]. Each group records size/count/last checked position/completion. Both per-row completion labels and all nine feedback variants reserve their actual wrapped height with inert, aria-hidden sizing copies. One polite status announces both groups' counts/states and the current instruction. Outlines are described as last checked, including after completion. Shared eight-column desktop / four-column mobile grids keep cells equal-sized, with the larger group wrapping to two rows on mobile.

All207 Node tests (34 model tests including unchanged actual-C oracle), TypeScript, production build and diff whitespace checks passed. Independent function-hash review confirmed all23 prior model functions and41 prior non-dispatcher visual/helper bodies unchanged; only dispatcher gained its necessary branch. Existing eleven visual attachments remain, twelve total;45 topics, historical anchors/labels, manuscripts, downloads and protected sources are unchanged.

Browser-verified all nine frames in KO/EN at1280/375/320px: exact per-row counts/marks/last outlines/completion, frozen completed short row, native Enter/Space with visible focus, final disabled action, completed and mid-search restart, equal cell widths, responsive row counts[1,1]desktop/[1,2]mobile, two controls/one polite region, nine distinct announcements, inert sizing copies/no other inputs/page overflow, and identical cell/button geometry/panel/following-topic positions across all states. Heights:589px desktop both languages; Korean685px at375/320px; English709px at375px and733px at320px. Published EN/KO ready states and full Korean eight-click replay verified final4/8 counts and589px retained height.

All561 recorded protected source/manuscript/download reference hashes stayed unchanged. Only five verified files were synced into the dirty primary website checkout via a checked binary patch; unrelated work and public audience preserved. Isolated source clean, owned preview stopped and viewport reset. Live screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-linear-efficiency-live.png`; matching archive `chapter-nine-linear-efficiency-site.tar` in that directory.


## 2026-11-11 — Chapter 9 glossary and hash-function rules

Published Sites version295 from source `efaf6a3a0a61b77a14bc669b45d630cb8a17f733`. Existing public deployment `appgdep_6af4765b12b08191b4e3f4eb74deb7a4` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Applied the supplied eleven-term Korean glossary with English terms in parentheses and matching English definitions: key, direct-address table, hashing, hash function, hash value, hash table, bucket/slot, collision, chaining, open addressing/probing and brute force. Retained existing semantic IDs key/bucket/collision/separate-chaining; added seven new glossary IDs. Updated invariant/rules heading and first two rule/benefit paragraphs to hash-function range validity and deterministic results. Remaining two invariant topics and all later web content are byte-identical. Also synchronized the requested table-capacity wording in the collision-cost paragraph. The bilingual schema now has44 topics, counts[8,4,11,4,4,5,8].

Preserved all historical label keys; updated only current glossary/rule heading values and added seven labels. Added eight retired glossary anchor aliases: payload/node-index→C node-storage; complement→Thinking complement; allocation-counter→C node-allocation; prepend/duplicate-key→C head-insertion; sentinel→C key-lookup; status-and-index→post-increment syntax. All ten previous aliases remain,18 total. All twelve visuals/attachments and all model/UI functions remain unchanged. Public manuscripts and deterministic24-entry ZIP match the web editions.

Root Korean already contained the new glossary; only its first two invariant blocks were updated, preserving the entire prefix/trailing spaces and broken-rules-through-EOF. Root English glossary table was replaced with the eleven translated H3 definitions and a two-topic Invariant section inserted before its existing Coding Plan; only the two requested capacity wording substitutions were made elsewhere. Root EN Coding Plan-through-EOF and every C block were preserved byte-for-byte. Agent used concurrent reread checks before bounded writes.

All207 Node tests (including34 model tests/real-C oracle, bilingual schema/labels, aliases and ZIP C build), TypeScript, production build and whitespace checks passed. Independent review confirmed exact supplied Korean, English translations,44-topic parity, historical labels,18 active alias targets, all twelve visuals, preserved tails/functions, eight displayed C blocks' executable-token parity, all24 ZIP entries and protected download bytes. Browser verified live EN/KO glossary and rules,44 topics/twelve visuals, desktop/mobile wrapping without page overflow, all eight new glossary alias parent targets and representative native landings (~96px below viewport top). Final screenshot captures the new rules and guarantees. Viewport reset and Korean Invariant page marked deliverable.

All509 recorded protected source/model/UI hashes remained unchanged. Eight verified website files were synced via a checked binary patch into the dirty primary checkout; unrelated labels/work and public audience preserved. Three live downloads exactly match publication bytes; isolated source clean. No preview server was started for this prose-only update. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-glossary-rules-live.png`; matching archive `chapter-nine-glossary-rules-site.tar` in that directory.


## 2026-11-11 — Direct-address-table efficiency comparison

Published Sites version296 from source `5af1ac532c34d29e338850ed39c7b06916482ccc`. Public deployment `appgdep_6af47cf1aae48191ac4b2dc2b66927f7` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “어느 표든 한 칸만 확인하기” / “One check in either table” only under calculating-efficiency/direct-address-cost. Two prepared tables cover allowed keys0–3 and0–7, with recorded locations only for keys1/3. One lookup of missing key2 highlights only entry2, labels it Checked, reports one check and Not found in both tables, and disables Lookup. Restart clears lookup marks/counts/results/final feedback while retaining occupancy. The final caption explains equal one-slot lookup work and doubled table capacity for the wider key range. Four/eight-column responsive grids preserve equal cell sizes; eight-slot table wraps into two rows on mobile. No scanning, insertion, selectors, inputs or playback.

Added independent frozen numeric fixtures and readonly DirectAddressEfficiencyFrame/directAddressEfficiencyFrames, returning exactly two deeply immutable states. Preserved the symbolic direct-address model and all24 prior model functions,44 prior non-dispatcher UI/helper bodies, and twelve existing visual attachments (thirteen total). Topic/anchor/feedback/tutor contexts,44-topic content, labels and historical aliases are unchanged. Independent snapshot review confirmed36 protected lab/PPT files and29 manuscript/download artifacts remain byte-identical.

All210 tests (37 model tests including the existing actual-C oracle), TypeScript, production build and diff whitespace checks passed. Browser-tested KO/EN at1280/375/320px: prepared occupancy, exactly one checked entry/count, Not found, completion disabling, native Enter/Space and restart, visible focus, one polite region/two controls/no inputs, inert aria-hidden sizing, no page overflow, equal cell widths and responsive row counts[1,1]desktop/[1,2]mobile. Panel height, cell geometry and following-topic offset were identical before/after lookup/restart. Panel heights:592px desktop both languages; KO756/780px and EN780/804px at375/320px. Verified live EN lookup/restart and KO completed lookup. Viewport reset and Korean page marked deliverable.

Only five verified source/test files were synced via checked binary patch into the dirty primary website checkout; unrelated work and public audience preserved. Isolated source clean; owned preview server stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-direct-address-efficiency-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-direct-address-efficiency-live.png`.


## 2026-11-11 — Simplified direct-address efficiency to one table

Published Sites version297 from source `001652bb3392fd4ac9b56c211b17f445e847a96e`. Public deployment `appgdep_6af47fb3c464819180ebd1464a3b5b50` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Applied user feedback that the comparison was hard to comprehend and one table is enough. Replaced the two-table visual with “한 칸만 확인하기” / “Check just one slot”: one four-slot table0–3, occupied keys1/3, a single lookup of missing key2, and Restart. Removed the second table, all comparison/range-doubling copy, and the oversized shared eight-column grid. Four cells remain in one row at every width. Ready text explains checking slot2 directly; completion explains that the missing recorded location establishes absence in one check. The result retains only slot2's outline/Checked label, count1, and Not found. Restart restores the ready state and retains occupancy.

Simplified DirectAddressEfficiencyFrame to singular frame.table and replaced the sizes fixture with deeply frozen numeric slots. Exactly two independent deeply frozen frames remain. Updated the same three dedicated tests. Only three functions changed: directAddressEfficiencyFrames, DirectAddressEfficiencyFeedback, and DirectAddressEfficiencyLesson; all other model/UI/helper functions and all13 attachments are byte-identical. Independent review verified36 protected lab/PPT files and29 manuscript/download artifacts unchanged.

All210 tests, TypeScript, production build and diff whitespace checks passed. KO/EN browser QA at1280/375/320px verified one table/one row, one checked key/count, retained occupancy, completion disabling, native Enter/Space/visible focus, restart, one polite region/two buttons/no inputs, inert aria-hidden sizing and no overflow. Panel/cell/following-topic geometry stayed fixed across ready/complete/restart. Panel heights:400px desktop both languages (previous592px); KO424px at375/320px, EN448/472px at375/320px. Live Korean lookup/restart and final completed state verified. Viewport reset; Korean page marked deliverable.

Only three verified files were synced via checked binary patch into the dirty primary checkout. Unrelated work/public audience preserved; isolated source clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-single-table-efficiency-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-single-table-efficiency-live.png`.


## 2026-11-11 — Simplified linear-search efficiency to one row

Published Sites version298 from source `4946a58b2e4fd623d219b86f0234fcc5e97ed6d5`. Public deployment `appgdep_6af481cbf5108191b77eaf0e904a95b5` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Applied user feedback that the linear-search efficiency visual also needs only one table/group. Replaced the four-versus-eight comparison with “모든 칸 확인하기” / “Check every box”: one row of four anonymous memory boxes at every width. Each Check next checks exactly one next box, leaves × marks on previous misses, retains a last-checked outline, and increments the single counter0→4. Only the fourth check reports Not found and disables Next. Restart clears the row, counter, completion and feedback. The caption states the wanted value is absent; final feedback explains that every box had to be checked. Removed all two-group/doubling language and the second row/group.

Flattened LinearSearchEfficiencyFrame to readonly size4/checkedCount/lastCheckedIndex/complete and replaced the paired sizes fixture with SIZE4. The pure model returns exactly five independently frozen frames. Updated only its three dedicated tests and import destructuring. Independent review confirmed only four functions changed: linearSearchEfficiencyFrames and linearEfficiencyMessage/Feedback/Lesson. All24 other model functions and44 other UI/helper functions, including the direct-address visual/dispatcher, are byte-identical. All36 protected lab/PPT files and29 manuscript/download artifacts still match the fresh baseline hashes.

All210 tests, TypeScript, production build and diff whitespace checks passed. KO/EN browser QA at1280/375/320px verified all five states, exactly one new miss per click, sequential order, completion only at four, single row/group/count, native Enter/Space and visible focus, complete and partial restart, five unique polite announcements in one region, inert aria-hidden sizing, two controls/no inputs and no page overflow. Panel/cell/following-topic positions stayed identical across checking/completion/reset. Heights:328px desktop both languages,352px mobile both languages. Live Korean full sequence/restarts and final completed state verified. Viewport reset; Korean page marked deliverable.

Three verified files were synced into the dirty primary website checkout with a checked binary patch. Unrelated work/public audience preserved; isolated source clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-single-linear-efficiency-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-single-linear-efficiency-live.png`.


## 2026-11-11 — Collision-cost linked-list visual

Published Sites version299 from source `687e82df813117e13f30135d50f27006d4ae6256`. Public deployment `appgdep_6af48b0f5fec8191be481c70cc91ce97` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “한 칸에서 여러 번 확인하기” / “One slot, several checks” only beneath calculating-efficiency/chain-work, retaining its topic anchor and tutor/feedback context. One bucket0 leads through four anonymous nodes to End. Intro explains that the stored values and absent wanted value all map to0. Each Check next compares one node, adds ×, retains the last-node outline and increments the comparison count. The fourth comparison also reaches End, underlines its marker, reports Not found and disables Next; there is no fifth End comparison. Restart clears the complete or partial search. Final feedback uses the approved bilingual statement that values sharing one index must be searched one at a time. No values/indices within nodes, selectors, inputs, insertion or playback.

Added frozen COLLISION_COST_CHAIN next links[1,2,3,null], HEAD0, readonly CollisionCostFrame and pure collisionCostFrames(). Actual next-link traversal yields exactly five independently frozen frames: ready0/null/false, checking1/node0, checking2/node1, checking3/node2, not-found4/node3/endReachedtrue. Three focused tests cover exact traversal/counts, deep immutability, independent repeated calls and restart. All25 pre-existing model functions and46 non-dispatcher UI/helper functions remain byte-identical; only the dispatcher gained its branch. Existing13 attachments remain,14 total. Independent review verified36 protected lab/PPT files and29 manuscript/download artifacts unchanged.

All213 tests (40 model tests, including unchanged actual-C oracle), TypeScript, production build and diff whitespace checks passed. KO/EN browser QA at1280/375/320px covered all five states, four checks with no fifth click, only final Not found/End underline, last-node outline, five distinct polite announcements in one region, two native controls, Enter/Space with visible focus, partial/complete restart, inert aria-hidden sizing and no page/chain overflow. Narrow decorative arrows and four equal flexible nodes remain in one horizontal row at320px (node widths34.65px KO/31.86px EN). Panel/node/bucket/link/end/following-topic geometry stayed identical across all checks and resets. Heights:360px desktop both languages; KO408px at375/320px; EN432/456px at375/320px. Live Korean full traversal/restarts and final completion verified. Viewport reset; Korean page marked deliverable.

Only five verified source/test files were synced into the dirty primary website checkout using a checked binary patch. Unrelated edits and public audience preserved; isolated source clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-collision-cost-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-collision-cost-live.png`.


## 2026-11-11 — Hash-only two-sum efficiency visual

Published Sites version300 from source `c6091fed36f880099f7670ac05c96de7d92c7404`. Public deployment `appgdep_6af494ba7a0c81918c6b587a73d9954e` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “숫자마다 한 번 찾기” / “One lookup per number” at calculating-efficiency/pair-comparisons. One fixed row[1,2,3,4], separate target10 and explicit no-pair caption show four complete lookup-then-store operations. Only Next number and Restart appear. The single Table lookups counter advances0→4; each processed number retains the Current number outline/label. Fourth click disables Next and adds the exact approved bilingual completion text. Restart clears selection/count/completion. Qualified time and proportional-space captions remain visible; the new visual has no table diagram, equation, comparison counter, input, selector or playback. Moved the existing detailed TwoSumLesson/AlgorithmTrace intact to c-code/hash-two-sum. All14 existing visuals remain,15 attachments total; topic anchors, labels, tutor/feedback context and historical aliases are retained.

Added separate TWO_SUM_EFFICIENCY_TARGET10, readonly TwoSumEfficiencyFrame and pure twoSumEfficiencyFrames(), reusing the frozen four values without changing the target6/complementFor helpers. Local Set.has/add implements lookup before insertion; immutable ordered snapshots record ready plus complements9/8/7/6, counts1–4, stored prefixes[1]→[1,2,3,4], and completion only on the last step. Three tests cover the exact five-state progression, no pair, before-store lookup, deep freezing, fixture preservation, repeated calls and restart. Independent function/hash review confirmed every old model/UI helper body unchanged except the necessary dispatcher branch, plus all36 protected lab/PPT files and29 manuscript/download artifacts byte-identical.

Final216 tests (43 model tests, including unchanged actual-C oracle), TypeScript, production build and diff whitespace checks passed. Browser KO/EN at1280/375/320px covered all five states, exactly one lookup per number, default no highlight, current labels, final disabling/exact message, complete and partial restart, native Enter/Space/visible focus, one polite region/five unique announcements, inert aria-hidden sizing, one row, no extra controls/diagram and no overflow. Panel/cell/control/following-content positions remained fixed. Panel heights:KO464/528/572px and EN484/564/632px at1280/375/320px. Relocated English and Korean detailed demos verified native slider End/Home/restart, target0 counts11 brute-force versus1 hash comparison, answer{4,5}, and out-of-range target rejection preserving the active trace. Live Korean full cost trace/restarts and completed lookup4 state verified; viewport reset and Korean page marked deliverable.

Only five verified source/test files were synced into the dirty primary website checkout with a checked binary patch; unrelated work/public audience preserved. Isolated source clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-two-sum-efficiency-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-two-sum-efficiency-live.png`.


## 2026-11-11 — Same key, same index

Published Sites version301 from source `69725d0b7ef2c9e7fded92f93ccd912a5f1a69cc`. Public deployment `appgdep_6af4f066af5c819189869a3aeb35b52c` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “같은 키는 같은 번호로” / “Same key, same index” only beneath invariant/rules, preserving its anchor and tutor/feedback context. The fixed key△ and small table with indices0–2 illustrate range validity and deterministic output. First calculation returns1 and highlights slot1; repeating returns1 in a second external readout and retains the same highlight. Table cells remain empty throughout. Primary action changes Calculate index→Calculate again and disables after the second result; Restart clears both readouts/highlight and restores the initial label. The visual has only two native controls, one polite status and no inputs, selectors, counters, playback, insertion/find or invalid-function scenarios.

Added HASH_RULE_KEY/HASH_RULE_INDICES, readonly HashRulesFrame and pure hashRulesFrames(), yielding exactly three independently deeply frozen states: ready[null,null], first[1,null], repeated[1,1]. Each calculation separately calls the unchanged symbolicHashLookup(triangle).index. Three tests cover exact progression/range, established mapping, deep tuple/frame/trace immutability, fixture preservation, repeated calls and restart. Existing27 model functions and52 non-dispatcher UI/helper bodies are byte-identical; only dispatcher/renderer integrations gained branches. Existing15 visuals remain,16 attachments total. Independent SHA-256 review verified36 protected files, including scanning all presentation extensions, and29 manuscript/download artifacts unchanged; no additional presentation binaries were found.

All219 tests (46 model tests including unchanged actual-C oracle), TypeScript, production build and diff whitespace checks passed. KO/EN at1280/375/320px browser-tested ready/first/repeated states, exact results and index1 highlight, continuously empty cells, primary label change/disabled completion, partial/complete reset, native Enter/Space and visible focus, one polite region/three distinct announcements, two controls, no extra input/overflow and one row of three slots. Inert aria-hidden alternatives reserve result numbers, all feedback variants and both primary labels; the latter use text-only spans inside the real button. Panel/cell/readout/button/following-content positions remain identical across all states and resets. Panel heights444px in KO/EN at1280/375px; at320px458px KO and482px EN. Live Korean full sequence/restarts and final two-result state verified. Viewport reset and Korean page marked deliverable.

Only five verified source/test files were synced via checked binary patch into the dirty primary website checkout. Unrelated work and public audience preserved; isolated source clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-rules-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-rules-live.png`.


## 2026-11-12 — Store, then find again

Published Sites version302 from source `a346d19e9f66a0a4cea131f505774b727b60181e`. Public deployment `appgdep_6af59bf448dc8191b36deba2a3a995de` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “저장하고 다시 찾기” / “Store, then find again” only beneath invariant/benefits, preserving its anchor and tutor/feedback context. A fixed△ and one three-slot table show ready empty→store△at1→recompute1/find the stored△. Find compares the own stored key before showing ✓ beside the retained△. The primary action changes Store△→Find△ and disables after success; Restart clears the whole demonstration. The single-value caption and approved bilingual final takeaway explain returning to the slot where the value was stored. No counters, selectors, inputs, extra result readouts, playback or invalid cases were introduced.

Added readonly HashRetrievalFrame and pure hashRetrievalFrames() with three independently deeply frozen snapshots recording phase/index/slots/matched. Two separate calls use only the existing symbolic mapping’s index; the match is computed against the demonstration’s own stored slot rather than the unrelated lookup fixture’s storedKey/matches fields. Three tests cover state order, exclusive slot1 storage, repeated index equality, own-key comparison, retained values, deep freezing, repeated calls and restart. All28 pre-existing model functions and54 non-dispatcher UI/helper bodies are byte-identical; only dispatcher/renderer integration branches changed. Existing16 visuals remain,17 total. Independent review confirmed36 protected/presentation files and29 manuscript/download artifacts unchanged.

All222 tests (49 model tests including unchanged actual-C oracle), TypeScript, production build and diff whitespace checks passed. KO/EN at1280/375/320px browser-tested all three states, own-key match/✓ only after Find, retained glyph and identical stored/found glyph/badge geometry, primary label/disabled changes, complete/partial reset, native Enter/Space and visible focus, one polite region/three distinct announcements, two native controls, inert sizing alternatives, no extra inputs/overflow, and one row of three slots. Panel/cell/control/following-topic positions stayed identical across states and resets. Panel heights392px desktop both languages; KO416/440px and EN440/464px at375/320px. Live Korean full sequence/restarts and completed match state verified. Viewport reset; Korean page marked deliverable.

Only five verified source/test files were synced through a checked binary patch into the dirty primary website checkout. Unrelated edits and public audience preserved; isolated source clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-retrieval-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-retrieval-live.png`.


## 2026-11-12 — When the index is wrong (visual only)

Published Sites version303 from source `e8406606552e606f21e299a7baefb55788ac052f`. Public deployment `appgdep_6af5a4baa9ac81918b7ab8a2336fcc21` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “번호가 잘못되면” / “When the index is wrong” only beneath invariant/broken-rules. This follows the user's explicit Visual only choice: existing prose, manuscripts and downloads are unchanged. One prepared three-slot table retains△at1 and fixed lookup key△. Initially no example is selected, no lookup index is displayed and no slot is outlined. Two native pressed-state example buttons immediately show deliberately broken lookup results: outside-table3 highlights/accesses no slot and explains that slot3 does not exist; changed-index2 outlines only empty slot2 with× and explains that this missed△already stored at1. Switching clears the old marker; repeated selection is idempotent. No fourth slot, Find, Restart, stepping or playback is added.

Added frozen HASH_FAILURE_SLOTS, HashFailureCase, readonly HashFailureView and pure hashFailureView(). Null gives the ready view; index3 fails the bounds check before any indexed slot read and returns checkedIndexnull; index2 reads/compares only valid slot2. Every view preserves the same frozen prepared table and the valid△→1 mapping remains unchanged. Three tests cover all views/bounds/retained data, deep freezing, repeated selection and switching. Independent hashes confirmed all29 old model functions and57 non-dispatcher UI/helper functions unchanged; only the dispatcher/renderer gained branches. Existing17 visuals remain,18 attachments total. All36 protected/presentation files and29 prose/manuscript/download artifacts match baseline bytes.

All225 tests (52 model tests including unchanged actual-C oracle), TypeScript, production build and whitespace checks passed. KO/EN browser QA at1280/375/320px checked ready, both failure states, repeated Enter/Space activation, back-and-forth switching, mutually exclusive pressed states and visible focus; unchanged△, exactly three cells/one row, no extra actions/inputs, one polite region/three distinct statuses, inert hidden glyph/×/index/feedback sizing, and no page overflow. Panel/cell/index-readout/button/following-topic positions stayed identical across all selections. Panel heights448px desktop both languages; KO448/472px and EN488/488px at375/320px. Live Korean both-case/repetition/switching verification passed and the changed-index state was captured. Viewport reset; Korean page marked deliverable.

Only five verified source/test files were synced using a checked binary patch into the dirty primary website checkout. Unrelated edits/public audience preserved; isolated source clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-failures-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-failures-live.png`.


## 2026-11-12 — Follow the hash code (visual only)

Published Sites version304 from source `8a61dcb210c8e7f10edc27682f38918d63b4b041`. Public deployment `appgdep_6af5adf4ec90819180f303b6e7e21956` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “해시 함수 코드 따라가기” / “Follow the hash code” only beneath invariant/preserve-rules, retaining its anchor and tutor/feedback context. Fixed key−16, TABLE_CAPACITY15 and valid returned range0–14 remain visible beside the actual five-line C body. Three Next actions highlight the assignment, entire conditional block, then return; one value readout changes blank→−1→14→14✓. Both early values use the intermediate label; only Return uses Returned index and ✓. The negative intermediate is neutral and performs no table access. Next disables on Return; complete and partial Restart clear every mark/value/feedback while retaining the fixed input. Exact bilingual final captions, only two native controls, one polite region, background-only code highlights and CSS soft wrapping are included; no prose, manuscripts or downloads changed.

Added frozen HASH_CODE_LINES/HASH_CODE_KEY, readonly HashCodeFrame and pure hashCodeFrames(), producing four frozen states using the existing capacity. Four focused tests cover exact state/arithmetic/range and model agreement, executable-token parity with the actual hash_func body, immutability, repeated calls and restart. All30 previous model functions and59 non-dispatcher UI/helper bodies are byte-identical; only necessary dispatcher/renderer branches changed. Existing18 visuals remain,19 attachments total. Independent review verified all36 protected/presentation files and29 prose/manuscript/download artifacts unchanged, including presentation-extension scans.

All229 tests (56 model tests including the actual-C reference), TypeScript, production build and diff whitespace checks passed. KO/EN at1280/375/320px browser-tested all four states, exact mounted code text, logical stage highlights, intermediate/returned labels, return-only checkmark, disabled completion, complete/partial restart and full replay, native Enter/Space/visible focus, one polite region/four unique statuses, inert aria-hidden sizing and no page/code overflow. Narrow320px code soft-wraps without text/token changes. Panel/code/readout/badge/control/following-topic positions remain identical through steps/reset/replay. Panel heights:536.5px desktop both languages; KO558/634px and EN582/658px at375/320px. Live Korean full sequence/restarts/replay passed and the returned14 state was captured. Viewport reset; Korean page marked deliverable.

Only five verified source/test files were synced through a checked binary patch into the dirty primary website checkout; all five match the published source. Unrelated edits and public audience preserved; isolated checkout clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-code-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-code-live.png`.


## 2026-11-12 — Revised Chapter9 prose and eight-step coding plan

User explicitly chose applying the supplied Korean draft to Korean/English web bodies and downloadable manuscripts. Published Sites version305 from source `216ba94e5933a805ad85454e33ef9037226f1479`. Public deployment `appgdep_6af5cda45b548191b916a1cda1139721` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Korean follows the supplied draft through Coding plan, normalizing Markdown/HTML spacing. Updated two-sum efficiency wording, two glossary definitions, and the broken-rules paragraph. Replaced the generic four-topic coding plan with eight authored steps: node design, node array, table capacity/initialization, hash function, insertion, key lookup, brute-force two sum, hash-based two sum. English translations match the Korean sequence and semantics. Removed the superseded invariant/preserve-rules prose heading and moved its unchanged hash-code visual to coding-plan/hash-function. Later C-syntax and C-code manuscript suffixes are byte-identical; all executable lab display tokens remain identical. Web manuscripts and both public downloadable textbooks match; regenerated ZIP keeps the exact member inventory and changes only the two textbook payloads. Separate older root module student manuscripts were not overwritten.

Chapter schema now has47 bilingual semantic topics [8,4,11,3,8,5,8]. Eight new coding-plan IDs/labels were added while every historical label remains unchanged. All18 old aliases remain; five new aliases preserve retired URLs: invariant-preserve-rules→coding-plan-hash-function, coding-plan-storage-plan→coding-plan-node-array, coding-plan-table-plan→coding-plan-head-insertion, coding-plan-pair-plan→coding-plan-hash-two-sum, coding-plan-evidence-plan→c-code-table-initialization. All19 visuals remain attached. Visual implementations, all models and model tests are byte-identical to version304. No database migration or historical analytics edits.

All230 tests, TypeScript, production build and whitespace checks passed, including bilingual schema/topic parity, historical-label retention, annotated C-token parity, protected hashes, ZIP inventory/bytes and extracted C-test buildability. Independent review confirmed exact Korean/English content and all integrations. KO/EN browser QA at1280/375/320px verified47 topics/19 visuals, eight new feedback/tutor scopes, relocated hash-code stages and restart, no overflow and stable panel/control/following-topic positions. Historical invariant-preserve-rules anchor resolves to the new hash-function topic; native language switching preserved that historical hash. Live Korean and English coding plans/broken-rules text verified. Browser-downloaded production EN/KO textbooks and ZIP match verified source bytes exactly. Direct non-browser HTTP checks returned403, so authenticated browser download verification was used instead. Viewport reset and Korean coding-plan page marked deliverable.

All86 snapshotted lab/presentation files remain byte-identical after publication/synchronization. Nine feature files synced via checked binary patch into dirty primary. Eight are byte-identical to isolated source; all Chapter9 entries in subsection-labels.json match while three unrelated existing Chapter3 label differences remain intact. Unrelated work and public audience preserved; isolated source clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-revised-prose-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-revised-prose-live.png`.


## 2026-11-12 — One node, three parts (visual only)

Published Sites version306 from source `c814b384297d4d68bce5133f12b337d341bb7fd9`. Public deployment `appgdep_6af5d43faf14819183d3040a10d2cd31` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “노드 하나에 세 가지 정보” / “One node, three parts” only beneath coding-plan/node-design. An outlined node contains equal contiguous native Key/Data/Next buttons in one row, a narrow permanent decorative arrow, and a neutral Another node box. Key is selected initially. Choosing a field changes its pressed state/outline and exactly one approved localized explanation; only Next colors the arrow. Next has the full localized accessible name Next node location / 다음 노드 위치. No actual values, indices, table, inputs, progress/reset/playback controls, or movement animation were added. One polite status with inert aria-hidden alternatives reserves the longest explanation from the first frame.

Added frozen NODE_FIELDS, NodeField, readonly NodeDesignView and pure nodeDesignView() with a frozen result. Default selection is key; linkHighlighted is true only for next. Three focused tests cover default/all selections, repeated/switch independence and fixture/view freezing. Existing31 model functions and62 non-dispatcher UI/helper bodies remain byte-identical; only dispatcher/renderer integrations gained branches. All19 previous visuals remain,20 attachments total, with47 unchanged bilingual topics and unchanged labels/aliases/tutor/feedback context. Existing chapter paragraphs, web manuscripts, public downloads and ZIP are byte-identical to version305. Independent preservation check matched89/90 snapshot entries, including every protected source/presentation and all isolated manuscripts/downloads; the sole exception was a concurrent user-owned edit to root module_09_hash_table/student/textbook_korean.md, left untouched.

All233 tests (59 model tests including unchanged actual-C oracle), TypeScript, production build and whitespace checks passed. KO/EN browser QA at1280/375/320px verified default Key, every field, repeated Next selection, back-and-forth switching, exact localized descriptions, mutually exclusive pressed states, Enter/Space/visible focus, Next-only arrow color and a neutral destination, one polite region/three distinct statuses, inert sizing, no extra controls/overflow, equal contiguous buttons in one row, and stable panel/diagram/control/following-topic positions. Panel heights190px desktop both languages,214px at375px both languages;320px KO214px and EN238px. Narrowest buttons are47.66–47.67px wide and64px tall. Live Korean and English interaction verification passed; final Korean Next-selected state was captured. Viewport reset and Korean page marked deliverable.

Only five verified source/test files synced with a checked binary patch into the dirty primary website checkout; all five match the published source. Unrelated edits and public audience preserved; isolated checkout clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-node-design-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-node-design-live.png`.


## 2026-11-12 — Full revised Chapter9 manuscript and annotated C examples

Applied the full Korean attachment at /Users/cbk/.codex/attachments/258cab7c-ff7f-4c81-98d4-03e2244a7fed/Pasted text.txt to Korean/English web and downloadable manuscripts. Published Sites version307 from source `66c32b3edaadc17fe1bbb8795f30936211528374`. Public deployment `appgdep_6af5e5a3a3f0819191425ee0a5f94e75` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

The current user-owned root lab now names its allocation counter size, while the frozen public lab still uses hnodes_unused. User explicitly selected “lab.c 사본은 유지하고 원고만 갱신” after being shown the four-identifier difference and the standing AGENTS.md prohibition. No lab.c copy, presentation, or support source was overwritten. The authored display uses size, separately declared capacity enums and literal NUMS_SIZE10; the web Downloads note explains that the protected lab/detailed traces use hnodes_unused and behave equivalently at the supplied capacities. Korean exactly matches the attachment after trailing-whitespace/final-newline normalization. English preserves the equivalent earlier prefix and translates all revised suffix prose/comments; both display programs have identical executable tokens. Separate root manuscripts were not overwritten.

New C syntax has3 topics (integer constant expressions, negative remainder, reverse loop); C code has8 revised headings with detailed author annotations. Schema now45 bilingual topics [8,4,11,3,8,3,8]. All historical heading label values remain;11 active label records added. All old alias keys remain and13 retired syntax/code anchors were added,36 flattened aliases total. All20 visuals remain with wholly unchanged model/UI implementations. Only necessary renderer attachments moved: signed-hash→new-c-syntax-explained/negative-remainder, capacity→c-code/initialize-table, detailed two-sum→c-code/hash-table-two-sum. Existing tutor/feedback contexts use new canonical IDs; language switching preserves historical hashes. No DB migration.

Tests now enforce exact bilingual executable tokens and only the authored counter/enum differences from the protected lab. Both annotated C programs compile/run all unchanged public core C assertions through temporary drivers, checking capacities10/15/10, collisions, duplicate keys, exhaustion preservation, reset/reuse and pair behavior. The actual-C oracle harness was updated to detect either global counter identifier because the current root source changed independently; all model operation sequences and comparison checks remain intact. Final234 tests pass with no skips, including59 model tests and the downloaded ZIP build. TypeScript, production build and whitespace checks pass. A prior full run found the old oracle driver’s hard-coded hnodes_unused reference; the harness fix resolved that failure without altering any C source.

KO/EN browser QA at1280/375/320px verified45 topics,36 aliases,20 visuals, three syntax topics/eight complete C blocks, authored size/constants, download explanation and no page overflow. Existing code blocks retain keyboard-accessible horizontal scrolling for long annotations. Signed INT_MIN gives remainder−8/bucket7; invalid fractional input preserves the trace. Retained detailed target0 trace gives11 brute-force versus1 hash-key comparison and answer{4,5} in both languages. Capacity checks verified ten allocated nodes, unchanged eleventh-insert state, reset retaining fields, node0 reuse with(7,70), and stable1204px desktop visual height. Historical signed-remainder link resolves directly to the new topic and native language switching retains its hash. Live KO/EN text verified; viewport reset and Korean annotated node-list page marked deliverable.

Both public textbooks match rendered manuscripts; ZIP retains the same24 members and changes only the two textbook payloads. Actual browser-downloaded EN/KO books and ZIP match verified source bytes exactly; the downloaded ZIP retains the unchanged public lab.c. The separate individual .c download event timed out in the browser tool; preservation was verified through source hashes and the delivered ZIP. All83 snapshotted protected/support files remain byte-identical, including canonical and public labs and presentations.

Ten feature files synced through a checked binary patch into dirty primary. Nine are byte-identical to published source; all Chapter9 label entries match while unrelated primary labels remain preserved. Public audience unchanged; isolated checkout clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-full-manuscript-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-full-manuscript-live.png`.


## 2026-11-12 — Add one node at the end (visual only)

Published Sites version308 from source `d6883e315df6f3b1a5f6ccfe129d22107dde77b4`. Public deployment `appgdep_6af65edae69c8191bf832a411fe38b0e` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “끝에 노드 하나 추가하기” / “Add one node at the end” only beneath coding-plan/node-array. Four fixed equal-width cells start empty and stay in one row at every checked width. Each native Add node button activation fills exactly the next cell with Node/노드, retains earlier nodes, outlines only the newest node and increments Stored nodes0→4. The fourth addition retains its outline and disables Add; no fifth-insertion attempt or failure story. Restart clears the whole example, including partial states. Approved bilingual caption/status strings are included. Count and message share one polite atomic region, giving five distinct announcements. Empty-cell Node glyph sizing and all five count/status states use inert aria-hidden alternatives. Native controls intentionally avoid the shared Button active translation; no movement/transition, extra values/indices/table/inputs/connectors/playback were introduced.

Added separate NODE_ARRAY_EXAMPLE_CAPACITY4, readonly NodeArrayFrame and pure nodeArrayFrames(), returning five independently frozen count/newest/completion frames. Occupancy is derived from the count; the lab NODES_CAPACITY10 is unchanged. Three focused tests cover exact ordered appends, one increment per step, retained occupied prefixes, completion, deep freezing, independent calls and fresh restart. All32 old model functions and64 non-dispatcher UI/helper bodies are byte-identical. Existing20 visuals remain,21 attachments total;45 bilingual topics and all headings/labels/aliases/tutor/feedback contexts remain unchanged. Independent review found no issues.

Final237 tests pass with no skips, including62 model tests, the actual-C oracle, both annotated C programs and the packaged ZIP build. TypeScript, production build and whitespace checks passed. KO/EN browser QA at1280/375/320px verified every count0–4, empty/occupied text, retained prefixes/newest-only outlines, disabled completion, complete/partial restart and full replay, native Enter/Space/visible focus, one polite atomic region/five distinct announcements, inert sizing and no extra controls/overflow. Cells remain equal-width in one row; panel/cell/feedback/button/following-topic positions are unchanged through every state/reset/replay. Panel height328px across all six language/width combinations. At320px cells52.25px wide/64px tall and controls112.5px wide/44px tall. Computed button transition0s/translate none. Live KO/EN full trace and restart verification passed; final Korean full-four state captured. Viewport reset; Korean page marked deliverable.

All90 preserved source/presentation/manuscript/download snapshot entries remain byte-identical, including every lab.c and the existing ZIP. Only five source/test feature files synced via checked binary patch into the dirty primary checkout; all five match published source. Unrelated edits and public audience preserved; isolated checkout clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-node-array-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-node-array-live.png`.


## 2026-11-12 — Prepare an empty table (visual only)

Published Sites version309 from source `c43f95e7d67ca661869625b430b3fd3c4c4c7745`. Public deployment `appgdep_6af6a1ceed2881919e4e7ed9696e8a51` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “빈 표 준비하기” / “Prepare an empty table” only beneath coding-plan/table-capacity. Fixed Node capacity4/Table capacity6 and the approved small-example caption remain visible. Six equal neutral noninteractive cells stay in one row. Planned table starts with blank layout placeholders explicitly labeled not yet created; these are not claimed to be actual C memory values. One Create empty table action changes the heading to Empty table, fills all six cells with−1 simultaneously, and gives the approved no-first-node explanation. Create remains visible but disabled; Restart restores the planned layout. No node diagram, indices, keys, averages, scanning, playback or lab initialize invocation was added. Native controls have visible focus and no movement/transition; inert aria-hidden alternatives reserve both headings, markers and wrapped statuses from the first frame.

Added separate TABLE_PREPARATION_CAPACITY derived from NODE_ARRAY_EXAMPLE_CAPACITY4*3/2, readonly TablePreparationFrame and pure tablePreparationFrames(), returning two independently deeply frozen six-slot snapshots null→−1. Three focused tests cover capacities, exact phase/order/all-six transition, deep freezing, independent repeats/restart and unchanged lab10/15 constants. All33 previous model functions and67 non-dispatcher UI/helper bodies are byte-identical; only dispatcher/renderer integrations gained branches. Existing21 visuals remain,22 total, with all45 bilingual topics/labels/aliases/tutor/feedback context unchanged. Independent review found no issues.

Final240 tests pass with no skips, including65 model tests, actual-C reference, both annotated C programs and ZIP buildability. TypeScript, production build and whitespace checks passed. KO/EN browser QA at1280/375/320px verified planned/created headings and exact messages, blank→six−1 values in one action, neutral unchanged cell borders/backgrounds, fixed4/6 labels, primary completion disabling, repeated reset and Enter/Space replay, visible keyboard focus, one polite region and inert sizing, two controls/no extras, no overflow, six equal cells/one row, and stable panel/heading/cell/glyph/feedback/button/following-topic positions. At320px cells35.5px wide and glyphs19.2px wide remain legible; controls are112.5px wide and44px KO/58px EN tall. Panel heights KO364/364/388px and EN364/402/450px at1280/375/320px. Live KO/EN interaction checks passed; final Korean created table was captured. Viewport reset and Korean page marked deliverable. CUA was rebound to the existing IAB tab1/browser2 after its prior runtime bindings had cleared.

All90 snapshotted protected source/presentation/manuscript/download entries remain byte-identical, including every lab.c and existing ZIP. Only five verified feature source/test files synced via checked binary patch into dirty primary; all five match published source. Unrelated edits and public audience preserved; isolated checkout clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-table-preparation-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-table-preparation-live.png`.


## 2026-11-12 — Calculate a table index (visual only)

Published Sites version310 from source `54e85b2c41912f833bd98df3ba2f06ced21e39d5`. Public deployment `appgdep_6af6a8d496a081918a250d750e75a9f0` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “표에 맞는 번호 구하기” / “Calculate a table index” only beneath coding-plan/hash-function. The small capacity-six example has three native mutually exclusive pressed key buttons8/10/−1, default8. It shows8%6=2,10%6=4, or−1%6=−1 (neutral Intermediate value), then−1+6=5. Only the final result is bold and only the valid returned index2/4/5 is outlined in the permanent noninteractive0–5 row. No stored values/head markers, insertion, editable fields, stepping, Restart, connectors or playback are added. Exact bilingual Use slot N and remainder/conditional-add caption strings appear. One polite atomic region includes calculation and result; all three feedback variants are reserved inertly from the first frame. Native controls have fixed border widths, visible focus and no CSS movement/transition.

Added frozen HASH_CALCULATION_KEYS/INDICES, HashCalculationKey, readonly HashCalculationView and pure hashCalculationView(), using the existing teaching capacity6 and direct remainder/conditional addition. Three tests verify exact arithmetic/adjustment/range, deep fixture/view freezing, deterministic independent calls, and unchanged lab NODES10/TABLE15/hashFunc(−16)=14. All34 existing model functions and70 non-dispatcher UI/helper bodies are byte-identical. The intact hash-code walkthrough moved from coding-plan/hash-function to c-code/create-hash-function; historical invariant-preserve-rules now resolves directly there. All other anchors and historical labels are unchanged. Existing22 visuals remain,23 total;45 bilingual topics unchanged. Independent review found no issues.

Final243 tests pass with no skips, including68 model tests, actual-C oracle, bilingual annotated C core assertions and ZIP buildability. TypeScript, production build and whitespace checks passed. KO/EN browser QA at1280/375/320px verified default8, all key selections, repeated−1, switching back/forth, exact equations/conditional intermediate label, only final bold/highlight, previous outline clearing, native Enter/Space and visible focus, one atomic polite region/three distinct announcements, inert sizing, no extra controls/overflow and six equal noninteractive cells in one row. Panel/cell/button/feedback/following-topic positions remain fixed through all selections. Panel heights KO468/468/492px and EN468/492/508px at1280/375/320px; smallest cell35.5px, keys at least72.33×44px. Rechecked the English320px index row with fresh DOM/screenshot after scrolling; all cells are visible and legible.

Relocated walkthrough verified in both languages at desktop/320px: ready→remainder−1→adjusted14→returned14✓, correct active code group, all five literal lines mounted, completion disabled, restart clears, no excerpt overflow, CSS soft wrapping and stable heights536.5px desktop/634px KO320/658px EN320. Historical anchor resolves to c-code/create-hash-function in both languages; general Coding plan hash-function remains the new math example. Live KO/EN key selection and relocated walkthrough checks passed; final Korean−1→5 state captured. Viewport reset and Korean page marked deliverable.

All90 protected source/presentation/manuscript/download snapshot entries remain byte-identical. Six source/test/integration files synced through a checked binary patch into dirty primary, all matching published source. Unrelated edits/public audience preserved; isolated checkout clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-calculation-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-calculation-live.png`.


## 2026-11-12 — Hash-calculation choices7,9,−1

Published Sites version311 from source `9bdf930295bd7bd1a38bdb815daf5424b656ab43`; public deployment `appgdep_6af6acc0e5a081919f5bc1ed70f8a2f2` succeeded. Changed only HASH_CALCULATION_KEYS from8/10/−1 to7/9/−1 and five existing model-test lines. Default7, positive equations and highlights derive automatically:7%6=1,9%6=3, negative case unchanged−1→5. No UI code, other models, prose or downloads changed. Independent review confirmed no stale feature key references or unrelated diffs.

All243 tests pass with no skips, TypeScript/production build/diff checks pass. KO/EN at1280/320px browser-tested default7, all choices, exact equations, pressed states, index1/3/5 and stable layout; existing23 visuals retained. Live English full choice verification and Korean default/choice rendering passed; Korean default7 screenshot saved and page marked deliverable, viewport reset. All90 preserved source/presentation/manuscript/download snapshots remain byte-identical.

Both verified model/test files synced through a checked binary patch into dirty primary and match published source; unrelated work/public audience preserved, isolated checkout clean, owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-keys-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-keys-live.png`.


## 2026-11-12 — Put the new node first (visual only)

Published Sites version312 from source `c2d08fa276cf2b0156e1845d7fcb680ecc3cc6eb`; public deployment `appgdep_6af6b55a03fc819198dc2b338b5b97bf` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “새 노드를 맨 앞에 연결하기” / “Put the new node first” only beneath coding-plan/head-insertion. The capacity-six teaching example shows only slot1, existing key7/data70 and incoming key13/data130. The incoming caption changes To store→Stored after one native Store action. The new node appears in its reserved position and becomes head, pointing to the retained existing node; the old End link remains. The permanently reserved48px head-connector band changes its destination from existing to new without moving either node or End. Store disables with its label retained; Restart restores the prepared chain. Native controls have no CSS transition/translation, one polite status announces the exact approved bilingual messages, and inert aria-hidden sizing reserves the tallest caption/status/node state.

Added frozen HEAD_INSERTION_NODES, readonly node/frame types and pure headInsertionFrames(), returning exactly two independent deeply frozen snapshots. Both keys map to1 using teaching capacity6. Allocation order remains existing,new; chain order becomes new→existing. Three focused tests cover mappings, link/data retention, deep immutability, repeated calls/restart and unchanged lab capacities10/15. Independent review verified all35 existing model functions and72 existing non-dispatcher UI/helper bodies are byte-identical, with only the dispatcher and topic renderer gaining a branch. All23 old visuals remain,24 total; all45 topics, aliases, labels and tutor/feedback context remain unchanged.

All246 tests (71 model tests including actual-C oracle), TypeScript, production build and whitespace checks passed. KO/EN browser QA at1280/375/320px verified ready/store/reset/replay, Enter/Space, Tab-visible focus, completion disabling, correct captions/statuses, hidden pending node, retained key7/data70, one polite region, inert sizing, no internal/page overflow and aligned connectors. Panel/row/bucket/both node/End/control/following-topic positions stayed identical across all states. Panel heights KO388/436/436px, EN388/460/484px; narrowest node72.12px, buttons at least44px tall. Live English and Korean store/reset checks passed; final Korean stored state captured. Viewport reset and Korean page marked deliverable.

All550 protected source/presentation/prose/download/schema snapshot entries remain byte-identical, including every lab.c and existing ZIP. Only five verified feature source/test files synced through a checked binary patch into dirty primary; all five match published source. Unrelated edits and public audience preserved; isolated checkout clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-head-insertion-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-head-insertion-live.png`. Verification: `student-textbook-web/outputs/chapter-nine-publication-20261108/head-insertion-verification.json`.


## 2026-11-12 — Find the matching key (visual only)

Published Sites version313 from source `48b6d021601dbc4520bfef069500692665563fd6`; public deployment `appgdep_6af6bdc110a481918c2224d0220f8267` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “키가 같은 노드 찾기” / “Find the matching key” only beneath coding-plan/key-lookup. The fixed capacity-six teaching example retains slot1→key13/data130→key7/data70→End, with Find key7 visible. Each native Check next activation compares one key: first13 gets× and its Key field is emphasized; second7 gets✓ and the current outline/emphasis moves while the previous× remains. The second comparison disables Check next. Restart clears all search marks/current emphasis while retaining both records and all links. Native44px controls have no transition/translation, one polite status uses the exact approved three bilingual messages, and inert aria-hidden variants reserve wrapped statuses and key/badge styles. No input/selector/counter/node-index/playback or extra scenario was added.

Added KEY_LOOKUP_TARGET7, readonlyKeyLookupFrame and purekeyLookupFrames(), returning three deeply frozen independent frames ready→different→found. Slot1 is calculated7%6; traversal starts at'new' and followsNext to'existing', comparing keys13→7 instead of payloads or allocation order. Three focused tests cover exact ordered traversal, immediate stop, frozen/repeated frames, retained fixture data/links, restart and unchanged lab capacities10/15. All36 prior model function bodies and75 prior non-dispatcher UI/helper bodies remain byte-identical. All24 old visual attachments remain,25total; topic/schema/labels/aliases/tutor/feedback integration unchanged. Independent review found no issues.

All249 tests (74 model tests including actual-C oracle), TypeScript, production build and whitespace checks passed. KO/EN browser QA at1280/375/320px verified all three phases, marks[]→[×]→[×,✓], only current Key underlined/semibold, one comparison per Enter/Space/click, completion disabling, complete/partial restart and replay, Tab-visible focus, one polite region, inert sizing, fixed80px nodes/links/bucket, no overflow, and stable panel/diagram/node/link/End/status/control/following-topic positions. Panel heights KO356/356/380px, EN356/380/404px; narrowest nodes72.12px, all controls44px tall. Initial English desktop keyboard check ran before hydration completed; repeating after the page was interactive passed the full trace. Live English/Korean traces and English restart passed. Viewport reset and final Korean found-state screenshot saved; page marked deliverable.

All550 protected source/presentation/prose/download/schema snapshot entries remain byte-identical, including every lab.c and unchanged ZIP. Only five verified feature source/test files synced through a checked binary patch into dirty primary; all match published source. Unrelated edits/public audience preserved; isolated checkout clean; owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-key-lookup-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-key-lookup-live.png`. QA and verification: `key-lookup-browser-qa.json`, `key-lookup-verification.json` in the same outputs directory.


## 2026-11-12 — Lookup data values9and8

Published Sites version314 from source `997bacf70d7375c03cd7f9c4fc0f4241a693631a`; public deployment `appgdep_6af6bfe949b881919e5eec92c8648a81` succeeded. User requested data9and8 in the current key-lookup visual. Added frozen KEY_LOOKUP_NODES derived from the existing keys/links with new/key13/data9 and existing/key7/data8. Only the lookup model/UI consumes this fixture, including its accessible labels; preceding insertion retains130/70. Updated the existing fixture/immutability tests and asserted that insertion payloads remain unchanged. Independent review confirmed all other36 model and78 UI functions and550protected/prose/download/schemafiles unchanged.

All249tests, TypeScript, production build and diff checks pass. KO/EN at1280/320px verified9/8, retained keys and links, mismatch→match, badges, completion disabling and stable heights/no overflow. Live KO/EN labels verified and English completed trace captured after hydration settled. Only3verified featurefiles synced through a checked patch into dirty primary. Public audience/unrelated edits preserved, isolated checkout clean, owned preview stopped. Viewport reset and English page marked deliverable. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-lookup-data-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-lookup-data-live.png`. Reports: `lookup-data-browser-qa.json`, `lookup-data-verification.json`.


## 2026-11-13 — Keep one number fixed (visual only)

Published Sites version315 from source `21c9fdc136ab2add6ab23660cb55ec0f48069634`; public deployment `appgdep_6af6c9cb514c8191a886ef1c354756bc` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “한 숫자를 고정하고 확인하기” / “Keep one number fixed” only beneath coding-plan/brute-force. Reuses unchanged frozen four-number fixture[1,2,3,4],target6, BruteForcePairFrame and bruteForcePairFrames(). Exactly one comparison per native Check next pair produces2+1,3+2,3+1,4+3,4+2, stopping on6. Four fixed boxes use solid current/dashed earlier outlines with reserved localized labels. Feedback replaces its equation and derives upcoming-action messages from the next frame: advance to3, keep3/try1, advance to4, keep4/try2, then stop. Korean numeral particles use3을/4를and1과/2와. Ready has no highlights or equation; completion disables the primary button; Restart clears full or partial traces. Approved caption explains holding the current number and early stopping. Native controls have no transition/translation, one polite atomic status announces equation+message, and inert aria-hidden alternatives reserve all role/equation/status states.

Only3source/testfiles changed: new separate view/dispatcher mode, topic attachment, and assertions requiring exactly one new mode and26total attachments. All25 prior visuals remain. All37 existing model functions, entire model source, and78 prior non-dispatcher UI/helper bodies are byte-identical; all551 protected/prose/download/schema/model snapshots remain unchanged. Independent review found no issues. No lab.c, presentation, manuscript or download changed.

All249tests, TypeScript, production build and whitespace checks pass. KO/EN browser QA at1280/375/320px checked all six states/exact equations/messages, current persistence with descending earlier candidates, solid/dashed outlines, matching role labels, no accumulated box marks, completion disabling, full/partial restart/replay, native Enter/Space/Tab-visible focus, one polite atomic region/inert sizing, no overflow and unchanged older brute-force visual ready state. Panel/box/role-label/feedback/control/caption/following-topic positions stay fixed across every frame/reset. EN panel heights472/536/598px, KO448/488/536px; minimum box52.25×64px, buttons at least44px (EN320px wraps to58px). Live KO/EN full traces and restarts passed. Viewport reset and English final-match screenshot saved; page marked deliverable.

Only three verified feature files synced through a checked binary patch into dirty primary, all matching published source. Unrelated edits and public audience preserved, isolated checkout clean, owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-brute-force-plan-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-brute-force-plan-live.png`. QA and verification: `brute-force-plan-browser-qa.json`, `brute-force-plan-verification.json` in the same outputs directory.


## 2026-11-13 — Look for the partner first (visual only)

Published Sites version316 from source `ba883c0a2df50d2f9ae501f9feacc41f107b317f`; public deployment `appgdep_6af6d37062048191bb79cd3a4424ea22` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “짝이 되는 숫자부터 찾기” / “Look for the partner first” only beneath coding-plan/hash-two-sum. The fixed[1,2,3,4]/target6 teaching example uses six slots0–5, directly showing previously seen numbers with a simplified-diagram caption and slot=value%6 formula. One current input and its complement calculation remain visible. Each primary activation performs one operation: look5(empty),store1/advance2,look4(empty),store2/advance3,look3(empty),store3/advance4,look2(found). Lookup outlines only its checked cell; Store retains the inserted value, advances the input/calculation and clears the lookup outline. The lookup3 state shows an empty slot3 before the separate Store3 action, avoiding self-pairing. Final2+4=6✓ retains input4 and slot2, disables Lookfor2 and never stores4. Restart empties the table and restores input1/calculation5. Native controls use no transition/translation; one polite atomic region announces current calculation plus result. Inert aria-hidden sizing variants reserve role labels, all equations, cell markers, statuses, and every primary-button label.

Added pure hashTwoSumPlanFrames():readonlyTwoSumTableFrame[] with eight independently deeply frozen six-slot snapshots, reusing existing frozen numbers/target/complement helper and TABLE_PREPARATION_CAPACITY6. Existing four-slot model/UI remains unchanged. Three focused tests cover exact operations/mappings, unchanged lookup snapshots, storage before advancement, lookup-before-storage3, no4insert, immutability/independent arrays/repeated calls/restart and old model/lab preservation. Independent review verified all37 prior model-function bodies and81 prior non-dispatcher UI/helper bodies are byte-identical,26oldvisuals retained27total, and all550 protected/prose/download/schema snapshots match. Only five expected source/test files changed.

All252tests (77modeltests including actual-C oracle), TypeScript, production build and whitespace checks pass. KO/EN at1280/375/320px verified all eight frames, action labels/currents/complements/lookup indices, exact table snapshots, failure-before-store3, final match/no4, only checked-slot outlines, native Enter/Space/Tab-visible focus, complete/partial restart and replay, one polite atomic region/inert sizing, no overflow and unchanged old four-slot visual. Panel/input/role-label/equation/table/cell/glyph/status/control/caption/following-topic positions remain fixed across every state/reset. EN panel heights588/652/652px, KO588/588/636px; narrowest table cells35.5×56px with12px-wide glyphs; buttons44px tall. Live KO/EN full seven-operation traces and Korean restart passed. Viewport reset, final English match screenshot saved, page marked deliverable.

Only five verified feature files synced through a checked binary patch into dirty primary and all match published source. Unrelated edits/public audience preserved, isolated checkout clean, owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-two-sum-plan-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-hash-two-sum-plan-live.png`. QA and verification: `hash-two-sum-plan-browser-qa.json`, `hash-two-sum-plan-verification.json` in the same outputs directory.


## 2026-11-13 — Give a calculation a constant name (visual only)

Published Sites version317 from source `c3dabe362582e79cf661e3efc579503c5f0ec377`; public deployment `appgdep_6af6eec4d0dc81919b55f0c7e1d58f87` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “계산한 값에 상수 이름 붙이기” / “Give a calculation a constant name” only beneath new-c-syntax-explained/constant-expression. Two literal enum declarations remain mounted and unchanged. Ready shows NODES_CAPACITY×3÷2 and blank TABLE_CAPACITY=, with localized accessible Value not shown yet. One native Show the value click reveals10×3÷2=15 and TABLE_CAPACITY=15 with bold named result, disables the same-labeled control, and leaves code untouched. Restart restores ready. The approved compiler-before-execution explanation is visible in both states. Separate inert aria-hidden sizing variants reserve the calculation and named-result rows individually, so the named row stays fixed when the initial expression wraps at320px but revealed arithmetic uses one line. One polite atomic region exposes only actual values/pending text; native buttons have no translation/transition. Code uses pre-wrap/overflow-wrap:anywhere without changing raw text or tokens.

Added frozen CONSTANT_EXPRESSION_CODE_LINES, readonlyConstantExpressionFrame and pureconstantExpressionFrames() with two independently frozen frames ready/null→revealed/Math.trunc(NODES_CAPACITY*3/2). Three focused tests verify arithmetic against unchanged10/15 lab constants, deepfreeze/repeats/restart, literal parity with both authored manuscripts, and temporary strict C11 compilation/execution with_Static_assert plus file-scope array bound. All255tests (80modeltests), TypeScript, production build and diff checks pass, with no skips. Independent review verified all38 old model functions and84 old non-dispatcher UI bodies byte-identical;27oldattachments retained28total.

KO/EN browser QA at1280/375/320px verified ready/revealed/reset/replay, native Enter/Space/Tab-visible focus, blank/pending accessibility, bold15, exact unchanged code/explanation, one polite atomic region/inert sizing, completion disabling and no overflow/internal scrolling. Panel/code/calculation-reservation/named-row/control/explanation/following-topic positions stay fixed. EN panel heights351/422/488px, KO351/398/474px. Code heights75/98/122px with unchanged two raw lines;320px reserves56px for initial arithmetic versus28px revealed, keeping the named row fixed. Buttons44px except English320px58px. First Korean desktop keyboard automation ran before hydration; repeating once interactive passed the complete trace. Historical enum-capacity alias still sits in the correct topic and reaches the new visual. Live KO/EN reveal and Korean reset passed. Viewport reset and English revealed screenshot saved; page marked deliverable.

Final preservation check:549/550 snapshot files remain byte-identical. The sole exception is a concurrent unrelated user-owned source edit to root module_10_priority_queue/student/lab.c at2026-11-13T11:03:22.772236Z (oldSHA93f9236be4ce3a556411e1467506d3368377b3208a6e123e6ffacfb3efb047be,newSHAa95b55f241a6233d789d28e6107ed57d6c68f61cbefc0d0ae112009446f98be0). This task never wrote that file and left it untouched; user was informed in commentary. All other lab/presentation files, prose, downloads, aliases and labels match. Only five verified feature files synced via checked binary patch into dirty primary and match published source. Unrelated edits/public audience preserved, isolated checkout clean, owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-constant-expression-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-constant-expression-live.png`. Reports: `constant-expression-browser-qa.json`, `constant-expression-verification.json`.


## 2026-11-13 — See the remainder’s sign (visual replacement)

Published final Sites version319 from source `ce555b25942b300f1df6eedfd64ba549bd780f8d`; public deployment `appgdep_6af6f532c10081918480cd2adcccd351` succeeded at https://data-structures.chaebinkim.chatgpt.site/ . Initial version318 (`7842f3188cadd41c577d94706016640249a12675`,deployment `appgdep_6af6f34649c88191a14c00cb9dbf3cec`) was superseded after live QA identified a first-load readiness issue.

Replaced only SignedHashLesson/fifteen-bucket input UI under new-c-syntax-explained/negative-remainder with “나머지의 부호 확인하기” / “See the remainder’s sign”, modeinteger-remainder. Two native7/−7buttons default−7 and mutually exclusively pressed. Fixed small-example divisor3; negative displays−7/3=−2 and−7%3=−1, positive displays7/3=2 and7%3=1. Only the remainder result is bold, with identical neutral foreground color for both signs. One polite atomic region announces both calculations and exact localized short remainder status. Approved explanation says C truncates towardzero and negative dividends can produce negative remainders. No input/grid/adjustment/restart/step/playback remains in this lesson. Per-row inert aria-hidden variants reserve quotient/remainder/status heights. Native48px buttons have visible focus and no CSS transition/translation. Historical signed-hashing and signed-remainder anchors retain their topic/context/labels.

Added frozenINTEGER_REMAINDER_DIVIDENDS, divisor3, derivedIntegerRemainderDividend, readonlyIntegerRemainderView and pureintegerRemainderView(default−7), using Math.trunc(n/3) and n−quotient*3. Three focused tests cover exact/default views, reconstruction/magnitude/sign, deepfreezing/repeatedswitches, unchanged15-bucketmodel/parser, and temporary actual C11reference output. All39oldmodel function bodies unchanged; hashFunc/parseInt32/lab15remain intact. Only oldSignedHashLesson was removed; all86other prior non-dispatcher UI/helper bodies remain byte-identical. Other27visuals preserved,28attachments total. Exact5featurefiles changed across this task; all unrelated source/prose/download/schema/alias/label files untouched.

All258tests (83modeltests including C-reference), TypeScript, production build and diff checks pass. KO/EN at1280/375/320px verified default−7, both calculations/statuses, bold neutral remainder, mutually exclusive pressed states, Enter/Space/Tab-visible focus, repeatedselection/back-and-forthswitching, one polite atomic region/inert sizing, onlytwo controls, nooverflow/legacygrid and stable panel/control/calculation/status/explanation/following-topic positions. EN panel heights348/396/396px, KO348/372/396px; buttons at least112.5×48px. Both historical aliases verified at their unchanged topics in both languages.

Live318 QA caught a cold-load click arriving before client initialization (no consoleerrors; later selection worked). Final319 scopes a readiness gate to the replacement lesson: buttons render disabled until the component mounts, preserving identical geometry and defaultcalculations. LocalfreshKO/EN320px and finalliveKO/EN both observed initialreadyfalse/disabledcontrols; the very first positiveclick waited forreadytrue and produced7 immediately, then Space restored−7. Initialpanel/control/following positions match enabledstates. No changes to other lessons. Renewed an expired Sites source credential through the native same-project workflow; secrets remained in session/stdin only. Live final verification passed; viewport reset and English defaultnegative screenshot saved; page marked deliverable.

Final snapshot check550/551match. The sole exception is a concurrent unrelated root Module10 presentation edit: module_10_priority_queue/student/ppt_lab_material.md changed at2026-11-13T11:27:43Z, nowSHA9f0433f1eebb3c1fa3019b0c2818a0403132f0978e46d37d22f3890027844add. This task never wrote it and left it untouched; user informed. All lab.c files, including currentModule10laba95b55f..., and all other presentation/prose/download/schema files match the fresh baseline. Only five verified feature files plus the later checked readiness patch synced into dirty primary; all five match finalpublishedsource. Public audience/unrelated edits preserved; isolated checkout clean; owned preview stopped.

Final archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-integer-remainder-ready-site.tar` (initial318archive: `chapter-nine-integer-remainder-site.tar`). Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-integer-remainder-live.png`. Reports: `integer-remainder-browser-qa.json`, `integer-remainder-verification.json`.


## 2026-11-13 — Visit earlier positions backward (visual only)

Published Sites version320 from source `4c1d705e4fe7f3faa978df0d2454e16d574627ab`; public deployment `appgdep_6af704b521648191a6bf9f8b21a775b8` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “앞의 위치를 거꾸로 방문하기” / “Visit earlier positions backward” only beneath new-c-syntax-explained/reverse-loop. Four fixed position boxes0–3 retain solid i at3 and move a single dashed last-visited j marker2→1→0. The exact loop header remains mounted with CSS soft wrapping. Three native Visit earlier activations each visit one earlier position, and completion disables the unchanged-labeled control while retaining last-visited j at0. Completion explains the subsequent counter−1/false condition; no−1 box or extra click is introduced. Full and partial Restart clear j while retaining i3. Short bilingual status messages explain order; introductory copy explicitly identifies positions/fixed i/last-visited j. Native controls gate readiness until mount, have44px minimum targets and visible keyboard focus, without movement animations. One polite atomic status plus inert aria-hidden sizing alternatives reserve every wrapped completion and tag state.

Added frozen REVERSE_LOOP_POSITIONS, REVERSE_LOOP_CURRENT3, exact REVERSE_LOOP_HEADER, readonly ReverseLoopFrame and pure reverseLoopFrames(). Its descending loop generates four frozen independent frames ready/null→visiting2→visiting1→complete0. Three focused tests verify exact one-visit order/completion/exclusions, immutable fixtures/frames/repeats/restart, unchanged10/15 lab constants, literal header parity against both authored manuscripts, and actual temporary C11 reference output2,1,0. All261tests (86modeltests), TypeScript, production build and diff checks pass with no skips. Independent review verified all40 previous model function bodies and89 previous non-dispatcher UI function bodies byte-identical,28prior attachments retained29total, new mode attached only at its intended topic, existing descending-loop alias/labels/tutor/feedback contexts unchanged. Exact5expected source/testfiles changed.

KO/EN browser QA at1280/375/320px verified ready/each visit/completion/reset/replay, fixed i3, solid/dashed outlines, exactly one j/no accumulated marks, no visit3 or−1, unchanged code text with readable wrapping, native Enter/Space/Tab focus,44px controls, one polite atomic region/inert hidden alternatives, disabled completion and no internal overflow. Panel/boxes/tags/code/status/control/following-content positions stay fixed through all states/reset; EN panel heights398.5/446/518px, KO398.5/446/494px. Historical descending-loop alias reaches the same new visual in both languages. Live KO/EN cold loads initially showed ready=false/disabled controls, then the first click waited for readiness and visited2 immediately; both completed2→1→0 and Korean Restart passed. Viewport reset, final English completed screenshot saved and page marked deliverable.

All551 preservation hashes match fresh baseline, including every protected lab/presentation file and all prose/manuscripts/downloads. Only5verified featurefiles synced via checked binary patch into dirty primary and match published source; unrelated edits/public audience preserved. Isolated checkout clean, owned preview stopped. Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-reverse-loop-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-reverse-loop-live.png`. Reports: `reverse-loop-browser-qa.json`, `reverse-loop-live-qa.json`, `reverse-loop-verification.json` in the same outputs directory.


## 2026-11-13 — Space and count (visual only)

Published Sites version321 from source `c33f8dfd0d38ce6b2b5b8915bac3162bed980208`; public deployment `appgdep_6af71096d72481918d2388b169d6db91` succeeded at https://data-structures.chaebinkim.chatgpt.site/ .

Added “저장 공간과 개수” / “Space and count” only beneath c-code/node-list. Two stacked full-width native declaration buttons show exact `struct hnode hnodes[NODES_CAPACITY];` and `int size = 0;`, wrapping through CSS without changing raw text. Default array selection outlines its declaration and the complete ten-space array boundary; size selection outlines its declaration and separate size=0 count. Ten anonymous noninteractive blank boxes remain unused, captioned accordingly, with localized accessible position/occupancy labels. Actual ten-node capacity appears as ten columns on desktop and five columns/two rows on mobile. Selection only changes emphasis plus the approved bilingual status; no insertion, execution, field values, visible indices, restart, or other controls. Native buttons use mutually exclusive pressed states, localized names,44px minimum targets, visible focus, and client-readiness gating. One polite atomic status and inert aria-hidden longest-state alternatives keep geometry stable; no movement animations or internal scrolling.

Added frozen NODE_LIST_DECLARATIONS keyed array/size, derivedNodeListPart, readonlyNodeListView and pure nodeListView(defaultarray). Every returned view is independently frozen with unchanged NODES_CAPACITY10 and storedCount0. Three focused tests verify defaults/both views, immutability/switches/repeats/unchanged lab constants, and exact excerpt parity against authored KO/EN manuscripts and matching downloads. All264tests (89modeltests), TypeScript, production build and diff checks pass without skips. Independent review verified all41 previous model function bodies and91 previous non-dispatcher UI function bodies byte-identical,29priorattachments retained30total, only intended topic attachment, and preserved aliases/labels/tutor/feedback contexts. Exact5expected featurefiles changed.

KO/EN browser QA at1280/375/320px verified default/array/size/repeatedselection, native Enter/Space/Tab-visible focus, mutually exclusive pressed states and target outlines, ten neutral unused cells, fixed zero count, exact CSS-wrapped code, minimum44px buttons, one polite atomic status/inert sizing, and no extra inputs/players/internal overflow. Panel/control/array/cell/count/status/following-content positions remain fixed across every selection, with panel heights416/490/514px in both languages. Cold Korean local loads atall3widths initially disabled controls until mount, then first clickselectedsize. Live KO/EN320px both initially showed ready=false/disabled, then first size click waited for readiness and worked immediately; Space restoredarray and Enter repeated it deterministically. Historical c-code-node-storage alias reaches same topic/visual. Viewport reset, final English array-selection screenshot saved, page marked deliverable.

Final snapshot check550/551match. Sole exception is a concurrent unrelated edit to root module_10_priority_queue/student/ppt_lab_material.md at2026-11-13T13:29:16.971959Z: baselineSHAe2545432d527f722e740631b5925b1caeb1323a3b5a4509b616b84fd128559c0, currentSHA41ac251732af0f19283407795dfb19c6888123c0782f8f530e8cc781e3907e1d. This task never wrote that file and left it untouched; user informed. Every lab.c and all other protected/prose/manuscript/download/schema files match fresh baseline. Only5verified featurefiles synced by checked binary patch into dirty primary and all match published source. Public audience/unrelated work preserved; isolatedcheckoutclean; ownedpreviewstopped.

Archive: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-node-list-site.tar`. Screenshot: `student-textbook-web/outputs/chapter-nine-publication-20261108/chapter-nine-node-list-live.png`. Reports: `node-list-browser-qa.json`, `node-list-live-qa.json`, `node-list-verification.json` in the same outputs directory.
