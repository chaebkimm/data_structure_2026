#include "event_queue.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifndef EVENT_QUEUE_TESTING
#error "Core tests require -DEVENT_QUEUE_TESTING."
#endif

#define REQUIRE(condition)                                                 \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  requirement failed at line %d: %s\n",      \
                __LINE__, #condition);                                     \
            release_active_queue();                                        \
            return false;                                                  \
        }                                                                  \
    } while (false)

typedef bool (*TestFunction)(void);

static EventQueue *active_queue = NULL;
static unsigned int tests_run = 0U;
static unsigned int tests_failed = 0U;

/*
 * This is an explicitly non-owning observation. It never represents another
 * Queue and must never be passed to event_queue_destroy.
 */
typedef struct {
    const int *data_identity;
    size_t capacity;
    size_t head;
    size_t size;
} QueueFieldSnapshot;

static void track_queue(EventQueue *queue)
{
    active_queue = queue;
}

static void release_active_queue(void)
{
    if (active_queue != NULL) {
        event_queue_destroy(active_queue);
        active_queue = NULL;
    }
}

static QueueFieldSnapshot snapshot_fields(const EventQueue *queue)
{
    QueueFieldSnapshot snapshot;

    snapshot.data_identity = queue->data;
    snapshot.capacity = queue->capacity;
    snapshot.head = queue->head;
    snapshot.size = queue->size;
    return snapshot;
}

static bool fields_match(
    const EventQueue *queue,
    const QueueFieldSnapshot *snapshot
)
{
    return queue->data == snapshot->data_identity &&
        queue->capacity == snapshot->capacity &&
        queue->head == snapshot->head &&
        queue->size == snapshot->size;
}

static void snapshot_slots(
    const int *slots,
    size_t count,
    int *out_snapshot
)
{
    size_t index;

    for (index = 0U; index < count; ++index) {
        out_snapshot[index] = slots[index];
    }
}

static bool slots_match(
    const int *slots,
    const int *snapshot,
    size_t count
)
{
    size_t index;

    for (index = 0U; index < count; ++index) {
        if (slots[index] != snapshot[index]) {
            return false;
        }
    }
    return true;
}

static bool test_zero_reinitialization_and_destroy(void)
{
    EventQueue queue = {0};
    QueueFieldSnapshot before;
    int before_slots[3];

    REQUIRE(
        event_queue_init(NULL, 3U) == EVENT_QUEUE_INVALID_ARGUMENT
    );

    REQUIRE(event_queue_init(&queue, 0U) == EVENT_QUEUE_OK);
    REQUIRE(event_queue_validate(&queue) == EVENT_QUEUE_OK);
    REQUIRE(queue.data == NULL);
    REQUIRE(queue.capacity == 0U);
    REQUIRE(queue.head == 0U);
    REQUIRE(queue.size == 0U);

    /* Capacity-zero initialization leaves the Queue object all-zero. */
    REQUIRE(event_queue_init(&queue, 0U) == EVENT_QUEUE_OK);

    REQUIRE(event_queue_init(&queue, 3U) == EVENT_QUEUE_OK);
    track_queue(&queue);
    REQUIRE(event_queue_validate(&queue) == EVENT_QUEUE_OK);
    REQUIRE(queue.data != NULL);
    REQUIRE(queue.capacity == 3U);
    REQUIRE(queue.head == 0U);
    REQUIRE(queue.size == 0U);

    queue.data[0] = 731;
    queue.data[1] = 732;
    queue.data[2] = 733;
    before = snapshot_fields(&queue);
    snapshot_slots(queue.data, 3U, before_slots);
    REQUIRE(
        event_queue_init(&queue, 2U) == EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(fields_match(&queue, &before));
    REQUIRE(slots_match(queue.data, before_slots, 3U));

    release_active_queue();
    REQUIRE(queue.data == NULL);
    REQUIRE(queue.capacity == 0U);
    REQUIRE(queue.head == 0U);
    REQUIRE(queue.size == 0U);
    REQUIRE(event_queue_validate(&queue) == EVENT_QUEUE_OK);

    REQUIRE(event_queue_init(&queue, 2U) == EVENT_QUEUE_OK);
    track_queue(&queue);
    REQUIRE(queue.capacity == 2U);
    release_active_queue();
    event_queue_destroy(&queue);
    event_queue_destroy(NULL);
    REQUIRE(event_queue_validate(&queue) == EVENT_QUEUE_OK);
    return true;
}

static bool test_capacity_limit_and_allocation_failure(void)
{
    EventQueue queue = {0};
    QueueFieldSnapshot before = snapshot_fields(&queue);

    REQUIRE(
        event_queue_init(
            &queue,
            (size_t)EVENT_QUEUE_MAX_CAPACITY + 1U
        ) == EVENT_QUEUE_LIMIT
    );
    REQUIRE(fields_match(&queue, &before));

    event_queue_test_fail_next_allocation();
    REQUIRE(
        event_queue_init(&queue, 4U) == EVENT_QUEUE_ALLOCATION
    );
    REQUIRE(fields_match(&queue, &before));

    REQUIRE(
        event_queue_init(
            &queue,
            (size_t)EVENT_QUEUE_MAX_CAPACITY
        ) == EVENT_QUEUE_OK
    );
    track_queue(&queue);
    REQUIRE(queue.data != NULL);
    REQUIRE(
        queue.capacity == (size_t)EVENT_QUEUE_MAX_CAPACITY
    );
    REQUIRE(queue.head == 0U);
    REQUIRE(queue.size == 0U);
    release_active_queue();
    return true;
}

static bool test_zero_and_capacity_one(void)
{
    EventQueue queue = {0};
    QueueFieldSnapshot before;
    int output = 999;
    int *pointer;
    int slot_before;

    REQUIRE(event_queue_init(&queue, 0U) == EVENT_QUEUE_OK);
    before = snapshot_fields(&queue);
    REQUIRE(
        event_queue_enqueue(&queue, 31) == EVENT_QUEUE_FULL
    );
    REQUIRE(fields_match(&queue, &before));
    REQUIRE(
        event_queue_peek(&queue, &output) == EVENT_QUEUE_EMPTY
    );
    REQUIRE(output == 999);
    REQUIRE(
        event_queue_dequeue(&queue, &output) == EVENT_QUEUE_EMPTY
    );
    REQUIRE(output == 999);

    REQUIRE(event_queue_init(&queue, 1U) == EVENT_QUEUE_OK);
    track_queue(&queue);
    pointer = queue.data;
    REQUIRE(event_queue_enqueue(&queue, 31) == EVENT_QUEUE_OK);
    REQUIRE(queue.head == 0U);
    REQUIRE(queue.size == 1U);
    REQUIRE(queue.data[0] == 31);

    before = snapshot_fields(&queue);
    slot_before = queue.data[0];
    REQUIRE(event_queue_enqueue(&queue, 8) == EVENT_QUEUE_FULL);
    REQUIRE(fields_match(&queue, &before));
    REQUIRE(queue.data[0] == slot_before);

    REQUIRE(event_queue_peek(&queue, &output) == EVENT_QUEUE_OK);
    REQUIRE(output == 31);
    REQUIRE(fields_match(&queue, &before));
    REQUIRE(queue.data[0] == slot_before);

    REQUIRE(event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK);
    REQUIRE(output == 31);
    REQUIRE(queue.head == 0U);
    REQUIRE(queue.size == 0U);
    REQUIRE(queue.data == pointer);
    REQUIRE(queue.capacity == 1U);

    output = 999;
    before = snapshot_fields(&queue);
    slot_before = queue.data[0];
    REQUIRE(
        event_queue_dequeue(&queue, &output) == EVENT_QUEUE_EMPTY
    );
    REQUIRE(output == 999);
    REQUIRE(fields_match(&queue, &before));
    REQUIRE(queue.data[0] == slot_before);
    REQUIRE(
        event_queue_peek(&queue, &output) == EVENT_QUEUE_EMPTY
    );
    REQUIRE(output == 999);
    REQUIRE(fields_match(&queue, &before));
    REQUIRE(queue.data[0] == slot_before);

    REQUIRE(event_queue_enqueue(&queue, 8) == EVENT_QUEUE_OK);
    REQUIRE(event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK);
    REQUIRE(output == 8);
    REQUIRE(queue.head == 0U);
    REQUIRE(queue.size == 0U);
    release_active_queue();
    return true;
}

static bool test_fifo_and_peek_preservation(void)
{
    EventQueue queue = {0};
    QueueFieldSnapshot before;
    int *pointer;
    int output = -1;

    REQUIRE(event_queue_init(&queue, 5U) == EVENT_QUEUE_OK);
    track_queue(&queue);
    pointer = queue.data;

    REQUIRE(event_queue_enqueue(&queue, 31) == EVENT_QUEUE_OK);
    REQUIRE(event_queue_enqueue(&queue, 8) == EVENT_QUEUE_OK);
    REQUIRE(event_queue_enqueue(&queue, 47) == EVENT_QUEUE_OK);
    REQUIRE(queue.head == 0U);
    REQUIRE(queue.size == 3U);

    before = snapshot_fields(&queue);
    REQUIRE(event_queue_peek(&queue, &output) == EVENT_QUEUE_OK);
    REQUIRE(output == 31);
    REQUIRE(fields_match(&queue, &before));

    REQUIRE(event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK);
    REQUIRE(output == 31);
    REQUIRE(queue.head == 1U);
    REQUIRE(queue.size == 2U);
    REQUIRE(event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK);
    REQUIRE(output == 8);
    REQUIRE(queue.head == 2U);
    REQUIRE(queue.size == 1U);
    REQUIRE(event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK);
    REQUIRE(output == 47);
    REQUIRE(queue.head == 0U);
    REQUIRE(queue.size == 0U);
    REQUIRE(queue.data == pointer);
    REQUIRE(queue.capacity == 5U);
    release_active_queue();
    return true;
}

static bool test_exact_wraparound_and_full_preservation(void)
{
    EventQueue queue = {0};
    QueueFieldSnapshot before;
    int before_slots[4];
    int *pointer;
    int output = -1;
    const int expected[] = {47, 19, 62, 5};
    size_t index;

    REQUIRE(event_queue_init(&queue, 4U) == EVENT_QUEUE_OK);
    track_queue(&queue);
    pointer = queue.data;

    REQUIRE(event_queue_enqueue(&queue, 31) == EVENT_QUEUE_OK);
    REQUIRE(event_queue_enqueue(&queue, 8) == EVENT_QUEUE_OK);
    REQUIRE(event_queue_enqueue(&queue, 47) == EVENT_QUEUE_OK);
    REQUIRE(event_queue_enqueue(&queue, 19) == EVENT_QUEUE_OK);
    REQUIRE(event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK);
    REQUIRE(output == 31);
    REQUIRE(event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK);
    REQUIRE(output == 8);
    REQUIRE(queue.head == 2U);
    REQUIRE(queue.size == 2U);

    REQUIRE(event_queue_enqueue(&queue, 62) == EVENT_QUEUE_OK);
    REQUIRE(event_queue_enqueue(&queue, 5) == EVENT_QUEUE_OK);
    REQUIRE(queue.data[0] == 62);
    REQUIRE(queue.data[1] == 5);
    REQUIRE(queue.data[2] == 47);
    REQUIRE(queue.data[3] == 19);
    REQUIRE(queue.head == 2U);
    REQUIRE(queue.size == 4U);
    REQUIRE((queue.head + queue.size) % queue.capacity == 2U);

    before = snapshot_fields(&queue);
    for (index = 0U; index < 4U; ++index) {
        before_slots[index] = queue.data[index];
    }
    REQUIRE(event_queue_enqueue(&queue, 90) == EVENT_QUEUE_FULL);
    REQUIRE(fields_match(&queue, &before));
    for (index = 0U; index < 4U; ++index) {
        REQUIRE(queue.data[index] == before_slots[index]);
    }

    for (index = 0U; index < 4U; ++index) {
        REQUIRE(
            event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK
        );
        REQUIRE(output == expected[index]);
    }
    REQUIRE(queue.head == 0U);
    REQUIRE(queue.size == 0U);
    REQUIRE(queue.data == pointer);
    REQUIRE(queue.capacity == 4U);
    release_active_queue();
    return true;
}

static bool test_repeated_fill_and_drain_cycles(void)
{
    EventQueue queue = {0};
    int output = -1;
    int cycle;

    REQUIRE(event_queue_init(&queue, 3U) == EVENT_QUEUE_OK);
    track_queue(&queue);

    for (cycle = 0; cycle < 12; ++cycle) {
        int base = cycle * 10;

        REQUIRE(
            event_queue_enqueue(&queue, base + 1) == EVENT_QUEUE_OK
        );
        REQUIRE(
            event_queue_enqueue(&queue, base + 2) == EVENT_QUEUE_OK
        );
        REQUIRE(
            event_queue_enqueue(&queue, base + 3) == EVENT_QUEUE_OK
        );
        REQUIRE(
            event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK
        );
        REQUIRE(output == base + 1);
        REQUIRE(
            event_queue_enqueue(&queue, base + 4) == EVENT_QUEUE_OK
        );
        REQUIRE(
            event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK
        );
        REQUIRE(output == base + 2);
        REQUIRE(
            event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK
        );
        REQUIRE(output == base + 3);
        REQUIRE(
            event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK
        );
        REQUIRE(output == base + 4);
        REQUIRE(queue.head == 0U);
        REQUIRE(queue.size == 0U);
        REQUIRE(event_queue_validate(&queue) == EVENT_QUEUE_OK);
    }

    release_active_queue();
    return true;
}

static bool test_invalid_arguments_and_states(void)
{
    int storage[3] = {11, 22, 33};
    EventQueue zero_with_data = {storage, 0U, 0U, 0U};
    EventQueue zero_with_head = {NULL, 0U, 1U, 0U};
    EventQueue zero_with_size = {NULL, 0U, 0U, 1U};
    EventQueue excessive_capacity = {
        storage,
        (size_t)EVENT_QUEUE_MAX_CAPACITY + 1U,
        0U,
        1U
    };
    EventQueue missing_data = {NULL, 2U, 0U, 1U};
    EventQueue excessive_size = {storage, 2U, 0U, 3U};
    EventQueue empty_nonzero_head = {storage, 3U, 1U, 0U};
    EventQueue head_out_of_range = {storage, 3U, 3U, 1U};
    EventQueue queue = {0};
    QueueFieldSnapshot before;
    int storage_before[3];
    int queue_slots_before[2];
    int output = 777;

    REQUIRE(
        event_queue_validate(NULL) == EVENT_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        event_queue_validate(&zero_with_data) ==
        EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(
        event_queue_validate(&zero_with_head) ==
        EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(
        event_queue_validate(&zero_with_size) ==
        EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(
        event_queue_validate(&excessive_capacity) ==
        EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(
        event_queue_validate(&missing_data) ==
        EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(
        event_queue_validate(&excessive_size) ==
        EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(
        event_queue_validate(&empty_nonzero_head) ==
        EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(
        event_queue_validate(&head_out_of_range) ==
        EVENT_QUEUE_INVALID_STATE
    );

    before = snapshot_fields(&head_out_of_range);
    snapshot_slots(storage, 3U, storage_before);
    REQUIRE(
        event_queue_enqueue(&head_out_of_range, 44) ==
        EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(fields_match(&head_out_of_range, &before));
    REQUIRE(slots_match(storage, storage_before, 3U));

    before = snapshot_fields(&missing_data);
    REQUIRE(
        event_queue_dequeue(&missing_data, &output) ==
        EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(output == 777);
    REQUIRE(fields_match(&missing_data, &before));

    before = snapshot_fields(&excessive_size);
    snapshot_slots(storage, 3U, storage_before);
    REQUIRE(
        event_queue_peek(&excessive_size, &output) ==
        EVENT_QUEUE_INVALID_STATE
    );
    REQUIRE(output == 777);
    REQUIRE(fields_match(&excessive_size, &before));
    REQUIRE(slots_match(storage, storage_before, 3U));
    REQUIRE(
        event_queue_enqueue(NULL, 1) == EVENT_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        event_queue_dequeue(NULL, &output) ==
        EVENT_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(
        event_queue_peek(NULL, &output) ==
        EVENT_QUEUE_INVALID_ARGUMENT
    );

    REQUIRE(event_queue_init(&queue, 2U) == EVENT_QUEUE_OK);
    track_queue(&queue);
    queue.data[0] = 501;
    queue.data[1] = 502;
    before = snapshot_fields(&queue);
    snapshot_slots(queue.data, 2U, queue_slots_before);
    REQUIRE(
        event_queue_dequeue(&queue, NULL) ==
        EVENT_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(fields_match(&queue, &before));
    REQUIRE(slots_match(queue.data, queue_slots_before, 2U));
    REQUIRE(
        event_queue_peek(&queue, NULL) ==
        EVENT_QUEUE_INVALID_ARGUMENT
    );
    REQUIRE(fields_match(&queue, &before));
    REQUIRE(slots_match(queue.data, queue_slots_before, 2U));
    release_active_queue();
    return true;
}

static bool test_status_names(void)
{
    REQUIRE(strcmp(
        event_queue_status_name(EVENT_QUEUE_OK),
        "ok"
    ) == 0);
    REQUIRE(strcmp(
        event_queue_status_name(EVENT_QUEUE_INVALID_ARGUMENT),
        "invalid argument"
    ) == 0);
    REQUIRE(strcmp(
        event_queue_status_name(EVENT_QUEUE_LIMIT),
        "requested Queue capacity exceeds maximum"
    ) == 0);
    REQUIRE(strcmp(
        event_queue_status_name(EVENT_QUEUE_FULL),
        "Queue is full"
    ) == 0);
    REQUIRE(strcmp(
        event_queue_status_name(EVENT_QUEUE_EMPTY),
        "Queue is empty"
    ) == 0);
    REQUIRE(strcmp(
        event_queue_status_name(EVENT_QUEUE_ALLOCATION),
        "allocation failed"
    ) == 0);
    REQUIRE(strcmp(
        event_queue_status_name(EVENT_QUEUE_INVALID_STATE),
        "Queue representation is invalid"
    ) == 0);
    REQUIRE(strcmp(
        event_queue_status_name((EventQueueStatus)99),
        "unknown EventQueueStatus"
    ) == 0);
    return true;
}

static void run_test(const char *name, TestFunction test)
{
    bool passed = test();

    tests_run += 1U;
    if (passed) {
        printf("PASS %s\n", name);
    } else {
        tests_failed += 1U;
        printf("FAIL %s\n", name);
    }
}

int main(void)
{
    run_test(
        "zero initialization, reinitialization, and destroy",
        test_zero_reinitialization_and_destroy
    );
    run_test(
        "capacity limit and allocation failure",
        test_capacity_limit_and_allocation_failure
    );
    run_test("zero and capacity one", test_zero_and_capacity_one);
    run_test(
        "FIFO and peek preservation",
        test_fifo_and_peek_preservation
    );
    run_test(
        "exact wrap-around and full preservation",
        test_exact_wraparound_and_full_preservation
    );
    run_test(
        "repeated fill and drain cycles",
        test_repeated_fill_and_drain_cycles
    );
    run_test(
        "invalid arguments and states",
        test_invalid_arguments_and_states
    );
    run_test("status names", test_status_names);

    printf(
        "\n%u core test(s), %u failure(s)\n",
        tests_run,
        tests_failed
    );
    return tests_failed == 0U ? 0 : 1;
}
