# Left-Rotation Leak Autopsy

Start with this three-node shape:

```text
20
  \
   30
  /
 25
```

The node containing `25` is the **middle subtree**. A correct left rotation
moves that subtree to the right link of `20` before making `20` the left
child of `30`.

The isolated faulty branch first writes `NULL` to the right link of `20`.
That replacement is wrong, but `30` still reaches `25` through its left link
at that instant. The following assignment overwrites the left link of `30`
with the address of `20`. That second assignment removes the last reachable
link to `25`, so the allocated node cannot be released. This is a **memory
leak**: allocated storage has become unreachable.

The ordinary target is safe and inspect-only:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File ..\build.ps1 `
  -Target autopsy
```

It explains and performs the correct rewiring, checks that all three nodes
remain reachable, and cleans them up.

The actual defective branch is intentionally isolated. It requires a
sanitizer and is compiled but never run automatically:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File ..\build.ps1 `
  -Target autopsy -UnsafeAutopsy -Sanitize
```

Use the unsafe binary only in an instructor-controlled disposable
environment. A leak detector should report the lost allocation for node
`25`.
