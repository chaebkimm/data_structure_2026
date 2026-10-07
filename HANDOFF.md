# Chapter 5 textbook and website handoff

Updated: 2026-10-07.

## Current state

The latest Chapter 5 website changes are published at https://data-structures.chaebinkim.chatgpt.site/chapter-5#thinking-1.

- Sites project: `appgprj_6a955240a2d0819191a05a6f72a08e8f`; audience remains public.
- Published version: 176.
- Website source commit: `840007ca90703aca61ec71181ecda17a6c85ff32`.
- Deployment: `appgdep_6ac633dd88048191ad6740d2b8414399`, succeeded.
- Website checkout: `/Users/cbk/Documents/GitHub/data_structure_2026/student-textbook-web` (its own Git repository). Its working tree was clean when this note was saved.
- Local preview servers started for verification have been stopped.

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

## Verification

Latest change passed TypeScript checking and the production build. Browser verification showed the measured panel height was 1230 px at the preview width, reduced from 1758 px. At the four-card state, scrollHeight equaled clientHeight; the following section's document position stayed at 1727 px before and after reset. Playback and pause were verified earlier. No further work is pending.

## Continuing work

Use Sites building/hosting skills for website edits and publishing. Open the existing Site's source with the bundled workflow before editing. Preserve project ID, audience, current architecture, and unrelated user changes. Obtain fresh source credentials as needed; never save tokens in this handoff or files.

The system Git requires an unaccepted Xcode license; use the bundled executables:

- Node: `/Users/cbk/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/bin/node`
- Git: `/Users/cbk/.cache/codex-runtimes/codex-primary-runtime/dependencies/bin/fallback/git`
- Python: `/Users/cbk/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3`
- Sites scripts: `/Users/cbk/.codex/plugins/cache/openai-curated-remote/sites/0.1.75/scripts/`

For the workflow process, prepend bundled Node and fallback Git directories to PATH, launch `site-workflow.mjs --project-id <existing project ID>` in the website checkout with a PTY, and send credentials through hidden stdin. First run without an archive to open source; retain the returned source object. After changes, run again with that source, necessary checks/build commands, and an absolute archive path. Save the exact pushed commit/archive through Sites, then deploy the returned saved version. Confirm deployment succeeded before reporting publication. The normal build command is `node <Sites scripts>/build-site.mjs`; the TypeScript command is `node node_modules/typescript/bin/tsc --noEmit`.

This handoff is a local repository note; it does not require another website publication.
