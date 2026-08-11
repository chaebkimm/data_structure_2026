#include <stdio.h>
#include <stdlib.h>

typedef struct AutopsyNode {
    int value;
    struct AutopsyNode *next;
} AutopsyNode;

int main(void)
{
    AutopsyNode *r = (AutopsyNode *)malloc(sizeof *r);
    AutopsyNode *q = (AutopsyNode *)malloc(sizeof *q);
    AutopsyNode *p = (AutopsyNode *)malloc(sizeof *p);
    AutopsyNode *previous;
    AutopsyNode *victim;
    AutopsyNode *cleanup_tail;

    if (r == NULL || q == NULL || p == NULL) {
        free(r);
        free(q);
        free(p);
        fputs("Autopsy setup allocation failed.\n", stderr);
        return 1;
    }

    r->value = 17;
    r->next = q;
    q->value = 23;
    q->next = p;
    p->value = 31;
    p->next = NULL;
    previous = r;
    victim = q;

    /*
     * This independently saved pointer is used only to release P after the
     * isolated faulty step. It is not used to repair previous->next.
     */
    cleanup_tail = p;

#ifdef AUTOPSY_INSPECT_ONLY
    AutopsyNode *saved_next = victim->next;

    puts("INSPECT ONLY: R(17) -> Q(23) -> P(31), remove middle Q.");
    puts("Safe repair: save Q.next, set R.next, then free Q once.");
    previous->next = saved_next;
    free(victim);
    free(cleanup_tail);
    free(previous);
    return 0;
#else
    /*
     * Intentional bounded defect: exactly one field read occurs after free.
     * This branch is isolated from every normal build and test target.
     */
    free(victim);
    previous->next = victim->next;

    free(cleanup_tail);
    free(previous);
    return 0;
#endif
}
