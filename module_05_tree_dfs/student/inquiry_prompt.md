# Stage A — Initial Inquiry: Visiting a Hierarchy

Name: ____________________________  
Date: ____________________________

Use only this file during the initial inquiry. Preserve your first answers.
Later, add labeled corrections instead of erasing your first thinking.

This activity reuses tree words from Module 2. A **tree** is a hierarchy of
connected items. Its one starting item is the **root**. Each item is a
**node**. A node may have a **left child** and a **right child** below it. A
**leaf** is a node with no children.

The example is a synthetic policy tree. **Synthetic** means invented for
safe practice. A **policy** is a set of rules. A computer **directory**
organizes entries so stored items can be located. This is not a real
directory or security policy.

## A. Read the tree

```text
50
├─ left: 30  [review]
│  ├─ left: 20
│  └─ right: 40  [review]
└─ right: 70  [review]
```

A **review marker** is a stored yes-or-no note saying that an item needs
attention.

List every key in the tree:

____________________________________________________________________

Which key is the root? _____________________________________________

Which keys are leaves? ____________________________________________

Which keys have review markers? ___________________________________

## B. Invent a visiting rule

To **visit** a node means to stop at it and perform the current task. In this
activity, the task is to write its key.

Invent a repeatable rule that starts at the root, visits every node exactly
once, and prefers a left choice before a right choice.

Your rule:

____________________________________________________________________

____________________________________________________________________

Use your rule on the tree. Write the keys in the order visited:

____________________________________________________________________

How will your method know that no node was missed?

____________________________________________________________________

## C. Remember choices not yet taken

Suppose your method begins at key 50, then reaches key 30, then reaches leaf
20.

At key 20, which parts of the tree still need attention?

____________________________________________________________________

What information must be remembered so the method can return to those
parts?

____________________________________________________________________

Could one remembered item be completed while another older item is still
unfinished? Explain.

____________________________________________________________________

## D. Report selected nodes

Now suppose the task is to report only nodes carrying a review marker.
The method must still inspect enough of the tree to find every marked node.

Which keys should be reported?

____________________________________________________________________

Would changing what gets reported require changing the tree’s child
relationships? Explain.

____________________________________________________________________

## E. Consider stopping conditions

What should your method do when it reaches a missing child position?

____________________________________________________________________

What should it do after visiting a leaf?

____________________________________________________________________

What would go wrong if the method kept following missing child positions
forever?

____________________________________________________________________

## F. Macro-Question

> How can one repeatable method visit every node in a tree, remember
> unfinished choices, and stop safely?

Your initial explanation:

____________________________________________________________________

____________________________________________________________________

One question your current method does not settle:

____________________________________________________________________
