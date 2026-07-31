#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    size_t distance = SIZE_MAX - 3U;
    size_t weight = 5U;
    size_t old_neighbor_distance = 20U;
    size_t unchecked_candidate = distance + weight;
    bool faulty_relaxes =
        unchecked_candidate < old_neighbor_distance;
    bool safe_to_add =
        distance != SIZE_MAX &&
        weight <= SIZE_MAX - distance;
    bool guarded_ok = false;
    size_t guarded_neighbor_distance =
        old_neighbor_distance;

    if (safe_to_add) {
        size_t guarded_candidate = distance + weight;

        guarded_ok = guarded_candidate != SIZE_MAX;
        if (guarded_ok &&
            guarded_candidate <
                guarded_neighbor_distance) {
            guarded_neighbor_distance =
                guarded_candidate;
        }
    }

    (void)printf("distance: %zu\n", distance);
    (void)printf("weight: %zu\n", weight);
    (void)printf(
        "unchecked candidate: %zu\n",
        unchecked_candidate
    );
    (void)printf(
        "faulty relaxation: %s\n",
        faulty_relaxes ? "YES" : "NO"
    );
    (void)printf(
        "guarded status: %s\n",
        guarded_ok ? "DIJKSTRA_OK" :
            "DIJKSTRA_COST_RANGE"
    );
    (void)printf(
        "guarded neighbor distance: %zu\n",
        guarded_neighbor_distance
    );
    return 0;
}
