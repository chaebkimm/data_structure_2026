/* Entry point for the instructional functions in ../student/lab.c. */
#include <stdio.h>

extern char eq[8];
extern char postfix[8];
extern char eq_paren[8];

void convert_to_postfix(void);
void infix_to_postfix_parentheses(void);
int eval_postfix(void);

int main(void)
{
    convert_to_postfix();
    (void)printf("infix: %s\n", eq);
    (void)printf("postfix: %s\n", postfix);
    (void)printf("result: %d\n", eval_postfix());
    infix_to_postfix_parentheses();
    (void)printf("infix with parentheses: %s\n", eq_paren);
    (void)printf("postfix: %s\n", postfix);
    (void)printf("result: %d\n", eval_postfix());
    return 0;
}
