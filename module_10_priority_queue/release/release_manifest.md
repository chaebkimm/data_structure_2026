# Chapter 10 Current Student Release

Generate the standalone priority-queue package from the repository root:

```sh
python3 module_10_priority_queue/release/prepare_student_release.py
```

Default output is dist/module_10_priority_queue.zip inside the module. Pass --output with a new path for repeated verification. Existing files are never overwritten. PowerShell uses prepare_student_release.ps1 -OutputPath with the same policy.

## Exact inventory

The packager explicitly lists 16 student files: lab.c, the two presentation references, both textbooks, vocabulary, lab, two inquiry formats, representation reveal, pause, two investigation formats, evidence template, rubric and priority-queue autopsy. It includes four code/tests files (core, student smoke, comparison and shared fixtures), five release/stage opening notes, the student root README, code README/Makefile/build.ps1 and diagrams/priority_queue_models.md. A generated MANIFEST.txt gives the 30 source files' SHA-256 values, for **31 total entries**.

The exact source and presentations are included without editing. No graph dependency, instructor directory, legacy file, alternate implementation, release tooling, generated executable or build directory is included. The five opening notes are checkpoints within one artifact, not separate assignments.

## Determinism and verification

Source bytes are read before writing. Entry names are validated, entries are sorted, timestamps and permissions are fixed, and the resulting ZIP is read back in memory to verify the inventory and every byte. The manifest excludes itself from its hashes. Repeated packaging from identical inputs yields identical archive bytes within the same toolchain.

Run the package regression checks:

```sh
python3 -m unittest discover -s module_10_priority_queue/release -p 'test_*.py' -v
```

These verify deterministic bytes, manifest/source equality, exclusions, unsafe paths, overwrite refusal, extracted links and standalone compilation/tests. Independently run the repository core suite under sanitizers as documented in code/README.md. No PowerShell execution is claimed when that runtime is unavailable.

The old module_11_graph_dijkstra.zip is preserved in legacy/dist as a historical artifact. It is not overwritten or redistributed as the current lesson.
