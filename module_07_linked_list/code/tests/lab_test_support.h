#ifndef MODULE_07_LAB_TEST_SUPPORT_H
#define MODULE_07_LAB_TEST_SUPPORT_H
#include <stdio.h>
#include <stdlib.h>
#include "lab.c"

/* Keep checks and operations active in NDEBUG builds too. */
#define CHECK(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "%s:%d: check failed: %s\n", __FILE__, __LINE__, #condition); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

static void expect_clean_lab(void)
{
    /* First call initializes. Later calls must preserve a fully returned pool. */
    init_lnodes_pool();
    CHECK(is_empty_queue() && qhead == -1 && qtail == -1);
    int seen[CAPACITY] = {0};
    int count = 0;
    for (int node = free_head; node != -1; node = lnodes[node].next) {
        CHECK(node >= 0 && node < CAPACITY && !seen[node]);
        seen[node] = 1;
        ++count;
    }
    CHECK(count == CAPACITY);
}

static int allocate_value(int value)
{
    int node = new_lnode();
    CHECK(node != -1 && lnodes[node].next == -1);
    lnodes[node].data = value;
    return node;
}
#endif
