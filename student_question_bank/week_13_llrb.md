# Week 13 — Left-Leaning Red–Black Trees and Review

Use these questions with the [student chapter](../module_13_llrb/student/textbook.md) and [guided lab](../module_13_llrb/student/lab.md).

**Week 13 vocabulary (5 terms).** Red link, black height, left rotation, right rotation, color flip. Retrieve edge height and BST ordering from Week 12.

## Search and insertion

1. Which 2–3–4 node does 20B with a single red left child 10R represent? Where are its three child ranges?
2. Why can a new red leaf be attached without immediately increasing a path’s black count?
3. Insert 10, 20. Which link leans right before the repair? Which key becomes the subtree root?
4. In a fresh tree, insert 30, 20, 10. What condition triggers a right rotation? Which condition becomes true immediately afterward?
5. During a rotation, which node inherits the old root’s color? Where does the subtree between the two keys go?
6. Just before the flip, 20B has red children 10R and 30R. Which 2–3–4 node do they encode? Which keys are grouped together after the root is recolored?
7. In the ascending sequence from 10 to 50, where does 30 move when 20 rotates left? Which path finds it afterward?
8. In the same sequence, continue with 60 and 70. Where do the two flips occur on insertion of 70? Why do we set the final root to black?

## Cost and workload

9. After inserting 10 and 20, find two root-to-missing-child paths of different lengths. How many black keys does each contain?
10. In the completed ascending seven-key tree, how many nodes does a lookup for 70 visit? How does an ordinary BST built in the same order compare?
11. If a path contains b black keys, why can it contain at most 2b keyed nodes? How does grouping the keys after all temporary 4-nodes have split bound b?
12. For an index with frequent insertions, how would a requirement for sorted output affect your choice between a hash table, a sorted array, and an LLRB?
