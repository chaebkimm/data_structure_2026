# Module 12 — AVL Insertion with Indexed Nodes

The required Week 12 lesson follows [`student/lab.c`](student/lab.c).
It reuses Module 2's ten character nodes and integer child links, then adds
stored heights, four rotations, and recursive AVL insertion. The complete
source is supplied. Students predict states, trace the code, and extend
assertion tests. There are no required implementation TODOs.

The inquiry, traces, BST comparison, and tests form **one submission within
180 minutes**. Follow the [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md).
Full AVL deletion is outside the required lab.

## Teaching materials

| Material | Purpose |
| --- | --- |
| [Textbook](student/textbook.md) · [Vocabulary](student/vocabulary.md) | Develop ordering, edge height, balance, and local repair |
| [Initial inquiry](student/inquiry_prompt.md) · [Linear version](student/inquiry_prompt_linear.md) | Preserve an initial model before introducing names and formulas |
| [Representation reveal](student/representation_reveal.md) · [Cognitive Pause](student/cognitive_pause.md) | Connect the model to indexed nodes and retrieve the key ideas |
| [Investigation](student/investigation_worksheet.md) · [Linear version](student/investigation_worksheet_linear.md) | Trace links, cached heights, and returned roots |
| [Lab](student/lab.md) · [Lab slides](student/ppt_lab_material.md) | Run and explain the supplied source |
| [Evidence](student/evidence_template.md) · [Rubric](student/rubric.md) | Assemble the single Week 12 submission |
| [Autopsy](student/tree_rotation_autopsy.md) · [Models](diagrams/bst_avl_models.md) | Diagnose lost links and stale heights |
| [Lesson plan](instructor/lesson_plan.md) · [Chapter guide](../instructor_guide/chapter_12.md) | Deliver the unit in 180 minutes |
| [Code guide](code/README.md) · [Release manifest](release/release_manifest.md) | Build and distribute the current lab |

## Actual source contract

The include `module_02_binary_tree/student/lab.c` supplies:

```c
struct TreeNode {
    char data;
    int left;
    int right;
};
struct TreeNode nodes[10];
```

Root and child links are node IDs `0..9`; `-1` means no node. A label is
`nodes[id].data`, not the ID itself. `alphabet_init()` assigns A through J
and initializes every child link to `-1`. Its `nodes_size` becomes 10; that
is not the number of records reachable from the current root.

`height[10]` is a separate array indexed by the same IDs. A missing subtree
has edge height `-1`, and a leaf has height `0`. `get_balance(l,r)` returns
left height minus right height. Every completed AVL subtree has a balance
factor in `[-1,1]` and an exact stored height.

`_add(i,new_node)` receives an existing subtree root and a fresh, detached
node ID whose label is already loaded and whose children are both `-1`.
It returns the possibly changed subtree root. Always retain that result:

```c
alphabet_init();
int root = -1;
root = _add(root, 2);  /* C */
root = _add(root, 0);  /* A */
root = _add(root, 1);  /* B; LR repair returns ID 1 */
```

The caller supplies valid indices, at most ten distinct node IDs, and a
valid AVL tree with correct heights. The code has no allocation, capacity
rejection, input validator, status code, deletion, or search operation.
Reinserting an already linked ID is invalid.

Equal labels are accepted on different IDs. Insertion follows the left
branch on `<=`; a rotation can later put an equal label on the right.
The lasting ordering rule is **left labels ≤ current label ≤ right labels**
throughout the subtrees, equivalently a nondecreasing inorder sequence.

## How repair works

The recursive return is assigned both to the real child link and the local
`l` or `r`. The current frame therefore uses the child's new root when it
computes balance. A balanced frame refreshes its height and returns `i`.
An unbalanced frame selects a case from the child's subtree heights.

The four `rotate_*` functions only reconnect links using the saved child
and grandchild IDs. They do not refresh heights. `_add` performs those
updates after each rotation, from children to the new local root:

| Case | Three-label insertion | Height update order |
| --- | --- | --- |
| LL | C, B, A | `i`, then `l` |
| RR | A, B, C | `i`, then `r` |
| LR | C, A, B | `i` and `l`, then `lr` |
| RL | A, C, B | `i` and `r`, then `rl` |

All four cases finish with B over A and C, stored heights `1,0,0`, and
inorder A, B, C. LR and RL implement the effect of two rotations through
one direct link-rewiring helper call in this source.

## Seven-label comparison

Use stable IDs A=0 through G=6 and insert each ID once:

```text
ascending:  A B C D E F G
descending: G F E D C B A
mixed:      D B F A C E G
```

The driver supplies the ordinary BST baseline and search counter. Count
one logical key comparison per visited node, including a matching node;
the final `-1` link adds no comparison.

| Order | Present / missing probe | BST height | BST comparisons, each probe | AVL height | AVL comparisons, each probe |
| --- | --- | ---: | ---: | ---: | ---: |
| ascending | G / H | 6 | 7 | 2 | 3 |
| descending | A / @ | 6 | 7 | 2 | 3 |
| mixed | G / H | 2 | 3 | 2 | 3 |

All three AVL builds finish at ID 3, label D. These examples fit the actual
ten-slot buffer. Search and comparison counts are driver evidence, not
functions or counters exported by `lab.c`.

## Build and evidence

From the repository root:

```sh
make -C module_12_bst_avl/code lab-compile core student-tests comparison
```

Each driver includes the actual lab exactly once. The build adds include
paths for `student/` and the repository root so the Module 2 include resolves.
Do not link another compiled copy of either included source.

Extend `code/tests/test_lab_student.c` with original rotation/subtree,
measurement, and duplicate/boundary evidence. The supplied core also checks
all 5,040 insertion orders of seven distinct keys. See the
[lab](student/lab.md) for the submission and the [code guide](code/README.md)
for PowerShell, sanitizers, and the inherited Module 2 warnings.

## Cost and optional reference

For a generalized tree of `n` nodes and height `h`, one rotation costs
`O(1)` and insertion follows one path in `O(h+1)` time and active calls.
AVL balance gives `O(log(n+1))` insertion time and call space. A plain
sorted BST can have height `n-1`. The driver validator scans the whole tree
in `O(n)` time; exclude it from ordinary insertion/search work.
The concrete arrays reserve ten slots each.

Sorted input can degrade plain-BST search work. That is an
algorithmic-complexity problem, distinct from an invalid memory access or
running out of a finite resource. The lab does not validate external input.

`code/include`, `code/starter`, `code/solution`, `code/support`, the older
`test_core.c`/`test_extension.c`/`test_student.c`, and `code/autopsy` retain
an optional 64-node pointer library. Its strict duplicate rejection,
allocation failure contracts, iterative destruction, and TODOs belong to
that reference. Named `solution-*` and `starter-*` targets remain available.
