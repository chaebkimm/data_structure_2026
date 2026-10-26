#include "dsu.h"

static bool dsu_has_valid_shallow_shape(const Dsu *sets)
{
    if (sets == NULL ||
        sets->element_count > (size_t)DSU_MAX_ELEMENTS ||
        sets->component_count > sets->element_count) {
        return false;
    }

    return (sets->element_count == 0U) ==
        (sets->component_count == 0U);
}

/* Supplied bounded first-pass helper: it never changes the DSU. */
static DsuStatus dsu_locate_root(
    const Dsu *sets,
    size_t element,
    size_t *out_root
)
{
    size_t current;
    size_t steps;

    if (!dsu_has_valid_shallow_shape(sets)) {
        return DSU_INVALID_STATE;
    }
    if (element >= sets->element_count) {
        return DSU_OUT_OF_RANGE;
    }

    current = element;
    for (steps = 0U; steps < sets->element_count; ++steps) {
        size_t parent = sets->parent[current];

        if (parent >= sets->element_count) {
            return DSU_INVALID_STATE;
        }
        if (parent == current) {
            if (sets->component_size[current] == 0U ||
                sets->component_size[current] > sets->element_count) {
                return DSU_INVALID_STATE;
            }
            *out_root = current;
            return DSU_OK;
        }
        if (sets->component_size[current] != 0U) {
            return DSU_INVALID_STATE;
        }

        current = parent;
    }

    return DSU_INVALID_STATE;
}

/* Supplied second-pass helper: call it only after locate_root succeeds. */
static void dsu_compress_path(Dsu *sets, size_t element, size_t root)
{
    size_t current = element;

    while (current != root) {
        size_t next = sets->parent[current];

        sets->parent[current] = root;
        current = next;
    }
}

DsuStatus dsu_init(Dsu *sets)
{
    size_t index;

    if (sets == NULL) {
        return DSU_INVALID_ARGUMENT;
    }

    sets->element_count = 0U;
    sets->component_count = 0U;
    for (index = 0U; index < (size_t)DSU_MAX_ELEMENTS; ++index) {
        sets->parent[index] = DSU_NO_ELEMENT;
        sets->component_size[index] = 0U;
    }

    return DSU_OK;
}

bool dsu_is_valid(const Dsu *sets)
{
    size_t membership[DSU_MAX_ELEMENTS] = {0U};
    size_t root_count = 0U;
    size_t index;

    if (!dsu_has_valid_shallow_shape(sets)) {
        return false;
    }

    for (index = sets->element_count;
         index < (size_t)DSU_MAX_ELEMENTS;
         ++index) {
        if (sets->parent[index] != DSU_NO_ELEMENT ||
            sets->component_size[index] != 0U) {
            return false;
        }
    }

    for (index = 0U; index < sets->element_count; ++index) {
        size_t root = DSU_NO_ELEMENT;

        if (dsu_locate_root(sets, index, &root) != DSU_OK) {
            return false;
        }
        membership[root] += 1U;
        if (sets->parent[index] == index) {
            root_count += 1U;
        } else if (sets->component_size[index] != 0U) {
            return false;
        }
    }

    if (root_count != sets->component_count) {
        return false;
    }

    for (index = 0U; index < sets->element_count; ++index) {
        if (sets->parent[index] == index) {
            if (sets->component_size[index] != membership[index]) {
                return false;
            }
        } else if (membership[index] != 0U) {
            return false;
        }
    }

    return true;
}

/*
 * TODO 2: Complete make_set and iterative two-pass find.
 *
 * make_set creates the next dense ID and commits the caller output last.
 * find first locates a valid root without mutation, then compresses the same
 * path, and finally publishes the root.
 */
DsuStatus dsu_make_set(Dsu *sets, size_t *out_element)
{
    (void)sets;
    (void)out_element;
    return DSU_INVALID_STATE;
}

DsuStatus dsu_find(
    Dsu *sets,
    size_t element,
    size_t *out_representative
)
{
    (void)sets;
    (void)element;
    (void)out_representative;
    return DSU_INVALID_STATE;
}

/* Supplied query wrapper: both paths are located before compression. */
DsuStatus dsu_connected(
    Dsu *sets,
    size_t left,
    size_t right,
    bool *out_connected
)
{
    size_t left_root = DSU_NO_ELEMENT;
    size_t right_root = DSU_NO_ELEMENT;
    DsuStatus status;

    if (out_connected == NULL || sets == NULL) {
        return DSU_INVALID_ARGUMENT;
    }

    status = dsu_locate_root(sets, left, &left_root);
    if (status != DSU_OK) {
        return status;
    }
    status = dsu_locate_root(sets, right, &right_root);
    if (status != DSU_OK) {
        return status;
    }

    dsu_compress_path(sets, left, left_root);
    dsu_compress_path(sets, right, right_root);
    *out_connected = left_root == right_root;
    return DSU_OK;
}

/*
 * TODO 3: Implement union by component size.
 *
 * Locate both roots before mutation. Already-shared roots return OK/false
 * after compression. Otherwise attach the smaller component below the
 * larger; when sizes tie, the smaller root ID wins. Update both root-size
 * slots and component_count, then commit out_merged.
 */
DsuStatus dsu_union(
    Dsu *sets,
    size_t left,
    size_t right,
    bool *out_merged
)
{
    (void)sets;
    (void)left;
    (void)right;
    (void)out_merged;
    return DSU_INVALID_STATE;
}

/* Supplied cycle wrapper. */
DsuStatus dsu_add_connection(
    Dsu *sets,
    size_t left,
    size_t right,
    bool *out_created_cycle
)
{
    bool merged;
    DsuStatus status;

    if (out_created_cycle == NULL) {
        return DSU_INVALID_ARGUMENT;
    }

    status = dsu_union(sets, left, right, &merged);
    if (status != DSU_OK) {
        return status;
    }

    *out_created_cycle = !merged;
    return DSU_OK;
}

const char *dsu_status_name(DsuStatus status)
{
    switch (status) {
        case DSU_OK:
            return "DSU_OK";
        case DSU_INVALID_ARGUMENT:
            return "DSU_INVALID_ARGUMENT";
        case DSU_OUT_OF_RANGE:
            return "DSU_OUT_OF_RANGE";
        case DSU_FULL:
            return "DSU_FULL";
        case DSU_INVALID_STATE:
            return "DSU_INVALID_STATE";
        default:
            return "DSU_UNKNOWN_STATUS";
    }
}
