# Module 10 Vocabulary

Use these names after working through the [textbook](textbook.md) and
[lab](lab.md). The definitions describe the current fixed-array source.

| Term | Meaning in this lab |
| --- | --- |
| Priority Queue / 우선순위 큐 | A collection whose next removal is selected by a stated ranking rather than arrival alone. |
| Complete binary tree / 완전 이진 트리 | Levels fill top to bottom, left to right, with only the final level possibly incomplete. |
| Binary Heap / 이진 힙 | A complete binary tree whose parent/child comparisons obey its ranking rule. |
| Root / 루트 | Position 0. The simple Heap stores its extreme integer there. Each full Heap stores an ID with an extreme selected endpoint, not an extreme ID number. |
| Live prefix / 활성 구간 | Integer positions 0 through `size-1`; reserved slots beyond it are not live values. |
| Minimum Heap / 최소 힙 | Every parent value is no larger than each existing child's value. |
| Maximum Heap / 최대 힙 | Every parent value is no smaller than each existing child's value. |
| Comparator / 비교 함수 | A function deciding whether one entry belongs above another. `comp` takes positions; `_comp_on_max` and `_comp_off_min` take IDs. |
| Sentinel / 센티널 | A special value marking an absent item. `-1` from relationship helpers is never an array position. |
| Sift-up / 상향 조정 | Repair toward the root, called `heapify_up` or `_heapify_up` in this source. |
| Sift-down / 하향 조정 | Repair toward the better existing child, called `heapify_down` or `_heapify_down`. |
| Bottom-up construction / 아래에서 위로 구성 | Repair internal positions from the last parent toward the root; `heapify` and `_heapify` perform this work. |
| Function pointer / 함수 포인터 | A stored choice of function. `Heap_Full.comp` compares IDs and `Heap_Full.swap` swaps positions. |
| Indexed Heap / 위치 맵을 갖는 힙 | A Heap with an inverse map from each ID to its current position. |
| Inverse map / 역방향 위치 맵 | `_max_heap_pos[id]` or `_min_heap_pos[id]`; swapping IDs also updates their positions. |
| Closed interval / 닫힌 구간 | A time span including both endpoints; `[a,b]` allows time `a` and time `b`. |
| Epoch / 현재 구간 번호 | `epoch[id]` selects that ID's current interval; columns `2*epoch` and `2*epoch+1` hold its endpoints. |
| Intersection / 교집합 | Times shared by all selected intervals; it is `[max(on),min(off)]` when the start is no later than the end. |
| Caller precondition / 호출 전 조건 | A condition the caller must establish because a supplied function does not check it. |
| Invariant / 불변 조건 | A property preserved after a valid operation, such as Heap order and correct inverse maps. |

The equal-value comparator keeps its first argument; the lab gives no
stable first-arrival ordering. C's dynamic-memory heap is a separate use
of the word Heap. The current lab does not allocate storage with `malloc`.
