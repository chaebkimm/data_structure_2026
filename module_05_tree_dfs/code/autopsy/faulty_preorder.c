#include <stddef.h>
#include <stdio.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

/*
 * This deliberately faulty program is isolated from the graded traversal.
 * Predict its complete output before running it, then locate the earliest
 * decision that causes the behavior to differ from the required preorder.
 */
int main(void)
{
    Node node20 = {20, NULL, NULL};
    Node node40 = {40, NULL, NULL};
    Node node70 = {70, NULL, NULL};
    Node node30 = {30, &node20, &node40};
    Node node50 = {50, &node30, &node70};
    const Node *stack[5];
    size_t size = 0U;
    size_t visit_count = 0U;

    stack[size] = &node50;
    size += 1U;

    while (size > 0U) {
        const Node *current;

        size -= 1U;
        current = stack[size];
        if (visit_count > 0U) {
            putchar(',');
        }
        printf("%d", current->key);
        visit_count += 1U;

        if (current->left != NULL) {
            stack[size] = current->left;
            size += 1U;
        }
        if (current->right != NULL) {
            stack[size] = current->right;
            size += 1U;
        }
    }

    putchar('\n');
    return 0;
}
