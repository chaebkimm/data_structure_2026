# Module 12 — Stage E: Lab and Evidence

Start with `student/lab.md`, then edit only:

- the three numbered `TODO` sections in `code/starter/dijkstra.c`; and
- the three `TODO` test sections in `code/tests/test_student.c`.

`TODO` marks an unfinished section that the student must complete.

Students complete:

1. textual weight parsing that rejects a negative value before conversion;
2. the Dijkstra loop with strict relaxation, lazy duplicate pushes,
   stale-pop skipping, and guarded cost addition; and
3. bounded predecessor-path reconstruction.

Weighted-graph ownership and the minimum frontier are supplied.
`arc_count` is the number of stored one-way connections. Each run uses a
frontier limit of `arc_count + 1`, never more than 241. `INF` is `SIZE_MAX`;
overflow or a candidate exactly equal to `INF` returns
`DIJKSTRA_COST_RANGE` and preserves caller output.

The canonical A-through-F run must produce cost 6, path `A,C,D,E`, 8 pushes,
8 pops, 3 stale pops, peak frontier size 4, and 17 Heap comparisons.

The autopsy—a careful investigation after a failure—is standalone, uses
defined unsigned wrap, and stays within fixed checked bounds.

Submit the files and evidence listed in the lab, then complete
`student/evidence_template.md`.
