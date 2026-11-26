#include "llrb.h"

#include <stdio.h>

static void print_tree(const Tree *tree, int id, int depth, const char *side)
{
    if (id == NO_NODE) {
        return;
    }
    const Node *node = &tree->nodes[id];
    printf("%*s%s %d%c\n", 3 * depth, "", side, node->key, node->red ? 'R' : 'B');
    print_tree(tree, node->left, depth + 1, "L");
    print_tree(tree, node->right, depth + 1, "R");
}

static void show_insertions(const int *keys, size_t count)
{
    Tree tree;
    tree_init(&tree);
    for (size_t i = 0; i < count; ++i) {
        tree_insert(&tree, keys[i]);
        printf("Insert %d\n", keys[i]);
        print_tree(&tree, tree.root, 0, "root");
    }
}

int main(void)
{
    const int ascending[] = {10, 20, 30, 40, 50, 60, 70};
    const int descending[] = {30, 20, 10};
    puts("Ascending keys");
    show_insertions(ascending, sizeof ascending / sizeof ascending[0]);
    puts("\nDescending keys in a fresh tree");
    show_insertions(descending, sizeof descending / sizeof descending[0]);
    return 0;
}
