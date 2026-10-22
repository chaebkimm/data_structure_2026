#include "linked_queue.h"
#include <assert.h>

int main(void)
{
    /* Add the three cases required by the lab. */
    LinkedQueue q = {0};
    assert(lq_is_valid(&q));
    lq_destroy(&q);
    return 0;
}
