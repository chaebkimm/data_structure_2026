# Module 2 Staged Release Manifest

Run `prepare_student_release.ps1` to create five ZIP archives in `../dist`.
The script validates all sources before writing and refuses to overwrite an
existing archive. Verify reference code and release contents first.

## Stage A — Initial Hierarchy Inquiry

Release before Meeting A: the standard and linear inquiry prompts for
`1+2*3`. Students propose how to record its order of work before formal C
representation or vocabulary is revealed. Preserve both first models and
later annotations. No worked model, code, or instructor material is included.

## Stage B — Representation and Cognitive Pause

Release after the initial model: the array-index representation reveal,
vocabulary, and three-target Cognitive Pause. The pause covers indices
(`-1` versus `0`), term construction with `pos` and a changing root, and
recursive evaluation. Keep expert calibration until every student has
preserved a first response, including approved accessible equivalents.

## Stage C — Construction and Evaluation Investigation

Release after the pause and calibration: standard and linear worksheets
using the transfer expression `2*3+4*5`. Students track node reservation,
child indices, parser position, precedence, left grouping, and recursive
results. No answer key is included.

## Stage D — Textbooks and Models

Release after the Stage C attempt is preserved:

- `textbook.md`, the English chapter;
- `textbook_korean.md`, its Korean edition; and
- `diagrams/tree_models.md`, correct models with text equivalents.

Both editions use the same C representation and executable examples.
This stage contains no worked Stage E fault prediction or repair answer.

## Stage E — Lab and Evidence

Release for Meeting B:

- lab, 100-point rubric, evidence record, and autopsy worksheet;
- `include/binary_tree.h` and `starter/binary_tree.c`;
- core tests and the three-test student template;
- student-only PowerShell and GNU Make build files; and
- standalone `autopsy/faulty_precedence.c` with its README.

The four required functions are `new_node`, `term`, `terms`, and
`eval_tree`. They use `nodes[20]`, character data, integer child indices,
`-1` empty links, `size`, `eq[20]`, and `pos`. The parser assumes valid
single-digit `+`/`*` expressions of at most 19 characters without spaces or
parentheses; all intermediate and final results fit in `int`. Boundary
checks use valid inputs, including zero and a maximum-length expression.
Input rejection, search, and clearing are not required tasks.

Students author three distinct tests for creation, construction, and
evaluation. The autopsy is independent of the starter and solution. It
shows a logical precedence fault using finite valid trees and ordinary
arithmetic, so students predict the result rather than a memory crash.

Exclude `instructor/`, `code/solution/`, `code/lecture/`,
`code/tests/test_extension.c`, all answer keys, and earlier inquiry materials
from Stage E. Extension tests add cases for the same four functions, not
additional implementation requirements.

## Instructor verification

Use `../code/README.md` to run reference core/extension checks, the lecture,
and autopsy with warnings and supported sanitizers. Compile both textbook
programs and compare their output. Check that the incomplete starter and
student placeholders fail cleanly.

Verify every release source and unique destination name. Stage D must
include both language editions. Student build scripts must work using only
Stage E entries and expose only starter core/student tests and autopsy.
Check that solutions, instructor content, and extensions are absent.
