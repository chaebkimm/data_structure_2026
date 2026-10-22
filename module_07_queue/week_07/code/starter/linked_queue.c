#include "support.h"
#include <stdint.h>

LqStatus lq_enqueue(LinkedQueue *q, int value)
{
    /* TODO 1: Reject NULL and size overflow; allocate before changing links.
     * Handle empty/nonempty tail, then commit tail and size. */
    (void)q;
    (void)value;
    return LQ_ARGUMENT;
}

LqStatus lq_dequeue(LinkedQueue *q, int *out)
{
    /* TODO 2: Check arguments and empty first. Save the value and next link,
     * advance head, update size, clear tail on final removal, release old,
     * and publish the output last. */
    (void)q;
    (void)out;
    return LQ_ARGUMENT;
}
