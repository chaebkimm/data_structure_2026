# Student Textbook - Connecting Every Site at Minimum Cost

## 1. One model, two questions

A **synthetic** example is invented. A **graph** stores **vertices** (items)
and **edges** (relationships). An **undirected edge** works both ways. A
**weight** is its numeric cost.

A **path** is a sequence of adjoining edges. Dijkstra's **algorithm** is a
finite step-by-step procedure that finds a least-cost path from one
**source**, or start, to every reachable vertex when weights are
nonnegative. Its **shortest-path tree** records one source path per vertex.

Module 15 minimizes the edge total that connects all possible vertices, not
each source route.

## 2. Tree, MST, and forest

Vertices are **connected** when a path joins them. A **cycle** returns to its
start without reusing an edge. A **tree** is connected with no cycle. A
**spanning tree** includes every vertex of a connected graph.

A **minimum spanning tree (MST)** has the smallest spanning-tree total. A
**component** is a largest connected part. A disconnected graph has no
single spanning tree. A **forest** is a collection of trees; a **minimum
spanning forest (MSF)** gives one MST per component. An isolated vertex is
one tree.

If `V` is vertex count and `c` is component count, every spanning forest has
`V-c` selected edges. The count alone proves neither validity nor minimum
cost.

## 3. Compare exact results

Use:

```text
ID0 AB4  ID1 AC4  ID2 BC1  ID3 BD5
ID4 CD2  ID5 CE3  ID6 DE3  ID7 AE10
```

Dijkstra from A records AB, AC, CD, and CE. Their edge sum is 13. Its A-to-C
path is direct and costs 4.

One MST uses AB, BC, CD, and CE:

```text
4 + 1 + 2 + 3 = 10
```

Its A-to-C path goes through B and costs 5. The MST lowers the network's
selected-edge total, not every source route. Equal weights permit four MSTs:
choose AB or AC, choose CE or DE, and always keep BC and CD.

## 4. Store each relationship faithfully

A **logical edge** is one relationship with one edge ID. An **edge list**
stores one record per logical edge. An **incident record** views an edge
from one **endpoint** (a vertex at its end). An **indexed adjacency list**
groups these records by vertex for quick access; an undirected edge appears
twice.

A **self-loop** has one endpoint twice. **Parallel edges** have different
IDs but the same endpoints. A loop cannot join groups and is never selected;
parallel edges remain separate choices.

A **signed weight** may be negative, zero, or positive. Negative weights are
valid for MST algorithms but can break Dijkstra's rule that a removed
smallest source distance is final. MST edges here are two-way; **directed**
means one-way and needs another algorithm.

## 5. Grow with Prim

**Prim's algorithm** grows one tree. A **cut** separates the vertices into
two groups; a **crossing edge** has one endpoint in each. A **safe edge**
leaves some minimum result possible. Prim chooses a minimum crossing edge
from its tree.

For each outside vertex, `key[v]` stores its cheapest known crossing-edge
weight, `parent[v]` stores the other endpoint, and `in_tree[v]` records
membership. A Prim key is one edge weight, not a Dijkstra distance.

The **frontier** is pending work. A **Priority Queue** removes its
first-ranked record. A binary **Heap** is a tree-shaped Priority Queue in
which each position has at most two children.

With **lazy duplicates**, an improvement pushes a new **snapshot**, or saved
candidate, without removing the old. A **stale** snapshot has an old key.
Already-selected vertices are also skipped. **Strict improvement** means
equality changes nothing. The stable Heap removes earlier equal keys first.

From A, Prim selects and updates:

```text
A/0: B=4/A, C=4/A, E=10/A
B/4: select AB; C=1/B, D=5/B
C/1: select BC; D=2/C, E=3/C
D/2: select CD; equal E=3 changes nothing
E/3: select CE
```

Old `C/4`, `D/5`, and `E/10` are skipped. Counts are 8 pushes, 8 pops, 3
stale pops, peak 5, 16 incident scans, 8 crossing tests, and 7 improvements.

## 6. Restart for disconnected input

When the frontier empties, Prim restarts at the smallest unvisited vertex.
The restart has no parent edge and adds no weight.

For vertices A through F, use AB4, BC-2, AC3, two parallel DE1 edges, and
self-loop EE-9; F is isolated. Prim selects AC3, BC-2, and the earlier DE1.
It restarts at A, D, and F. The result has three components, three selected
edges, and total 2. This is an MSF, not an MST.

## 7. Merge with Kruskal

**Kruskal's algorithm** sorts logical edges by signed weight. **Normalized
endpoints** put the smaller ID first; ties use the other endpoint and edge
ID. A **comparator** orders two records. It uses `<` (smaller than) and `>`
(greater than) because subtraction can exceed the signed range.

**Disjoint-set union (DSU)**, or **Union-Find**, maintains nonoverlapping
groups. A **representative root** names a group. `find` obtains it; `union`
combines two groups.

Kruskal scans every edge, selecting only different-root endpoints and then
unioning them. Equal roots would create a cycle. It adds BC, CD, CE, skips
DE, adds AB, then skips AC, BD, and AE: 8 examined, 4 cycle skips, total 10.

Tied algorithms need not return identical edges. On the all-weight-1 square
AD, CD, AB, BC, the fixed tie rules make Prim select AD, AB, CD and Kruskal
select AB, AD, BC. Both totals are 3.

## 8. Validate structure and minimum cost

An **invariant** is a rule for every valid state. A **validator** checks
input membership, unique IDs, no selected loop or cycle, the original
component partition (how vertices are divided into connected groups),
`V-c`, and total.

A **certificate** is checkable evidence. An **exchange check** compares each
unselected non-loop edge with the greatest selected weight on its endpoint
path. A lighter edge proves a cheaper replacement; equality identifies an
alternative minimum.

`int64_t` is C's signed 64-bit whole-number type. **Overflow** exceeds its
range. Canceling opposite signs before accumulation makes the mathematical
total order-independent, accepting a fitting final sum even if one selection
order first forms a running subtotal outside that range.

## 9. Match cost to representation

**Complexity** describes how work grows. `O(n)` grows with all `n` items;
`O(log n)` grows with repeated halving. Let `E` be logical-edge count.
Indexed-adjacency lazy Prim takes `O(V + E log(E+1))` time and `O(V+E)`
**auxiliary state**, meaning extra storage. Kruskal sorting takes
`O(E log E)` plus DSU work growing almost with `E`.

An edge list suits Kruskal. An indexed adjacency list suits Heap Prim.
**Sparse** means relatively few possible edges exist; **dense** means many.
A **matrix** stores one position for every vertex pair. Matrix Prim can use
`O(V^2)` work on dense input. Count work needed to change storage forms.

## 10. Minimum cost is not resilience

**Resilience** is continued required service after failure. Every tree edge
is a **bridge**, an edge whose removal increases component count. Removing
BC from the canonical MST separates A and B from C, D, and E.

Adding an unselected edge creates one alternate route around some failures,
not necessarily all. An MST proves minimum cost only for the validated
stored model. It does not prove weights are genuine or current, links have
enough capacity, failures are independent, access is authorized, or the
whole system is secure.
