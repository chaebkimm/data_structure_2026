# Module 13 Lab Slides — 소스와 검사

Connect each prediction to a particular source condition. Read the supplied source in order and keep the one-submission boundary.

## 1. Search without mutation

Use `linear_search(values,n,key)` and confirm the first match is returned. The original canonical 17 is index 2. Missing and empty inputs return -1. 원본과 결과 인덱스를 함께 보관한다.

## 2. Keep a half-open interval

Use `binary_search_first(sorted,n,key)`. Before a read require `lo<hi`; compute `lo+(hi-lo)/2`. On equality set hi=mid. After convergence check lo<n before reading sorted[lo]. 정렬은 호출자가 준비한다.

## 3. Save, shift, insert

Use `insertion_sort`. Save values[i], shift while the preceding value is strictly greater, then fill the gap. Predict the pass using 17B and explain why 17A is not shifted past it. 이동 수와 키의 최종 쓰기를 따로 센다.

## 4. Divide, merge, copy back

Use `merge_sort` and `merge_range`. The base case is hi-lo<=1. Every merge writes only its half-open range into the same nonoverlapping scratch array. Choose left on <=. 버퍼 용량 n과 겹치지 않음을 호출자가 보장한다.

## 5. Run independent checks

Run `make -C code`. Compare both sorts with a non-overflowing `qsort` comparator and searches with an independent first-match scan. Add original groups for search, sorting, and boundary/repeated-call behavior. Run only valid caller states. 정수 결과 비교와 안정성의 표식 추적은 서로 다른 증거다.

## 6. Submit one justified choice

Preserve predictions, traces, commands/output, three original groups, tagged tie reasoning, operation counts, and the workload-selection table. Compare preparation/query/update/storage rather than selecting by one Big O label. 모든 부분은 한 제출물이다.
