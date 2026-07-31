# Student Code Package

`TODO` marks an unfinished section. You will complete exactly three
implementation `TODO` sections:

1. validate the Queue representation;
2. enqueue one event code; and
3. dequeue the oldest event code.

A **Queue** removes the item that has waited longest. **First in, first out
(FIFO)** means the first item added is the first removed. The supplied
setup, peek, cleanup, and status functions remain unchanged.

You will also complete the three test `TODO` sections. Edit only:

- `starter/event_queue.c`; and
- `tests/test_student.c`.

Run the public core tests:

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
header, supplied functions, or supplied tests.
