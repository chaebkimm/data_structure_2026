# Stage A — Initial Inquiry: Closing What Was Opened

Name: ____________________________  
Date: ____________________________

Use only this file during the initial inquiry. Preserve your first thinking.
Later, add labeled corrections instead of erasing it.

An **expression** is a sequence of symbols that communicates a value or rule.
A **delimiter** is a mark that shows where a group begins or ends. The
opening delimiters in this activity are `(`, `[`, and `{`. Their closing
partners are `)`, `]`, and `}`.

## A. Inspect one candidate expression

Consider:

```text
A(B[C]{D})
```

Read from left to right.

Circle or list the opening delimiters:

____________________________________________________________________

Circle or list the closing delimiters:

____________________________________________________________________

Draw a line from each closing delimiter to the opening delimiter you think
it completes, or describe each pair in words.

____________________________________________________________________

What makes you confident that the grouping is complete?

____________________________________________________________________

## B. Track unfinished groups

An **unresolved opening** is an opening delimiter whose closing partner has
not yet appeared.

Complete the table using your own tracking idea. Ordinary letters do not
begin or end a group.

| Symbol just read | Unresolved openings before it | What your method does | Unresolved openings after it |
|---|---|---|---|
| `A` | | | |
| `(` | | | |
| `B` | | | |
| `[` | | | |
| `C` | | | |
| `]` | | | |
| `{` | | | |
| `D` | | | |
| `}` | | | |
| `)` | | | |

When a closing delimiter arrives, which unresolved opening should your method
check? Why?

____________________________________________________________________

____________________________________________________________________

## C. Challenge your rule

**Malformed input** is input that breaks the stated grouping rules.
Consider each expression independently. Do not assume that every one is
complete.

| Expression | First place your method can make a decision | Complete or malformed? | Reason |
|---|---|---|---|
| `A(B[C]{D})` | | | |
| `A)B` | | | |
| `A(B]` | | | |
| `A(B` | | | |

Could two different failures be discovered at different times—one while
reading and one only after the final symbol? Explain.

____________________________________________________________________

## D. Add a resource boundary

A **resource boundary** is a stated limit on how much time or storage a task
may use. Suppose this activity permits at most two simultaneously unresolved
openings.

Consider:

```text
A([B{C}])
```

At which symbol, if any, should the method reject the input?

____________________________________________________________________

What should happen to information already being tracked when the boundary is
reached?

____________________________________________________________________

Why is a stated boundary useful even when more computer memory is available?

____________________________________________________________________

## E. Macro-Question

A **program** is a group of instructions a computer can run. **State** is the
information a program currently remembers.

> If the most recently opened task must be completed first, what access rule
> should the program enforce?

Your initial explanation:

____________________________________________________________________

____________________________________________________________________

## F. Tracking brainstorm

Do not write C instructions yet. **C** is the programming language used in
this course.

What information must be remembered when an opening delimiter arrives?

____________________________________________________________________

What must be true before a closing delimiter can be accepted?

____________________________________________________________________

What must be true after the final input symbol?

____________________________________________________________________

One question your current method does not settle:

____________________________________________________________________
