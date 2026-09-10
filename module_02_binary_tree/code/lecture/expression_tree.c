#include "binary_tree.h"

#include <stdio.h>

int main(void)
{
    int root = terms();           /* Build the textbook's initial eq. */
    int answer = eval_tree(root); /* Start evaluation from the root index. */

    (void)printf("%s = %d\n", eq, answer);
    return 0;
}
