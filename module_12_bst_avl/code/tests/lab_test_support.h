#ifndef MODULE_12_LAB_TEST_SUPPORT_H
#define MODULE_12_LAB_TEST_SUPPORT_H

#include <assert.h>
#include <stdio.h>
#include "lab.c"

/* Driver support, not a lab.c API. Include once; do not link lab.c again. */
static unsigned lab_active_mask;

static inline void reset_lab(void)
{
    alphabet_init();
    lab_active_mask = 0;
    for (int id = 0; id < 10; ++id) height[id] = 0;
}

static inline int inspect_lab_tree(int id, unsigned *seen, int *previous,
                                   int *has_previous, int check_avl)
{
    if (id == -1) return -1;
    assert(id >= 0 && id < 10);
    unsigned bit = 1u << (unsigned)id;
    assert((lab_active_mask & bit) != 0u);
    assert((*seen & bit) == 0u); /* No cycles or shared children. */
    *seen |= bit;
    int hl = inspect_lab_tree(nodes[id].left, seen, previous,
                              has_previous, check_avl);
    if (*has_previous) assert(*previous <= nodes[id].data);
    *previous = nodes[id].data;
    *has_previous = 1;
    int hr = inspect_lab_tree(nodes[id].right, seen, previous,
                              has_previous, check_avl);
    int actual = (hl > hr ? hl : hr) + 1;
    if (check_avl) {
        assert(height[id] == actual);
        assert(hl - hr >= -1 && hl - hr <= 1);
    }
    return actual;
}

static inline int assert_lab_shape(int root, int expected_count, int check_avl)
{
    assert(expected_count >= 0 && expected_count <= 10);
    unsigned seen = 0;
    int previous = 0;
    int has_previous = 0;
    int actual = inspect_lab_tree(root, &seen, &previous, &has_previous, check_avl);
    assert(seen == lab_active_mask);
    int count = 0;
    for (unsigned mask = seen; mask != 0u; mask >>= 1) count += (int)(mask & 1u);
    assert(count == expected_count);
    return actual;
}

static inline void assert_lab_tree(int root, int expected_count)
{
    (void)assert_lab_shape(root, expected_count, 1);
}

static inline int insert_lab(int root, int id)
{
    assert(id >= 0 && id < 10);
    unsigned bit = 1u << (unsigned)id;
    assert((lab_active_mask & bit) == 0u);
    assert(nodes[id].left == -1 && nodes[id].right == -1);
    lab_active_mask |= bit;
    return _add(root, id);
}

/* Same records and duplicate policy, intentionally no AVL height maintenance. */
static inline int baseline_add(int root, int id)
{
    if (root == -1) return id;
    if (nodes[id].data <= nodes[root].data) {
        nodes[root].left = baseline_add(nodes[root].left, id);
    } else {
        nodes[root].right = baseline_add(nodes[root].right, id);
    }
    return root;
}

static inline int build_lab_order(const int *order, int count, int use_avl)
{
    assert(count >= 0 && count <= 10);
    reset_lab();
    int root = -1;
    for (int pos = 0; pos < count; ++pos) {
        int id = order[pos];
        if (use_avl) {
            root = insert_lab(root, id);
        } else {
            assert(id >= 0 && id < 10);
            unsigned bit = 1u << (unsigned)id;
            assert((lab_active_mask & bit) == 0u);
            lab_active_mask |= bit;
            root = baseline_add(root, id);
        }
        (void)assert_lab_shape(root, pos + 1, use_avl);
    }
    return root;
}

/* Count one logical key comparison per visited node, including a match.
   The terminal missing link adds no comparison. */
static inline int search_comparisons(int root, char key, int *found)
{
    int count = 0;
    *found = 0;
    while (root != -1) {
        assert(root >= 0 && root < 10);
        ++count;
        if (key == nodes[root].data) {
            *found = 1;
            break;
        }
        root = key < nodes[root].data ? nodes[root].left : nodes[root].right;
    }
    return count;
}

#endif
