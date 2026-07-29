# Chapter 12: Graph Theory I (Adjacency & Network Topologies)
**A Comprehensive Textbook and Pedagogical Blueprint for the Data Structures 2026 Curriculum**

---

## Abstract and Peer Review Introduction

As a postgraduate-level instructional architect and research peer, the following document represents the definitive textbook contents and pedagogical execution manual for **Week 12: Graph Theory I (Adjacency & Network Topologies)**. 

Following the mastery of hierarchical data structures (Trees and Heaps) in Phase III, Week 12 marks a profound architectural pivot into Phase IV: Complex Networks & Advanced Architectures. In traditional Computer Science Education (CSEd), Graph Theory is frequently introduced as an abstract, almost purely mathematical discipline. Students are taught to solve the Seven Bridges of Königsberg, find the shortest path between arbitrary cities on a map, or navigate a maze. While mathematically sound, this decontextualized, transmission-based pedagogy fails to engage the affective domain of the Cybersecurity freshman. It treats graphs as academic puzzles rather than physical, exploitable realities.

This chapter executes a radical epistemological shift. We do not teach Graph Theory to solve mazes; we teach it to **model the cyber battlefield**. A graph is the literal cartography of an enterprise network. Vertices are servers, workstations, and routers. Edges are open TCP ports, firewall rules, and compromised Active Directory trust relationships. 

By framing the data structure through the lens of a ransomware worm executing lateral movement, we leverage Richard Mayer’s Generative Learning Theory and the subcultural "Hacker Ethos." We shift the analytical focus from Time Complexity (Big-O) to Space Complexity (Memory). The student learns that choosing the wrong data structure (an Adjacency Matrix) for a sparse enterprise network is not just inefficient; it is a catastrophic architectural failure that will crash the attacker's own malware via Out-Of-Memory (OOM) exhaustion. 

Furthermore, by deconstructing the memory architecture of Nmap (the industry-standard network scanner), we validate the student's progression, proving that the C structures they are building are the exact mechanisms used by elite security tools. The following text is structured as a dual-layered manuscript, integrating the **Core Academic Content** (the rigorous technical explanations of C syntax, memory architecture, and graph topologies) seamlessly with the **Pedagogical Architecture** (the postgraduate-level commentary detailing *how* and *why* this content is delivered via the Sequenced Lecture Model).

---

## 1.0. Pedagogical Preamble & Epistemological Baseline

### 1.1. The Phase Objective: Escaping the Hierarchy
From Week 9 to Week 11, students operated strictly within hierarchies. Trees and Heaps are rigid: a child has exactly one parent, and data flows downward. There are no cycles. 
However, the real world is not a strict hierarchy. In an enterprise network, Workstation A can talk to Server B, Server B can talk to Router C, and Router C can talk back to Workstation A. This creates a **Cycle**. A data structure that allows many-to-many relationships and cyclical paths is called a **Graph**. The objective of Week 12 is to teach students how to represent this chaotic, interconnected reality within the linear, rigid confines of computer memory.

### 1.2. Epistemological Framing: The Ransomware Cartographer
To maintain domain enthusiasm and lower the affective filter, we frame Graph Theory through the lens of offensive reconnaissance and malware propagation.
*   **The Battlefield Map:** When a ransomware worm (like WannaCry or NotPetya) compromises a single host, it is blind. It must scan the network to find other vulnerable hosts. As it scans, it must build a map in its memory to track where it has been and where it can go. This map is a Graph.
*   **Sparse vs. Dense Networks:** We introduce the critical distinction between Sparse and Dense graphs. In a Dense network, almost every computer talks to every other computer. In a Sparse network (like a real enterprise environment segmented by VLANs and firewalls), a computer only talks to a few specific servers. We frame the choice of data structure (Matrix vs. List) as a life-or-death decision for the malware. If the malware uses a Matrix for a Sparse network, it will consume gigabytes of RAM storing "empty" connections, triggering the host's Endpoint Detection and Response (EDR) or crashing the system before it can propagate.

### 1.3. Target Schema Acquisition
By the conclusion of Week 12, the student must demonstrate mastery over three distinct cognitive schemas:
1.  **The Adjacency Matrix:** Understanding the 2D array syntax and internalizing the catastrophic $O(V^2)$ space complexity penalty.
2.  **The Adjacency List:** Spiraling the Week 7 Hash Table schema (Array of Pointers to Linked Lists) to represent sparse connections efficiently.
3.  **Directed vs. Undirected Edges:** Visuospatially mapping the difference between a bidirectional connection (symmetric memory) and a unidirectional connection (asymmetric memory representing firewall rules).

---

## 2.0. Asynchronous Pre-Lecture Module: Schema Priming

*Architectural Commentary: The C syntax for a 2D array (`int matrix[V][V]`) and an array of pointers (`struct Node* adjList[V]`) induces massive cognitive load. It combines the contiguous math of Week 2 with the pointer indirection of Week 5. According to Sweller’s Cognitive Load Theory, introducing this syntax simultaneously with the conceptual logic of Graph Theory will push the cohort into Vygotsky's Zone 3 (Panic Zone). The Pre-Lecture Module isolates and pre-trains this syntax.*

### 2.1. The "Syntax Primer" Video (5 Minutes)

**Textbook Content: The Syntax of the Grid and the Chain**

**1. The 2D Array (The Grid)**
In Week 2, we built 1D arrays: a single row of contiguous memory. To build a Graph, we often need a grid—rows and columns. In C, we declare a 2D array like this:
```c
int matrix[5][5]; // A 5x5 grid (25 total integers)
```
In physical memory, this is still just a single, flat, contiguous block of RAM. The compiler uses math to simulate the grid. To access the cell at row 2, column 3, we write `matrix[2][3]`. 
*The Memory Cost:* The size of this grid grows exponentially. If you have $V$ vertices (nodes), the memory required is $V \times V$ (or $V^2$). 

**2. The Array of Pointers (The Chain)**
In Week 7 (Hash Tables), we learned how to build an array where every slot holds a memory address pointing to a Linked List. We will use this exact same syntax for Graphs.
```c
struct Node* adjList[5]; // An array of 5 pointers
```
Remember the trap from Week 7: When you declare this array, it is full of garbage memory addresses. You must explicitly initialize every slot to `NULL` before you use it, or your program will Segfault.

### 2.2. Pre-Lecture Formative Assessment
To enforce compliance and verify schema acquisition, students complete a two-question, low-stakes quiz:
1.  *If a network has 65,536 IP addresses, how many total integer slots are required to build a 2D Adjacency Matrix?* (Answer: $65,536 \times 65,536 = 4,294,967,296$ slots. Priming the $V^2$ memory explosion schema).
2.  *True or False: In an Adjacency List, if Node A is not connected to Node B, we must store a `0` or `NULL` in Node B's specific slot to represent the lack of connection.* (Answer: False. We simply don't create a node. This primes the sparse memory schema).

---

## 3.0. Day 1: The Pseudocode Sanctuary (Theory & Visuospatial Encoding)

*Architectural Commentary: Day 1 enforces the "No C Syntax" rule for complex logic. The goal is to build a visuospatial map of the two competing Graph architectures. If students do not physically draw the Matrix grid and the List chains side-by-side, they will not grasp the profound memory trade-offs between them.*

### 3.1. Phase I: The Syntactic Sandbox (Minutes 0–12)

**Execution:** Students open a C file. They are tasked with writing a basic 3x3 2D array, initializing it with zeros using nested `for` loops, and manually setting `matrix[0][1] = 1` and `matrix[1][0] = 1`. They then print the matrix to the terminal.
```c
#include <stdio.h>

int main() {
    int matrix[3][3] = {0}; // Initialize all to 0
    
    // Node 0 connects to Node 1, and Node 1 connects to Node 0
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```
**Observation:** The instructor directs the students to observe the output. They will see a grid with a diagonal symmetry of `1`s. 
*ZPD Management:* Mentors circulate, asking: *"If Node 0 connects to Node 1, why did we also have to set `matrix[1][0]` to 1?"* This physical observation anchors the concept of an **Undirected Graph** (bidirectional communication) into deterministic reality.

### 3.2. Phase II: The Cognitive Reset (Minutes 12–15)
Laptops are closed. The phonological loop is cleared. The instructor prepares the cohort for the heavy intrinsic load of the Macro-Question.

### 3.3. Phase III: Macro-Question & Micro-Deconstruction (Minutes 15–25)

**The Macro-Question Presentation:**
> *"When mapping the lateral movement of a ransomware worm through an enterprise network, why is an Adjacency List vastly more memory-efficient than an Adjacency Matrix for a sparse network, and how does this impact the speed of the worm's propagation?"*

**Textbook Content: The Architecture of the Battlefield**

**Micro-Question 1: The Matrix and the $V^2$ Explosion**
*How does a 2D array represent connections, and why does it require $O(V^2)$ memory even if the network has zero connections?*
An **Adjacency Matrix** is a 2D grid. The rows represent the source host, and the columns represent the destination host. If Host 2 can talk to Host 4, we put a `1` at `matrix[2][4]`. If they cannot talk, we put a `0`.
The fatal flaw in the Matrix is that it forces us to store the *absence* of a connection. A `0` still consumes 4 bytes of RAM. If a ransomware worm scans a `/16` subnet (65,536 IP addresses), the Matrix requires $65,536 \times 65,536 = 4.2$ Billion slots. That is **17 Gigabytes of RAM** just to store the map. If the malware tries to allocate 17GB of RAM on a victim's workstation, the OS will kill the malware instantly. The Matrix is fatal for large networks.

**Micro-Question 2: The List and Sparse Networks**
*How does spiraling our Week 7 Hash Table architecture allow us to only store the connections that actually exist?*
Real enterprise networks are **Sparse**. Out of 65,536 IPs, a single workstation might only be allowed to talk to 3 servers (DNS, Domain Controller, File Share). The other 65,533 connections are blocked by firewalls.
To map a Sparse network, we use an **Adjacency List**. We create a 1D array of pointers (one for each IP). If Host 2 talks to Host 4, we go to index 2, and we add a Linked List node containing "4". We do not store `0`s. We only store the `1`s. 
For our `/16` subnet where each host talks to 3 servers, the Adjacency List requires 65,536 pointers + (65,536 * 3 nodes). This consumes roughly **4 Megabytes of RAM**. We reduced the memory footprint from 17 Gigabytes to 4 Megabytes. The malware survives.

**Micro-Question 3: The Time-Complexity Trade-off**
*If the Adjacency List saves gigabytes of RAM, what is the time-complexity penalty we pay?*
In computer science, you never get something for nothing. 
In a Matrix, if you want to know if Host A connects to Host B, you check `matrix[A][B]`. It takes $O(1)$ time. Instant.
In a List, if you want to know if Host A connects to Host B, you must go to index A, and then *traverse the Linked List* until you find B or hit `NULL`. This takes $O(E)$ time, where $E$ is the number of edges connected to A. We traded CPU time for RAM.

### 3.4. Phase IV: Visuospatial Sketchpad & Pseudocode (Minutes 25–35)

*Architectural Commentary: The visual language must explicitly map the difference between the two structures. Students must draw the exact same network twice to physically feel the wasted space of the Matrix versus the elegance of the List.*

**Standardizing the Visual Language:**
*   **The Graph:** Drawn as circles (Vertices) connected by lines (Edges). If the line has an arrowhead, it is a **Directed Edge** (one-way firewall rule). If it has no arrowhead, it is an **Undirected Edge** (two-way communication).
*   **The Matrix:** Drawn as a rigid grid. Every cell must be filled with a 1 or a 0.
*   **The List:** Drawn exactly like Week 7's Hash Table. A vertical column of squares (the array), with horizontal rectangles (Linked List nodes) growing out of them.

**The Pseudocode Exercise:**
Students must write the logic for `add_edge(u, v)` for both data structures, assuming an Undirected Graph.
*Example Student Pseudocode:*
```text
// MATRIX IMPLEMENTATION
FUNCTION add_edge_matrix(u, v):
    matrix[u][v] = 1
    matrix[v][u] = 1 // Because it is undirected!

// LIST IMPLEMENTATION
FUNCTION add_edge_list(u, v):
    // Add v to u's list
    CREATE new_node with value v
    new_node.next = adjList[u]
    adjList[u] = new_node
    
    // Add u to v's list (Because it is undirected!)
    CREATE new_node with value u
    new_node.next = adjList[v]
    adjList[v] = new_node
```

### 3.5. Phase V: The Cognitive Pause & Hybrid Verification (Minutes 35–50)

*Architectural Commentary: This generative encoding phase forces the student to visualize the exact memory state of a complex network. By enforcing absolute silence, we prevent dual-task interference in the phonological loop.*

**1. The Cognitive Pause (5 Minutes):**
Absolute silence. Laptops closed. 
**The Prompt:** *"I am projecting a diagram of a 6-node enterprise network. Nodes 0, 1, and 2 are workstations. Node 3 is a Switch. Node 4 is a Web Server. Node 5 is the Domain Controller. 
Notice the arrows: The workstations have undirected edges to the Switch. The Switch has a directed edge (one-way) to the Web Server. The Web Server has a directed edge to the Domain Controller. 
Silently draw the exact Adjacency List memory state for this network."*

**2. The Expert Reveal:**
The instructor projects the correct visuospatial map. 
*   Indices 0, 1, and 2 each have a single node pointing to `3`.
*   Index 3 has a Linked List containing `0 -> 1 -> 2 -> 4`. (It points back to the workstations because the edges were undirected, and it points to 4 because of the directed edge).
*   Index 4 has a single node pointing to `5`.
*   Index 5 is `NULL` ($\equiv$). It receives connections, but initiates none.

**3. The "Red Pen" Self-Correction:**
Students use a red pen to correct their diagrams. 
**Metacognitive Calibration:** *"If you drew a node for '4' in index 5's list, you violated the firewall rule. Cross it out in red. A directed edge from 4 to 5 means 4 can talk to 5, but 5 cannot initiate a connection to 4. In memory, directed edges are asymmetric. You just visualized how firewall rules are represented in RAM."*

---

## 4.0. Day 2: The C Crucible (Production Code & Implementation)

*Architectural Commentary: Day 2 translates the visuospatial map into C syntax. We spiral back to Week 7 to reinforce the initialization of pointer arrays. We then deconstruct the source code of Nmap, validating the Hacker Ethos and proving that the Adjacency List is the industry standard for network reconnaissance.*

### 4.1. Phase I: Sanitized Translation (Minutes 0–15)

**Textbook Content: The C Implementation and the Phantom Edge**
Let us translate our Adjacency List pseudocode into C syntax.

```c
#include <stdio.h>
#include <stdlib.h>

#define VERTICES 6

struct Node {
    int dest;
    struct Node* next;
};

struct Graph {
    // An array of pointers to Nodes
    struct Node* adjList[VERTICES]; 
};

// Function to create a new node on the Heap
struct Node* create_node(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->dest = v;
    newNode->next = NULL;
    return newNode;
}

void add_edge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest (Insert at front of Linked List)
    struct Node* newNode = create_node(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}
```

**The `NULL` Initialization Trap (Spiraling Week 7):**
When we instantiate `struct Graph* g = malloc(sizeof(struct Graph));`, the `adjList` array is filled with garbage memory addresses. If we do not explicitly initialize every slot to `NULL` using a `for` loop, the graph will contain "Phantom Edges"—connections to random memory addresses that do not exist. When we try to traverse the graph, the program will Segfault.

### 4.2. Phase II: Production Code Reveal (Minutes 15–30)

*Architectural Commentary: We now analyze how Nmap (Network Mapper) represents discovered subnets. This is a masterclass in instructional scaffolding. We show them that the exact concepts they are learning are used by the world's most famous hacking tool.*

**Textbook Content: Deconstructing Nmap Architecture**
Nmap is the industry-standard tool for network reconnaissance. When you run `nmap -p 1-65535 192.168.1.0/24`, Nmap scans 65,535 ports across 256 IP addresses. 

If Nmap used an Adjacency Matrix to store the results, it would need a grid of $256 \times 65535$. Most of those ports are closed. Storing "closed" states would consume massive amounts of RAM, slowing down the scan and potentially crashing the machine running the tool.

Instead, Nmap uses an architecture conceptually identical to an Adjacency List. 
*Sanitized Nmap Source Code (C++ `Target` and `PortList` classes):*
```cpp
class Target {
  public:
    struct sockaddr_storage targetsock; // The IP Address (The Array Index)
    PortList ports;                     // The Adjacency List of open ports
};

class PortList {
  private:
    Port *port_list[PORTLIST_BUCKETS]; // Array of pointers to Linked Lists
};
```
**Deconstructing the Architecture:**
Nmap maintains a list of `Target` objects (the IP addresses). Inside each `Target` is a `PortList`. The `PortList` does not store closed ports. It only allocates a `Port` object on the Heap when it discovers an *open* port, linking it into the chain. 
By using an Adjacency List, Nmap remains incredibly lightweight, allowing it to scan massive enterprise networks from a standard laptop without running out of memory. The C code you are writing today is the architectural foundation of offensive reconnaissance.

### 4.3. Phase III: Guided Implementation & Segfault Autopsy (Minutes 30–50)

*Architectural Commentary: Students must now execute an Adjacency List implementation. This transitions the theory into embodied, deterministic practice. When they trigger the Segfault, they perform an Autopsy, reinforcing the danger of uninitialized pointers.*

**The Implementation Task:**
Students are provided with a C program skeleton. They must implement the `Graph` struct, the `NULL` initialization loop, the `add_edge` function, and a `print_graph` traversal function.

**The Segfault Autopsy Protocol (The Phantom Edge):**
1.  **The Exploit:** Students successfully implement the Graph and print the connections.
2.  **The Crash:** The instructor orders the students to comment out the `for` loop that initializes `adjList[i] = NULL;`. They compile and run. The program immediately crashes with a **Segmentation Fault (Core Dumped)** during the `print_graph` phase.
3.  **The Autopsy Report:** Why did it crash? Students must draw the memory state. They must deduce that the `print_graph` function uses a `while (curr != NULL)` loop. Because the array was not initialized, `curr` was loaded with a garbage address (e.g., `0x7f8a9b`). The CPU traveled to `0x7f8a9b`, attempted to read the `dest` integer, hit protected memory, and the OS killed the program. 

*ZPD Management:* Near-Peer Mentors circulate. When a student asks why it worked perfectly before they commented out the loop, the mentor asks, *"Does the OS spend CPU cycles scrubbing memory with zeros before handing it to you? No. It gives you whatever was left behind by the last program. You must build your own ground wires."*

---

## 5.0. Asynchronous Post-Lecture Module: Synthesis & Exploitation

*Architectural Commentary: To consolidate the schema, students must apply their knowledge in a gamified, high-stakes environment. The Micro-CTF requires precise parsing of a Graph structure in memory, completely eliminating the possibility of Voodoo Programming. They must engineer the solution structurally.*

### 5.1. The Synthesis Portfolio (Red-Pen Digitization)
**Task:** Students scan and upload their Red-Pen corrected 6-node network diagrams from Day 1, along with their Phantom Edge Autopsy report from Day 2. 
**Professional Framing:** This is framed as a "Reconnaissance Threat Model." Students must write a one-page executive summary calculating the exact memory footprint of an Adjacency Matrix versus an Adjacency List for a `/8` subnet (16 million IPs) where each host only connects to 3 others. This trains them to articulate complex Big-O space complexity trade-offs to non-technical stakeholders.

### 5.2. The Micro-CTF: "Operation Lateral Movement"

**Textbook Content: Capture The Flag - Operation Lateral Movement**
You have been provided with a raw memory dump (`network_map.bin`) extracted from a compromised server used by a ransomware gang. 

**The Scenario:**
The ransomware gang mapped the internal enterprise network and stored the map in memory as an Adjacency List. You have extracted the binary representation of this list. 

**The Objective:**
In Graph Theory, the "Degree" of a vertex is the number of edges connected to it. In an enterprise network, the Domain Controller (the server that manages all passwords and authentications) almost always has the highest In-Degree, because every workstation must connect to it to authenticate.
You must parse the memory dump, reconstruct the Graph, and find the Domain Controller to capture the flag.

**The Execution:**
1.  **The Parser:** Write a C program that reads `network_map.bin`. The file contains a sequence of integers representing directed edges (e.g., `0 5` means an edge from Node 0 to Node 5).
2.  **The Reconstruction:** As you read the file, use your `add_edge` function to build the Adjacency List in your own program's Heap memory.
3.  **The Analysis:** Write a function that iterates through the `adjList` array. For each index, traverse the Linked List and count the number of nodes (calculating the Out-Degree). To find the In-Degree (which nodes are being pointed *to*), you must traverse the entire graph and tally how many times each destination node appears.
4.  **The Kill Shot:** Identify the array index with the highest In-Degree. Print that index to the terminal. If you correctly identify the Domain Controller, the CTF harness will validate the ID and print the cryptographic flag.

*Architectural Commentary: This CTF requires absolute mastery of the Adjacency List's internal mechanics. The student cannot brute-force the solution. They must physically reconstruct the fragmented memory architecture on their own Heap and traverse it deterministically. This satisfies the Hacker Ethos (analyzing malware memory dumps to find high-value targets) while enforcing rigorous understanding of Graph topologies.*

---

## 6.0. Instructor Directives & Psychosocial Calibrations for Week 12

*Architectural Commentary: Week 12 introduces Complex Networks, which frequently triggers "Graph Shock." The visual mess of nodes and crossing edges overwhelms the visuospatial sketchpad. The instructional team must carefully manage the cohort's psychosocial state to prevent the affective filter from blocking schema acquisition.*

### 6.1. Managing "Graph Shock"
When students see a network diagram with 20 crossing lines, their working memory is instantly overwhelmed. They attempt to process the entire graph simultaneously, leading to cognitive paralysis.
**Directive:** The instructor must aggressively scaffold this by teaching them to trace *one node at a time*. 
*   Say: *"Do not look at the whole network. The CPU does not look at the whole network. The CPU only looks at one array index at a time. Put your finger on Node 0. Where do the arrows leaving Node 0 go? Write them down. Now forget Node 0. Put your finger on Node 1."* 
*   By forcing the student to serialize the visual data, the instructor artificially lowers the element interactivity, preventing cognitive overload.

### 6.2. Explicitly Mapping the Spiral (Week 7 to Week 12)
If the instructor does not explicitly connect Week 12 to Week 7 (Hash Tables), students will view the Adjacency List as a completely new, overwhelming concept.
**Directive:** The instructor must explicitly state the pedagogical architecture: *"Look at the C code for the Adjacency List. It is exactly the same code we wrote in Week 7 for the Hash Table. The only difference is the epistemology. In Week 7, we used a math function to turn a string into an array index. Today, the array index is just the IP address of the computer. You already know how to build this structure. Today, we are just using it to map a battlefield."* This metacognitive framing reduces the perceived intrinsic load.

### 6.3. The "Battlefield" Metaphor
Students will ask why they need to learn both the Matrix and the List if the List is so much better for memory.
**Directive:** The instructor must use the Battlefield metaphor to explain the trade-off. *"The Adjacency List is a sniper rifle. It is lightweight, efficient, and perfect for sparse environments. The Adjacency Matrix is a nuclear bomb. It is massive, heavy, and consumes everything. But if you need to know instantly, in $O(1)$ time, if Node A connects to Node B, the Matrix gives you the answer. In Week 14, when we study dense, fully connected botnets, the Matrix will become our weapon of choice. A Security Architect must know how to wield both."*

### Conclusion to Week 12
By the end of Week 12, the student has mastered Graph Theory not as an abstract mathematical puzzle, but as the physical cartography of enterprise networks. They have learned how to synthesize 2D arrays and arrays of Linked Lists, how to calculate the catastrophic memory footprint of an Adjacency Matrix, and how elite tools like Nmap utilize Adjacency Lists for offensive reconnaissance. They have successfully entered Phase IV (Complex Networks) and are now prepared to unleash algorithms upon these topologies, beginning with Breadth-First Search (BFS) and Active Directory pathfinding in Week 13.