# Homework 3 — Linked Lists, Polynomials, and Sparse Matrices

Original C++ coursework for the Data Structures course at National Tsing Hua University.

## Programs

| Source | Implementation | Input / execution |
|---|---|---|
| [`HW3-1_109070025.cpp`](<HW3-1_109070025.cpp>) | Singly linked chain operations | Built-in demonstration data |
| [`HW3-2(1)_109070025.cpp`](<HW3-2(1)_109070025.cpp>) | Circular linked list operations | Built-in demonstration data |
| [`HW3-2(2)_109070025.cpp`](<HW3-2(2)_109070025.cpp>) | Header linked list operations | Built-in demonstration data |
| [`HW3-3_109070025.cpp`](<HW3-3_109070025.cpp>) | List manipulation and traversal | Built-in demonstration data |
| [`HW3-4_109070025.cpp`](<HW3-4_109070025.cpp>) | Linked polynomial operations | Interactive polynomial terms |
| [`HW3-5_109070025.cpp`](<HW3-5_109070025.cpp>) | Linked sparse matrix operations | Interactive matrix data |

## Compilation

Compile each source individually because each contains its own program entry point. For example, from this directory:

```bash
g++ -std=gnu++17 -Wall -Wextra "HW3-1_109070025.cpp" -o homework_demo
./homework_demo
```

Replace the source filename to compile other examples. On Windows with MinGW, run `homework_demo.exe`.

## Supporting files

Original course reports are preserved in [`docs/`](docs/), with submission ZIP archives under [`docs/submissions/`](docs/submissions/).

Original headers: Chain.h, CircularList.h, HeaderList.h, List.h, Polynomial.h, Queue.h, SparseMatrix.h, Stack.h.

## Known limitations

Queue.h and Stack.h include List.h. The standalone .cpp files implement their own classes. HW3-2(1) includes a small empty-list destructor guard. HW3-3 has a warning concerning a reference to a local variable.

> Compilation and basic smoke tests do not establish comprehensive correctness or memory safety. These are historical coursework implementations.
