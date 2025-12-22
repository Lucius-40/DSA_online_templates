# DSA-2 Templates Collection

This repository contains a comprehensive collection of Data Structures and Algorithms (DSA) templates, specifically focusing on graph algorithms and their implementations.

## 📁 Repository Structure

### Core Algorithm Templates

- **[GraphAlgorithms.h](GraphAlgorithms.h)** - Main header file containing clean, well-documented implementations of all graph algorithms with exact requirements and specifications
- **[dijkstra.cpp](dijkstra.cpp)** - Dijkstra's shortest path algorithm implementation
- **[bellman_ford.cpp](bellman_ford.cpp)** - Bellman-Ford algorithm for shortest paths with negative edges
- **[floyd_warshall.cpp](floyd_warshall.cpp)** - Floyd-Warshall all-pairs shortest path algorithm
- **[BFS.cpp](BFS.cpp)** - Breadth-First Search implementation
- **[DFS.cpp](DFS.cpp)** - Depth-First Search implementation
- **[topological_sort.cpp](topological_sort.cpp)** - Topological sorting algorithm
- **[BFS_in_grid.cpp](BFS_in_grid.cpp)** - BFS variant for grid-based problems *(Solution to an online problem in Moodle)*

### Problem-Specific Solutions

- **[2305159_p01.cpp](2305159_p01.cpp)** - Assignment problem solution
- **[2305159_p02.cpp](2305159_p02.cpp)** - Assignment problem solution (Bellman-Ford with negative cycle detection)
- **[leetcode.cpp](leetcode.cpp)** - LeetCode problem solution using modified Bellman-Ford
- **[Bp1.cpp](Bp1.cpp)** - Specific problem implementation

## 🎯 Purpose

The `.cpp` files in this repository are designed to be **modified versions** of standard algorithms, tailored for specific problem requirements. Each file demonstrates how to adapt core algorithms to solve particular types of problems.

### Key Features:
- **Template-based approach**: Easy to modify for different problem constraints
- **Problem-specific adaptations**: Shows real-world applications of theoretical algorithms
- **Educational focus**: Clear code structure for learning and reference

## 📖 Usage Guidelines

1. **For exact algorithm specifications and requirements**: Refer to **[GraphAlgorithms.h](GraphAlgorithms.h)**
2. **For problem-specific modifications**: Use the individual `.cpp` files as starting points
3. **For grid-based problems**: Check **[BFS_in_grid.cpp](BFS_in_grid.cpp)** for reference implementation

## 🧩 Algorithm Categories

### Shortest Path Algorithms
- Dijkstra's Algorithm (non-negative weights)
- Bellman-Ford Algorithm (handles negative weights)
- Floyd-Warshall Algorithm (all-pairs shortest paths)

### Graph Traversal
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Grid-based BFS

### Graph Analysis
- Topological Sorting
- Negative Cycle Detection

## 🔧 Compilation

Standard C++ compilation with C++17 or later:
```bash
g++ -std=c++17 -o output filename.cpp
```

## 📝 Notes

- All implementations use standard competitive programming practices
- Code includes common macros and optimizations
- Templates are designed for easy modification and adaptation
- The BFS_in_grid.cpp specifically solves an online problem from Moodle platform

## 🎓 Educational Value

This collection serves as:
- Reference templates for competitive programming
- Study material for graph algorithms
- Examples of algorithm adaptation for specific problems
- Practice problems and solutions

---
*For detailed algorithm specifications, complexity analysis, and exact requirements, always refer to [GraphAlgorithms.h](GraphAlgorithms.h)*