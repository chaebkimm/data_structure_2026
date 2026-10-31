# Chapter 0. How to Store Data Smartly

## Thinking Logically

### The social media app

Imagine you are building a new social media application. Your app needs to handle posts, comment threads, and data on who follows whom. Because the shape of the information changes depending on the feature, the way we store it changes, too.

- The feed (list): When a user opens the app, they see a chronological feed of posts. This is a simple, straight line. One post follows another.
- The comments (tree): If a user clicks on a post, they see the comments. User A leaves a comment. User B and User C reply to User A. User D replies to User C. This branches out like a family tree (a nested hierarchy).
- The follower network (graph): If you map out how users connect to each other, it becomes an interconnected web. You follow John, John follows Mary, Mary follows you back, and you both follow a celebrity. It is a network of connections.

### What information does the program store?

The program processes and saves information such as usernames, post content, timestamps, and follower counts.

### How can the program organize it?

Programmers organize stored information according to the actions a program perform—like lining up posts in a chronological List or linking users together in a graph.

### What does efficiency mean?

Programs consume processing time and memory. Efficiency is the evaluation of the processing steps and memory required under a specific workload. Because a data structure often uses additional memory to reduce processing work, both resources cannot always be minimized simultaneously.

### How can we count the work?

Store ten user IDs in an array. If we know the position we want, reading that item inspects one ID. If we know only the ID's value, compare items from the beginning until a match appears. Finding the last item or confirming that no match exists inspects all ten IDs.

Now store one hundred IDs. Reading a known position still inspects one ID. Searching for a value at the end or absent from the array inspects one hundred IDs. Count the inspected items first, then ask how that count changes as the input grows.

### How does storage grow?

The array needs ten integer slots for ten IDs and one hundred slots for one hundred IDs. Either search can use a fixed number of extra variables to record the current position and target. The stored input grows, while the extra search storage stays constant. Count processing work, stored input, and extra storage separately.

### How do we express this growth?

Let `n` be the number of stored IDs. A cost whose bound stays constant as `n` grows is written `O(1)`. Reading a known position takes `O(1)` work. A cost bounded by a constant multiple of `n` for large enough inputs is written `O(n)`. Checking every ID takes `O(n)` work. This way of expressing a growth bound is called Big O notation.

The array uses `O(n)` storage, and the search uses `O(1)` extra storage. A time bound describes work; a space bound describes storage. A linear search can therefore take `O(n)` time while using `O(1)` extra space.

### Which search case are we counting?

A value search can stop after one comparison if the first ID matches. This is the best case. It needs `n` comparisons if the ID is last or absent. This is the worst case. An average depends on how often the different cases occur in the workload.

State the case before giving its cost. Here the value search has `O(1)` best-case time and `O(n)` worst-case time. Big O describes a bound on the chosen cost; the notation itself does not select the worst case.

## Glossary

### Data

The raw information a computer program processes, such as usernames, text, numbers, or passwords.

### Data structure

The way programmers organize stored information according to the actions a program must perform. Different shapes of data (like Lists, Trees, or Graphs) require different structures.

### Efficiency

The measure of the processing time and memory required for a workload, often involving a tradeoff between minimizing steps and saving space.

### Big O notation

A notation for an upper bound on how work or storage grows with the input size. State the measured resource and the input case separately.

### O(1)

Pronounced "O of 1." A constant upper bound as the input grows. Reading one known array position takes constant work; keeping a fixed number of search variables takes constant extra storage.

### O(n)

Pronounced "O of N." An upper bound proportional to input size `n`. Inspecting every stored ID takes linear work; storing all `n` IDs takes linear space.
