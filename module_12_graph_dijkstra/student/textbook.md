# Chapter 12. Finding the Route with the Lowest Total Cost

## Thinking Logically

### Is a route always cheaper if it has fewer steps?

Our previous search method found the route with the fewest steps (connections). That route is only guaranteed to be the cheapest if every single step costs exactly the same amount of money.

If different roads have different toll costs, the answer changes completely! Let's compare these two routes:

```text
A -> E            Total Cost: 14
A -> C -> D -> E  Total Cost: 2 + 2 + 2 = 6
```

The first route has only one step, but it is extremely expensive. Now, we must compare the *sum* of the road costs, not just the number of steps.

### What should we remember to compare?

We need a place to write down the absolutely lowest cost we have found so far to travel from our starting point to every other location. We save this number in a list called `distance`. If we haven't found a route to a location yet, we write down a special "Infinity" mark meaning "too far to reach right now." In our code, this mark is exactly the absolute maximum number the computer can hold (`SIZE_MAX`).

```text
distance[starting point] = 0
distance[everywhere else] = Infinity
```

We also keep a `predecessor` list, where we write down the location we stepped on right before arriving at our destination on our chosen cheap route. If we suddenly discover a cheaper route, we erase our old notes and update *both* the new cost and the new previous location together!

### How do we calculate the new candidate cost?

Imagine we are currently standing at location `u`, and we see a road leading to location `v` that costs `weight`. The new candidate cost to travel to `v` by passing through our current spot is simple math:

```text
candidate cost = distance[u] + weight
```

We only accept this new candidate route if it is strictly *cheaper* than the old cost we had already written down. If the cost is exactly the same, we just stick with our old record.

```text
Is candidate cost < distance[v] ?
```

This simple action of updating our notes with a better price is incredibly important. However, we only officially erase our old notes after we successfully drop this new, better candidate into our waiting line. This safely prevents a disaster where we update our notes but fail to actually queue the candidate up for checking!

### Which location should we process first?

Among all the candidate routes currently waiting in line, we must *always* take out the one with the smallest total cost first. If we use the clever, self-sorting tree (Min-Heap) from Chapter 11, it will naturally hand us the cheapest candidate instantly!

If two candidates happen to have the exact same total cost, the one that got into the line first comes out first. The location numbers themselves do not change this order.

### What do we do with old records if we find a cheaper route later?

Imagine we drop a candidate into the line saying it costs 9 to reach location B. But later, we discover a brilliant new shortcut that only costs 4! Instead of wasting time digging through the waiting line to find and fix the old `B/9` ticket, we just write a brand-new `B/4` ticket and drop it into the line too.

```text
Inside the waiting line: B/4, B/9
Our official notes: distance[B] = 4
```

Because our line sorts by cheapest price, `B/4` will pop out first. We process it normally. Much later, when the old `B/9` ticket finally pops out, we compare it against our official notes. Because 9 doesn't match our official cost of 4, we instantly know it is an old, outdated ticket! We simply throw it straight in the trash without checking any of its roads.

Leaving old tickets in the line and throwing them away when they pop out saves us from writing incredibly complicated code to edit random spots inside the waiting line.

### When can we lock in the final cost?

When we pull the absolute cheapest candidate out of the line (and it's not an outdated ticket), we officially lock in the cost for that location. Because all future roads cost 0 or more, it is mathematically impossible to find a cheaper route to this location later!

*(Note: This logic completely shatters if roads can have negative costs, like a road that pays you -7 to travel on it! If a -7 road appears later, it could suddenly make a locked-in cost cheaper. Because of this, the tool in this chapter strictly refuses to work on maps with negative costs).*

### In what order do the numbers change in a real example?

Let's use locations `A=0` to `F=5`. The roads and their costs are:

```text
A->B (9)   A->C (2)   A->E (14)
B->D (0)   B->E (8)
C->B (2)   C->D (2)
D->E (2)
```

There are no roads leading to F. As we pull candidates from the line and update prices, the process goes exactly like this:

```text
Take A/0: Found B=9, C=2, E=14
Take C/2: Updated B=4, D=4
Take B/4: D's candidate 4 ties (kept old), Updated E=12
Take D/4: Updated E=6
Take E/6: No roads going out
Take B/9: Threw away old outdated ticket!
Take E/12: Threw away old outdated ticket!
Take E/14: Threw away old outdated ticket!
```

The locked-in, final cheapest costs from A to F are `0, 4, 2, 4, 6, Infinity`. The order we locked them in was `A, C, B, D, E`. In this search, we attempted to update prices 8 times and succeeded 7 times. We dropped 8 tickets into the line (including the start) and pulled exactly 8 tickets out.

### How do we rebuild the route we found?

To get the exact route to E, we just follow our "previous location" notes backwards starting from E: `E, D, C, A`. If we flip that list around, we get our perfect route: `A, C, D, E`.

```text
A -> C -> D -> E
2 + 2 + 2 = 6
```

If we try to follow the previous locations but end up taking more steps than there are total locations on the map, it means there is an infinite loop (a cycle) broken in our notes! Also, because our rebuilding tool doesn't look at the actual map, you must check the map yourself to prove those roads actually existed.

The route to the starting point is just the starting point, costing 0. If you ask for a route to an unreachable place like F, the tool returns an "unreachable" error and doesn't ruin your old route variables.

### Are "unreachable" and "too expensive" the same thing?

We specifically reserved the massive number `SIZE_MAX` to mean "there is no route." It is absolutely not allowed to be used as a real road cost.

Our tool that reads costs written as text strictly only accepts positive numbers (or zero). It allows spaces and a single `+` sign.

| Input Text | Result |
| --- | --- |
| `"0"`, `"  +42\t"` | Perfectly accepted as 0 and 42 |
| `"-1"` | Rejected instantly because it is negative |
| `""`, `"+"`, `"12x"`, `"1 2"` | Rejected because it is not a clean, single number |
| A number `SIZE_MAX` or bigger | Rejected for being too massive to hold |

Right before we add two costs together, we double-check the math. If adding them causes the number to overflow the computer's limits or exactly hit our special "Infinity" mark, it returns a "cost range" error. This brilliantly separates the idea of "there is no route" from "the route is too expensive for the computer to calculate."

## Calculating Efficiency

### Efficiency of preparing the map?

If there are `V` locations and `E` roads, writing down the starting notes and checking the saved roads takes `O(V+E)` work.

### Efficiency of checking the roads?

We only check the roads leaving a location when we officially lock it in. Because we eventually try to update the price for every single road, this checking part takes `O(E)` work.

### Efficiency of using the waiting line?

A single road can trigger a successful price update at most exactly once. So, counting the starting point, the absolute maximum number of tickets dropped into the line is `E+1`. Dropping or pulling one ticket takes `O(log(E+1))` work.

Adding it all together, the total running time is `O(V + E log(E+1))`. Our specific practice code handles up to 16 locations, 240 roads, and limits the waiting line to 241 tickets.

### Efficiency of rebuilding the route?

Because we just follow the previous locations backward, taking at most `V` steps, it takes an incredibly fast `O(V)` work.

### How much extra memory is used?

We need `O(V)` space to hold our official notes (costs and previous locations). We need `O(E)` space for the waiting line (including all the outdated tickets). The total extra space needed is `O(V+E)`.

## Glossary

### Weighted Graph

A graph where values like cost or distance are attached to each edge.

### Tentative Distance

The smallest cost found so far from the starting point to a vertex.

### Relaxation

The process of updating the distance and predecessor if the candidate cost going through the current vertex is smaller.

### Frontier

A collection of candidate records waiting to be processed in the heap.

### Stale Entry

A heap record that no longer matches the current distance because a cheaper value was saved later.

### Dijkstra's Algorithm

An algorithm that finds the lowest-cost path from one starting point in a graph with no negative edges.

### INF (Infinity)

A special value excluded from actual costs to show that a path hasn't been found yet.

## Coding Plan

### Reading a String Cost

* **Check input:** Make sure the text string and output variable exist.
* **Skip spaces:** Skip leading spaces and a single `+` sign.
* **Reject negatives:** Return `WEIGHTED_GRAPH_NEGATIVE_WEIGHT` if it starts with `-`.
* **Check range:** Make sure the math won't exceed the `size_t` limit before attaching a new digit.
* **Check end:** Reject if there are any weird characters after the number (other than trailing spaces).
* **Check reserved value:** If the final result equals `SIZE_MAX`, reject it so it isn't saved as a real cost.

### Preparing the Shortest Path Result

* **Create temporary result:** Fill all distance and predecessor notes with the special "Infinity" mark.
* **Set starting point:** Change the starting point's distance note to 0.
* **Prepare heap:** Set the line limit to the total number of roads plus one (for the starting ticket).
* **Put first record:** Drop `(starting point, cost 0)` into the line.

### Processing the Cheapest Record

* **Take minimum record:** Pull the cheapest ticket out of the line.
* **Filter old records:** Instantly skip it if the ticket's cost doesn't match our official distance note.
* **Finalize vertex:** Officially mark the location as locked-in and record the finalization order.
* **Check addition:** Double-check that adding the new cost won't overflow `size_t` or hit `DIJKSTRA_INF`.
* **Update (Relax):** If the new candidate cost is strictly smaller, update the official notes *only after* successfully dropping the new ticket into the line.
* **Confirm result:** Copy the temporary workspace to the user's `DijkstraResult` only after the entire search finishes flawlessly.

### Reconstructing the Path

* **Check result:** Verify the mathematical relationships inside the result package using `dijkstra_result_validate`.
* **Check destination:** Distinguish between location numbers that don't exist and locations that are simply unreachable.
* **Save backwards:** Follow the predecessors backwards from the destination and put them into a temporary list.
* **Prevent cycles:** If it loops backwards more times than there are locations, trigger an invalid result error.
* **Flip order:** Copy the final list to `DijkstraPath` so it perfectly reads from start to destination.

## C Code

### Appending a Digit to the Cost String

```c
size_t digit = (size_t)(*cursor - '0');

if (candidate > (SIZE_MAX - digit) / 10U) {
        return WEIGHTED_GRAPH_WEIGHT_OUT_OF_RANGE;
}

candidate = candidate * 10U + digit;
```

### Skipping Outdated Heap Records

```c
DijkstraFrontierEntry entry;

frontier_status = dijkstra_frontier_pop(&frontier, &entry);
if (frontier_status != DIJKSTRA_FRONTIER_OK) {
        return fail_after_frontier(
                &frontier,
                map_frontier_failure(frontier_status)
        );
}

if (entry.distance != candidate.distance[entry.vertex]) {
        candidate.stale_pop_count =
                candidate.stale_pop_count + 1U;
        continue;
}
```

### Checking Cost Range and Updating (Relaxation)

```c
if (candidate.distance[entry.vertex] == DIJKSTRA_INF ||
        edge->weight >
                DIJKSTRA_INF - candidate.distance[entry.vertex]) {
        return fail_after_frontier(
                &frontier,
                DIJKSTRA_COST_RANGE
        );
}

size_t relaxed_distance =
        candidate.distance[entry.vertex] + edge->weight;

if (relaxed_distance == DIJKSTRA_INF) {
        return fail_after_frontier(
                &frontier,
                DIJKSTRA_COST_RANGE
        );
}

if (relaxed_distance < candidate.distance[edge->to]) {
        frontier_status = dijkstra_frontier_push(
                &frontier,
                edge->to,
                relaxed_distance
        );

        if (frontier_status != DIJKSTRA_FRONTIER_OK) {
                return fail_after_frontier(
                        &frontier,
                        map_frontier_failure(frontier_status)
                );
        }

        candidate.distance[edge->to] = relaxed_distance;
        candidate.predecessor[edge->to] = entry.vertex;
}
```

### Gathering Previous Locations Backwards

```c
size_t current = destination_vertex;
size_t reverse_count = 0U;

for (;;) {
        if (reverse_count >= result->vertex_count) {
                return DIJKSTRA_INVALID_RESULT;
        }

        reverse_vertices[reverse_count] = current;
        reverse_count = reverse_count + 1U;

        if (current == result->source) {
                break;
        }

        current = result->predecessor[current];
        if (current >= result->vertex_count) {
                return DIJKSTRA_INVALID_RESULT;
        }
}
```