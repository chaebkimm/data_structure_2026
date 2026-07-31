# Stage A — Initial Inquiry: Linear Accessible Format

Name: ____________________________  
Date: ____________________________

Use only this file during the initial inquiry. Preserve your first answers.
Later, add labeled corrections instead of erasing your first thinking.

This version states every storage position in words. It has the same facts
and questions as the standard inquiry.

A **security event** is a stored report about something a system noticed.
An **event collector** is a program that temporarily stores such reports
until they can be handled. The examples are synthetic, meaning invented for
safe practice.

## A. Preserve the arrival promise

Three letter-labeled events arrive in this order: K, then B, then T.

The letters identify events; alphabetical position does not state
importance.

Which event should be handled first if arrival order must be preserved?

____________________________________________________________________

After that event is handled, which event should be handled next?

____________________________________________________________________

Why would choosing the alphabetically first event break the stated promise?

____________________________________________________________________

## B. Use fixed numbered slots

The collector has four physical slots:

1. physical slot 0 stores event K;
2. physical slot 1 stores event B;
3. physical slot 2 stores event T; and
4. physical slot 3 is unused.

A **physical slot** is one actual position in the storage. First handle K,
then handle B. Do not shift event T to another slot.

Which event remains waiting?

____________________________________________________________________

Which physical slot still contains that waiting event?

____________________________________________________________________

Which slots may now be reused?

____________________________________________________________________

## C. Continue after the physical end

Events R, C, and M arrive next. The collector still has only four slots. It
must not move event T.

Where could the arriving events be placed?

____________________________________________________________________

How could the collector continue after it uses physical slot 3?

____________________________________________________________________

What facts must it remember so that physical position does not change the
arrival promise?

____________________________________________________________________

## D. Decide what happens when every slot is occupied

A **resource boundary** is a stated limit on storage or work. Suppose every
slot is occupied when event Q arrives.

Consider three choices:

1. refuse the new event;
2. discard the event that has waited longest; or
3. ask the source to slow or stop sending events.

For each choice, state which event information might be lost or delayed.

____________________________________________________________________

Why would silently choosing one of these behaviors be unsafe?

____________________________________________________________________

A **retention policy** is a rule stating which information is kept. What
retention policy would you choose for this exercise, and why?

____________________________________________________________________

## E. Compare an earlier access rule

Module 4 used a collection in which the most recently added item left first.

Would that rule preserve event arrival order here? Explain.

____________________________________________________________________

When would “newest leaves first” and “earliest arrival leaves first” produce
different results?

____________________________________________________________________

## F. Macro-Question

> How can a security-event collector process events in arrival order without
> shifting all remaining events after every removal?

Your initial explanation:

____________________________________________________________________

____________________________________________________________________

One question your current idea does not settle:

____________________________________________________________________
