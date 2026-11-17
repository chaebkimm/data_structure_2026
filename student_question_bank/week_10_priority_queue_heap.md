# Chapter 10 — Priority Queues and Finding a Meeting Time: Vocabulary and Questions

[All-week vocabulary and question bank](../Data_Structures_Course_2026_Student_Question_Bank.md)

## Required scope

Use the unchanged [lab.c](../module_10_priority_queue/student/lab.c), concept/code presentations, and matching English/Korean textbooks. Trace sorted insertion, front/rear, strict comparison and stable ties, then the three-user meeting search. Availability is [login,logout); endpoint equality fails. The source has no main or external module dependency and is supplied complete.

Use three nonnegative nonempty chronological nonoverlapping intervals per user. Prevent full insertion at the end and empty removal. Slots are never reused before initialization, so ten slots must cover up to nine cumulative insertions. The sample returns 12. This is one ordinary lab artifact within 180 minutes; no heap, graph, inverse-map or allocation implementation is required. Superseded materials are archived and excluded from the release.

The filename retains the existing Week 10 question-bank route. Package titles use Chapter 10. The presentations say Week 12; their label does not move other course weeks.

## Required vocabulary — 21 entries

| Term | Working meaning |
| --- | --- |
| FIFO | Remove in arrival order; the earlier queue rule being recalled. |
| Priority queue | Remove an item with highest priority under a comparison rule. |
| Comparator | A function returning nonzero when its first argument has strictly higher priority. |
| Sorted insertion | Shift lower-priority live items right to open the correct position. |
| Stable ties | Equal-priority items retain their order of insertion into the queue. |
| `front` | Index of the first live item; incremented by removal. |
| `rear` | Index of the last live item; incremented by insertion. |
| Live range | Positions front through rear; count rear - front + 1. |
| Empty state | front == rear + 1; initially 0 and -1. |
| Cumulative insertion count | All insertions since queue initialization; equals rear + 1. |
| Caller precondition | A condition callers must ensure because the source does not check it. |
| User ID | Row number identifying one user; the queue stores this ID. |
| Half-open interval | [login,logout): online at login, offline at logout. |
| Epoch | Zero-based selected interval number, stored in users[id].epoch. |
| Candidate | Greatest current login; meeting_time in survey. |
| Blocking interval | An interval whose logout is at or before the candidate. |
| Exhaustion | No next interval exists; next_epoch returns -1 after incrementing epoch. |
| Function pointer | Stores a function address; compare selects the priority rule. |
| Function address | &earlier_logout, passed to init_queue. |
| Invariant | A state relationship preserved by each valid operation. |
| Independent oracle | A different calculation used to check results, here interval-combination enumeration. |

No optional vocabulary cluster is required for this package.

## Questions — 47 prompts

### Priority and representation

1. How does choosing by priority differ from choosing the first arrival?
2. Does the abstract priority queue require arrival order for equal priorities? What does this source do?
3. What does queue[position] store during survey: an ID, a position, or a time?
4. What do front and rear identify when the queue is nonempty?
5. Why are the initial indices 0 and -1?
6. How do rear-front+1 and front==rear+1 describe count and emptiness?
7. Why are consumed positions before front outside the live range?
8. Why can a successful survey leave queued IDs instead of an empty queue?

### Sorted insertion and removal

9. Where does enqueue first try to place a new item?
10. Which values move when compare(new,old) reports higher priority?
11. Why must the insertion loop stop at front rather than index zero?
12. After inserting 7,2,5 and removing once, what happens when 1 is inserted?
13. Why does strict comparison preserve arrival order for equal priorities?
14. Using smaller last-digit priority, in what order do 21,11,32,1,22 leave?
15. Why does dequeue take constant work without shifting the live items?
16. After ten total insertions and removals, why is another enqueue invalid without initialization?

### Current intervals and C callbacks

17. How do log indices 2*epoch and 2*epoch+1 select the current pair?
18. Which fields does init_users set for each user?
19. What is the difference between timelogs and users?
20. What type of function does int (*compare)(int,int) point to?
21. What does &earlier_logout pass to init_queue?
22. Does the comparator return strict Boolean priority or a negative/zero/positive ordering code?
23. Why can changing a still-queued user's logout break the stored order?
24. Which names and sample size differ between the slides and actual lab?

### Candidate and interval advancement

25. Why is the greatest current login the earliest possible meeting for the selected intervals?
26. Why does equality of candidate and earliest logout fail?
27. Which interval must be advanced when the current candidate is not feasible?
28. Why can discarding that blocking interval not discard a possible earlier meeting?
29. Why can only the returning user's new login be compared with the old candidate?
30. Why does a new login of 11 leave an existing candidate of 12 unchanged?
31. Why must the removed ID be reinserted before selecting the next earliest logout?

### Canonical trace and endings

32. What are the sample's initial candidate, sorted IDs and first removed ID?
33. Which six user advances and candidate values lead to the sample answer?
34. Which three current intervals contain the returned meeting time 12?
35. What are the final front, rear, live IDs and selected ID?
36. How many insertions, removals and successful advances occur, and how were they measured?
37. Which fields change or stay old when next_epoch returns -1, and what does a fresh survey reset?

### Work, storage and comparison

38. What is the worst-case work of insertion into k live items, and of removal?
39. Why can initial population cost O(U²) before A advances cost O(AU)?
40. How does the linear logout-scan reference cost O(U+AU), and why is no queue speedup claimed?
41. Why must queue storage cover U+A<=UE cumulative insertions rather than peak live U?
42. How does enumerating all interval combinations check results independently of the advancement rule?

### Testing and evidence

43. Why compile the test driver alone when it includes lab.c, and is any external module needed?
44. Which valid fixtures check immediate overlap, endpoint-only contact, exhaustion and repeated calls?
45. How can an original regression expose accepting equality or lowering a candidate?
46. How do custom fixture tests preserve and restore the original input without editing lab.c?
47. What belongs in the single driver, trace, comparison and correction artifact, and why is the supplied smoke test insufficient?

## Teaching references

- [Chapter 10 package](../module_10_priority_queue/README.md)
- [English textbook](../module_10_priority_queue/student/textbook.md) · [한국어 교재](../module_10_priority_queue/student/textbook_korean.md)
- [Instructor guide](../instructor_guide/chapter_10.md)
- [Rubric](../module_10_priority_queue/student/rubric.md)
