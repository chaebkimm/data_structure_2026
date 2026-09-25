char stack[10];
int capacity = 10;
int top = 10;

int is_full() {
    return top == 0;
}

void push(char data) {
    if (is_full()) {
        return;
    }
    top -= 1;
    stack[top] = data;
}

int is_empty() {
    return top == 10;
}

char peek() {
    if (is_empty()) {
        return '\0';
    }
    return stack[top];
}

char pop() {
    if (is_empty()) {
        return '\0';
    }
    char data = stack[top];
    top += 1;
    return data;
}

int prec(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/' || op == '%') {
        return 2;
    }
    return 0;
}

char infix[8] = "1-2*3+4";

char postfix[8] = "";
int size = 0;

void infix_to_postfix() {
    size = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (c >= '0' && c <= '9') {
            postfix[size++] = c;
        }
        else {
            char op = peek();
            while (prec(op) >= prec(c)) {
                postfix[size++] = pop();
                op = peek();
            }
            push(c);
        }
    }
    while (!is_empty()) {
        postfix[size++] = pop();
    }
    postfix[size] = '\0';
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
    int values[10];
    int pos = 0;

    for (int i = 0; i < size; i++) {
        char c = postfix[i];
        if (c >= '0' && c <= '9') {
            values[pos++] = c - '0';
        }
        else {
            int num2 = values[--pos];
            int num1 = values[--pos];
            values[pos++] = calc(num1, num2, c);
        }
    }

    return values[--pos];
}