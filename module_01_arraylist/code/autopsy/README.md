# Isolated Memory-Fault Autopsy

`faulty_append.c` is intentionally broken. It must not be linked into the normal library or test targets.

Before running it:

1. Predict the first statement that can make the list invalid.
2. Record the expected `data`, `size`, and `capacity` after the simulated allocation failure.
3. Predict where the program may first show an observable symptom.

## Inspect without the intentional fault

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy -InspectOnly
```

## Run the intentional fault

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build.ps1 `
  -Target autopsy
```

The second command may produce sanitizer output, an access violation, a segmentation fault, a zero exit, or another result because the program deliberately invokes undefined behavior. A dramatic crash is not the learning target.

Use `student/segfault_autopsy.md` to distinguish trigger, first invalid state, and later symptom. Preserve your prediction and annotate any correction after observing the run.

Do not add this executable to a normal passing test suite.
