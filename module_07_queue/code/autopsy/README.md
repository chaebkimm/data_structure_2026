# Isolated Queue Autopsy

`faulty_wrap.c` is a complete standalone program. It does not include or link
the student Queue and contains no undefined behavior.

The capacity-three training Queue begins with:

```text
physical slots: [10 STALE] [20] [30]
head: 1
size: 2
logical events: 20, 30
```

It has room for event `40`, but one intentional state decision causes the
attempt to be rejected. The program checks every physical index before using
it, so execution stays inside the array and always produces the same result.

Before running it:

1. predict every printed line;
2. identify the first incorrect state decision; and
3. describe the smallest correction and its required precondition.
