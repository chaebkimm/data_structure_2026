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

/*
 * Follows at most element_count links and never changes the DSU.
 */
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

/*
 * The caller first proves that this path reaches root, so this second pass
 * cannot encounter a new error.
 */
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

DsuStatus dsu_make_set(Dsu *sets, size_t *out_element)
{
    size_t new_element;

    if (out_element == NULL || sets == NULL) {
        return DSU_INVALID_ARGUMENT;
    }
    if (!dsu_has_valid_shallow_shape(sets)) {
        return DSU_INVALID_STATE;
    }
    if (sets->element_count == (size_t)DSU_MAX_ELEMENTS) {
        return DSU_FULL;
    }

    new_element = sets->element_count;
    if (sets->parent[new_element] != DSU_NO_ELEMENT ||
        sets->component_size[new_element] != 0U) {
        return DSU_INVALID_STATE;
    }

    sets->parent[new_element] = new_element;
    sets->component_size[new_element] = 1U;
    sets->element_count += 1U;
    sets->component_count += 1U;
    *out_element = new_element;
    return DSU_OK;
}

DsuStatus dsu_find(
    Dsu *sets,
    size_t element,
    size_t *out_representative
)
{
    size_t root = DSU_NO_ELEMENT;
    DsuStatus status;

    if (out_representative == NULL || sets == NULL) {
        return DSU_INVALID_ARGUMENT;
    }

    status = dsu_locate_root(sets, element, &root);
    if (status != DSU_OK) {
        return status;
    }

    dsu_compress_path(sets, element, root);
    *out_representative = root;
    return DSU_OK;
}

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

DsuStatus dsu_union(
    Dsu *sets,
    size_t left,
    size_t right,
    bool *out_merged
)
{
    size_t left_root = DSU_NO_ELEMENT;
    size_t right_root = DSU_NO_ELEMENT;
    size_t left_size;
    size_t right_size;
    size_t winner;
    size_t loser;
    DsuStatus status;

    if (out_merged == NULL || sets == NULL) {
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

    if (left_root == right_root) {
        dsu_compress_path(sets, left, left_root);
        dsu_compress_path(sets, right, right_root);
        *out_merged = false;
        return DSU_OK;
    }
    if (sets->component_count < 2U) {
        return DSU_INVALID_STATE;
    }

    left_size = sets->component_size[left_root];
    right_size = sets->component_size[right_root];
    if (left_size == 0U || right_size == 0U ||
        left_size > sets->element_count ||
        right_size > sets->element_count ||
        left_size > sets->element_count - right_size) {
        return DSU_INVALID_STATE;
    }

    dsu_compress_path(sets, left, left_root);
    dsu_compress_path(sets, right, right_root);

    if (left_size > right_size) {
        winner = left_root;
        loser = right_root;
    } else if (right_size > left_size) {
        winner = right_root;
        loser = left_root;
    } else if (left_root < right_root) {
        winner = left_root;
        loser = right_root;
    } else {
        winner = right_root;
        loser = left_root;
    }

    sets->parent[loser] = winner;
    sets->component_size[winner] =
        sets->component_size[winner] + sets->component_size[loser];
    sets->component_size[loser] = 0U;
    sets->component_count -= 1U;
    *out_merged = true;
    return DSU_OK;
}

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
