#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "../../student/lab.c"

/* Check ownership independently: every pool slot belongs to exactly one
   bucket or to the free chain, and all chains terminate without a cycle. */
static int check_pool(void)
{
    int seen[10] = {0};
    int live = 0;
    for (int bucket = 0; bucket < 10; ++bucket) {
        int node = hashtable[bucket];
        while (node != -1) {
            assert(node >= 0 && node < 10);
            assert(!seen[node]);
            seen[node] = 1;
            ++live;
            node = lnodes[node].next;
        }
    }
    int node = free_head;
    while (node != -1) {
        assert(node >= 0 && node < 10);
        assert(!seen[node]);
        seen[node] = 1;
        node = lnodes[node].next;
    }
    for (int i = 0; i < 10; ++i) {
        assert(seen[i]);
    }
    return live;
}

static void test_hash_and_chains(void)
{
    assert(hash_func(INT_MIN) >= 0 && hash_func(INT_MIN) < 10);
    assert(hash_func(INT_MAX) >= 0 && hash_func(INT_MAX) < 10);
    assert(hash_func(-16) == 4 && hash_func(-1) == 9);
    assert(hash_func(0) == 0 && hash_func(-10) == 0);
    assert(hash_func(12) == 2 && hash_func(22) == 2);
    assert(hash_func(-8) == 2);
    assert(find_data(2, 12) == -1);
    assert(save_data(2, 12) == 0);
    assert(save_data(2, 22) == 1);
    assert(save_data(2, -8) == 2);
    assert(hashtable[2] == 2 && free_head == 3);
    assert(lnodes[2].next == 1 && lnodes[1].next == 0);
    assert(lnodes[0].next == -1);
    assert(find_data(2, -8) == 2 && find_data(2, 12) == 0);
    assert(find_data(2, 32) == -1);
    assert(save_data(2, 22) == 3); /* duplicates prepend, not update */
    assert(find_data(2, 22) == 3 && lnodes[3].next == 2);
    assert(check_pool() == 4);
    init_hashtable();
    assert(check_pool() == 0 && free_head == 3);
    puts("1. Hashing and linked chains passed.");
}

static void test_pool_lifecycle(void)
{
    /* Reinitialization is idempotent and preserves the recycled ordering. */
    int slots[10];
    int saved_free = free_head;
    init_lnodes_pool();
    free_lnode_chunk(-1);
    assert(free_head == saved_free);
    for (int i = 0; i < 10; ++i) {
        int expected = free_head;
        slots[i] = save_data(0, i * 10);
        assert(slots[i] == expected);
    }
    assert(check_pool() == 10 && free_head == -1);
    struct Linked_Node before[10];
    memcpy(before, lnodes, sizeof before);
    assert(save_data(1, 7) == -1);
    assert(hashtable[1] == -1 && hashtable[0] == slots[9]);
    for (int i = 0; i < 10; ++i) {
        assert(lnodes[i].data == before[i].data);
        assert(lnodes[i].next == before[i].next);
    }
    init_hashtable();
    assert(check_pool() == 0 && free_head == slots[9]);
    init_hashtable(); /* empty reset must not recycle a node twice */
    assert(check_pool() == 0 && free_head == slots[9]);
    int reused = save_data(7, 17);
    assert(reused == slots[9] && free_head == slots[8]);
    init_hashtable();
    assert(check_pool() == 0);
    puts("2. Pool exhaustion and recycling passed.");
}

static int pair_exists(int target)
{
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] + nums[j] == target) {
                return 1;
            }
        }
    }
    return 0;
}

static void check_answer(int target, int exists)
{
    if (!exists) {
        assert(answer[0] == -1 && answer[1] == -1);
    } else {
        assert(answer[1] >= 0 && answer[1] < answer[0]);
        assert(answer[0] < 10);
        assert(nums[answer[0]] + nums[answer[1]] == target);
    }
}

static void test_two_sum(void)
{
    two_sum_bf(0);
    assert(answer[0] == 5 && answer[1] == 4);
    two_sum_ht(0);
    assert(answer[0] == 5 && answer[1] == 4);
    assert(check_pool() == 5); /* successful current index not inserted */
    for (int target = -40; target <= 40; ++target) {
        int exists = pair_exists(target);
        two_sum_bf(target);
        check_answer(target, exists);
        two_sum_ht(target);
        check_answer(target, exists);
        assert(check_pool() <= 10);
    }
    two_sum_ht(32);
    assert(answer[0] == -1 && answer[1] == -1);
    assert(check_pool() == 10);
    two_sum_ht(0); /* no pool reset: the function recycles the previous run */
    assert(answer[0] == 5 && answer[1] == 4 && check_pool() == 5);

    int original[10];
    memcpy(original, nums, sizeof original);
    for (int i = 0; i < 10; ++i) nums[i] = 20;
    nums[0] = 5;
    two_sum_ht(10); /* one 5 cannot be paired with itself */
    check_answer(10, 0);
    nums[1] = 5;
    two_sum_ht(10);
    assert(answer[0] == 1 && answer[1] == 0);
    for (int i = 0; i < 10; ++i) nums[i] = 0;
    nums[0] = nums[1] = 1;
    nums[2] = 5;
    two_sum_bf(6);
    assert(answer[0] == 2 && answer[1] == 0);
    two_sum_ht(6);
    assert(answer[0] == 2 && answer[1] == 1);
    check_answer(6, 1);
    init_hashtable();
    memcpy(nums, original, sizeof nums);
    assert(check_pool() == 0);
    puts("3. Two-sum oracle, distinct indices, and repeated runs passed.");
}

int main(void)
{
    init_lnodes_pool();
    assert(check_pool() == 0);
    test_hash_and_chains();
    test_pool_lifecycle();
    test_two_sum();
    puts("Module 09 current lab core tests passed.");
    return 0;
}
