# Stage A — Initial Inquiry: Which Alert Goes Next?

Name: ____________________________  
Date: ____________________________

Use only this file during the initial inquiry. Preserve your first answers.
Later, add labeled corrections instead of erasing your first thinking.

A **security alert** is a stored notice that a system may need attention.
The alerts here are **synthetic**, meaning invented for safe study. A letter
is only an alert label. An **urgency number** is a course score: a smaller
number means the alert should be handled sooner.

## A. Separate label from urgency

Five alerts arrive in this order:

| Arrival | Alert label | Urgency number |
|---:|:---:|---:|
| 1 | K | 3 |
| 2 | B | 1 |
| 3 | T | 2 |
| 4 | R | 1 |
| 5 | C | 4 |

### A1. Read arrival

Which alert arrived first? Which arrived last?

____________________________________________________________________

### A2. Read urgency

Which alerts have the smallest urgency number?

____________________________________________________________________

### A3. Ignore the identifier

Why must alphabetical order not decide which alert is handled next?

____________________________________________________________________

## B. Apply a repeatable rule

### B1. Service order

Handle smaller urgency numbers before larger urgency numbers. Write the
complete handling order.

____________________________________________________________________

### B2. Equal urgency

B and R have equal urgency. State a repeatable rule for choosing between
them and explain why it is reasonable.

____________________________________________________________________

### B3. Arrival-only contrast

If arrival alone controlled handling, what would the order be? Identify the
first place where that answer differs from B1.

____________________________________________________________________

## C. New arrivals and waiting

### C1. A more urgent arrival

Suppose K is still waiting when alert M with urgency 1 arrives. Should M be
handled before K? Apply your rule, then explain.

____________________________________________________________________

### C2. A long wait

Could alert C wait forever if urgency-1 alerts continue to arrive? What
fairness concern does this create?

____________________________________________________________________

## D. Changing a waiting score

### D1. Silent change

Suppose a program silently changes T's urgency from 2 to 1 while T waits.
What earlier decision may now need to change?

____________________________________________________________________

### D2. Required evidence

What fact should the program record or control if a waiting alert's urgency
is allowed to change?

____________________________________________________________________

## E. Meet a storage boundary

A **resource boundary** is a stated limit on storage or work. Suppose the
collector can hold four waiting alerts and another alert arrives.

### E1. State the policy

Choose one explicit response: refuse the new alert, remove an existing
alert, or ask the source to slow or retry. Explain what may be delayed or
lost.

____________________________________________________________________

### E2. Preserve failure

If the new alert is refused, which earlier facts must remain unchanged?

____________________________________________________________________

## F. Initial synthesis

### F1. Macro-question

> If urgent alerts should be processed before routine alerts, what replaces
> arrival order, and what does that choice cost?

Your initial explanation:

____________________________________________________________________

____________________________________________________________________

### F2. Open question

What question does your current rule not settle?

____________________________________________________________________
