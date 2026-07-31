# Stage A - Initial Inquiry: Ordered Record Lookups

Name: ____________________________
Date: ____________________________

Use only this file during the initial inquiry. Preserve your first
responses. Later, add labeled corrections instead of erasing them.

This is a synthetic activity. The records do not describe real systems.

## A. Place unique records - 10 points

An index begins empty and can hold at most 64 records. Each record has one
unique whole-number label.

Use this placement rule:

1. If the current place is END, put the new record there.
2. If the new label is smaller, continue through the left marker.
3. If the new label is larger, continue through the right marker.
4. If the labels are equal, reject the new record.

END means that no record is stored at that place.

### A1. Place three records - 6 points

Place 30, then 20, then 10. Show every comparison and left/right choice.

Response: ___________________________________________________________

### A2. Preserve the rule - 4 points

State the rule that all records reached through a left marker and all
records reached through a right marker must satisfy.

Response: ___________________________________________________________

## B. Compare three arrival orders - 12 points

Each lookup begins at the first record. One comparison checks the requested
label against one stored label. A missing-label lookup stops only when it
reaches END.

Use these three arrival orders:

1. Ascending labels: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
   15.
2. Descending labels: 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,
   1.
3. Mixed labels: 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15.

### B1. Predict the shapes - 4 points

For each order, predict whether records spread across both directions or
form one long route. Explain from the placement rule.

Response: ___________________________________________________________

### B2. Count a deepest lookup - 4 points

For each order, count the comparisons needed to find a record at the end
of a longest route.

Response: ___________________________________________________________

### B3. Count a missing lookup - 4 points

For each order, choose one missing label whose lookup follows a longest
route. Count its comparisons.

Response: ___________________________________________________________

## C. Repair four three-record cases - 12 points

Consider these arrival orders:

1. Case 1 labels: 30, 20, 10.
2. Case 2 labels: 10, 20, 30.
3. Case 3 labels: 30, 10, 20.
4. Case 4 labels: 10, 30, 20.

### C1. Draw the four placements - 4 points

Show the left and right markers after each arrival order.

Response: ___________________________________________________________

### C2. Shorten the routes - 4 points

For each case, reconnect markers to make the longest lookup route as short
as possible while preserving the placement rule. Which record becomes
first, and where are the other two reached? Do not discard or duplicate a
record.

Response: ___________________________________________________________

### C3. State what stayed true - 4 points

After each reconnection, list the labels in smaller-to-larger order. Explain
why a lookup still follows the placement rule.

Response: ___________________________________________________________

## D. Threat and scope - 6 points

Suppose an untrusted sender controls the arrival order but every label is
valid and unique.

### D1. Describe the slowdown - 3 points

How could the sender make later lookups perform more comparisons?

Response: ___________________________________________________________

### D2. Limit the claim - 3 points

Does a slow but valid lookup by itself prove that storage was read outside
its permitted region? Does it prove that all machine resources are gone?
Explain both distinctions.

Response: ___________________________________________________________

## Initial synthesis

> How can a few local marker changes keep lookup routes short without
> changing smaller-to-larger order?

Initial response:

____________________________________________________________________

One question your current plan does not settle:

____________________________________________________________________
