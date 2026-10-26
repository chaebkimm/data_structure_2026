# Stage A — Initial Inquiry: Change Record Order

Name: ____________________________  Date: ____________________________

Use only this file for the initial inquiry. Preserve first responses;
later add labeled corrections. All records are invented. You may answer
with words, tables, drawings, or an equivalent spoken description.

## A. Follow records without moving them

A first-place marker stores 0. The ten places are numbered 0 through 9.
The current records are:

| Place | Stored number | Continue at |
|---:|---:|---|
| 0 | 17 | 1 |
| 1 | 23 | 2 |
| 2 | 31 | END |

`END` means there is no later record. Available places form another chain
beginning at 3: 3,4,5,6,7,8,9,END. A place cannot belong to the active
records and available places at the same time.

1. Starting at the first-place marker, in what order are numbers visited?
2. Remove the record holding 23 without moving the other records. Which
   surviving record must change? What information must remain available
   until that change is complete?
3. Make the removed place available again by putting it before place 3.
   How does that change the meaning of its “continue at” field? Why would
   making that change before removal be risky?
4. A new record holding 8 needs a place. Explain how the newly available
   place could be reused without changing the 17,31 visit order. Who
   keeps track of a new record that is not yet connected to the others?

Response: ___________________________________________________________

____________________________________________________________________

## B. Insert and reuse a place

Start with place 0 continuing at 2, and place 2 ending the records. Place 1 is allocated but not connected.

1. How can place 1 holding 23 go between places 0 and 2?
2. Which old continuation must be copied before changing place 0?
3. If every place is in use, what should another request return? Which existing records should change?
4. Can a place become available twice without being allocated in between? Explain the resulting continuation.

Response: ___________________________________________________________

Preserve one uncertainty to revisit after the representation reveal:

____________________________________________________________________

## C. Keep requests in arrival order

Requests carrying 17, 23, and 31 arrive one at a time. Reuse the records above to keep their arrival order without shifting them. Where should a new request be attached? Which record should leave next? Which two places would you remember so neither action needs a search? What should both markers contain when the last request leaves?

Response: ___________________________________________________________
