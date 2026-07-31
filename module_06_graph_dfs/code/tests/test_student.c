#include "graph_dfs.h"

#include <stdbool.h>
#include <stdio.h>

typedef bool (*TestFunction)(void);

/*
 * Replace each placeholder with a test you designed. A test is a small
 * experiment that compares an observed result with an expected result.
 */
static bool test_traversal_or_reachability(void)
{
    /*
     * TODO: Build a graph with a cycle or disconnected vertex. Check one
     * exact order or reachable set, including that no vertex repeats.
     */
    return false;
}

static bool test_failure_preservation(void)
{
    /*
     * TODO: Prepare a marked output, cause an invalid-source or Stack-limit
     * failure, and prove that every part of the output stayed unchanged.
     */
    return false;
}

static bool test_component_count(void)
{
    /*
     * TODO: Count components in an undirected graph that contains an
     * isolated vertex, or check the empty undirected graph.
     */
    return false;
}

static int run_test(const char *name, TestFunction test)
{
    bool passed = test();

    if (passed) {
        printf("PASS %s\n", name);
    } else {
        printf("FAIL %s\n", name);
    }
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;

    failures += run_test(
        "student traversal/reachability test",
        test_traversal_or_reachability
    );
    failures += run_test(
        "student failure-preservation test",
        test_failure_preservation
    );
    failures += run_test(
        "student component-count test",
        test_component_count
    );
    return failures == 0 ? 0 : 1;
}
