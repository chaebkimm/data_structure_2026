#include "module_02_binary_tree/student/lab.c"

int height[10];
int get_height(int i) {
    if (i == -1) {return -1;}
    else {return height[i];}
}
int get_balance(int l, int r) {
    return get_height(l) - get_height(r);
}
void set_height(int i, int l, int r) {
    int h_l = get_height(l);
    int h_r = get_height(r);
    height[i] = (h_l > h_r ? h_l : h_r) + 1;
}

int rotate_ll(int i, int l, int lr) {
    nodes[i].left = lr;
    nodes[l].right = i;
    return l;
}

int rotate_lr(int i, int l, int lr, int lrl, int lrr) {
    nodes[l].right = lrl;
    nodes[i].left = lrr;
    nodes[lr].left = l;
    nodes[lr].right = i;
    return lr;
}

int rotate_rl(int i, int r, int rl, int rll, int rlr) {
    nodes[i].right = rll;
    nodes[r].left = rlr;
    nodes[rl].left = i;
    nodes[rl].right = r;
    return rl;
}

int rotate_rr(int i, int r, int rl) {
    nodes[i].right = rl;
    nodes[r].left = i;
    return r;
}

int _add(int i, int new_node) {
    if (i == -1) {
        height[new_node] = 0;
        return new_node;
    }
    int l = nodes[i].left;
    int r = nodes[i].right;
    if (nodes[new_node].data <= nodes[i].data) {
        l = nodes[i].left = _add(l, new_node);
    } else {
        r = nodes[i].right = _add(r, new_node);
    }
    int root = i;
    int bf = get_balance(l, r);
    if (bf <= 1 && bf  >= -1) {
        set_height(i, l, r);
    } else if (bf == 2) {
        int ll = nodes[l].left;
        int lr = nodes[l].right;
        if (get_height(ll) >= get_height(lr)) {
            root = rotate_ll(i, l, lr);
            set_height(i, lr, r);
            set_height(l, ll, i);
        } else {
            int lrl = nodes[lr].left;
            int lrr = nodes[lr].right;
            root = rotate_lr(i, l, lr, lrl, lrr);
            set_height(i, lrr, r);
            set_height(l, ll, lrl);
            set_height(lr, l, i);
        }
    } else if (bf == -2) {
        int rl = nodes[r].left;
        int rr = nodes[r].right;
        if (get_height(rr) >= get_height(rl)) {
            root = rotate_rr(i, r, rl);
            set_height(i, l, rl);
            set_height(r, i, rr);
        } else {
            int rll = nodes[rl].left;
            int rlr = nodes[rl].right;
            root = rotate_rl(i, r, rl, rll, rlr);
            set_height(i, l, rll);
            set_height(r, rlr, rr);
            set_height(rl, i, r);
        }
    }
    return root;
} 