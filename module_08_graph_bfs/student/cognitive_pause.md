# Chapter 8 Cognitive Pause — 저장된 순서대로 데이터 처리하기

Take five minutes without tools, notes, or classmates. Preserve all three initial answers before comparing. Use `{y,x}` coordinates and list queues front to back. 도구나 노트 없이 5분 동안 답한다. 첫 답을 남긴 뒤 수정한다.

## Target 1 — Explain the queue positions / 큐 위치 설명

A linear queue starts with front 0/rear -1 and has 25 slots. After 25 enqueues and 25 dequeues, what are its endpoints? Is it empty, and can it accept another value without breaking `0 <= front <= rear + 1 <= 25`? 선형 큐에 25번 넣고 모두 꺼낸 뒤의 상태를 설명한다.

For a circular comparison with one reserved slot, fill 0–23, remove 0/1, then append 24/25. Use the convention that, when nonempty, front is the first queued data’s index and rear is the last queued data’s index. Give endpoints, pending count, and next value. 같은 위치 정의로 원형 큐의 결과를 쓴다.

Answer / 답: ________________________________________________________

## Target 2 — Preserve tree levels / 트리 층 유지

Root A has B/C. B has D/E. C has left child F. Enqueue existing left children before right children. Give the queue after processing B, the complete processing order, and depths. Explain why a valid tree does not need a discovery flag. A/B/C/D/E/F의 대기 순서와 깊이를 설명한다.

Answer / 답: ________________________________________________________

## Target 3 — Discover before enqueue / 추가 전에 발견 기록

In the supplied 5×5 maze, start at `{1,1}`. `{2,2}` first discovers `{3,2}` at distance 3. Later `{3,1}` checks `{3,2}` while it is still queued. Explain why it is skipped. Give the final distance at `{3,3}` and explain why first discovery is shortest. How does skipping a discovered BFS neighbor differ from allowing an unprocessed neighbor to enter the comparison stack again? 아직 큐에서 꺼내지 않은 통로를 다시 넣지 않는 이유와 스택의 중복 대기 비교를 설명한다.

Answer / 답: ________________________________________________________

## Compare after time is called / 시간이 끝난 뒤 비교

Spend five minutes on labeled corrections. 첫 답을 지우지 않고 수정 이유를 덧붙인다.

1. Linear endpoints are 25/24. It is empty, but no unused write position remains. Another enqueue would break the maintained upper bound; the caller must supply an available write position. Circular endpoints are 2/0, 24 values wait, and label 2 leaves next. Circular empty/full conditions require the stated one-slot convention; they are not the maze source's linear predicate.
2. After B, the queue is `[C,D,E]`. Complete order is A/B/C/D/E/F with depths 0/1/1/2/2/2. Each nonroot node has one parent and the tree has no cycle. A shared destination or cycle needs discovery tracking.
3. `{3,2}` already has a finite distance, so the current lab skips it without enqueue or another record. `{3,3}` receives distance 4. Equal-cost moves and FIFO process closer layers first; any shorter route would have discovered the cell earlier. The graph-stack comparison instead permits another copy of an unprocessed neighbor and skips already processed nodes on pop. The lab records distance only.

Correction and reason / 수정과 이유: _________________________________
