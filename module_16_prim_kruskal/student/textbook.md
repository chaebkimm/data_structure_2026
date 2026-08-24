# Chapter 16. Connecting All Locations at the Lowest Cost

## Thinking Logically

### Does collecting the cheapest individual routes make the cheapest overall connection?

In Chapter 12, our tool found the absolute cheapest route from one single starting point to every other location. Our goal this time is completely different! We don't care about the fastest personal route from A to B. We just want to connect *all* the locations together into one giant network so you can reach anywhere, while keeping the total amount of money spent on building those roads as small as possible.

Let's look at this two-way map. `ID0 AB(4)` means road ID 0 connects town A and town B, and it costs 4 to build.

```text
ID0 AB(4)  ID1 AC(4)  ID2 BC(1)  ID3 BD(5)
ID4 CD(2)  ID5 CE(3)  ID6 DE(3)  ID7 AE(10)
```

If you ask our old route-finding tool from Chapter 12 to find paths from A, it will tell you to build roads AB, AC, CD, and CE. The total money spent is 13.

But there is a much cheaper way to connect every town: build roads AB, BC, CD, and CE! The total money spent drops to 10. In this cheaper network, traveling from A to C forces you to go through B (A-B-C) costing 5, which is technically worse than the direct road of 4.

This proves a vital rule: building the cheapest overall network and finding the cheapest personal travel routes give you completely different answers!

### How many roads should we build?

If you connect all the towns on the map without accidentally building any pointless circular loops, you create a clean, perfect, branching network (a tree shape). If this network successfully reaches every single town on the map, it is a complete connecting network.

Out of all the thousands of possible ways to connect the towns, the one specific network with the absolutely smallest total price tag is our grand champion!

If your map happens to be physically broken into separate islands, you obviously cannot link everyone into one giant network. Instead, you just build the cheapest possible network for each separate island. The final result is just a collection of independent networks (a forest). Even a completely lonely town with zero roads counts as its own tiny network!

If there are `V` total towns and `c` separate islands on the map, the absolute perfect network will always safely use exactly `V - c` roads. However, just picking the right number of roads doesn't magically guarantee they are fully connected, loop-free, and cheapest!

### Which road should we pick while building?

Let's start building! We claim town A first. This instantly divides the world into two groups: towns already safe inside our growing network (A), and towns still waiting outside (B, C, D, E).

We simply look at all the roads acting as "bridges" crossing the gap between our inside group and the outside group, and we pick the absolute cheapest one! We add that new town into our network, and we keep repeating this simple choice to grow it outward.

```text
Inside Network | Waiting Outside
     A         | B, C, D, E
```

Any network that connects everyone *must* build at least one bridge crossing between these two groups. Why is picking the cheapest one perfectly safe? If the absolute cheapest possible network somehow didn't use the cheap bridge we just picked, we could force it in! Adding our cheap bridge would create a loop, and if we simply broke the loop by deleting a more expensive road, the overall price tag would get even smaller! Because of this logic, there is always a champion network that includes the cheapest crossing road.

### What do we write down for the towns waiting outside?

For every town `v` that is still waiting outside, we keep a sticky note tracking the single cheapest bridge that can connect it directly to our growing network.

```text
best_cost    The price of the cheapest single bridge we found so far.
best_parent  The town already inside the network it connects to.
best_edge    The specific ID number of that bridge.
in_network   A simple true/false mark showing if the town is already inside.
```

Notice that `best_cost` is *not* a massive running total from the starting point like in Chapter 12! It is just the raw price of one single road crossing the gap.

### How do we update our waiting line if we find a cheaper bridge?

When we find a cheaper bridge for a waiting town, we don't dig through the waiting line to fix the old ticket. We just write a brand-new, cheaper ticket and toss it into the line!

When we finally pull a ticket out, if the price, parent, or road ID written on it doesn't perfectly match our official sticky notes, we know it's an old, outdated ticket. We simply throw it in the trash! We also throw it away if the town has already been brought safely into the network.

We do not write a new ticket if the cost is exactly the same as our old note. If tickets tie inside the line, the one that got in first comes out first.

Starting from A, the building process looks like this:

```text
Take A/0:  Found bridges B=4(via A), C=4(via A), E=10(via A)
Take B/4:  Brought B in using ID0. Updated notes for C=1/B, D=5/B
Take C/1:  Brought C in using ID2. Updated notes for D=2/C, E=3/C
Take D/2:  Brought D in using ID4. New bridge for E costs 3, ties old best (ignored)
Take E/3:  Brought E in using ID5.
```

The chosen road IDs are `0, 2, 4, 5`, and the total money spent is exactly 10. The outdated tickets `C/4`, `D/5`, and `E/10` were safely thrown away when they popped out later.

### What if the map has disconnected islands?

If our waiting line becomes completely empty but there are still lonely towns left unpicked on the map, it means we hit the ocean! We just start a brand-new network on the next unvisited town with the smallest ID number. This new starting point doesn't need a parent road and adds exactly 0 to the total bill.

Let's look at a broken world with three independent islands:

```text
AB(4), BC(-2), AC(3) | two different DE(1) roads | EE(-9) | isolated town F
```

Our tool will safely pick AC(3), BC(-2), and one DE(1) road. It will start fresh networks at A, D, and F. It successfully chose 3 roads, and the total cost sum is exactly 2.

Because we aren't adding up travel distances, this tool works perfectly even if you have weird roads that cost negative money to build (they pay you)! If a road pays you, we will gladly pick it if it's the cheapest connection.

We absolutely never pick silly roads that just loop from a town straight back to itself. However, if there are two completely different roads connecting the exact same two towns (parallel roads), we treat them fairly as separate choices and pick the cheaper one.

For a completely empty map with zero towns, the result is a perfectly empty network with zero costs and zero roads chosen.

### What if we just sort every single road by price first?

There is a completely different, brilliant way to build the cheapest network! First, sort absolutely every road in the world from cheapest to most expensive. Every single town starts out as its own independent 1-person team (using the team-merging tool from Chapter 14).

Then, just look at the roads one by one, starting with the absolute cheapest: If the road connects two towns on *different* teams, build it and instantly merge the teams together! If the road connects two towns that are already on the *same* team, a path already exists, so building it would just create a pointless, expensive loop. We just skip it!

For our map, the 8 roads are judged exactly in this order:

```text
ID2 BC (1)   Teams different? Picked!           Sum = 1
ID4 CD (2)   Teams different? Picked!           Sum = 3
ID5 CE (3)   Teams different? Picked!           Sum = 6
ID6 DE (3)   Same team! Trash (Creates Loop)
ID0 AB (4)   Teams different? Picked!           Sum = 10
ID1 AC (4)   Same team! Trash (Creates Loop)
ID3 BD (5)   Same team! Trash (Creates Loop)
ID7 AE (10)  Same team! Trash (Creates Loop)
```

This sorting method picked IDs `2, 4, 5, 0`. The order it built them is completely different than our first method, but the final network shape and the total 10 bill are absolutely identical!

### Why is sorting the roads first guaranteed to be safe?

If you split a team away from the rest of the world, you create a boundary gap. The road we are currently looking at crosses that exact gap.

Because we are checking from cheapest to most expensive, any cheaper road crossing that exact same gap would have already been looked at! If we had picked it, the towns would already be on the same team. Therefore, the road we are looking at right now is mathematically guaranteed to be the absolute cheapest available bridge!

### Can both methods be correct even if they pick different roads?

Yes! If multiple roads have the exact same price tag, there can be multiple "cheapest" networks. On our map, after building BC and CD, we could finish by picking *either* AB or AC, and *either* CE or DE! All four of those combinations cost exactly 10.

Our two building methods must perfectly agree on the final lowest total bill. They do not have to agree on the exact road IDs they picked to get there!

### Is it enough if just the final price matches?

Even if the final price looks perfect, the network might illegally use roads that don't exist, or accidentally contain a hidden loop! Our heavy diagnostic tool separately verifies all of these strict rules:

* Do the chosen roads actually exist on the map, and are there no duplicate IDs?
* Are there no self-looping roads, and is the final network completely free of loops?
* Does it successfully connect absolutely every town on every island?
* Is the total number of roads exactly `V - c`, and is the math for the final bill perfectly correct?

It also aggressively checks if the network is truly the cheapest possible. If we can add any unpicked road, create a loop, and then break that loop by removing a more expensive road, it proves the network wasn't the cheapest! This is a massive, heavy check, so we don't run it during normal everyday building.

### In what order do we add negative and massive positive numbers?

Road costs and the final bill are stored in massive computer numbers (`int64_t`). They can be negative, 0, or positive.

If we blindly add them in the exact order they are picked, the temporary math might explode past the computer's absolute limits, even if a negative number later would have brought it back down! To safely prevent a false crash, our math tool carefully groups the positive and negative amounts separately, cancels them out safely, and only then checks if the final total fits securely inside the computer's limits.

If the final bill is genuinely too massive to hold, the tool returns an "out of range" error and safely leaves your old variables completely untouched.

### Is the cheapest network safe against disasters?

If you break just one single road in a perfect network, the entire thing splits into two disconnected halves! The cheapest network *only* guarantees you saved money.

If you want your network to survive a road breaking (resilience), you absolutely must spend extra money to build backup roads! Even then, just adding one extra road doesn't magically guarantee you will survive all disasters. Our tool also doesn't care if the prices are accurate, if the roads physically exist, or if you have legal permission to build there!

## Calculating Efficiency

### Efficiency of the "building outward" method (Prim)?

If there are `V` towns and `E` physical roads, setting up a quick-reference list takes $O(V+E)$ work once. As each town is brought into the network, we check its connected roads exactly once, so checking all of them takes $O(V+E)$ work.

### Efficiency of the "building outward" waiting line?

Every time we find a cheaper road, we drop one note into the line. We also drop one note for every starting point. The absolute maximum number of tickets dropped in is `E+V`. In our specific code, this caps at exactly 136.

Managing the line with outdated tickets takes $O(E \log(E+1))$ work. Processing new starting points takes $O(V)$ work. The total time is incredibly fast at $O(V + E \log(E+1))$, and it takes $O(V+E)$ extra memory space.

### Efficiency of the "sort every road" method (Kruskal)?

Building the giant list of roads takes $O(E)$ work, and sorting it perfectly from cheapest to most expensive takes $O(E \log E)$ work. After that, using the team-merging tool takes almost zero extra time per road.

Because sorting is the heaviest task, the overall time is $O(E \log E)$. It uses $O(V+E)$ space to hold the road list and the team tracking notes.

### Efficiency of double-checking the entire result?

Our heavy diagnostic tool checks the input and aggressively traces the paths for every single road that wasn't picked. The full check takes massive $O(V + E + EV)$ work. The specific step to logically prove the network is truly the cheapest takes $O(EV)$ work.

### Which storage method fits best?

The "building outward" method (Prim) works perfectly with a list-style map, letting you instantly see all roads connected to a town. The "sort every road" method (Kruskal) works perfectly with a giant raw list of roads, since it just sorts them all at once anyway.

If you have a map with only a few towns but millions of roads, a completely different tree-growing tool that scans a massive grid might be better. The actual practice code in this chapter uses the quick-reference lists and the self-sorting waiting line!

## Glossary

### Spanning Tree

A subgraph that connects all vertices of the original graph without creating any cycles.

### Minimum Spanning Tree

The spanning tree that has the smallest possible sum of edge costs.

### Minimum Spanning Forest

A collection of Minimum Spanning Trees, one for each connected component of a disconnected graph.

### Cut

A boundary that divides the vertices into two non-overlapping groups.

### Crossing Edge

An edge that connects a vertex on one side of a cut to a vertex on the other side.

### Prim's Algorithm

An algorithm that repeatedly picks the cheapest edge connecting the current tree to an outside vertex (The "building outward" method).

### Kruskal's Algorithm

An algorithm that looks at all edges from cheapest to most expensive, picking ones that do not create cycles (The "sort every road" method).

### Parallel Edges

Separate edges that have different IDs but connect the exact same two endpoints.

### Resilience

The ability of a network to maintain necessary connections even when some edges fail.

## Coding Plan

### Preparing the Undirected Graph

* **Check vertex count:** Accept from 0 up to exactly 16 vertices.
* **Add edges:** Save the endpoints, `int64_t` cost, and a new `edge_id` into two incident records.
* **Preserve parallel edges:** Treat records with the same endpoints but different IDs as completely separate, competing roads.
* **Preserve self-edges:** You can put them in the input, but both tools will safely skip them during selection.
* **Bundle into one edge:** Combine two incident records with the same ID into a single `UndirectedEdge`.

### Building a Forest with the Growing Method (Prim)

* **Build adjacency table:** Allow fast reading of related edge IDs for each location.
* **Prepare temp workspace:** Set up `in_tree`, lowest cost, parent, edge ID, and the waiting line.
* **Put new root:** Put the smallest unpicked location into the heap with cost 0 and no parent.
* **Take min record:** Skip tickets that differ from the current saved values (outdated tickets) or locations already inside the network.
* **Pick edge:** If it is not a root, officially add the ticket's road to the result.
* **Inspect incident records:** Skip self-edges and neighbors already inside the network.
* **Record cheaper connection:** Change the cost, parent, and edge ID only after successfully pushing to the waiting line.
* **Start next component:** If the line is empty but towns remain, drop a new starting point in.

### Building a Forest with the Sorting Method (Kruskal)

* **Sort edge list:** Sort strictly by cost, then `u`, then `v`, then `edge_id`.
* **Prepare DSU:** Create a completely separate one-element group for each location.
* **Check from cheapest:** Skip self-loops and find the representatives (Leaders) of the two endpoints.
* **Check cycles:** If the Leaders are exactly the same, throw the road in the trash.
* **Pick edge:** If the Leaders are different, add the road to the result and merge the two groups!
* **Record components:** Save the final number of remaining DSU groups into the result.

### Finalizing the Total Sum and Result

* **Gather magnitudes by sign:** Add up all the positive weights and negative weights completely separately.
* **Cancel out:** Subtract the common amount between the positives and negatives safely.
* **Check final range:** Make sure the remaining amount fits safely inside `int64_t`.
* **Finalize temp result:** Copy to the user's result structure only after every task succeeds.

### Validating the Minimum Spanning Forest

* **Check input edges:** Make sure the selected IDs, endpoints, and costs exactly match the original map.
* **Check structure:** Use DSU to verify there are absolutely zero cycles and connected island limits are perfect.
* **Check counts and sum:** Confirm the selection count is exactly `V-c` and the saved sum matches the real sum.
* **Verify minimality:** Prove that absolutely no unpicked road can replace a heavier chosen road to lower the total price.

## C Code

### Making a Map and Running Both Algorithms

```c
UndirectedIncidentGraph graph = {0};
PrimResult prim_result = {0};
KruskalResult kruskal_result = {0};

if (mst_graph_init(&graph, 3U) != MST_OK) {
        return 1;
}

if (mst_graph_add_edge(&graph, 0U, 1U, INT64_C(4)) != MST_OK ||
        mst_graph_add_edge(&graph, 0U, 2U, INT64_C(4)) != MST_OK ||
        mst_graph_add_edge(&graph, 1U, 2U, INT64_C(1)) != MST_OK) {
        return 1;
}

if (prim_minimum_spanning_forest(&graph, &prim_result) != MST_OK) {
        return 1;
}

if (kruskal_minimum_spanning_forest(&graph, &kruskal_result) != MST_OK) {
        return 1;
}
```

### Recording a Cheaper Connection in Prim

```c
if (!workspace->in_tree[neighbor] &&
        (!workspace->has_best[neighbor] ||
         edge->weight < workspace->best_key[neighbor])) {
        PrimFrontierStatus status = prim_frontier_push(
                &workspace->frontier,
                neighbor,
                edge->weight,
                vertex,
                edge_id
        );

        if (status != PRIM_FRONTIER_OK) {
                return map_frontier_status(status);
        }

        workspace->has_best[neighbor] = true;
        workspace->best_key[neighbor] = edge->weight;
        workspace->best_parent[neighbor] = vertex;
        workspace->best_edge[neighbor] = edge_id;
}
```

### Skipping Outdated Tickets in Prim

```c
if (!workspace->has_best[entry.vertex] ||
        entry.key != workspace->best_key[entry.vertex] ||
        entry.parent != workspace->best_parent[entry.vertex] ||
        entry.edge_id != workspace->best_edge[entry.vertex]) {
        workspace->result.stale_pop_count =
                workspace->result.stale_pop_count + 1U;
        continue;
}

if (workspace->in_tree[entry.vertex]) {
        workspace->result.already_in_tree_pop_count =
                workspace->result.already_in_tree_pop_count + 1U;
        continue;
}
```

### Picking Loop-Free Roads in Kruskal

```c
if (edge->u == edge->v) {
        candidate->self_loop_skip_count =
                candidate->self_loop_skip_count + 1U;
        continue;
}

if (dsu_find(sets, edge->u, &left_root) != DSU_OK ||
        dsu_find(sets, edge->v, &right_root) != DSU_OK) {
        return MST_INVALID_STATE;
}

if (left_root == right_root) {
        candidate->cycle_skip_count =
                candidate->cycle_skip_count + 1U;
        continue;
}

if (candidate->forest.selected_count >=
        (size_t)MST_MAX_SELECTED_EDGES) {
        return MST_INVALID_STATE;
}

candidate->forest.selected_edges[
        candidate->forest.selected_count
] = *edge;
candidate->forest.selected_count =
        candidate->forest.selected_count + 1U;

if (dsu_union(sets, edge->u, edge->v, &merged) != DSU_OK ||
        !merged) {
        return MST_INVALID_STATE;
}
```