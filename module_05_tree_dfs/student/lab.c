struct TreeNode {
    char data;
    int left;
    int right;
};

struct TreeNode nodes[10];
int capacity = 10;
int size = 0;


void alphabet_init() {
	size = capacity;

	for (int i = 0; i < capacity; i++) {
		nodes[i].data = 'A' + i;
		nodes[i].left = nodes[i].right = -1;
	}
}

int tree_connect() {
	int root = 0;

	nodes[root].left = 1;
	nodes[root].right = 2;

	nodes[1].left = 3;
	nodes[1].right = 4;

	nodes[5].left = root;
	root = 5;
  	nodes[5].right = 6;

	return root;
}

int pre_data, in_data, post_data;

void tree_traversal(int i) {
    pre_data = nodes[i].data;
    if (nodes[i].left != -1) {
        tree_traversal(nodes[i].left);
    }
    in_data = nodes[i].data;
    if (nodes[i].right != -1) {
        tree_traversal(nodes[i].right);
    }
    post_data = nodes[i].data;
}

char post_eq[6] = "123*+"; /* assume no malformed post_eq */

int eq_tree() {
    int stack[10];
    int top = -1;
    size = 0;
    for (int i = 0; post_eq[i] != '\0'; i++) {
        char c = post_eq[i];
        nodes[i].data = c;
        if (c >= '0' && c <= '9') {
            nodes[i].left = nodes[i].right = -1;
        } else {
            nodes[i].right = stack[top--];
            nodes[i].left = stack[top--];

        }
        stack[++top] = i;
        size++;
    }
    return stack[top];
}

int prec(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/' || op == '%') {
        return 2;
    }
    else if (op >= '0' && op <= '9') {
        return 3;
    }
    return 0;
}

char infix[10] = "";
int pos = 0;

void write_infix(int i) {
    char c = nodes[i].data;
    if (c >= '0' && c <= '9') {
        infix[pos++] = c;
        return;
    }

    int l = nodes[i].left;
    char l_data = nodes[l].data;

    if (prec(c) > prec(l_data)) {
        infix[pos++] = '(';
    }

    write_infix(nodes[i].left);

    if (prec(c) > prec(l_data)) {
        infix[pos++] = ')';
    }

    infix[pos++] = c;

    int r = nodes[i].right;
    char r_data = nodes[r].data;
    
    if (prec(c) >= prec(r_data)) {
        infix[pos++] = '(';
    }

    write_infix(r);

    if (prec(c) >= prec(r_data)) {
        infix[pos++] = ')';
    }
}

void start_write_infix(int root) {
    pos = 0;
    write_infix(root);
    infix[pos++] = '\0';
}