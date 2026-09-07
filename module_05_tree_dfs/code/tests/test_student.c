#include "tree_dfs.h"

#include <stdbool.h>
#include <stdio.h>

/* Add one focused test for each traversal role. */
static bool test_preorder_copy(void) { return false; }
static bool test_inorder_print(void) { return false; }
static bool test_postorder_evaluate(void) { return false; }

int main(void)
{
    int failures = 0;
    failures += test_preorder_copy() ? 0 : 1;
    failures += test_inorder_print() ? 0 : 1;
    failures += test_postorder_evaluate() ? 0 : 1;
    puts(failures == 0 ? "Student tests passed." : "Complete the three TODO tests.");
    return failures == 0 ? 0 : 1;
}
