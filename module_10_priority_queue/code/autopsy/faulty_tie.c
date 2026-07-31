#include <stddef.h>
#include <stdio.h>

typedef struct {
    int alert_id;
    size_t priority;
    size_t arrival_sequence;
} TrainingAlert;

static size_t faulty_minimum_index(
    const TrainingAlert *alerts,
    size_t count
)
{
    size_t minimum = 0U;
    size_t index;

    for (index = 1U; index < count; ++index) {
        /*
         * Intentional defect: replacement on equal numeric priority ignores
         * the earlier arrival sequence.
         */
        if (alerts[index].priority <= alerts[minimum].priority) {
            minimum = index;
        }
    }
    return minimum;
}

int main(void)
{
    static const TrainingAlert alerts[] = {
        {80, 2U, 0U},
        {91, 1U, 1U},
        {17, 1U, 2U},
        {44, 3U, 3U}
    };
    const size_t count = sizeof alerts / sizeof alerts[0];
    size_t index;
    size_t selected;

    for (index = 0U; index < count; ++index) {
        (void)printf(
            "index %zu: alert=%d priority=%zu sequence=%zu\n",
            index,
            alerts[index].alert_id,
            alerts[index].priority,
            alerts[index].arrival_sequence
        );
    }

    selected = faulty_minimum_index(alerts, count);
    (void)printf(
        "selected: alert=%d priority=%zu sequence=%zu\n",
        alerts[selected].alert_id,
        alerts[selected].priority,
        alerts[selected].arrival_sequence
    );
    return 0;
}
