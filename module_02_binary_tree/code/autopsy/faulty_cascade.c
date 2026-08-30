/*
 * INTENTIONALLY INVALID SHARED-CHILD TRAINING FIXTURE.
 *
 * The six local node objects remain alive throughout main. The child links
 * contain no cycle, so the observation is memory-safe. The defect is the
 * shared link, not the supplied recursive clearance routine.
 */

#include "binary_tree.h"

#include <stdio.h>

/* Supplied here so this standalone exercise does not need the starter. */
void tree_clear(struct TreeNode *node)
{
    if (node == NULL) {
        return;
    }

    tree_clear(node->left);
    node->left = NULL;
    tree_clear(node->right);
    node->right = NULL;
    node->data = 0;
}

int main(void)
{
    struct TreeNode three = { 3, NULL, NULL };
    struct TreeNode shared_five = { 5, NULL, NULL };
    struct TreeNode plus = { '+', &three, &shared_five };
    struct TreeNode two = { 2, NULL, NULL };
    struct TreeNode minus = { '-', &shared_five, &two };
    struct TreeNode root = { '*', &plus, &minus };

    (void)printf("before: shared operand data=%d\n", shared_five.data);

    tree_clear(root.left);
    root.left = NULL;

    (void)printf("after clearing and detaching the plus branch:\n");
    (void)printf("root.left is NULL: %s\n", root.left == NULL ? "yes" : "no");
    (void)printf(
        "root.right still points to minus: %s\n",
        root.right == &minus ? "yes" : "no"
    );
    (void)printf(
        "minus.left still points to shared_five: %s\n",
        minus.left == &shared_five ? "yes" : "no"
    );
    (void)printf("minus.left->data=%d\n", minus.left->data);
    return 0;
}
