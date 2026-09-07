# Stage A — Initial Inquiry: Which Function Resumes First?

Name: ____________________________  
Date: ____________________________

Use only this file during the initial inquiry. Preserve your first thinking.
Later, add labeled corrections instead of erasing it.

## A. Follow three function calls

Suppose a program runs these events in order:

1. Function 100 starts.
2. Function 100 pauses and starts Function 200.
3. Function 200 pauses and starts Function 300.
4. Function 300 finishes.

Which paused function must resume next? Explain.

____________________________________________________________________

After that function finishes, which function resumes?

____________________________________________________________________

## B. Track unfinished functions

Complete the table. List unfinished function IDs from the earliest call to the
most recent call.

| Event | Unfinished function IDs before | What changes? | Unfinished function IDs after |
|---|---|---|---|
| Start Function 100 | | | |
| Function 100 starts Function 200 | | | |
| Function 200 starts Function 300 | | | |
| Function 300 finishes | | | |
| Function 200 finishes | | | |
| Function 100 finishes | | | |

Which end of your record changes at every start and finish?

____________________________________________________________________

## C. Test the access rule

Consider each request independently.

1. The record contains `100, 200, 300`, from earliest to most recent. Which
   value may be inspected without removing it?

   _________________________________________________________________

2. The same record contains `100, 200, 300`. Which value may be removed next?

   _________________________________________________________________

3. The record is empty. What should happen if the program asks to inspect or
   remove a value?

   _________________________________________________________________

Why would removing 100 before 300 change the required return order?

____________________________________________________________________

## D. Add a fixed boundary

Suppose the record has ten prepared positions and already contains ten IDs.
A request arrives to add ID 400.

Should the request be accepted? _____________________________________

What should happen to the ten existing IDs and the current count?

____________________________________________________________________

Suppose a failed inspection was asked to write its answer into a variable
that already contains 999. What should remain in that variable?

____________________________________________________________________

## E. Macro-Question

**State** is the information a program currently remembers.

> If the most recently started unfinished task must finish first, what access
> rule should the program enforce?

Your initial explanation:

____________________________________________________________________

____________________________________________________________________

## F. Transfer brainstorm

Do not write C instructions yet.

The expression `1+2*3` cannot be evaluated strictly from left to right because
multiplication has higher priority than addition.

What information must wait while `2*3` is calculated?

____________________________________________________________________

How might “use the most recent waiting item first” help?

____________________________________________________________________

One question your current method does not settle:

____________________________________________________________________
