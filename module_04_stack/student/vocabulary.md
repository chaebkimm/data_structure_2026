# Module 4 Vocabulary — Stage B Reference

Open this page after completing and preserving the Cognitive Pause.

| Term | Plain-language definition |
|---|---|
| state | The information a program currently remembers |
| data structure | A planned way to organize information in a program |
| abstract data type (ADT) | A collection described by allowed operations and rules rather than one required storage method |
| Stack ADT | An ADT that permits adding, inspecting, and removing at one end |
| top | The one accessible end of a Stack |
| last in, first out (LIFO) | The most recently added item is the first item that may be removed |
| operation | One task provided by a data structure |
| `push` | Add one item at the top |
| `peek` | Report the top item without removing it |
| `pop` | Remove and report the top item |
| empty Stack | A Stack containing no logical item and therefore having no top |
| underflow | A request to `peek` or `pop` an empty Stack |
| full-Stack rejection | Refusal to push when size already equals capacity, with the Stack unchanged |
| representation | A chosen way to store or show information |
| fixed-capacity array | An array whose prepared number of positions does not change |
| integer | A whole-number value stored with a C integer type |
| call frame | Information kept for one active function call; the course's integer IDs are simplified labels rather than real call frames |
| array | A numbered row of values of one type |
| index | A numbered array position; C begins at zero |
| logical item | A value that currently belongs to the Stack according to `size` |
| inactive slot | A physical array position that is within capacity but outside the current logical Stack |
| `size` | The number of logical items currently in the Stack |
| `capacity` | The number of prepared array positions the operations must honor |
| caller | The program part that creates storage and requests a function |
| caller-owned storage | An array created and controlled by the caller and borrowed by Stack functions |
| output parameter | Caller-provided storage through which a function reports an additional result |
| invariant | A rule true in every valid completed state |
| contract | Rules stating what a function accepts, changes, returns, and preserves |
| rejection | Refusal to perform an operation because its requirements are not satisfied |
| preservation | Keeping required prior state or output unchanged after rejection |
| trace | A step-by-step record of changing state |
| function ID | An integer label used in the canonical example to identify one function |
| expression | A sequence of operands and operators that describes a calculation |
| digit | One character from `'0'` through `'9'` |
| operand | A value used by an operator |
| operator | A symbol such as `+` or `*` that requests a calculation |
| operator precedence | The rule that determines which different operator is applied first |
| left associativity | The rule that equal-precedence operators are applied from left to right |
| integer overflow | A calculation whose mathematical result is outside the C `int` range |
| regression test | A test kept so that a repaired defect does not return |
