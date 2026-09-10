#include "binary_tree.h"

/* Reset size and pos before building another expression in this array. */
struct TreeNode nodes[20];
int size = 0;
char eq[20] = "1+2*3";
int pos = 0;

int new_node(char data)
{
    nodes[size].data = data;
    nodes[size].left = nodes[size].right = -1; /* No children yet. */
    return size++; /* Return the old index and advance the count. */
}

int term(void)
{
    int root = new_node(eq[pos++]); /* First digit starts the term. */

    while (eq[pos] == '*') {
        int op = new_node(eq[pos++]);
        int num = new_node(eq[pos++]);

        nodes[op].left = root; /* Preserve the entire term built so far. */
        nodes[op].right = num;
        root = op;
    }
    return root; /* '+' or '\0' remains unread. */
}

int terms(void)
{
    int root = term();

    while (eq[pos] == '+') {
        int op = new_node(eq[pos++]);
        int next_term = term(); /* Finish multiplication before addition. */

        nodes[op].left = root;
        nodes[op].right = next_term;
        root = op;
    }
    return root;
}

int eval_tree(int node)
{
    if (nodes[node].data >= '0' && nodes[node].data <= '9') {
        return nodes[node].data - '0'; /* Digit leaf: stop recursing. */
    }
    if (nodes[node].data != '+' && nodes[node].data != '*') {
        return -1;
    }

    /* Child answers are local values; the stored tree stays unchanged. */
    int left = eval_tree(nodes[node].left);
    int right = eval_tree(nodes[node].right);

    if (nodes[node].data == '+') return left + right;
    if (nodes[node].data == '*') return left * right;
    return -1;
}
