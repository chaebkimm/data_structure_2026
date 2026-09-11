# Module 3 Evidence Record

Complete this record after the Stage E lab. A numbered list may replace any
table if it uses the same headings.

Name: ____________________________  
Compiler or approved CI: ____________________________

## 1. One graph in three forms

Show the original seven-account follower graph as a diagram or line-by-line
arrow description, the directed edge set, and all seven active matrix rows.
Use 0 Mina, 1 Joon, 2 Sora, 3 Dae, 4 Hana, 5 Leo, and 6 Nuri, with edges
`0 → 1`, `1 → 2`, `2 → 0`, `2 → 3`, `4 → 5`, and `5 → 4`. Explain why the
three representations agree and what each arrow means.

____________________________________________________________________

## 2. Stored representation

Complete the meaning of each field or name:

- `vertex_count`:
- `grid[from][to]`:
- `GRAPH_MAX_VERTICES`:

Why are `grid[from][to]` and `grid[to][from]` separate facts?

____________________________________________________________________

## 3. Invariant evidence

State the rules for the vertex count and active indexes, values in grid cells,
inactive rows and columns, and diagonal cells. For one rejected request, state
what remained unchanged.

____________________________________________________________________

## 4. Core operation trace

| Step | Expected evidence | Actual evidence | Pass? |
|---|---|---|---|
| Initialize seven accounts | Full 16-by-16 grid is zero; active indexes are 0–6 | | |
| Add `0 → 1`, `1 → 2`, `2 → 0`, `2 → 3`, `4 → 5`, `5 → 4` | Canonical seven-row matrix with six `1` cells | | |
| Guarded lookups of `0 → 1` and `1 → 0` | `1` and `0`; opposite follows are separate | | |
| Count Sora's out-degree | Row 2 contains two `1` cells | | |
| Remove `2 → 3` | Only `grid[2][3]` changes | | |
| Count Sora's out-degree again | Row 2 is `[1, 0, 0, 0, 0, 0, 0]`; count is 1 | | |
| Reject a self-loop or inactive index with count 7 | State/output preserved; index 7 is inactive | | |

## 5. Exactly three student-authored tests

For each test, record a distinct claim and why it adds evidence.

1. Test and rationale:

   ____________________________________________________________________

2. Test and rationale:

   ____________________________________________________________________

3. Test and rationale:

   ____________________________________________________________________

## 6. Cost and representation choice

- one direct edge lookup:
- one add or remove:
- one out-degree count:
- physical storage:

Give one situation in which an edge list or adjacency list could avoid unused
matrix cells:

____________________________________________________________________

## 7. Ghost-connection autopsy

Use the separate autopsy fixture with counts 4, then 3, then 4. Keep its
observations separate from the seven-account follower trace.

- first invalid cell:
- invariant broken:
- delayed symptom:
- repair:
- regression claim:

## 8. Stage D reflection, model boundary, and transfer

These questions follow the Stage C attempt and Stage D reading of either
`textbook.md` or `textbook_korean.md`.

List the original follower graph's weak and strong components. Explain Dae's
membership, why a singleton component need not be isolated, and why maximal
does not mean the largest group. After removing only `2 → 3`, explain which
memberships change and which stay the same.

____________________________________________________________________

For Mina, distinguish directly followed accounts, other accounts in the same
strong component, and accounts in the same weak component but a different
strong component. Could an eligible post by Dae rank above one by Sora?
Explain what information beyond component membership a ranking rule needs.
Why would restricting Sora's feed to Sora's strong component omit a directly
followed account?

____________________________________________________________________

Why does a follow edge, path, or component neither guarantee that a post
appears in a feed nor grant permission to view it? Explain why the component
rules are a hypothetical feed design, not a claim about a particular SNS.

____________________________________________________________________

Choose a fixed ArrayList, a binary tree, or a directed graph for each and give
one reason: an ordered event sequence; a left/right hierarchy; follow
relationships that can contain shared destinations or cycles.

____________________________________________________________________

## 9. Correction note

My initial model:

____________________________________________________________________

The evidence that changed or strengthened it:

____________________________________________________________________
