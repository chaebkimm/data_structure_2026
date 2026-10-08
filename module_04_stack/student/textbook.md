# Chapter 4. Taking Out the Last Value First

We will store items so that only the newest remaining item can be read or removed. Then we will use that rule to decide when to calculate an expression.

## Thinking Logically

### Why do we need a special order?

Place three plates on a pile. To remove a plate from the top, take the most recently added plate first. The older plates stay in place. A list can store the plates' names, but allowing removal at any position does not describe this rule.

We need to add, read, and remove items at one end only. Taking out the newest remaining item first is last-in first-out, or LIFO. A data structure that follows this rule is a stack. Its accessible end is the top. Adding an item is `push`, reading the top without removing it is `peek`, and removing the top is `pop`.

### How can an array keep this order?

We already know how to put list items into adjacent array cells. Keep the stack's items in the same way, beginning at index 0. Record the index of the last occupied cell in `top`.

An empty stack has no last occupied cell, so `top` starts at -1. After adding `'A'`, `'B'`, and `'C'`, the cells at indexes 0, 1, and 2 hold those values. The top index is 2, and the item count is `top + 1`, which is 3. The index and the count are different.

### How do we add, read, and remove an item?

To add an item, increase `top` first and write at the new index. To read the newest item, read `stack[top]`. To remove it, read the current cell and then decrease `top`. The earlier cells do not move.

| Action | Active items, bottom to top | `top` | Item count | Returned value |
|---|---|---:|---:|---|
| Start | none | -1 | 0 | — |
| `push('A')` | A | 0 | 1 | — |
| `push('B')` | A, B | 1 | 2 | — |
| `push('C')` | A, B, C | 2 | 3 | — |
| `peek()` | A, B, C | 2 | 3 | `'C'` |
| `pop()` | A, B | 1 | 2 | `'C'` |

Removing `'C'` does not erase its old cell. The active part of the array now ends at index 1. A later push can overwrite index 2.

### What happens at the boundaries?

Ten array cells can hold ten items. The stack is full at `top == 9`, because `top + 1 == capacity`. It is empty at `top == -1`.

Adding to a full stack is an overflow. Reading or removing from an empty stack is an underflow. The lab provides `is_full` and `is_empty` to report those states, but the operations do not call them automatically. A push on the full stack would write at index 10. A peek or pop on the empty stack would read index -1. These accesses are outside the array; no defined failure result or unchanged state is promised.

The rule to preserve is `-1 <= top < capacity`, with active items at indexes 0 through `top`. This is the stack's invariant. Only the last active item is accessible through the stack operations.

### How does this relate to function calls?

When a function calls another function, the older call must resume after the newer call finishes. Nested calls therefore finish in the same last-in first-out order. The information needed to resume one call is called a call frame. This comparison explains the order; the lab's integer array is not the runtime's call stack.

### When should an expression's operators be calculated?

Consider `1-2*3+4`. Calculating every operator as soon as it appears would subtract before the multiplication is ready. Multiplication has higher precedence, so `2*3` must be calculated first. Subtraction and addition have equal precedence and are processed from left to right. This rule is left associativity.

Writing the grouping explicitly gives `((1-(2*3))+4)`. A closing parenthesis finishes the most recently opened group that is still unfinished. That order is another use for a stack.

### How can two stacks calculate the expression directly?

Separate the waiting operators from the numbers. Read the input from left to right. Save a number when it appears. Before saving a new operator, finish waiting operators whose precedence is at least as high as the new operator's precedence. To finish an operation, remove its operator, remove the right number, remove the left number, calculate, and save the result.

In `1-2*3+4`, the `-` waits when `*` arrives. When `+` arrives, finish `2*3` to obtain 6, then `1-6` to obtain -5. Save `+`, read 4, and finish `-5+4` to obtain -1. This direct method motivates the order used next. The lab instead separates conversion and evaluation into two phases that reuse one global stack.

### What if each operator follows the values it needs?

An operator usually appears between its operands, the values used by the operation. That order is infix notation. We can instead write an operator after both operands. This is postfix notation.

Write each digit when it is read. Write each waiting operator when the direct two-stack method would calculate it. Then `1-2*3+4` becomes `123*-4+`. The `*` follows 2 and 3. The `-` follows 1 and the multiplication result. The final `+` follows the subtraction result and 4.

### How do we build that order without calculating?

Use a stack only for waiting operators. Copy digits directly to the output. Before pushing a new operator, look at waiting operators while the stack is not empty. If the top operator has lower precedence, stop. Otherwise, pop it and copy it to the output. Equal precedence therefore removes the older operator first and preserves left associativity.

The code checks whether the stack is empty before reading its top. After reading the input, pop the remaining operators into the output. Then write the null character `'\0'` directly after the output characters to end the string.

The table shows only the characters written so far. Intermediate output need not be a terminated string, especially when the buffer is being reused.

| Input or action | Output so far | Operator stack, bottom to top | `top` |
|---|---|---|---:|
| Start | empty | empty | -1 |
| `1` | `1` | empty | -1 |
| `-` | `1` | `-` | 0 |
| `2` | `12` | `-` | 0 |
| `*` | `12` | `-`, `*` | 1 |
| `3` | `123` | `-`, `*` | 1 |
| `+`: pop `*`, pop `-`, push `+` | `123*-` | `+` | 0 |
| `4` | `123*-4` | `+` | 0 |
| Drain `+` | `123*-4+` | empty | -1 |
| Write `'\0'` | `123*-4+` followed by `'\0'` | empty | -1 |

Without parentheses, waiting operators have strictly increasing precedence from bottom to top. An equal or higher predecessor is removed before a new operator is pushed.

### How do we calculate the rewritten expression?

Read the output from left to right. Convert each digit character to an integer and push it. For an operator, pop the right operand first, then the left operand. Push their calculated result.

| Input | Action | Active integer values, bottom to top | `top` |
|---|---|---|---:|
| Start | Reset the stack | none | -1 |
| `1` | Push 1 | 1 | 0 |
| `2` | Push 2 | 1, 2 | 1 |
| `3` | Push 3 | 1, 2, 3 | 2 |
| `*` | `2 * 3 = 6` | 1, 6 | 1 |
| `-` | `1 - 6 = -5` | -5 | 0 |
| `4` | Push 4 | -5, 4 | 1 |
| `+` | `-5 + 4 = -1` | -1 | 0 |
| Return the final pop | Return -1 | none | -1 |

Each stored value is the result of a completed part of the expression that a later operation may use. At a valid postfix operator, the top two values are its operands. This is not true at every earlier point in the scan; an operand may still be unread.

### How do parentheses change the conversion?

A group must finish before the surrounding operation. The second converter handles this boundary explicitly. It reads `1+(2+3)` from `eq_paren`.

Push `(` when it appears. Its precedence is 0, so an ordinary arithmetic-operator comparison stops at that boundary. On `)`, repeatedly pop an item while the stack is not empty. If the removed item is `(`, stop without copying it. Otherwise, copy the removed operator to the output. Neither parenthesis appears in a valid postfix result. Conversion writes operators; it does not calculate them.

| Input or action | Output so far | Operator stack, bottom to top | `top` |
|---|---|---|---:|
| Start | empty | empty | -1 |
| `1` | `1` | empty | -1 |
| `+` | `1` | `+` | 0 |
| `(` | `1` | `+`, `(` | 1 |
| `2` | `12` | `+`, `(` | 1 |
| `+` | `12` | `+`, `(`, `+` | 2 |
| `3` | `123` | `+`, `(`, `+` | 2 |
| `)`: pop and write `+`, pop and discard `(` | `123+` | `+` | 0 |
| Drain `+` | `123++` | empty | -1 |
| Write `'\0'` | `123++` followed by `'\0'` | empty | -1 |

The output is `123++`. The same evaluator first computes `2+3`, then `1+5`, and returns 6. Precedence increases only within each group of waiting arithmetic operators separated by `(`. It need not increase across a parenthesis boundary.

### Which inputs fit the supplied code?

The buffers each hold eight characters: at most seven input or output characters plus `'\0'`. The loops stop at the null character, so shorter valid expressions also work. For example, `2+3` converts to `23+` and evaluates to 5. A single digit is also a valid expression. An empty expression is not valid for evaluation.

Use single digits and the binary operators `+`, `-`, `*`, `/`, and `%`. Do not include spaces, multidigit operands, or unary signs. Negative intermediate integer results are allowed. `convert_to_postfix` accepts expressions without parentheses. Only `infix_to_postfix_parentheses` handles balanced parentheses. Parentheses count toward its seven-character input limit but are omitted from its output.

The code assumes valid syntax, enough stack and output space, and null-terminated input. Every operator must have two operands, and evaluation must finish with exactly one result. Division and remainder require a nonzero right operand. All integer arithmetic must remain representable, including the quotient required by division or remainder. These assumptions are not checked. The parentheses converter checks for an empty stack before each pop, but it does not report an unmatched closing parenthesis. It may drain operators and discard that closing parenthesis without finding a match. An unmatched opening parenthesis can be copied into the output. These behaviors do not validate the expression.

## Calculating Efficiency

### How much work does one stack operation do?

A push increments one index and writes one cell. A peek reads one cell. A pop reads one cell and decrements one index. Each boundary predicate performs a fixed number of arithmetic and comparison operations. No existing item moves, so each operation takes constant time, `O(1)`.

### Does a loop inside a loop repeat all the work?

In `1-2*3+4`, conversion reads seven characters. Each of the three operators is pushed once and popped once. That is three pushes and three pops. Writing the final null character adds one output write and no stack operation. Although one incoming operator can pop several predecessors, a removed operator is never popped again.

For an input of `n` characters, the total number of reads, pushes, and pops grows in proportion to `n`. Conversion takes `O(n)` time. In the parentheses version, each `(` is also pushed once and popped once. For `1+(2+3)`, the two operators and one opening parenthesis require three pushes and three pops. The same time bound holds.

Evaluation of `123*-4+` pushes four original numbers, performs three calculations, and returns one result. Each calculation uses two pops and one push. Including the final answer pop, the example performs seven pushes and seven pops. With `m` postfix characters, evaluation takes `O(m)` time. For `1+(2+3)`, seven input characters produce five postfix characters because the parentheses disappear.

### How much storage is reserved and used?

The lab reserves ten integers for `stack` and three arrays of eight characters for `eq`, `postfix`, and `eq_paren`. That reservation stays fixed even when an expression is short. Only the active prefix, whose length is `top + 1`, contains current stack items. Resetting `top` does not erase the cells.

The first conversion uses at most two active stack cells, with a maximum `top` of 1. Its evaluation uses at most three. The parentheses example uses at most three during conversion, with a maximum `top` of 2, and three during evaluation. Conversion and evaluation reuse the same integer array sequentially.

For a version whose buffers grow with the input, the worst-case operator or operand stack and output each need `O(n)` space. The supplied fixed arrays reserve constant space and impose a fixed capacity; they cannot handle arbitrary input lengths.

## Glossary

The operations and expression rules now have concrete examples. The table collects their names.

| Term | Meaning in this chapter |
|---|---|
| Stack / 스택 | Stores items that can be read or removed only at the newest end |
| LIFO / 후입선출 | Removes the newest remaining item first |
| Top / 마지막 데이터 위치 | `top` is the last active index; -1 means empty |
| Push / 추가 | Increases `top` and stores a new item |
| Peek / 확인 | Reads `stack[top]` without changing the stack |
| Pop / 삭제 | Returns `stack[top]` and decreases `top` |
| Overflow / 오버플로 | Adding an item when no cell is available |
| Underflow / 언더플로 | Reading or removing an item from an empty stack |
| Invariant / 불변식 | A rule maintained by every valid operation |
| Null terminator / 널 종료 문자 | `'\0'` written after the output characters to end the string |
| infix | Places an operator between its operands |
| postfix | Places an operator after its operands |
| Operand / 피연산자 | A value used by an operation |
| Operator / 연산자 | Selects an operation to apply to values |
| Precedence / 우선순위 | Determines which operations must happen first |
| Left associativity / 좌측결합 | Processes equal-precedence operators from left to right |
| Call frame / 호출 프레임 | Information needed to resume a function call |

## Coding Plan

Build the stack helpers first. Then convert an expression and evaluate the output. Finally, add the converter that recognizes parentheses. Both converters write the same output buffer and reuse the same integer stack as evaluation.

1. **Store and access stack items.** Declare `stack[10]`, `capacity = 10`, and `top = -1`. Implement `push` with `stack[++top]`, `peek` with `stack[top]`, and `pop` with `stack[top--]`. Report full with `top + 1 == capacity` and empty with `top == -1`.
2. **Prepare precedence and expression storage.** Return 1 for `+` and `-`, 2 for `*`, `/`, and `%`, and 0 otherwise. Store the first input in `eq` and reserve `postfix` for output.
3. **Convert the first expression.** Reset `top` to -1 and read `eq` until its terminator. Copy digits directly. While the stack is not empty, stop if the top operator has lower precedence; otherwise pop and write it. Push the incoming operator. Drain remaining operators and explicitly write `'\0'` to end the output.
4. **Calculate one operation.** Let `calc` select the arithmetic operation on its left and right integer arguments.
5. **Evaluate the postfix output.** Reset `top` and read `postfix` until its terminator. Push each digit's integer value. For an operator, pop `num2`, then `num1`, and push `calc(num1, num2, c)`. Pop and return the final answer.
6. **Convert an expression with parentheses.** Read `eq_paren`. Keep the same digit and arithmetic-operator handling. Push `(` directly. On `)`, pop an item while the stack is not empty. Stop if the removed item is `(`; otherwise write it to the output. Drain the remaining operators into `postfix`, then explicitly write `'\0'`.

## C Code

The following six blocks reproduce `lab.c` in source order. The lab defines helpers and global storage; a separate driver provides `main`.

### 1. Store and access the newest item

The array reserves ten integer cells. `capacity` records that limit; changing it does not resize the array. `top` identifies the active cells independently of their contents. Global array cells initially contain zero, but `top == -1` makes the stack empty.

```c
int stack[10];
int capacity = 10;
int top = -1;

void push(int data) {stack[++top] = data;}

int peek() {return stack[top];}
int pop() {return stack[top--];}

int is_full() {return top + 1 == capacity;}
int is_empty() {return top == -1;}
```

`++top` increments before providing an index. Starting at -1, the first push writes to index 0. `top--` provides the old index and then decrements. Starting at 2, pop reads index 2 and leaves `top == 1`. The expression returns the stored integer, not the new index.

`is_full` and `is_empty` return 1 when their comparisons are true and 0 otherwise. They change no state. The caller must use them when necessary; the other helpers are unchecked.

### 2. Assign precedence and reserve strings

The converter needs to compare waiting operators with the new one. The function supplies small integer levels for that comparison. An opening parenthesis receives 0, so arithmetic operators inside the group leave it in place.

```c
int prec(char op) {
    switch (op) {
        case '*': case '/': case '%':
            return 2;
        case '+': case '-':
            return 1;
        default:
            return 0;
    }
}

char eq[8] = "1-2*3+4";
char postfix[8] = "";
```

`switch` selects the matching `case` label. The consecutive `*`, `/`, and `%` labels share `return 2;`. The `+` and `-` labels share `return 1;`. Each `return` ends the function, so these branches need no `break`. `default` handles all other characters and returns 0.

Returning 0 is not input validation. The converter can store an unsupported character and copy it into the output. The `!is_empty()` checks prevent its comparison loop from reading an empty stack, but they do not reject malformed expressions. In the digit test used below, `&&` requires both bounds to hold.

The string `"1-2*3+4"` contains seven visible characters followed by `'\0'`. Single quotes denote one character; double quotes denote a string. The null character has value zero and differs from the digit character `'0'`. The initially empty output array has eight zero-valued cells.

### 3. Write the postfix order

Conversion starts with a fresh output position and a fresh active stack. It does not need the caller to clear the stack. It does not erase the output buffer in advance; it writes a new terminated result.

```c
void convert_to_postfix() {
    int pos = 0;
    top = -1;
    for (int i = 0; eq[i] != '\0'; i++) {
        char c = eq[i];
        if (c >= '0' && c <= '9') {
            postfix[pos++] = c;
        }
        else {
            while (!is_empty()) {
                char op = peek();
                if (prec(op) < prec(c)) {
                    break;
                }
                postfix[pos++] = pop();
            }
            push(c);
        }
    }
    while (!is_empty()) {
        postfix[pos++] = pop();
    }
    postfix[pos++] = '\0';
}
```

`pos` is the next output index. `postfix[pos++] = c;` writes at its old value and then increases it. `top = -1;` discards the previous active stack contents. The stack stays empty until the first operator is pushed.

The `for` loop tests `eq[i] != '\0'`, so the actual string length determines its iterations. For `1-2*3+4`, it reads indexes 0 through 6. When an operator arrives, `while (!is_empty())` permits `peek()` only while a waiting item exists. If `prec(op) < prec(c)`, `break` exits this inner `while` loop. It does not exit the surrounding `for` loop or return from the function. Execution continues at `push(c)`.

Otherwise, `postfix[pos++] = pop();` writes the waiting operator. The next iteration checks emptiness again before declaring a new `op` with `peek()`. Equal precedence does not satisfy the lower-precedence condition, so the older operator is removed first.

| Step at the incoming `+` | Output so far | `pos` | `top` |
|---|---|---:|---:|
| Before popping | `123` | 3 | 1 |
| Pop `*` | `123*` | 4 | 0 |
| Pop `-` | `123*-` | 5 | -1 |
| Empty stack ends the loop; push `+` | `123*-` | 5 | 0 |

After reading 4, `pos == 6`. The final loop pops `+` into `postfix[6]` and leaves `top == -1`, `pos == 7`. Since the stack is now empty, that loop ends. The separate statement `postfix[pos++] = '\0';` writes the terminator at index 7 and advances `pos` to 8. It does not change `top`.

For a shorter input such as `2+3`, the output is `23+`, the terminator is at index 3, and the final `pos` is 4. Old bytes beyond that terminator may remain. The evaluator and string output stop at the new terminator and do not use those bytes.

### 4. Return the result of one integer operation

Once two integer operands are ready, the operator selects how to combine them. `num1` is the left operand and `num2` is the right operand.

```c
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
```

`switch` selects the matching `case` label. Each branch returns immediately, so no `break` is needed. The final 0 for an unknown operator is not an error report; zero can also be a valid result. The function assumes its operator and arithmetic are valid.

For the running example, `calc(2, 3, '*')` returns 6, `calc(1, 6, '-')` returns -5, and `calc(-5, 4, '+')` returns -1. Integer division makes `calc(7, 2, '/')` return 3; the corresponding remainder `calc(7, 2, '%')` is 1.

### 5. Reuse the stack for integer results

The converted string already determines the operation order. Evaluation therefore needs only the numbers and completed results. It resets the same stack to an empty state before reading the first digit.

```c
int eval_postfix() {
    top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
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
```

The loop stops at `postfix`'s actual null terminator. A digit becomes an integer through `c - '0'`; C guarantees consecutive values for digit characters. The subtraction must preserve operand order: the first pop gives the right operand 6, and the second gives the left operand 1, so the result is `1 - 6`.

| Operator in `123*-4+` | Right operand | Left operand | `top`: before → first pop → second pop → push |
|---|---:|---:|---|
| `*` | 3 | 2 | 2 → 1 → 0 → 1 |
| `-` | 6 | 1 | 1 → 0 → -1 → 0 |
| `+` | 4 | -5 | 1 → 0 → -1 → 0 |

A valid expression leaves one result at `stack[0]`, with `top == 0`. `return pop();` returns that result and leaves `top == -1`. Evaluation does not change the input or output strings. The function does not check whether operands are missing or extra results remain.

### 6. Keep operations inside their parentheses

The second converter must prevent an operation outside a group from being emitted before that group closes. It stores the opening parenthesis as a boundary and handles closing parentheses separately from arithmetic operators.

```c
char eq_paren[8] = "1+(2+3)";

void infix_to_postfix_parentheses() {
    int pos = 0;
    top = -1;

    for (int i = 0; eq_paren[i] != '\0'; i++) {
        char c = eq_paren[i];

        if (c >= '0' && c <= '9') {
            postfix[pos++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (!is_empty()) {
                char op = pop();
                if (op == '(') {
                    break;
                }
                postfix[pos++] = op;
            }
        }
        else {
            while (!is_empty()) {
                char op = peek();
                if (prec(op) < prec(c)) {
                    break;
                }
                postfix[pos++] = pop();
            }
            push(c);
        }
    }
    while (!is_empty()) {
        postfix[pos++] = pop();
    }
    postfix[pos++] = '\0';
}
```

On `(`, `push(c)` stores the boundary. On `)`, the loop first checks `!is_empty()`, then removes an item with `char op = pop();`. If that item is `(`, `break` exits the loop. The opening parenthesis has already been removed, so there is no additional pop. For any other removed item, `postfix[pos++] = op;` writes the operator to the output.

For `1+(2+3)`, the closing parenthesis pops the inner `+` and writes it at output index 3. Popping `(` then leaves only the outer `+`, so `top == 0`. The final drain writes the outer `+` at index 4 and leaves `top == -1`, `pos == 5`. The separate terminator statement writes `'\0'` at index 5 and advances `pos` to 6. Calling `eval_postfix()` then returns 6 and again leaves `top == -1`.

Both converters overwrite `postfix`. Evaluate or display one result before calling the other converter if both results are needed. Balanced parentheses and valid input are prerequisites. An unmatched closing parenthesis can empty the loop without finding `(`, and an unmatched opening parenthesis can reach the final output. Neither mismatch is reported.

### How do the separate source files work together?

The definitions outside functions create storage shared by the helpers. Local variables such as `pos`, `i`, and `c` belong to one function call. The converters return `void` and leave their results in `postfix`. The evaluator returns an integer and empties its active stack.

The driver declares shared arrays with `extern` and declares helper functions before calling them. Those declarations do not create another stack or another output array. Building the driver together with `lab.c` connects the declarations to the definitions. Run `make lab-demo` in `module_04_stack/code` to exercise the supplied helpers.

### Can you predict each state?

1. After three pushes, why is `top` 2 while the count is 3? The first item occupies index 0, so the count is always `top + 1`.
2. Why may a popped value remain in the array? Decreasing `top` excludes that cell from the active prefix.
3. Why does a new `+` release both `*` and `-`? Neither precedence level, 2 or 1, is lower than `prec('+')`, so neither comparison takes `break`.
4. Why does conversion finish with `pos == 8` and `top == -1`? The drain empties the operator stack after seven output characters. A separate write adds `'\0'` and increments `pos` once more.
5. Why does `1+(2+3)` produce five output characters? Both parentheses are consumed as boundaries rather than copied.
6. Why does a shorter conversion replace a longer result correctly? It writes a new terminator, and both scanning loops use that terminator rather than a fixed iteration count.
