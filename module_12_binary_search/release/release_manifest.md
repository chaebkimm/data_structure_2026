# Module 13 Student Release

Run `python release/prepare_student_release.py --output /absolute/path/module13.zip` from the module root. The default is `dist/module_13_search_sort_consolidation.zip`. Existing archives are never overwritten.

The archive contains a student landing page, every current file in `student/`, the code guide, Makefile and PowerShell runner, core oracle tests, student test starter, and `MANIFEST.txt`. It excludes instructor answers, instructor plans, build products, and the packaging script. It imports no sibling module. The same source is used in the repository and extracted archive.

Before distribution, extract to a fresh temporary directory, run `make -C code`, compare canonical source/document bytes, and check local Markdown links. Core checks must pass before students add tests. Preserve predictions before textbook/source explanations; the workbook supplies the common evidence record. One archive supports one 180-minute lesson and one submission.
