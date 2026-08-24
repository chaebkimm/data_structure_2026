# Chapter 6. Exploring Maps Without Going in Circles

## Thinking Logically

### What changes if we follow one path like in a tree?

In a tree, there is only one straight, downward path to reach a specific item. But in a free-flowing map, multiple connections can lead to the exact same item, and paths can even loop all the way back to an item you have already visited.

```text
0 → 1   0 → 2   1 → 3
2 → 3   3 → 4   4 → 1
5 is not connected to any item.

```

We can still use our strategy of following one path all the way to a dead end. But if we don't remember the items we have already visited, we might loop around the `1 → 3 → 4 → 1` path forever, or accidentally process item 3 twice.

### When should we leave a mark to avoid checking an item again?

We keep a simple true/false checklist for each item. If an item is marked "true", it means we have already found it and reserved its turn to be checked.

We must check off an item **the exact moment we drop it into our waiting container**, not later when we finally take it out. This completely stops other connections from trying to shove the exact same item into the container again while it is already waiting patiently inside.

We only leave a checkmark if it successfully goes into the container. If the container is full and fails to take the item, but we mark it as "true" anyway, it won't actually be in the container, and we will accidentally skip checking it forever!

### In what order should we add neighbors to visit smaller numbers first?

In our tall waiting container, the last item dropped in is always the first one to come out. So, if we look at our current item's neighbors and drop them in starting from the *largest* number, the *smallest* number will go in last—meaning it will pop out first!

```text
Drop the starting item 0 in and mark it.

Repeat until the container is empty:
    Take out an item and write it down in the final list.
    Check its neighbors starting from the largest number.
    Drop a neighbor into the container if it is not marked yet.
    If it successfully goes in, mark it as true.

```

In the example map above, if we start from 0, the container changes like this. The container is written from bottom to top.

| Processed Item | Inside the Container | Final Visit Order |
| --- | --- | --- |
| Before start | `0` | Empty |
| 0 | `2, 1` | `0` |
| 1 | `2, 3` | `0, 1` |
| 3 | `2, 4` | `0, 1, 3` |
| 4 | `2` | `0, 1, 3, 4` |
| 2 | Empty | `0, 1, 3, 4, 2` |

Item 5 is not in the final list because there is no path leading to it from 0. The starting item is always included in the final list.

### Can we find the same items using repeating instructions?

Yes! When we arrive at an item, we mark it, write it down, and then simply tell the computer to run the exact same instructions for all unvisited neighbors, starting from the smallest number. The exact order we visit them might be slightly different than using the container, but the final group of items we reach will be exactly the same.

The repeating instructions use the computer's hidden background memory. The container method uses our own custom-built container to hold the item numbers.

### How do we find items we can't reach from our starting point?

A single search only finds the items you can actually reach from where you started. If we want to find everything, we can scan the entire map. Every time we see an unmarked item, we start a brand-new search. This lets us count completely separate, independent groups (like islands) one by one.

If we make all the connections in our example two-way streets, items 0 to 4 form one connected group, and the lonely item 5 forms a second independent group. So, there are 2 groups in total. A completely empty map has 0 groups.

In a one-way map, just because you can go down a connection doesn't mean you can come back. Because of this, our group-counting tool will safely reject one-way maps.

### How do we protect the result if the search fails?

Before searching, we make sure the map grid from Chapter 3 is valid. The starting item must actually exist, and our container is strictly limited to 16 items.

We build the final visit list in a temporary workspace first. If the map is broken, or if we hit the container limit or run out of memory, we throw away the workspace and do not change the user's existing list. We only copy the finished list when everything succeeds perfectly.

## Calculating Efficiency

### How long does it take to process one item in a grid map?

To find neighbors in our grid map, we must check all `V` possible destination boxes in that item's row. Because we eventually check every item, checking all `V` rows takes an amount of work that grows very rapidly, like the square of the items: `O(V^2)`.

### How long does it take if we use a different map style?

If we stored our map as a simple list of connected paths instead of a giant grid, we would only check the actual paths that exist. This takes `O(V + E)` time, where `E` is the number of connections. Even for the exact same search, the time it takes changes depending on how the map is stored!

### How much extra space is needed during the search?

Because the true/false checklist and the waiting container can hold up to the total number of items, it requires a steady amount of extra space proportional to the total items, `O(V)`.

### How long does it take to count independent groups?

Every item is marked exactly once. Because we have to check all the rows in our grid map to find connections, it still takes `O(V^2)`. (If it were a list of connected paths, it would be `O(V + E)`).

## Glossary

### Depth-First Search (DFS)

A search method that follows one branch all the way to the end before returning to check the remaining branches.

### Visited Mark

A value that remembers whether each vertex has already been found to prevent processing it again.

### Reachability

The ability to reach another vertex by following the edges from a starting vertex.

### Cycle

A path that follows edges and loops back to the vertex where it started.

### Connected Component

The largest group of vertices in an undirected graph that can all reach each other.

## Coding Plan

### Searching with Recursion (Repeating Instructions)

* **Mark:** Change the checklist to `true` the exact moment you enter a vertex.
* **Record:** Add the current vertex to the visit result.
* **Progress:** Check outgoing edges starting from the smallest number, and call the instructions again for unvisited neighbors.
* **Complete:** Copy the temporary workspace to the final output only after the whole process is fully built.

### Searching with a Stack (Waiting Container)

* **Start:** Push the starting vertex into the stack, then immediately mark it as `true`.
* **Visit:** Pop the vertex out and record it in the result.
* **Reserve:** Check neighbors starting from the largest number. Only mark the vertices that were successfully pushed into the stack.
* **Clean up:** Free the stack's memory whether the search succeeds or fails.

### Counting Connected Components

* **Check:** Make sure the graph is a two-way (undirected) graph.
* **Search:** Look at all the vertices starting from 0, and start a brand-new DFS whenever you find an unmarked vertex.
* **Calculate:** Increase the connected component count by 1 every time you trigger a new DFS.
* **Finish:** Output the final calculated count after checking all vertices.

### Protecting the Output on Failure

* **Inspect:** First, check the graph, the starting vertex, the output address, and the stack limits.
* **Build:** Create the visiting order and the component count entirely inside temporary variables.
* **Apply:** Update the user's actual output variables only when all tasks succeed completely.

## C Code

### How does the recursive search continue?

```c
static void recursive_visit(
    const Graph *graph,
    size_t vertex,
    bool seen[GRAPH_MAX_VERTICES],
    GraphDfsOrder *order
)
{
    size_t neighbor;

    seen[vertex] = true;
    order->vertices[order->count] = vertex;
    order->count += 1U;

    for (neighbor = 0U; neighbor < graph->vertex_count; ++neighbor) {
        if (graph->adjacency[vertex][neighbor] && !seen[neighbor]) {
            recursive_visit(graph, neighbor, seen, order);
        }
    }
}

```

The public function first checks the graph and the starting vertex. It fills `seen` and the temporary `GraphDfsOrder` with zeros, runs this function, and then copies only the perfectly finished order to the output.

### When do we leave a mark in the iterative (stack) search?

```c
stack_status = vertex_stack_push(&stack, start_vertex);
if (stack_status == VERTEX_STACK_OK) {
    seen[start_vertex] = true;
}

while (status == GRAPH_DFS_OK) {
    size_t vertex;
    size_t cursor;

    stack_status = vertex_stack_pop(&stack, &vertex);
    if (stack_status == VERTEX_STACK_UNDERFLOW) {
        break;
    }
    if (stack_status != VERTEX_STACK_OK) {
        status = map_stack_failure(stack_status);
        break;
    }

    candidate.vertices[candidate.count] = vertex;
    candidate.count += 1U;

    for (cursor = graph->vertex_count; cursor > 0U; --cursor) {
        size_t neighbor = cursor - 1U;

        if (graph->adjacency[vertex][neighbor] && !seen[neighbor]) {
            stack_status = vertex_stack_push(&stack, neighbor);
            if (stack_status != VERTEX_STACK_OK) {
                status = map_stack_failure(stack_status);
                break;
            }
            seen[neighbor] = true;
        }
    }
}

```

The `map_stack_failure` helper changes stack limit errors and memory allocation failures into `GRAPH_DFS_LIMIT` and `GRAPH_DFS_ALLOCATION` error codes. When the loop ends, it safely destroys the stack and outputs the `candidate` workspace only if `status` is a perfect success.

### How do we count connected components?

```c
size_t component_count = 0U;
size_t vertex;

for (vertex = 0U; vertex < graph->vertex_count; ++vertex) {
    if (!seen[vertex]) {
        component_count += 1U;
        recursive_visit(graph, vertex, seen, &all_vertices);
    }
}

*out_component_count = component_count;

```

This code runs only after confirming that the graph is a valid, undirected (two-way) graph. For directed maps, it will safely reject the request and return `GRAPH_DFS_REQUIRES_UNDIRECTED`.