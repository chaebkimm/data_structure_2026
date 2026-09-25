int stack[10];
int capacity = 10;
int size = 0;

void push(int data) {stack[size++] = data;}

int peek() {return stack[size - 1];}
int pop() {return stack[--size];}

int is_full() {return size == capacity;}
int is_empty() {return size == 0;}

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
    size = 0;
    push('\0');
    for (int i = 0; i < 7; i++) {
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
    size = 0;

    for (int i = 0; i < 7; i++) {
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
