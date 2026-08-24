# Korean Textbook Validation Record

The validation date is August 14, 2026. The targets are the introductory textbook and the student textbooks from Chapters 1 to 16.

## Beginner Reading Validation

We read through the text by dividing into three reader roles.

* For Chapters 1–5, we assumed the reader only knows C variables, functions, arrays, loops, and conditionals.
* For Chapters 6–10, we assumed the reader has completely understood Chapters 1–5.
* For Chapters 11–16, we assumed the reader has completely understood Chapters 1–10.

We re-read each chapter following the five steps used in Chapter 1: understanding the problem, efficiency, vocabulary, coding plan, and C code. If an idea suddenly appeared without being explained in an earlier step, or if the plan and the code were different, we marked it as a failure. After fixing the failed sentences and examples, we read them again using a different reader role.

## Code and Document Validation

* We made sure that each chapter's public headers, provided tests, and baseline code matched the textbook's rules for limits, states, and keeping the exact state after a failure.
* The `solution-core` tests of the baseline code all passed for the rewritten chapters from 2 to 16. During each cross-review, the required `solution-extension` tests and the compilation of the main C examples also passed.
* We checked the main examples of each chapter and the exact order of visiting, taking out, and selecting items.
* We checked if all chapters from 1 to 16 had the five core sections in the exact same order.
* We checked the pairs of code blocks and the links in the table of contents.
* We checked that no banned old terms or overly formal ending styles were left in the text.
* We checked that explanations used short, plain sentences, and that question sentences and question-style titles asked directly.
* We checked that the subtitles for "Thinking Logically" and "Calculating Efficiency" were short questions or clear answer titles, just like in Chapter 1.
* We checked that we explained the ideas first before giving them formal names, and that the coding plan and C code followed the same order of actions.
* `git diff --check` passed successfully.

## Vocabulary Rules

We use the vocabulary boundary table and the fixed vocabulary list in the [Korean Textbook Style Guide](https://www.google.com/search?q=KOREAN_TEXTBOOK_STYLE_GUIDE.md) as our strict standard. For any future edits, we will not just use new names right away; we will update this table first before applying them.

## Actual Validation Status

This current validation was a mock (practice) beginner reading. We have prepared the [Actual Beginner Pilot Package](https://www.google.com/search?q=textbook_pilot/README.md), but we do not have actual test responses from real students yet.

We will only change the status to an "actual pass" after we record how much time real participants took to explain things in their own words, which exact sentences they got stuck on, and their reasons for giving wrong answers. Until we have those real records, we will not add any more content or widen the scope.