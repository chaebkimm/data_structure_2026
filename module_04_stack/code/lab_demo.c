/* Entry point for the instructional functions in ../student/lab.c. */
#include <stdio.h>

extern char infix[8];
extern char postfix[8];
extern int size;

void infix_to_postfix(void);
int eval_postfix(void);

int main(void)
{
    infix_to_postfix();
    (void)printf("infix: %s\n", infix);
    (void)printf("postfix: %s\n", postfix);
    (void)printf("size: %d\n", size);
    (void)printf("result: %d\n", eval_postfix());
    return 0;
}
