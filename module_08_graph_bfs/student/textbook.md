# Chapter 8. Processing data in stored order

Store data in an array and remove it in the order it was stored. Use that order to explore trees and graphs from the starting point outward and find shortest distances.

## Thinking logically

### How can we process data in the order it was stored?

Add new data at the back and remove data from the front. This processes data in the order it was stored. We call this a queue.

### How do we mark the front and rear of an array queue?

In a nonempty queue, `front` is the index of the first data and `rear` is the index of the last data. In an empty queue, `front` is one greater than `rear`, so the range from `front` through `rear` is empty. Adding data to an empty queue leaves one item, making `front` and `rear` equal.

### What initial values should front and rear have?

When the first data is stored at array index `0`, both `front` and `rear` become `0`. Adding data increases `rear` by one, so its initial value is `-1`. Adding data does not change `front`, so its initial value is `0`.

### What happens when the rear reaches the end of the array?

In a simple implementation, no more data can be stored once `rear` reaches the array's last index.

Removing data advances `front` and leaves unused space at the beginning of the array. We can also wrap `front` and `rear` around to reuse that space.

### What happens when we explore a tree with a queue?

Add the root to the queue. While the queue contains nodes, remove one from the front, process its data, and add its children at the back. The children wait behind the nodes already in the queue, so the current level finishes before the next level begins.

A stack instead removes the most recently added node. It follows the current branch deeply before returning to other branches that were already waiting.

### How do we know which level we are processing?

A node's level is its distance from the root. Record the distance before adding the node to the queue. The root's distance is zero. A child's distance is its parent's distance plus one.

### How does graph traversal differ from tree traversal?

In a tree, every node except the root has one parent. Following only child links adds each node once. A graph can contain cycles or multiple paths to the same node, so different nodes may try to add the same neighbor. Repeated processing can follow a cycle indefinitely. Check whether a node has already been processed and process it only once.

### What happens when we explore a graph with a queue?

Add the starting node to the queue. While the queue contains nodes, remove one from the front, process its data, and add its neighbors at the back. Nodes are processed in order of increasing distance from the start. Adding a previously queued neighbor again cannot make its first processing happen earlier, so do not add it again.

A stack instead processes the most recently added node first. In this form of stack traversal, add an unprocessed neighbor again even if an earlier entry is already waiting. The new entry is removed before the old one and can bring the node's processing forward. This follows the current path as deeply as possible before exploring another path. When removing an entry, skip it if its node has already been processed.

### How do we find shortest distances from a graph's starting node?

With each edge counting as one step, a queue processes nodes in order of increasing distance from the start. When a neighbor that has never entered the queue is first discovered, no path to it is shorter than the path through the current node. The starting node's shortest distance is zero. Give each newly discovered neighbor the current node's shortest distance plus one before adding it to the queue.

### How can we represent a maze?

Divide the maze into cells and distinguish walls from passages. Each passage cell is a graph node. Passage cells that share a horizontal or vertical side are neighbors. Each move adds one to the distance, so the shortest distance from the start is the minimum number of moves.

### How do we find a cell's neighbors?

A neighboring cell is one horizontal or vertical step from the current cell. Generate candidates in a fixed direction order, then check that each candidate is within the maze and is a passage.

### How do we find distances from the starting cell?

The starting cell needs no moves, so set its distance to zero. Mark the other distances as unknown with a value larger than any possible shortest distance, such as the total number of cells. Add the starting cell to the queue. While the queue contains cells, remove one and repeat the same work. For each neighbor whose distance is unknown, record the current cell's distance plus one, then add that neighbor to the queue.

### Why is the first recorded distance the minimum?

Every move to a neighboring cell has the same cost, and cells enter the queue in order of increasing distance from the start.

### How can we reconstruct a shortest path?

When a cell is first discovered, also save the current cell that discovered it. Starting at the destination, follow the saved cells backward to the start and collect the cells along the way. Reverse their order to recover the shortest path.

## Calculating efficiency

### Memory needed to create a queue

Creating an array queue requires space for its full capacity. If the simple queue does not reuse removed positions at the front, capacity for the total number of items that will be added is sufficient.

### Efficiency of adding or removing one item

To add data, increase `rear` by one and store the data at that position. To remove data, read it at `front` and increase `front` by one. No other queued data moves, so each operation takes constant time regardless of the number of items.

## Glossary

### Queue

A data structure that adds data at the back and removes the earliest added data first, like a line of waiting people.

### First-in first-out

The rule that the first data added is the first data removed.

### Enqueue

Adding data at the back of a queue.

### Dequeue

Removing and returning data from the front of a queue.

### Front

The index identifying the first data in a nonempty queue. An empty queue has no first data.

### Rear

The index identifying the last data in a nonempty queue. An empty queue has no last data.

### Linear queue

A simple array queue whose occupied range advances toward the end of the array without reusing removed positions or wrapping around during operation.

### Circular queue

An array queue whose indices wrap around to reuse removed positions.

### Level order

Processing all nodes at one tree level before processing the next level.

### Breadth-first search

A traversal that uses a queue to process nodes from the starting point outward. When every move has the same cost, it can find shortest distances.

### Discovered

The state of a node whose distance from the start has been determined. It includes nodes waiting in the queue and nodes already processed.

### Processed

The state of a node that has been removed from the queue and had its neighbors examined.

### Iterator

Something that provides successive items in a defined order, such as the next neighbor of a node.

### Sentinel

A value chosen to carry a special meaning. `INF` means that the distance from the start has not yet been determined.

### Predecessor

The current cell that first discovered another cell. It is that cell's parent in the search and is used to reconstruct a path.

## Invariant

### What is the breadth-first search invariant?

- Distances from the start stay the same or increase from the front of the queue to the back.

### What is the benefit of the invariant?

When every move has the same cost, a neighbor's shortest distance is determined when it is first discovered from the node removed from the queue. No shorter path can be discovered later, so each node only needs to enter the queue once, at its first discovery.

### What happens if the invariant is broken?

Using a stack instead of a queue, or giving moves different costs, removes the guarantee that nodes are taken out in order of increasing distance from the start. If a shorter path is discovered later, the distance must be updated and the neighbors explored again.

### How do we keep the invariant intact?

- Remove a node from the front of the queue. For each undiscovered neighbor, record the removed node's distance plus one, then add the neighbor at the back.

## Coding plan

### Representing the maze

- Name the square maze's size `N`. Store walls and passages as `0` and `1` in a two-dimensional array.
- Define the members of `struct point` in `y`, `x` order. Following the row-first index order of a two-dimensional array, read a cell with `maze[p.y][p.x]`.
- Make the maze's border walls so that checking neighbors does not take array indices outside the maze.

### Generating horizontal and vertical neighbor candidates in order

- Remember the current cell and the next direction to examine. When a candidate is requested, copy the current cell's coordinates, change `x` or `y` for that direction, and provide the candidate. Advance to the next direction. Finish the iteration after all four candidates have been examined.

### Storing waiting coordinates

- Make the queue an array of `struct point`. Each cell enters at most once, so a capacity of `N * N`, the total number of cells, is sufficient. Start `front` at `0` and `rear` at `-1`.
- To add a coordinate, increase `rear` by `1` and store it at that position. To remove a coordinate, read it at `front` and increase `front` by `1`. The queue is empty when `front` is greater than `rear`.

### Preparing the distance search

- Create a two-dimensional array named `distance` to store shortest distances from the start.
- Name the value `N * N` as `INF`; it is larger than any possible shortest distance. Before searching, initialize every cell's `distance` to `INF` to mark it as undiscovered.
- For a passage start, set its `distance` to `0` and add it to the queue.

### Finding shortest distances

- While the queue is nonempty, remove the current cell from the front.
- Examine its four neighbor candidates one at a time. If a candidate is a passage (`1`) and its `distance` is `INF`, store the current cell's distance plus `1` in its `distance`, then add the cell to the queue.

## New C syntax explained

### Initializing a two-dimensional array

Each inner brace pair in `int maze[N][N] = { ... };` initializes one row. `maze[p.y][p.x]` first selects a row, then a column within it.

### Copying and returning a structure

`struct point p = cur_point;` copies both members. Changing `p.x` afterward does not change `cur_point.x`. Functions can also accept or return a whole structure, as `enqueue` and `dequeue` do.

### Short-circuit logical OR

In `is_wall(p) || get_distance(p) != INF`, either true condition is enough to skip the coordinate. If the wall test is true, C does not evaluate the distance test.

## C code

### Maze storage

```c
enum { N = 5 }; // Use the same size for storage and initialization.

int maze[N][N] = {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
}; // 0 is a wall; 1 is a passage. Keep the outer border closed with walls.
```

### Representing and checking coordinates

```c
struct point {
        int y; // Put the row first to match the first array index.
        int x; // Put the column second.
};

int is_wall(struct point p) {
        // Requires an in-bounds coordinate. This function does not check bounds.
        return maze[p.y][p.x] == 0;
}
```

### Generating horizontal and vertical neighbor candidates in order

```c
struct point cur_point;
int state; // The next directions are right, left, down, and up, in that order.

void init_iter(struct point p) {
        cur_point = p;
        state = 0;
}

int has_next_iter(void) {
        return state < 4;
}

struct point next_iter(void) {
        // Requires an interior current cell and a direction still left to examine.
        struct point p = cur_point; // Start every candidate from the same current cell.
        switch (state) {
                case 0: p.x += 1; break;
                case 1: p.x -= 1; break;
                case 2: p.y += 1; break;
                case 3: p.y -= 1; break;
        }
        ++state; // The next call selects the next direction.
        return p;
}
```

### Storing coordinates in arrival order

```c
struct point queue[N * N]; // Store whole coordinates.
int front = 0; // Index of the first data when the queue is nonempty.
int rear = -1; // Index of the last data when the queue is nonempty.

void init_queue(void) {
        // Old values need not be erased. The occupied range becomes empty.
        front = 0;
        rear = -1;
}

int is_empty_queue(void) {
        return front > rear;
}

void enqueue(struct point data) {
        // Requires an unused write position. Removal does not move rear backward.
        queue[++rear] = data;
}

struct point dequeue(void) {
        // Requires a nonempty queue. Read the first data, then advance front.
        return queue[front++];
}
```

### Storing distances

```c
int distance[N][N];

void set_distance(struct point p, int d) {
        distance[p.y][p.x] = d;
}

int get_distance(struct point p) {
        return distance[p.y][p.x];
}

enum { INF = N * N }; // Larger than any possible shortest distance in the maze.
```

### Initializing the search

```c
void init_bfs(struct point s) {
        init_queue(); // Restart the queue indices on every call.
        struct point p;
        for (p.y = 0; p.y < N; p.y++) {
                for (p.x = 0; p.x < N; p.x++) {
                        // Clear old discovery records, including wall entries.
                        set_distance(p, INF);
                }
        }
        // The start must be in bounds. A wall start leaves the queue empty.
        if (!is_wall(s)) {
                set_distance(s, 0);
                enqueue(s);
        }
}
```

### Finding shortest distances

```c
void bfs(struct point start) {
        init_bfs(start); // Reset both the queue and distances on every run.
        while (!is_empty_queue()) {
                struct point cur = dequeue();
                int cur_dist = get_distance(cur);
                init_iter(cur);
                while (has_next_iter()) {
                        struct point p = next_iter();
                        if (is_wall(p) || get_distance(p) != INF) {
                                // Coordinates still waiting in the queue are already discovered.
                                continue;
                        }
                        // Record discovery before another path can add this coordinate.
                        set_distance(p, cur_dist + 1);
                        enqueue(p);
                }
        }
}
```
