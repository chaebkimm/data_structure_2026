struct TreeNode {
    char data;
    int left;
    int right;
};

struct TreeNode nodes[10];
int nodes_capacity = 10;
int nodes_size = 0;

void alphabet_init()
{
    nodes_size = 10;

    for (int i = 0; i < nodes_capacity; i++) {
        nodes[i].data = 'A' + i;
        nodes[i].left = nodes[i].right = -1;
    }
}

int root = 0;

void tree_connect()
{
    nodes[root].left = 1;
    nodes[root].right = 2;

    nodes[1].left = 3;
    nodes[1].right = 4;

    nodes[2].left = 5;
    nodes[2].right = 6;
}

char buffer[10] = "";
int buf_pos = 0;

void tree_recursion(int i)
{
    if (i >= 0 && i < nodes_size) {
        tree_recursion(nodes[i].left);
        tree_recursion(nodes[i].right);
        buffer[buf_pos++] = nodes[i].data;
    }
}

void eq_plus_init()
{
    char eq[10] = "1+2+3";
    int eq_size = 5;
    nodes_size = eq_size;

    for (int i = 0; i < eq_size; i++) {
        nodes[i].data = eq[i];
        nodes[i].left = nodes[i].right = -1;
    }
}

void eq_plus_connect()
{
    int i = 0;
    root = i++;
    while (i < nodes_size) {
        int op = i++;
        int num = i++;
        nodes[op].left = root;
        nodes[op].right = num;
        root = op;
    }
}

int eval(int i)
{
    if (nodes[i].data >= '0' && nodes[i].data <= '9') {
        return nodes[i].data - '0';
    }
    int l = eval(nodes[i].left);
    int r = eval(nodes[i].right);
    return l + r;
}