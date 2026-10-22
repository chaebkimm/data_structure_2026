#include "dsu.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    Dsu sets;
    Dsu before;
    bool merged = false;
    size_t root = DSU_NO_ELEMENT;
    const size_t pairs[][2] = {{0,1},{2,3},{0,2},{4,5},{6,7},{4,6},{0,4}};
    assert(dsu_init(&sets) == DSU_OK);
    for (size_t i = 0; i < 8; ++i) {
        size_t id = DSU_NO_ELEMENT;
        assert(dsu_make_set(&sets, &id) == DSU_OK && id == i);
    }
    for (size_t i = 0; i < 7; ++i) {
        assert(dsu_union(&sets, pairs[i][0], pairs[i][1], &merged) == DSU_OK);
        assert(merged && dsu_is_valid(&sets));
    }
    assert(sets.parent[7] == 6 && sets.parent[6] == 4 && sets.parent[4] == 0);
    assert(dsu_find(&sets, 7, &root) == DSU_OK && root == 0);
    assert(sets.parent[7] == 0 && sets.parent[6] == 0);
    assert(sets.component_count == 1 && sets.component_size[0] == 8);
    assert(dsu_union(&sets, 3, 7, &merged) == DSU_OK && !merged);
    assert(dsu_is_valid(&sets));
    memcpy(&before, &sets, sizeof sets);
    root = 99;
    assert(dsu_find(&sets, 8, &root) == DSU_OUT_OF_RANGE && root == 99);
    assert(memcmp(&before, &sets, sizeof sets) == 0);
    merged = true;
    assert(dsu_union(&sets, 7, 8, &merged) == DSU_OUT_OF_RANGE && merged);
    assert(memcmp(&before, &sets, sizeof sets) == 0);
    assert(dsu_find(&sets, 0, NULL) == DSU_INVALID_ARGUMENT);
    assert(dsu_union(&sets, 0, 1, NULL) == DSU_INVALID_ARGUMENT);
    assert(dsu_is_valid(&sets));
    puts("Week 13 DSU core tests passed");
    return 0;
}
