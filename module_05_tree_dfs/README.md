# Module 5 — Depth-First Traversal and Expression Trees

The current lecture follows [`student/lab.c`](student/lab.c) and the
[Chapter 5 textbook](student/textbook.md). Nodes store characters and integer
child indices in `nodes[10]`; `-1` marks an absent child.

Students first trace the alphabet tree rooted at `F`. The three assignment
positions in `tree_traversal()` show preorder, inorder, and postorder. The
globals retain only their last assigned characters, `G`, `G`, and `F`.

Students then trace `tree_traversal_with_stack()` using three per-node
progress steps, and reconstruct the slides' `A`-rooted tree from preorder
and inorder. `build_tree_from_postfix()` uses the shared Chapter 4 stack
to join expression subtrees, popping right before left and returning the
root with a final pop. Prepare the initially empty `postfix` before use.

`write_infix()` emits bare inorder symbols and terminates the output.
Stack traversal and writing currently support one run. Parentheses,
progress resets, and output-position resets are extension exercises from
the slides/textbook. Input is valid nonempty postfix of at most seven
tokens: single digits and binary `+ - * / %`, with no spaces. Neither input
nor output bounds are validated.

## Lecture materials

- [Instructor guide](../instructor_guide/chapter_05.md): questions and board traces.
- [Lesson plan](instructor/lesson_plan.md): two meetings within 180 minutes.
- [Technical notes](instructor/technical_notes.md) and [answer key](instructor/answer_key.md): implementation facts and instructor checks.
- [Initial inquiry](student/inquiry_prompt.md) and [linear version](student/inquiry_prompt_linear.md): predictions before the reveal.
- [Representation reveal](student/representation_reveal.md), [pause](student/cognitive_pause.md), and [vocabulary](student/vocabulary.md): name and explain the observed operations.
- [Investigation worksheet](student/investigation_worksheet.md) and [linear version](student/investigation_worksheet_linear.md): equivalent reasoning tasks.
- [Tree models](diagrams/dfs_models.md) and [question bank](../student_question_bank/week_05_tree_dfs.md): lecture and discussion support.
- [Runnable demo](code/lecture/lab_demo.c): the textbook's driver using the actual lab source.

From `code/`, run `make lecture`. For PowerShell, run
`./build.ps1 -Target lecture`. See the [code guide](code/README.md) for
manual compilation and expected output. `lab.c` has no `main`; the demo
supplies it. Predict the output before running it.

## Separate earlier exercises

The pointer-based copy/print/evaluate exercise remains in `code/include`,
`code/starter`, `code/solution`, and its original tests and autopsy. Its
[lab instructions](student/lab.md), rubric, evidence record, and Stage E
release use that earlier API. Those requirements do not describe the
current lecture or test `student/lab.c`.

The staged release script still packages that earlier Stage E exercise and
does not include the new lecture driver. Use the repository lecture files
above for this lesson. The [iterative traversal sample](code/lecture/iterative_traversals.c)
is an optional pointer-based comparison; it is not the implementation in
`student/lab.c`.
