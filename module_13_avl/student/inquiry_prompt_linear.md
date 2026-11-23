# Stage A — Initial Inquiry: Ordered Record Lookups

Name: ____________________________
Date: ____________________________

Use only this file during the initial inquiry. Preserve the first
response. Add labeled corrections later. All records are synthetic.

## A. Place records — 10 points

A collection begins empty and holds at most ten records. Each record has
one letter label. Use the course alphabet order A before B before C, and
so on. Different records may carry the same label.

Follow these placement steps:

1. Start at the first record.
2. At an END marker, place the new record.
3. For a smaller or equal label, follow the left marker.
4. For a larger label, follow the right marker.

END means that no record is stored at that place.

### A1. Follow each comparison — 6 points

Place C, then B, then A. Show every comparison and left/right choice.
Keep each record's identity separate from the letter written on it.

Response: __________________________________________________________

### A2. State the ordering rule — 4 points

Before any reconnection, what must be true of every label reached through
a left marker and through a right marker?

Response: __________________________________________________________

## B. Compare arrival orders — 12 points

A lookup begins at the first record. Count one comparison each time it
reads a record's label. A missing-label lookup stops at END.

Fields: Order; Labels; Present probe; Missing probe.
- Order: ascending; Labels: A, B, C, D, E, F, G; Present probe: G; Missing probe: H.
- Order: descending; Labels: G, F, E, D, C, B, A; Present probe: A; Missing probe: @.
- Order: mixed; Labels: D, B, F, A, C, E, G; Present probe: G; Missing probe: H.

For this fixture, @ is a synthetic label ordered before A.

### B1. Predict the shapes — 4 points

For each order, predict whether the records spread across both directions
or form one long route. Explain from the placement steps.

Response: __________________________________________________________

### B2. Count present lookups — 4 points

Trace each present probe. Write the visited labels and comparison count.

Response: __________________________________________________________

### B3. Count missing lookups — 4 points

Trace each missing probe. Does arriving at END add a record comparison?

Response: __________________________________________________________

## C. Shorten four three-record arrangements — 12 points

Use four separate empty collections:

Fields: Case; Arrival order.
- Case: 1; Arrival order: C, B, A.
- Case: 2; Arrival order: A, B, C.
- Case: 3; Arrival order: C, A, B.
- Case: 4; Arrival order: A, C, B.

### C1. Draw or list the links — 4 points

Show the markers after all three arrivals in each case.

Response: __________________________________________________________

### C2. Reconnect without losing a record — 4 points

Shorten the longest route while keeping the same labels in the same
smaller-to-larger order. Give the new first record and its two directions.

Response: __________________________________________________________

### C3. Preserve what matters — 4 points

List each arrangement from smallest to largest before and after the
change. State what must stay true if two records carry equal labels.

Response: __________________________________________________________

## D. Slowdown and scope — 6 points

Suppose an untrusted sender controls arrival order but every record is valid.

### D1. Describe the extra work — 3 points

Which arrival order makes later lookups inspect many records? Explain
without assuming any invalid storage access.

Response: __________________________________________________________

### D2. Limit the conclusion — 3 points

Does a slow valid lookup alone prove that storage was accessed outside its
permitted region? Does it prove that all machine resources are gone?

Response: __________________________________________________________

## Initial synthesis

How can a few marker changes shorten routes while keeping ordered lookup?

____________________________________________________________________

One question the current plan does not settle:

____________________________________________________________________
