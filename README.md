Echo Server Verification - Final Report
=======================================

Authors: Reagan Caliendo (rcali3), Gianmarco Luciano (gluci3)  
Course: CS 472 @ UIC
Tool: VeriFast  
Language: C

---

Files Included
-----------------

- `echo_verify.c`:  
  Final implementation of a memory-safe echo buffer. This file contains:
  - Struct definition (`struct buffer`)
  - Initialization (`create_buffer`)
  - Simulated message send/receive functions
  - Deallocation (`destroy_buffer`)
  - Complete annotations for memory safety using VeriFast

- `README.md`:  
  This document.

---

How To Run
------------------

1. Download the VeriFast binary for your device.
2. Open the vfide application.
3. Upload the file echo_verify.c file provided.
4. Run the code to model a server and client using VeriFast annotations.
   
---

Key Definitions
------------------

1. `struct buffer`:  
   A struct containing:
   - `char *data`: a pointer to dynamically allocated memory
   - `int size`: the length of the buffer

2. `fixpoint list<char> replicate(int n, char c)`:  
   A fixpoint function that builds a list of `n` repetitions of character `c`.  
   Used in annotations to describe the symbolic content of the buffer.

3. `predicate buffer(struct buffer *buf, int size, list<char> content)`:  
   A predicate expressing ownership of the buffer and its memory.  
   It ensures:
   - `buf` and its fields are allocated
   - `data` points to a valid character buffer of the given `size`
   - The contents match the symbolic list `content`

---

Verified Properties
----------------------

- **Memory Safety**:  
  The buffer is initialized correctly, with all memory explicitly allocated and freed.  
  No invalid accesses or overflows are possible.

- **Content Symbolism**:  
  The buffer contents are represented symbolically using `replicate(size, 0)`, and this is preserved across model function calls like `send` and `receive`.

- **Initialization Loop**:  
  A loop-based construction of the buffer contents (setting all bytes to 0) is fully annotated and verified with loop invariants.

---

Unfinished Work
------------------

- We did not verify actual socket-based I/O. From our understanding, VeriFast does not support reasoning about real message exchange or file descriptors since it can't necessarily view terminal output implement socket programming. We attempted to create a model to replicate our server and client implementation but were at a loss for how to verify the sent or recieved messages.
  
- Full message integrity (`send(client, msg) -> receive(server, msg)`) could not be proven beyond a symbolic model due to the above reason.

- We did not extend the model to support multiple clients or ordering guarantees due to time constraints like we had suggested in the proposal.

---

Final Remarks
----------------

While we could not verify a full echo server with real networking, we successfully modeled and verified an abstract model of the core idea: a memory-safe buffer capable of sending and receiving messages. To us, this aligned well enough with our goal to verify a server and client implementation for echo communication that we were satisfied with the progress we had made.

This project deepened our understanding of predicate-based reasoning, symbolic heaps, and the challenge of formally verifying real-world systems using tools like VeriFast. Initially, VeriFast was pretty challenging to understand due to the lack of documentation on it, especailly regarding socket programming. However, it provided great insight for us into the logic of what verifying an echo and server client could look like. With more time or more resources, we would hope to have been able to prove the server communication.
