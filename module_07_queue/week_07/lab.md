# Week 7 lab — One linked Queue artifact

Read [the lesson](textbook.md) and `code/linked_queue.h`. Start from a zero
object, `LinkedQueue q = {0}`. Operations require valid Queue state; arbitrary
corrupt/dangling input is outside this small lab's contract.

## Implementation

Complete only `lq_enqueue` and `lq_dequeue` in
`code/starter/linked_queue.c`. Use `lq_node_create` and `lq_node_release` so
allocation-failure and live-node tests work. `peek`, destruction, validation,
and allocation wrappers are supplied. Trace their behavior and explain why
destruction saves the next link before release.

Run from `code/`:

```sh
make starter-compile
make starter-core
make student-tests
```

The untouched starter compiles but is expected to fail behavioral core tests.
Use the first failed assertion to guide a correction. Warning flags are
included. On supported GCC/Clang toolchains also run:

```sh
make starter-core BUILD_DIR=build-sanitize CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -fno-omit-frame-pointer'
```

Add three original cases to `tests/test_student.c`:

1. FIFO with repeated values or negative integers; peek must not remove.
2. Singleton → empty → enqueue again, asserting both pointers and size.
3. Forced allocation failure on a nonempty Queue, proving unchanged values,
   links, size, and live-node count; destroy and prove zero live nodes.

## Trace and comparison

Preserve an initial prediction and correction for the lesson's linked trace.
Show or describe which node owns each live value, and when a node is released.
Diagnose the hypothetical final-dequeue bug that leaves `tail` unchanged;
identify its first invalid later write and a regression test.

Trace the supplied circular Queue's capacity-4 example from the lesson.
Compare logical order, fixed capacity versus allocation failure, storage,
and cleanup. No circular-Queue implementation is required.

## Submission and rubric

Submit one artifact: starter source, student tests, reproducible test/compiler
output, linked ownership trace, circular trace/comparison, corrected prediction,
and two sentences explaining why BFS also needs discovery state.

| Criterion | Weight |
|---|---:|
| FIFO and representation reasoning | 20% |
| Correct operations and boundary cases | 25% |
| Ownership, allocation failure, and cleanup | 20% |
| Tests and reproducible tool evidence | 15% |
| Costs and representation selection | 10% |
| Correction and BFS transfer explanation | 10% |

General list mutations, a second Queue implementation, and concurrency are
optional and do not gate the core grade.
