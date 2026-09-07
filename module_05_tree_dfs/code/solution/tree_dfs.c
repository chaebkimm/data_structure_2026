#include "tree_dfs.h"

#include <limits.h>
#include <stdbool.h>

static bool is_digit(char data) { return data >= '0' && data <= '9'; }
static bool is_operator(char data) { return data == '+' || data == '*'; }

static int priority(char data)
{
    if (data == '*') return 2;
    if (data == '+') return 1;
    return 3;
}

static TreeDfsStatus copy_node(
    const Node *original,
    NodePool *destination,
    Node **out_copy
)
{
    Node *copy;
    TreeDfsStatus status;

    if (original == NULL) {
        *out_copy = NULL;
        return TREE_DFS_OK;
    }
    status = tree_node_create(destination, original->data, &copy);
    if (status != TREE_DFS_OK) return status;
    status = copy_node(original->left, destination, &copy->left);
    if (status != TREE_DFS_OK) return status;
    status = copy_node(original->right, destination, &copy->right);
    if (status != TREE_DFS_OK) return status;
    *out_copy = copy;
    return TREE_DFS_OK;
}

TreeDfsStatus tree_copy_preorder(
    const Node *original,
    NodePool *destination,
    Node **out_copy
)
{
    size_t used_before;
    Node *candidate = NULL;
    TreeDfsStatus status;

    if (destination == NULL || out_copy == NULL) {
        return TREE_DFS_INVALID_ARGUMENT;
    }
    used_before = destination->used;
    status = copy_node(original, destination, &candidate);
    if (status != TREE_DFS_OK) {
        destination->used = used_before;
        return status;
    }
    *out_copy = candidate;
    return TREE_DFS_OK;
}

typedef struct {
    char *data;
    size_t capacity;
    size_t length;
} TextOutput;

static TreeDfsStatus append_character(TextOutput *output, char character)
{
    if (output->length + 1U >= output->capacity) {
        return TREE_DFS_OUTPUT_TOO_SMALL;
    }
    output->data[output->length++] = character;
    output->data[output->length] = '\0';
    return TREE_DFS_OK;
}

static TreeDfsStatus print_node(const Node *node, TextOutput *output)
{
    TreeDfsStatus status;
    bool parentheses;

    if (node == NULL) return TREE_DFS_INVALID_EXPRESSION;
    if (is_digit(node->data)) {
        if (node->left != NULL || node->right != NULL) {
            return TREE_DFS_INVALID_EXPRESSION;
        }
        return append_character(output, node->data);
    }
    if (!is_operator(node->data) || node->left == NULL || node->right == NULL) {
        return TREE_DFS_INVALID_EXPRESSION;
    }

    parentheses = is_operator(node->left->data) &&
        priority(node->left->data) < priority(node->data);
    if (parentheses && (status = append_character(output, '(')) != TREE_DFS_OK) return status;
    status = print_node(node->left, output);
    if (status != TREE_DFS_OK) return status;
    if (parentheses && (status = append_character(output, ')')) != TREE_DFS_OK) return status;
    status = append_character(output, node->data);
    if (status != TREE_DFS_OK) return status;

    parentheses = is_operator(node->right->data) &&
        priority(node->right->data) <= priority(node->data);
    if (parentheses && (status = append_character(output, '(')) != TREE_DFS_OK) return status;
    status = print_node(node->right, output);
    if (status != TREE_DFS_OK) return status;
    if (parentheses) return append_character(output, ')');
    return TREE_DFS_OK;
}

TreeDfsStatus tree_print_inorder(
    const Node *root,
    char *output,
    size_t output_capacity
)
{
    TextOutput candidate;
    TreeDfsStatus status;

    if (root == NULL || output == NULL || output_capacity == 0U) {
        return TREE_DFS_INVALID_ARGUMENT;
    }
    candidate = (TextOutput){output, output_capacity, 0U};
    output[0] = '\0';
    status = print_node(root, &candidate);
    if (status != TREE_DFS_OK) output[0] = '\0';
    return status;
}

static TreeDfsStatus evaluate_node(const Node *node, int *out_value)
{
    int left;
    int right;
    TreeDfsStatus status;

    if (node == NULL) return TREE_DFS_INVALID_EXPRESSION;
    if (is_digit(node->data)) {
        if (node->left != NULL || node->right != NULL) {
            return TREE_DFS_INVALID_EXPRESSION;
        }
        *out_value = (int)(node->data - '0');
        return TREE_DFS_OK;
    }
    if (!is_operator(node->data) || node->left == NULL || node->right == NULL) {
        return TREE_DFS_INVALID_EXPRESSION;
    }
    status = evaluate_node(node->left, &left);
    if (status != TREE_DFS_OK) return status;
    status = evaluate_node(node->right, &right);
    if (status != TREE_DFS_OK) return status;

    if (node->data == '+') {
        if (left > INT_MAX - right) return TREE_DFS_ARITHMETIC_OVERFLOW;
        *out_value = left + right;
    } else {
        if (left != 0 && right > INT_MAX / left) {
            return TREE_DFS_ARITHMETIC_OVERFLOW;
        }
        *out_value = left * right;
    }
    return TREE_DFS_OK;
}

TreeDfsStatus tree_evaluate_postorder(const Node *root, int *out_value)
{
    int candidate;
    TreeDfsStatus status;

    if (root == NULL || out_value == NULL) return TREE_DFS_INVALID_ARGUMENT;
    status = evaluate_node(root, &candidate);
    if (status == TREE_DFS_OK) *out_value = candidate;
    return status;
}
