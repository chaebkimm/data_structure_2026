# Chapter 3. Storing Relationships in Multiple Directions

## Thinking Logically

### How do we show relationships a tree can't hold?

Real-world relationships are much freer than those in a tree. To show these free-flowing, messy relationships, we use a map made up of items (like dots) and the direct connections between them (like directed links).

### Example: Modeling a 3-Server System

To understand these rules, imagine we are managing three servers: a Web Server (Item 0), an App Server (Item 1), and a Database (Item 2). We will use this simple three-item map throughout the chapter to see how relationships work.

### Why do directions matter?

The direction of a connection is critical. Often, a connection is strictly one-way. For example, our Web Server (0) might be allowed to send requests to the App Server (1), but the App Server is not allowed to initiate a connection backward to the Web Server. This is modeled as a directed connection. 

### What about two-way connection?

If two-way communication is needed, it can be explicitly built using two separate directed connections pointing in opposite ways.

### How do we count relationships around one item?

To understand how busy a specific item is, we count its connections. In a directed map, we differentiate between incoming and outgoing paths. We calculate the number of paths leaving an item (out-degree) and the number of paths terminating at that item (in-degree).

In our example, if the App Server (1) receives data from the Web Server (0) and sends data to the Database (2), the App Server has an in-degree of 1 and an out-degree of 1.

### What can we learn by tracing paths?

When data travels from item to item across multiple links, it forms a route or path. Tracing these paths allows us to see if two distant items can communicate. For instance, the Web Server (0) can reach the Database (2) by tracing a path through the App Server (1).

### How should we store this network?

To represent this map in software, we must translate these connections into memory. A highly efficient approach is a two-dimensional grid (a table) mapping every possible pair of items. We check the intersection of a row and column to see if a one-way connection exists from the row's item to the column's item.

### What about the node connected to itself?

In some scenarios, an item might connect directly back to itself. This is known as a self-loop. For instance, a webpage might contain a button that simply reloads its own page. Depending on the rules of your specific system, you can choose to allow or forbid these self-loops.

### Preview: Adding Weights to Links

In many real-world scenarios, connections are not all equal. A road between two cities has a specific distance or travel time. To model this, advanced graphs assign a numerical value—known as a weight or cost—to each connection, allowing algorithms to find the shortest or fastest paths. In this chapter, we only care if a connection exists, so we just use a simple `1` (yes) or `0` (no).

## Calculating Efficiency

### Efficiency of adding or removing a connection

To add or remove a link, we just go to the specific row and column in our grid and change a `0` to a `1` (or vice versa). Because the computer can calculate exactly where that box is instantly, this takes constant time, no matter how massive the map is.

### Efficiency of checking specific connection

We instantly read one spot in the grid using the starting and ending numbers. This is instantly fast.

### Efficiency of finding neighbors

To find neighbors, we have to scan every single box in one entire row or column. This means the amount of work grows steadily in proportion to the total number of items we currently have.

### Efficiency of analyzing the entire topology

We have to look at every single spot in the entire grid that is currently in use. The grid size is the square of the number of items.

### Memory efficiency

Even if there are very few connections, we still have to build a giant grid with boxes for every possible pair of items. The memory space needed grows based on the total items squared. 

## Glossary

### Graph

A data structure showing items and the connections among them.

### Vertex

Each individual item that makes up a graph.

### Edge

A direct connection between two vertices.

### Directed Graph

A graph where edges have a specific starting and ending direction.

### Undirected Graph

A graph that doesn't distinguish between the start and end of an edge.

### Degree

The number of edges touching a single vertex. In a directed graph, out-degree is the number of edges going out from a single vertex. Also, in-degree is the number of edges coming into a single vertex.

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

## Invariant

### What is the invariant (the golden rule) in this data structure?

1. The Boundary Rule: The total number of active items must never exceed the absolute size of the grid we carved out in memory.

2. The Clean Slate Rule (No Ghost Connections): If a machine is removed or doesn't exist yet, its entire row and column must remain strictly `0`. We cannot leave leftover `1`s from old data, or the computer will think a ghost machine is sending data.

3. The Self-Loop Rule: If our specific network rules forbid a machine from connecting to itself, the diagonal line running down the center of the grid (where row 0 meets column 0, row 1 meets column 1, etc.) must permanently remain `0`.

## Example: Modeling a 3-Tier Web Architecture

Imagine we are managing network firewalls for three servers: a Web Server (Item 0), an App Server (Item 1), and a Database (Item 2). We start with a 3x3 grid of all `0`s.

1. Web talks to App: We open a connection from Web (0) to App (1). We go to Row 0, Column 1, and write a `1`.

2. App talks to Database: We open a connection from App (1) to Database (2). We go to Row 1, Column 2, and write a `1`.

3. App replies to Web: We open a connection from App (1) back to Web (0). We go to Row 1, Column 0, and write a `1`.

If we look at Row 1 (the App server's outgoing rules), we see `[1, 0, 1]`. This instantly tells us the App server sends data to the Web server (Column 0) and the Database (Column 2), but not to itself (Column 1).

## Coding Plan

### Initializing the Network Topology

- Validate bounds: Make sure the number of items fits in the prepared memory.
- Zero-initialize grid: Use a double loop to visit every single box and set it to `0`, ensuring no phantom connections exist. 
- Save metadata: Store the total number of active items.

### Adding a Connection

- Check numbers: See if the two items are within the range we are currently using.
- Reject loops: Fail if the two item numbers are exactly the same.
- Update matrix: Make the value at [from][to] equal `1` to record the one-way link. 

### Deleting a Connection

- Check numbers: Look at the range of the two items.
- Clear spot: Make the value at [from][to] equal `0`.

### Counting Outgoing Traffic (Out-Degree)

- Check numbers: Ensure the requested item actually exists.
- Scan row: Loop through every column in that item's specific row. Every time you see a 1, increase your count.

## New C Syntax Explained

### `[][]` (Two-Dimensional Arrays)

To create a grid in C, you use two sets of square brackets. For example, `grid[10][10]` sets aside a square of memory with 10 rows and 10 columns (100 boxes total). To access a specific box, you provide the row number first, then the column number: `grid[2][5]` accesses the box in row 2, column 5.

### `size_t`

`size_t` is a special type of unsigned integer in C. It is specifically designed to represent the size of objects in memory or to count items. Because you can never have a negative amount of memory or a negative number of items in an array, `size_t` cannot hold negative numbers.

## C Code

### Designing the Grid

```c
#define GRAPH_MAX_VERTICES 16

struct DirectedGraph {
        size_t vertex_count;
        int grid[GRAPH_MAX_VERTICES][GRAPH_MAX_VERTICES];
};
```

### Initializing the Grid

```c
struct DirectedGraph network;
network.vertex_count = 3; /* Web, App, Database */

/* Use a double loop to visit every row and column, setting all to 0 */
for (size_t row = 0; row < GRAPH_MAX_VERTICES; row = row + 1) {
        for (size_t col = 0; col < GRAPH_MAX_VERTICES; col = col + 1) {
                network.grid[row][col] = 0;
        }
}
```

### Adding Connections

```c
size_t from = 0; /* Web Server */
size_t to = 1;   /* App Server */

/* Ensure the servers exist and are not the same machine */
if (from < network.vertex_count && to < network.vertex_count && from != to) {
        /* Set the specific box to 1 (Yes) */
        network.grid[from][to] = 1;
}

/* App talks to Database */
network.grid[1][2] = 1;

/* App replies to Web */
network.grid[1][0] = 1;
```

### Removing a Connection

```c
size_t cut_from = 1; /* App Server */
size_t cut_to = 2;   /* Database */

if (cut_from < network.vertex_count && cut_to < network.vertex_count) {
        /* Set the specific box to 0 (No) */
        network.grid[cut_from][cut_to] = 0;
}
```

### Counting Outgoing Connections (Out-Degree)

```c
size_t target_server = 1; /* App Server */
size_t outgoing_count = 0;

if (target_server < network.vertex_count) {
        /* Lock in the row, and loop through all the columns */
        for (size_t col = 0; col < network.vertex_count; col = col + 1) {
                if (network.grid[target_server][col] == 1) {
                        outgoing_count = outgoing_count + 1;
                }
        }
}
```