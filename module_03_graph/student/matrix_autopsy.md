# Matrix Symmetry Autopsy — One Edge, One Missing Mirror

## What an autopsy means here

An **autopsy** is a careful investigation after something goes wrong. The
goal is to find the first broken rule, not merely the final incorrect result.

A **program** is a group of instructions a computer can run. **C** is the
programming language used in this course. A **graph** is a model of objects
and relationships; one object is a **vertex** and one relationship is an
**edge**.

An **undirected edge** has no direction. In an **adjacency matrix**, a table
whose cells record edges, that relationship needs two matching cells. The
cells are **mirrors** because their row and column indexes trade places.
**Symmetry** means that every pair of mirror cells agrees. A **Boolean
value** is either `true` or `false`.

The supplied program intends to build an undirected graph but writes one
edge into only one of its two mirrored cells. An **array** is a numbered row
of matching values, and an **index** is one numbered position. Every array
access remains inside the **fixed** matrix, meaning the matrix does not grow
while the program runs.

## Before running

Predict:

1. Which two matrix cells should represent the relationship between vertices
   0 and 1?
2. Which one does the faulty program leave `false`?
3. Which two printed observations will contradict each other?

Preserve your prediction.

## Incident report

An **incident report** records what went wrong and how it was corrected. You
may answer any table in this file as a numbered list using the same column
headings.

### 1. Intended relationships

Record every intended undirected edge:

| First vertex | Second vertex | Two required cells |
|---:|---:|---|
| | | |
| | | |

### 2. First invalid completed state

An **assignment** is a C instruction that stores a value. Identify the
assignment after which the matrix no longer represents an undirected graph.

____________________________________________________________________

### 3. Broken rule

An **invariant** is a rule that must hold in every valid completed state.
State the exact symmetry invariant that is broken.

____________________________________________________________________

### 4. Observable contradiction

A **degree** is the number of edges touching a vertex in an undirected graph.
Explain why the faulty matrix can report that vertex 0 sees vertex 1 while
vertex 1 does not see vertex 0.

____________________________________________________________________

Explain why their degree counts can also disagree with the intended model.

____________________________________________________________________

### 5. Repair

Write the missing assignment:

____________________________________________________________________

An **operation** is one task provided by code.
Why must a correct undirected insertion update both cells as one operation?

____________________________________________________________________

### 6. Regression tests

A **test** runs one case and checks its result. A **regression test** is a
test kept to prevent a repaired defect from returning.

Write two tests:

1. _________________________________________________________________
2. _________________________________________________________________

## After observation

Label each correction with one of:

`row/column` · `direction` · `symmetry` · `degree` · `invariant`

The evidence that changed my model was:

____________________________________________________________________
