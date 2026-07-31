# Safe BFS Autopsy

This standalone program uses only five local nodes and a five-slot pending
array. Every insertion is checked before it writes, so the observation is
bounded and does not rely on undefined behavior.

Before running it:

1. draw the `A` through `E` tree from `main`;
2. predict the complete processing order;
3. predict which node with key `44` the search will report; and
4. record the predicted depth.

Then build and run the program. Compare the observation with Module 8's
published processing contract.

Your autopsy report must identify:

1. the first decision after processing `A` that differs from the contract;
2. the smallest source change that restores the contract;
3. the corrected complete order and selected match; and
4. one regression test that would fail if the same defect returned.

Do not replace the bounded fixture with a live filesystem, process tree, or
production policy source.
