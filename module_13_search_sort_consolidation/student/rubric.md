# Module 13 Rubric

Assess one artifact using the [lab](lab.md) and [evidence record](evidence_template.md). Total: 100 points.

| Criterion | Points | Full-credit evidence |
| --- | ---: | --- |
| Search and first-match reasoning | 20 | Original index 2 versus sorted index 1; half-open invariant, equality-left behavior, final bound check, misses, and unchanged search input |
| Sorting and stability reasoning | 25 | Correct insertion prefixes and eight shifts; divide/merge/copy-back trace; independent sorted order/multiplicity checks; tagged equal-record trace and exact strict/equal conditions rather than claiming integer output proves stability |
| Caller contracts and reproducible tests | 20 | Three original groups with predictions; valid size/storage/sorted/scratch conditions; empty/singleton/extreme/boundary/repeated calls; build commands, diagnostics, and observed output |
| Consolidation and workload selection | 25 | All six scenarios compare preparation, query, update, ordering, and space; justified method and alternative; distinguishes list relink/search, heap minimum/arbitrary lookup, exact lookup/traversal, and scoped hash/AVL assumptions |
| Costs and correction | 10 | Concrete counts before growth notation; sorting preparation versus repeated queries; source/scratch/recursion storage separated; one preserved misconception corrected with evidence |
| **Total** | **100** | |

The complete implementation is supplied. No additional old structure, DSU/MST, or general-purpose sort implementation is required. Optional record-valued stability tests do not replace the required paper/source explanation. Equivalent typed, oral, tabular, or diagram explanations receive equal credit. Speed and drawing quality are not criteria.
