#ifndef LLRB_H
#define LLRB_H

#include <stdbool.h>

enum { NO_NODE = -1, MAX_KEYS = 64 };

typedef struct {
    int key;
    int left;
    int right;
    bool red;  /* Color of the link from the parent to this node. */
} Node;

typedef struct {
    Node nodes[MAX_KEYS];
    int root;
    int count;
} Tree;

void tree_init(Tree *tree);
bool tree_contains(const Tree *tree, int key);
bool tree_insert(Tree *tree, int key);

#endif
