# Tree DFS Models

Models for the current [lab](../student/lab.c) and
[lab slides](../student/ppt_lab_material.md).

## Array tree and visit hooks

```text
          F [5]
         /     \
      A [0]   G [6]
      /   \
   B [1] C [2]
   /   \
D [3] E [4]
```

```text
nodes_size = 10; root = 5; reachable = 7; unconnected = H, I, J
recorded preorder hook:  F A B D E C G
recorded inorder hook:   D B E A C F G
recorded postorder hook: D E B C A G F
```

These are predicted symbol traces if recording actions are placed at the
visit comments. The source comments alone record nothing. At `D`, active
real-node calls are `F → A → B → D`. Each leaf calls on `-1` twice,
returning immediately; four real frames plus one empty frame can be active.

## Explicit stack and progress

```text
tree_traversal_proceed(peek()) receives top node index i
negative i: pop before reading nodes[i] or progress[i]
real i: step = progress[i]++ (old step; advance stored progress)

step 0: preorder hook;  push left
step 1: inorder hook;   push right
step 2: postorder hook; pop current

[5] → [5,0] → [5,0,1] → [5,0,1,3]
→ [5,0,1,3,-1] → [5,0,1,3]
→ [5,0,1,3,-1] → [5,0,1,3] → [5,0,1] → [5,0,1,4]
```

Stacks are shown bottom to top. Reached nodes finish at progress 3 and the
stack finishes empty. The wrapper resets `top` only; reset progress to 0
before another traversal, including after constructing a replacement tree.

## Postfix construction

```text
Input:  1       2         3           *        +
Index:  0       1         2           3        4
Stack: [0] → [0,1] → [0,1,2] → [0,3] → [4] → []
                                right=2   right=3  return pop(): 4
                                left=1    left=0

          + [4]             nodes_size = 5; final top = -1
         /     \
      1 [0]   * [3]
              /   \
           2 [1] 3 [2]
```

Prepare `postfix` first; its initial value is empty. Peak stack use here
is three indices. Construction replaces the alphabet tree and records
structure without calculating a result.

## Precedence-aware infix reconstruction

| Postfix | Bare inorder thought experiment | Current writer |
| --- | --- | --- |
| `123*+` | `1+2*3` | `1+2*3` |
| `12+3*` | `1+2*3` | `(1+2)*3` |
| `123--` | `1-2-3` | `1-(2-3)` |
| `12-3-` | `1-2-3` | `1-2-3` |
| `123++` | `1+2+3` | `1+(2+3)` |
| `1234+++` | `1+2+3+4` | `1+(2+(3+4))` |

```text
prec2(digit) = 3; prec2(* / %) = 2; prec2(+ -) = 1
left child:  wrap when child < parent
right child: wrap when child <= parent

write_infix(root)
    infix_pos = 0
    _write_infix(root)        shared cursor; parentheses around child calls
    write_char('\0')

123*+ → 1 + 2 * 3 \0         terminator index 5; final infix_pos 6
12+3* → ( 1 + 2 ) * 3 \0     next complete call restarts at index 0
```

The right equality rule preserves the tree under left associativity.
`write_infix(-1)` writes the empty string; missing operator children are
still unchecked because the helper reads their data before recursion.

`postfix[8]` permits seven tokens; `infix[20]` fits grouping output in this
range. `1+(2+(3+4))` needs twelve cells including its terminator. An
iterative ten-node chain needs eleven stack slots with its absent-child
sentinel. No input or capacity checks are supplied.

## Optional reconstruction exercise from the general slides

```text
preorder ABDECFG    inorder DBEAFCG    postorder DEBFGCA
root A; left inorder DBE / preorder BDE; right inorder FCG / preorder CFG

        A
       / \
      B   C
     / \ / \
    D  E F  G
```

Distinct labels permit unique inorder splits. This is a separate tree;
reconstruction is not implemented in the four-step lab sequence.
