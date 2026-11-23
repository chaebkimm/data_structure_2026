# Module 12 — Binary Search and BSTs

**Course-plan update — 2026-11-10.** Week 12 now develops binary search
and ordinary BST search/insertion. AVL balance, rotations, and guided
insertion belong to [Module 13](../module_13_avl_review/README.md).
Follow the [14-week delivery guide](../Data_Structures_Course_2026_14_Week_Delivery_Guide.md)
and [Chapter 12 planning summary](../instructor_guide/chapter_12.md).

Teaching-content alignment remains pending. Existing textbooks,
worksheets, lab guides, detailed lesson plans, tests, and releases await
alignment. The directory is now named `module_12_binary_search_bst`, while
the supplied AVL source remains grouped in Module 12;
that source is a reference for the revised Week 13, not a required Week 12
AVL assignment. No revised student release is supplied here.
Existing ZIP filenames and release-script defaults retain their original
names; archives have not been regenerated.

## Required learning and assessment outline

Start with a linear-search recap, then trace first-match binary search on
supplied sorted arrays. Explain why order allows interval elimination and
why the returned index belongs to the array being searched. Transfer the
smaller/larger decision to BST ordering, search, insertion, and inorder.

Use ascending, descending, and mixed insertions to connect edge height to
visited-node comparisons. A BST can preserve ordering and still become a
chain. Finish with that skewed tree as Week 13's repair problem.

One submission combines interval and BST traces, original search/insertion
checks, inorder/height/comparison evidence, and a corrected explanation.
BST deletion is outside required scope. Sorting implementations are optional;
provide sorted inputs directly. AVL checks are assessed in Week 13.

| Required contact activity | Minutes |
|---|---:|
| Linear-search recap and first-match binary search on supplied sorted arrays | 45 |
| BST ordering, search, insertion, and inorder reasoning | 60 |
| Height, insertion-order effects, and search costs; finish with a skewed tree | 35 |
| Traces, checks, and one combined evidence artifact | 40 |
| **Total** | **180** |

## Existing teaching resources — pending alignment

These resources retain the previous combined BST/AVL lesson. Their weekly
labels and complete submission requirements await alignment. Select only
search/BST references for Week 12; use AVL references in Week 13.

| Existing material | Reference use |
| --- | --- |
| [Textbook](student/textbook.md) · [Vocabulary](student/vocabulary.md) | Ordering and tree-height background; AVL content belongs to Week 13 |
| [Initial inquiry](student/inquiry_prompt.md) · [Linear version](student/inquiry_prompt_linear.md) | Existing tree-repair inquiry |
| [Representation reveal](student/representation_reveal.md) · [Cognitive Pause](student/cognitive_pause.md) | Indexed nodes and retrieval references |
| [Investigation](student/investigation_worksheet.md) · [Linear version](student/investigation_worksheet_linear.md) | Existing AVL link/height/root traces |
| [Lab](student/lab.md) · [Lab slides](student/ppt_lab_material.md) | Existing supplied AVL source walkthrough |
| [Evidence](student/evidence_template.md) · [Rubric](student/rubric.md) | Previous submission outline, not the revised Week 12 assignment |
| [Autopsy](student/tree_rotation_autopsy.md) · [Models](diagrams/bst_avl_models.md) | AVL repair references for Week 13 |
| [Detailed lesson plan](instructor/lesson_plan.md) | Previous combined lesson; use the revised budget above |
| [Code guide](code/README.md) · [Release manifest](release/release_manifest.md) | Existing builds and releases, not revised weekly packaging |
| [Search/sort textbook](../module_13_avl_review/student/textbook.md) · [Korean](../module_13_avl_review/student/textbook_korean.md) | Binary-search reference still stored in Module 13; pending alignment |
| [Week 12 questions](../student_question_bank/week_12_avl.md) | Existing question bank, pending alignment |

## Existing AVL source contract — Week 13 reference

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

## Existing AVL reference build and checks

The protected lab slides retain the previous folder name in their build
command. Use the replacement command below; the slides remain unchanged.

From the repository root:

```sh
make -C module_12_binary_search_bst/code lab-compile core student-tests comparison
```

Each driver includes the actual lab exactly once. The build adds include
paths for `student/` and the repository root so the Module 2 include resolves.
Do not link another compiled copy of either included source.

The existing `code/tests/test_lab_student.c` contains rotation/subtree,
measurement, and duplicate/boundary evidence. The supplied core also checks
all 5,040 insertion orders of seven distinct keys. See the
[existing lab](student/lab.md) (submission outline pending alignment) and the
[code guide](code/README.md) (weekly role pending alignment) for PowerShell,
sanitizers, and the inherited Module 2 warnings. These checks remain reference
material; this planning pass changes no test or build target.

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
