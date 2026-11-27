/*
 * Left-leaning red-black tree: insert only.
 *
 * It is a 2-3 tree stored as a binary search tree. A red node shares one
 * 2-3 node with its parent:
 *   - a black node with no red child     = a 2-node (one key)
 *   - a black node with a red left child = a 3-node (two keys)
 *
 * Rules that hold after every add():
 *   1. A red node is always a left child (the tree "leans left").
 *   2. A red node never has a red child.
 *   3. Every path from the root down to an empty link passes the same
 *      number of black nodes.
 *   4. The root is black.
 * Together they keep the height at or below 2 * log2(n + 1).
 *
 * Nodes live in a fixed array and refer to each other by index instead
 * of by pointer. Index -1 means "no node".
 */

enum { CAP = 12 };              /* the most nodes the pool can hold */

struct Rbtree_Node {
    int data;                   /* the key */
    int left;                   /* index of the left child, or -1 */
    int right;                  /* index of the right child, or -1 */
    int is_red;                 /* color of the link from the parent:
                                   1 = red, 0 = black */
};

struct Rbtree_Node nodes[CAP];  /* the node pool */
int nodes_size = 0;             /* slots used so far = next free index */

/*
 * Puts key d in the next free slot and returns its index. Returns -1 if
 * the pool is full; the key is then not added.
 *
 * A new node is red: it joins the 2-3 node above it. Red adds no black
 * node to any path, so rule 3 cannot break. Rules 1 and 2 can, and
 * add_at() repairs them.
 */
int new_node(int d) {
    if (nodes_size == CAP) { return -1; }
    int i = nodes_size++;
    nodes[i].data = d;
    nodes[i].is_red = 1;
    nodes[i].left = -1;
    nodes[i].right = -1;
    return i;
}

/*
 * Is node i red? An empty link (-1) counts as black. The i != -1 test
 * comes first, so nodes[-1] is never read.
 */
int check_red(int i) {
    return i != -1 && nodes[i].is_red;
}

/*
 * Adds val to the subtree whose top is node i, and returns the index of
 * that subtree's top afterwards. A rotation can change the top, so the
 * caller must store the result back into the link it followed.
 */
int add_at(int i, int val) {
    /* Going down: a plain binary search tree insert. */
    if (i == -1) {
        return new_node(val);   /* empty link: the new red node goes here */
    }
    if (val == nodes[i].data) {
        return i;               /* already in the tree: change nothing */
    }

    int l = nodes[i].left;      /* i's children; kept current from here on */
    int r = nodes[i].right;

    if (val < nodes[i].data) {
        nodes[i].left = add_at(l, val);
        l = nodes[i].left;      /* the left subtree may have a new top */
    } else {
        nodes[i].right = add_at(r, val);
        r = nodes[i].right;     /* the right subtree may have a new top */
    }

    /*
     * Coming back up: three repairs, always in this order. Throughout,
     * i is the top of this subtree and l and r are its children, so each
     * rotation ends by moving those names to the new shape. (The lines
     * left commented out would move ll and rr as well. Nothing reads
     * them afterwards, so they are not needed.)
     */

    /*
     * 1. Rotate left: a red link leans right.
     *
     *        i                      r
     *       / \                    / \
     *      l   r (red)  =>  (red) i   rr
     *         / \                / \
     *        rl  rr             l   rl
     *
     * Same two keys in the same 2-3 node, now leaning left. r takes i's
     * color, so the node above sees no change. The !check_red(l) test
     * skips the case of two red children: step 3 handles that one
     * without rotating.
     */
    if (check_red(r) && !check_red(l)) {
        int rl = nodes[r].left;             /* the keys between i and r */
        nodes[r].left = i;                  /* i goes under r ... */
        nodes[i].right = rl;                /* ... and gets rl */
        nodes[r].is_red = nodes[i].is_red;  /* r takes i's color */
        nodes[i].is_red = 1;                /* i is r's red left child */

        /* Rename for the new shape: r is the top, the old top its left
           child. Save the old top in l before i changes. */
        /* int ll = l; */
        l = i;
        i = r;
        r = nodes[i].right;
    }

    /*
     * 2. Rotate right: two red links in a row on the left.
     *
     *              i                    l
     *             / \                 /   \
     *      (red) l   r    =>   (red) ll     i (red)
     *           / \                        / \
     *    (red) ll  lr                     lr  r
     *
     * l, the middle of the three keys, becomes the top. Both of its
     * children are now red, so step 3 always follows.
     */
    if (check_red(l)) {         /* l is red, so it exists: nodes[l] is safe */
        int ll = nodes[l].left;
        if (check_red(ll)) {
            int lr = nodes[l].right;            /* the keys between l and i */
            nodes[l].right = i;                 /* i goes under l ... */
            nodes[l].is_red = nodes[i].is_red;  /* l takes i's color */
            nodes[i].left = lr;                 /* ... and gets lr */
            nodes[i].is_red = 1;                /* i is l's red right child */

            /* Rename for the new shape: l is the top, the old top its
               right child. Save the old top in r before i changes. */
            /* int rr = r; */
            r = i;
            i = l;
            l = ll;
            /* ll = nodes[i].left; */
        }
    }

    /*
     * 3. Flip colors: both children are red. That is three keys in one
     * node, one more than a 2-3 node may hold, so split it. The children
     * turn black (two separate nodes) and i turns red (the middle key
     * moves up into the parent's node). No link changes, and the number
     * of black nodes on every path stays the same. If i turning red
     * breaks rule 1 or 2 one level up, the caller's own three checks
     * repair it.
     */
    if (check_red(l) && check_red(r)) {
        nodes[l].is_red = 0;
        nodes[r].is_red = 0;
        nodes[i].is_red = 1;
    }

    return i;
}

/*
 * Adds val to the tree and returns the root, which a rotation may have
 * changed. Start with root = -1 (an empty tree) and always call it as
 *     root = add(root, val);
 */
int add(int root, int val) {
    root = add_at(root, val);
    if (root != -1) {           /* -1: an empty tree and a full pool */
        nodes[root].is_red = 0; /* rule 4. When a flip has just turned the
                                   root red, this is the tree growing one
                                   level. */
    }
    return root;
}