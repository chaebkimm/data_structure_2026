# Module 5 Lesson Plan

## Outcomes

Students will trace and implement preorder copy, inorder expression printing,
and postorder evaluation on the same expression tree. They will connect
recursive depth to `O(h)` call space and preserve caller state after failure.

## Meeting A

1. Rebuild `(3+5)*2` from Chapter 2.
2. Trace one branch to a leaf and name the saved return work.
3. Compare the three visit positions using the diagram.
4. Complete preorder copy and prove address independence.

## Meeting B

1. Derive the parentheses needed by inorder output.
2. Trace postorder values `3, 5, 8, 2, 16`.
3. Complete printing and evaluation.
4. Run the pool-exhaustion autopsy and discuss rollback.
5. Finish student tests and the evidence record.

## Checks for understanding

- Why must copy create the parent before attaching children?
- Why must evaluation process the operator last?
- What changes when a balanced tree becomes a chain?
- Which outputs remain unchanged after a failed operation?
