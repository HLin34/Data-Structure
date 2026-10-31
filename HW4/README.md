# Homework 4 — Binary Trees, Heaps, and Binary Search Trees

Original C++ coursework for the Data Structures course at National Tsing Hua University.

## Programs

| Source | Implementation | Input / execution |
|---|---|---|
| [`HW4-1_109070025.cpp`](<HW4-1_109070025.cpp>) | Binary tree operations and traversals | Built-in demonstration data |
| [`HW4-2_109070025.cpp`](<HW4-2_109070025.cpp>) | Heap and priority-queue operations | Built-in demonstration data |
| [`HW4-3_109070025.cpp`](<HW4-3_109070025.cpp>) | Binary search tree dictionary operations | Built-in demonstration data |

## Compilation

Compile each source individually because each contains its own program entry point. For example, from this directory:

```bash
g++ -std=gnu++17 -Wall -Wextra "HW4-1_109070025.cpp" -o homework_demo
./homework_demo
```

Replace the source filename to compile other examples. On Windows with MinGW, run `homework_demo.exe`.

## Supporting files

Original course reports are preserved in [`docs/`](docs/), with submission ZIP archives under [`docs/submissions/`](docs/submissions/).

Original headers: BST.h, ChangeSize1D (1).h.

## Known limitations

The accompanying headers are retained as coursework references; the standalone programs do not directly include them. HW4-1 retains compiler warnings.

> Compilation and basic smoke tests do not establish comprehensive correctness or memory safety. These are historical coursework implementations.
