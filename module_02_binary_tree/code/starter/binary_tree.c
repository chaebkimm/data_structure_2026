#include "binary_tree.h"

struct TreeNode nodes[20];
int size = 0;
char eq[20] = "1+2*3";
int pos = 0;

int new_node(char data)
{
    /*
     * TODO(core): Save data at the next unused index, initialize both child
     * links to -1, advance size, and return the index that was reserved.
     * Index 0 is a node; it is not the empty-child marker.
     */
    (void)data;
    return -1; /* Placeholder only: valid allocation must return an index. */
}

int term(void)
{
    /*
     * TODO(core): Consume the first digit using eq[pos++] and new_node.
     * For each following '*', consume the operator and next digit, join
     * the old root on the left and the new digit on the right, and keep
     * the operator as the new root. Leave '+' or '\0' for the caller.
     */
    return -1;
}

int terms(void)
{
    /*
     * TODO(core): Begin with term(). For each '+', consume the operator,
     * build the next complete term, and join both subtrees under that '+'.
     * Returning the new root each time preserves multiplication precedence.
     */
    return -1;
}

int eval_tree(int node)
{
    /*
     * TODO(core): For a digit leaf, return data - '0'. Otherwise evaluate
     * the left child and then the right child into local integers, combine
     * them with '+' or '*', and return the answer without changing nodes.
     */
    (void)node;
    return -1; /* Safe placeholder; the tests report missing work. */
}
