# Chapter 12 Lab Slides — Trace the Supplied AVL Source

Use the [lab](lab.md) for the assignment and [lab.c](lab.c) as the actual
source. Show one state per scene. Keep node IDs separate from key letters.

## 1. Which source are we running?

The source includes Module 2's `nodes[10]` and has no `main`. A driver
includes the lab once and supplies `int main(void)`. Build with the
student directory and repository root on the include path. Do not link
another compiled copy of either included source.

## 2. What must exist before insertion?

Prepare a fresh valid ID, its `char` key, and child links -1. Start a new
tree at root -1. `alphabet_init()` prepares A=0 through J=9; its
`nodes_size=10` does not count the nodes reached from a selected root.
Never reinsert a live ID or attempt an eleventh ID as a rejection test.

## 3. Why can sorted input be slow?

Trace A,B,C,D,E,F,G into an ordinary BST. Its height is 6. Finding G or
missing H visits seven records. Use D,B,F,A,C,E,G with the same keys; G/H
each visit three. Count records, not the final absent link.

## 4. Which height does the source use?

Show `get_height(-1)==-1`, leaf height 0, and
`height[i]=max(height(left),height(right))+1`. State left-minus-right
balance and allowed values -1,0,1. Compare independently measured height
with the separate saved `height[]` array.

## 5. What does the recursive assignment save?

Trace `l = nodes[i].left = _add(l,new_node)`. Save the returned subtree
root in the actual link and the local variable used for balance. Show the
right-side mirror. The base case connects an existing fresh node; it does
not allocate a record.

## 6. Which case is first unbalanced?

Use CBA, ABC, CAB, and ACB for LL, RR, LR, and RL. All finish at B with
children A/C, heights 1/0/0, and inorder ABC. LL/RR use two link changes;
LR/RL perform four direct link changes in one helper each.

## 7. Where does the middle subtree go?

For LL, save `lr` before assigning `nodes[l].right=i`; reconnect it as
`nodes[i].left`. For RR, move `rl` to `nodes[i].right`. For LR and RL,
trace both saved child IDs of the promoted middle node. Use a nonempty
middle subtree so a lost-link defect cannot hide behind -1.

## 8. Which saved height is ready first?

The helpers only relink. In `_add`, update LL `i,l`; RR `i,r`;
LR `i,l,lr`; RL `i,r,rl`. Show that the new root reads refreshed lower
heights. Keep the returned root in `root = _add(root,id)`.

## 9. What changes when equal keys arrive?

Use three different IDs carrying B. New equals descend left, but an LL
rotation places an equal key on the right. Check nondecreasing inorder
and exact IDs. Equal-key acceptance is different from reusing a live ID.
There is no duplicate-rejection status.

## 10. What evidence belongs in the submission?

Run `make -C module_12_bst_avl/code lab-compile core student-tests comparison`.
Record the four traces, independent invariants, original tests, seven-key
BST/AVL comparison, commands/output, and correction trail in the
[evidence record](evidence_template.md). Separate local rotation work,
one-path insertion, recursive space, and diagnostic scans. Explain the
Heap/BST/AVL distinction and the limits of the security claim.
