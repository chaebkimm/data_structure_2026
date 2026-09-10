#ifndef BINARY_TREE_H
#define BINARY_TREE_H

struct TreeNode {
    char data; /* A digit character, '+', or '*'. */
    int left;  /* Index in nodes; -1 means no child. */
    int right; /* Index in nodes; 0 is a valid child index. */
};

/* One expression at a time; these objects live for the whole program. */
extern struct TreeNode nodes[20];
extern int size;    /* Used nodes and the next unused array index. */
extern char eq[20]; /* Initially "1+2*3". */
extern int pos;     /* Next unread character in eq. */

/*
 * Input contract: a nonempty expression of single digits separated by '+'
 * or '*', with no whitespace or parentheses, and at most 19 characters plus
 * the ending '\0'. Every intermediate and final result must fit in int.
 * These teaching functions assume valid input; they do not check it.
 * Before each independent expression, set size = 0 and pos = 0 and copy
 * the valid expression into eq. Previous root indices then become obsolete.
 */

/* Reserve nodes[size], initialize both links to -1, and return its index.
 * Requires 0 <= size < 20. Allocation advances size but does not read eq. */
int new_node(char data);

/* Build one digit followed by zero or more '*'-digit pairs at eq[pos].
 * Return the term's root index; leave the next '+' or '\0' unread. */
int term(void);

/* Build a sum of complete terms, so multiplication has higher precedence.
 * Return the expression's root index; pos stops at the ending '\0'.
 * Within each operator level, new operators parent the tree built so far. */
int terms(void);

/* Return the integer result of a completed expression subtree, preserving
 * node data and links. Requires a valid root index and a finite, acyclic
 * tree with no shared children. Digit leaves are the recursive base case;
 * each operator has two children. Never pass -1 as an evaluation root. */
int eval_tree(int node);

#endif
