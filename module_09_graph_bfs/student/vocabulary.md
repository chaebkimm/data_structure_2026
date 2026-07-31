# Module 9 Vocabulary Reference

Keep this file closed until the Cognitive Pause response is preserved.

- **active vertex:** a vertex whose ID is from 0 through one less than the
  graph's stored vertex count.
- **adjacency list:** one stored collection of outgoing neighbors for each
  vertex.
- **adjacency matrix:** a square table whose cell `[u][v]` states whether
  edge `u -> v` exists.
- **allocation:** a block of storage obtained while a program runs.
- **auxiliary space:** temporary working storage separate from the input
  graph and returned output.
- **breadth-first search (BFS):** a method that processes smaller hop
  counts before larger hop counts from one source.
- **caller:** code that asks a function to run.
- **candidate:** a temporary possible output that is published only after
  all required work succeeds.
- **commit:** copy a completed candidate into output owned by the caller.
- **discovered:** successfully added to waiting work earlier.
- **distance:** the minimum edge or hop count from the source in this
  unweighted graph.
- **dynamic array:** a sequence in adjacent memory slots whose allocation
  may be obtained or replaced while a program runs.
- **edge:** one stored direct relationship between vertices.
- **FIFO:** “first in, first out,” the Queue rule that removes the
  earliest-added waiting item.
- **frontier:** discovered vertices that are still waiting to be processed.
- **graph:** a model of items and their direct relationships.
- **hop:** one followed edge.
- **ID:** an identifying number.
- **invariant:** a rule that remains true at each completed step.
- **outgoing neighbor:** the destination of an edge leaving the current
  vertex.
- **path:** a route that does not repeat a vertex.
- **path certificate:** a returned path whose endpoints, edges, and hop
  count can be checked.
- **predecessor:** the previous vertex on the route fixed at first
  discovery.
- **processed:** removed from the Queue and recorded in visit order.
- **Queue:** a waiting collection that removes the earliest-added item.
- **reconstruct:** build a forward path by following predecessors backward
  and reversing the sequence.
- **sentinel:** a stored value chosen to represent a special case; this
  package uses 16 for no distance or no predecessor.
- **source:** the selected starting vertex.
- **unreachable:** having no directed route from the selected source.
- **unweighted graph:** a graph in which every edge contributes one hop.
- **vertex:** one item stored in a graph.
- **visit order:** the order in which vertices are dequeued and recorded.
