# Module 13 — Left-Leaning Red–Black Trees and Review

Insert 10 through 70 into an ordinary BST in increasing order. Finding 70 takes seven node visits. Can we keep the familiar binary search and change how we insert? In this lesson each node stores one key and the color of its incoming link. Students use a left rotation, a right rotation, and a color flip to restore balance as an insertion returns to the root.

| Class material | Where to start |
|---|---|
| Reading and worked examples | [English chapter](student/textbook.md) · [한국어 교재](student/textbook_korean.md) |
| Guided C lab | [Trace and submission](student/lab.md) · [Demo](code/demo.c) · [LLRB implementation](code/llrb.c) |
| Teaching and assessment | [Instructor guide and answers](../instructor_guide/chapter_13.md) · [Week 13 questions](../student_question_bank/week_13_llrb.md) |

From this directory, run `make -C code` to print both insertion sequences and run the checks. The class spends 120 minutes on search and bottom-up insertion and 60 minutes on course review and one submission. Students group the binary keys on paper to read a 2–3–4 node. A lone red left link forms a 3-node. Two red children form the temporary 4-node that the C insertion splits with a color flip.
