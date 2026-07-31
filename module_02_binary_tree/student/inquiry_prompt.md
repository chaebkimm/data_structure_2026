# Stage A — Initial Inquiry: Remembering a Hierarchy

Name: ____________________________  
Date: ____________________________

Use only this file during the initial inquiry. Preserve your first answers.
Later, add labeled corrections instead of erasing your original thinking.

A **hierarchy** is an arrangement in levels: one item can lead to items below
it. An **immediate relationship** connects two items with no item between them.

## A. Reconstruct the hierarchy

A training lab stores reports in this arrangement:

| Item | Immediate item above it |
|---|---|
| Security Lab | none |
| Logs | Security Lab |
| Reports | Security Lab |
| Login Events | Logs |
| Firewall Events | Logs |
| Daily Summary | Reports |
| Incident Summary | Reports |

Draw the arrangement, or describe it line by line.

____________________________________________________________________

____________________________________________________________________

Which item is the single starting item? _____________________________

Which items have nothing below them? _______________________________

Write one route from `Security Lab` to an item at the bottom:

____________________________________________________________________

## B. Find rules that preserve the hierarchy

Consider each change separately.

1. `Firewall Events` is placed directly below both `Logs` and `Reports`.
   What becomes unclear?

   _________________________________________________________________

2. A relationship is added from `Login Events` back to `Security Lab`.
   Following relationships can now return to an earlier item. What problem
   might this cause?

   _________________________________________________________________

3. `Daily Summary` is removed from below `Reports` but is still claimed to be
   part of the hierarchy. How could anyone reach it from the starting item?

   _________________________________________________________________

Write two rules that the original arrangement follows:

1. _________________________________________________________________
2. _________________________________________________________________

## C. Macro-Question

An **object** is one stored thing that groups related information. A **graph**
is a general network of items and relationships; it may contain shared items
or routes that loop back. **Computer memory** is the working storage in which
a running program keeps values.

> How can separate objects in computer memory represent a hierarchy, and what
> rules prevent their links from becoming an arbitrary graph?

Your initial explanation:

____________________________________________________________________

____________________________________________________________________

## D. Storage brainstorm

Do not write C code yet. **C** is the programming language used in this
course, and **code** means instructions written for a computer.

What fact must the program store for each item so it can find the items
directly below it?

____________________________________________________________________

How could the program show that an item has no item below it on one side?

____________________________________________________________________

Must two related items be next to each other in computer memory? Explain your
current thinking.

____________________________________________________________________

One question your model does not yet answer:

____________________________________________________________________
