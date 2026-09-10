/*
 * INTENTIONALLY FAULTY PRECEDENCE, WITH VALID ARRAY LINKS.
 * Both operators are grouped from left to right, so 1+2*3 becomes (1+2)*3.
 * This standalone fixture does not depend on the starter or solution.
 */
#include "binary_tree.h"

#include <stdio.h>

static struct TreeNode demo_nodes[20];
static int demo_size = 0;
static char demo_eq[20] = "1+2*3";
static int demo_pos = 0;

static int demo_node(char data)
{
    int index = demo_size++;
    demo_nodes[index].data = data;
    demo_nodes[index].left = demo_nodes[index].right = -1;
    return index;
}

static int faulty_terms(void)
{
    int root = demo_node(demo_eq[demo_pos++]);

    while (demo_eq[demo_pos] == '+' || demo_eq[demo_pos] == '*') {
        int op = demo_node(demo_eq[demo_pos++]);
        int num = demo_node(demo_eq[demo_pos++]);

        /* Defect: every operator parents the whole expression so far. */
        demo_nodes[op].left = root;
        demo_nodes[op].right = num;
        root = op;
    }
    return root;
}

/* Both fixtures have valid digit leaves and two-child operator nodes. */
static int demo_eval(int node)
{
    if (demo_nodes[node].data >= '0' && demo_nodes[node].data <= '9') {
        return demo_nodes[node].data - '0';
    }
    int left = demo_eval(demo_nodes[node].left);
    int right = demo_eval(demo_nodes[node].right);
    return demo_nodes[node].data == '+' ? left + right : left * right;
}

int main(void)
{
    int faulty_root = faulty_terms();
    int faulty_answer = demo_eval(faulty_root);
    (void)printf("faulty:  %s = %d (root '%c')\n",
                 demo_eq, faulty_answer, demo_nodes[faulty_root].data);

    /* A separate, explicit fixture shows the intended hierarchy. */
    demo_nodes[0] = (struct TreeNode){ '1', -1, -1 };
    demo_nodes[1] = (struct TreeNode){ '+', 0, 3 };
    demo_nodes[2] = (struct TreeNode){ '2', -1, -1 };
    demo_nodes[3] = (struct TreeNode){ '*', 2, 4 };
    demo_nodes[4] = (struct TreeNode){ '3', -1, -1 };
    int correct_root = 1;
    int correct_answer = demo_eval(correct_root);
    (void)printf("correct: %s = %d (root '%c')\n",
                 demo_eq, correct_answer, demo_nodes[correct_root].data);

    if (faulty_answer == 9 && correct_answer == 7) {
        (void)puts("Precedence fault demonstrated.");
        return 0; /* Success means the planned defect was reproduced. */
    }
    return 1;
}
