# Module 4 Vocabulary — Stage B Reference

Open this page after completing and preserving the Cognitive Pause.

| Term | Plain-language definition |
|---|---|
| state | Information a program currently remembers |
| data structure | A planned way to organize information in a program |
| abstract data type (ADT) | A collection described by its operations and rules rather than a required storage method |
| Stack ADT | An ADT that permits adding, inspecting, and removing at one end |
| top | The accessible end of a Stack; the global variable `top` records its index, or -1 when empty |
| last in, first out (LIFO) | The most recently added item is the first item that may be removed |
| operation | One task provided by a data structure |
| `push` | Add one item at the top; this integer implementation increases `top` before writing at that index |
| `peek` | Report the top without removing it |
| `pop` | Read the integer at `stack[top]`, decrease `top`, and return the value; requires a nonempty Stack |
| empty Stack | No active items; the integer Stack has `top == -1` |
| underflow | A request to peek or pop an empty Stack; unchecked here, so callers must prevent it |
| full Stack | All ten positions are active and `top == 9`; another push would access outside the array |
| representation | A chosen way to store or show information |
| fixed-capacity array | An array with a prepared number of positions that does not change |
| character | One C `char` value, such as `'A'`, `'3'`, or `'*'` |
| integer | A whole-number value; global `stack` stores C `int` values and character codes |
| call frame | Bookkeeping for an active function call; character labels are not real call frames |
| array | A numbered row of values of one type |
| index | A numbered array position; C begins at zero |
| logical item | A stored value that belongs to the current Stack's active region |
| inactive slot | A physical cell inside an array but outside the active region |
| active prefix | Indexes 0 through `top` in the shared Stack |
| `capacity` | The global initialized to 10 and used by the `is_full()` predicate; the actual array has ten cells |
| global variable | An object declared outside functions and shared by the functions that use it |
| local variable | An object declared within a function or block, such as conversion cursor `pos` |
| `pos` | Local conversion cursor; next output index, ending one past the output terminator |
| `top` | Shared global top index; -1 means empty, and the item count is `top + 1`; reset by each expression phase |
| null character | `'\0'`, marking the end of a string; each converter explicitly writes it after draining the operators |
| `switch` | Select a branch by a value; `prec` returns a priority for each operator group |
| `break` | Exit the nearest loop or switch; the converter uses it to stop operator popping |
| invariant | A rule true in every valid completed state, such as `-1 <= top < capacity` |
| contract | Rules stating what a function assumes, changes, returns, and preserves |
| preservation | Keeping required prior state unchanged, as with a predicate or valid peek |
| trace | A step-by-step record of changing state |
| infix | Expression order with operators between operands, such as `1+2` |
| postfix | Expression order with each operator after its operands, such as `12+` |
| digit | One character from `'0'` through `'9'`; subtracting `'0'` yields its numeric value |
| operand | A value used by an operator |
| operator | A symbol such as `+`, `-`, `*`, `/`, or `%` requesting a calculation |
| operator precedence | The rule determining which operators are applied before others |
| parentheses | Grouping symbols; the dedicated converter pushes `(` and emits waiting operators at `)` before discarding `(` |
| left associativity | Applying operators of equal precedence from left to right |
| integer overflow | A calculation whose mathematical result does not fit C `int`; this lab does not check for it |
| precondition | A requirement the caller must satisfy, such as valid expression syntax or a nonzero divisor |
| regression test | A repeatable test kept so that a repaired defect does not return |
