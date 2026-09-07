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

### How to evaluate efficiency

Running a program always requires a baseline amount of work and memory. Small examples make different methods appear similar. Their growth patterns become clearer as the amount of data increases. Programmers evaluate efficiency by analyzing how the required work and memory scale as the data grows.

### How to express efficiency

Programmers use Big O notation to name the growth patterns of work and memory. Letting n represents the amount of input, O(1) means the task requires a constant amount of work and memor. O(n) menas the work and memory grows proportionally with the amount of data.

### Preparing for the worst

Because small amounts of data are always fast to process, programmers measure efficiency by looking at the worst possible situation. We don't ask how fast the computer is on a good day when the user we want is the very first one we check. We ask: "If we have one million users and the one we need is at the very end of the database—or not there at all—how much work will the computer have to do?"

## Glossary

### Data

The raw information a computer program processes, such as usernames, text, numbers, or passwords.

### Data structure

The way programmers organize stored information according to the actions a program must perform. Different shapes of data (like Lists, Trees, or Graphs) require different structures.

### Efficiency

The measure of the processing time and memory required for a workload, often involving a tradeoff between minimizing steps and saving space.

### Big O notation

A standard notation programmers use to classify how a computer's workload scales as the amount of data grows.

### O(1)

Pronounced "O of 1." A classification meaning the amount of work does not grow based on the amount of data. The task requires a constant amount of effort whether there is one item or one million.

### O(n)

Pronounced "O of N." A classification meaning the workload grows proportionally with the amount of data. More data equals more work.