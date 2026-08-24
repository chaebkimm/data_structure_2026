# Module 1 Evidence Record

Name: ____________________________
Toolchain: _______________________
Core or extension submission: _______________________

## 1. Textbook-to-code mapping

Explain how the textbook's starting address, number of stored items, and
number of available slots map to the three `IntList` fields.

____________________________________________________________________

## 2. Representation invariant

State the complete invariant:

____________________________________________________________________

How does the implementation preserve it:

- before an operation? _____________________________________________
- after success? __________________________________________________
- after failure? __________________________________________________

## 3. Operation costs

| Operation | Cost | Evidence/reason |
|---|---:|---|
| `get` | | |
| append with spare capacity | | |
| one growth append | | |
| append, amortized | | |
| insert/remove near front | | |

## 4. Test evidence

| Case | Expected result | Actual result | Pass? |
|---|---|---|---|
| Empty get | | | |
| First append | | | |
| Repeated growth | | | |
| Invalid index | | | |
| Overflow request | | | |
| Forced allocation failure (instructor/CI) | | | |
| Destroy/reset | | | |
| Other | | | |

### Student-authored tests

For each test, state the claim it checks and why the supplied tests alone did
not make your evidence complete.

1. Test and rationale:

   ____________________________________________________________________

2. Test and rationale:

   ____________________________________________________________________

3. Test and rationale:

   ____________________________________________________________________

## 5. Engineering and resource-policy evidence

Compiler warnings:

```text
paste output here
```

Sanitizer, debugger, or instructor-CI result:

```text
paste output here
```

Dynamic growth protects the representation, but it does not authorize
unlimited retention. State one concrete maximum, eviction, sampling, or
backpressure policy for authentication-event ingestion:

____________________________________________________________________

What happens when that policy limit is reached, and how is the event or error
reported rather than silently lost?

____________________________________________________________________

## 6. Segfault Autopsy summary

- Trigger:
- First invalid assumption:
- Memory state:
- Repair:
- Regression test:

## 7. Textbook connection

Which lab operation implements the textbook's expansion sequence?

____________________________________________________________________

How does the implementation preserve the textbook's no-gap rule?

____________________________________________________________________

## 8. Correction note

My initial misconception:

____________________________________________________________________

The evidence that changed my reasoning:

____________________________________________________________________
