#include "tree_dfs.h"

#include <stdbool.h>
#include <stdio.h>

/* A stack stores node addresses. The nodes themselves stay in the tree. */
typedef struct {
    const Node *items[TREE_DFS_POOL_CAPACITY];
    size_t size;
} NodeStack;

static bool push(NodeStack *stack, const Node *node)
{
    if (stack->size == TREE_DFS_POOL_CAPACITY) return false;
    stack->items[stack->size++] = node;
    return true;
}

/* Call pop and peek only when size is greater than zero. */
static const Node *pop(NodeStack *stack)
{
    return stack->items[--stack->size];
}

static const Node *peek(const NodeStack *stack)
{
    return stack->items[stack->size - 1U];
}

static bool preorder(const Node *root)
{
    NodeStack stack = {0};

    if (root == NULL) return true;
    if (!push(&stack, root)) return false;

    while (stack.size > 0U) {
        const Node *node = pop(&stack);
        printf("%c ", node->data);

        /* Right waits below left, so left is popped first. */
        if (node->right != NULL && !push(&stack, node->right)) return false;
        if (node->left != NULL && !push(&stack, node->left)) return false;
    }
    return true;
}

static bool inorder(const Node *root)
{
    NodeStack stack = {0};
    const Node *current = root;

    while (current != NULL || stack.size > 0U) {
        while (current != NULL) {
            if (!push(&stack, current)) return false;
            current = current->left;
        }

        current = pop(&stack);
        printf("%c ", current->data);
        current = current->right;
    }
    return true;
}

static bool postorder(const Node *root)
{
    NodeStack stack = {0};
    const Node *current = root;
    const Node *last_visited = NULL;

    while (current != NULL || stack.size > 0U) {
        if (current != NULL) {
            if (!push(&stack, current)) return false;
            current = current->left;
        } else {
            const Node *node = peek(&stack);

            if (node->right != NULL && last_visited != node->right) {
                /* Keep the parent until its right subtree is complete. */
                current = node->right;
            } else {
                printf("%c ", node->data);
                last_visited = pop(&stack);
            }
        }
    }
    return true;
}

int main(void)
{
    Node three = {'3', NULL, NULL};
    Node five = {'5', NULL, NULL};
    Node two = {'2', NULL, NULL};
    Node times = {'*', &five, &two};
    Node plus = {'+', &three, &times};

    printf("preorder: ");
    if (!preorder(&plus)) return 1;
    printf("\ninorder: ");
    if (!inorder(&plus)) return 1;
    printf("\npostorder: ");
    if (!postorder(&plus)) return 1;
    putchar('\n');
    return 0;
}
