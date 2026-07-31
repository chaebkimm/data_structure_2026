# Module 10 Evidence Record

Name: ____________________________  
Date: ____________________________  
Compiler or instructor CI: __________________________________________

CI means a separate computer automatically builds and tests submitted code.
Use an approved equivalent when local tools are unavailable.

## 1. Preserved reasoning

- Stage A response location: _________________________________________
- Stage B three-target response location: ___________________________
- Labels used on corrections: ______________________________________
- Evidence that changed my thinking: ________________________________

## 2. Comparator contract

Complete:

```text
Record a comes before record b when:
```

____________________________________________________________________

Why alert ID is excluded:

____________________________________________________________________

## 3. Canonical trace

Post-insertion fields:

```text
capacity:
size:
next_sequence:
physical active IDs:
logical service IDs:
```

Swap-with-last states after the first three extractions:

```text
after 88:
after 17:
after 63:
```

Total comparisons for all seven extractions: ________________________

Drained-state fields:

```text
data:
capacity:
size:
next_sequence:
```

## 4. Implementation evidence

### TODO 1 — Comparator and scan

Smallest test run: _________________________________________________

How the metric saturates: __________________________________________

### TODO 2 — Insert and growth

Smallest test run: _________________________________________________

How allocation failure preserves state: ____________________________

### TODO 3 — Extract and swap-last

Smallest test run: _________________________________________________

Why output is committed last: ______________________________________

## 5. Exactly three original tests

### Test 1 — Mixed priorities and stable ties

Claim: _____________________________________________________________

Key input and assertions: __________________________________________

### Test 2 — Growth and swap-scrambled storage

Claim: _____________________________________________________________

Key input and assertions: __________________________________________

### Test 3 — Empty and full failure preservation

Claim: _____________________________________________________________

Key input and assertions: __________________________________________

Supplied instructor/core allocation-failure evidence: ______________

## 6. Build and run evidence

Warning-enabled command: ___________________________________________

Core-test result: __________________________________________________

Student-test result: _______________________________________________

Sanitizer, debugger, or instructor-CI evidence: _____________________

## 7. Workload comparison

```text
unsorted 32 inserts — record comparisons:
paper sorted 32 chosen inserts — record comparisons:
unsorted 32 extracts — record comparisons:
paper sorted 32 right-end extracts — record comparisons:
```

Backend selection for insert-heavy work:

____________________________________________________________________

Backend selection for removal-heavy work:

____________________________________________________________________

## 8. Contract boundaries

What constant-time validation can check:

____________________________________________________________________

What it cannot prove:

____________________________________________________________________

Why output must not alias owned storage:

____________________________________________________________________

## 9. Safe autopsy

Correct selected ID: __________  Faulty selected ID: __________

First divergent comparison: _______________________________________

Exact repair: ______________________________________________________

Regression test: __________________________________________________

## 10. Policy and safe meaning

Starvation scenario and possible policy:

____________________________________________________________________

Mutable-priority hazard:

____________________________________________________________________

Decrease-key versus duplicate/stale entry:

____________________________________________________________________

What passing this lab does **not** prove about a real SOC:

____________________________________________________________________

## 11. Final synthesis

In three sentences, answer the module question using:

1. the service rule;
2. one backend cost; and
3. one fairness or update risk.

____________________________________________________________________

____________________________________________________________________
