int stack[10];
int capacity = 10;
int top = 10;

void push(int data) {
    top -= 1;
    stack[top] = data;
}

int is_full() {
    return top == 0;
}

int peek() {
    return stack[top];
}

int is_empty() {
    return top == 10;
}

int pop() {
    int data = stack[top];
    top += 1;
    return data;
}

