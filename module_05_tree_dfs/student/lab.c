#include "../../module_02_binary_tree/student/lab.c"
/* Both earlier labs use capacity; keep the stack's definition distinct. */
#define capacity stack_capacity
#include "../../module_04_stack/student/lab.c"
#undef capacity

int pre_data, in_data, post_data;

void tree_traversal(int i) {
    if (i < 0) {
        return;
    }
    pre_data = nodes[i].data;
    tree_traversal(nodes[i].left);
    in_data = nodes[i].data;
    tree_traversal(nodes[i].right);
    post_data = nodes[i].data;
}

int build_tree_from_postfix() {
    top = -1;
    nodes_size = 0;
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        nodes[i].data = c;
        if (c >= '0' && c <= '9') {
            nodes[i].left = -1;
            nodes[i].right = -1;
        } else {
            nodes[i].right = pop();
            nodes[i].left = pop();
        }
        push(i);
        ++nodes_size;
    }
    return pop();
}

char infix[10] = "";
int infix_pos = 0;

/* assume original equation did not have parenthesis*/
void _write_infix(int i) {
    char c = nodes[i].data;
    if (c >= '0' && c <= '9') {
        infix[infix_pos++] = c;
        return;
    }
    _write_infix(nodes[i].left);
    infix[infix_pos++] = c;
    _write_infix(nodes[i].right);
}

/* only single run */
void write_infix(int root) {
    _write_infix(root);
    infix[infix_pos++] = '\0';
}

int progress[10] = {0};

void tree_traversal_proceed() {
    int i = peek();
    if (i < 0) {
        pop();
        return;
    }

    int step = progress[i]++;
    switch (step) {
        case 0:
            pre_data = nodes[i].data;
            push(nodes[i].left);
            return;
        case 1:
            in_data = nodes[i].data;
            push(nodes[i].right);
            return;
        case 2:
            post_data = nodes[i].data;
            pop();
            return;
    }
}

/* only single run */
void tree_traversal_with_stack(int root_index) {
    top = -1;
    push(root_index);
    while (!is_empty()) {
        tree_traversal_proceed();
    }
}
