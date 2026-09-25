char stack[10];
int capacity = 10;
int size = 0;

int is_full() {
    return size == capacity;
}

void push(char data) {
    if (is_full()) {
        return;
    }
    stack[size] = data;
    size += 1;
}

int is_empty() {
    return size == 0;
}

char peek() {
    if (is_empty()) {
        return '\0';
    }
    return stack[size - 1];
}

char pop() {
    if (is_empty()) {
        return '\0';
    }
    char data = stack[size - 1];
    size -= 1;
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
int postfix_size = 0;

void infix_to_postfix() {
    postfix_size = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (c >= '0' && c <= '9') {
            postfix[postfix_size++] = c;
        }
        else {
            char op = peek();
            while (prec(op) >= prec(c)) {
                postfix[postfix_size++] = pop();
                op = peek();
            }
            push(c);
        }
    }
    while (!is_empty()) {
        postfix[postfix_size++] = pop();
    }
    postfix[postfix_size] = '\0';
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
    int value_size = 0;

    for (int i = 0; i < postfix_size; i++) {
        char c = postfix[i];
        if (c >= '0' && c <= '9') {
            values[value_size++] = c - '0';
        }
        else {
            int num2 = values[--value_size];
            int num1 = values[--value_size];
            values[value_size++] = calc(num1, num2, c);
        }
    }

    return values[--value_size];
}
