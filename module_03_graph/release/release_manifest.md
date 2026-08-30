# Module 3 Staged Release Manifest

Run `prepare_student_release.ps1` from this directory to create five ZIP
archives in `../dist`. The script checks every required source and refuses
to overwrite existing archives. Do not generate archives before verification.

## Stage A — Initial Relationship Inquiry

Release before Meeting A:

- standard inquiry; and
- linear accessible inquiry.

This stage contains no graph vocabulary reference, formal matrix model, code,
solution, or instructor material.

## Stage B — Directed Matrix and Cognitive Pause

Release after students preserve the Stage A response:

- directed adjacency-matrix reveal;
- exactly three Cognitive Pause targets; and
- Stage B vocabulary reference.

The pause covers matrix orientation, one removal/out-degree trace, and
self-loop/active-bound decisions. Withhold calibration and Stage C until the
response is preserved.

## Stage C — Investigation

Release after pause calibration:

- standard investigation; and
- linear accessible investigation.

Both formats use the canonical Web/App/Database graph and the same translation,
operation, invariant, comparison, and model-boundary targets. They do not
supply worked answers.

## Stage D — Textbook and Models

Release after the complete Stage C attempt is saved:

- current graph textbook; and
- correct directed-matrix diagrams with text equivalents.

Do not include the exact Stage E ghost-connection prediction or observed
output. A generic explanation of full initialization is part of the ordinary
model, not the autopsy answer.

## Stage E — Lab and Evidence

Release for Meeting B:

- lab, 100-point rubric, evidence template, and Matrix Autopsy;
- `include/graph_matrix.h` and `starter/graph_matrix.c`;
- public core tests and the three-test student template;
- student-only PowerShell and GNU Make build files; and
- isolated `autopsy/faulty_ghost_connection.c`.

The only library tasks are `graph_init`, `graph_add_edge`,
`graph_remove_edge`, and `graph_out_degree`. Guarded direct lookup is
caller code. Conceptual comparisons do not add APIs.

Stage E excludes:

- `instructor/`;
- `code/solution/`;
- `code/tests/test_extension.c`;
- answer keys; and
- earlier inquiry materials.

## Instructor verification

Build reference core and extension targets and the isolated autopsy using
`../code/README.md`. Run supported warning and sanitizer checks.

Audit five stages, existing unique sources, vocabulary in Stage B, and the
absence of instructor/solution/extension files. Confirm release builds use
`faulty_ghost_connection.c` and executable `ghost_connection_autopsy`.
