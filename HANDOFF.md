# Textbook website handoff

Updated: 2026-10-17.

## Current state

Chapter 6 is the default homepage at https://data-structures.chaebinkim.chatgpt.site/ and https://data-structures.chaebinkim.chatgpt.site/en. `/ko` also opens Chapter 6. Explicit `/chapter-6`, `/en/chapter-6`, and `/ko/chapter-6` URLs remain available. Chapter 5 now uses `/chapter-5` and `/en/chapter-5` in navigation and language switches. Explicit Chapter 0–6 routes remain available; canonical URLs and language alternates follow the new homepage mapping.

- Sites project: `appgprj_6a955240a2d0819191a05a6f72a08e8f`; audience remains public.
- Published version: 198.
- Website source commit: `d7115152677718d2fa49697c2ae80ecbcc0be351`.
- Deployment: `appgdep_6ad393aeaa008191a973d26184203814`, succeeded.
- Website checkout: `/Users/cbk/Documents/GitHub/data_structure_2026/student-textbook-web` (its own Git repository). Its working tree was clean when this note was saved.
- Local preview servers started for verification have been stopped.

## Chapter 6

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
