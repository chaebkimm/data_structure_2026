# Module 8 Evidence — Processing data in stored order

Name: ____________________  Date: ____________________

Use the [lab](lab.md), [workbook](class_material.md), and unchanged [source](lab.c). Submit queue, tree, and maze reasoning together. Preserve predictions and add corrections. All coordinate pairs mean `{y, x}`.

## 1. Which queue states did I predict?

Record actual endpoint changes for the linear queue and the paper circular comparison.

| Trace | First prediction | Observation and correction |
| --- | --- | --- |
| Enqueue `{1,1}`, `{2,1}`, `{2,2}` and drain | | |
| 25 linear writes followed by 25 removals | | |
| 25-slot circular queue: fill 24, remove two, append two | | |

```text
front means:
rear means:
linear empty condition:
linear enqueue/dequeue preconditions:
maintained queue bound and how each valid operation preserves it:
why a drained linear queue can still lack a write position:
circular convention, empty/full conditions, and reserved slot:
```

## 2. How does the tree establish levels?

Use root A, children B/C, B's children D/E, and C's left child F. Enqueue existing left children before right children. This is a paper exercise.

```text
pending after A:
pending after B:
pending after C:
complete processing order and depths:
how I would retain the current depth:
why a valid tree has no duplicate scheduling:
what cycles or shared destinations change in a graph:
why an unprocessed graph neighbor may enter the comparison stack again:
why an already processed node is skipped when popped from that stack:
why BFS never enqueues a discovered neighbor again:
```

## 3. Which current source did I run?

Record the command and output from the current lab driver. The source has no main function; the separate driver includes it. No tree or linked-pool source is needed.

```text
source: module_08_graph_bfs/student/lab.c
driver: module_08_graph_bfs/code/tests/test_lecture.c
build/run command:
observed output:
where bfs resets queue and distances:
valid-start and border assumptions:
```

## 4. How does a point enter the queue?

Explain the two fields and the discovery action before recording the trace.

```text
struct point field order:
{2,3} accesses which maze cell:
right/left/down/up neighbors of {2,2}:
N and INF meanings:
which operation marks a passage discovered:
why pending distances do not decrease from front to back:
how each inner brace pair initializes one maze row:
how whole-point copying, passing, and returning work:
when short-circuit OR omits the distance read:
review of increment timing and switch/break/continue scope:
```

| Processed point | Distance | Pending points, front to back | Newly discovered points |
| --- | --- | --- | --- |
| Initial | — | | |
| `{1,1}` | | | |
| `{2,1}` | | | |
| `{2,2}` | | | |
| `{3,1}` | | | |
| `{2,3}` | | | |
| `{3,2}` | | | |
| `{3,3}` | | | |
| `{1,3}` | | | |

```text
why {3,1} does not enqueue the waiting {3,2} again:
why first discovery gives a shortest distance:
reached passage count:
total enqueue/dequeue counts:
peak pending count:
final front/rear:
```

## 5. Which fresh-run checks did I observe?

State an expected result before executing each valid case. Make temporary maze changes in the driver and restore the baseline.

| Check | Expected | Actual | Explanation or correction |
| --- | --- | --- | --- |
| Start `{1,1}`, target `{3,3}` | | | |
| Reverse start `{3,3}`, target `{1,1}` | | | |
| Wall start `{0,0}` | | | |
| Block `{2,1}`; start `{1,1}` and target `{3,3}` | | | |
| Restore `{2,1}` and repeat baseline | | | |
| One original valid check in a separate driver | | | |

## 6. What route could we recover?

Write one shortest route on paper. The supplied code records distances only; explain the previous-point extension from the concept slides separately.

```text
target distance:
one route as {y,x} points:
number of edges:
how to save the discovering current point as the parent cell:
how backward following reaches the start:
why reversing the collected points gives the start-to-target route:
why the existing lab does not already store this route:
```

## 7. How much work and space are required?

Count actual work before generalizing to R rows, C columns, and P reached passages.

```text
number of initialized distances:
number of neighbor candidates:
reset cost:
traversal cost:
reserved queue/distance space:
why total writes, not just peak pending, bound this linear queue:
one original prediction I corrected and why:
```

The optional checked matrix/list API is outside this submission. Its statuses, sentinel 16, and predecessor arrays are not evidence about the current maze implementation.
