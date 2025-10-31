# Change-Management-Software
## Overview
The Change Management System is a project developed in C that simulates how change requests can be tracked, prioritized, processed, and reverted.

It demonstrates the use of key Data Structures:
- Binary Search Tree (BST) for organizing and searching change requests.
- Priority Queue (Min Heap) for processing high-priority requests first.
- Stack for implementing an Undo feature.

This project shows how multiple data structures can work together in a practical system.

---

## Features

### 1. Add Change Request
Each request has an ID, title, priority, and status.  
It is added to both the BST (for ID-based search) and the Priority Queue (for priority-based processing), and also pushed onto the Stack for Undo operations.

### 2. Process Highest Priority Request
Dequeues the request with the lowest priority number (highest importance) from the Priority Queue.  
Updates its status in the BST to "Approved".

### 3. Search Request by ID
Searches the BST for a specific request using its unique ID.

### 4. Display All Requests
Displays all requests in sorted order (by ID) using In-Order Traversal of the BST.

### 5. Undo Last Added Request
Removes the most recently added change from the Stack and deletes it from both BST and Priority Queue.

---

## Data Structures Used

| Data Structure | Purpose | Key Operations |
|----------------|----------|----------------|
| Binary Search Tree (BST) | Organize and search requests by ID | Insert, Search, Delete, Inorder |
| Priority Queue (Min Heap) | Process requests by priority | Enqueue, Dequeue |
| Stack | Support Undo functionality | Push, Pop |

---

## Time Complexity

| Operation | Data Structure | Time Complexity |
|------------|----------------|-----------------|
| Insert Change | BST / PQ | O(log n) |
| Search Change | BST | O(log n) |
| Process Change | PQ | O(log n) |
| Undo Change | Stack | O(1) |
| Display All | BST | O(n) |

---

## How to Compile and Run

### Using GCC
```bash
gcc change_management.c -o change_mgmt
./change_mgmt
