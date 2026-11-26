enum { CAPACITY = 12 };

struct Rbtree_Node {
    int data;
    int left;
    int right;
    int is_red;
};

struct Rbtree_Node nodes[CAPACITY];
int nodes_size = 0;

int new_node(int d) {
    if (nodes_size == CAPACITY) { return -1; }
    int i = nodes_size++;
    nodes[i].data = d;
    nodes[i].is_red = 1;
    nodes[i].left = -1;
    nodes[i].right = -1;
    return i;
}

int check_red(int i) {
    return i != -1 && nodes[i].is_red;
}
int add_node_private(int i, int value) {
    if (i == -1) { return new_node(value); }
    if (value == nodes[i].data) { return i; }
    if (value < nodes[i].data) {
        nodes[i].left = add_node_private(nodes[i].left, value);
    } else {
        nodes[i].right = add_node_private(nodes[i].right, value);
    }
    int l = nodes[i].left;
    int r = nodes[i].right;
    if (check_red(r) && !check_red(l)) {
        int rl = nodes[r].left;
        nodes[r].left = i;
        nodes[i].right = rl;
        nodes[r].is_red = nodes[i].is_red;
        nodes[i].is_red = 1;
        /* int ll = l; */
        l = i;
        i = r;
        r = nodes[i].right;
    }
    if (check_red(l)) {
        int ll = nodes[l].left;
        if (check_red(ll)) {
            int lr = nodes[l].right;
            nodes[l].right = i;
            nodes[l].is_red = nodes[i].is_red;
            nodes[i].left = lr;
            nodes[i].is_red = 1;
            /* int rr = r; */
            r = i;
            i = l;
            l = ll;
            /* ll = nodes[i].left; */
        }
    }
    if (check_red(l) && check_red(r)) {
        nodes[l].is_red = nodes[r].is_red = 0;
        nodes[i].is_red = 1;
    }
    return i;
}

int add_node(int root, int value) {
    root = add_node_private(root, value);
    if (root != -1) { nodes[root].is_red = 0; }
    return root;
}