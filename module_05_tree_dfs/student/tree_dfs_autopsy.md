# Tree DFS Autopsy

Do this work before editing the isolated faulty program.

The intended preorder is:

```text
50,30,20,40,70
```

Open `code/autopsy/faulty_preorder.c`, then answer:

1. **Prediction:** What complete sequence will the program print? Explain
   your prediction using the Stack rule “newest item leaves first.”
2. **First broken decision:** Identify the first child-push decision that
   makes the future visit order wrong. Do not merely point at the final
   output.
3. **Smallest fix:** State the smallest change that restores
   root-left-right preorder.
4. **Regression test:** Give one test that would fail if this defect returned.
   A regression test is a test kept to prevent a known defect from returning.

Now run the autopsy target and compare the observed sequence with your
prediction. The program is standalone: it does not use or grade your DFS
implementation.
