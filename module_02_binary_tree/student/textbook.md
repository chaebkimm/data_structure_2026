# Chapter 2. Organizing Data in a Hierarchy

## Thinking Logically

### What does hierarchical data look like?

A tree can store structural information, such as operator precedence in the expression `1 + 2 * 3`.

### How do we store the structural information?

In the expression `2 * 3`, the `*` operator multiplies `2` and `3`, so it stores `2` on the left and `3` on the right. In the expression `1 + 2 * 3`, the `+` operator adds `1` to the result of the multiplication, so it stores `1` on the left and the `*` node on the right.

### How do we calculate the expression stored hierarchically?

In the expression `2 * 3`, the `*` operator multiplies `2` and `3`, which is `6`. In the expression `1 + 2 * 3`, the `+` operator adds `1` to the result of the `*` operator (`6`), which results in `7`.

### How do we access the entire expression?

In the expression `2 * 3`, since the `*` operator stores the information for `2` and `3`, we access the whole expression through the `*` operator. In the expression `1 + 2 * 3`, the `+` operator stores the information for `1` and the `*` operator, and the `*` operator stores the information for `2` and `3`. Therefore, we access the whole expression through the `+` operator.

### What do we store for each operator or number?

We store the actual characters, such as `1` or `*`, and the information for the left and right sides of the operator.

### How do we connect an item to this data structure?

An item can be connected to the left or right side of the operator in the data structure. Alternatively, the root used to access the data structure can be connected to the left or right side of a new operator.

### A simple example

Let's consider a valid expression consisting of single digits and the `+` and `*` operators. Start with a digit, then follow each operator with one digit. Use no spaces or parentheses and at most 19 characters, leaving room for the string's ending `\0` in `eq[20]`. Assume that every intermediate result and the final answer fit in an `int`; the example does not check these input conditions.

### How do we calculate the result of the operation?

For numbers, such as `1` or `2`, the result is the same as the corresponding integer value. For operators, such as `+` or `*`, the result is calculated by performing the operation on the results of the left and right sides, which are calculated recursively prior to the operation.

### What is the hierarchical characteristic of a term with zero or more `*`s?

We group a sequence like `1 * 2 * 3` from left to right as `(1 * 2) * 3`. The first `*` node becomes the left child of the second `*` node. For a longer sequence, each new `*` becomes a parent of the term built so far.

### How do we build the hierarchy of a term with zero or more `*`s?

We can build the hierarchy by keeping track of the root to access the expression that has been processed so far. Initially, the root is the first number. As we encounter a `*` while scanning the expression, the old root becomes the left side of the `*`, the next number becomes the right side of the `*`, and the `*` becomes the new root.

### How do we build the hierarchy of an expression with `*`s and `+`s?

Because `*` has a higher operator precedence than `+`, we can treat the expression as a sum of terms. Initially, the root is the first term. As we encounter a `+` while scanning the expression, the old root becomes the left side of the `+`, the next term becomes the right side of the `+`, and the `+` becomes the new root.

## Calculating Efficiency

### How much memory does one item use?

Every item takes up space for its data (a number or symbol), plus space for left and right information.

### How much memory is used for iterating over items?

When searching or calculating deeply through the expression, the computer uses temporary memory to keep track of its place. This temporary memory grows based on how deep the branches go.

### How fast is creating or adding one item?

Setting up a new empty item takes constant time. Hooking it up to an empty left or right spot also takes constant time because you are just updating one single location, regardless of how massive the entire equation is.

### How fast is iterating over items?

The time it takes grows in proportion to the total number of items stored in the tree.

## Glossary

### Node

One object that stores data and links to related nodes.

### Tree

A hierarchy in which a node may have children.

### Binary Tree

A hierarchy in which every node has at most two children, specifically distinguished as left and right.

### Expression Tree

A tree that represents an expression. In this chapter's example, an operator node has two operand children and a number node is a leaf.

### Root

The top node (usually the final operation to be evaluated in an expression).

### Parent

A node that is directly above another node in the hierarchy.

### Child

A node that is directly below a parent node.

### Sibling

A different node that shares the same parent.

### Ancestor

An ancestor is a node earlier on the path from the root to another node. Ancestors still exist even though our nodes do not store upward links.

### Descendant

A node found below a given node by following one or more child links.

### Leaf

A node with no children.

### Subtree

One node together with all of its descendants (a standalone sub-expression).

### Recursion

A technique in which a function calls itself on a smaller part of the same problem. A tree function can process one node and then call itself on each child subtree.

### Base Case

A case that returns without another recursive call. Evaluation stops at a number.

## Invariant

### What is the invariant (the golden rule) in this data structure?

- The Root Rule: A nonempty tree has exactly one root at the very top.

- The Single-Parent Rule: Every node below the root appears in exactly one child position. Two parent nodes cannot share the exact same child node, and one parent cannot use the exact same node as both its left and right child.

- The Acyclicity Rule (No Loops): A node cannot be placed inside itself, and you can never create an endless loop where following child links downward leads you back to where you started.

### What happens if an invariant is broken?

- If the Root Rule breaks: A search that starts at one root cannot reach the nodes below the other root.

- If the Single-Parent Rule breaks: A search may visit a node twice.

- If the Acyclicity Rule breaks: A search may get stuck in an infinite loop.

### How do we keep the invariant intact?

Each new parent joins the existing subtree to newly built nodes, preserving a tree without cycles or shared children. The programmer must use initialized nodes and valid indices into the live `nodes` array.

## Coding Plan

All nodes live in the `nodes` array. A link or root is an integer index into that array: `nodes[root]` is the node at the root of the current subtree. The value `-1` means no child; `0` is a valid index for the first node.

### Designing a node

- Store one character named `data`, such as `2`, `+`, or `*`.
- Store two indices: one for the `left` child, one for the `right` child.

### Reserving and initializing a node

- Use the next unused array position, recorded by `size`.
- Save the data and set both the left and right indices to `-1`.
- Advance `size` and return the position just reserved as the new node's index.

### Adding a child

- Choose an empty child position, whose index is `-1`.
- Store the child's index in the parent's `left` or `right` field.

### Building a term from an expression string

The shared variable `pos` marks the next unread character in `eq`. To consume a character means to read it and advance `pos`.

1. Consume a digit, reserve its node, and make its index the current root.
2. While the next character is `*`, consume it and reserve an operator node.
3. Consume the following digit and reserve its node.
4. Link the old root on the operator's left and the new digit on its right.
5. Make the operator the current root and repeat from step 2.
6. Return the root when the next character is not `*`, leaving that character unread.

### Building a sum of terms from an expression string

For valid input, the final unread character is `\0`.

1. Build a complete term and make its index the current root.
2. While the next character is `+`, consume it and reserve an operator node.
3. Build the next complete term.
4. Link the old root on the operator's left and the new term on its right.
5. Make the operator the current root and repeat from step 2.
6. Return the root when the next character is not `+`.

### Evaluating an expression tree

1. At a digit leaf, convert its character to an integer by subtracting `'0'`
   and return that value. This is the base case.
2. At an operator, evaluate the left child and then the right child into
   separate local values.
3. Apply the current operator to those values and return the calculated result.

## New C Syntax Explained

### Defining a `struct` tag

A custom data type can be defined with the `struct` keyword and a tag, where the members are declared in the following curly braces `{}`. For example, `struct TreeNode { char data; int left; int right; };`

### Using a `struct` tag

The tag tells the compiler what kind of custom data type you are referencing. Every time you declare a node variable, you write `struct TreeNode`.

### `.` (Accessing Fields)

`nodes[root].data` accesses the `data` field of the node at index `root`. The brackets select an array element, and the dot selects one of its fields.

### Recursive Functions

A recursive function calls itself on a smaller part of the same problem. A recursive function needs a base case. Without a base case, calls could continue infinitely. The evaluator has a number node as a base case.

## C Code

### Designing a node

The same structure represents a digit leaf or an operator with two children.

```c
struct TreeNode {
        char data; /* A digit character, '+', or '*'. */
        int left;  /* Left child's index in nodes, or -1 if absent. */
        int right; /* Right child's index in nodes, or -1 if absent. */
};
```

### Reserving nodes

`size` counts the used nodes and also identifies the next unused position. The array is declared outside the functions, so its nodes remain available after a function returns.

```c
/* One expression at a time; these nodes live for the whole program. */
struct TreeNode nodes[20];
int size = 0;

int new_node(char data)
{
        nodes[size].data = data;
        /* A newly reserved node has no children yet. */
        nodes[size].left = nodes[size].right = -1;
        return size++; /* Advance size; the returned value is its old index. */
}
```

### Building a term

`term()` builds one digit followed by zero or more `*`-digit pairs. In `eq[pos++]`, the old value of `pos` selects the character, then `pos` advances. Checking `eq[pos]` in the loop leaves the character unread.

```c
char eq[20] = "1+2*3"; /* No spaces; the string ends with '\0'. */
int pos = 0;          /* Index of the next unread character. */

int term(void)
{
        /* Begin with the first digit as a one-node subtree. */
        int root = new_node(eq[pos++]);
        while (eq[pos] == '*') {
                int op = new_node(eq[pos++]);  /* Consume '*'. */
                int num = new_node(eq[pos++]); /* Consume the next digit. */
                /* Group the term built so far with the next digit. */
                nodes[op].left = root;
                nodes[op].right = num;
                root = op; /* The new operator is now the subtree's root. */
        }
        /* Leave '+' or '\0' unread for the caller. */
        return root;
}
```

### Building a sum of terms

`terms()` calls `term()` for each operand of `+`. Both functions share `pos`, so each call continues where the preceding call stopped.

```c
int terms(void)
{
        int root = term();
        while (eq[pos] == '+') {
                int op = new_node(eq[pos++]); /* Consume '+'. */
                /* Finish the next term, including all its multiplications. */
                int next_term = term();
                nodes[op].left = root;
                nodes[op].right = next_term;
                root = op; /* The new '+' joins the two subtrees. */
        }
        return root; /* Index of the whole expression's root. */
}
```

### Evaluating children before the operator

`node` is an index, while the return value is the subtree's answer. Subtracting `'0'` converts a stored digit such as `'3'` to the integer `3`, because C's digit character codes are consecutive. This evaluator assumes a completed tree from valid input; it does not validate malformed trees.

```c
int eval_tree(int node)
{
        /* Base case: a digit leaf already supplies its numeric answer. */
        if (nodes[node].data >= '0' && nodes[node].data <= '9') {
                return nodes[node].data - '0';
        }

        /* A valid tree contains only digits and the two supported operators. */
        if (nodes[node].data != '+' && nodes[node].data != '*') return -1;

        /* Each call keeps its own results; the left call finishes first. */
        int left = eval_tree(nodes[node].left);
        int right = eval_tree(nodes[node].right);

        /* Combine the returned values without changing the stored operator. */
        if (nodes[node].data == '+') return left + right;
        if (nodes[node].data == '*') return left * right;

        return -1;
}
```

### Running the example

`main` starts the program, builds the tree once, and prints the result returned by the evaluator.

```c
#include <stdio.h> /* Declares printf. */

int main(void)
{
        int root = terms();           /* Build the tree and keep its root index. */
        int answer = eval_tree(root); /* Evaluate the tree from that index. */
        printf("%s = %d\n", eq, answer);
        return 0;
}
```

The output is `1+2*3 = 7`. In `printf`, `%s` prints the expression string, `%d` prints the integer answer, and `\n` ends the line. The root stores `'+'`; its right child stores `'*'`, whose children store `'2'` and `'3'`.

## Full C Code Explanation

This section assumes no previous knowledge of C. It explains all six
examples in **C Code**, including every kind of symbol, what each statement
does, and the values that change while the program runs. Read a little at
a time beside the original examples. The original chapter above remains
the starting point; this section is a detailed companion.

### 1. What are we reading, and where does the program begin?

**Code** is text that gives instructions in a programming language. Our
language is C. A **program** is a complete set of instructions that a
computer can run. To **execute** a statement means to carry it out. A C
**compiler** translates the source code we write into a runnable program.

The six code boxes above are parts of one program. We will put them
together in Section 13. They are not six independent programs: later parts
use the types, storage, and functions introduced in earlier parts.

A **function** is a named piece of code that performs a job. The function
named `main` is where execution of this example begins. A **function call**
asks another function to do its job. The caller waits while the called
function runs, and then continues when that function returns.

The function definitions appear before `main` so that their names and
interfaces are known when used. Their bodies do not run merely because
they are written earlier in the file. In this example, the main sequence is:

1. `main` calls `terms` to build the expression tree.
2. `terms` calls `term`, and both builders call `new_node` as needed.
3. When the building finishes, `main` receives the root's array index.
4. `main` calls `eval_tree` to calculate the answer from that root.
5. `main` calls `printf` to display the expression and answer.
6. `main` returns `0` to report successful completion.

The storage declared outside functions is initialized before `main` runs.
Building a tree and printing an answer are separate actions. None of the
builder's assignments automatically displays a node on the screen.

We use the expression string `"1+2*3"`. This example accepts a deliberately
small kind of input: one digit, followed by zero or more operator-and-digit
pairs. Each operator must be `+` or `*`. Use no spaces, parentheses,
negative signs, or numbers containing several digits. Use at most 19
characters, and assume every arithmetic result fits in an `int`.

Thus `"7"`, `"2*3*4"`, and `"1+2+3"` fit the assumptions. `"12+3"`,
`"1 + 2"`, and `"1+"` do not. The code assumes valid input; it does not
check these rules for us. The printed form `1 + 2 * 3` in an explanation
may contain spaces for readability, but the stored input here is `"1+2*3"`.

The shaded boxes, backticks, and `c` label used to format this textbook
are not C instructions. When copying a program, copy only the text inside
the code box. The numbered sections and explanatory tables are not part
of the program either.

### 2. What are variables, types, names, and assignments?

A **value** is information, such as the integer `5` or the character `'+'`.
A **variable** is a named place to store a value. A variable's **type**
says what kind of information it can hold and what operations make sense
for it. This program uses `int` for integers and `char` for characters.

An `int` can store whole numbers within a supported range, including
negative numbers, zero, and positive numbers. C does not promise that an
`int` always occupies four bytes or holds an arbitrarily large number.
Our example uses small values that fit.

A `char` stores a small integer value; here we use it to store character
codes representing digits and operator symbols. We write `'3'` to refer
to the character for the digit three, and `3` to refer to the number three.
Section 7 explains why those are different values.

Consider this complete line:

```c
int size = 0;
```

| Part | Meaning in this line |
|---|---|
| `int` | A C keyword specifying the variable's integer type. |
| `size` | The name we chose for the variable. |
| `=` | Introduces the initial value in this declaration. |
| `0` | The integer value zero. A value written directly in code is a literal. |
| `;` | Ends the declaration. |

This line **declares** `size`, introducing its name and type, and
**initializes** it, giving it its first value. Here we choose zero because
we have not reserved any nodes yet.

Now compare these lines:

```c
int root = 0;
root = 1;
```

The first line declares and initializes a new variable. The second line
**assigns** a new value to that existing variable. After both lines, `root`
contains `1`. Assignment replaces the previous value; it does not keep a
history and does not assert that the two sides are mathematically equal.

In `root = op;`, C reads the current value of `op` and stores a copy in
`root`. If `op` contains `3`, `root` becomes `3`. This does not permanently
connect the two variables, and it does not move a node in the array.

Names such as `size`, `pos`, `root`, `op`, `num`, `next_term`, `data`, and
`answer` are chosen by the programmer. C does not know that `size` should
count nodes or that `pos` should mark input progress; our code maintains
those meanings. `op` abbreviates “operator,” and `num` abbreviates “number.”
The underscore in `next_term` or `new_node` is part of one name, not an
arithmetic operation. Uppercase and lowercase matter: `root` and `Root`
would be different names.

A **keyword**, such as `int`, `char`, `struct`, `while`, `if`, `return`, or
`void`, has a meaning supplied by C. We cannot use these keywords as our
own variable names. `TreeNode`, `term`, and `eval_tree` are our names, not
built-in C commands.

Where a declaration appears also matters. The declarations of `nodes`,
`size`, `eq`, and `pos` are outside every function. They introduce the
shared, or **global**, storage used throughout this program. That storage
exists for the program's entire run.

A variable declared inside a function or one of its brace-delimited
blocks is **local**. Its name is available within its scope, meaning the
part of the code where that declaration can be used. `root` inside `term`
and `root` inside `terms` are different variables, despite their identical
spelling. One does not overwrite the other simply because their names match.
Each new function call has its own local values.

The variables `op` and `num` inside a loop body belong to that body. On a
later iteration, their declarations run again and initialize new local
values for that iteration. The nodes they refer to remain in the global
array after those local variables are no longer available.

For a local declaration such as `int answer;`, no initial value is given.
We must store a value before reading that local variable. It does not
automatically begin at zero. Global storage is different: an omitted
initializer gives it zero initialization. Section 5 explains why even
zero-initialized storage is not yet a properly reserved tree node.

### 3. How do we read the symbols, comments, and conditions?

An **expression** produces a value. `size + 1` produces an integer;
`eq[pos]` produces the character at a selected position; `term()` produces
the value returned by that function call. A **statement** performs an
instruction, such as storing a value or returning from a function.

The same symbol can have different jobs in different contexts. Use the
surrounding code to read it:

| Symbol or form | Meaning in this chapter |
|---|---|
| `=` | Initializes a declaration or assigns a value to existing storage. |
| `==` | Compares two values for equality; it does not change either one. |
| `!=` | Compares whether two values are different. |
| `>=` | Tests “greater than or equal to.” |
| `<=` | Tests “less than or equal to.” |
| `&&` | Logical AND: the condition requires both sides to be true. |
| `+` | Adds numbers in `left + right`; inside `'+'` it names a character. |
| `-` | Subtracts in `data - '0'`; in `-1` it makes the integer negative. |
| `*` | Multiplies in `left * right`; inside `'*'` it names a character. |
| `++` after a variable | Uses the old value and also increases that variable by one. |
| `[20]` in a declaration | Gives the number of elements to reserve in an array. |
| `[node]` in an expression | Selects the array element whose index is the value of `node`. |
| `.` | Selects a named field from one structure object. |
| `(...)` | Surrounds function parameters, function arguments, or a condition. |
| `{ ... }` | Groups the fields of a structure or the statements of a block. |
| `;` | Ends declarations and many statements. |
| `,` | Separates arguments in the `printf` call used here. |
| `'...'` | Surrounds a character constant, such as `'3'` or `'*'`. |
| `"..."` | Surrounds a string literal, such as `"1+2*3"`. |
| `/* ... */` | Surrounds a comment for the human reader. |
| `\` inside a quoted escape | Begins an escape such as `\n` or `\0`; see Sections 7 and 13. |

For example, these two lines do different jobs:

```c
root = op;
if (nodes[node].data == '+') return left + right;
```

The first changes `root`. The second checks whether the stored character
is `'+'` and returns a sum if so. Two equals signs are one comparison
operator; they are not two successive assignments.

A **condition** is an expression used to decide what to do next. In C,
zero is false and a nonzero value is true when used as a condition.
Comparisons such as `==`, `!=`, `>=`, and `<=` produce the integer `1`
for true or `0` for false. The operator `&&` also produces `1` or `0`.

In this condition:

```c
nodes[node].data >= '0' && nodes[node].data <= '9'
```

we first check whether the character code is at least the code for `'0'`.
Only if that is true do we check whether it is at most the code for `'9'`.
Both checks must succeed for the complete condition to be true. This
left-to-right, stop-when-false behavior is called **short-circuit evaluation**.
The second part is skipped if the first part is false.

An `if` tests its condition once and executes its controlled statement
only when the condition is true. A `while` tests its condition before each
iteration, executes its body if true, and then tests again. A loop whose
first condition is false runs its body zero times. Indentation makes these
relationships easier to see, but parentheses and braces establish them.

In a function definition, `{` begins its body and the matching `}` ends
it. Braces inside a `while` or `if` group several statements into one
block. Statements in an entered block run in order unless a call, loop,
conditional, or `return` changes the flow. The closing brace of a function
does not need a following semicolon; the closing brace in a structure
definition does, as we will see next.

`/* A newly reserved node has no children yet. */` is a comment. `/*`
starts it and `*/` ends it. Its words explain an intention; they do not
set the child fields themselves. The following assignments perform that
work. The star in a comment marker is not a multiplication operator.

Spaces separate words: `int root` contains a keyword and a name, whereas
`introot` would be one name. Extra spaces, blank lines, and indentation
help organize code. They do not replace semicolons or braces. Text inside
quotes is different: adding a space to `"1+2*3"` changes the actual input.

### 4. What does every part of `struct TreeNode` mean?

Here is the original definition:

```c
struct TreeNode {
        char data; /* A digit character, '+', or '*'. */
        int left;  /* Left child's index in nodes, or -1 if absent. */
        int right; /* Right child's index in nodes, or -1 if absent. */
};
```

A **structure** combines several named pieces of information in one kind
of object. Those pieces are called **members** or **fields**. Our tree node
needs one character and two child indices, so we define a structure with
three fields.

| Part | Meaning |
|---|---|
| `struct` | Introduces a structure type. |
| `TreeNode` | Our chosen tag, which names this kind of structure. |
| `{` | Begins the list of fields for this type. |
| `char data;` | Every object of this type has a character field named `data`. |
| `int left;` | Every object has an integer field named `left`. |
| `int right;` | Every object has a separate integer field named `right`. |
| `}` | Ends the list of fields. |
| `;` after `}` | Completes the structure declaration. |

The comments explain how we intend to use the fields. C does not enforce
“only digits, plus, or star” merely because that appears in a comment.
The code must follow that rule.

This definition describes the shape of a node; it does not yet declare
our array of actual nodes. In this program, the full type name is
`struct TreeNode`. When we reserve storage later, we write both words.
`TreeNode` alone is not a replacement for `struct TreeNode` in this code.

Each actual node has its own `data`, `left`, and `right`. For example,
a node could hold these three values:

| Field | Stored value | Interpretation |
|---|---|---|
| `data` | `'+'` | This node represents addition. |
| `left` | `0` | Its left child is the node at index zero. |
| `right` | `3` | Its right child is the node at index three. |

The right field's `3` is an **index**, not the answer three and not the
character `'3'`. To find that child's character, we must look at
`nodes[3].data`. A node's array position, its stored character, and the
answer of its subtree are three different pieces of information.

Now read this expression from left to right:

```c
nodes[op].left
```

`nodes` names the array. `[op]` selects one element using the current
integer value of `op`. The dot then selects that element's field named
`left`. If `op` contains `1`, the whole expression refers to the `left`
field of `nodes[1]`. It does not select a separate array named `left`.

Field names belong to the structure. A local variable also named `left`
inside `eval_tree` is separate from the `left` field of every node. The
expression `nodes[node].left` includes a dot and refers to a stored child
index; the expression `left` alone there refers to a local calculated answer.

### 5. What are `nodes[20]`, `size`, and the special value `-1`?

The shared storage begins with these declarations:

```c
/* One expression at a time; these nodes live for the whole program. */
struct TreeNode nodes[20];
int size = 0;
```

In `struct TreeNode nodes[20];`, `struct TreeNode` is the type of each
element, `nodes` is the array's name, `[20]` reserves twenty elements,
and `;` ends the declaration. Each element contains all three fields,
not just a character. The number twenty counts nodes, not bytes.

An **array** holds a fixed number of elements of the same type. An
**index** selects one of those elements. C array indices start at zero:
our twenty positions are `0` through `19`. `nodes[0]` is the first node;
`nodes[19]` is the twentieth. `nodes[20]` as an access would ask for an
element beyond the array. The `[20]` in the declaration gives a length;
the brackets in a later access give an index.

`size` is a separate variable. We use it as both the number of reserved
nodes and the index of the next unused position:

| Current `size` | Reserved indices | Index the next call will use |
|---|---|---|
| `0` | None | `0` |
| `1` | `0` | `1` |
| `5` | `0`, `1`, `2`, `3`, `4` | `5` |

Changing `size` does not resize the array. Its capacity stays twenty.
C does not update `size` when we use an element; `new_node` updates it
explicitly. The already reserved nodes occupy indices from `0` through
`size - 1` when `size` is positive.

Because the array is declared outside functions, its storage lasts for
the whole program. Returning from `new_node`, `term`, or `terms` does
not erase it. That is why a returned integer index can still identify a
node built by a function that has finished.

This global array has no explicit initializer, so C initially zeroes its
fields. However, integer zero is **not** our “no child” marker. Zero is a
valid index for the first node. We use `-1` as a **sentinel**, a specially
chosen value meaning “there is no child in this position.”

The distinction is essential:

- `left = 0` means the left child is `nodes[0]`.
- `left = -1` means there is no left child.
- Neither statement tells us the child's arithmetic answer.

Unused zero-initialized array positions are not initialized tree nodes
ready for traversal. Each `new_node` call stores the intended character
and explicitly sets both child fields to `-1`. Only then do we treat that
position as a reserved node. We must never try to use `nodes[-1]`; the
sentinel is information to interpret, not a valid array position.

### 6. How does a function work, and what does `new_node` do?

Here is the original function:

```c
int new_node(char data)
{
        nodes[size].data = data;
        /* A newly reserved node has no children yet. */
        nodes[size].left = nodes[size].right = -1;
        return size++; /* Advance size; the returned value is its old index. */
}
```

The first line describes how the function can be called:

| Part | Meaning |
|---|---|
| `int` before `new_node` | The function returns an integer value to its caller. |
| `new_node` | Our chosen function name. |
| `(` and `)` | Surround the parameter list in this definition. |
| `char data` | Declare one parameter named `data`, of type `char`. |
| `{` and `}` | Surround the statements that form the function body. |

A **parameter** is a variable that receives a value when the function is
called. An **argument** is the value or expression supplied by the caller.
In the call `new_node('2')`, `'2'` is the argument. The function's parameter
`data` receives that character value. The caller does not write `char`
inside the call; the type belongs to the definition's parameter declaration.

The parameter is local to this call. Its name `data` is independent of
the field name after the dot. In this first statement:

```c
nodes[size].data = data;
```

C reads the parameter on the right and writes its character into the
selected node's field on the left. If `size` is `2` and the argument was
`'2'`, this stores `'2'` in `nodes[2].data`. The two appearances of `data`
refer to different storage; the dot identifies the structure field.

The next executable statement is a **chained assignment**:

```c
nodes[size].left = nodes[size].right = -1;
```

Its grouping is `nodes[size].left = (nodes[size].right = -1)`. The inner
assignment stores `-1` in the right field and supplies the assigned value,
`-1`, to the outer assignment. The left field receives `-1` as well. For
understanding this example, the effect is the same as writing:

```c
nodes[size].right = -1;
nodes[size].left = -1;
```

There is still only one selected node. Both child positions start absent.
The original chained line does not compare the fields for equality.

The final statement needs particular care:

```c
return size++;
```

`return` ends the current function call and sends a value back to its
caller. `size++` is **postfix increment**: the expression's value is the
old value of `size`, and `size` is also increased by one. If `size` was
`2`, this call returns `2` and leaves the global `size` equal to `3`.
The caller receives the index just used, not the next unused index.

For the purpose of tracing this program, we can expand the idea as:

```c
int reserved_index = size;
size = size + 1;
return reserved_index;
```

Those three lines are an explanation of the original `return size++;`.
They are not additional lines to insert after it. Code after an executed
`return` in the same function call is not executed.

For example, starting with `size` equal to `0`, the call `new_node('1')`
sets `nodes[0]` to `{ data: '1', left: -1, right: -1 }`, leaves `size`
equal to `1`, and returns `0`. The braces and colons in that sentence are
a display of the values, not a C initializer to copy.

The name “new node” means reserving and initializing the next position
of our existing array. This function does not ask for additional dynamic
storage. It also contains no capacity check, so the caller must stay
within the input and storage assumptions stated earlier.

### 7. How do characters, strings, and `eq[pos++]` work?

The input and reading position are declared together:

```c
char eq[20] = "1+2*3"; /* No spaces; the string ends with '\0'. */
int pos = 0;          /* Index of the next unread character. */
```

`char` gives the type of each array element. `eq` is our chosen array
name, short for “equation.” `[20]` reserves twenty character positions.
`=` introduces the initializer, and `"1+2*3"` is a **string literal**.
The double quotes mark its boundaries in the source; they are not stored
as characters of the expression. `;` ends the declaration.

A C **string** is a sequence of characters ending with a special zero
character called the **null character** or **null terminator**, written
`'\0'`. In this array initializer, C stores the five visible characters,
then the terminator, and initializes the remaining positions to zero:

| Index in `eq` | `0` | `1` | `2` | `3` | `4` | `5` | `6` through `19` |
|---|---|---|---|---|---|---|---|
| Stored character | `'1'` | `'+'` | `'2'` | `'*'` | `'3'` | `'\0'` | `'\0'` in each position |

`'\0'` represents one character whose value is zero. It is not the two
characters backslash and zero, and it is not the visible digit `'0'`.
The backslash introduces an **escape sequence**, a way to write a special
character inside quotes. The null terminator marks where the string ends;
it is not an extra operator or digit to process.

Keep these related forms separate:

| C spelling | What it represents |
|---|---|
| `3` | The integer three. |
| `'3'` | The character code for the digit three. |
| `"3"` | A string containing `'3'` followed by `'\0'`. |
| `0` | The integer zero. |
| `'0'` | The character code for the visible digit zero. |
| `'\0'` | The null character, whose value is zero. |

Technically an ordinary character constant such as `'3'` has type `int`
in C. Here it represents a character code that can be stored in a `char`.
The surrounding single quotes distinguish that code from the integer
literal `3`. We do not need to memorize the code's numeric value. C
requires the digit codes `'0'` through `'9'` to be consecutive, which is
why subtracting `'0'` will later recover the digit's numeric value.

`int pos = 0;` declares a shared integer position and starts it at the
first character. It is separate from `size`: `pos` counts progress through
the input, while `size` counts reserved nodes. An index into `eq` selects
a character; an index into `nodes` selects a structure containing fields.
Even when the numbers happen to match in this example, the arrays and
the meanings remain different.

`eq[pos]` reads the character at the current position without changing
`pos`. If `pos` is `1`, it reads `'+'`, and `pos` remains `1`. We use this
form when checking what comes next.

`eq[pos++]` both reads a character and advances the position. The old value
of `pos` is the index used for the access. If `pos` is `2`, this expression
reads `eq[2]`, which is `'2'`, and increases `pos` to `3`. This is what
**consume a character** means in this chapter.

In this full statement:

```c
int root = new_node(eq[pos++]);
```

C evaluates the argument to `new_node`, using the old `pos` to select a
character and incrementing `pos`. The argument evaluation, including that
increment, is complete before the body of `new_node` begins. `new_node`
receives the selected character, reserves its node, and returns its index.
That returned index initializes the local variable `root`.

Starting with `pos = 0` and `size = 0`, the statement consumes `'1'`,
leaves `pos = 1`, reserves `nodes[0]`, leaves `size = 1`, and initializes
`root` to `0`. The value stored in `root` is the node's index, not the
character `'1'` and not the calculated number `1`.

C does not generally promise to evaluate every part of every expression
from left to right. This example uses one argument with `pos++` in each
`new_node` call, and successive declarations are separate statements.
Follow those statement boundaries; do not invent an extra increment when
reading a plain `eq[pos]` check.

### 8. How does `term(void)` build one multiplication group?

Here is the complete original function again:

```c
int term(void)
{
        /* Begin with the first digit as a one-node subtree. */
        int root = new_node(eq[pos++]);
        while (eq[pos] == '*') {
                int op = new_node(eq[pos++]);  /* Consume '*'. */
                int num = new_node(eq[pos++]); /* Consume the next digit. */
                /* Group the term built so far with the next digit. */
                nodes[op].left = root;
                nodes[op].right = num;
                root = op; /* The new operator is now the subtree's root. */
        }
        /* Leave '+' or '\0' unread for the caller. */
        return root;
}
```

`int term(void)` says that the function named `term` returns an integer
and receives no arguments. `void` in this parameter list means “no
parameters.” It does not mean “return nothing”; the `int` before the name
specifies the return type. The call is written `term()`, with no arguments
between the parentheses. We do not write `term(void)` at the call site.

The function reads the shared `eq` and `pos`, so it can make progress
through the input without receiving them as parameters. Its own `root`
is local to this call. The opening brace starts its body.

`int root = new_node(eq[pos++]);` consumes the first digit of this term,
reserves a leaf node for it, and stores the returned index in `root`.
Our valid-input assumption is what makes this character a digit; that
line does not test it. At this point the term consists of a single node.

`while (eq[pos] == '*') {` starts a loop. The parentheses contain the
condition: compare the next unread character with the character `'*'`.
This use of `*` is inside single quotes, so it is not multiplication.
The equality check does not consume the character. If the condition is
false, execution skips the entire body and proceeds to `return root;`.

When the condition is true, these five statements run in order:

| Statement | What happens |
|---|---|
| `int op = new_node(eq[pos++]);` | Consume the `'*'`, reserve its node, and store its index in a local integer named `op`. |
| `int num = new_node(eq[pos++]);` | Consume the following digit, reserve its node, and store its index in a local integer named `num`. |
| `nodes[op].left = root;` | Make the subtree built so far the new operator's left child. |
| `nodes[op].right = num;` | Make the new digit node the operator's right child. |
| `root = op;` | Remember the new operator as the root of the enlarged subtree. |

Before `root = op;`, `root` still contains the old subtree's index.
That is why the left-child assignment can preserve the subtree built so
far. After the assignment, the old subtree still exists in `nodes`; the
new operator's left field leads to it. Updating `root` does not erase it.

The loop's closing brace leads back to the condition. C checks the new
next unread character, enters the body again if it is another `'*'`, or
leaves the loop if it is not. The body does not run a fixed number of
times; the input determines that number.

For input `"1+2*3"`, the first call to `term()` consumes `'1'` and then
sees `'+'`. Its loop executes zero times. It returns index `0`, with
`pos` still `1`, leaving the plus sign for `terms()` to handle.

The second call begins with `pos = 2`, consumes `'2'`, sees `'*'`,
consumes the star and `'3'`, and links a multiplication subtree. It then
sees `'\0'`, so the loop stops. It returns the multiplication node's
index `3`, with `pos = 5`. Section 10 follows every allocation.

The statement `return root;` ends the function and sends the current
root index to its caller. It does not evaluate the subtree's arithmetic.
The word `term` here names a complete multiplication group, which may
contain no multiplication at all if there is only a single digit.

For `"2*3*4"`, the first star joins `'2'` and `'3'`. The second star
then takes that entire earlier subtree as its left child and `'4'` as
its right child. This builds `(2 * 3) * 4`, a **left-associative** grouping.
The algorithm gets this grouping by repeatedly making the old root the
new operator's left child.

### 9. How does `terms(void)` build a sum and preserve precedence?

Here is the original function:

```c
int terms(void)
{
        int root = term();
        while (eq[pos] == '+') {
                int op = new_node(eq[pos++]); /* Consume '+'. */
                /* Finish the next term, including all its multiplications. */
                int next_term = term();
                nodes[op].left = root;
                nodes[op].right = next_term;
                root = op; /* The new '+' joins the two subtrees. */
        }
        return root; /* Index of the whole expression's root. */
}
```

The name `terms` ends in `s`; it is a different function from `term`.
C does not attach a special grammatical meaning to that extra letter.
We chose the names because one function builds a multiplication group
and the other joins such groups with addition.

`int terms(void)` declares a function returning an integer and taking
no arguments. Its opening brace begins its body. `int root = term();`
calls `term`, waits until that call finishes, and initializes this
function's local `root` with the index that `term` returns.

The two functions have separate local variables named `root`, but share
one global `pos`. When `term` returns, it leaves `pos` at the next unread
character. `terms` sees that updated value immediately; returning does
not reset the position to zero.

`while (eq[pos] == '+') {` checks whether the next unread character is
the plus-sign character. If it is, the body runs; if it is not, the loop
ends. This check leaves `pos` unchanged. The five body statements have
these jobs:

| Statement | What happens |
|---|---|
| `int op = new_node(eq[pos++]);` | Consume `'+'`, reserve its node, and save its index. |
| `int next_term = term();` | Build the complete next multiplication group and save its root index. |
| `nodes[op].left = root;` | Put the sum built so far on the new plus node's left. |
| `nodes[op].right = next_term;` | Put the complete next term on its right. |
| `root = op;` | Make the new plus node the current sum's root. |

While the inner `term()` call runs, the outer call's `op` and `root`
remain available. The `op` inside `term` belongs to that other function's
loop body and cannot overwrite the outer `op`. When `term` returns,
execution resumes at the next statement in `terms` with the correct
plus-node index still stored in the outer `op`.

At the closing loop brace, C tests the next character again. If there
is another plus sign, the next iteration joins another complete term.
When the loop stops, `return root;` supplies the entire expression's
root index to the caller.

This arrangement makes multiplication have higher **precedence**, meaning
it is grouped before the surrounding additions. When parsing `1+2*3`,
`terms` does not immediately attach the digit `'2'` as the complete right
operand of `'+'`. It asks `term()` to finish the whole `2*3` group, then
attaches that group's root. The resulting hierarchy represents
`1 + (2 * 3)`.

C's own arithmetic precedence does not build this tree automatically.
The characters in `eq` are data. Our function calls and child assignments
establish the input expression's grouping. For `"1+2+3"`, successive
iterations similarly build `(1 + 2) + 3` by putting the previous sum on
the left of each new plus node.

### 10. What happens during every step of building `1+2*3`?

Start a fresh program with `eq` containing `"1+2*3"`, `pos = 0`, and
`size = 0`. `main` calls `terms()`. Remember that `pos` selects the next
input character and `size` selects the next unused node slot.

Every character consumed by these builders produces one node. The exact
reservation order is:

| Call that consumes the character | `pos` before | Character | Returned node index | `pos` after | `size` after |
|---|---|---|---|---|---|
| First `term`, initial digit | `0` | `'1'` | `0` | `1` | `1` |
| `terms`, plus operator | `1` | `'+'` | `1` | `2` | `2` |
| Second `term`, initial digit | `2` | `'2'` | `2` | `3` | `3` |
| Second `term`, star operator | `3` | `'*'` | `3` | `4` | `4` |
| Second `term`, next digit | `4` | `'3'` | `4` | `5` | `5` |

Each reservation first gives that node `left = -1` and `right = -1`.
Only the later linking statements change the operator nodes' children.
Follow the calls and links in order:

1. The first `term` reserves node `0` for `'1'` and sets its local
   `root` to `0`. The next character is `'+'`, so its star loop does
   not run. It returns `0` without consuming the plus.
2. `terms` initializes its own `root` to `0`. Its plus condition is
   true, so it reserves node `1` for `'+'` and sets its local `op` to
   `1`. This node's children are still absent at this moment.
3. `terms` calls `term` again. That call reserves node `2` for `'2'`
   and initializes its own `root` to `2`. The outer `root = 0` and
   `op = 1` are waiting in the suspended `terms` call.
4. The second `term` sees `'*'`. It reserves node `3` for the star and
   node `4` for `'3'`. In this loop body, `op = 3` and `num = 4`.
5. `nodes[op].left = root;` stores `2` in `nodes[3].left`.
   `nodes[op].right = num;` stores `4` in `nodes[3].right`.
   `root = op;` changes this `term` call's root to `3`.
6. `eq[5]` is `'\0'`, which is not `'*'`. The second `term` returns
   `3`. Back in `terms`, the local `next_term` receives `3`.
7. The waiting outer values are still `op = 1` and `root = 0`.
   `nodes[op].left = root;` stores `0` in `nodes[1].left`.
   `nodes[op].right = next_term;` stores `3` in `nodes[1].right`.
   `root = op;` changes the outer root to `1`.
8. The next character is still `'\0'`, which is not `'+'`. `terms`
   returns `1` to `main`. The final state is `root = 1`, `size = 5`,
   and `pos = 5`.

The completed node array contains:

| Array index | `data` | `left` | `right` | Meaning |
|---|---|---|---|---|
| `0` | `'1'` | `-1` | `-1` | Digit leaf for one. |
| `1` | `'+'` | `0` | `3` | Add the subtrees at indices `0` and `3`. |
| `2` | `'2'` | `-1` | `-1` | Digit leaf for two. |
| `3` | `'*'` | `2` | `4` | Multiply the subtrees at indices `2` and `4`. |
| `4` | `'3'` | `-1` | `-1` | Digit leaf for three. |

The tree described by those links is:

```text
              index 1: '+'
              /          \
     index 0: '1'     index 3: '*'
                       /        \
              index 2: '2'    index 4: '3'
```

This is a picture to read, not C source code. The links are exactly
`1 -> 0`, `1 -> 3`, `3 -> 2`, and `3 -> 4`, with the first link in each
pair being the left child.

The array stores nodes in reservation order, while the child indices
establish tree order. The root is index `1`, even though it is neither
the first nor the last reserved node. Do not find a child by assuming it
is in the immediately following slot. Read the parent's child field.

At this point no operator node has been replaced by a number. The tree
has been built, and the arithmetic answer has not yet been computed.

### 11. What does every line of `eval_tree` mean?

The evaluator is:

```c
int eval_tree(int node)
{
        /* Base case: a digit leaf already supplies its numeric answer. */
        if (nodes[node].data >= '0' && nodes[node].data <= '9') {
                return nodes[node].data - '0';
        }

        /* A valid tree contains only digits and the two supported operators. */
        if (nodes[node].data != '+' && nodes[node].data != '*') return -1;

        /* Each call keeps its own results; the left call finishes first. */
        int left = eval_tree(nodes[node].left);
        int right = eval_tree(nodes[node].right);

        /* Combine the returned values without changing the stored operator. */
        if (nodes[node].data == '+') return left + right;
        if (nodes[node].data == '*') return left * right;

        return -1;
}
```

`int eval_tree(int node)` defines a function named `eval_tree` that
receives one integer parameter, `node`, and returns one integer answer.
The parameter is an index into `nodes`. The returned integer is the
calculated value of that node's subtree. Their shared type `int` does
not mean they have the same role.

The first `if` checks whether the current node stores a digit character:

```c
if (nodes[node].data >= '0' && nodes[node].data <= '9') {
        return nodes[node].data - '0';
}
```

`nodes[node]` selects the current node. `.data` reads its character field.
`>= '0'` checks the lower end of the digit range, `<= '9'` checks the
upper end, and `&&` requires both checks to be true. The parentheses
surround the condition. The braces group the action to take when true.

The subtraction converts the character code into the corresponding
number. C guarantees consecutive codes for the ten decimal digits:
`'0' - '0'` is `0`, `'1' - '0'` is `1`, and `'3' - '0'` is `3`.
We subtract the character constant `'0'`, not the integer `0`. Subtracting
the integer zero would leave the original character code unchanged.
This reasoning does not depend on memorizing ASCII code numbers.

For a digit node, `return` immediately ends this call. It never reaches
the child-evaluation statements below. This is the **base case**, the
case that supplies an answer without another call to `eval_tree`.
Consequently a correctly built digit leaf's `-1` child fields are never
used as array indices.

For a non-digit node, execution continues to:

```c
if (nodes[node].data != '+' && nodes[node].data != '*') return -1;
```

`!=` means “is different from.” This condition asks whether the character
is different from both `'+'` and `'*'`. If so, it returns `-1` from this
call. A plus node makes the first comparison false, so the second part
is skipped by short-circuit evaluation. A star node makes the first part
true and the second false. Both supported operators therefore continue.

There are no braces after this `if` because it controls only one
statement: `return -1;`. The meaning is the same as:

```c
if (nodes[node].data != '+' && nodes[node].data != '*') {
        return -1;
}
```

The statements following that return statement are not part of the
unbraced `if`. A line break or extra indentation cannot make a second
statement belong to it. Braces would be needed to group several
controlled statements.

Next come two separate declarations:

```c
int left = eval_tree(nodes[node].left);
int right = eval_tree(nodes[node].right);
```

The first reads the current node's left child index, passes it to another
call of `eval_tree`, waits for that call to finish, and stores its returned
answer in the local variable `left`. The second does the same for the
right child and stores its answer in the separate local `right`.

A function calling itself is **recursion**. Each call receives its own
`node` parameter and has its own local values. The computer keeps enough
information about each unfinished call to resume it after a child call
returns. This per-call record is often called a **call frame**. A child
call does not replace the parent's parameter or local variables.

The left child's entire evaluation finishes before the right declaration
runs because these are separate statements. Within the first call there
may be further recursive calls, all of which must finish before the
first declaration can complete. We are following program flow, not
assuming a general left-to-right rule for arbitrary expressions.

After both child answers have been obtained, the function checks the
stored operator:

```c
if (nodes[node].data == '+') return left + right;
if (nodes[node].data == '*') return left * right;
```

The first line compares the character with `'+'`. If it matches, the
unquoted `+` adds the two integer answers and `return` sends the sum to
the caller. The second line is not reached after that return. Otherwise,
the second line checks for `'*'`, multiplies the answers with the unquoted
`*`, and returns the product.

For the multiplication node in our example, the stored field
`nodes[node].left` is index `2`, but the local `left` becomes the answer
`2`. On its right, the stored field is index `4`, but the local `right`
becomes answer `3`. These meanings must be kept separate even when a
particular index happens to equal the corresponding answer.

The final `return -1;` is a fallback. Given the preceding checks and a
completed valid tree, execution returns earlier through a digit or a
supported operator, so it does not reach this line.

These `-1` returns are not complete input or tree validation. In
particular, `nodes[node].data` is accessed before any check that `node`
is a valid index. The function also assumes that both children of an
operator are valid and that recursive calls follow an acyclic tree.
Section 14 explains the limits of those assumptions.

### 12. How does recursion evaluate the example to seven?

After building the example, `main` holds root index `1`. It calls
`eval_tree(1)`. The node at index `1` stores `'+'`, so the call must
obtain two child answers before it can add them.

Follow the calls and returns in this order:

| Step | Action | Result or waiting state |
|---|---|---|
| `1` | Enter `eval_tree(1)`, whose character is `'+'`. | Needs the left subtree's answer first. |
| `2` | Call `eval_tree(0)`, whose character is `'1'`. | Digit base case returns integer `1`. |
| `3` | Resume `eval_tree(1)`. | Its local `left` is now `1`; begin the right child. |
| `4` | Call `eval_tree(3)`, whose character is `'*'`. | Needs its own left subtree's answer. |
| `5` | Call `eval_tree(2)`, whose character is `'2'`. | Digit base case returns integer `2`. |
| `6` | Resume `eval_tree(3)`. | Its local `left` is now `2`; begin its right child. |
| `7` | Call `eval_tree(4)`, whose character is `'3'`. | Digit base case returns integer `3`. |
| `8` | Resume `eval_tree(3)`. | Its local `right` is `3`; return `2 * 3`, which is `6`. |
| `9` | Resume `eval_tree(1)`. | Its local `right` is `6`; return `1 + 6`, which is `7`. |
| `10` | Resume `main`. | Initialize `answer` with the returned integer `7`. |

The digit call at index `4` returns `3`, not `4`. The multiplication call
at index `3` returns `6`, not `3`. The whole-tree call at index `1`
returns `7`, not `1`. Array indices tell us where to find a node;
evaluated answers tell us what its expression means numerically.

While the multiplication call is working, two different unfinished calls
have different values under the same local names:

| Call | Its `node` parameter | Its local `left` after the left child returns |
|---|---|---|
| Outer addition call | `1` | `1` |
| Inner multiplication call | `3` | `2` |

The inner call's `left = 2` does not overwrite the outer call's `left = 1`.
When the inner call returns `6`, the outer call stores that returned
value in its own `right`. The per-call values are why recursion can keep
track of several partly completed operations.

The base cases stop this process. On a digit, the evaluator returns
before following either child link. On an operator, both recursive calls
move into smaller child subtrees. A properly built finite tree therefore
eventually reaches digits and unwinds through all the waiting calls.

The evaluator reads the tree; it does not rewrite it. After the answer
has been computed, `nodes[1].data` is still `'+'` and `nodes[3].data` is
still `'*'`. Their child indices are also unchanged. The numbers `6`
and `7` are returned answers, not replacements for the stored operators.

It helps to state the return meanings explicitly:

- `new_node` returns the index of the node just reserved.
- `term` returns the index of one term's root.
- `terms` returns the index of the whole expression's root.
- `eval_tree` returns the numeric answer of a subtree.
- `main` returns a completion status to the environment.

All five use `int`, but the programmer determines what each returned
integer represents.

### 13. What is the complete runnable program, including the output?

The following program assembles the six original C examples. The
`#include` line appears first so that the declaration of `printf` is
available before its use. The node type comes before the array, and
functions are defined before the calls that need them.

```c
#include <stdio.h> /* Declares printf. */

struct TreeNode {
        char data; /* A digit character, '+', or '*'. */
        int left;  /* Left child's index in nodes, or -1 if absent. */
        int right; /* Right child's index in nodes, or -1 if absent. */
};

/* One expression at a time; these nodes live for the whole program. */
struct TreeNode nodes[20];
int size = 0;

int new_node(char data)
{
        nodes[size].data = data;
        /* A newly reserved node has no children yet. */
        nodes[size].left = nodes[size].right = -1;
        return size++; /* Advance size; the returned value is its old index. */
}

char eq[20] = "1+2*3"; /* No spaces; the string ends with '\0'. */
int pos = 0;          /* Index of the next unread character. */

int term(void)
{
        /* Begin with the first digit as a one-node subtree. */
        int root = new_node(eq[pos++]);
        while (eq[pos] == '*') {
                int op = new_node(eq[pos++]);  /* Consume '*'. */
                int num = new_node(eq[pos++]); /* Consume the next digit. */
                /* Group the term built so far with the next digit. */
                nodes[op].left = root;
                nodes[op].right = num;
                root = op; /* The new operator is now the subtree's root. */
        }
        /* Leave '+' or '\0' unread for the caller. */
        return root;
}

int terms(void)
{
        int root = term();
        while (eq[pos] == '+') {
                int op = new_node(eq[pos++]); /* Consume '+'. */
                /* Finish the next term, including all its multiplications. */
                int next_term = term();
                nodes[op].left = root;
                nodes[op].right = next_term;
                root = op; /* The new '+' joins the two subtrees. */
        }
        return root; /* Index of the whole expression's root. */
}

int eval_tree(int node)
{
        /* Base case: a digit leaf already supplies its numeric answer. */
        if (nodes[node].data >= '0' && nodes[node].data <= '9') {
                return nodes[node].data - '0';
        }

        /* A valid tree contains only digits and the two supported operators. */
        if (nodes[node].data != '+' && nodes[node].data != '*') return -1;

        /* Each call keeps its own results; the left call finishes first. */
        int left = eval_tree(nodes[node].left);
        int right = eval_tree(nodes[node].right);

        /* Combine the returned values without changing the stored operator. */
        if (nodes[node].data == '+') return left + right;
        if (nodes[node].data == '*') return left * right;

        return -1;
}

int main(void)
{
        int root = terms();           /* Build the tree and keep its root index. */
        int answer = eval_tree(root); /* Evaluate the tree from that index. */
        printf("%s = %d\n", eq, answer);
        return 0;
}
```

The first line deserves its own explanation:

```c
#include <stdio.h>
```

`#` begins this **preprocessing directive**, an instruction handled as
part of preparing the source for compilation. `include` asks for the
named header's contents to be made available. `<` and `>` surround the
header name in this directive; they are not numeric comparisons here.
`stdio.h` is the standard input/output header. Its name refers to a
header file, and the dot in that name is not structure-field access.
The header supplies the declaration needed to call `printf` correctly.
This directive has no ending semicolon.

`int main(void)` defines the starting function for this program. `int`
specifies its return type, `main` is the required entry-point name here,
and `(void)` says this form receives no arguments. The braces enclose
its body. Its four statements run as follows:

1. `int root = terms();` declares a local integer, calls the builder,
   and initializes `root` with the returned root index, `1`.
2. `int answer = eval_tree(root);` passes that index to the evaluator
   and initializes `answer` with the returned number, `7`.
3. `printf("%s = %d\n", eq, answer);` displays a line of text.
4. `return 0;` ends `main` and reports successful completion.

The third line is a function call with three arguments. `printf` is
provided by the C standard library, a collection of supplied facilities
such as formatted output. The parentheses contain the arguments, and
the two commas separate them. The semicolon ends the call statement.

The first argument is the **format string** `"%s = %d\n"`. The double
quotes delimit the string in source code and are not printed. Within
that string:

| Part | Output meaning |
|---|---|
| `%s` | Print the string supplied by the next corresponding argument, `eq`, up to its null terminator. |
| The space, `=`, and following space | Print these literal characters between the expression and its answer. |
| `%d` | Print the integer supplied by the next corresponding argument, `answer`, in decimal form. |
| `\n` | Print a newline, moving subsequent output to the next line. |

Here `%` starts a formatting instruction inside the format string; it
is not being used as C's arithmetic remainder operator. `s` identifies
string formatting, and `d` identifies decimal integer formatting. The
`=` inside this quoted text is an output character, not assignment.
The backslash and `n` form one newline escape, rather than printing a
visible backslash followed by `n`.

The second argument, `eq`, supplies the character array holding the
expression. We pass the array's name to let `printf` read its string;
we do not write `eq[20]`, which would attempt to select an element beyond
the array. The third argument, `answer`, supplies the integer `7`. The
formatting instructions and argument types must match, as they do here.

`printf` itself returns information about its output, but this example
does not store that returned value. The function call can still perform
its printing job when its return value is unused.

The exact visible output is:

```text
1+2*3 = 7
```

A newline follows the final `7`. If we describe the output using an
escaped string, it is `"1+2*3 = 7\n"`; the quotes and `\n` spelling are
not additional visible text. Building and evaluating the tree produce
no other output in this program.

The `0` in `return 0;` is the program's success status, not the arithmetic
answer. `answer` remains `7` at the end of `main`; returning a status
of zero does not turn seven into zero or print another line.

If a C compiler is installed, save only the program's C text in a file
named `expression_tree.c`. In a terminal opened in that file's directory,
one way to compile and run it on macOS or Linux is:

```sh
cc -std=c11 -Wall -Wextra -pedantic expression_tree.c -o expression_tree
./expression_tree
```

These are terminal commands, not C statements to paste into the source
file. `cc` invokes the system's C compiler. `-std=c11` asks it to use the
C11 language standard, which supports the declarations used here.
`-Wall` enables a common collection of compiler warnings; despite the
name it does not mean literally every possible warning. `-Wextra`
enables additional warnings, and `-pedantic` asks for diagnostics about
certain departures from the selected language standard.

`expression_tree.c` names the source file. `-o expression_tree` names
the runnable output file. The spaces separate the command's arguments;
the hyphens begin compiler options rather than subtracting numbers.
Compilation may print nothing when it succeeds. The second command,
`./expression_tree`, runs the compiled program from the current directory;
`./` means “in this directory.” Do not include the code fences or the
`sh` formatting label when copying these commands.

### 14. What assumptions and boundaries must we remember?

The complete program is a small illustration, and its correctness relies
on its stated input and tree conditions. Understanding those conditions
is part of understanding what each line can safely mean.

For the input format, begin with exactly one digit from `0` through `9`.
After it, repeat an operator (`+` or `*`) followed by exactly one digit,
or stop. There must be no spaces or parentheses. The empty string is
not valid, and a trailing operator is not valid. Several adjacent digits
do not form a supported multi-digit number in this code.

A valid expression of this form always has odd length: one starting
digit plus two characters for each additional operator-and-digit pair.
In `eq[20]`, at most nineteen visible characters leave one position for
the terminating `'\0'`. With valid input, one node is reserved per visible
character, so at most nineteen nodes are used and they fit in `nodes[20]`.
The terminator is checked but never consumed as a node.

`new_node` does not check whether `size` has reached the array's capacity.
`term` does not check whether a supposed digit actually is a digit.
`terms` does not reject every unconsumed suffix. For example, an input
such as `"12+3"` can make it stop after the first digit; that behavior
is not support for the number twelve. These input forms are outside the
example's contract rather than cases the code correctly parses.

The node indices used during evaluation must identify reserved elements.
A completed operator must have two valid children, and following child
links must eventually reach digit leaves without a cycle. A newly
reserved operator temporarily has `-1` in both child fields while the
builders finish its children. The program waits until the whole tree
is built before evaluating it.

`-1` means “absent” in a child field, but must never be used as an array
index. The evaluator does not begin by rejecting an invalid `node`
argument, so calling `eval_tree(-1)` is not a supported way to ask about
an absent subtree. Correct digit leaves avoid that access by returning
in the base case before their child fields are followed.

The evaluator's `return -1;` lines handle unsupported stored characters
in a limited way. They do not make a malformed tree safe to access, and
a returned error is not separately propagated by the parent. A parent
would use any returned `-1` as an arithmetic operand. We therefore do
not use this evaluator as a general validator or rely on it to diagnose
arbitrary damaged data.

All intermediate and final results must fit in `int`. The code contains
no arithmetic range checks. Input that violates the storage, structure,
or arithmetic assumptions requires additional handling beyond this
example; the short functions do not establish those conditions themselves.

The global variables are initialized once when the program starts.
Calling `terms()` a second time in the same run does not automatically
restore `pos = 0` or `size = 0`. A new independent parse would need a
valid terminated expression and both counters reset before building.
Reusing the same array from index zero would overwrite the earlier tree,
so its old root index could no longer be treated as identifying the
original expression. For the experiments below, change the initializer
and run a freshly compiled program each time.

Here are three complete variants that stay within the assumptions:

| Input in a fresh run | Final root index | Final `size` | Final `pos` | Grouping | Printed output |
|---|---|---|---|---|---|
| `"7"` | `0` | `1` | `1` | A single digit leaf. | `7 = 7` |
| `"2*3*4"` | `3` | `5` | `5` | `(2 * 3) * 4` | `2*3*4 = 24` |
| `"1+2+3"` | `3` | `5` | `5` | `(1 + 2) + 3` | `1+2+3 = 6` |

Every printed output in the table ends with a newline. For `"7"`, both
builder loops execute zero times, and evaluation uses the base case
immediately. For `"2*3*4"`, the second star at index `3` has left child
`1` and right child `4`; the first star at index `1` has children `0`
and `2`. The same index shape holds for `"1+2+3"`, with plus signs in
place of stars. This makes the repeated left grouping visible in storage.

### 15. Can you predict the values before reading the answers?

Try each question using the definitions and traces above. “Index,”
“stored character,” and “numeric answer” refer to different things.

1. After the declaration `int size = 0;`, is `size` a C keyword or
   a name chosen by the programmer? What does the semicolon do?
2. How many nodes does `struct TreeNode nodes[20];` reserve space for?
   What are the first and last valid indices?
3. A node's `left` field is `0`. Does it have no left child? What
   does `-1` mean instead?
4. Before `new_node('8')`, `size` is `4`. Which node receives `'8'`,
   what are its initial child fields, what is returned, and what is
   the new value of `size`?
5. In `"1+2*3"`, suppose `pos` is `2`. What does `eq[pos]` read,
   and does it change `pos`? What does `eq[pos++]` read, and what
   value does it leave in `pos`?
6. Are `3`, `'3'`, and `"3"` the same thing? Is `'\0'` the visible
   digit `'0'`?
7. When the first `term()` call has consumed `'1'`, why does it stop
   before consuming the plus sign? How many times did its loop run?
8. In the complete example, why is the plus node's right child index
   `3` rather than `2`?
9. After building `"1+2*3"`, what are `size`, `pos`, and the root
   index? What does the root's `data` field contain?
10. For that tree, what does `eval_tree(4)` return? Why does it not
    follow the `-1` child indices?
11. During `eval_tree(3)`, what are the stored left and right child
    indices, and what are the local `left` and `right` answers?
12. Which finishes first: the left child evaluation or the right
    child evaluation of one operator? What in the code establishes
    that order?
13. After evaluation returns `7`, do the plus and star characters in
    the array become `7` and `6`?
14. In `printf("%s = %d\n", eq, answer);`, which argument supplies
    `%s`, which supplies `%d`, and what does `\n` do?
15. Does `return 0;` in `main` print zero or mean that the arithmetic
    answer was zero?
16. Will calling `terms()` again automatically start a fresh parse?
    Does the program support `"12+3"` or `"1 + 2"` as input?

**Answers**

1. `size` is our chosen name; `int` is the keyword. The semicolon
   ends the declaration. C does not make the name count nodes on
   its own; the program's statements maintain that count.
2. There is space for twenty nodes. The first index is `0`, and
   the last is `19`. Index `20` would be beyond the array.
3. A left field of `0` links to the first node, `nodes[0]`. The
   sentinel `-1` means that there is no left child.
4. `nodes[4]` receives `'8'`. Its left and right fields both become
   `-1`. The call returns index `4`, and `size` becomes `5`.
5. Both forms read `'2'`. Plain `eq[pos]` leaves `pos` at `2`;
   `eq[pos++]` uses that old index and leaves `pos` at `3`.
6. `3` is an integer, `'3'` denotes the digit's character code,
   and `"3"` is a string with a terminating null character.
   `'\0'` is the zero-valued terminator, not the visible digit `'0'`.
7. Its condition asks whether the next character equals `'*'`.
   The next character is `'+'`, so the condition is false. The
   loop body ran zero times, and the plus remains unread.
8. The next `term()` finishes the whole `2*3` group and returns
   its star-node root at index `3`. Index `2` is only the digit
   `'2'`, one child of that multiplication node.
9. `size = 5`, `pos = 5`, and the root index is `1`. The root's
   `data` is `'+'`. The unread character at position `5` is `'\0'`.
10. It returns integer `3`, because index `4` stores `'3'`.
    The digit base case returns before either child is accessed.
11. The stored child indices are `2` and `4`. The local child
    answers are `left = 2` and `right = 3`. Multiplication returns
    `6` from this call.
12. The left evaluation finishes first. Its call appears in a
    separate declaration before the declaration that calls the
    right child. That first statement finishes before the next begins.
13. No. The evaluator does not assign new values to those fields.
    The array still stores `'+'` and `'*'`, with the same child links.
14. `eq` supplies `%s`, `answer` supplies `%d`, and `\n` produces
    the newline after the displayed answer.
15. Neither. Returning `0` reports successful program completion.
    The answer printed by the preceding statement is still `7`.
16. No. The shared `pos` and `size` retain their values until code
    changes them or a fresh program starts. Neither example input
    fits the supported single-digit, no-space format.
