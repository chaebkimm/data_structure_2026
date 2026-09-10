# Instructor Lesson Plan — Module 2: Binary Expression Trees

## Purpose and limits

This module follows Chapter 2 in `student/textbook.md` and
`student/textbook_korean.md`. Students represent expression structure in a
fixed array, construct that structure with operator precedence, and evaluate
it recursively. Every node stores one character and two integer child
indices. The four core implementations are `new_node`, `term`, `terms`, and
`eval_tree`.

Chapter 1 supplies fixed arrays, indices, conditions, loops, and invariants.
Introduce structure tags, field access, a shared parsing position, and
recursive calls here. Links use indices: `-1` means no child, while `0`
identifies the first node.

The module has two 90-minute meetings. Its input contract is a nonempty
expression alternating single digits and `+` or `*`, with no whitespace or
parentheses, at most 19 characters, and all intermediate and final values
fitting in an `int`. These are assumptions, not required input-validation
features. Binary-search ordering, dynamic allocation, graph validation, and
additional expression operators are outside the core.

## Learning targets

Students will be able to:

1. identify root, parent, child, sibling, leaf, ancestor, and subtree;
2. translate a hierarchy among a diagram, an index table, and C fields;
3. reserve and initialize the next node in a fixed array;
4. distinguish an index, a stored character, and an evaluated integer;
5. explain why fresh nodes and valid child indices preserve tree invariants;
6. trace the shared `pos` through `term()` and `terms()`;
7. build multiplication terms before combining them with addition;
8. evaluate children before their operator without changing the tree; and
9. support claims with tests, compiler evidence, and an autopsy explanation.

## Canonical representation and fixture

```c
struct TreeNode {
    char data; /* A digit character, '+', or '*'. */
    int left;  /* Child index, or -1 for no child. */
    int right;
};

struct TreeNode nodes[20];
int size = 0;
char eq[20] = "1+2*3";
int pos = 0;
```

The parser reserves nodes in expression-character order. Array position
does not determine a node's depth or whether it is the root.

```text
          [1] '+'
          /     \
      [0] '1'  [3] '*'
                /   \
            [2] '2' [4] '3'
```

| Index | `data` | `left` | `right` |
|---:|---|---:|---:|
| 0 | `'1'` | -1 | -1 |
| 1 | `'+'` | 0 | 3 |
| 2 | `'2'` | -1 | -1 |
| 3 | `'*'` | 2 | 4 |
| 4 | `'3'` | -1 | -1 |

The whole-expression root is index `1`; `size == 5`, `pos == 5`, and
`eq[pos] == '\0'`. Evaluation returns `7` while the operator fields still
store `'+'` and `'*'`.

Stage C uses `2*3+4*5`, with root index `3` for `'+'`, left root `1` for
`'*'`, and right root `5` for `'*'`. The digit indices are `0`, `2`, `4`,
and `6`, respectively. It evaluates to `26`.

The representation allows at most two children in named positions. A
completed expression for this grammar has two children at each operator
and none at each digit. Keep the general binary-tree rule distinct from
the stronger expression-shape rule.

## Beginner language sequence

| Word or symbol | First-use explanation |
|---|---|
| node | one array element holding a character and child links |
| index | an integer identifying a position in an array |
| `nodes[root]` | the node selected by the root index |
| `nodes[root].data` | the data field of that selected node |
| `-1` | no child; never an index to dereference |
| `size` | number of used nodes and index of the next unused slot |
| `eq` | the expression string, terminated by `\0` |
| `pos` | index of the next unread character in `eq` |
| consume | read a character and advance `pos` |
| term | one digit followed by zero or more multiplication-digit pairs |
| precedence | which operation groups more tightly in an expression |
| left association | make each later operator the parent of the group built so far |
| recursion | a function calling itself on a smaller part of the problem |
| base case | a case handled without further recursive calls |
| precondition | a fact established before calling an operation |

Introduce hierarchy vocabulary from the Stage B vocabulary sheet. A parent
is a relationship: this structure stores no upward link. Require students
to identify whether an integer in a trace is an array index or a returned
arithmetic value.

## Five release gates

| Gate | Release time | Give students | Hold back |
|---|---|---|---|
| A — Initial inquiry | before Meeting A | standard or linear inquiry prompt | representation, vocabulary, code, answers |
| B — Model and pause | after the first model is saved | index representation reveal, vocabulary, three-target Cognitive Pause | expert calibration and investigation |
| C — Investigation | after the pause and calibration | standard or linear investigation | worked notes, code, answers |
| D — Textbooks and models | after the Stage C attempt is saved | both English and Korean textbooks, diagram/text models | lab, autopsy prediction answers, instructor materials |
| E — Lab and evidence | Meeting B | lab, 100-point rubric, evidence form, autopsy, header, starter, public tests, build files | solution, instructor extension tests, answer key |

Accommodations may change timing without changing the reasoning target.
Preserve the sequence “attempt, compare, correct.” Vocabulary begins in
Stage B. Stage D teaches correct construction and evaluation without
revealing the Stage E autopsy's worked prediction.

## Meeting A — Model and Reason (90 minutes)

Macro-question: How can a hierarchy preserve the meaning of an expression,
and how can we build and evaluate that hierarchy using a fixed array?

| Minutes | Activity | Evidence |
|---:|---|---|
| 0–8 | Retrieve array indices, bounds, loops, and invariants | Entry response |
| 8–18 | Stage A expression-structure inquiry | Preserved first model |
| 18–28 | Compare proposed groupings and starting items | Annotated relationships |
| 28–38 | Stage B reveal: character data and two child indices | Index/field labels |
| 38–43 | Five-minute Cognitive Pause | Three independent responses |
| 43–54 | Calibrate the three pause targets | Corrected pause |
| 54–70 | Stage C index tables, parsing position, and root changes | Worksheet traces |
| 70–80 | Trace child results and operator results | Return-value trace |
| 80–88 | Compare structural validity with expression meaning | Invariant and precedence claims |
| 88–90 | Exit ticket | One supported correction |

### Stage B calibration

The three independent pause targets are:

1. distinguish root index `1`, its left index `0`, the character `'1'`, and
   an absent child `-1`;
2. trace a fresh `term()` call on `1+2*3`: root `0`, `size == 1`,
   `pos == 1`, and the `+` remains unread; and
3. trace completed evaluation results `1, 2, 3, 6, 7`, explaining that
   operator characters and all other tree/parser state remain unchanged.

Keep their initial responses, then add corrections with reasons. A valid
index and a numeric result may have the same integer value while serving
different roles.

### Representation and construction demonstration

Reserve a digit at the next unused slot and show all three initialized
fields. The returned old value of `size` identifies the node; the new
value of `size` identifies the next unused slot. An index can remain usable
after `new_node()` returns because the node lives in the global array.

Build a fresh parent above an existing root by assigning the old root to
the parent's left field and a freshly built operand to its right. Replace
the local root with the parent index. This does not move a node in memory.

For each parsing step, record `pos`, `eq[pos]`, `size`, the current root,
and new child assignments. Explain why `term()` stops before `+` and why
`terms()` requests a complete term for each addition operand. The shared
`pos` makes the next call continue where the preceding call stopped.

Trace repeated operators as well as mixed operators. Each new operator is
the parent of the group already built, producing left association at its
level. Inspect links to prove this shape: addition and multiplication
values alone do not distinguish all alternative groupings.

### Invariant and evaluation calibration

A valid expression tree has one root, no cycles, and one incoming child
link at every other reachable node. Each nonempty child index selects an
initialized slot below `size`. Equal characters in two slots identify two
different nodes; using one child index twice introduces sharing.

An unused child field alone does not establish that an attachment is safe.
The construction algorithm uses fresh nodes and disjoint subtrees to
preserve the rules. Discuss cycles on paper without evaluating them.

A digit returns its character minus `'0'`. An operator waits for its left
call and then its right call, combines the two local results, and returns
its answer. Node fields, `eq`, `size`, and `pos` stay unchanged during
evaluation. A structurally valid tree can still encode the wrong grouping.

### Formative checks

- Does root index `0` mean an empty tree? No; it identifies the first slot.
- Does `term()` consume the `+` where it stops? No.
- Does finishing one `term()` necessarily finish the expression? No.
- Does `new_node()` alone attach its node to a parent? No.
- Must the final root be the last reserved index? No.
- Does evaluation replace an operator character with its answer? No.

## Between meetings

1. Preserve the Stage C attempt before releasing Stage D.
2. Ask students to annotate earlier answers using either textbook language
   and the shared models; make both textbooks available.
3. Release Stage E for Meeting B.
4. Validate reference tests and the standalone autopsy with strong warnings
   and supported runtime checks.

## Meeting B — Implement, Test, and Explain (90 minutes)

| Minutes | Activity | Evidence |
|---:|---|---|
| 0–8 | Retrieve index links, precedence, and digit base case | Re-entry response |
| 8–18 | Read the four-function contract and input assumptions | Header annotations |
| 18–28 | Implement `new_node` and test fresh slots | Creation assertions |
| 28–43 | Implement `term` and trace unread `+` | Term trace and assertions |
| 43–56 | Implement `terms` and inspect mixed-operator links | Precedence and association assertions |
| 56–68 | Implement `eval_tree` and compare state before/after | Results and nonmutation assertions |
| 68–77 | Run public tests and finish three authored tests | Transcript and rationales |
| 77–87 | Preserve an autopsy prediction, then run and explain it | Incident record |
| 87–90 | Check submission against the 100-point rubric | Evidence checklist |

### Coaching boundaries

Coach the contract through short questions about the current state: which
slot is unused, which character remains unread, which index is the old
root, which operand must be a complete term, and which value returns to
the waiting call. Distinguish character `'3'` from integer `3` and both
from index `3`.

Before an independent expression run, reset `size` and `pos` to zero and
copy a valid, bounded expression into `eq`. Old root indices no longer
identify the previous logical tree after its slots are reused. A reset
helper or parser wrapper is not an additional required API.

Do not require malformed-input rejection, empty-expression handling, or
overflow detection. The evaluator's fallback return does not validate bad
indices, missing operands, or cycles.

## Tests, autopsy, and assessment

Require three nonduplicate student-authored tests, each with a rationale:

1. node creation: returned indices, advancing `size`, stored character,
   and both absent children;
2. expression construction: correct links for precedence and left
   association, plus the final unread position; and
3. recursive evaluation: correct results and unchanged node fields and
   parser state.

| Criterion | Points |
|---|---:|
| Representation and invariants | 20 |
| Node creation | 15 |
| Expression construction | 20 |
| Recursive evaluation | 20 |
| Operation efficiency | 10 |
| Tests and tool evidence | 10 |
| Autopsy and forward transfer | 5 |
| Total | 100 |

Instructor extension tests add valid boundary and sequence evidence without
expanding the four-function contract. The standalone
`code/autopsy/faulty_precedence.c` builds a structurally valid tree with an
incorrect precedence policy. Students predict before running, compare the
observed tree and result, explain the construction defect, and propose a
regression test. Keep worked answers in the instructor answer key. The
autopsy does not require a fourth student-authored C test.

Provide linear text, selectable commands, verbal or tactile equivalents,
and instructor CI where needed. Grade reasoning and evidence, not drawing
quality, typing speed, or exact memorized terminology.
