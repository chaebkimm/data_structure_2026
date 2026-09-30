int stack[10];
int capacity = 10;
int top = -1;

void push(int data) {stack[++top] = data;}

int peek() {return stack[top];}
int pop() {return stack[top--];}

int is_full() {return top + 1 == capacity;}
int is_empty() {return top == -1;}

int prec(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/' || op == '%') {
        return 2;
    }
    return 0;
}

char eq[8] = "1-2*3+4";
char eq_re[8] = "";

void infix_to_postfix() {
    int pos = 0;
    top = -1;
    push('\0');
    for (int i = 0; eq[i] != '\0'; i++) {
        char c = eq[i];

        if (c >= '0' && c <= '9') {
            eq_re[pos++] = c;
        }
        else {
            char op = peek();
            while (prec(op) >= prec(c)) {
                eq_re[pos++] = pop();
                op = peek();
            }
            push(c);
        }
    }
    while (!is_empty()) {
        eq_re[pos++] = pop();
    }
}

int calc(int num1, int num2, int op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        case '%': return num1 % num2;        
    }
    return 0;
}

int eval_postfix() {
    top = -1;

    for (int i = 0; eq_re[i] != '\0'; i++) {
        char c = eq_re[i];
        if (c >= '0' && c <= '9') {
            push(c - '0');
        }
        else {
            int num2 = pop();
            int num1 = pop();
            push(calc(num1, num2, c));
        }
    }

    return pop();
}

char eq_paren[8] = "1+(2+3)";

void infix_to_postfix_parentheses() {
    int pos = 0;
    top = -1;
    push('\0');
    for (int i = 0; eq_paren[i] != '\0'; i++) {
        char c = eq_paren[i];

        if (c >= '0' && c <= '9') {
            eq_re[pos++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            char op = peek();
            while (op != '(') {
                eq_re[pos++] = pop();
                op = peek();
            }
            pop();
        }
        else {
            char op = peek();
            while (prec(op) >= prec(c)) {
                eq_re[pos++] = pop();
                op = peek();
            }
            push(c);
        }
    }
    while (!is_empty()) {
        eq_re[pos++] = pop();
    }
}
