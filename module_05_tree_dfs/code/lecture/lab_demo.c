#include <stdio.h>
#include <string.h>

/* Compile only this source; it includes the classroom lab. */
#include "../../student/lab.c"

static void show_expression(const char *input) {
    (void)strcpy(postfix, input);
    int root = build_tree_from_postfix();
    write_infix(root);
    printf("%s -> %s\n", postfix, infix);
}

int main(void) {
    alphabet_init();
    int root = tree_connect();
    tree_traversal(root);
    printf("Recursive traversal complete (visit comments).\n");

    (void)memset(progress, 0, sizeof progress);
    tree_traversal_with_stack(root);
    printf("Stack progress (A-G):");
    for (int i = 0; i < 7; ++i) {
        printf(" %d", progress[i]);
    }
    putchar('\n');

    convert_to_postfix();
    root = build_tree_from_postfix();
    write_infix(root);
    printf("%s -> %s\n", postfix, infix);
    printf("Root: %d; nodes: %d; top: %d\n", root, nodes_size, top);
    show_expression("1234+++");
    show_expression("12+3*");
    show_expression("831-/");
    return 0;
}
