#include "llrb.h"

#ifdef NDEBUG
#error "Compile the checks with assertions enabled."
#endif

#include <assert.h>
#include <limits.h>
#include <stdio.h>

typedef struct {
    bool seen[MAX_KEYS];
    int visited;
    int previous_key;
} Walk;

/* Count black keyed nodes, including the current node, down to a missing link. */
static int inspect(const Tree *tree, int id, bool parent_red, Walk *walk)
{
    if (id == NO_NODE) {
        return 0;
    }
    assert(id >= 0 && id < tree->count && !walk->seen[id]);
    walk->seen[id] = true;
    const Node *node = &tree->nodes[id];
    assert(!(parent_red && node->red));
    int left_black = inspect(tree, node->left, node->red, walk);
    if (walk->visited > 0) {
        assert(walk->previous_key < node->key);
    }
    ++walk->visited;
    walk->previous_key = node->key;
    int right_black = inspect(tree, node->right, node->red, walk);
    assert(node->right == NO_NODE || !tree->nodes[node->right].red);
    assert(left_black == right_black);
    return left_black + (node->red ? 0 : 1);
}

static int check_tree(const Tree *tree, const int *keys, int count)
{
    Walk walk = {0};
    int black_height = inspect(tree, tree->root, false, &walk);
    assert(tree->root == NO_NODE || !tree->nodes[tree->root].red);
    assert(walk.visited == count && count == tree->count);
    for (int i = 0; i < count; ++i) {
        assert(tree_contains(tree, keys[i]));
    }
    return black_height;
}

static void check_order(const int *keys, int count)
{
    Tree tree;
    tree_init(&tree);
    for (int i = 0; i < count; ++i) {
        assert(tree_insert(&tree, keys[i]));
        check_tree(&tree, keys, i + 1);
    }
}

static void permute(int *keys, int start, int count)
{
    if (start == count) {
        check_order(keys, count);
        return;
    }
    for (int i = start; i < count; ++i) {
        int saved = keys[i];
        keys[i] = keys[start];
        keys[start] = saved;
        permute(keys, start + 1, count);
        keys[start] = keys[i];
        keys[i] = saved;
    }
}

int main(void)
{
    Tree tree;
    int keys[] = {10, 20, 30, 40, 50, 60, 70};
    const int black_heights[] = {1, 1, 2, 2, 2, 2, 3};
    tree_init(&tree);
    assert(check_tree(&tree, keys, 0) == 0);
    for (int i = 0; i < 7; ++i) {
        assert(tree_insert(&tree, keys[i]));
        assert(check_tree(&tree, keys, i + 1) == black_heights[i]);
        assert(!tree_insert(&tree, keys[i]));
        check_tree(&tree, keys, i + 1);
        assert(!tree_contains(&tree, keys[i] + 1));
    }
    assert(tree.nodes[tree.root].key == 40);
    permute(keys, 0, 7);

    int full[MAX_KEYS];
    tree_init(&tree);
    for (int i = 0; i < MAX_KEYS; ++i) {
        full[i] = i - MAX_KEYS / 2;
        assert(tree_insert(&tree, full[i]));
    }
    assert(!tree_insert(&tree, INT_MAX));
    assert(!tree_contains(&tree, INT_MAX));
    check_tree(&tree, full, MAX_KEYS);
    int extremes[] = {INT_MAX, INT_MIN, 0};
    check_order(extremes, 3);
    puts("Passed LLRB ordering, color, black-height, search and capacity checks.");
    return 0;
}
