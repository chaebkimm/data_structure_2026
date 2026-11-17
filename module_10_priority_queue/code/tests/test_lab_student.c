#include <assert.h>
#include <stdio.h>
#include "lab.c"

int main(void)
{
    /* Supplied smoke check, not original student evidence. Add one focused
       regression with a prediction and the defect it would detect. Use valid
       ordered half-open intervals and stay within cumulative queue capacity.
       If changing timelogs, save and restore the original sample. */
    assert(survey() == 12);
    assert(survey() == 12);
    assert(front == 7 && rear == 8);
    puts("Chapter 10 student smoke passed; add one original regression.");
    return 0;
}
