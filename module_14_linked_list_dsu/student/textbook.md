# Chapter 14. Linking with Addresses and Managing Connected Groups

## Thinking Logically

### What happens when we delete a value from the middle of an array?

Values inside a normal array are packed tightly together in one solid block. Because of this, if you want to squeeze a new value in or pull a value out from the exact middle, you are forced to slide every single value that comes after it to make room or fix the gap.

Instead of keeping them packed together, what if we gave each value its own separate, individual storage box? Inside each box, we just write down the exact memory address of the *next* box. This way, even if the boxes are scattered wildly all over the computer's memory, we can still link them together into a perfect, ordered chain just by following the addresses!

### How do we connect scattered values into a chain?

We package our actual data value and the memory address of the next box together into a single unit.

```c
typedef struct LinkedNode {
        int value;
        struct LinkedNode *next;
} LinkedNode;
```

To start reading, we just keep the address of the very first box safely saved in a variable called `head`. If you hop from box to box following the `next` addresses and eventually hit a completely empty address (`NULL`), it simply means you have reached the very end of the chain.

```text
head
 |
 v
Box(17) -> Box(23) -> Box(31) -> Empty (NULL)
```

### How do we insert a new value at the very front?

When you want to drop a brand-new box (let's call it R) at the very front of the chain, you must be careful. First, you copy the old `head` address and write it into R's `next` address spot. This successfully links R to the old first box. Only *after* that do you update your main `head` variable to point to R.

```text
R's next address = old head address
head = R's address
```

If you do these two steps backward, you will permanently overwrite your only address to the rest of the chain, and the rest of the boxes will be lost forever in memory! Our tool perfectly handles this delicate job of safely adding a new box to the front.

Our chain manager also tracks exactly how many boxes we have right now (`size`) and the strict maximum number allowed (`limit`, up to 16). If the chain hits its limit, or if the computer refuses to give us a new box, the tool safely leaves the existing chain completely untouched.

### How do we safely delete a middle box?

Let's say we want to permanently delete Box Q, which is holding the number 23.

```text
previous box = R
victim box   = Q
next box     = P
```

While Box Q is still perfectly alive, we carefully read its `next` address (which points to P) and save it securely. Next, we walk back to Box R and change R's `next` address so it completely skips over Q and points directly to P. Finally, we safely tell the computer to destroy Box Q (giving its memory back to the system).

If you give Box Q back to the computer *first* and then try to read its `next` address, you are illegally digging through trash memory that the computer already took back! This causes an incredibly dangerous, crashing error. On the other hand, if you safely unhook Q from the chain but completely forget to give it back to the computer, that memory is locked up and lost forever.

If the box you want to delete is the very first one, you just update `head` instead. If the same value appears multiple times in the chain, our tool only deletes the very first one it bumps into. If the value isn't there at all, it's not an error; the tool just calmly reports that nothing was removed.

### How do we safely destroy the entire chain?

You cannot just throw the boxes away blindly. Before destroying the box you are currently holding, you absolutely must read and save its `next` address! Then you can safely destroy the current box, jump to the saved location, and repeat this until you hit an empty address (`NULL`).

```text
Save next address -> Destroy current box -> Walk to next address
```

When all the boxes are gone, we cleanly reset `head=NULL`, `size=0`, and `limit=0`. *(Warning: If you lazily copy just the `head` address of a living chain into a second chain manager, both managers will mistakenly believe they exclusively own the exact same boxes, which will cause massive destruction when they both try to clean up!)*

### Do we have to search the whole map every time a road is built?

Let's switch gears and think about a different problem. If two-way roads are being built on a map one by one, forcing the computer to search the entire giant map every single time just to see if two towns are finally connected is exhausting and incredibly slow.

Instead, what if we just kept a simple list of which "team" each town belongs to? Then, when a road connects two teams, we just instantly merge the whole teams together! We don't even need to remember the actual roads or paths.

### What shape should we use to store connected teams?

Every single town simply remembers the ID number of its "parent" (or boss). If you keep following the bosses up the chain, you will eventually reach the single, ultimate "Leader" of that team. A town that claims it is its *own* parent is the Leader!

```text
parent[x] = x
team_size[x] = 1
```

A brand-new town always starts out completely alone, acting as the leader of a 1-person team. Our team-building tool creates these towns with simple IDs in perfect order (0, 1, 2) up to a limit of 16.

We strictly only record the total size of the team on the Leader's notepad (`team_size`). For regular towns that aren't leaders, this size number is ignored (kept at 0). Because we are tracking the family trees of multiple groups at the same time, this structure is called a "forest."

### Why do we build a shortcut after finding the Leader?

When we want to know what team a town is on, we follow the chain of bosses all the way up to find the Leader. To avoid taking that exact same long, exhausting journey the next time we ask, we do something incredibly clever: we tell *every single town* we just walked past to forget their old parent and point directly to the Leader instead!

```text
Before checking: H -> G -> E -> A (Leader)
After checking:  H ----------> A (Leader)
```

We do this carefully in two separate steps. First, we safely walk the path just to verify all the parent IDs are legal and to find the Leader. *Only after that succeeds* do we walk the path a second time to actually change the parents and build the shortcuts. This safely prevents us from half-changing a path if we discover it's broken halfway up!

Our merging tools *always* safely check both teams first before changing absolutely anything.

### When merging two teams, which Leader stays in charge?

When a new road connects two different teams, we look at their Leaders. We always force the Leader of the *smaller* team to surrender and report directly to the Leader of the *larger* team! If both teams are exactly the same size, the Leader with the smaller ID number wins.

We mathematically add the sizes of both teams together and write the massive new total on the winning Leader's notepad. The losing Leader's notepad is wiped to 0, and we decrease the total number of independent teams in the world by 1.

Imagine we have 8 towns (A to H) and we merge them in this order:

```text
A+B, C+D, A+C, E+F, G+H, E+G, A+E
```

After all those mergers, a possible parent chain might look perfectly organized like this:

```text
parent          [A, A, A, C, A, E, E, G]
team_size       [8, 0, 0, 0, 0, 0, 0, 0]
team_count      1
```

If we search for town H, its path `H->G->E->A` will instantly be permanently shortcutted to `H->A`. The parents of C, D, and F won't change at all because they weren't standing on that specific path.

### What if the Leaders of both locations are already exactly the same?

If both locations already report to the exact same Leader, it means a path *already exists* between them somewhere! If you try to build a brand new road between them now, that new road will just create a pointless circle (a loop).

When this happens, our merging tool stops and safely reports that nothing was merged (`merged=false`). Our road-building tool reports this exact same situation by warning that a closed loop was created (`created_cycle=true`).

This grouping tool is incredibly fast, but it *only* tells you if things are connected. It absolutely does not tell you the actual route, the travel distance, or if the road is safe. It also completely lacks a way to delete a road once it has been built!

### Why shouldn't we count a two-way road twice?

When we record two-way roads, one single physical road accidentally gets written down twice (once for location A looking at B, and once for B looking at A). If we want to sort our roads later to find the cheapest ones, we absolutely must glue these two records back into one real road!

We do this by attaching the exact same `edge_id` to both records. Our tool spots this ID and perfectly combines them into just one single road. It smartly organizes the locations so the smaller ID number is always listed first.

*(Note: If a silly road just loops from a location straight back to itself, it still creates two records. Even if the connected towns are perfectly identical, if two roads have different IDs, they are considered parallel roads—two completely different roads connecting the exact same spots!)*

When we sort the final list, the order goes: Cost first, then smaller town, then larger town, and finally the edge ID. We use simple math (`<` and `>`) to compare costs instead of subtracting them. Subtracting massive numbers can cause the computer's math to overflow and crash!

## Calculating Efficiency

### Efficiency of inserting at the front of a chain?

Because we only change two addresses and bump the `size` count, it is instantly fast, taking $O(1)$ work. We completely avoid scanning the rest of the chain!

### Efficiency of finding and deleting a box?

If there are $n$ boxes, searching for a specific value forces you to walk from the very front, box by box. The worst-case scenario takes $O(n)$ work. Destroying the entire chain also forces you to touch every single box once, taking $O(n)$ work.

### Efficiency of initially setting up the teams?

Setting up $n$ towns so they all start as their own independent Leaders takes $O(n)$ work.

### Efficiency of finding and merging teams?

By brilliantly building shortcuts and always making the smaller team surrender to the larger one, the paths never get very long. Averaged out over time, the work to find or merge teams becomes almost instantly fast! *(The mathematical proof uses the Inverse Ackermann function).*

### Efficiency of organizing the two-way roads?

If there are $E$ real physical roads, scanning $2E$ mixed-up records to combine them back together takes $O(E)$ work. Sorting the final list takes $O(E \log E)$ work.

## Glossary

### Node

A storage unit that bundles a value and the address of the next node together.

### Singly Linked List

A data structure where each node stores the address of exactly one following node.

### Traversal

The process of visiting each node in order, starting from the `head` and following the next addresses.

### Use-After-Free

A dangerous bug where a program tries to read or write to a memory address that has already been given back to the system.

### Memory Leak

A situation where allocated memory cannot be freed because the program has lost track of its address.

### Disjoint Sets

Groups (sets) that do not share any elements with each other.

### DSU (Disjoint-Set Union)

A data structure that efficiently finds the representative of a disjoint set and merges two sets together.

### Path Compression

A technique used during a `find` operation to make future searches faster by pointing all visited elements directly to the root.

### Union by Size

A merging technique that attaches the root of the smaller group under the root of the larger group to keep the overall tree shallow.

### Logical Edge ID

A specific number proving that two endpoint records actually belong to the exact same undirected relationship.

## Coding Plan

### Creating a Linked List

* **Check limits:** Ensure `limit` is strictly between 0 and 16.
* **Record empty state:** Set `head=NULL`, `size=0`, and set `limit` to the requested value.

### Inserting a Value at the Front

* **Shallow check:** Verify the basic relationship between `size`, `limit`, and `head`.
* **Check limit:** If `size == limit`, safely leave the list exactly as it is.
* **Make node:** Ask the computer for memory for a new node, then safely store the value and the old `head` address.
* **Change start address:** Update `head` to officially point to the new node and increase `size` by one.

### Deleting the First Matched Node

* **Find node:** Move `previous` and `current` forward together carefully.
* **Preserve next address:** Absolutely always save `current->next` *before* giving the memory back!
* **Change links:** If it's the very first node, update `head`. Otherwise, smartly update `previous->next`.
* **Return space:** Safely free the current node and decrease `size` by one.

### Destroying the Entire List

* **Preserve next address:** Always save `next` before freeing the current node.
* **Return all nodes:** Move to the saved address and repeat until hitting an empty `NULL`.
* **Restore empty state:** Cleanly reset to `head=NULL`, `size=0`, and `limit=0`.

### Creating DSU Elements (Teams)

* **Pick next ID:** Use the current `element_count` as the brand-new ID.
* **Make single-element group:** Set its parent to itself and its group size to 1.
* **Increase counts:** Increase both the total element count and the independent group count by one.

### Finding the Representative and Building Shortcuts

* **Find root:** Move upwards while strictly checking if parent IDs are valid and verifying the Leader's size.
* **Limit loop:** If we follow parents more times than the total number of items, instantly trigger a broken state error.
* **Compress path:** Change the parent of absolutely every element along the safe path to point directly to the Leader.

### Merging Two Groups

* **Check both paths:** Find both Leaders securely before changing anything at all.
* **Handle same representative:** If they match, record `merged=false` without changing the structure.
* **Pick winner:** Choose the Leader with the larger group. If tied, pick the smaller ID.
* **Update parent and size:** Attach the losing Leader entirely under the winner and perfectly add their sizes together.
* **Decrease group count:** Decrease `component_count` by one and safely record `merged=true`.

### Building an Undirected Edge List

* **Verify endpoint records:** Ensure the exact same ID appears exactly twice and that the costs and directions match perfectly.
* **Make one edge:** For each matched pair, carefully copy the smaller endpoint, larger endpoint, cost, and ID into one clean record.
* **Sort by cost:** Compare strictly by cost, then smaller endpoint, then larger endpoint, then edge ID.

## C Code

### Inserting at the Front of a Linked List

```c
LinkedNode *new_node = malloc(sizeof *new_node);

if (new_node == NULL) {
        return LINKED_LIST_ALLOCATION;
}

new_node->value = value;
new_node->next = list->head;
list->head = new_node;
list->size = list->size + 1U;
```

### Deleting the First Matched Node

```c
LinkedNode *current = list->head;
LinkedNode *previous = NULL;

while (current != NULL && current->value != value) {
        previous = current;
        current = current->next;
}

if (current != NULL) {
        LinkedNode *successor = current->next;

        if (previous == NULL) {
                list->head = successor;
        } else {
                previous->next = successor;
        }

        free(current);
        list->size = list->size - 1U;
}
```

### Destroying the Entire List

```c
LinkedNode *current = list->head;

while (current != NULL) {
        LinkedNode *next = current->next;

        free(current);
        current = next;
}

list->head = NULL;
list->size = 0U;
list->limit = 0U;
```

### Finding the Representative and Compressing the Path

```c
size_t root = element;

while (sets->parent[root] != root) {
        root = sets->parent[root];
}

size_t current = element;
while (current != root) {
        size_t next = sets->parent[current];
        sets->parent[current] = root;
        current = next;
}


```

The actual `dsu_find` function rigorously verifies the parent IDs, loop counts, and the root size *before* starting the very first loop. It strictly only runs the second loop (building shortcuts) after all these safety checks succeed perfectly!

### Merging Two Representatives by Size

```c
size_t winner;
size_t loser;

if (left_size > right_size ||
        (left_size == right_size && left_root < right_root)) {
        winner = left_root;
        loser = right_root;
} else {
        winner = right_root;
        loser = left_root;
}

sets->parent[loser] = winner;
sets->component_size[winner] = left_size + right_size;
sets->component_size[loser] = 0U;
sets->component_count = sets->component_count - 1U;
```

### Comparing Edge Costs Safely Without Math Overflow

```c
if (left_edge->weight < right_edge->weight) {
        return -1;
}
if (left_edge->weight > right_edge->weight) {
        return 1;
}
```