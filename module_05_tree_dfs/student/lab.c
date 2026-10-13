#include "module_02_binary_tree/student/lab.c"
/* Both earlier labs call their capacity global `capacity`. */
#define capacity stack_capacity
#include "module_04_stack/student/lab.c"
#undef capacity

void tree_traversal(int i) {
	if (i < 0) {
		return;
	}
	/* preorder */
	tree_traversal(nodes[i].left);
	/* inorder */
	tree_traversal(nodes[i].right);
	/* postorder */
}

int progress[10] = {0};

void tree_traversal_proceed(int i) {
	if (i < 0) {
		pop();
		return;
	}
	int step = progress[i]++;
	switch (step) {
	case 0: /* preorder */
		push(nodes[i].left);
		return;
	case 1: /* inorder */
		push(nodes[i].right);
		return;
	case 2: /* postorder */
		pop();
		return;
	}
}

void tree_traversal_with_stack(int root_index) {
	top = -1;
	push(root_index);
	while (!is_empty()) {
		tree_traversal_proceed(peek());
	}
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

char infix[20] = "";
int infix_pos = 0;

int prec2(char c) {
	if (c >= '0' && c <= '9') {
		return 3;
	} else {
		return prec(c);
	}
}

void write_char(char c) { infix[infix_pos++] = c; }

void _write_infix(int i) {
	if (i < 0) {
		return;
	}
	char c = nodes[i].data;
	if (c >= '0' && c <= '9') {
		write_char(c);
		return;
	}
	char l = nodes[nodes[i].left].data;
	char r = nodes[nodes[i].right].data;

	/* preorder */
	if (prec2(l) < prec2(c)) {
		write_char('(');
	}
	_write_infix(nodes[i].left);

	/* inorder */
	if (prec2(l) < prec2(c)) {
		write_char(')');
	}
	write_char(c);

	if (prec2(r) <= prec2(c)) {
		write_char('(');
	}
	_write_infix(nodes[i].right);

	/* postorder */
	if (prec2(r) <= prec2(c)) {
		write_char(')');
	}
}

void write_infix(int root) {
	infix_pos = 0;
	_write_infix(root);
	write_char('\0');
}
