# Isolated Autopsy Program

`faulty_preorder.c` is a complete, standalone program. It does not use the
student implementation and contains no undefined behavior.

The program intends to perform preorder on this tree:

```text
        50
       /  \
     30    70
    /  \
   20  40
```

It contains one deliberate behavior defect. Build it, predict the complete
output before running it, locate the earliest decision that causes the
difference, and then compare the result with the required preorder
`50,30,20,40,70`.
