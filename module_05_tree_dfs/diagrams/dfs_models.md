# Tree DFS Models

Models for the current [lab](../student/lab.c) and [slides](../student/ppt_material.md).

## Array tree and visits

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
preorder:  F A B D E C G     final G
inorder:   D B E A C F G     final G
postorder: D E B C A G F     final F
```

At `D`, real-node calls are `F → A → B → D`. Each leaf calls on `-1`
twice, returning immediately; four real frames plus one empty frame can
be active. The three globals store final values, not complete orders.

## Explicit stack and progress

```text
step 0: preorder; advance progress; push left
step 1: inorder;  advance progress; push right
step 2: postorder; advance progress; pop current
negative top: pop without reading data or progress

[5] → [5,0] → [5,0,1] → [5,0,1,3]
→ [5,0,1,3,-1] → [5,0,1,3]
→ [5,0,1,3,-1] → [5,0,1,3] → [5,0,1] → [5,0,1,4]
```

Reached nodes finish at progress 3. Reset progress for another run.

## Reconstruction exercise from the slides

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
reconstruction is not implemented in the lab.

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
is three indices. The shared nodes replace the alphabet tree.

## Current writer versus grouping extension

| Postfix | Current bare inorder | Slides' extension |
| --- | --- | --- |
| `123*+` | `1+2*3` | `1+2*3` |
| `12+3*` | `1+2*3` | `(1+2)*3` |
| `123--` | `1-2-3` | `1-(2-3)` |
| `12-3-` | `1-2-3` | `1-2-3` |
| `123++` | `1+2+3` | `1+(2+3)` |

Extension: parenthesize operator children using parent `>` left precedence
or parent `>=` right precedence. `prec()` gives digits 0, so exclude them.

```text
write_infix(root)
    _write_infix(root)       shared infix_pos; no reset
    infix[infix_pos++] = '\0'

123*+ → 1 + 2 * 3 \0       final infix_pos = 6
```

The current wrapper supports one write; reset position for reuse.
`postfix[8]` permits seven tokens, whose bare output fits `infix[10]`.
Adding parentheses can require twelve bytes for `1+(2+(3+4))`. An
iterative ten-node chain also needs eleven stack slots with its sentinel.
No input or capacity checks are supplied.
