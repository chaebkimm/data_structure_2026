# Module 2 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script validates required sources and refuses to
overwrite an existing archive. Do not generate archives before the reference
and release checks pass.

## Stage A — Initial Hierarchy Inquiry

Release before Meeting A:

- standard initial prompt; and
- linear accessible initial prompt.

Students reconstruct the expression hierarchy `(3 + 5) * 2` without C
representation vocabulary. This stage contains no node representation,
vocabulary reference, worked invariant, code, solution, or instructor
material.

## Stage B — Representation and Cognitive Pause

Release after students preserve their first hierarchy model:

- child-only binary representation reveal;
- vocabulary reference; and
- three-target Cognitive Pause.

The reveal maps `(3 + 5) * 2` to local nodes named `root`, `plus`, `three`,
`five`, and `two`. The pause addresses named left/right operand positions,
caller responsibility for acyclic construction, and the search sequence
`'*', '+', 3, 5, 2`. Withhold expert calibration until every student preserves
a first response, including approved extended-time or asynchronous
equivalents.

## Stage C — Structural Investigation

Release after the pause and instructor calibration:

- standard investigation worksheet; and
- linear accessible investigation worksheet.

Students translate the fresh expression `(8 - 3) * (4 + 2)` into local-node
addresses, distinguish named child sides, reason about paths and caller
preconditions, trace recursive search, and separate clearance from
detachment. No answer key is supplied.

## Stage D — Textbook and Models

Release after the Stage C attempt is preserved:

- the current expression-tree-framed binary-tree textbook; and
- correct-operation diagrams with text equivalents.

Do not include worked predictions or repair answers for the Stage E
autopsy. Generic correct clearance examples are separate from that fixture.

## Stage E — Lab and Evidence

Release for Meeting B:

- lab, 100-point rubric, evidence template, and Tree Structure Autopsy;
- `include/binary_tree.h` and `starter/binary_tree.c`;
- supplied core tests and the student-test template;
- student-only PowerShell and GNU Make build files; and
- isolated `autopsy/faulty_cascade.c`.

Only `tree_find` and `tree_clear` are library implementation tasks.
Direct initialization, guarded attachment, and caller-side detachment are
core examples and test work. Require three distinct student-authored tests,
not additional APIs.

The public core suite carries the canonical `(3 + 5) * 2` fixture while also
checking that the underlying binary-tree API handles valid one-child,
duplicate-value, zero-value, and unsorted-data cases.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- every answer key; and
- earlier inquiry materials.

## Instructor verification

Build the reference core and extension targets and the isolated autopsy
using `../code/README.md`. Check supported warning and sanitizer builds.
The student Makefile and PowerShell script must expose only starter/core,
student tests, and the isolated autopsy; instructor extensions stay private.

Verify all release sources, unique archive entry names, vocabulary in Stage
B only, and no Stage D autopsy answers. The public source paths are
`binary_tree.h`, `binary_tree.c`, and `faulty_cascade.c`.
