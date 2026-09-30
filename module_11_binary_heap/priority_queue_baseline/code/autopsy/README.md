# Safe Stable-Tie Autopsy

`faulty_tie.c` is a complete standalone program. It does not include or link
the student Priority Queue. It uses four fixed synthetic records, performs no
allocation, and keeps every access inside the array.

The fixture is:

```text
index 0: alert 80, priority 2, sequence 0
index 1: alert 91, priority 1, sequence 1
index 2: alert 17, priority 1, sequence 2
index 3: alert 44, priority 3, sequence 3
```

Before running it:

1. predict the selected alert;
2. apply the published stable comparator and predict its selection; and
3. identify the first comparison at which those answers diverge.

After running it, explain why replacing the current choice merely because an
equal numeric priority appears later violates stability. State the smallest
comparator correction and one regression test using at least three tied
alerts.

Do not replace the fixture with production alerts, logs, hostnames, or
identifiers.
