#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define HASH_TABLE_MIN_CAPACITY 8U
#define HASH_TABLE_MAX_CAPACITY 64U

typedef enum {
    HASH_SLOT_EMPTY = 0,
    HASH_SLOT_OCCUPIED,
    HASH_SLOT_DELETED
} HashSlotState;

typedef struct {
    uint32_t key;
    int value;
    HashSlotState state;
} HashSlot;

/*
 * The table owns slots. Active capacities are 8, 16, 32, or 64. A
 * destroyed table is the all-zero state. Keys use key % capacity as their
 * home index and linear probing thereafter.
 */
typedef struct {
    HashSlot *slots;
    size_t size;
    size_t tombstones;
    size_t capacity;
} HashTable;

typedef enum {
    HASH_TABLE_OK = 0,
    HASH_TABLE_INVALID_ARGUMENT,
    HASH_TABLE_ALLOCATION,
    HASH_TABLE_FULL,
    HASH_TABLE_INVALID_STATE
} HashTableStatus;

typedef struct {
    bool inserted;
    size_t probe_count;
} HashTablePutResult;

typedef struct {
    bool found;
    int value;
    size_t probe_count;
} HashTableGetResult;

typedef struct {
    bool removed;
    int value;
    size_t probe_count;
} HashTableRemoveResult;

/*
 * Allocates the minimum-capacity table. The input must be all-zero. On
 * failure the table is unchanged.
 */
HashTableStatus hash_table_init(HashTable *table);

/*
 * Performs a full diagnostic scan. It checks shape and counts, canonical
 * inactive slots, the three-quarter effective-occupancy bound, duplicate
 * keys, and reachability of every occupied slot through its probe chain.
 * The canonical all-zero state is valid.
 */
HashTableStatus hash_table_validate(const HashTable *table);

/*
 * Inserts a new key/value pair or updates the existing key. Key 0 is legal.
 * A successful update reports inserted=false. probe_count is the number of
 * slots examined for this requested key. If maintenance occurs, it reports
 * the initial old-table search and excludes rehashing and replacement-table
 * placement. The result changes only on success.
 */
HashTableStatus hash_table_put(
    HashTable *table,
    uint32_t key,
    int value,
    HashTablePutResult *out_result
);

/*
 * Looks up a key. A miss is successful and reports found=false, value=0.
 * probe_count is the number of slots examined, including the terminating
 * EMPTY slot on a miss. The result changes only on success.
 */
HashTableStatus hash_table_get(
    const HashTable *table,
    uint32_t key,
    HashTableGetResult *out_result
);

/*
 * Removes a key without breaking later probe chains. A miss is successful
 * and reports removed=false, value=0. probe_count has the same meaning as
 * for lookup. The result changes only on success.
 */
HashTableStatus hash_table_remove(
    HashTable *table,
    uint32_t key,
    HashTableRemoveResult *out_result
);

/*
 * Releases owned storage and restores the all-zero state. Passing NULL is
 * harmless. A non-NULL table must be active or already all-zero.
 */
void hash_table_destroy(HashTable *table);

const char *hash_table_status_name(HashTableStatus status);

#ifdef HASH_TABLE_TESTING
/* Makes the next attempted table allocation fail once. */
void hash_table_test_fail_next_allocation(void);

/* Reports allocations currently owned by tables in this implementation. */
size_t hash_table_test_live_allocations(void);
#endif

#endif
