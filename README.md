# Data Structures and Algorithms — C++ Coursework

C++ implementations created for the **Data Structures** course at **National Tsing Hua University (NTHU)**. This repository preserves the original coursework implementations of fundamental data structures and algorithms, with documentation and limited fixes for reproducible execution.

## Assignments

| Homework | Topics | Programs | Documentation |
|---|---|---:|---|
| HW1 | Polynomials, sparse matrices, custom strings | 3 | [HW1](HW1/README.md) |
| HW2 | Queues, stacks, deques, maze traversal | 4 | [HW2](HW2/README.md) |
| HW3 | Linked lists, linked polynomials, sparse matrices | 6 | [HW3](HW3/README.md) |
| HW4 | Binary trees, heaps, binary search trees | 3 | [HW4](HW4/README.md) |
| HW5 | Graph traversal, components, shortest paths | 2 | [HW5](HW5/README.md) |
| HW6 | QuickSort, merge sort, symbol tables | 2 | [HW6](HW6/README.md) |

## Repository structure

Each `HW1/`–`HW6/` directory contains independent `.cpp` implementations, any original supporting `.h` files, its own `README.md`, and a `docs/` folder for the original reports. Original submission archives are preserved in `docs/submissions/`. `HW2/maze.txt` is an input fixture.

## Build and run

**Requirements:** GCC or Clang with GNU C++17 support. The 20 independent programs were compiled with GCC 14.2.0 during repository review; this does **not** establish complete runtime correctness or memory safety.

Compile each source separately (several define their own `main()`):

```bash
cd HW5
g++ -std=gnu++17 -Wall -Wextra HW5-1_109070025.cpp -o hw5_graph
./hw5_graph
```

On Windows with MinGW, run `hw5_graph.exe`. For the maze program, compile and run from `HW2/` because it reads `maze.txt` relative to the working directory. Some programs require interactive input; consult each assignment README and the original documents.

## Preservation and review notes

These are **historical educational implementations**, not production-ready libraries. Original algorithms, class designs, and filenames are preserved. Limited fixes for `HW2-4` (portable maze input), `HW3-2(1)` (empty circular-list destructor), and `HW6-1` (QuickSort demonstration and bounds) have been included. Original DOCX/PDF reports and submission archives remain available in `docs/`; generated `.exe` and `.o` files were removed.

**Known limitations:** Some programs retain compiler warnings and manual memory management. `HW2/Queue_1.h` refers to `Stack.h` although the corresponding file is named `Stack_1.h`. Input-dependent examples and edge cases have not been exhaustively validated. See per-homework READMEs for details.

## Attribution and license

Coursework by the repository author, completed at NTHU. No open-source license is specified.
