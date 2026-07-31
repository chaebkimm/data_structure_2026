# Student Code Package

You will complete exactly three operations in
`starter/alert_priority_queue.c`:

1. apply the comparator and scan for the minimum record's index;
2. insert an alert, growing the array geometrically when needed; and
3. extract the minimum alert, replacing its slot with the last live record.

A **Priority Queue** chooses a waiting record by a defined priority rule.
This package uses a **minimum** rule: a smaller `size_t` priority is selected
first. Equal priorities are selected by the earlier `size_t` arrival
sequence, so the behavior is **stable**. `size_t` is a C whole-number type
used for sizes and array positions; it cannot represent a negative number.
Replacing the removed slot with the last record is called **swap-last
removal**. It avoids shifting every later record, and physical array order
may change. The unsorted array grows geometrically and holds at most 64 live
records.

Edit only:

- `starter/alert_priority_queue.c`; and
- `tests/test_student.c`.

Run the public core tests from this directory:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1
```

Run your three tests:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -StudentTests
```

Run the isolated faulty program:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

GNU Make users can run:

```sh
make starter-core
make starter-student-tests
make autopsy
```

The starter is intentionally incomplete. A failed first test run is
expected. Fix the earliest failed requirement without changing the public
header or core tests.
