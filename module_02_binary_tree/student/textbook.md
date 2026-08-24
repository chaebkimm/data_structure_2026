# Chapter 2. Organizing Data

## Thinking Logically

### What does data in a hierarchy look like?

Think about the folders and files on your computer. Inside the very top folder (called the "root"), there are other folders or files. Inside those folders, there can be even more folders or files.

### What do we need to store to keep this hierarchy?

We need to package and store not just the data itself, but also the information about how it connects (or links) to other pieces of data.

### The Simplest Method

We set up empty spots for each piece of data so that it can connect to a maximum of just two other pieces of data.

### How do we add data?

We connect the new data to an existing piece of data that still has an empty spot available.

### How do we delete data?

If the data you want to delete has nothing else connected to it, you simply cut the connection to it.

If the data you want to delete *does* have other data attached to it, you cut the connection to the data you are removing, and then you take the leftover attached data and add it back in.

When a node with two children is deleted, the right child takes its place. The left child is then dragged all the way down to the bottom-left corner of the right child's family line so the numbers stay in the correct order.

### How do we delete data with two children?

First, we promote one branch so that the grandparent bypasses the target and grabs onto that branch. This leaves the second branch orphaned, meaning we need to find it a new home on the tree. We scout for a valid empty spot, attach the orphaned branch there, and finally, clean up the memory of the old target node.

## Measuring Efficiency

### Memory Efficiency

Unlike an array that sets aside a huge chunk of space in advance, here we only ask for new memory space exactly when we add a new piece of data. However, each piece of data uses a bit more memory because it also has to store the "connection links" (up to two extra spots) to point to other data.

### Efficiency of Adding Data

To add new data, you simply start at the top and travel down the connections to find an empty spot. Because you don't have to push or shift a massive row of existing data backward, adding data is very fast. The amount of work depends on how deep the layers go, rather than the total amount of data.

### Efficiency of Deleting Data

Just like adding data, you don't need to shift everything around. If the data you want to delete is at the very bottom (with nothing connected to it), you just erase the connection instantly. If it has other data connected below it, you simply do a little extra work to reconnect the leftover data so nothing gets lost.

### Efficiency of Finding Data

Since the data is connected in layers, you don't have to check every single item one by one. You just follow the connections starting from the top. 

## Helpful Terms

### Node

A single package or "box" that holds your actual data, along with the connection spots (links) to attach to other data.

### Tree

A data structure that organizes data in a hierarchy. It is called a tree because if you draw it, it branches out downwards from a single starting point, looking exactly like an upside-down tree.

### Binary Tree

A special kind of tree structure where each node can connect to a maximum of exactly **two** other nodes (usually called a "left" connection and a "right" connection).

### Root Node

The very first, topmost piece of data in the tree. Every search or journey starts from this point.

### Leaf Node

A piece of data at the very bottom of the tree that has empty connection spots (meaning nothing is connected below it).

### Pointer (or Link)

The hidden information inside a node that tells the computer exactly where the next connected piece of data is saved in the memory. If a spot is empty, programmers usually call it **NULL**.

## Coding Plan

### Designing a Data Package (Node)

* **Blueprint:** Create a blueprint that has one spot for the data, one spot for a left connection, and one spot for a right connection.

### Creating New Data

* **Allocate Memory:** Get exactly enough memory space from the computer to hold one single node.
* **Save Data:** Put your data into the node's data spot.
* **Empty Connections:** Set both the left and right connections to "empty" since the package isn't connected to the tree yet.

### Connecting Data Together

* **Find a Parent:** Choose an existing node in the tree that still has an empty connection spot.
* **Attach Child:** Link the existing node's empty left or right connection spot directly to your newly created node.

### Deleting Data (Cutting a Connection)

* **Find Target:** Find the parent of the data you want to delete.
* **Cut Link:** Change the parent's connection from the target data to "empty".
* **Clean Up:** Give the memory space used by the deleted data back to the computer.

## New C Syntax Explained

### `struct` (Structures)

In Chapter 1, we stored simple numbers using standard types like `int`. However, a tree node needs to hold three things at once: the data, a left connection, and a right connection. A `struct` allows you to design your own custom package or "blueprint" that groups these different pieces of information together into one single unit.

### `*` (Pointers and Structures)

When you connect nodes together, you don't physically place one entire node inside another. Instead, you use a pointer. By placing an asterisk (`*`) next to a data type (like `struct Node *`), you tell the computer that this variable won't hold actual data. Instead, it holds the exact memory address (the physical location) of where another piece of data is stored. In our tree, the left and right connection spots are pointers acting as signposts guiding the computer to the next connected node.

### `->` (The Arrow Operator)

When you have a normal package of data, you can look inside it easily. But when you only have a pointer (the map to the package), you need a special tool to reach inside it. The arrow operator (`->`) tells the computer: "Follow this pointer to the actual memory address, and once you are there, access this specific spot inside the package." For example, `new_node->data = 100` means "go to the new node's location and set its data spot to 100."

### `NULL`

When you create a pointer, it needs to point somewhere. If a node doesn't have any other data connected to it yet (like a newly created node or a leaf at the bottom of the tree), you must explicitly set its connection to NULL. NULL is a special programming keyword that means "empty" or "nowhere." It serves as a safe dead end, telling the computer to stop looking because there is no further data down this path.

## C Code

### Designing a Data Package (Node)

```c
/* Blueprint for a Node */
struct Node {
        int data;               /* Spot for the data */
        struct Node *left;      /* Spot for the left connection */
        struct Node *right;     /* Spot for the right connection */
};

```

### Creating New Data

```c
#include <stdlib.h>

/* Allocate Memory */
struct Node *new_node = malloc(sizeof(struct Node));

if (new_node != NULL) {
        
        /* Save Data */
        new_node->data = 100;

        /* Empty Connections (NULL means empty) */
        new_node->left = NULL;
        new_node->right = NULL;
}

```

### Connecting Data Together

```c
/* Imagine we already have a top node called 'root_node' */
/* and we want to attach our 'new_node' to its left side */

/* Find Parent's empty spot and Attach Child */
root_node->left = new_node;

```

### Deleting Data (Cutting a Connection)

```c
/* If we want to delete a child node that has nothing else connected below it */

/* Cut Link */
root_node->left = NULL;

/* Clean Up Memory */
free(new_node);

```

```c
/* If we want to delete a child node that has only left node connected below it */

/* Cut Link */
root_node->left = new_node->left;

/* Clean Up Memory */
free(new_node);

```

```c
/* If we want to delete a child node that has only right node connected below it */

/* Cut Link */
root_node->left = new_node->right;

/* Clean Up Memory */
free(new_node);

```

```c
/* If we want to delete a child node that has both left and right node connected below it */

/* Cut Link */
root_node->left = new_node->right;

/* save left node */
struct Node *new_parent = new_node->right;

while (new_parent->left != NULL)
        new_parent = new_parent->left;

new_parent->left = new_node->left;

/* Clean Up Memory */
free(new_node);

```

### Complete, Working Example of Tree

```c
#include <stdio.h>
#include <stdlib.h>

/* 1. The Blueprint */
struct Node {
        int data;
        struct Node *left;
        struct Node *right;
};

/* 2. A helper function to build a new package (node) safely */
struct Node* create_node(int data) 
{
        /* Allocate exact memory for one node */
        struct Node *new_node = malloc(sizeof(struct Node));

        /* Make sure the computer actually gave us the memory */
        if (new_node != NULL) {
                new_node->data = data;
                new_node->left = NULL;  /* Set empty connections */
                new_node->right = NULL; 
        }

        return new_node;
}

int main() 
{
        /* 3. Create the Root Node */
        struct Node *root = create_node(50);

        /* 4. Attach Children using the "Smart Rule" */
        /* 25 is smaller than 50, so it goes left */
        root->left = create_node(25);

        /* 75 is bigger than 50, so it goes right */
        root->right = create_node(75);

        /* 5. Prove it works by printing the data */
        printf("Root node: %d\n", root->data);
        printf("Left child: %d\n", root->left->data);
        printf("Right child: %d\n", root->right->data);

        /* 6. The Safety Check: Clean up memory! */
        /* Always free the bottom leaves first, then the root */
        free(root->left);
        free(root->right);
        free(root);

        return 0;
}
```
