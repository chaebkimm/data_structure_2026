# Safe Frontier Autopsy

This standalone program uses five local vertices and an eight-slot checked
pending Queue. Every array index and insertion is bounded. It requests no
memory and uses only a synthetic graph.

Before running it:

1. draw the graph encoded in `main`;
2. predict the removal order;
3. predict the largest pending state; and
4. predict the predecessor of vertices 3 and 4.

Run the observation and compare it with Module 9's published discovery
contract. Your report must identify:

1. the first vertex scheduled more than once;
2. the first decision that permitted that repeated scheduling;
3. the corrected pending state after vertex 2;
4. the corrected removal order and predecessors; and
5. one regression test that would expose the same defect.

Do not replace the fixture with a live network, service inventory, or
production communication source.
