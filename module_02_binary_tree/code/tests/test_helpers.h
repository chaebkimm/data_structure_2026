#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "binary_tree.h"

#include <stdio.h>
#include <string.h>

static int tests_run = 0;
static int tests_failed = 0;

#define REQUIRE(condition)                                                   \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)fprintf(stderr, "  requirement failed at %s:%d: %s\n",      \
                          __FILE__, __LINE__, #condition);                    \
            return 0;                                                        \
        }                                                                    \
    } while (0)

/* Test inputs satisfy the header's contract, including the 19-char limit. */
static inline void begin_expression(const char *expression)
{
    size = 0;
    pos = 0;
    (void)strcpy(eq, expression);
}

static inline int valid_index(int node)
{
    return size > 0 && size <= 20 && node >= 0 && node < size;
}

static inline int leaf_is(int node, char digit)
{
    return valid_index(node) && nodes[node].data == digit
        && nodes[node].left == -1 && nodes[node].right == -1;
}

/* Guard test inspection/evaluation when a student's builder is incomplete.
 * This harness check is not an additional function students must implement. */
static inline int inspect_subtree(int node, int seen[20], int *count)
{
    if (!valid_index(node) || seen[node]) return 0;
    seen[node] = 1; /* Reject cycles and shared children before recursing. */
    *count = *count + 1;

    if (nodes[node].data >= '0' && nodes[node].data <= '9') {
        return nodes[node].left == -1 && nodes[node].right == -1;
    }
    if (nodes[node].data != '+' && nodes[node].data != '*') return 0;
    return inspect_subtree(nodes[node].left, seen, count)
        && inspect_subtree(nodes[node].right, seen, count);
}

static inline int complete_tree(int root)
{
    int seen[20] = { 0 };
    int count = 0;
    return inspect_subtree(root, seen, &count) && count == size;
}

static inline void run_test(const char *name, int (*test)(void))
{
    tests_run = tests_run + 1;
    if (test()) {
        (void)printf("PASS %s\n", name);
    } else {
        tests_failed = tests_failed + 1;
        (void)printf("FAIL %s\n", name);
    }
}

static inline int finish_tests(const char *suite)
{
    (void)printf("\n%d %s test(s), %d failure(s)\n",
                 tests_run, suite, tests_failed);
    return tests_failed == 0 ? 0 : 1;
}

#endif
