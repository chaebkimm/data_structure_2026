# Chapter 9. Finding the Route with the Fewest Steps

## Thinking Logically

### Can we check a map the exact same way we check a top-down structure?

In a top-down structure (like a tree), there is only one downward path to reach any place. But on a free-flowing map, multiple roads can lead to the exact same location, and paths can even loop back around to places you have already visited.

If you just drop all connected neighbors into a waiting line like you do with a tree, the exact same location will get put in multiple times. The search might never finish, or you might just run around in circles repeating the exact same work. You must keep a strict checklist of whether a location has already been put into the line for the very first time.

### How do we visit closer locations first?

First, put your starting location into the waiting line. Every time you take a location out, put all its reachable neighbors at the very back of the line. Because the locations you found first are taken out first, you naturally check all the places that are fewer steps away before you start checking the places that are farther away.

### What do we need to record to rebuild the route later?

To perfectly remember our journey, we track three pieces of information for every single location `v`:

* `discovered[v]`: A simple true/false check showing if location `v` has ever been put into the waiting line.
* `distance[v]`: The absolute minimum number of steps (connections) needed to travel from the starting point to location `v`.
* `predecessor[v]`: The specific location we stepped on right before arriving at `v` on our chosen route.

The locations we actually take out of the line and finish checking are written down in order on a final `visit_order` list. Because a "discovered" location might still be patiently sitting inside the waiting line, the exact moment we discover a place and the moment we actually finish checking it are kept completely separate.

### When do we change the discovery checkmark?

We try putting a brand-new, undiscovered neighbor into the waiting line. The exact moment it successfully goes in, we check off `discovered` as true.

If you mark it *before* putting it in, a location that failed to enter (because the line was full) would falsely look like it was already waiting in line. If you delay marking it until it finally *comes out* of the line, another road might mistakenly try to shove that exact same location into the line again while it is still waiting!

```text
If neighbor v is not discovered yet:
    Put v into the waiting line.
    If putting it in succeeds:
        discovered[v] = true
        distance[v] = distance[current place] + 1
        predecessor[v] = current place
```

After a location is discovered for the very first time, we lock it in and never change these three pieces of information again.

### How do we mark locations we cannot reach yet?

In this practice code, our map has a strict maximum of 16 locations, simply numbered from 0 to 15. The number 16 cannot be a real location number. Also, the maximum number of steps you can take without walking in circles is 15.

Therefore, we cleverly use the number 16 as a special code word meaning "no location" and "no distance".

```text
NO_LOCATION = 16
NO_DISTANCE = 16
```

The starting point is exactly 0 steps away from itself and has no previous location. After the whole search ends, any locations that were never discovered at all will also be left marked with "no distance" and "no location".

### How does the actual search happen?

Let's say our starting location is 0. We check each location's neighbors starting from the smallest number.

```text
0 connects to: [1,2]  1 connects to: [3,4]  2 connects to: [4,5]  3 connects to: [6]
4 connects to: [6]    5 connects to: [4]    6 connects to: [1]    7 connects to: []


```

The waiting line changes like this:

```text
Start             [0]
After checking 0  [1,2]
After checking 1  [2,3,4]
After checking 2  [3,4,5]
After checking 3  [4,5,6]
After checking 4  [5,6]
After checking 5  [6]
After checking 6  []
```

Notice that even when location 2 sees location 4 as a neighbor, it doesn't put 4 in the line again! Location 4 was already discovered when we checked location 1.

```text
visit_order  0,1,2,3,4,5,6
distance     0,1,1,2,2,2,3,16
predecessor  16,0,0,1,1,2,3,16
```

Even though we completely failed to reach location 7, the search process itself is considered a perfect success.

### Why is the very first distance found guaranteed to be the shortest?

The starting point (distance 0) is checked first. Its neighbors drop into the line getting a distance of 1. Because of how the line works, *all* locations with a distance of 1 will be completely checked *before* we ever touch a location with a distance of 2. This exact rule perfectly repeats for every step.

If there was a secretly shorter route to location `v`, the previous location on that shorter route would have been checked earlier. If that happened, `v` would have been discovered earlier too! Therefore, the very first time a location drops into the line, its distance is absolutely guaranteed to be the minimum number of steps.

*(Note: This magic only works if every single connection takes the exact same amount of effort. If some roads are longer or cost more money to travel, our simple waiting line won't notice, and it won't guarantee the cheapest route.)*

### How do we rebuild the route using previous locations?

Start from your destination (6) and simply follow the `predecessor` (previous location) backwards!

```text
6 <- 3 <- 1 <- 0
```

If you carefully flip this backward list, you get the perfect, shortest route from the start to the destination.

```text
0 -> 1 -> 3 -> 6
```

The route to the starting point itself is just the starting point, taking 0 steps. If you ask for a route to an undiscovered, unreachable location (like 7), the tool safely returns an "unreachable" error.

Our safety tool checks if the relationship between the distances and previous locations makes mathematical sense. However, because this tool doesn't look at the map itself, you must check the original map separately if you want to prove real roads actually existed between those locations.

### Does the answer change if we store the map differently?

A grid-style map checks every single possible slot in a row to find connections. A list-style map only reads the specific connections that actually exist. The way they hold information is totally different, but as long as both methods check the neighbors in the exact same order (smallest to largest), the final search result is perfectly identical!

This chapter provides code tools for both a grid map and a list map. Both tools create the exact same final result package without changing your original map at all.

### What if the waiting line becomes full during the search?

You can choose exactly how many locations are allowed to wait in the line at the same time (between 0 and 16). If the required line size ever goes over your chosen limit, the process safely stops and returns a limit error.

The search result and the rebuilt route are strictly created inside a temporary, hidden workspace first. They are only copied to your actual output variables when the entire process finishes flawlessly. If it hits a limit or breaks halfway, your old information stays perfectly safe.

## Calculating Efficiency

### Efficiency of checking a grid-style map?

If there are `V` total locations, processing just one location forces you to check all `V` possible slots in its row. Because you eventually process all locations, the total work grows very rapidly like a square, taking $O(V^2)$ work. The memory needed to build the grid is also $O(V^2)$.

### Efficiency of checking a list-style map?

It processes each location exactly once and only checks the actual connections that exist. If there are `V` locations and `E` connections, the work is simply $O(V+E)$. The memory needed to build the list is also exactly $O(V+E)$.

### How much extra memory is needed during the search?

The discovery checklists, the recorded distances, the previous locations, the final visit order, and the waiting line all need one slot per location. This means the extra memory needed grows steadily with the number of locations, taking $O(V)$ space.

### Efficiency of rebuilding the route?

First, it quickly verifies the full array of search results, taking $O(V)$ work. After that, it simply follows the previous locations backward exactly once. If the route length is `L`, this tracking takes $O(L)$ time. Because a route can never be longer than the total number of locations, rebuilding the whole route is incredibly fast, taking at most $O(V)$ time.

## Glossary

### Hop

One step moving from one vertex to another across a single edge.

### Unweighted Graph

A graph where all edges are treated equally as one hop.

### Graph BFS (Breadth-First Search)

A search method that uses a queue to visit vertices starting from those with the fewest hops from the starting point.

### Discovery

The state of marking a vertex when it is first put into the queue so it is not put in again.

### Distance

In this chapter, it means the minimum number of edges passed from the starting point to a specific vertex.

### Predecessor

The vertex immediately before the current vertex on the chosen path.

### Reachable

The state where a vertex can be reached by following edges from the starting point.

### Adjacency Matrix

A way of storing whether an edge exists between every possible pair of vertices using grid slots.

### Adjacency List

A way of storing only the actual connected neighbors specifically for each vertex.

## Coding Plan

### Preparing the BFS Result

* **Fill default values:** Set all discovery marks to `false`, and set distances and predecessors to 16.
* **Put starting point in:** Put the starting point into the queue, change its discovery mark to `true`, and set its distance to 0.
* **Use temporary result:** Do not change the caller's result before the search successfully finishes.

### Searching the Graph

* **Take out vertex:** Take the front vertex out of the queue and write it in `visit_order`.
* **Check neighbors:** Look at outgoing neighbors starting from the smallest vertex number.
* **Put new vertex in:** Put undiscovered neighbors into the queue.
* **Save path info:** If pushing succeeds, record the discovery mark, distance, and predecessor.
* **Confirm result:** Copy the temporary result to the output only after the queue is empty.

### Rebuilding the Path

* **Check result:** Inspect the number of BFS results and the relationship between distances and predecessors.
* **Check reachability:** If the destination was never discovered, return `GRAPH_BFS_UNREACHABLE`.
* **Save backwards:** Follow the predecessors backwards from the destination and put them in a temporary array.
* **Flip order:** Read the temporary array backwards to save the path from the starting point to the destination.
* **Confirm path:** Copy the finished temporary path to the output.

### Using Both Storage Methods

* **Matrix search:** In `graph_bfs_matrix`, check all destination slots in one row.
* **List search:** In `graph_bfs_list`, check only the saved neighbors of the current vertex.
* **Unify order:** Both methods must process neighbors starting from the smallest number.

## C Code

### Searching an Adjacency Matrix Graph

```c
#include "graph_bfs.h"

Graph graph = {0};
GraphBfsResult result = {0};
GraphBfsPath path = {0};

graph_init(&graph, 8U, GRAPH_DIRECTED);
graph_add_edge(&graph, 0U, 1U);
graph_add_edge(&graph, 0U, 2U);
graph_add_edge(&graph, 1U, 3U);
graph_add_edge(&graph, 1U, 4U);
graph_add_edge(&graph, 2U, 4U);
graph_add_edge(&graph, 2U, 5U);
graph_add_edge(&graph, 3U, 6U);
graph_add_edge(&graph, 4U, 6U);
graph_add_edge(&graph, 5U, 4U);
graph_add_edge(&graph, 6U, 1U);

if (graph_bfs_matrix(&graph, 0U, 3U, &result) ==
    GRAPH_BFS_OK) {
        /* result.distance[6] is 3. */

        if (graph_bfs_reconstruct_path(&result, 6U, &path) ==
            GRAPH_BFS_OK) {
                /* path.vertices[0..3] are 0, 1, 3, 6. */
        }
}
```

### Recording After a Successful Discovery

```c
#include "graph_bfs.h"
#include "vertex_queue.h"

static GraphBfsStatus discover_vertex(
        VertexQueue *queue,
        size_t from_vertex,
        size_t to_vertex,
        GraphBfsResult *result)
{
        VertexQueueStatus status;

        status = vertex_queue_enqueue(queue, to_vertex);
        if (status == VERTEX_QUEUE_LIMIT) {
                return GRAPH_BFS_LIMIT;
        }
        if (status != VERTEX_QUEUE_OK) {
                return GRAPH_BFS_INVALID_ARGUMENT;
        }

        result->discovered[to_vertex] = true;
        result->distance[to_vertex] =
                result->distance[from_vertex] + 1U;
        result->predecessor[to_vertex] = from_vertex;
        return GRAPH_BFS_OK;
}
```

The result is not changed until the queue successfully accepts the vertex.

### Searching an Adjacency List Graph

```c
GraphAdjList list = {0};
GraphBfsResult list_result = {0};

if (graph_adj_list_init(&list, 4U, GRAPH_DIRECTED) ==
    GRAPH_ADJ_LIST_OK) {
        graph_adj_list_add_edge(&list, 0U, 1U);
        graph_adj_list_add_edge(&list, 0U, 2U);
        graph_adj_list_add_edge(&list, 1U, 3U);
        graph_adj_list_add_edge(&list, 2U, 3U);

        graph_bfs_list(&list, 0U, 2U, &list_result);
        graph_adj_list_destroy(&list);
}
```

### Following Predecessors Backwards

```c
size_t reverse[GRAPH_MAX_VERTICES];
size_t reverse_count = 0U;
size_t current = 6U;

for (;;) {
        reverse[reverse_count] = current;
        reverse_count = reverse_count + 1U;

        if (current == result.source) {
                break;
        }

        current = result.predecessor[current];
}

for (size_t i = 0U; i < reverse_count; i = i + 1U) {
        path.vertices[i] = reverse[reverse_count - i - 1U];
}
path.count = reverse_count;
```