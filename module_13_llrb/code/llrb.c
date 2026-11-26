#include "llrb.h"

void tree_init(Tree *tree)
{
    *tree = (Tree){.root = NO_NODE};
}

bool tree_contains(const Tree *tree, int key)
{
    int id = tree->root;
    while (id != NO_NODE) {
        const Node *node = &tree->nodes[id];
        if (key == node->key) {
            return true;
        }
        id = key < node->key ? node->left : node->right;
    }
    return false;
}

static bool is_red(const Tree *tree, int id)
{
    return id != NO_NODE && tree->nodes[id].red;
}

/* The promoted node inherits the link from the parent. */
static int rotate_left(Tree *tree, int id)
{
    Node *old = &tree->nodes[id];
    int next = old->right;
    Node *top = &tree->nodes[next];
    old->right = top->left;
    top->left = id;
    top->red = old->red;
    old->red = true;
    return next;
}

static int rotate_right(Tree *tree, int id)
{
    Node *old = &tree->nodes[id];
    int next = old->left;
    Node *top = &tree->nodes[next];
    old->left = top->right;
    top->right = id;
    top->red = old->red;
    old->red = true;
    return next;
}

/* In bottom-up insertion the incoming link is black and both children red. */
static void flip_colors(Tree *tree, int id)
{
    Node *node = &tree->nodes[id];
    node->red = true;
    tree->nodes[node->left].red = false;
    tree->nodes[node->right].red = false;
}

static int insert_at(Tree *tree, int id, int key)
{
    if (id == NO_NODE) {
        int fresh = tree->count++;
        tree->nodes[fresh] = (Node){key, NO_NODE, NO_NODE, true};
        return fresh;
    }

    Node *node = &tree->nodes[id];
    if (key < node->key) {
        node->left = insert_at(tree, node->left, key);
    } else if (key > node->key) {
        node->right = insert_at(tree, node->right, key);
    } else {
        return id;
    }

    if (is_red(tree, node->right) && !is_red(tree, node->left)) {
        id = rotate_left(tree, id);
        node = &tree->nodes[id];
    }
    if (is_red(tree, node->left) && is_red(tree, tree->nodes[node->left].left)) {
        id = rotate_right(tree, id);
        node = &tree->nodes[id];
    }
    if (is_red(tree, node->left) && is_red(tree, node->right)) {
        flip_colors(tree, id);
    }
    return id;
}

bool tree_insert(Tree *tree, int key)
{
    if (tree->count == MAX_KEYS) {
        return false;
    }
    int before = tree->count;
    tree->root = insert_at(tree, tree->root, key);
    tree->nodes[tree->root].red = false;
    return tree->count > before;
}
