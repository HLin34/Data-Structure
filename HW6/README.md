# Homework 6 — Sorting and Symbol Tables

Original C++ coursework for the Data Structures course at National Tsing Hua University.

## Programs

| Source | Implementation | Input / execution |
|---|---|---|
| [`HW6-1_109070025.cpp`](<HW6-1_109070025.cpp>) | QuickSort, recursive merge sort, iterative merge sort | Built-in arrays |
| [`HW6-2_109070025.cpp`](<HW6-2_109070025.cpp>) | Symbol-table insert, search, display | Built-in string examples |

## Compilation

Compile each source individually because each contains its own program entry point. For example, from this directory:

```bash
g++ -std=gnu++17 -Wall -Wextra "HW6-1_109070025.cpp" -o homework_demo
./homework_demo
```

Replace the source filename to compile other examples. On Windows with MinGW, run `homework_demo.exe`.

## Supporting files

Original course reports are preserved in [`docs/`](docs/), with submission ZIP archives under [`docs/submissions/`](docs/submissions/).

Original headers: None.

## Known limitations

HW6-1 includes a minimal QuickSort boundary correction and corrects the demonstration start index. Other edge cases have not been exhaustively tested.

> Compilation and basic smoke tests do not establish comprehensive correctness or memory safety. These are historical coursework implementations.
