#include "event_queue.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#ifndef EVENT_QUEUE_TESTING
#error "Extension tests require -DEVENT_QUEUE_TESTING."
#endif

#define CHECK(condition)                                                   \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr, "  check failed at line %d: %s\n",            \
                __LINE__, #condition);                                     \
            release_active_queue();                                        \
            return false;                                                  \
        }                                                                  \
    } while (false)

typedef bool (*TestFunction)(void);

static EventQueue *active_queue = NULL;

/*
 * This snapshot observes fields without representing or owning a Queue.
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

static bool queue_matches_reference(
    const EventQueue *queue,
    const int *reference,
    size_t reference_size,
    size_t expected_capacity,
    const int *expected_pointer
)
{
    size_t index;

    if (event_queue_validate(queue) != EVENT_QUEUE_OK ||
        queue->capacity != expected_capacity ||
        queue->data != expected_pointer ||
        queue->size != reference_size) {
        return false;
    }

    if (reference_size == 0U && queue->head != 0U) {
        return false;
    }

    for (index = 0U; index < reference_size; ++index) {
        size_t physical =
            (queue->head + index) % queue->capacity;

        if (queue->data[physical] != reference[index]) {
            return false;
        }
    }
    return true;
}

static bool test_exact_maximum_wraparound(void)
{
    EventQueue queue = {0};
    QueueFieldSnapshot before;
    int before_slots[EVENT_QUEUE_MAX_CAPACITY];
    int *pointer;
    int output = -1;
    size_t index;

    CHECK(
        event_queue_init(
            &queue,
            (size_t)EVENT_QUEUE_MAX_CAPACITY
        ) == EVENT_QUEUE_OK
    );
    track_queue(&queue);
    pointer = queue.data;

    for (index = 0U;
         index < (size_t)EVENT_QUEUE_MAX_CAPACITY;
         ++index) {
        CHECK(
            event_queue_enqueue(&queue, (int)index) ==
            EVENT_QUEUE_OK
        );
    }

    before = snapshot_fields(&queue);
    for (index = 0U;
         index < (size_t)EVENT_QUEUE_MAX_CAPACITY;
         ++index) {
        before_slots[index] = queue.data[index];
    }
    CHECK(event_queue_enqueue(&queue, 999) == EVENT_QUEUE_FULL);
    CHECK(fields_match(&queue, &before));
    for (index = 0U;
         index < (size_t)EVENT_QUEUE_MAX_CAPACITY;
         ++index) {
        CHECK(queue.data[index] == before_slots[index]);
    }

    for (index = 0U; index < 32U; ++index) {
        CHECK(
            event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK
        );
        CHECK(output == (int)index);
    }
    CHECK(queue.head == 32U);
    CHECK(queue.size == 32U);

    for (index = 64U; index < 96U; ++index) {
        CHECK(
            event_queue_enqueue(&queue, (int)index) ==
            EVENT_QUEUE_OK
        );
    }
    CHECK(queue.head == 32U);
    CHECK(
        queue.size == (size_t)EVENT_QUEUE_MAX_CAPACITY
    );

    for (index = 32U; index < 96U; ++index) {
        CHECK(
            event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK
        );
        CHECK(output == (int)index);
    }
    CHECK(queue.head == 0U);
    CHECK(queue.size == 0U);
    CHECK(queue.data == pointer);
    CHECK(
        queue.capacity == (size_t)EVENT_QUEUE_MAX_CAPACITY
    );
    release_active_queue();
    return true;
}

static bool test_every_head_position(void)
{
    EventQueue queue = {0};
    size_t target_head;

    for (target_head = 0U; target_head < 5U; ++target_head) {
        int output = -1;
        size_t index;

        CHECK(event_queue_init(&queue, 5U) == EVENT_QUEUE_OK);
        track_queue(&queue);

        for (index = 0U; index < 5U; ++index) {
            CHECK(
                event_queue_enqueue(&queue, (int)index) ==
                EVENT_QUEUE_OK
            );
        }

        for (index = 0U; index < target_head; ++index) {
            CHECK(
                event_queue_dequeue(&queue, &output) ==
                EVENT_QUEUE_OK
            );
            CHECK(output == (int)index);
        }

        if (target_head == 0U) {
            CHECK(queue.head == 0U);
        } else {
            CHECK(queue.head == target_head);
        }

        for (index = 0U; index < target_head; ++index) {
            CHECK(
                event_queue_enqueue(&queue, (int)(5U + index)) ==
                EVENT_QUEUE_OK
            );
        }
        CHECK(queue.size == 5U);

        for (index = target_head; index < 5U; ++index) {
            CHECK(
                event_queue_dequeue(&queue, &output) ==
                EVENT_QUEUE_OK
            );
            CHECK(output == (int)index);
        }
        for (index = 0U; index < target_head; ++index) {
            CHECK(
                event_queue_dequeue(&queue, &output) ==
                EVENT_QUEUE_OK
            );
            CHECK(output == (int)(5U + index));
        }
        CHECK(queue.head == 0U);
        CHECK(queue.size == 0U);
        release_active_queue();
    }
    return true;
}

static bool test_zero_capacity_does_not_consume_hook(void)
{
    EventQueue queue = {0};

    event_queue_test_fail_next_allocation();
    CHECK(event_queue_init(&queue, 0U) == EVENT_QUEUE_OK);
    CHECK(event_queue_validate(&queue) == EVENT_QUEUE_OK);
    CHECK(
        event_queue_init(&queue, 4U) == EVENT_QUEUE_ALLOCATION
    );
    CHECK(queue.data == NULL);
    CHECK(queue.capacity == 0U);
    CHECK(queue.head == 0U);
    CHECK(queue.size == 0U);

    CHECK(event_queue_init(&queue, 4U) == EVENT_QUEUE_OK);
    track_queue(&queue);
    release_active_queue();
    return true;
}

static bool test_capacity_one_many_cycles(void)
{
    EventQueue queue = {0};
    int output = -1;
    int value;

    CHECK(event_queue_init(&queue, 1U) == EVENT_QUEUE_OK);
    track_queue(&queue);

    for (value = 0; value < 200; ++value) {
        CHECK(
            event_queue_enqueue(&queue, value) == EVENT_QUEUE_OK
        );
        CHECK(queue.head == 0U);
        CHECK(queue.size == 1U);
        CHECK(event_queue_enqueue(&queue, -1) == EVENT_QUEUE_FULL);
        CHECK(
            event_queue_dequeue(&queue, &output) == EVENT_QUEUE_OK
        );
        CHECK(output == value);
        CHECK(queue.head == 0U);
        CHECK(queue.size == 0U);
    }

    release_active_queue();
    return true;
}

static uint32_t next_random(uint32_t *state)
{
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}

static bool test_deterministic_differential_sequence(void)
{
    enum {
        CAPACITY = 11,
        STEPS = 2000
    };

    EventQueue queue = {0};
    int reference[CAPACITY];
    int before_slots[CAPACITY];
    size_t reference_size = 0U;
    uint32_t state = UINT32_C(0xC071A);
    int *pointer;
    int step;
    size_t slot_index;

    CHECK(
        event_queue_init(&queue, (size_t)CAPACITY) ==
        EVENT_QUEUE_OK
    );
    track_queue(&queue);
    pointer = queue.data;
    for (slot_index = 0U;
         slot_index < (size_t)CAPACITY;
         ++slot_index) {
        queue.data[slot_index] = 2000 + (int)slot_index;
    }

    for (step = 0; step < STEPS; ++step) {
        uint32_t random_value = next_random(&state);
        unsigned int operation = (unsigned int)(random_value % 3U);
        int value = (int)(random_value & UINT32_C(0x7FFF));
        QueueFieldSnapshot before = snapshot_fields(&queue);
        size_t index;

        snapshot_slots(
            queue.data,
            (size_t)CAPACITY,
            before_slots
        );

        if (operation == 0U) {
            EventQueueStatus status =
                event_queue_enqueue(&queue, value);

            if (reference_size == (size_t)CAPACITY) {
                CHECK(status == EVENT_QUEUE_FULL);
                CHECK(fields_match(&queue, &before));
                CHECK(slots_match(
                    queue.data,
                    before_slots,
                    (size_t)CAPACITY
                ));
            } else {
                CHECK(status == EVENT_QUEUE_OK);
                reference[reference_size] = value;
                reference_size += 1U;
            }
        } else if (operation == 1U) {
            int output = -777;
            EventQueueStatus status =
                event_queue_dequeue(&queue, &output);

            if (reference_size == 0U) {
                CHECK(status == EVENT_QUEUE_EMPTY);
                CHECK(output == -777);
                CHECK(fields_match(&queue, &before));
                CHECK(slots_match(
                    queue.data,
                    before_slots,
                    (size_t)CAPACITY
                ));
            } else {
                CHECK(status == EVENT_QUEUE_OK);
                CHECK(output == reference[0]);
                for (index = 0U;
                     index + 1U < reference_size;
                     ++index) {
                    reference[index] = reference[index + 1U];
                }
                reference_size -= 1U;
            }
        } else {
            int output = -777;
            EventQueueStatus status =
                event_queue_peek(&queue, &output);

            if (reference_size == 0U) {
                CHECK(status == EVENT_QUEUE_EMPTY);
                CHECK(output == -777);
            } else {
                CHECK(status == EVENT_QUEUE_OK);
                CHECK(output == reference[0]);
            }
            CHECK(fields_match(&queue, &before));
            CHECK(slots_match(
                queue.data,
                before_slots,
                (size_t)CAPACITY
            ));
        }

        CHECK(queue_matches_reference(
            &queue,
            reference,
            reference_size,
            (size_t)CAPACITY,
            pointer
        ));
    }

    release_active_queue();
    return true;
}

static bool test_error_precedence_and_preservation(void)
{
    int invalid_storage[2] = {811, 812};
    int invalid_slots_before[2];
    EventQueue invalid_queue = {invalid_storage, 2U, 2U, 1U};
    QueueFieldSnapshot invalid_before =
        snapshot_fields(&invalid_queue);
    EventQueue live_queue = {0};
    QueueFieldSnapshot live_before;
    int live_slots_before[4];

    CHECK(
        event_queue_init(
            NULL,
            (size_t)EVENT_QUEUE_MAX_CAPACITY + 1U
        ) == EVENT_QUEUE_INVALID_ARGUMENT
    );

    CHECK(event_queue_init(&live_queue, 4U) == EVENT_QUEUE_OK);
    track_queue(&live_queue);
    live_queue.data[0] = 821;
    live_queue.data[1] = 822;
    live_queue.data[2] = 823;
    live_queue.data[3] = 824;
    live_before = snapshot_fields(&live_queue);
    snapshot_slots(live_queue.data, 4U, live_slots_before);
    CHECK(
        event_queue_init(
            &live_queue,
            (size_t)EVENT_QUEUE_MAX_CAPACITY + 1U
        ) == EVENT_QUEUE_INVALID_STATE
    );
    CHECK(fields_match(&live_queue, &live_before));
    CHECK(slots_match(live_queue.data, live_slots_before, 4U));

    snapshot_slots(
        invalid_storage,
        2U,
        invalid_slots_before
    );
    CHECK(
        event_queue_dequeue(&invalid_queue, NULL) ==
        EVENT_QUEUE_INVALID_ARGUMENT
    );
    CHECK(fields_match(&invalid_queue, &invalid_before));
    CHECK(slots_match(
        invalid_storage,
        invalid_slots_before,
        2U
    ));
    CHECK(
        event_queue_peek(&invalid_queue, NULL) ==
        EVENT_QUEUE_INVALID_ARGUMENT
    );
    CHECK(fields_match(&invalid_queue, &invalid_before));
    CHECK(slots_match(
        invalid_storage,
        invalid_slots_before,
        2U
    ));

    release_active_queue();
    return true;
}

static bool test_broad_invalid_states(void)
{
    int storage[64];
    int storage_before[64];
    EventQueue cases[] = {
        {storage, 0U, 0U, 0U},
        {NULL, 0U, 1U, 0U},
        {NULL, 0U, 0U, 1U},
        {NULL, 1U, 0U, 0U},
        {storage, 2U, 1U, 0U},
        {storage, 2U, 2U, 1U},
        {storage, 2U, 0U, 3U},
        {
            storage,
            (size_t)EVENT_QUEUE_MAX_CAPACITY + 1U,
            0U,
            1U
        }
    };
    size_t index;

    for (index = 0U; index < 64U; ++index) {
        storage[index] = 1000 + (int)index;
    }
    snapshot_slots(storage, 64U, storage_before);

    for (index = 0U;
         index < sizeof cases / sizeof cases[0];
         ++index) {
        QueueFieldSnapshot before = snapshot_fields(&cases[index]);
        int output = 444;

        CHECK(
            event_queue_validate(&cases[index]) ==
            EVENT_QUEUE_INVALID_STATE
        );
        CHECK(
            event_queue_enqueue(&cases[index], 91) ==
            EVENT_QUEUE_INVALID_STATE
        );
        CHECK(fields_match(&cases[index], &before));
        CHECK(slots_match(storage, storage_before, 64U));
        CHECK(
            event_queue_dequeue(&cases[index], &output) ==
            EVENT_QUEUE_INVALID_STATE
        );
        CHECK(output == 444);
        CHECK(fields_match(&cases[index], &before));
        CHECK(slots_match(storage, storage_before, 64U));
        CHECK(
            event_queue_peek(&cases[index], &output) ==
            EVENT_QUEUE_INVALID_STATE
        );
        CHECK(output == 444);
        CHECK(fields_match(&cases[index], &before));
        CHECK(slots_match(storage, storage_before, 64U));
    }
    return true;
}

static int run_test(TestFunction function, const char *name)
{
    bool passed = function();

    printf("%s: %s\n", name, passed ? "PASS" : "FAIL");
    return passed ? 0 : 1;
}

int main(void)
{
    int failures = 0;

    failures += run_test(
        test_exact_maximum_wraparound,
        "exact maximum and wrap-around"
    );
    failures += run_test(
        test_every_head_position,
        "every physical head position"
    );
    failures += run_test(
        test_zero_capacity_does_not_consume_hook,
        "zero capacity preserves allocation hook"
    );
    failures += run_test(
        test_capacity_one_many_cycles,
        "capacity-one repeated cycles"
    );
    failures += run_test(
        test_deterministic_differential_sequence,
        "deterministic differential sequence"
    );
    failures += run_test(
        test_error_precedence_and_preservation,
        "error precedence and preservation"
    );
    failures += run_test(
        test_broad_invalid_states,
        "broad invalid states"
    );

    if (failures != 0) {
        printf("%d extension test group(s) failed.\n", failures);
        return 1;
    }

    puts("All extension test groups passed.");
    return 0;
}
