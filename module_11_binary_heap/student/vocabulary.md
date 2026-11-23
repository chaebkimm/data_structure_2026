# Module 11 Vocabulary

Use this English–Korean glossary with the [investigation worksheet](investigation_worksheet.md)
and [lab source](lab.c).

| Term | Meaning in this lab |
| --- | --- |
| Priority queue / 우선순위 큐 | A collection that removes the value with the highest priority. Smaller integers have higher priority here. |
| Complete binary tree / 완전 이진 트리 | Levels fill from top to bottom and from left to right. Only the last level can be incomplete. |
| Binary min-heap / 이진 최소 힙 | A complete binary tree in which every parent value is less than or equal to each child's value. |
| Root / 루트 | Index 0. In a nonempty min-heap, this slot holds a smallest value. |
| Live prefix / 활성 구간 | The `size` entries starting at `pq[0]`. Occupied tree positions are consecutive. |
| Capacity / 용량 | The number of slots reserved in `pq`. Here `CAPACITY` is 5. |
| Leaf / 리프 | A live position whose candidate left child index is at least `size`. |
| Comparator / 비교 함수 | `compare(x, y)` is true when the value `x` is smaller than the value `y`. |
| Sift-up / 상향 조정 | `sift_up` copies larger parents down and returns the insertion index for the saved value. |
| Sift-down / 하향 조정 | `sift_down` copies smaller children up and returns the placement index for the saved value. |
| Bottom-up construction / 상향식 힙 구성 | `heapify()` establishes heap order by repairing parent subtrees from the bottom up. |
| Heap sort / 힙 정렬 | Here `heap_sort(sorted)` drains a valid min-heap into a separate array in ascending order. |
| Caller precondition / 호출 전 조건 | A requirement before a call. Insertion needs a free slot. Removal needs a live value. |
| Invariant / 불변 조건 | A property that holds after each valid operation, such as the parent–child ordering of the live heap. |
