#include "hash_table.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef HASH_TABLE_TESTING
#error "Extension tests require -DHASH_TABLE_TESTING."
#endif

#define REFERENCE_KEY_COUNT 80U
#define CHURN_STEPS 4000U

typedef bool (*TestFunction)(void);

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

static uint32_t next_random(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static bool test_deterministic_differential_churn(void)
{
    HashTable table = {0};
    bool present[REFERENCE_KEY_COUNT] = {false};
    int values[REFERENCE_KEY_COUNT] = {0};
    size_t reference_size = 0U;
    uint32_t random_state = UINT32_C(0xC0FFEE12);
    size_t step;

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);

    for (step = 0U; step < CHURN_STEPS; ++step) {
        uint32_t random_value = next_random(&random_state);
        uint32_t key = (random_value >> 8U) % REFERENCE_KEY_COUNT;
        unsigned int operation = (unsigned int)(random_value % 5U);
        int value = (int)(next_random(&random_state) & UINT32_C(0x7fff)) -
            16000;

        if (operation <= 1U) {
            HashTablePutResult result = {true, 999U};
            HashTableStatus status = hash_table_put(
                &table,
                key,
                value,
                &result
            );

            if (present[key]) {
                REQUIRE(status == HASH_TABLE_OK);
                REQUIRE(!result.inserted);
                values[key] = value;
            } else if (reference_size < 48U) {
                REQUIRE(status == HASH_TABLE_OK);
                REQUIRE(result.inserted);
                present[key] = true;
                values[key] = value;
                reference_size += 1U;
            } else {
                REQUIRE(status == HASH_TABLE_FULL);
                REQUIRE(result.inserted && result.probe_count == 999U);
            }
            if (status == HASH_TABLE_OK) {
                REQUIRE(result.probe_count >= 1U);
                REQUIRE(result.probe_count <= table.capacity);
            }
        } else if (operation <= 3U) {
            HashTableGetResult result = {true, 999, 999U};

            REQUIRE(hash_table_get(&table, key, &result) == HASH_TABLE_OK);
            REQUIRE(result.found == present[key]);
            REQUIRE(result.value == (present[key] ? values[key] : 0));
            REQUIRE(result.probe_count >= 1U);
            REQUIRE(result.probe_count <= table.capacity);
        } else {
            HashTableRemoveResult result = {true, 999, 999U};
            bool was_present = present[key];
            int old_value = values[key];

            REQUIRE(hash_table_remove(&table, key, &result) == HASH_TABLE_OK);
            REQUIRE(result.removed == was_present);
            REQUIRE(result.value == (was_present ? old_value : 0));
            REQUIRE(result.probe_count >= 1U);
            REQUIRE(result.probe_count <= table.capacity);
            if (was_present) {
                present[key] = false;
                reference_size -= 1U;
            }
        }

        REQUIRE(table.size == reference_size);
        REQUIRE(table.size + table.tombstones <=
            (table.capacity / 4U) * 3U);
        if (step % 29U == 0U) {
            REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
        }
    }

    for (step = 0U; step < REFERENCE_KEY_COUNT; ++step) {
        HashTableGetResult result;

        REQUIRE(hash_table_get(&table, (uint32_t)step, &result) ==
            HASH_TABLE_OK);
        REQUIRE(result.found == present[step]);
        REQUIRE(result.value == (present[step] ? values[step] : 0));
    }
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    release_table();
    REQUIRE(hash_table_test_live_allocations() == 0U);
    return true;
}

static bool test_diagnostic_corruption_detection(void)
{
    HashTable table = {0};
    HashTablePutResult put_result;
    HashSlot saved_slot;
    size_t saved_count;
    size_t saved_capacity;

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);
    REQUIRE(hash_table_put(&table, 10U, 10, &put_result) == HASH_TABLE_OK);
    REQUIRE(hash_table_put(&table, 18U, 18, &put_result) == HASH_TABLE_OK);
    REQUIRE(hash_table_put(&table, 26U, 26, &put_result) == HASH_TABLE_OK);
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);

    saved_count = table.size;
    table.size += 1U;
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_INVALID_STATE);
    table.size = saved_count;

    saved_slot = table.slots[7];
    table.slots[7].key = 77U;
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_INVALID_STATE);
    table.slots[7] = saved_slot;

    saved_slot = table.slots[7];
    table.slots[7].state = (HashSlotState)99;
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_INVALID_STATE);
    table.slots[7] = saved_slot;

    saved_slot = table.slots[3];
    table.slots[3].key = 10U;
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_INVALID_STATE);
    table.slots[3] = saved_slot;

    saved_slot = table.slots[2];
    table.slots[2] = (HashSlot){0U, 0, HASH_SLOT_EMPTY};
    table.size -= 1U;
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_INVALID_STATE);
    table.slots[2] = saved_slot;
    table.size += 1U;

    saved_count = table.tombstones;
    table.tombstones = 4U;
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_INVALID_STATE);
    table.tombstones = saved_count;

    saved_capacity = table.capacity;
    table.capacity = 12U;
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_INVALID_STATE);
    table.capacity = saved_capacity;
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    release_table();
    return true;
}

static bool test_normal_operations_do_not_run_full_diagnostic(void)
{
    HashTable table = {0};
    HashTableGetResult get_result = {true, 123, 123U};
    HashSlot saved_slot;

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);

    saved_slot = table.slots[7];
    table.slots[7].key = 99U;
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_INVALID_STATE);
    REQUIRE(hash_table_get(&table, 0U, &get_result) == HASH_TABLE_OK);
    REQUIRE(!get_result.found && get_result.value == 0);
    REQUIRE(get_result.probe_count == 1U);
    table.slots[7] = saved_slot;

    saved_slot = table.slots[0];
    table.slots[0].state = (HashSlotState)99;
    get_result = (HashTableGetResult){true, 123, 123U};
    REQUIRE(hash_table_get(&table, 0U, &get_result) ==
        HASH_TABLE_INVALID_STATE);
    REQUIRE(get_result.found && get_result.value == 123);
    REQUIRE(get_result.probe_count == 123U);
    table.slots[0] = saved_slot;

    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    release_table();
    return true;
}

static bool test_compaction_allocation_failure_is_transactional(void)
{
    HashTable table = {0};
    HashTableRemoveResult remove_result;
    HashTablePutResult put_result = {false, 444U};
    HashSlot *saved_slots;
    HashSlot saved_copy[HASH_TABLE_MIN_CAPACITY];
    size_t key;

    REQUIRE(hash_table_init(&table) == HASH_TABLE_OK);
    track_table(&table);
    for (key = 0U; key < 6U; ++key) {
        REQUIRE(hash_table_put(
            &table,
            (uint32_t)key,
            (int)key,
            &put_result
        ) == HASH_TABLE_OK);
    }
    for (key = 0U; key < 4U; ++key) {
        REQUIRE(hash_table_remove(&table, (uint32_t)key, &remove_result) ==
            HASH_TABLE_OK);
    }
    saved_slots = table.slots;
    for (key = 0U; key < table.capacity; ++key) {
        saved_copy[key] = table.slots[key];
    }

    put_result = (HashTablePutResult){false, 444U};
    hash_table_test_fail_next_allocation();
    REQUIRE(hash_table_put(&table, 6U, 6, &put_result) ==
        HASH_TABLE_ALLOCATION);
    REQUIRE(!put_result.inserted && put_result.probe_count == 444U);
    REQUIRE(table.slots == saved_slots);
    REQUIRE(table.size == 2U && table.tombstones == 4U);
    for (key = 0U; key < table.capacity; ++key) {
        REQUIRE(table.slots[key].key == saved_copy[key].key);
        REQUIRE(table.slots[key].value == saved_copy[key].value);
        REQUIRE(table.slots[key].state == saved_copy[key].state);
    }
    REQUIRE(hash_table_validate(&table) == HASH_TABLE_OK);
    release_table();
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
        test_deterministic_differential_churn,
        "deterministic differential churn"
    );
    failures += run_test(
        test_diagnostic_corruption_detection,
        "diagnostic corruption detection"
    );
    failures += run_test(
        test_normal_operations_do_not_run_full_diagnostic,
        "normal-operation shallow validation"
    );
    failures += run_test(
        test_compaction_allocation_failure_is_transactional,
        "transactional compaction failure"
    );

    if (failures != 0) {
        (void)fprintf(stderr, "%d extension test group(s) failed.\n", failures);
        return 1;
    }
    puts("All hash-table extension tests passed.");
    return 0;
}
