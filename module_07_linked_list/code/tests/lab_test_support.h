#ifndef MODULE_07_LAB_TEST_SUPPORT_H
#define MODULE_07_LAB_TEST_SUPPORT_H
#include <assert.h>
#include <stdio.h>
#include "lab.c"

static void reset_lab(void)
{
    /* No live node users remain from the preceding independent test. */
    init_lnodes_pool();
    head = tail = -1;
}
#endif
