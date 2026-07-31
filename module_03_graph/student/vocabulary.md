# Module 3 Word Reference — Open Only After the Pause

This reference is intentionally released after the five-minute individual
activity. Do not use it during Stage A or during that timed activity. Some
definitions give the names and rules that the earlier questions ask you to
construct.

**C**  
The programming language used for this course’s programming work.

**code**  
Instructions written for a computer.

**program**  
A group of instructions a computer can run.

**function**  
A named block of code that performs one task.

**model**  
A simplified description used for reasoning.

**representation**  
A chosen way to store or show information.

**data structure**  
A planned way to organize information in a program.

**graph**  
A model made of objects and their relationships.

**vertex**  
One object in a graph. The plural is **vertices**.

**edge**  
One direct relationship between two vertices.

**endpoint**  
Either vertex named by an edge.

**set**  
A collection in which an item appears at most once.

**ordered pair**  
A pair whose positions have different roles. `(u, v)` places `u` first and
`v` second.

**edge set**  
The set of all edges in a graph.

**directed edge**  
An edge with one direction. `(u, v)` records `u → v`.

**directed graph**  
A graph whose edges have direction.

**undirected edge**  
An edge with no direction; it connects both endpoints.

**undirected graph**  
A graph whose edges have no direction.

**weight**  
A number attached to an edge, such as distance, time, or cost.

**weighted graph**  
A graph that stores a weight for each edge.

**unweighted graph**  
A graph that records whether edges exist but stores no edge weight.

**index**  
A numbered position. C begins indexes at zero.

**array**  
A numbered row of matching values.

**two-dimensional array**  
An array of rows.

**matrix**  
A rectangular grid of values arranged in rows and columns.

**cell**  
One position in a matrix.

**Boolean value**  
A value with exactly two choices: `true` or `false`. `bool` is C’s name for
storing such a value.

**adjacent**  
Directly joined by an edge.

**adjacency matrix**  
A matrix with one row and one column per vertex; row `u`, column `v` records
whether `u → v` exists.

**diagonal**  
The cells of a matrix whose row and column indexes match.

**mirrored cells**  
The two matrix cells `[u][v]` and `[v][u]`, whose row and column positions
trade places.

**symmetric matrix**  
A matrix in which every cell equals its mirrored cell across the diagonal.

**diagram**  
A visual representation that shows vertices as labeled marks and edges as
lines or arrows.

**equivalent representations**  
Different representations of exactly the same objects and relationships.

**neighbor**  
Another vertex joined by an edge.

**source**  
The vertex where a directed edge begins.

**destination**  
The vertex where a directed edge ends.

**out-neighbor**  
The destination of an edge leaving a vertex.

**in-neighbor**  
The source of an edge entering a vertex.

**degree**  
The number of edges touching a vertex in an undirected graph.

**out-degree**  
The number of directed edges leaving a vertex.

**in-degree**  
The number of directed edges entering a vertex.

**route**  
A sequence of vertices in which every consecutive pair has the required
edge.

**path**  
A route that does not repeat a vertex.

**cycle**  
A route that returns to its starting vertex without repeating another
vertex.

**reachable**  
Able to be arrived at from a stated start by following a route.

**connected**  
Joined by a route in an undirected graph.

**connected component**  
A largest group of vertices in an undirected graph in which every vertex is
connected to every other vertex in the group.

**isolated vertex**  
A vertex with no edge.

**state**  
The information currently stored by a program.

**contract**  
The rules stating what code accepts, changes, reports, and preserves.

**invariant**  
A rule that is true in every valid completed state.

**fixed vertex set**  
A group of vertices whose count is selected when the graph is created and
does not change afterward.

**active vertex index**  
An index from zero through one less than the graph’s stored vertex count.

**self-loop**  
An edge from a vertex to itself.

**parallel edges**  
Repeated edges with the same endpoints and, in a directed graph, the same
direction.

**simple graph**  
A graph with no self-loop and no parallel edges.

**malformed graph**  
A stored graph whose values break its invariant.

**operation**  
One task provided by a data structure’s code.

**query**  
An operation that asks for information without changing the graph.

**validator**  
Code that checks stated rules.

**sparse graph**  
A graph with few edges compared with the number of possible edges.

**edge-list representation**  
A stored sequence containing one endpoint pair per edge.

**adjacency-list representation**  
A representation that stores a collection of outgoing neighbors for each
vertex.

**dynamic storage**  
Computer memory requested or released while a program runs.

**type**  
A description of the kind of value C stores.

**variable**  
Named storage for a value.

**struct**  
A C type that groups related values.

**field**  
One named value inside a struct.

**enum**  
A C type whose allowed choices have names.

**`size_t`**  
A nonnegative whole-number C type used for counts and indexes.

**`#define`**  
A C instruction that gives a fixed name to text used by the program.

**`Graph`**  
The C type that stores this module’s vertex count, direction kind, and
Boolean adjacency matrix.

**`GraphKind`**  
The C enum whose choices are `GRAPH_DIRECTED` and `GRAPH_UNDIRECTED`.

**`GraphNeighbors`**  
The C type that stores a neighbor count followed by vertex indexes.

**status code**  
A named result that reports success or one kind of failure.

**`GraphStatus`**  
The C enum used for the graph functions’ status codes.

**`GRAPH_MAX_VERTICES`**  
The fixed name for this module’s limit of 16 vertices.

**algorithm**  
A precise, step-by-step method for completing a task.

**tree**  
A restricted relationship model with one starting item called the root, one
immediately preceding item called a parent for every other item, no cycle,
and a route from the root to every item.

**arena**  
A prepared storage area used for objects.

**ArrayList**  
A numbered sequence that can replace its storage to make room for more items.

**synthetic data**  
Invented information used for safe practice or testing.

**network**  
A group of devices or services that can communicate. A service is a program
that performs a task for other programs.

**permission**  
A rule that allows an action.

**exploitability**  
Whether a real weakness could actually be used to cause harm.
