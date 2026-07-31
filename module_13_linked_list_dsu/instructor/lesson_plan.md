# Instructor Lesson Plan - Module 13

## Module identity

**Linked-List Retrieval Clinic and Union-Find Bridge** is the Linear stage
of Spiral 5. It returns to Module 1's linked-node preview and prepares DSU
for Kruskal without changing the capstone graph representation.

## Module question

> As relationships arrive one at a time, how can careful local link
> changes preserve ownership and answer whether two vertices are already
> connected?

## Five-gate control

1. **Gate A:** release only the standard and linear informal inquiry.
2. **Gate B:** reveal formal names, then preserve exactly three Cognitive
   Pause targets before opening vocabulary.
3. **Gate C:** release one investigation format. Preserve Sections A
   through F.
4. **Gate D:** release the short textbook and exact-equivalent models.
   Students add labeled corrections rather than erasing earlier work.
5. **Gate E:** release the lab, evidence, rubric, starter code, visible
   tests, supplied edge builder, and isolated autopsy.

Do not combine the archives or reveal later files early.

## Before class

- Verify the Stage A archive contains only its README and two inquiry
  versions.
- Confirm both prompts use the exact R-Q-P and A-H facts but none of the
  embargoed formal vocabulary, code, formulas, or answers.
- Prepare physical record cards labeled R, Q, P and device cards A through
  H. Physical materials are optional; every fact also appears in text.
- Run reference core, extension, student-template, and autopsy builds.
- Verify zero live list nodes after cleanup.
- Keep vocabulary closed until pause responses are preserved.
- Offer the linear materials, keyboard-accessible files, and approved
  extended-time/asynchronous pause without requiring disclosure.

## Meeting A - Retrieve, name, and reason

### 1. Gate A record inquiry - 10 minutes

Students follow R, Q, P; propose adding S; propose removing Q; and describe
cleanup. Ask:

- “What fact would be lost if Q disappeared too early?”
- “Which surviving record must change?”
- “How would you know every record was handled once?”

Do not supply pointer vocabulary or corrective syntax yet.

### 2. Gate A grouping inquiry - 10 minutes

Process:

```text
A-B, C-D, A-C, E-F, G-H, E-G, A-E
```

Students may circle cards, rewrite labels, or narrate groups. Then pose the
later D-H report. Preserve all initial schemes, including inefficient but
coherent ones.

### 3. Compare informal plans - 5 minutes

Invite two record plans and two grouping plans. Compare:

- what local information each plan saves;
- what whole-state fact each plan attempts to preserve;
- what work would repeat as reports grow.

Do not judge drawing style or arithmetic speed.

### 4. Gate B formal linked-list reveal - 18 minutes

Open `representation_reveal.md`. Introduce in this order:

1. address and pointer;
2. node, head, next, and `NULL`;
3. `*` in a declaration and `->` field access;
4. traversal;
5. allocation, ownership, and invariant;
6. push-front, first-match removal, and destruction;
7. leak, dangling pointer, and use-after-free.

Rebuild the exact P, Q, R push trace. Demonstrate the all-zero destroyed
state, including `limit=0`.

### 5. Formal DSU bridge - 20 minutes

Continue the reveal:

1. disjoint sets and connected components;
2. dense IDs and inactive sentinel 16;
3. parent forest and self-parent root;
4. root-only component sizes;
5. make-set;
6. iterative two-pass find and path compression;
7. union by component size and smaller-root ties;
8. same-set/no-merge cycle result.

Build the seven unions slowly. Leave D, F, and H on their longer paths.

### 6. Exactly-three-target Cognitive Pause - 5 minutes

Students complete:

1. safe deletion of Q;
2. exact H find/compression;
3. D-H same-set decision plus scope.

Use the same targets for all approved timing formats. Pause work is scored
for serious participation and correction, not immediate perfection.

### 7. Pause calibration - 10 minutes

Project or read the exact answers. Require students to preserve initial
responses and label changes:

- `ownership order`;
- `compression`;
- `same set`;
- `cycle`;
- `scope`.

Explicitly note that E is visited during H's compression but already points
to A; G and H are the entries whose stored values change.

### 8. Gate C investigation A-C - 15 minutes

Students complete list representation, mutation, and ownership sections.
Circulate for these misconceptions:

- head contains the whole node;
- releasing Q automatically reconnects R and P;
- `free` recursively releases later nodes;
- an absent removal must be an error;
- destroy resets only head and size. Correct this to the exact all-zero
  state, including limit zero.

### 9. Gate C investigation D-F - 20 minutes

Students complete the DSU forest, exact unions, compression, costs, and
scope. Require full arrays, not only group circles.

Use a brief peer check:

- every nonroot size is zero;
- component count equals root count;
- H path is exact;
- D-H does not merge;
- validator cost is not hidden.

### 10. Exit gate - 5 minutes

Prompt:

> Name one local field change and the whole invariant it preserves.

Collect one list example or one DSU example. Confirm Sections A-F are
preserved before releasing Stage D.

## Between meetings

- Release Stage D only to students who completed or arranged an equivalent
  for Sections A-F.
- Ask students to read the textbook once and add at most five labeled
  corrections to preserved work.
- Do not assign memorization of the 50-term vocabulary list.
- Verify the student release contains no solution or extension tests.

## Meeting B - Implement, test, and bridge forward

### 1. Gate D retrieval - 10 minutes

Without code, students write:

```text
save successor -> relink -> release
locate root -> compress
compare root sizes -> attach one root
```

They explain what must remain true after each sequence.

### 2. Gate E public contracts - 12 minutes

Open the lab and headers. Highlight:

- fixed maximum 16;
- exact list all-zero lifecycle;
- absent removal is `OK` with false;
- output preservation on every error;
- inactive DSU sentinel 16;
- no DSU allocation or destroy;
- full validators are diagnostic;
- external IDs checked before indexing.

Demonstrate the standard release build commands.

### 3. TODO 1 linked-list cluster - 25 minutes

Students complete push-front, remove-first, and destroy. Require a
before/after ownership diagram before running.

Checkpoint:

```text
R(17)->Q(23)->P(31)->NULL
remove 23
R(17)->P(31)->NULL
destroy
head=NULL, size=0, limit=0
```

Run visible tests and inspect the live-node counter.

### 4. TODO 2 make-set and find - 22 minutes

Students implement dense creation and iterative two-pass find. Require the
first pass to prove the root path before the second pass mutates it.

Checkpoint:

```text
H->G->E->A
parent after find(H): [A,A,A,C,A,E,A,A]
```

### 5. TODO 3 union - 22 minutes

Students locate both roots before compression, implement the size/tie
policy, and preserve output on error.

Checkpoint:

```text
union(D,H)
merged=false
parent=[A,A,A,A,A,E,A,A]
components=1
```

### 6. Exactly three student tests - 20 minutes

Require one test in each locked category:

1. list lifecycle and preserved failure;
2. creation/compression, smaller-root tie, and invalid ID;
3. repeated relationship, self-loop, component count, connected query, and
   trust scope.

Reject duplicate tests that merely repeat one visible assertion.

### 7. Supplied edge-list pre-lab - 12 minutes

Students read and test, but do not implement:

- two reciprocal incident records per dense edge ID;
- two identical records for a self-loop;
- parallel endpoints preserved by distinct IDs;
- one canonical output record per edge ID;
- relational signed-weight comparison.

Trace sorted A-D edges. A-C/3 is the first cycle-producing edge. Mention
that this is preparation for Kruskal, not Kruskal implementation.

### 8. Bounded autopsy - 10 minutes

Students predict before running the isolated faulty executable. Focus on
the first invalid lifetime action rather than demanding a crash.

Accept sanitizer output, debugger evidence, or the supplied deterministic
trace. Confirm the faulty object is absent from normal links.

### 9. Cost, trust, and Spiral 5 close - 8 minutes

Students distinguish:

- local `O(1)` push mutation from separate `O(n)` validation;
- amortized DSU work from a full diagnostic scan;
- modeled membership from authorization or trust;
- DSU connectivity from a route, shortest path, resilience, and deletion.

Preview the shared Spiral 5 idea: later AVL rotations and Kruskal edge
acceptance also make local changes while preserving global invariants.

## Formative misconceptions

- A pointer stores an object rather than an address.
- `NULL` is an allocated empty node.
- The list allocation releases all later nodes at once.
- Reading a released field is safe if the bytes did not change.
- A shallow copy creates an independent list.
- Every DSU parent must point directly to the root at all times.
- Component size belongs at every member.
- Path compression changes which component an ID belongs to.
- Union attaches one input ID directly rather than one representative root.
- A same-root union is an error rather than successful no-merge.
- `alpha(n)` means each call is literally constant.
- A complete validator can be inserted into every call without affecting
  reported cost.
- Shared membership proves trust, an actual route, or authorization.
- The linked clinic changes the capstone graph backend.

## Extension prompts

Only after core completion:

- compare union by rank with union by component size;
- measure parent depth with and without compression;
- implement a nonowning iterator under a clearly stated mutation rule;
- explain why removing relationships is difficult for basic DSU;
- add equal-weight parallel edges to the supplied pre-lab.

Do not add linked-list sorting, generic `void *` nodes, DSU rollback,
concurrent mutation, or Kruskal implementation to the core module.

## Submission check

- [ ] Stage A and exactly three pause targets are preserved.
- [ ] List trace and all-zero destroy are exact.
- [ ] No leak, dangling link, or normal-build use-after-free remains.
- [ ] Seven-union, H-find, and D-H arrays are exact.
- [ ] Exactly three original test categories add meaningful assertions.
- [ ] Invalid IDs are rejected before indexing.
- [ ] Builds and available memory evidence are recorded.
- [ ] Edge builder remains supplied read/test work.
- [ ] Complexity describes the actual validation strategy.
- [ ] Trust and DSU limitations are explicit.
