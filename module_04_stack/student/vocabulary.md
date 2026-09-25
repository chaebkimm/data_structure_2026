# Module 4 Vocabulary — Stage B Reference

Open this page after completing and preserving the Cognitive Pause.

| Term | Plain-language definition |
|---|---|
| state | Information a program currently remembers |
| data structure | A planned way to organize information in a program |
| abstract data type (ADT) | A collection described by its operations and rules rather than a required storage method |
| Stack ADT | An ADT that permits adding, inspecting, and removing at one end |
| top | The accessible end of a Stack; in the character Stack, `top` is its current array index |
| last in, first out (LIFO) | The most recently added item is the first item that may be removed |
| operation | One task provided by a data structure |
| `push` | Add one item at the top; this character implementation decreases `top` before writing |
| `peek` | Report the top without removing it |
| `pop` | Remove and report the top; this character implementation increases `top` after reading |
| empty Stack | No active items; the character Stack has `top == 10` |
| underflow | A request to peek or pop an empty Stack; the character functions return `'\0'` |
| full Stack | All ten character positions are active and `top == 0`; another push changes nothing |
| representation | A chosen way to store or show information |
| fixed-capacity array | An array with a prepared number of positions that does not change |
| character | One C `char` value, such as `'A'`, `'3'`, or `'*'` |
| integer | A whole-number value; the local `values` array stores C `int` results |
| call frame | Bookkeeping for an active function call; character labels are not real call frames |
| array | A numbered row of values of one type |
| index | A numbered array position; C begins at zero |
| logical item | A stored value that belongs to the current Stack's active region |
| inactive slot | A physical cell inside an array but outside the active region |
| active suffix | The character Stack's indexes `top` through 9 |
| active prefix | The numeric Stack's indexes 0 through `pos - 1` |
| `capacity` | The descriptive global initialized to 10; current character operations hardcode their boundaries |
| global variable | An object declared outside functions and shared by the functions that use it |
| local variable | An object declared within a function or block, such as `values` and `pos` |
| `size` | Number of postfix characters produced, excluding the terminator; not character Stack item count |
| `pos` | Number of active integers in `values` during postfix evaluation |
| null character | `'\0'`, used as a string terminator and as this Stack's empty peek/pop result |
| invariant | A rule true in every valid completed state, such as `0 <= top <= 10` |
| contract | Rules stating what a function assumes, changes, returns, and preserves |
| preservation | Keeping required prior state unchanged, as with full push or empty peek/pop |
| trace | A step-by-step record of changing state |
| infix | Expression order with operators between operands, such as `1+2` |
| postfix | Expression order with each operator after its operands, such as `12+` |
| digit | One character from `'0'` through `'9'`; subtracting `'0'` yields its numeric value |
| operand | A value used by an operator |
| operator | A symbol such as `+`, `-`, `*`, `/`, or `%` requesting a calculation |
| operator precedence | The rule determining which operators are applied before others |
| left associativity | Applying operators of equal precedence from left to right |
| integer overflow | A calculation whose mathematical result does not fit C `int`; this lab does not check for it |
| precondition | A requirement the caller must satisfy, such as valid expression syntax or a nonzero divisor |
| regression test | A repeatable test kept so that a repaired defect does not return |
