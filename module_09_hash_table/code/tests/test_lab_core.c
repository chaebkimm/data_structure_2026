#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "../../student/lab.c"

/* Every allocated slot is reachable once, in its key's bucket. This also
   detects invalid links, cycles, shared nodes, and unpublished allocations. */
static int check_table(void)
{
    int seen[NODES_CAPACITY] = {0};
    int count = 0;
    assert(hnodes_unused >= 0 && hnodes_unused <= NODES_CAPACITY);
    for (int bucket = 0; bucket < TABLE_CAPACITY; ++bucket) {
        int node = hashtable[bucket];
        while (node != -1) {
            assert(node >= 0 && node < hnodes_unused);
            assert(!seen[node]);
            seen[node] = 1;
            ++count;
            assert(hash_func(hnodes[node].key) == bucket);
            node = hnodes[node].next;
        }
    }
    assert(count == hnodes_unused);
    return count;
}

static void assert_nodes_equal(const struct hnode *before)
{
    for (int i = 0; i < NODES_CAPACITY; ++i) {
        assert(hnodes[i].key == before[i].key);
        assert(hnodes[i].data == before[i].data);
        assert(hnodes[i].next == before[i].next);
    }
}

static void test_hash_and_chains(void)
{
    assert(NODES_CAPACITY == 10 && TABLE_CAPACITY == 15);
    assert(NUMS_SIZE == NODES_CAPACITY);
    assert(hash_func(INT_MIN) >= 0 && hash_func(INT_MIN) < TABLE_CAPACITY);
    assert(hash_func(INT_MAX) == INT_MAX % TABLE_CAPACITY);
    assert(hash_func(INT_MIN) == (INT_MIN % TABLE_CAPACITY + TABLE_CAPACITY)
                                   % TABLE_CAPACITY);
    assert(hash_func(-16) == 14 && hash_func(-1) == 14);
    assert(hash_func(0) == 0 && hash_func(-15) == 0);
    assert(hash_func(12) == 12 && hash_func(27) == 12);
    assert(hash_func(-3) == 12);

    initialize(); /* Globals alone do not set the bucket heads to -1. */
    assert(check_table() == 0);
    assert(find(12) == -1);
    assert(insert(12, 50) == 0);
    assert(insert(27, 60) == 0);
    assert(insert(-3, 70) == 0);
    assert(hashtable[12] == 2 && hnodes_unused == 3);
    assert(hnodes[2].next == 1 && hnodes[1].next == 0);
    assert(hnodes[0].next == -1);
    assert(find(-3) == 2 && find(27) == 1 && find(12) == 0);
    assert(find(42) == -1); /* Same bucket does not imply equal key. */
    assert(find(50) == -1); /* Lookup compares keys, not payloads. */
    assert(insert(27, 99) == 0); /* Duplicate keys prepend, not update. */
    assert(find(27) == 3 && hnodes[3].data == 99);
    assert(hnodes[3].next == 2 && hnodes[1].data == 60);
    assert(check_table() == 4);
    puts("1. Signed hashing, key lookup, and collision chains passed.");
}

static void test_capacity_and_reset(void)
{
    struct hnode before[NODES_CAPACITY];
    memcpy(before, hnodes, sizeof before);
    answer[0] = 3;
    answer[1] = 7;
    initialize();
    assert_nodes_equal(before); /* Reset makes old records unreachable. */
    assert(answer[0] == 3 && answer[1] == 7);
    assert(check_table() == 0);
    initialize();
    assert(check_table() == 0);

    for (int i = 0; i < NODES_CAPACITY; ++i) {
        assert(insert(i * TABLE_CAPACITY, i + 100) == 0);
        assert(hnodes_unused == i + 1);
        assert(hashtable[0] == i);
    }
    assert(check_table() == NODES_CAPACITY);
    int heads[TABLE_CAPACITY];
    memcpy(heads, hashtable, sizeof heads);
    memcpy(before, hnodes, sizeof before);
    assert(insert(1, 7) == -1); /* Empty bucket does not provide a node. */
    assert(insert(0, 999) == -1); /* A duplicate also needs a new slot. */
    assert(new_hnode(9, 9, -1) == -1);
    assert(hnodes_unused == NODES_CAPACITY);
    assert(memcmp(heads, hashtable, sizeof heads) == 0);
    assert_nodes_equal(before);
    assert(find(0) == 0 && hnodes[0].data == 100);

    initialize();
    assert_nodes_equal(before);
    assert(check_table() == 0);
    assert(insert(1, 17) == 0);
    assert(find(1) == 0 && hnodes_unused == 1);
    assert(hnodes[0].data == 17 && hnodes[0].next == -1);
    assert(check_table() == 1);

    /* Direct allocation returns an index and stores all three arguments.
       It does not publish a bucket head; insert performs that step. */
    initialize();
    assert(new_hnode(7, 91, -1) == 0);
    assert(hnodes[0].key == 7 && hnodes[0].data == 91);
    assert(hnodes[0].next == -1 && hnodes_unused == 1);
    assert(hashtable[hash_func(7)] == -1);
    initialize();
    assert(check_table() == 0);
    puts("2. Capacity, failure preservation, reset, and reuse passed.");
}

/* An independent exhaustive oracle chooses the earliest finishing position,
   then the greatest matching earlier position, as required by the lab. */
static void expected_pair(int target, int result[2])
{
    result[0] = result[1] = -1;
    for (int i = 1; i < NUMS_SIZE; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] + nums[i] == target) {
                result[0] = j;
                result[1] = i;
            }
        }
        if (result[1] != -1) return;
    }
}

static void check_answer(int target, const int expected[2])
{
    assert(answer[0] == expected[0] && answer[1] == expected[1]);
    if (expected[0] != -1) {
        assert(answer[0] >= 0 && answer[0] < answer[1]);
        assert(answer[1] < NUMS_SIZE);
        assert(nums[answer[0]] + nums[answer[1]] == target);
    }
}

static void check_both(int target)
{
    int expected[2];
    expected_pair(target, expected);
    two_sum_bf(target);
    check_answer(target, expected);
    two_sum_ht(target);
    check_answer(target, expected);
    int count = check_table();
    assert(count == (expected[0] == -1 ? NUMS_SIZE : expected[1]));
    for (int node = 0; node < count; ++node) {
        assert(hnodes[node].data == node);
        assert(hnodes[node].key == nums[node]);
    }
}

static void test_two_sum(void)
{
    int original[NUMS_SIZE];
    memcpy(original, nums, sizeof original);
    const int targets[] = {0, 2, 3, 100};
    const int pairs[][2] = {{4, 5}, {3, 7}, {5, 6}, {-1, -1}};
    for (int i = 0; i < 4; ++i) {
        check_both(targets[i]);
        check_answer(targets[i], pairs[i]);
    }
    check_both(0); /* A full miss is reset automatically at the next call. */
    check_both(0); /* Early-success records are also reset automatically. */
    for (int target = -40; target <= 40; ++target) check_both(target);

    for (int i = 0; i < NUMS_SIZE; ++i) nums[i] = 20;
    nums[0] = 5;
    check_both(10); /* One 5 must not pair with itself. */
    assert(answer[0] == -1 && answer[1] == -1);
    nums[1] = 5;
    check_both(10);
    assert(answer[0] == 0 && answer[1] == 1);

    for (int i = 0; i < NUMS_SIZE; ++i) nums[i] = 0;
    nums[0] = nums[1] = 1;
    nums[2] = 5;
    check_both(6);
    assert(answer[0] == 1 && answer[1] == 2); /* Newest earlier match. */

    /* Small signed inputs keep every sum and complement within int range. */
    unsigned int state = 9;
    for (int trial = 0; trial < 40; ++trial) {
        for (int i = 0; i < NUMS_SIZE; ++i) {
            state = state * 1664525u + 1013904223u;
            nums[i] = (int)(state % 41u) - 20;
        }
        for (int target = -45; target <= 45; ++target) check_both(target);
    }
    memcpy(nums, original, sizeof nums);
    initialize();
    puts("3. Two-sum oracle, exact pair order, duplicates, and repeated runs passed.");
}

int main(void)
{
    test_hash_and_chains();
    test_capacity_and_reset();
    test_two_sum();
    puts("Module 09 current lab core tests passed.");
    return 0;
}
