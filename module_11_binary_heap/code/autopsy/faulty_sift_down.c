#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    int alert_id;
    size_t priority;
    size_t arrival_sequence;
} TrainingRecord;

static bool record_precedes(
    const TrainingRecord *left,
    const TrainingRecord *right
)
{
    if (left->priority != right->priority) {
        return left->priority < right->priority;
    }
    return left->arrival_sequence < right->arrival_sequence;
}

static bool is_min_heap(
    const TrainingRecord *records,
    size_t size
)
{
    size_t child;

    for (child = 1U; child < size; ++child) {
        size_t parent = (child - 1U) / 2U;

        if (record_precedes(&records[child], &records[parent])) {
            return false;
        }
    }
    return true;
}

/*
 * This bounded faulty repair always selects the left child when one exists.
 * It checks every index before access, so the defect corrupts Heap order
 * without reading outside the fixed array.
 */
static void faulty_sift_down(
    TrainingRecord *records,
    size_t size,
    TrainingRecord candidate
)
{
    size_t hole = 0U;

    for (;;) {
        size_t left = hole * 2U + 1U;

        if (left >= size) {
            break;
        }
        if (!record_precedes(&records[left], &candidate)) {
            break;
        }

        records[hole] = records[left];
        hole = left;
    }
    records[hole] = candidate;
}

static void print_priorities(
    const char *label,
    const TrainingRecord *records,
    size_t size
)
{
    size_t index;

    (void)printf("%s [", label);
    for (index = 0U; index < size; ++index) {
        if (index > 0U) {
            (void)fputs(", ", stdout);
        }
        (void)printf("%zu", records[index].priority);
    }
    (void)puts("]");
}

int main(void)
{
    TrainingRecord records[5] = {
        {5, 5U, 0U},
        {41, 41U, 1U},
        {17, 17U, 2U},
        {55, 55U, 3U},
        {70, 70U, 4U}
    };
    TrainingRecord extracted = records[0];
    TrainingRecord candidate = records[4];
    size_t new_size = 4U;

    print_priorities("before:", records, 5U);
    faulty_sift_down(records, new_size, candidate);
    (void)printf("extracted priority: %zu\n", extracted.priority);
    print_priorities("after faulty repair:", records, new_size);
    (void)printf(
        "is minimum Heap: %s\n",
        is_min_heap(records, new_size) ? "yes" : "no"
    );
    return 0;
}
