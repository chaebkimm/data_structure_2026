# Supplied Priority Queue Baseline

This completed implementation appends records to an unsorted array, scans
for the minimum, and fills an extracted slot with the last live record.
Smaller priority comes first. Equal priorities use earlier arrival sequence.
The identifier and current array position never settle a tie.

Trace this reference during Module 11's opening 40-minute block. Keep it
unchanged and compare its outputs and comparison counts with your Heap.
For the seven-record fixture, insertion uses zero comparisons and draining
uses 21. The Heap uses 8 for insertion and 12 for draining; count its checker
separately.

From the released `code/` directory, run:

```sh
make baseline-core
```

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 -Target baseline
```

The baseline and Heap define the same service functions. Build them as
separate programs with their own headers. Do not link both implementations
into one executable. The baseline has no Heap-order checker.

This directory contains a completed scan reference and its public tests.
Your required implementation is `code/starter/alert_priority_queue.c` in
Stage E. There is one combined Module 11 submission.
