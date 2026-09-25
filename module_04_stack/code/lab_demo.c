/* Entry point for the instructional functions in ../student/lab.c. */
#include <stdio.h>

extern char eq[8];
extern char eq_re[8];

void infix_to_postfix(void);
int eval_postfix(void);

int main(void)
{
    infix_to_postfix();
    (void)printf("infix: %s\n", eq);
    (void)printf("postfix: %s\n", eq_re);
    (void)printf("result: %d\n", eval_postfix());
    return 0;
}
