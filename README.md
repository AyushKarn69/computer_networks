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

---

### 🔹 Lab 2: Multithreaded Server with Client Simulation

- **Objective**: Implement a multithreaded server capable of handling multiple clients concurrently.
- **Languages**: C, Python
- **Key Concepts**:
  - Thread creation and management
  - Handling multiple client connections
  - Simulating multiple clients on a single machine
  - Synchronization and shared data management

---

### 🔹 Lab 3: Webserver (Socket Programming in C)

- **Objective**: Build a simple **web server in C** that responds to HTTP requests from a TCP client (browser) by serving an HTML file (`index.html`).
- **Languages**: C
- **Key Concepts**:
  - Creating a TCP socket
  - Binding and listening on a port (e.g., `8080`)
  - Accepting client (browser) connections
  - Parsing HTTP request headers
  - Sending HTTP response headers and serving `index.html`
  - Inspecting request/response packets using **Wireshark**

- **Steps**:
  1. Create an HTML file named `index.html` to serve.
  2. Implement `webserver.c` to handle socket communication:
     - Wait for HTTP GET requests.
     - Send back HTTP 200 OK header + contents of `index.html`.
  3. Compile and run the server:
     ```bash
     gcc webserver.c -o webserver
     ```
  4. **Run Server**:
     ```bash
     ./webserver
     ```
  5. Open a browser and visit:
     ```
     http://localhost:8080
     ```
     You should see the contents of `index.html`.
  6. Use **Wireshark** to capture and analyze the packets:
     - Observe **TCP three-way handshake**.
     - Inspect **HTTP GET request** sent by the browser.
     - Inspect **HTTP response** with HTML content sent by the server.

- **Features**:
  - Serves static HTML pages.
  - Simple HTTP header handling.
  - Demonstrates how a browser communicates with a TCP server.

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

---

### Compilation and Execution

#### C Implementation

1. **Compile the server**:
   ```bash
   gcc server.c -o server -pthread
1. **Compile the server**:
   ```bash
   ./server

1. **Compile the server**:
   ```bash
   gcc client.c -o client
1. **Compile the server**:
   ```bash
   ./client 1
   ./client 2

#### Features Across Labs

- Multithreading: Servers can handle multiple clients simultaneously.
- Client Simulation: Easily simulate multiple clients on a single machine.
- Cross-language Implementation: Demonstrates socket programming concepts in both C and Python.
- Webserver Implementation: Serve real HTML files via TCP sockets and analyze traffic using Wireshark.
- Modular Design: Each lab exercise is self-contained and well-documented.
