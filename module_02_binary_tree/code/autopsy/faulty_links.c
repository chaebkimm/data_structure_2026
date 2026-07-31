/*
 * INTENTIONALLY INVALID TREE-SHAPE TRAINING PROGRAM.
 *
 * This program remains memory-safe: every address points inside the fixed
 * node array. Its purpose is to compare an address diagram with the result
 * of a deliberately simple branch-counting function.
 */

#include "tree_arena.h"

#include <stdio.h>

static size_t count_from(const TreeNode *node)
{
    if (node == NULL) {
        return 0U;
    }

    return 1U + count_from(node->left) + count_from(node->right);
}

static size_t count_key_from(const TreeNode *node, int wanted_key)
{
    size_t here;

    if (node == NULL) {
        return 0U;
    }

    here = node->key == wanted_key ? 1U : 0U;
    return here +
        count_key_from(node->left, wanted_key) +
        count_key_from(node->right, wanted_key);
}

int main(void)
{
    TreeNode nodes[4];
    TreeArena arena;
    size_t index;

    for (index = 0U; index < 4U; ++index) {
        nodes[index].key = (int)((index + 1U) * 10U);
        nodes[index].left = NULL;
        nodes[index].right = NULL;
    }

    arena.nodes = nodes;
    arena.count = 4U;
    arena.root = &nodes[0];

    nodes[0].left = &nodes[1];
    nodes[0].right = &nodes[2];
    nodes[1].left = &nodes[3];
    nodes[2].right = &nodes[3];

    (void)printf("arena slots: %zu\n", arena.count);
    (void)printf("branch-count result: %zu\n", count_from(arena.root));
    (void)printf(
        "times key 40 is encountered: %zu\n",
        count_key_from(arena.root, 40)
    );
    (void)printf(
        "node[1].left=%p, node[2].right=%p\n",
        (void *)nodes[1].left,
        (void *)nodes[2].right
    );
    return 0;
}
