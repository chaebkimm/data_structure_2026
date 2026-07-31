# Stage A — Initial Inquiry: Routes That Reconnect

Name: ____________________________  
Date: ____________________________

Use only this file during the initial inquiry. Preserve your first answers.
Later, add labeled corrections instead of erasing your first thinking.

This activity retrieves a few words from Module 3. A **graph** describes
items and their direct relationships. Each item is a **vertex**. Each direct
relationship is an **edge**. A **directed edge** works in one stated
direction. The notation `0 → 1` means that the relationship goes from
vertex 0 to vertex 1.

The example is synthetic, meaning invented for safe practice. A **service**
is a program that performs a task for another program. A **policy** is a set
of rules. A **model** is a simplified description. These relationships form
only an invented policy model.

## A. Read the service relationships

The vertices are:

```text
0 Gateway
1 Web
2 Admin
3 Database
4 Monitor
5 Archive
```

The directed edges are:

```text
0 → 1
0 → 2
1 → 3
2 → 3
3 → 4
4 → 1
```

In words:

- Gateway leads to Web and Admin.
- Web leads to Database.
- Admin leads to Database.
- Database leads to Monitor.
- Monitor leads to Web.
- Archive has no edge entering or leaving it.

Which vertices can be chosen immediately after Gateway?

____________________________________________________________________

Which vertex can be entered from both Web and Admin?

____________________________________________________________________

Which vertex is separate from every edge?

____________________________________________________________________

## B. Follow one route

A **route** is a sequence that follows the stated edge directions.

Begin at Web. Follow its edge to Database, then to Monitor, and continue
using the stated relationships.

Write the first five vertex names in that route:

____________________________________________________________________

What begins to repeat?

____________________________________________________________________

What problem could occur if a program continued in the same way forever?

____________________________________________________________________

## C. Invent the missing memory

Suppose a program must start at Gateway and inspect every vertex it can
reach without inspecting one vertex repeatedly.

What one yes-or-no fact could the program remember about each vertex?

____________________________________________________________________

When should that fact change?

____________________________________________________________________

What should the program do when an edge leads to a vertex whose fact has
already changed?

____________________________________________________________________

## D. Remember choices still waiting

Gateway offers Web and Admin. If Web is chosen first, Admin must not be
forgotten.

What information must wait while the program continues through Web?

____________________________________________________________________

After Web leads to Database, what earlier choice is still waiting?

____________________________________________________________________

How could the program decide which waiting choice to continue next?

____________________________________________________________________

## E. Decide what one start can cover

Can the stated edge directions lead from Gateway to Archive?

____________________________________________________________________

If the task changes from “inspect everything reachable from Gateway” to
“inspect every vertex,” what additional action is needed?

____________________________________________________________________

## F. Transfer from the tree

Module 5 followed one tree branch before returning to an unfinished branch.

What part of that idea still seems useful here?

____________________________________________________________________

What graph relationship creates a problem that a valid tree did not have?

____________________________________________________________________

## G. Macro-Question

> Tree branches do not reconnect. What must change when a route can lead
> back to a vertex already reached?

Your initial explanation:

____________________________________________________________________

____________________________________________________________________

One question your current idea does not settle:

____________________________________________________________________
