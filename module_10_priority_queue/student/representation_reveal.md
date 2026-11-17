# Chapter 10 — Store User IDs in Logout Order

Open this after preserving the initial inquiry. The goal is to select who leaves next while keeping the earliest time everyone has arrived.

## 1. Name the two decisions

The candidate meeting time is the greatest current login. The next user to examine has the smallest current logout. A priority queue separates this selection rule from the survey loop.

## 2. Match storage to meaning

| Source | Meaning |
| --- | --- |
| timelogs[id][2 * epoch] | Planned login for that user and interval |
| timelogs[id][2 * epoch + 1] | Planned logout |
| users[id] | Current login, logout, and epoch |
| queue[position] | A user ID, not a time |
| compare(x,y) | Whether ID x's current logout is earlier than ID y's |
| out_id | One removed user with an earliest current logout |

IDs and positions are different. At initialization the sorted IDs are `[2,1,0]`, with logout keys `[3,5,6]`. After removal, `out_id = 2`, `front = 1`, `rear = 2`, and only positions 1 and 2 are live.

## 3. Explain the callback

`int (*compare)(int x, int y)` stores a function address. `init_queue(&earlier_logout)` installs the function that reads the two users' logout fields. Nonzero means the first ID has higher priority. The queue does not receive negative/zero/positive ordering codes.

## 4. Preserve order while advancing

Advance only out_id, which is outside the live range. Raise the candidate if its new login is later. Reinsert that ID under its new logout, then remove the earliest ID. The other queued users did not change, so insertion into their already sorted range restores the complete order.

## 5. State the boundary

A candidate is valid only when candidate < earliest logout. Equality fails because logout is excluded. No later interval means return -1. Each survey resets all current users and queue indices, so a new call starts fresh.

The queue never recycles consumed positions. Ten slots cover the sample's maximum nine insertions, not merely its maximum three live users. Queue full/empty checks and interval validation are caller responsibilities.

## Source-reference note

The read-only slides use two users and shorter names arr/logs/on/off/IDS/EPOCHS/max_login_time. Current documentation and tests use lab.c's queue/timelogs/login/logout/N_USERS/N_EPOCHS/latest_login_time and its three-user sample. The slides say Week 12; the package uses Chapter 10 without moving course weeks.
