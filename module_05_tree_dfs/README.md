# Module 5 — Depth-First Traversal and Expression Trees

The current lecture follows [`student/lab.c`](student/lab.c), the
[lab slides](student/ppt_lab_material.md), and the
[Chapter 5 textbook](student/textbook.md). Nodes store characters and integer
child indices in `nodes[10]`; `-1` marks an absent child.

Students first trace the alphabet tree rooted at `F`. The three comment
positions in `tree_traversal()` mark where preorder, inorder, and postorder
data processing belongs; the lab does not yet perform visit actions there.

Students then trace `tree_traversal_with_stack()` using three per-node
progress steps. `build_tree_from_postfix()` uses the shared Chapter 4 stack
to join expression subtrees, popping right before left and returning the
root with a final pop. Prepare the initially empty `postfix` before use.

`write_infix()` writes inorder symbols with parentheses that preserve the
tree's grouping. `prec2()` gives digits precedence 3; a child with lower
precedence is parenthesized on the left, and a child with lower or equal
precedence is parenthesized on the right. The wrapper resets `infix_pos`
and terminates each result in `infix[20]`, supporting repeated writes.
Stack traversal still needs zeroed `progress` before another run. Input
is valid nonempty postfix of at most seven
tokens: single digits and binary `+ - * / %`, with no spaces. Neither input
nor output bounds are validated.

The companion [concept slides](student/ppt_material.md) also reconstruct
an `A`-rooted tree from preorder and inorder. Treat reconstruction as a
supplement to the lab slides' four-step sequence; `lab.c` has no
reconstruction function.

## Lecture materials

- [Instructor guide](../instructor_guide/chapter_05.md): questions and board traces.
- [Lesson plan](instructor/lesson_plan.md): two meetings within 180 minutes.
- [Technical notes](instructor/technical_notes.md) and [answer key](instructor/answer_key.md): implementation facts and instructor checks.
- [Initial inquiry](student/inquiry_prompt.md) and [linear version](student/inquiry_prompt_linear.md): predictions before the reveal.
- [Representation reveal](student/representation_reveal.md), [pause](student/cognitive_pause.md), and [vocabulary](student/vocabulary.md): name and explain the observed operations.
- [Investigation worksheet](student/investigation_worksheet.md) and [linear version](student/investigation_worksheet_linear.md): equivalent reasoning tasks.
- [Tree models](diagrams/dfs_models.md) and [question bank](../student_question_bank/week_05_tree_dfs.md): lecture and discussion support.
- [Runnable demo](code/lecture/lab_demo.c): the textbook's driver using the actual lab source.

From `code/`, run `make lecture` (or the default `make`) and `make lab-tests`.
For PowerShell, run
`./build.ps1 -Target lecture`. See the [code guide](code/README.md) for
manual compilation and expected output. `lab.c` has no `main`; the demo
supplies it. Predict the output before running it.

## Separate earlier exercises

The pointer-based copy/print/evaluate exercise remains in `code/include`,
`code/starter`, `code/solution`, and its original tests and autopsy as an
optional comparison. The [lab instructions](student/lab.md), rubric, and
evidence record identify the current classroom core and keep the pointer
API's optional requirements separate. Its original tests do not test
`student/lab.c`; use `make lab-tests` for the classroom implementation.

The Stage E release includes the current lab, its Chapter 2 and Chapter 4
dependencies, the lecture demo, and direct lab checks, alongside the
optional pointer exercise. The [iterative traversal sample](code/lecture/iterative_traversals.c)
is an optional pointer-based comparison; it is not the implementation in
`student/lab.c`.
