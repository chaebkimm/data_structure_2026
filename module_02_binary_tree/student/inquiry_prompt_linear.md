# Stage A — Initial Inquiry: Linear Accessible Format

## How to use this version

This version has the same learning targets as the standard inquiry. It avoids
tables, drawing requirements, and long blank lines. It is suitable for a
**screen reader**—software that reads on-screen text aloud—keyboard
navigation, speech input, or a response containing only text.

Preserve your first answers. Later, add a labeled correction instead of
replacing an initial answer. Use only this file during the initial inquiry.

A **hierarchy** is an arrangement in levels: one item can lead to items below
it. An **immediate relationship** connects two items with no item between them.

## Student information

Name:

Date:

## A. Reconstruct the hierarchy

The arrangement contains these facts:

1. Security Lab has no item above it.
2. Logs is immediately below Security Lab.
3. Reports is immediately below Security Lab.
4. Login Events is immediately below Logs.
5. Firewall Events is immediately below Logs.
6. Daily Summary is immediately below Reports.
7. Incident Summary is immediately below Reports.

### A1. Describe the arrangement

Describe the hierarchy line by line. You may use phrases such as “Security
Lab leads to Logs and Reports.”

Response:

### A2. Starting item

Which item is the single starting item?

Response:

### A3. Bottom items

Which items have nothing below them?

Response:

### A4. One route

State one route from Security Lab to an item at the bottom.

Response:

## B. Find rules that preserve the hierarchy

Consider each change separately.

### B1. One item in two places

Firewall Events is placed directly below both Logs and Reports. What becomes
unclear?

Response:

### B2. A route that loops back

A relationship is added from Login Events back to Security Lab. Following
relationships can now return to an earlier item. What problem might this
cause?

Response:

### B3. An unreachable item

Daily Summary is removed from below Reports but is still claimed to be part
of the hierarchy. How could anyone reach it from the starting item?

Response:

### B4. Two rules

State two rules followed by the original arrangement.

First rule:

Second rule:

## C. Macro-Question

An **object** is one stored thing that groups related information. A **graph**
is a general network of items and relationships; it may contain shared items
or routes that loop back. **Computer memory** is the working storage in which
a running program keeps values.

How can separate objects in computer memory represent a hierarchy, and what
rules prevent their links from becoming an arbitrary graph?

Initial explanation:

## D. Storage brainstorm

Do not write C code yet. **C** is the programming language used in this
course, and **code** means instructions written for a computer.

### D1. Remembering lower items

What fact must the program store for each item so it can find the items
directly below it?

Response:

### D2. Showing that no item exists

How could the program show that an item has no item below it on one side?

Response:

### D3. Memory position

Must two related items be next to each other in computer memory? Explain your
current thinking.

Response:

### D4. Open question

What question does your model not yet answer?

Response:
