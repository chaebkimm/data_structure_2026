#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define AUTOPSY_CAPACITY 8U

typedef enum {
    SLOT_EMPTY = 0,
    SLOT_OCCUPIED,
    SLOT_DELETED
} SlotState;

typedef struct {
    uint32_t key;
    SlotState state;
} DemoSlot;

static bool bounded_lookup(const DemoSlot *slots, uint32_t key)
{
    size_t home = (size_t)key % AUTOPSY_CAPACITY;
    size_t step;

    for (step = 0U; step < AUTOPSY_CAPACITY; ++step) {
        size_t index = (home + step) % AUTOPSY_CAPACITY;

        if (slots[index].state == SLOT_EMPTY) {
            return false;
        }
        if (slots[index].state == SLOT_OCCUPIED &&
            slots[index].key == key) {
            return true;
        }
    }
    return false;
}

int main(void)
{
    DemoSlot faulty[AUTOPSY_CAPACITY] = {0};
    DemoSlot repaired[AUTOPSY_CAPACITY] = {0};
    bool faulty_found;
    bool repaired_found;

    faulty[2] = (DemoSlot){10U, SLOT_OCCUPIED};
    faulty[3] = (DemoSlot){18U, SLOT_OCCUPIED};
    faulty[4] = (DemoSlot){26U, SLOT_OCCUPIED};

    /* Fault: deletion writes EMPTY and falsely ends the collision chain. */
    faulty[3] = (DemoSlot){0U, SLOT_EMPTY};

    repaired[2] = (DemoSlot){10U, SLOT_OCCUPIED};
    repaired[3] = (DemoSlot){0U, SLOT_DELETED};
    repaired[4] = (DemoSlot){26U, SLOT_OCCUPIED};

    faulty_found = bounded_lookup(faulty, 26U);
    repaired_found = bounded_lookup(repaired, 26U);

    (void)printf(
        "Faulty EMPTY deletion finds key 26: %s\n",
        faulty_found ? "yes" : "no"
    );
    (void)printf(
        "Repaired DELETED tombstone finds key 26: %s\n",
        repaired_found ? "yes" : "no"
    );

    if (faulty_found || !repaired_found) {
        (void)fputs("Autopsy fixture did not expose the intended fault.\n", stderr);
        return 1;
    }
    puts("The empty slot stopped probing early; the tombstone preserved it.");
    return 0;
}
