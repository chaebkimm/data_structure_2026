# Stage C — Investigation: Linear Accessible Format

## How to use this version

This version has the same learning targets as the standard investigation. It
contains no response table or drawing requirement. It works with a **screen
reader**, which is software that reads on-screen text aloud, as well as
keyboard navigation, meaning movement with keyboard keys; speech input,
meaning answering by voice; or a text-only response.

Open it after completing and preserving the five-minute individual response.
The word reference may now be used.

Before Stage D, complete and preserve Sections A, B, D, E, and G. Sections C,
F, H, I, and J may be completed during the announced independent work
window.

A **representation** is a chosen way to store or show information. A
**model** is a simplified description used for reasoning. A **graph** is a
model of objects and their relationships. A **vertex** is one
object in a graph, and an **edge** is one direct relationship between two
vertices. A visual **diagram** shows vertices as labeled marks and edges as
lines or arrows. In this version, a line-by-line arrow description provides
the same relationship information as a diagram.

## A. Translate one model three ways

A **directed edge** has one direction. Its **source** is where the edge
starts, and its **destination** is where the edge ends.
A **directed graph** uses directed edges. A **program** is a group of
instructions a computer can run, and a **service** is a program that performs
a task for other programs.

Use these six invented services:

1. Vertex 0 is Gateway.
2. Vertex 1 is Web.
3. Vertex 2 is Admin.
4. Vertex 3 is Database.
5. Vertex 4 is Monitor.
6. Vertex 5 is Archive.

Use these facts:

1. Gateway leads to Web.
2. Gateway leads to Admin.
3. Web leads to Database.
4. Admin leads to Database.
5. Database leads to Monitor.
6. Monitor leads to Web.
7. Archive has no edge.

**Isolated** means having no edge.

### A1. Diagram-equivalent description

For each vertex, list the destinations of arrows leaving that vertex.
Include Archive and state that it is isolated.

Response:

A **set** is a collection in which an item appears at most once. An
**ordered pair** puts the source first and the destination second. An
**edge set** is the set of all edges.

### A2. List every relationship

Write the complete directed edge set using ordered pairs.

Response:

A **matrix** is a grid of horizontal rows and vertical columns. An
**adjacency matrix** uses one row and one column for each vertex. An
**index** is a numbered position. Its row-`u`, column-`v` **cell**, meaning
one grid position, answers whether `u → v` exists. The letters `u` and `v`
stand for vertex indexes. Write `1` for yes and `0` for no.

### A3. State the matrix as row sequences

For each row from 0 through 5, state six values in column order 0 through 5.
For example, the response format for one row is “row 0: value, value, value,
value, value, value.”

Response:

**Equivalent representations** describe exactly the same objects and
relationships.

### A4. Check that all three forms match

How many arrows, ordered pairs, and `1` cells should the three directed
representations contain?

Response:

Explain how all three forms show that Archive is isolated.

Response:

## B. Compare one-way, two-way, and numbered relationships

An **undirected edge** connects both ways. An **undirected graph** uses
undirected edges. In a matrix, the two cells `[u][v]` and `[v][u]` are
**mirrored cells** because their row and column positions trade places.

The top-left-to-bottom-right **diagonal** contains cells with equal row and
column numbers. A matrix is **symmetric** when every cell equals its mirrored
cell across that diagonal.

### B1. One undirected edge

For the undirected edge `{1, 4}`, which two cells must contain `1`?

Response:

### B2. Symmetry

Why must the complete matrix of an undirected graph be symmetric?

Response:

Why does the directed edge `0 → 1` not require `1 → 0`?

Response:

A **weight** is a number attached to an edge, such as distance, time, or
cost. A **weighted graph** stores weights. An **unweighted graph** stores
only whether each edge exists. A **Boolean value** is either `true` or
`false`.

### B3. Limit of a Boolean cell

The course matrix stores one Boolean value per possible edge. Can it also
store a delay of 12 milliseconds? A **millisecond** is one thousandth of a
second. Explain what information would have to change.

Response:

This module implements only the unweighted Boolean form.

## C. Name immediate relationships

Two vertices are **neighbors** when an edge joins them. In a directed graph,
an **out-neighbor** is the destination of an edge leaving a vertex, and an
**in-neighbor** is the source of an edge entering a vertex.

For an undirected graph, **degree** is the number of edges touching a vertex.
For a directed graph, **out-degree** counts edges leaving a vertex and
**in-degree** counts edges entering it.

Use the directed six-vertex model from Section A.

### C1. Neighbors of Database

List the in-neighbors and out-neighbors of vertex 3.

Response:

### C2. Counts for Web

Give the in-degree and out-degree of vertex 1. Name the edge or edges counted
in each answer.

Response:

### C3. Isolated vertex

Give the in-degree and out-degree of vertex 5.

Response:

### C4. Undirected degree

Suppose an undirected vertex has edges to vertices 0, 2, and 5. What is its
degree?

Response:

## D. Follow several steps by hand

A **route** is a sequence of vertices in which every consecutive pair has the
required edge. In a directed graph, every arrow must be followed in its
stated direction. A **path** is a route that does not repeat a vertex. A
**cycle** is a route that returns to its starting vertex without repeating
another vertex.

A destination is **reachable** from a starting vertex when at least one
route leads from the start to the destination. The starting vertex is
reachable from itself by a route containing no edges.

For this section, follow relationships by hand; do not write code for the
process.

### D1. Path

Is `0, 1, 3, 4` a directed path? Explain by checking each consecutive pair.

Response:

### D2. Cycle

Is `1, 3, 4, 1` a directed cycle? Explain.

Response:

### D3. Reachability from Gateway

List every vertex reachable from vertex 0, including vertex 0.

Response:

### D4. Direction matters

Give a directed path from vertex 2 to vertex 1. Can vertex 1 reach vertex 2
in the given model? Explain.

Response:

## E. Name groups only when direction is absent

In an undirected graph, two vertices are **connected** when a route joins
them. A **connected component** is a largest group of vertices in which
every vertex is connected to every other vertex in the group. “Largest”
means that no additional vertex can be included while keeping that rule
true.

Consider an undirected graph with vertices 0 through 5 and edges `{0, 1}`,
`{1, 2}`, and `{3, 4}`. Vertex 5 is isolated.

### E1. Undirected groups

List every connected component.

Response:

### E2. Directed language

For the directed six-vertex model, do not call the vertices reachable from 0
a connected component. State the precise reachability sentence instead.

Response:

Why does direction make “connected component” ambiguous here?

Response:

## F. Test the course rules

A **contract** states what a program accepts, changes, reports, and
preserves. A **state** is the information currently stored. An **invariant**
is a rule that is true in every valid completed state. An **endpoint** is a
vertex at one end of an edge. A **self-loop** is an edge from a vertex to
itself. **Parallel edges** are repeated edges with the same endpoints and,
in a directed graph, the same direction. A **simple graph** has no self-loop
or parallel edges.

A **fixed vertex set** means the number of vertices is chosen when the graph
is created and does not change. An **active vertex index** is a number from 0
through one less than the stored vertex count. A **malformed graph** has
stored values that break the invariant.

**Code** means instructions written for a computer. An **operation** is one
task the graph code provides.

The course graph follows these rules:

1. The vertex count is no greater than 16.
2. Active indexes remain fixed after creation.
3. Only active rows and columns describe edges, and operations reject
   inactive indexes.
4. Every diagonal matrix cell is `false`, so no self-loop exists.
5. A Boolean cell stores at most one copy of a directed edge.
6. An undirected graph has equal mirrored cells.

Cycles are allowed. Several edges may enter the same vertex.

### F1. Classify proposed additions

For each independent request, write `accept` or `reject` and name the rule:

1. Add `2 → 2`.
2. Add another copy of the existing `0 → 1`.
3. Add `1 → 0` to the directed model.
4. Add `4 → 0`.
5. Add an edge involving index 6 when the vertex count is 6.

Response:

### F2. Boolean storage limit

Why can one Boolean cell not store two parallel copies of an edge?

Response:

A **validator** is code that checks rules.

### F3. Whole-model check

Why must an undirected validator compare mirrored cells throughout the active
matrix?

Response:

## G. Compare three storage choices

Let `V` mean the number of vertices and `E` mean the number of stored edges.
An **edge-list representation** stores a sequence of endpoint pairs. An
**adjacency-list representation** stores, for each vertex, a collection of
its outgoing neighbors. **Dynamic storage** is memory requested or released
while a program is running. An edge **query** asks whether an edge exists
without changing the graph.

The three choices have these traits:

1. An adjacency matrix stores `V × V` Boolean cells. One direct edge query
   inspects one cell. Finding all outgoing neighbors scans one complete row.
   It is useful when many possible edges exist or direct queries are common,
   but it reserves cells for missing edges.
2. An edge list stores `E` endpoint pairs. A direct query or a request for
   all outgoing neighbors usually scans the pairs. It is simple when a task
   processes every edge in turn.
3. An adjacency list stores `V` collections plus neighbor entries. A direct
   query usually scans one vertex’s neighbors, and reporting those neighbors
   reads that collection. It suits models with few edges but requires more
   work to manage changing storage.

An undirected adjacency list normally records each edge in both endpoints’
neighbor collections. This course returns to adjacency lists after more work
with dynamic storage.

A **sparse graph** has few edges compared with the number of possible edges.

### G1. Few relationships

Why can a matrix waste storage for a large sparse graph?

Response:

### G2. Frequent direct questions

Which representation gives the most direct answer to “Does `u → v` exist?”
Explain.

Response:

### G3. Process every edge

Which representation is especially simple when a task reads every edge once
and does not need frequent direct queries?

Response:

### G4. Neighbor work

Which representation avoids scanning a full matrix row when a vertex has
only a few neighbors?

Response:

## H. Transfer an earlier hierarchy model

A **hierarchy** arranges items in levels. A **root** is its starting item. A
**parent** is the item directly above another item, and a **child** is the
item directly below. A **tree** is a hierarchy with one root, exactly one
parent for every other item, no cycle, and a route from the root to every
item.

### H1. Rules that no longer apply

Which tree rules are intentionally removed when the model allows the two
edges `1 → 3` and `2 → 3`?

Response:

### H2. Edge toward an earlier vertex

Why does `4 → 1` prevent the relationship model from being a tree?

Response:

An **arena** is a prepared storage area used for objects.

### H3. Rule that still matters

Name one general correctness rule that matters for both a fixed tree arena
and this fixed graph.

Response:

### H4. Transfer sentence

Complete: “A tree is useful when __________; a graph is needed when
__________.”

Response:

## I. Respect the limits of the security model

**Synthetic data** is invented for safe teaching. A **network model** is a
simplified description of possible communication. A **permission** is a rule
that allows an action. **Exploitability** means whether a real weakness could
actually be used to cause harm.

In this activity, an edge means “communication is permitted in the invented
model.” It does not prove that communication occurred, that a real route
exists, or that a service is exploitable.

### I1. Supported conclusion

What can the edge `1 → 3` support you in saying?

Response:

### I2. Unsupported conclusion

Name one claim that the same edge does not prove.

Response:

## J. Conclude by hand

An **exploration procedure** is a step-by-step method for visiting vertices.
Formal procedures and their programs arrive in later modules. For now,
inspect only the tiny model by hand.

### J1. Manual reachability record

Starting at vertex 0, state a valid route each time you claim that a new
vertex is reachable. Stop when no new vertex can be justified.

Response:

An **ArrayList** is a resizable numbered sequence.

### J2. Choose a structure

Choose an ArrayList, a tree, or a graph for each case and give one reason:

1. A sequence of event codes in arrival order.
2. A strict folder hierarchy with no shared item.
3. Communication permissions that may include several routes and loops.

Response:

### J3. Exit sentence

Complete: “The model is no longer a tree because __________; the Boolean
matrix records __________.”

Response:
