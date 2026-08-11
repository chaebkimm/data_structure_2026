#ifndef DSU_H
#define DSU_H

#include <stdbool.h>
#include <stddef.h>

#define DSU_MAX_ELEMENTS 16U
#define DSU_NO_ELEMENT ((size_t)DSU_MAX_ELEMENTS)

/*
 * A Disjoint-Set Union (DSU) stores a forest in parent[]. A root is its own
 * parent. component_size is positive only at roots and zero at nonroots.
 * Slots at element_count through 15 use DSU_NO_ELEMENT and size zero.
 */
typedef struct {
    size_t element_count;
    size_t component_count;
    size_t parent[DSU_MAX_ELEMENTS];
    size_t component_size[DSU_MAX_ELEMENTS];
} Dsu;

typedef enum {
    DSU_OK = 0,
    DSU_INVALID_ARGUMENT,
    DSU_OUT_OF_RANGE,
    DSU_FULL,
    DSU_INVALID_STATE
} DsuStatus;

DsuStatus dsu_init(Dsu *sets);
bool dsu_is_valid(const Dsu *sets);
DsuStatus dsu_make_set(Dsu *sets, size_t *out_element);
DsuStatus dsu_find(
    Dsu *sets,
    size_t element,
    size_t *out_representative
);
DsuStatus dsu_connected(
    Dsu *sets,
    size_t left,
    size_t right,
    bool *out_connected
);
DsuStatus dsu_union(
    Dsu *sets,
    size_t left,
    size_t right,
    bool *out_merged
);
DsuStatus dsu_add_connection(
    Dsu *sets,
    size_t left,
    size_t right,
    bool *out_created_cycle
);
const char *dsu_status_name(DsuStatus status);

#endif
