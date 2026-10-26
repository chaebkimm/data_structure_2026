/* Reuse Module 7's value-based linked queue for tree-node IDs.
 * Before an independent run, initialize the unowned pool and set head=tail=-1.
 * A valid nonempty tree has no cycles/shared child and at most ten nodes.
 * order has ten slots; root -1 denotes an empty tree.
 */
#include <assert.h>
#include "module_02_binary_tree/student/lab.c"
#include "queue.c"

int tree_bfs(int root, int order[10]) {
    int count = 0;
    if (root == -1) return 0;
    bool added = enqueue(root);
    assert(added);
    (void)added;
    while (!is_empty_queue()) {
        int cur = dequeue(); /* Returns the ID and recycles its queue node. */
        order[count++] = cur;
        if (nodes[cur].left != -1) {
            added = enqueue(nodes[cur].left);
            assert(added);
        }
        if (nodes[cur].right != -1) {
            added = enqueue(nodes[cur].right);
            assert(added);
        }
    }
    return count;
}
