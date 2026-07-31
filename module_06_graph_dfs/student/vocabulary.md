# Module 6 Vocabulary — Graph Depth-First Search

Open this reference after completing and preserving the Cognitive Pause.

| Term | Plain-language definition |
|---|---|
| graph | Items plus the direct relationships between them |
| vertex | One item in a graph |
| edge | One direct relationship between two vertices |
| directed edge | An edge that works in one stated direction |
| undirected edge | An edge that connects both ways |
| out-neighbor | The destination of an edge leaving the current vertex |
| route | A sequence that follows stated edges |
| cycle | A route that returns to an earlier vertex |
| source | The vertex where a search starts |
| reachable | Having a route from the stated source |
| algorithm | A precise, repeatable set of steps |
| depth-first search (DFS) | A method that follows one available route deeply before returning to an unfinished choice |
| Boolean | A value that is either `true` or `false` |
| visited array | One Boolean per vertex recording whether that vertex has been discovered and scheduled |
| discover | Reach a vertex for the first time |
| schedule | Arrange for a vertex's work to occur |
| mark | Change one vertex's visited value from `false` to `true` |
| record | Append a processed vertex number to the output |
| function | A named group of instructions that performs one task |
| recursion | A function calling itself directly or through other functions |
| recursive call | A function call made as part of recursion |
| call frame | Saved information for one active function call |
| runtime call stack | Bookkeeping commonly used by a C implementation for active function calls |
| iterative algorithm | An algorithm that repeats with a loop instead of recursive calls |
| loop | Instructions repeated while a stated condition holds |
| Stack | A last-in, first-out collection |
| last in, first out (LIFO) | The newest stored item is the first removed |
| `push` | Add one item at the top of a Stack |
| `pop` | Remove and report the top Stack item |
| explicit vertex-ID Stack | A Stack directly operated by the program that stores vertex numbers |
| frontier | Discovered vertices still waiting to be processed |
| bottom-to-top order | A Stack listing from its oldest item to its removable newest item |
| pointer | A C value that identifies an object's memory location |
| `NULL` | The C pointer value meaning “points to no object” |
| caller | The function or program part that requests another function |
| isolated vertex | A vertex with no edge entering or leaving it |
| connected component | One separate group in an undirected graph whose vertices have routes to one another |
| adjacency matrix | A row-and-column grid that records possible edges |
| adjacency list | One stored list of outgoing neighbors for every vertex |
| `GraphDfsOrder` | Up to 16 recorded vertex numbers plus their count |
| API | Public types and operations available to other code |
| contract | Rules stating what an operation accepts, changes, reports, and preserves |
| output parameter | Caller-provided storage in which a function writes an answer |
| status code | A named result reporting success or one kind of failure |
| validation | Checking whether all required representation rules hold |
| failure preservation | A failed operation leaves the caller's complete old output unchanged |
| limit | A stated maximum |
| allocation | Storage obtained while a program runs |
| allocation failure | Requested storage could not be obtained |
| cleanup | Releasing temporary storage after its use |
| time complexity | A description of how work grows with input size |
| Big-O notation | A compact way to write a pattern of growth as `O(...)` |
| auxiliary space | Temporary working storage separate from input and output |
| `V` | The number of active vertices |
| `E` | The number of stored edges |
| `O(V²)` | Work or storage that can grow like vertex count times vertex count |
| `O(V+E)` | Work or storage that can grow with vertices plus edges |
| `O(V)` | Work or storage that can grow in proportion to vertex count |
| synthetic | Invented for safe practice rather than taken from a real system |

## Exact result names

| Status | Meaning |
|---|---|
| `GRAPH_DFS_OK` | The requested operation succeeded |
| `GRAPH_DFS_INVALID_ARGUMENT` | A required pointer was `NULL` |
| `GRAPH_DFS_OUT_OF_RANGE` | The requested source is not an active vertex |
| `GRAPH_DFS_INVALID_GRAPH` | The entire active stored graph breaks its Module 3 rules |
| `GRAPH_DFS_REQUIRES_UNDIRECTED` | Component counting received a directed graph |
| `GRAPH_DFS_LIMIT` | The requested or needed Stack limit, or maximum, cannot be met |
| `GRAPH_DFS_ALLOCATION` | Temporary Stack storage could not be obtained |

## Three related forms of saved work

- The Stack rule is the general last-in, first-out behavior.
- The explicit vertex-ID Stack is a program-created frontier.
- The runtime call stack commonly stores active recursive call frames.

They follow a similar newest-work-first pattern, but they are not the same
stored object.
