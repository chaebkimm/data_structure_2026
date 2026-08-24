# Chapter 3. Storing Relationships in Multiple Directions

## Thinking Logically

### How do we show relationships a tree can't hold?

In a tree, an item has only one parent directly above it. Real-world relationships are much freer. Two different items can connect to the exact same item, and a connection can even loop all the way back to a previous item.

To show these free-flowing, messy relationships, we use a map made up of items (like dots) and the direct connections between them (like lines or roads).

### Why do arrow directions matter?

Sometimes a connection is like a one-way street. Going from item 0 to item 1 doesn't automatically mean you can go backward from 1 to 0.

Other times, a relationship works both ways without caring about direction. This is like a two-way street, where a single connection between item 0 and item 1 lets you easily travel back and forth.

### How do we count relationships around one item?

If we are looking at one-way streets, we count the number of paths leaving an item and the number of paths coming into it separately. In a map of two-way streets, we simply count how many total lines touch that item.

Any item you can reach directly by following just one line is considered a neighbor. In a one-way map, we separate neighbors you can travel *to* from neighbors that can travel *to you*.

### What can we learn by following multiple lines?

When you travel from item to item by following the connected lines, you create a route. Sometimes, a route circles all the way back to the exact item where you started without visiting any other item twice.

In a map of two-way streets, you might find a large group of items that can all reach each other. Even a single, completely lonely item with zero connections counts as its own little independent group.

### How should we store this map in code?

There are a few ways to remember all these connections. We could write down a simple list of every single line. Or, for each item, we could collect a list of its specific neighbors. Another clever way is to draw a grid (like a multiplication table) for every possible pair of items, checking a box if a connection exists.

If we only use a simple list of lines, it's very hard to notice if there is a lonely item with no connections. Because of this, we also need to keep a separate count of the total number of items.

This chapter will use a fixed grid to store a maximum of 16 items.

```text
grid[start][end] == true   (Connection exists)
grid[start][end] == false  (Connection does not exist)

```

### Why do two-way streets use two spaces in the grid?

A two-way connection must be easy to find no matter which side you start from. If we connect item 2 and item 4, we must mark "true" for the path from 2 to 4, *and* mark "true" for the path from 4 to 2. This creates a perfectly mirrored grid, where the top right side is an exact reflection of the bottom left side.

### What kinds of lines do we reject?

The map in this chapter will not allow an item to draw a line directly back to itself. We also won't allow drawing the exact same line twice. If you want to delete a line, you must make sure that line actually exists first.

Finally, we are not storing how long the paths are or how much they cost to travel. We are only storing a simple "yes" or "no" for whether a line exists.

## Calculating Efficiency

### Efficiency of adding or removing a connection

We change one box in the grid for a one-way street, or two boxes for a two-way street. Because we can jump straight to the exact box, this takes the exact same tiny amount of time regardless of how many items there are.

### Efficiency of checking one connection

We instantly read one box in the grid using the starting and ending numbers. This is instantly fast.

### Efficiency of counting connections or finding neighbors

To find neighbors, we have to scan every single box in one entire row or column. This means the amount of work grows steadily in proportion to the total number of items we currently have.

### Efficiency of checking the whole map

We have to look at every single box in the entire grid that is currently in use. Because the grid size is items multiplied by items, the amount of work increases very rapidly, like the square of the data.

### Memory efficiency

Even if there are very few connections, we still have to build a giant grid with boxes for every possible pair of items. The memory space needed grows based on the total items squared. The code in this chapter locks in a 16 × 16 space from the beginning, so it takes up a fixed amount of memory even if we use fewer items.

## Glossary

### Graph

A structure showing vertices and the edges that connect them.

### Vertex (Plural: Vertices)

Each individual item that makes up a graph.

### Edge

A direct connection between two vertices.

### Directed Graph

A graph where edges have a specific starting and ending direction.

### Undirected Graph

A graph that doesn't distinguish between the start and end of an edge.

### Degree

The number of edges touching a single vertex.

### Out-degree and In-degree

In a directed graph, the number of edges going out from, or coming into, a single vertex.

### Path

A sequence of vertices connected by following the edges.

### Cycle

A path that returns to its starting vertex without repeating any other vertices along the way.

### Edge List

A list that simply saves the graph's edges one by one.

### Adjacency List

A list that collects and saves the neighbors specifically for each vertex.

### Adjacency Matrix

A grid (table) using rows and columns to save whether an edge exists between every possible pair of vertices.

### Connected Component

The largest group of vertices that can all reach each other by following undirected edges.

### Isolated Vertex

A completely lonely vertex with zero edges connecting it to anything else.

### Unweighted Graph

A graph that only stores whether an edge exists or not, without storing distances or travel costs.

### Symmetric Matrix

A grid where the values are perfectly mirrored across the diagonal line (used for undirected graphs).

## Coding Plan

### Preparing the Map

* **Check bounds:** Make sure the number of items is between 0 and 16.
* **Check type:** Make sure it is either a one-way or two-way map.
* **Initialize grid:** Set all 16 × 16 boxes to `false`, even the unused ones.
* **Save state:** Store the number of items and the map type.

### Adding a Connection

* **Check numbers:** See if the two items are within the range we are currently using.
* **Reject loops:** Fail if the two item numbers are exactly the same.
* **Reject duplicates:** Do not add a connection if its box is already `true`.
* **Set boxes:** Make `[from][to]` `true` for one-way maps. For two-way maps, also make the mirrored box `true`.

### Deleting a Connection

* **Check numbers:** Look at the range of the two items.
* **Check existence:** Fail if the connection doesn't exist.
* **Clear boxes:** Make the target box (and the mirrored box if needed) `false`.

### Checking Connections and Counting

* **Check connection:** Read `[from][to]` and use it as the result.
* **Count outgoing:** Count the `true` boxes in that item's row.
* **Count incoming:** Count the `true` boxes in that item's column.
* **Save neighbors:** Find the `true` destination items in the row, starting from the smallest number, and put them in the result.

### Checking the Whole Map

* **Check size:** Make sure the item count is not over 16.
* **Check loops:** Make sure all diagonal boxes where an item connects to itself are `false`.
* **Check symmetry:** In a two-way map, make sure `[a][b]` and `[b][a]` have the exact same value.
* **Determine completion:** If even one rule is broken, trigger an error.

## C Code

### Making the Adjacency Matrix

```c
#define GRAPH_MAX_VERTICES 16U

typedef enum {
        GRAPH_DIRECTED = 0,
        GRAPH_UNDIRECTED
} GraphKind;

typedef struct {
        size_t vertex_count;
        GraphKind kind;
        bool adjacency[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
} Graph;
```

### Adding and Checking Edges

```c
Graph graph;
bool has_edge = false;

if (graph_init(&graph, 6U, GRAPH_DIRECTED) != GRAPH_OK) {
        return 1;
}

if (graph_add_edge(&graph, 0U, 1U) != GRAPH_OK ||
    graph_add_edge(&graph, 0U, 2U) != GRAPH_OK ||
    graph_add_edge(&graph, 1U, 3U) != GRAPH_OK ||
    graph_has_edge(&graph, 0U, 2U, &has_edge) != GRAPH_OK) {
        return 1;
}
```

### Finding Degrees and Neighbors

```c
size_t in_degree = 0U;
size_t out_degree = 0U;
GraphNeighbors neighbors;

if (graph_in_degree(&graph, 3U, &in_degree) != GRAPH_OK ||
    graph_out_degree(&graph, 0U, &out_degree) != GRAPH_OK ||
    graph_out_neighbors(&graph, 0U, &neighbors) != GRAPH_OK) {
        return 1;
}
```

### Checking an Undirected Graph

```c
Graph undirected;

if (graph_init(&undirected, 5U, GRAPH_UNDIRECTED) != GRAPH_OK ||
    graph_add_edge(&undirected, 2U, 4U) != GRAPH_OK) {
        return 1;
}

if (undirected.adjacency[2][4] &&
    undirected.adjacency[4][2] &&
    graph_validate(&undirected) == GRAPH_OK) {
        /* Both mirrored boxes are the same. */
}
```