# Chapter 13. Finding a Specific ID in a Small Array

## Thinking Logically

### Can we just use large ID numbers directly as array positions?

When we mapped out graph locations, our numbers simply went in order starting from 0. Even if we used the location number itself directly as the array slot position, almost every single slot was filled.

This time, we are dealing with random ID numbers decided completely outside our program. We might connect a data value of `-4` to an ID number `18`, and later change the value at that exact same ID to `70`.

Because the ID number can represent massive numbers larger than 4 billion, if we only have a few actual data records to save but we force the computer to create an array slot for *absolutely every possible* ID number, almost all of our computer memory will sit completely empty and wasted. We absolutely must find a way to crunch these big ID numbers down mathematically to calculate a starting position inside a much smaller array.

### How many values do we connect to one ID?

We strictly connect exactly one value to one ID, and we never allow duplicate copies of the exact same ID to stay alive in our storage at the same time.

```text
put(18, -4)  Put in a brand new record for ID 18.
put(18, 70)  Change the already existing value to 70.
get(18)      Look up the value and find 70.
```

Our single tool handles both dropping in a new ID and updating an old ID. If its final report says it successfully added a new one, it was a brand new ID. If not, it simply updated the old value.

### How do we choose the very first slot to check?

Let's call the total number of slots we have our `capacity`, and the very first slot the ID wants to visit its `home`. In this chapter, we use this simple math trick to crunch the massive number down:

```text
home = ID % capacity
```

If our capacity is exactly 8, the starting slot for IDs `10`, `18`, and `26` is always exactly `2`. Notice that completely different IDs can easily bump into each other by getting the exact same starting slot!

### What if the starting slot is already full?

If the spot you want is already full, just start from that slot and check the next slots one by one to the right. If you hit the very end of the array, simply loop all the way back around to slot 0 and keep looking.

```text
index = (home + steps taken) % capacity
```

If we put in IDs `10`, `18`, and `26` in that exact order, it looks exactly like this:

```text
10: Checks 2 and saves perfectly at 2.      (Checked 1 time)
18: Checks 2, 3 and saves safely at 3.      (Checked 2 times)
26: Checks 2, 3, 4 and saves safely at 4.   (Checked 3 times)

Position   0  1  2   3   4   5  6  7
ID Tag           10  18  26
```

Every search strictly refuses to repeat more times than our total `capacity`. For IDs `7`, `15`, and `23` that all mathematically start at slot 7, they perfectly wrap around and are placed at 7, 0, and 1. We cleverly never try to read slot 8, which is completely outside our array!

### When can we safely stop searching if we see an empty slot?

If you check a slot and see that it is completely pristine and has *never* been used before, you can safely stop searching. An ID that started its journey before this blank slot could never have magically skipped over it to be saved further down the line!

However, an empty slot where an old record was *deleted* is completely different. Let's say IDs `10`, `18`, and `26` are sitting at slots 2, 3, and 4, and we suddenly delete `18`. If we stop searching the moment we see the empty hole at slot 3, we will completely miss the `26` sitting just past it at slot 4!

To fix this, we strictly save one of three distinct states for every single slot:

```text
EMPTY       A completely pristine slot that has never been used.
OCCUPIED    A slot holding a living ID and value.
DELETED     A slot where the record was deleted, but the search must NOT stop.
```

The `DELETED` state acts exactly like a placeholder marker. The deleted ID and value are erased back to 0, but its state is absolutely not changed back to `EMPTY`. Because an ID of `0` is a perfectly legal number, we never try to guess if a slot is empty just by looking at the numbers inside it! We strictly look at the state.

### Should we drop a new ID in as soon as we see a deleted placeholder?

While searching for a spot to put a new ID, you must carefully remember the physical position of the very first deleted placeholder you walk past. But do not stop! Keep searching until you either find the exact same ID already living in the array, or you hit a pristine `EMPTY` slot.

```text
Slot 2: ID 10
Slot 3: Deleted placeholder (Old ID 18)
Slot 4: ID 26
Slot 5: Pristine EMPTY slot
```

If we try to update `26` to `999`, it must walk past the placeholder to change the living value currently at slot 4. If you blindly dropped it into the placeholder at slot 3 right away, you would accidentally create two duplicate copies of ID 26!

If we try to add a brand new ID `34`, it keeps searching until it checks the pristine `EMPTY` slot 5. Once it confirms `34` is truly not living anywhere in the array, *only then* does it go back and cleverly reuse the deleted placeholder at slot 3 that it remembered walking past earlier. When this finally happens, our total count of living items goes up by one, and our placeholder count goes down by one.

### What do we do if the array is cluttered with too many deleted placeholders?

If there are too many living records and deleted placeholders cluttering the array, it will take a miserably long time to finally hit a pristine `EMPTY` slot. To keep things fast, our code strictly forces the sum of both living records and deleted placeholders to stay at or below 3/4 (75%) of the total capacity.

If dropping a new ID into an `EMPTY` slot would break this strict limit, we pause and completely rebuild the array first.

* If there are only a few living records but the array is cluttered with deleted placeholders, we rebuild it using the exact same capacity just to sweep away the placeholders.
* If there are too many living records, we double the capacity following the pattern: `8, 16, 32, 64`.
* We *never* rebuild when we are simply reusing an existing placeholder or updating an already living ID!

When the capacity number changes, the math crunch (`ID % capacity`) changes completely! Because of this, we must throw every single living ID back into the math machine and find its brand-new starting slot. If you lazily copied them into the exact same physical slot numbers as before, the search paths would be completely shattered!

### Can we keep adding items forever?

At our strict maximum capacity of 64, the combined limit of living records and deleted placeholders is strictly capped at 48. If there are deleted placeholders cluttering the space, we can easily clear them out by rebuilding at the same capacity of 64.

But if there are absolutely zero deleted placeholders and exactly 48 living records packed in, a 49th brand-new ID will demand a bigger array. Since we strictly refuse to exceed 64, we safely reject the new ID and return a "full" error. However, because updating an already living ID's value uses zero extra space, you can keep doing that freely forever!

### What if the computer fails to build the new array?

If we excitedly throw away our old array first, and then the computer fails to give us memory for the new array, we will permanently lose absolutely every single record! We must follow this ultra-safe order:

```text
1. Ask the computer for a brand-new empty array.
2. Carefully move only the living records from the old array into the new one.
3. Drop the brand-new ID into the new array too.
4. If absolutely everything succeeds, smoothly swap the old array for the new one.
5. Only then, safely throw the old array in the trash.
```

If it fails halfway through, we simply throw the unfinished new array in the trash. The old array, the size counts, the capacities, and the user's output variables remain perfectly untouched and safe.

Trying to find or delete an ID that doesn't actually exist is completely normal and not an error. We simply report that it wasn't found or removed, and hand back a value of 0. We strictly only protect the user's output variables when the tool genuinely fails due to limits or memory issues!

## Calculating Efficiency

### Efficiency of calculating the starting slot?

Because we crunch the starting slot using a single fast math operation, it takes instantly fast $O(1)$ time.

### Efficiency of searching, inserting, and deleting IDs?

If IDs are mathematically spread out nicely across the starting slots and we strictly limit how cluttered the array gets, the average number of slots we have to check stays incredibly small. Because of this, the typical expected work to find, drop, or remove an ID is amazingly fast, $O(1)$.

*(Note: "Expected cost" is a mathematical average across many possible ID mixtures. This is a different idea from the "amortized cost" we learned earlier, which spreads a rare but heavy task over a long timeline of guaranteed calls).*

### What happens if the IDs all crash into one spot?

If our capacity is `m` and absolutely all IDs magically end up getting the exact same starting slot, a single simple request might be forced to check the entire array. This worst-case scenario takes $O(m)$ work.

A clever attacker outside your program could intentionally slow your computer down by deliberately choosing IDs that they know will crash into the exact same slot! The simple math we use in this chapter is just to easily show how the basic idea works.

### Efficiency of rebuilding the array?

Because we must carefully check the entire old array to find and move every single living record to the new array, it takes $O(m)$ work. We only do this heavy lifting when we absolutely must clear deleted placeholders or expand the space.

### Efficiency of double-checking the entire system?

Our safety diagnostic tool checks if the status counts match the real numbers, hunts for duplicate IDs, and verifies the exact search path for every single ID! Because our current code might recheck the exact same paths from every single living slot, the worst-case scenario takes massive $O(m^2)$ work. We normally never run this heavy, exhausting diagnostic during regular, everyday actions!

## Glossary

### Key

An identification value used to find its connected value.

### Value

The data that is connected to a key and stored.

### Map

A data structure that connects exactly one value to one key, and provides actions to find or change it.

### Hash Function

A calculation that turns a key into the starting slot of an array.

### Hash Table

A data structure that uses a hash function to find starting slots and stores keys and values in an array.

### Collision

When completely different keys happen to get the exact same starting slot.

### Linear Probing

A method that handles a collision by simply checking the next array slots one by one.

### Tombstone

A state showing that a slot was deleted, without breaking the search path for other keys that follow it.

### Rehashing

The process of recalculating the starting slot for every key using a new capacity and placing them again.

### Expected Cost

The amount of work calculated as an average across many possible situations, based on assumptions about how the keys are arranged.

## Coding Plan

### Creating the Array Table

* **Check initial state:** Make sure every single field in the table structure is completely clean (`0`).
* **Create minimum array:** Use the `calloc` tool to grab exactly 8 perfectly pristine slots where all states start at `0` (`HASH_SLOT_EMPTY`).
* **Record fields:** Update the `slots` memory address and `capacity`, leaving `size` and `tombstones` safely at `0`.

### Probing (Walking) for an ID

* **Calculate starting slot:** Crunch the math `key % capacity`.
* **Remember tombstone:** Save the exact physical position of the very first `HASH_SLOT_DELETED` placeholder you walk past.
* **Check exact match:** If you see an `OCCUPIED` slot and the key matches perfectly, return that exact position.
* **Check empty:** If you hit an `EMPTY` slot, you are absolutely certain the key does not exist.
* **Decide insert position:** If you remembered a deleted placeholder earlier, pick that slot to safely reuse. If not, pick the `EMPTY` slot.
* **Limit repetition:** Absolutely never check more times than the total `capacity`.

### Putting an ID and Value

* **Update existing key:** If you found the key, change only its connected value, and securely report `inserted=false`.
* **Decide maintenance:** If adding a brand-new key breaks our 3/4 clutter limit, either rebuild the array to clear placeholders or double the capacity to make room.
* **Finish new array:** Only swap the old array for the new array after every living record and the brand-new key are perfectly placed inside the new memory.
* **Use empty slot:** Write the new key and value into the chosen slot, and permanently change its state directly to `OCCUPIED`.
* **Update counts:** If you cleverly reused a placeholder, decrease the tombstone count by 1. Always increase the `size` count by 1.

### Finding an ID

* **Run probe:** Keep checking slots until you hit the exact matching key or a pristine `EMPTY` slot.
* **Make success result:** If found, report `found=true` and hand back the value. If not found, report `found=false` and hand back `0`.
* **Record probe count:** Save the exact number of slots you checked into `probe_count` so the user can see how fast it was.

### Deleting an ID

* **Find key:** Find the exact slot holding the key using the same bumping rules.
* **Record deleted state:** Completely erase the key and value to `0`, and switch the state officially to `HASH_SLOT_DELETED`.
* **Update counts:** Decrease the `size` count by 1, and increase the `tombstones` count by 1.
* **Handle missing key:** If the key didn't exist, do absolutely nothing to the table, and just calmly report `removed=false`.

## C Code

### Representing One Slot in the Table

```c
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

```

### Walking Around the End of the Array

```c
size_t home = (size_t)key % table->capacity;
size_t first_deleted = SIZE_MAX;
size_t found_index = SIZE_MAX;
size_t insertion_index = SIZE_MAX;
bool found = false;

for (size_t step = 0U; step < table->capacity; step = step + 1U) {
        size_t index = (home + step) % table->capacity;
        const HashSlot *slot = &table->slots[index];

        if (slot->state == HASH_SLOT_OCCUPIED && slot->key == key) {
                found_index = index;
                found = true;
                break;
        }

        if (slot->state == HASH_SLOT_DELETED &&
                first_deleted == SIZE_MAX) {
                first_deleted = index;
        }

        if (slot->state == HASH_SLOT_EMPTY) {
                insertion_index = first_deleted == SIZE_MAX
                        ? index
                        : first_deleted;
                break;
        }
}
```

### Changing a Found Record into a Deleted Placeholder

```c
HashSlot *slot = &table->slots[found_index];

slot->key = 0U;
slot->value = 0;
slot->state = HASH_SLOT_DELETED;
table->size = table->size - 1U;
table->tombstones = table->tombstones + 1U;
```

### Swapping After the New Array is Finished Perfectly

```c
HashSlot *old_slots = table->slots;

table->slots = new_slots;
table->size = table->size + 1U;
table->tombstones = 0U;
table->capacity = new_capacity;

free(old_slots);
```