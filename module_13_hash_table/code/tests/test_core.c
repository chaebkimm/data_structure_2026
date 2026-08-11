#include "hash_table.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef HASH_TABLE_TESTING
#error "Core tests require -DHASH_TABLE_TESTING."
#endif

typedef bool (*TestFunction)(void);

typedef struct {
    HashSlot *slots_identity;
    size_t size;
    size_t tombstones;
    size_t capacity;
    HashSlot slots[HASH_TABLE_MAX_CAPACITY];
} TableSnapshot;

static HashTable *active_table = NULL;

static void track_table(HashTable *table)
{
    active_table = table;
}

static void release_table(void)
{
    if (active_table != NULL) {
        hash_table_destroy(active_table);
        active_table = NULL;
    }
}

#define REQUIRE(condition)                                                   \
    do {                                                                     \
        if (!(condition)) {                                                  \
            (void)fprintf(                                                   \
                stderr,                                                      \
                "  requirement failed at %s:%d: %s\n",                     \
                __FILE__,                                                    \
                __LINE__,                                                    \
                #condition                                                   \
            );                                                               \
            release_table();                                                 \
            return false;                                                    \
        }                                                                    \
    } while (false)

static TableSnapshot snapshot_table(const HashTable *table)
{
    TableSnapshot snapshot;

    snapshot.slots_identity = table->slots;
    snapshot.size = table->size;
    snapshot.tombstones = table->tombstones;
    snapshot.capacity = table->capacity;
    (void)memset(snapshot.slots, 0, sizeof(snapshot.slots));
    if (table->slots != NULL) {
        (void)memcpy(
            snapshot.slots,
            table->slots,
            table->capacity * sizeof(*table->slots)
        );
    }
    return snapshot;
}

static bool table_matches_snapshot(
    const HashTable *table,
    const TableSnapshot *snapshot
)
{
    return table->slots == snapshot->slots_identity &&
        table->size == snapshot->size &&
        table->tombstones == snapshot->tombstones &&
        table->capacity == snapshot->capacity &&
        (table->capacity == 0U ||
            memcmp(
                table->slots,
                snapshot->slots,
                table->capacity * sizeof(*table->slots)
            ) == 0);
}

static bool expect_put(
    HashTable *table,
    uint32_t key,
    int value,
    bool inserted,
    size_t probes
)
{
    HashTablePutResult result = {false, 0U};

    REQUIRE(hash_table_put(table, key, value, &result) == HASH_TABLE_OK);
    REQUIRE(result.inserted == inserted);
    REQUIRE(result.probe_count == probes);
    return true;
}

static bool expect_get(
    const HashTable *table,
    uint32_t key,
    bool found,
    int value,
    size_t probes
)
{
    HashTableGetResult result = {false, 0, 0U};

    REQUIRE(hash_table_get(table, key, &result) == HASH_TABLE_OK);
    REQUIRE(result.found == found);
    REQUIRE(result.value == value);
    REQUIRE(result.probe_count == probes);
    return true;
}

static bool test_initialization_key_zero_and_errors(void)
{
    HashTable table = {0};
    HashTablePutResult put_result = {true, 99U};
    HashTableGetResult get_result = {true, 77, 99U};
    HashTableRemoveResult remove_result = {true, 77, 99U};

    REQUIRE(hash_table_test_live_allocations() == 0U);
    REQUIRE(hash_table_validate(NULL) == HASH_TABLE_INVALID_ARGUMENT);
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    REQUIRE(
        hash_table_put(&table, 0U, 7, &put_result) ==
            HASH_TABLE_INVALID_STATE
    );
    REQUIRE(put_result.inserted && put_result.probe_count == 99U);
    REQUIRE(
        hash_table_get(&table, 0U, &get_result) == HASH_TABLE_INVALID_STATE
    );
    REQUIRE(get_result.found && get_result.value == 77);
    REQUIRE(
        hash_table_remove(&table, 0U, &remove_result) ==
            HASH_TABLE_INVALID_STATE
    );
    REQUIRE(remove_result.removed && remove_result.value == 77);

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);
    REQUIRE(table.capacity == 8U);
    REQUIRE(table.size == 0U && table.tombstones == 0U);
    REQUIRE(hash_table_test_live_allocations() == 1U);
    REQUIRE(hash_table_init(&table) == HASH_TABLE_INVALID_STATE);
    REQUIRE(expect_put(&table, 0U, -19, true, 1U));
    REQUIRE(expect_get(&table, 0U, true, -19, 1U));
    REQUIRE(expect_put(&table, UINT32_MAX, 314, true, 1U));
    REQUIRE(expect_get(&table, UINT32_MAX, true, 314, 1U));
    REQUIRE(
        hash_table_remove(&table, UINT32_MAX, &remove_result) == HASH_TABLE_OK
    );
    REQUIRE(remove_result.removed && remove_result.value == 314);
    REQUIRE(remove_result.probe_count == 1U);
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);

    REQUIRE(hash_table_put(NULL, 1U, 1, &put_result) ==
        HASH_TABLE_INVALID_ARGUMENT);
    REQUIRE(hash_table_put(&table, 1U, 1, NULL) ==
        HASH_TABLE_INVALID_ARGUMENT);
    REQUIRE(hash_table_get(NULL, 1U, &get_result) ==
        HASH_TABLE_INVALID_ARGUMENT);
    REQUIRE(hash_table_get(&table, 1U, NULL) ==
        HASH_TABLE_INVALID_ARGUMENT);
    REQUIRE(hash_table_remove(NULL, 1U, &remove_result) ==
        HASH_TABLE_INVALID_ARGUMENT);
    REQUIRE(hash_table_remove(&table, 1U, NULL) ==
        HASH_TABLE_INVALID_ARGUMENT);

    REQUIRE(strcmp(hash_table_status_name(HASH_TABLE_OK), "HASH_TABLE_OK") == 0);
    REQUIRE(strcmp(hash_table_status_name((HashTableStatus)99),
        "HASH_TABLE_UNKNOWN_STATUS") == 0);
    release_table();
    REQUIRE(hash_table_test_live_allocations() == 0U);
    return true;
}

static bool test_collisions_updates_and_probe_counts(void)
{
    HashTable table = {0};

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);
    REQUIRE(expect_put(&table, 10U, 100, true, 1U));
    REQUIRE(expect_put(&table, 18U, 180, true, 2U));
    REQUIRE(expect_put(&table, 26U, 260, true, 3U));
    REQUIRE(table.slots[2].key == 10U);
    REQUIRE(table.slots[3].key == 18U);
    REQUIRE(table.slots[4].key == 26U);
    REQUIRE(expect_get(&table, 10U, true, 100, 1U));
    REQUIRE(expect_get(&table, 18U, true, 180, 2U));
    REQUIRE(expect_get(&table, 26U, true, 260, 3U));
    REQUIRE(expect_get(&table, 34U, false, 0, 4U));
    REQUIRE(expect_put(&table, 18U, -18, false, 2U));
    REQUIRE(table.size == 3U && table.tombstones == 0U);
    REQUIRE(expect_get(&table, 18U, true, -18, 2U));
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    release_table();
    return true;
}

static bool test_wraparound_probe_counts(void)
{
    HashTable table = {0};

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);
    REQUIRE(expect_put(&table, 7U, 7, true, 1U));
    REQUIRE(expect_put(&table, 15U, 15, true, 2U));
    REQUIRE(expect_put(&table, 23U, 23, true, 3U));
    REQUIRE(table.slots[7].key == 7U);
    REQUIRE(table.slots[0].key == 15U);
    REQUIRE(table.slots[1].key == 23U);
    REQUIRE(expect_get(&table, 23U, true, 23, 3U));
    REQUIRE(expect_get(&table, 31U, false, 0, 4U));
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    release_table();
    return true;
}

static bool test_tombstone_reachability_reuse_and_no_duplicate(void)
{
    HashTable table = {0};
    HashTableRemoveResult removed = {false, 0, 0U};

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);
    REQUIRE(expect_put(&table, 10U, 10, true, 1U));
    REQUIRE(expect_put(&table, 18U, 18, true, 2U));
    REQUIRE(expect_put(&table, 26U, 26, true, 3U));
    REQUIRE(hash_table_remove(&table, 18U, &removed) == HASH_TABLE_OK);
    REQUIRE(removed.removed && removed.value == 18);
    REQUIRE(removed.probe_count == 2U);
    REQUIRE(table.size == 2U && table.tombstones == 1U);
    REQUIRE(table.slots[3].state == HASH_SLOT_DELETED);
    REQUIRE(table.slots[3].key == 0U && table.slots[3].value == 0);
    REQUIRE(expect_get(&table, 26U, true, 26, 3U));

    REQUIRE(expect_put(&table, 26U, 2600, false, 3U));
    REQUIRE(table.size == 2U && table.tombstones == 1U);
    REQUIRE(expect_get(&table, 26U, true, 2600, 3U));
    REQUIRE(expect_put(&table, 34U, 34, true, 4U));
    REQUIRE(table.slots[3].state == HASH_SLOT_OCCUPIED);
    REQUIRE(table.slots[3].key == 34U);
    REQUIRE(table.size == 3U && table.tombstones == 0U);
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    release_table();
    return true;
}

static bool test_growth_and_same_capacity_compaction(void)
{
    HashTable table = {0};
    HashTableRemoveResult removed;
    uint32_t key;

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);
    for (key = 0U; key < 6U; ++key) {
        REQUIRE(expect_put(&table, key, (int)key, true, 1U));
    }
    REQUIRE(table.capacity == 8U && table.size == 6U);
    REQUIRE(expect_put(&table, 6U, 6, true, 1U));
    REQUIRE(table.capacity == 16U);
    REQUIRE(table.size == 7U && table.tombstones == 0U);
    for (key = 0U; key < 7U; ++key) {
        REQUIRE(expect_get(&table, key, true, (int)key, 1U));
    }
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    release_table();

    table = (HashTable){0};
    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);
    for (key = 0U; key < 6U; ++key) {
        REQUIRE(expect_put(&table, key, (int)key, true, 1U));
    }
    for (key = 0U; key < 4U; ++key) {
        REQUIRE(hash_table_remove(&table, key, &removed) == HASH_TABLE_OK);
        REQUIRE(removed.removed && removed.probe_count == 1U);
    }
    REQUIRE(table.size == 2U && table.tombstones == 4U);
    REQUIRE(expect_put(&table, 6U, 60, true, 1U));
    REQUIRE(table.capacity == 8U);
    REQUIRE(table.size == 3U && table.tombstones == 0U);
    REQUIRE(expect_get(&table, 4U, true, 4, 1U));
    REQUIRE(expect_get(&table, 5U, true, 5, 1U));
    REQUIRE(expect_get(&table, 6U, true, 60, 1U));
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    release_table();
    return true;
}

static bool test_allocation_failure_preserves_everything(void)
{
    HashTable table = {0};
    HashTablePutResult result = {true, 987U};
    TableSnapshot snapshot;
    uint32_t key;

    REQUIRE(hash_table_test_live_allocations() == 0U);
    hash_table_test_fail_next_allocation();
    REQUIRE(hash_table_init(&table) == HASH_TABLE_ALLOCATION);
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    REQUIRE(hash_table_test_live_allocations() == 0U);

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);
    for (key = 0U; key < 6U; ++key) {
        REQUIRE(expect_put(&table, key, (int)key, true, 1U));
    }
    snapshot = snapshot_table(&table);
    hash_table_test_fail_next_allocation();
    REQUIRE(hash_table_put(&table, 6U, 6, &result) == HASH_TABLE_ALLOCATION);
    REQUIRE(result.inserted && result.probe_count == 987U);
    REQUIRE(table_matches_snapshot(&table, &snapshot));
    REQUIRE(hash_table_test_live_allocations() == 1U);
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    REQUIRE(expect_put(&table, 6U, 6, true, 1U));
    REQUIRE(table.capacity == 16U);
    REQUIRE(hash_table_test_live_allocations() == 1U);
    release_table();
    REQUIRE(hash_table_test_live_allocations() == 0U);
    return true;
}

static bool test_maximum_capacity_full_and_destroy(void)
{
    HashTable table = {0};
    HashTablePutResult result = {true, 555U};
    HashTableRemoveResult removed;
    TableSnapshot snapshot;
    uint32_t key;

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);
    for (key = 0U; key < 48U; ++key) {
        REQUIRE(hash_table_put(&table, key, (int)key, &result) == HASH_TABLE_OK);
        REQUIRE(result.inserted);
    }
    REQUIRE(table.capacity == 64U && table.size == 48U);
    REQUIRE(table.tombstones == 0U);
    snapshot = snapshot_table(&table);
    result = (HashTablePutResult){true, 555U};
    REQUIRE(hash_table_put(&table, 48U, 48, &result) == HASH_TABLE_FULL);
    REQUIRE(result.inserted && result.probe_count == 555U);
    REQUIRE(table_matches_snapshot(&table, &snapshot));
    REQUIRE(expect_put(&table, 47U, -47, false, 1U));
    REQUIRE(expect_get(&table, 47U, true, -47, 1U));

    REQUIRE(hash_table_remove(&table, 0U, &removed) == HASH_TABLE_OK);
    REQUIRE(removed.removed);
    REQUIRE(table.size == 47U && table.tombstones == 1U);
    REQUIRE(expect_put(&table, 48U, 48, true, 1U));
    REQUIRE(table.size == 48U && table.tombstones == 0U);
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);

    release_table();
    REQUIRE(table.slots == NULL && table.capacity == 0U);
    REQUIRE(table.size == 0U && table.tombstones == 0U);
    REQUIRE(hash_table_test_live_allocations() == 0U);
    hash_table_destroy(&table);
    hash_table_destroy(NULL);
    REQUIRE(hash_table_test_live_allocations() == 0U);
    return true;
}

static int run_test(TestFunction test, const char *name)
{
    bool passed = test();

    (void)printf("%s: %s\n", name, passed ? "PASS" : "FAIL");
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;

    failures += run_test(
        test_initialization_key_zero_and_errors,
        "initialization, key zero, and errors"
    );
    failures += run_test(
        test_collisions_updates_and_probe_counts,
        "collisions, updates, and probes"
    );
    failures += run_test(
        test_wraparound_probe_counts,
        "wraparound probes"
    );
    failures += run_test(
        test_tombstone_reachability_reuse_and_no_duplicate,
        "tombstone reachability, reuse, and duplicate prevention"
    );
    failures += run_test(
        test_growth_and_same_capacity_compaction,
        "growth and compaction"
    );
    failures += run_test(
        test_allocation_failure_preserves_everything,
        "allocation failure preservation"
    );
    failures += run_test(
        test_maximum_capacity_full_and_destroy,
        "maximum capacity, full, and destroy"
    );

    if (failures != 0) {
        (void)fprintf(stderr, "%d core test group(s) failed.\n", failures);
        return 1;
    }
    puts("All hash-table core tests passed.");
    return 0;
}
