#include <stdio.h>
#include <stdlib.h>

typedef struct AutopsyNode {
    int key;
    struct AutopsyNode *left;
    struct AutopsyNode *right;
} AutopsyNode;

static AutopsyNode *make_node(int key)
{
    AutopsyNode *node = (AutopsyNode *)malloc(sizeof *node);

    if (node != NULL) {
        node->key = key;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

static AutopsyNode *make_demo_tree(void)
{
    AutopsyNode *root = make_node(20);
    AutopsyNode *upper = make_node(30);
    AutopsyNode *middle = make_node(25);

    if (root == NULL || upper == NULL || middle == NULL) {
        free(root);
        free(upper);
        free(middle);
        return NULL;
    }

    root->right = upper;
    upper->left = middle;
    return root;
}

static void destroy_reachable(AutopsyNode *node)
{
    if (node != NULL) {
        destroy_reachable(node->left);
        destroy_reachable(node->right);
        free(node);
    }
}

#ifdef AUTOPSY_INSPECT_ONLY
static AutopsyNode *correct_left_rotation(AutopsyNode *root)
{
    AutopsyNode *upper = root->right;
    AutopsyNode *middle = upper->left;

    root->right = middle;
    upper->left = root;
    return upper;
}
#else
static AutopsyNode *faulty_left_rotation(AutopsyNode *root)
{
    AutopsyNode *upper = root->right;

    /*
     * Intentional bounded defect: NULL is already the wrong replacement,
     * but node 25 is still reachable through upper->left at this moment.
     */
    root->right = NULL;

    /*
     * This next overwrite removes that last reachable link to node 25.
     * The correct algorithm first saves upper->left as the middle subtree
     * and assigns that saved address to root->right.
     */
    upper->left = root;
    return upper;
}
#endif

int main(void)
{
    AutopsyNode *root = make_demo_tree();

    if (root == NULL) {
        fputs("Autopsy setup allocation failed.\n", stderr);
        return 1;
    }

#ifdef AUTOPSY_INSPECT_ONLY
    puts("INSPECT ONLY: 20 has right child 30; 30 has left child 25.");
    puts("A left rotation must move 25 to become the right child of 20.");
    root = correct_left_rotation(root);
    if (root->key != 30 ||
        root->left == NULL ||
        root->left->key != 20 ||
        root->left->right == NULL ||
        root->left->right->key != 25) {
        destroy_reachable(root);
        fputs("Safe inspection setup failed.\n", stderr);
        return 1;
    }
    puts("Safe inspection preserved all three reachable nodes.");
#else
    root = faulty_left_rotation(root);
#endif

    destroy_reachable(root);
    return 0;
}
