/*
 * Searching sorted data three ways: linear search, binary search,
 * and a binary search tree (BST) built from the same array.
 *
 * The tree uses no pointers and no malloc. Its nodes live in a fixed
 * array (nodes[]) and refer to each other by index; -1 means "no node".
 */

enum { CAP = 12 };                    // capacity of arr[] and of the node pool

int arr[CAP] = {1, 3, 5, 7, 9, 11};   // sorted ascending; unused slots are 0
int front = 0, rear = 5;              // valid data is arr[front..rear], inclusive

/*
 * Linear search: check each element from front to rear, in order.
 * Returns the index of target in arr[], or -1 if it is not there.
 * Works on unsorted data too. Time: O(n).
 */
int linear_search(int target) {
    for (int i = front; i <= rear; i++) {
        if (arr[i] == target) { return i; }
    }
    return -1;                        // checked every element: not found
}

/*
 * Binary search: compare with the middle element and discard the half
 * that cannot contain target. Requires arr[] to be sorted ascending.
 * Returns the index of target in arr[], or -1 if it is not there.
 * Time: O(log n).
 */
int binary_search(int target) {
    int low = front;                  // if target is present, it is in arr[low..high]
    int high = rear;
    while (low <= high) {             // the range still has elements
        int mid = (low + high) / 2;   // middle index (rounds down)
        if (target == arr[mid]) {
            return mid;
        } else if (target < arr[mid]) {
            high = mid - 1;           // target can only be in the left half
        } else {
            low = mid + 1;            // target can only be in the right half
        }
    }
    return -1;                        // the range became empty: not found
}

/*
 * One tree node. left and right are indexes into nodes[], not pointers;
 * -1 means there is no child on that side.
 */
struct Tree_Node {
    int data;
    int left;
    int right;
};

struct Tree_Node nodes[CAP];          // node pool: every node of the tree lives here
int nodes_size = 0;                   // nodes used so far, which is also the next free slot

/*
 * Take the next free slot in nodes[] and fill it in.
 * Returns the new node's index, or -1 if the pool is full.
 */
int new_node(int val, int l, int r) {
    if (nodes_size == CAP) { return -1; }
    int i = nodes_size++;             // use slot i, then advance the counter
    nodes[i].data = val;
    nodes[i].left = l;
    nodes[i].right = r;
    return i;
}

/*
 * Build a balanced BST from the sorted range arr[low..high].
 * The middle element becomes the root, the elements before it form the
 * left subtree, and the elements after it form the right subtree.
 * Returns the index of the subtree's root, or -1 for an empty range.
 *
 * Children are created before their parent (post-order), so the root of
 * the whole tree is the last node created. Keep the returned index:
 *     int root = convert_bst(front, rear);
 */
int convert_bst(int low, int high) {
    if (low > high) { return -1; }         // empty range -> empty subtree
    int mid = (low + high) / 2;
    int l = convert_bst(low, mid - 1);     // values smaller than arr[mid]
    int r = convert_bst(mid + 1, high);    // values larger than arr[mid]
    return new_node(arr[mid], l, r);
}

/*
 * Search the BST whose root is node i for val.
 * Smaller values are in the left subtree and larger values in the right,
 * so each comparison moves one level down the tree.
 * Returns the index of the node holding val, or -1 if it is not there.
 * Time: O(h), where h is the height of the tree.
 */
int bst_search(int i, int val) {
    while (i != -1) {                 // stop after stepping past a leaf
        if (val == nodes[i].data) {
            return i;
        } else if (val < nodes[i].data) {
            i = nodes[i].left;
        } else {
            i = nodes[i].right;
        }
    }
    return -1;
}

/*
 * Insert val into the BST whose root is node i.
 * Returns the index of the node holding val:
 *   - the existing node, if val is already in the tree (nothing is added)
 *   - the new node, otherwise
 *   - -1, if the node pool is full
 * If the tree is empty (i == -1), the new node is the root, so the caller
 * must keep the returned index as the root.
 * Time: O(h).
 */
int bst_add(int i, int val) {
    int p = -1;                       // parent: the last node visited before i
    while (i != -1) {                 // walk down exactly as bst_search does
        if (val == nodes[i].data) {
            return i;                 // duplicate: do not insert it again
        }
        p = i;
        if (val < nodes[i].data) {
            i = nodes[i].left;
        } else {
            i = nodes[i].right;
        }
    }
    // i == -1 here: this is the empty spot, below p, where val belongs.
    // Allocating only now means a duplicate never uses up a slot.
    int node = new_node(val, -1, -1);
    if (p != -1) {                    // p == -1 means the tree was empty
        // If the pool is full, node is -1 and the link simply stays -1.
        if (val < nodes[p].data) {
            nodes[p].left = node;     // val is smaller: attach as left child
        } else {
            nodes[p].right = node;    // val is larger: attach as right child
        }
    }
    return node;
}
