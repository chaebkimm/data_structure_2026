#include <stdio.h>

#include "binary_tree.h"

/* One expression at a time; these nodes live for the whole program. */
struct TreeNode nodes[20];
int node_count = 0;

struct TreeNode *new_node(int data)
{
    if (node_count == 20) {
        return NULL;
    }
    struct TreeNode *node = &nodes[node_count++];
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int precedence(char op)
{
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

/* q points to a shared cursor; call through build_expression below. */
struct TreeNode *expr_tree(char **q, int min)
{
    if (**q < '0' || **q > '9') {
        return NULL;
    }

    struct TreeNode *node = new_node(*(*q)++ - '0');
    if (node == NULL) return NULL;

    while (**q != '\0') {
        char op = **q;
        int level = precedence(op);
        if (level == 0) return NULL; /* Not a supported operator. */
        if (level < min) break;     /* Leave it for the caller. */

        (*q)++;
        struct TreeNode *parent = new_node(op);
        if (parent == NULL) return NULL;
        parent->left = node;
        parent->right = expr_tree(q, level + 1);
        if (parent->right == NULL) return NULL;
        node = parent;
    }
    return node;
}

struct TreeNode *build_expression(char *text)
{
    node_count = 0;
    if (text == NULL) return NULL;

    char *cursor = text;
    struct TreeNode *root = expr_tree(&cursor, 1);
    if (root == NULL || *cursor != '\0') {
        node_count = 0;
        return NULL;
    }
    return root;
}

/* Only finite, unshared expression trees; this is not a graph validator. */
int eval_tree(const struct TreeNode *node, double *out)
{
    if (node == NULL || out == NULL) return 0;

    if (node->left == NULL && node->right == NULL) {
        if (node->data < 0 || node->data > 9) return 0;
        *out = node->data;
        return 1;
    }
    if (node->left == NULL || node->right == NULL) return 0;

    double left;
    double right;
    if (!eval_tree(node->left, &left)) return 0;
    if (!eval_tree(node->right, &right)) return 0;

    double result;
    switch (node->data) {
    case '+': result = left + right; break;
    case '-': result = left - right; break;
    case '*': result = left * right; break;
    case '/':
        if (right == 0.0) return 0;
        result = left / right;
        break;
    default: return 0;
    }
    *out = result;
    return 1;
}

int main(int argc, char **argv)
{
    char example[] = "3+5*2";
    char *text = argc > 1 ? argv[1] : example;
    struct TreeNode *root = build_expression(text);
    if (root == NULL) {
        puts("Invalid expression or node array full.");
        return 1;
    }

    double answer;
    if (!eval_tree(root, &answer)) {
        puts("Invalid expression tree or division by zero.");
        return 1;
    }
    printf("%s = %g\n", text, answer);
    return 0;
}
