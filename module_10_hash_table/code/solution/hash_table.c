#include "hash_table.h"

#include <stdlib.h>

typedef struct {
    bool valid;
    bool found;
    size_t found_index;
    size_t insertion_index;
    size_t probe_count;
} ProbeResult;

#ifdef HASH_TABLE_TESTING
static bool fail_next_allocation = false;
static size_t live_allocations = 0U;
#endif

static bool is_zero_table(const HashTable *table)
{
    return table->slots == NULL && table->size == 0U &&
        table->tombstones == 0U && table->capacity == 0U;
}

static bool is_supported_capacity(size_t capacity)
{
    return capacity == 8U || capacity == 16U || capacity == 32U ||
        capacity == 64U;
}

static size_t occupancy_limit(size_t capacity)
{
    return (capacity / 4U) * 3U;
}

static bool has_valid_active_shape(const HashTable *table)
{
    return table->slots != NULL && is_supported_capacity(table->capacity) &&
        table->size <= table->capacity &&
        table->tombstones <= table->capacity - table->size &&
        table->size + table->tombstones <=
            occupancy_limit(table->capacity);
}

static HashSlot *allocate_slots(size_t capacity)
{
    HashSlot *slots;

#ifdef HASH_TABLE_TESTING
    if (fail_next_allocation) {
        fail_next_allocation = false;
        return NULL;
    }
#endif

    slots = calloc(capacity, sizeof(*slots));
#ifdef HASH_TABLE_TESTING
    if (slots != NULL) {
        live_allocations += 1U;
    }
#endif
    return slots;
}

static void release_slots(HashSlot *slots)
{
    if (slots == NULL) {
        return;
    }

    free(slots);
#ifdef HASH_TABLE_TESTING
    if (live_allocations > 0U) {
        live_allocations -= 1U;
    }
#endif
}

static ProbeResult probe_for_key(const HashTable *table, uint32_t key)
{
    ProbeResult result = {true, false, 0U, SIZE_MAX, 0U};
    size_t first_deleted = SIZE_MAX;
    size_t home = (size_t)key % table->capacity;
    size_t step;

    for (step = 0U; step < table->capacity; ++step) {
        size_t index = (home + step) % table->capacity;
        const HashSlot *slot = &table->slots[index];

        result.probe_count += 1U;
        if (slot->state == HASH_SLOT_OCCUPIED && slot->key == key) {
            result.found = true;
            result.found_index = index;
            return result;
        }
        if (slot->state == HASH_SLOT_DELETED && first_deleted == SIZE_MAX) {
            first_deleted = index;
        }
        if (slot->state == HASH_SLOT_EMPTY) {
            result.insertion_index = first_deleted == SIZE_MAX
                ? index
                : first_deleted;
            return result;
        }
        if (slot->state != HASH_SLOT_OCCUPIED &&
            slot->state != HASH_SLOT_DELETED) {
            result.valid = false;
            return result;
        }
    }

    result.insertion_index = first_deleted;
    return result;
}

static bool raw_insert(
    HashSlot *slots,
    size_t capacity,
    uint32_t key,
    int value
)
{
    size_t home = (size_t)key % capacity;
    size_t step;

    for (step = 0U; step < capacity; ++step) {
        size_t index = (home + step) % capacity;

        if (slots[index].state == HASH_SLOT_EMPTY) {
            slots[index].key = key;
            slots[index].value = value;
            slots[index].state = HASH_SLOT_OCCUPIED;
            return true;
        }
    }
    return false;
}

static HashTableStatus rebuild_with_entry(
    HashTable *table,
    size_t new_capacity,
    uint32_t key,
    int value
)
{
    HashSlot *new_slots = allocate_slots(new_capacity);
    HashSlot *old_slots;
    size_t index;

    if (new_slots == NULL) {
        return HASH_TABLE_ALLOCATION;
    }

    for (index = 0U; index < table->capacity; ++index) {
        const HashSlot *slot = &table->slots[index];

        if (slot->state == HASH_SLOT_OCCUPIED &&
            !raw_insert(new_slots, new_capacity, slot->key, slot->value)) {
            release_slots(new_slots);
            return HASH_TABLE_INVALID_STATE;
        }
    }
    if (!raw_insert(new_slots, new_capacity, key, value)) {
        release_slots(new_slots);
        return HASH_TABLE_INVALID_STATE;
    }

    old_slots = table->slots;
    table->slots = new_slots;
    table->size += 1U;
    table->tombstones = 0U;
    table->capacity = new_capacity;
    release_slots(old_slots);
    return HASH_TABLE_OK;
}

static HashTableStatus commit_put(
    HashTable *table,
    uint32_t key,
    int value,
    const ProbeResult *probe,
    HashTablePutResult *out_result
)
{
    HashTablePutResult result = {false, probe->probe_count};
    HashSlot *target;
    size_t effective_occupancy;

    if (probe->found) {
        table->slots[probe->found_index].value = value;
        *out_result = result;
        return HASH_TABLE_OK;
    }
    if (probe->insertion_index == SIZE_MAX) {
        return HASH_TABLE_INVALID_STATE;
    }

    target = &table->slots[probe->insertion_index];
    effective_occupancy = table->size + table->tombstones;
    if (target->state == HASH_SLOT_EMPTY &&
        effective_occupancy + 1U > occupancy_limit(table->capacity)) {
        HashTableStatus status;
        size_t new_capacity;

        if (table->tombstones > 0U) {
            new_capacity = table->capacity;
        } else if (table->capacity < HASH_TABLE_MAX_CAPACITY) {
            new_capacity = table->capacity * 2U;
        } else {
            return HASH_TABLE_FULL;
        }

        status = rebuild_with_entry(table, new_capacity, key, value);
        if (status != HASH_TABLE_OK) {
            return status;
        }
        result.inserted = true;
        *out_result = result;
        return HASH_TABLE_OK;
    }

    if (target->state == HASH_SLOT_DELETED) {
        table->tombstones -= 1U;
    }
    target->key = key;
    target->value = value;
    target->state = HASH_SLOT_OCCUPIED;
    table->size += 1U;

    result.inserted = true;
    *out_result = result;
    return HASH_TABLE_OK;
}

static HashTableStatus commit_remove(
    HashTable *table,
    const ProbeResult *probe,
    HashTableRemoveResult *out_result
)
{
    HashTableRemoveResult result;

    result.removed = probe->found;
    result.value = probe->found
        ? table->slots[probe->found_index].value
        : 0;
    result.probe_count = probe->probe_count;

    if (probe->found) {
        HashSlot *slot = &table->slots[probe->found_index];

        slot->key = 0U;
        slot->value = 0;
        slot->state = HASH_SLOT_DELETED;
        table->size -= 1U;
        table->tombstones += 1U;
    }

    *out_result = result;
    return HASH_TABLE_OK;
}

HashTableStatus hash_table_init(HashTable *table)
{
    HashSlot *slots;

    if (table == NULL) {
        return HASH_TABLE_INVALID_ARGUMENT;
    }
    if (!is_zero_table(table)) {
        return HASH_TABLE_INVALID_STATE;
    }

    slots = allocate_slots(HASH_TABLE_MIN_CAPACITY);
    if (slots == NULL) {
        return HASH_TABLE_ALLOCATION;
    }

    table->slots = slots;
    table->capacity = HASH_TABLE_MIN_CAPACITY;
    return HASH_TABLE_OK;
}

HashTableStatus hash_table_validate(const HashTable *table)
{
    size_t occupied_count = 0U;
    size_t deleted_count = 0U;
    size_t index;

    if (table == NULL) {
        return HASH_TABLE_INVALID_ARGUMENT;
    }
    if (is_zero_table(table)) {
        return HASH_TABLE_OK;
    }
    if (table->slots == NULL || !is_supported_capacity(table->capacity)) {
        return HASH_TABLE_INVALID_STATE;
    }
    if (table->size > table->capacity ||
        table->tombstones > table->capacity - table->size ||
        table->size + table->tombstones >
            occupancy_limit(table->capacity)) {
        return HASH_TABLE_INVALID_STATE;
    }

    for (index = 0U; index < table->capacity; ++index) {
        const HashSlot *slot = &table->slots[index];

        if (slot->state == HASH_SLOT_OCCUPIED) {
            occupied_count += 1U;
        } else if (slot->state == HASH_SLOT_DELETED) {
            if (slot->key != 0U || slot->value != 0) {
                return HASH_TABLE_INVALID_STATE;
            }
            deleted_count += 1U;
        } else if (slot->state == HASH_SLOT_EMPTY) {
            if (slot->key != 0U || slot->value != 0) {
                return HASH_TABLE_INVALID_STATE;
            }
        } else {
            return HASH_TABLE_INVALID_STATE;
        }
    }
    if (occupied_count != table->size ||
        deleted_count != table->tombstones) {
        return HASH_TABLE_INVALID_STATE;
    }

    for (index = 0U; index < table->capacity; ++index) {
        const HashSlot *slot = &table->slots[index];
        size_t other;
        size_t step;
        size_t home;
        bool reachable = false;

        if (slot->state != HASH_SLOT_OCCUPIED) {
            continue;
        }

        for (other = index + 1U; other < table->capacity; ++other) {
            if (table->slots[other].state == HASH_SLOT_OCCUPIED &&
                table->slots[other].key == slot->key) {
                return HASH_TABLE_INVALID_STATE;
            }
        }

        home = (size_t)slot->key % table->capacity;
        for (step = 0U; step < table->capacity; ++step) {
            size_t probe_index = (home + step) % table->capacity;

            if (table->slots[probe_index].state == HASH_SLOT_EMPTY) {
                break;
            }
            if (probe_index == index) {
                reachable = true;
                break;
            }
        }
        if (!reachable) {
            return HASH_TABLE_INVALID_STATE;
        }
    }

    return HASH_TABLE_OK;
}

HashTableStatus hash_table_put(
    HashTable *table,
    uint32_t key,
    int value,
    HashTablePutResult *out_result
)
{
    ProbeResult probe;

    if (table == NULL || out_result == NULL) {
        return HASH_TABLE_INVALID_ARGUMENT;
    }
    if (!has_valid_active_shape(table)) {
        return HASH_TABLE_INVALID_STATE;
    }

    probe = probe_for_key(table, key);
    if (!probe.valid) {
        return HASH_TABLE_INVALID_STATE;
    }
    return commit_put(table, key, value, &probe, out_result);
}

HashTableStatus hash_table_get(
    const HashTable *table,
    uint32_t key,
    HashTableGetResult *out_result
)
{
    ProbeResult probe;
    HashTableGetResult result;

    if (table == NULL || out_result == NULL) {
        return HASH_TABLE_INVALID_ARGUMENT;
    }
    if (!has_valid_active_shape(table)) {
        return HASH_TABLE_INVALID_STATE;
    }

    probe = probe_for_key(table, key);
    if (!probe.valid) {
        return HASH_TABLE_INVALID_STATE;
    }
    result.found = probe.found;
    result.value = probe.found ? table->slots[probe.found_index].value : 0;
    result.probe_count = probe.probe_count;
    *out_result = result;
    return HASH_TABLE_OK;
}

HashTableStatus hash_table_remove(
    HashTable *table,
    uint32_t key,
    HashTableRemoveResult *out_result
)
{
    ProbeResult probe;

    if (table == NULL || out_result == NULL) {
        return HASH_TABLE_INVALID_ARGUMENT;
    }
    if (!has_valid_active_shape(table)) {
        return HASH_TABLE_INVALID_STATE;
    }

    probe = probe_for_key(table, key);
    if (!probe.valid) {
        return HASH_TABLE_INVALID_STATE;
    }
    return commit_remove(table, &probe, out_result);
}

void hash_table_destroy(HashTable *table)
{
    if (table == NULL) {
        return;
    }

    release_slots(table->slots);
    table->slots = NULL;
    table->size = 0U;
    table->tombstones = 0U;
    table->capacity = 0U;
}

const char *hash_table_status_name(HashTableStatus status)
{
    switch (status) {
        case HASH_TABLE_OK:
            return "HASH_TABLE_OK";
        case HASH_TABLE_INVALID_ARGUMENT:
            return "HASH_TABLE_INVALID_ARGUMENT";
        case HASH_TABLE_ALLOCATION:
            return "HASH_TABLE_ALLOCATION";
        case HASH_TABLE_FULL:
            return "HASH_TABLE_FULL";
        case HASH_TABLE_INVALID_STATE:
            return "HASH_TABLE_INVALID_STATE";
        default:
            return "HASH_TABLE_UNKNOWN_STATUS";
    }
}

#ifdef HASH_TABLE_TESTING
void hash_table_test_fail_next_allocation(void)
{
    fail_next_allocation = true;
}

size_t hash_table_test_live_allocations(void)
{
    return live_allocations;
}
#endif
