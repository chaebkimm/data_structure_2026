# Stage A — Initial Inquiry: Change Record Order

Name: ____________________________  Date: ____________________________

Use only this file for the initial inquiry. Preserve first responses;
later add labeled corrections. All records are invented. You may answer
with words, tables, drawings, or an equivalent spoken description.

## A. Follow and change records without moving them

A first-place marker stores 0. The ten places are numbered 0 through 9.
The current records are:

| Place | Stored number | Continue at |
|---:|---:|---|
| 0 | 17 | 1 |
| 1 | 23 | 2 |
| 2 | 31 | END |

`END` means there is no later record. No record leads back to an earlier record.

1. Starting at the first-place marker, in what order are numbers visited? What happens if place 2 continues at 0 instead?
2. Remove the record holding 23 without moving the other records. Which surviving record must change? Which old continuation must remain available until that change is complete?
3. Restore place 1 holding 23 between places 0 and 2. Which continuation must be copied before changing place 0?
4. Where must the first-place marker be kept? How does it change when the first record leaves?

Response: ___________________________________________________________

____________________________________________________________________

## B. Share and reuse the available places

Available places form another chain beginning at 3: 3,4,5,6,7,8,9,END.
A place cannot belong to active records and available places at the same time.

1. Make removed place 1 available by putting it before place 3. How does the meaning of its continuation change? Why must removal happen first?
2. If every place is in use, what should another request return? Which records should change?
3. What happens if an unused detached place is never returned, or if one place is returned twice?
4. Another list takes returned place 1 and stores 8. What would a saved old reference to place 1 read? How could an old writer change the other list?
5. Two lists keep separate first-place markers. How can they use the same collection of available places? Why must they never own the same place at once?
6. How much following is needed to find the i-th record? What additional information does each record have to store?

Response: ___________________________________________________________

Preserve one uncertainty to revisit after the representation reveal:

____________________________________________________________________

## C. Take the latest record first

Records carrying 17,23,31 arrive one at a time. Place every arrival before the old first record, and remove only the first record.

1. What is the resulting chain, and in what order do records leave?
2. Which old first position must a new record remember before becoming first?
3. Before returning the first record's place, which data and continuation must be saved, and how can its continuation be marked END after the first-place marker advances?
4. What should happen if no record exists, or if no available place remains?

Response: ___________________________________________________________

## D. Keep requests in arrival order

In a separate run, requests carrying 17,23,31 arrive one at a time.

1. Where should a new request attach so the earliest one leaves first?
2. Which two places should be remembered so adding and removing need no search?
3. What do both markers become for the first arrival and after the last departure?
4. Why should a new last record have no continuation?

Response: ___________________________________________________________
