# Computer Networks Lab

## 📘 Overview

This repository contains implementations of various computer networking concepts, focusing on socket programming, client-server architectures, and multithreading. The projects are designed to demonstrate practical applications of networking protocols and concurrency in C and Python.

---

## 🧪 Projects

### 🔹 Lab 1: Basic Client-Server Communication

- **Objective**: Establish a simple client-server communication using TCP sockets.
- **Languages**: C, Python
- **Key Concepts**:
  - Socket creation and binding
  - Listening for incoming connections
  - Handling client requests
  - Sending and receiving messages

### 🔹 Lab 2: Multithreaded Server with Client Simulation

- **Objective**: Implement a multithreaded server capable of handling multiple clients concurrently.
- **Languages**: C, Python
- **Key Concepts**:
  - Thread creation and management
  - Handling multiple client connections
  - Simulating multiple clients on a single machine
  - Synchronization and shared data management

---

## 🚀 Getting Started

### Prerequisites

- **C Compiler**: GCC
- **Python**: Version 3.x
- **Libraries**:
  - For C:
    - `pthread` library for multithreading
  - For Python:
    - `socket` library (standard in Python 3.x)

### Compilation and Execution

#### C Implementation

1. **Compile the server**:

   ```bash
   gcc server.c -o server -pthread
2. **Run Server**:
    ```bash
    ./server
3. **Compile the client**
    ```bash
    gcc client.c -o client
4. **Run the client:**
    ```bash
    ./client 1
    ./client 2
**Or simulate multiple clients in parallel:**
     ```bash
    seq 5 | xargs -n1 -P5 ./client

**Features**:
    -Multithreading: Servers can handle multiple clients simultaneously.

    -Client Simulation: Easily simulate multiple clients on a single machine.

    -Cross-language Implementation: Demonstrates socket programming concepts in both C and Python.

    -Modular design: Each lab exercise is self-contained and well-documented.

