#include <stdio.h>

/* Compile only this source; it includes the classroom lab. */
#include "../../student/lab.c"

int main(void) {
    alphabet_init();
    int root = tree_connect();
    tree_traversal(root);
    printf("Recursive last visits: %c %c %c\n",
           pre_data, in_data, post_data);

    tree_traversal_with_stack(root);
    printf("Stack last visits: %c %c %c\n",
           pre_data, in_data, post_data);

    convert_to_postfix();
    root = build_tree_from_postfix();
    write_infix(root);
    printf("%s -> %s\n", postfix, infix);
    printf("Root: %d; nodes: %d; top: %d\n", root, nodes_size, top);
    return 0;
}
