# Stage A — Initial Inquiry: Linear Accessible Format

## How to use this version

This version has the same questions and learning targets as the standard
inquiry. It requires no table or drawing. It works with a screen reader,
keyboard navigation, speech input, or a text-only response.

Use only this file during the initial inquiry. Preserve your first thinking.
Later, add a labeled correction instead of replacing it.

## Student information

Name:

Date:

## A. Follow three function calls

Suppose a program runs these events in order:

1. Function 100 starts.
2. Function 100 pauses and starts Function 200.
3. Function 200 pauses and starts Function 300.
4. Function 300 finishes.

Which paused function must resume next? Explain.

Response:

After that function finishes, which function resumes?

Response:

## B. Track unfinished functions

Starting with no unfinished function, state the unfinished function IDs after
each event. List them from the earliest call to the most recent call.

1. Start Function 100.
2. Function 100 starts Function 200.
3. Function 200 starts Function 300.
4. Function 300 finishes.
5. Function 200 finishes.
6. Function 100 finishes.

Response:

Which end of your record changes at every start and finish?

Response:

## C. Test the access rule

Consider each request independently.

### C1. Inspect

The record contains `100, 200, 300`, from earliest to most recent. Which value
may be inspected without removing it?

Response:

### C2. Remove

The same record contains `100, 200, 300`. Which value may be removed next?

Response:

### C3. Empty record

The record is empty. What should happen if the program asks to inspect or
remove a value?

Response:

### C4. Wrong end

Why would removing 100 before 300 change the required return order?

Response:

## D. Add a fixed boundary

Suppose the record has ten prepared positions and already contains ten IDs.
A request arrives to add ID 400.

### D1. Decision

Should the request be accepted?

Response:

### D2. Preserved state

What should happen to the ten existing IDs and the current count?

Response:

### D3. Preserved output

Suppose a failed inspection was asked to write its answer into a variable
that already contains 999. What should remain in that variable?

Response:

## E. Macro-Question

State is the information a program currently remembers.

If the most recently started unfinished task must finish first, what access
rule should the program enforce?

Initial explanation:

## F. Transfer brainstorm

Do not write C instructions yet.

The expression `1+2*3` cannot be evaluated strictly from left to right because
multiplication has higher priority than addition.

### F1. Waiting information

What information must wait while `2*3` is calculated?

Response:

### F2. Most recent first

How might “use the most recent waiting item first” help?

Response:

### F3. Open question

What question does your current method not settle?

Response:
