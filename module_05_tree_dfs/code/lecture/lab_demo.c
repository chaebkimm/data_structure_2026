#include <stdio.h>
#include <string.h>

/* Use the classroom implementation directly; compile only this source file. */
#include "../../student/lab.c"

int main(void) {
    alphabet_init();
    int root = tree_connect();
    tree_traversal(root);
    /* These globals retain the last visit, not a complete traversal sequence. */
    printf("Last visits: %c %c %c\n", pre_data, in_data, post_data);

    root = eq_tree();
    start_write_infix(root);
    printf("%s -> %s\n", post_eq, infix);

    strcpy(post_eq, "12+3*");
    root = eq_tree();
    start_write_infix(root);
    printf("%s -> %s\n", post_eq, infix);

    strcpy(post_eq, "123--");
    root = eq_tree();
    start_write_infix(root);
    printf("%s -> %s\n", post_eq, infix);

    strcpy(post_eq, "12+");
    root = eq_tree();
    start_write_infix(root);
    printf("%s -> %s\n", post_eq, infix);
    return 0;
}
