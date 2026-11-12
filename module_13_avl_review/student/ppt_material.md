# Module 13 Concept Slides — 탐색, 정렬, 통합

Use each scene for prediction before showing the result. 학생의 첫 답을 보관하고 다음 상태를 보여 준다. Keep the same six records throughout.

## 1. Which position contains the first 17? / 첫 17은 어디에 있을까?

Show `[31,23,17,8,17,42]` with indices 0..5. Ask for the first position without rearranging. Reveal comparisons 31,23,17 and index 2. Missing 99 checks all six. 탐색은 원본을 바꾸지 않는다.

## 2. What lets us discard half? / 절반을 제외하려면 무엇이 필요할까?

Compare the unordered array with `[8,17,17,23,31,42]`. A middle comparison is useful only under the order rule. Trace `[0,6) → [0,3) → [0,1) → [1,1)`. Equality keeps the left candidates. The final check returns 1. 정렬 전 위치 2와 정렬 후 위치 1을 구분한다.

## 3. How does one ordered prefix grow? / 정렬된 앞부분을 어떻게 늘릴까?

Reveal insertion passes one at a time: saved keys 23,17A,8,17B,42; shifts 1,2,3,2,0. Save before shifting. Strictly larger values move; equal A stays before B. 총 오른쪽 이동은 8번이다.

## 4. How do two ordered ranges become one? / 정렬한 두 구간을 어떻게 합칠까?

Show `[17A,23,31]` and `[8,17B,42]`. Compare unused heads, write scratch, then copy back. Reveal 8,17A,17B,23,31,42. Equal keys choose left. 버퍼는 값 배열과 겹치지 않는 호출자 소유 저장 공간이다.

## 5. Does faster lookup repay preparation? / 준비 비용을 회수할 수 있을까?

Contrast one query with many queries on an unchanged snapshot. Separate preparation, query, update, and storage. Binary search does three interval decisions plus a final equality here; original linear search finds 17 after three comparisons. 작은 한 사례에서 이진 탐색이 반드시 적게 일하지는 않는다.

## 6. Which request does each structure answer? / 구조마다 어떤 요청에 답할까?

Compare ArrayList indexed access/scan, known-predecessor list updates, hash exact lookup, AVL ordered updates, heap minimum, and BFS/DFS/Dijkstra scheduling. Give assumptions with each cost. A heap does not answer arbitrary-key lookup at its root. 연결 리스트의 가운데 이동 비용도 센다.

## 7. What carries into Module 14? / 14장으로 무엇을 가져갈까?

Ordered edge candidates need sorting and tie rules. Sorting does not decide whether two vertices are already connected. Module 14 introduces that decision and supplies its edge sorter. No DSU implementation is assigned in this lesson.
