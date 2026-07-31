# Cognitive Pause — Growth, Failure, and Pointer Stability

Use no notes, slides, neighbors, or IDE for the first five minutes. You may draw, type, dictate, or use a structured table.

An approved extended-time or asynchronous version uses the same starting
state and reasoning targets. Complete the initial model before receiving the
expert calibration; speed, handwriting, and drawing quality are not assessed.

## Starting state

```text
data address = A
size = 3
capacity = 4
allocation A = [11, 22, 33, unused]
alias = &data[1]
```

The program appends `44`, then appends `55`. The second append successfully moves storage from address `A` to address `B` and uses the course doubling policy.

## Five-minute response

Complete these three targets:

1. Show `data`, `size`, `capacity`, and logical values after appending `44`
   and after the successful moving growth and append of `55`.
2. Decide whether `alias` may be dereferenced after the moving growth.
   Explain in one sentence.
3. List the fields and values that must remain unchanged if growth fails
   instead.

### Optional compact response table

| Moment | `data` | `size` | `capacity` | Logical values |
|---|---|---:|---:|---|
| After `44` | | | | |
| After moving growth and `55` | | | | |

Alias explanation:

____________________________________________________________________

Failure-preservation list:

____________________________________________________________________

## Calibration follow-up

During expert calibration:

1. add the state immediately before growth for `55`;
2. identify the observable entry and return points at which the invariant must
   hold;
3. annotate any correction to the timed response.

## Expert calibration

When the instructor reveals the expert model:

- preserve your initial response;
- place a check beside correct reasoning;
- label each correction with `representation`, `ordering`, `ownership`, `pointer`, or `complexity`;
- finish: “The evidence that changed my model was …”

Correction:

____________________________________________________________________

The evidence that changed my model was:

____________________________________________________________________
