# Homework 1 — Polynomial, Sparse Matrix, and String Implementations

Original C++ coursework for the Data Structures course at National Tsing Hua University.

## Programs

| Source | Implementation | Input / execution |
|---|---|---|
| [`HW1-1_109070025.cpp`](<HW1-1_109070025.cpp>) | Polynomial representation, addition, multiplication, evaluation | Interactive: iteration count, polynomials, evaluation value |
| [`HW1-2_109070025.cpp`](<HW1-2_109070025.cpp>) | Sparse matrix addition, multiplication, fast transpose | Interactive: iteration count and matrix input |
| [`HW1-3_109070025.cpp`](<HW1-3_109070025.cpp>) | Custom string comparison, length, pattern matching | Built-in demonstration data |

## Compilation

Compile each source individually because each contains its own program entry point. For example, from this directory:

```bash
g++ -std=gnu++17 -Wall -Wextra "HW1-1_109070025.cpp" -o homework_demo
./homework_demo
```

Replace the source filename to compile other examples. On Windows with MinGW, run `homework_demo.exe`.

## Supporting files

Original course reports are preserved in [`docs/`](docs/), with submission ZIP archives under [`docs/submissions/`](docs/submissions/).

Original headers: None.

## Known limitations

HW1-1 and HW1-2 explicitly invoke destructors on automatic objects. HW1-3 uses raw-pointer storage. Memory-safety and edge-case validation remain incomplete.

> Compilation and basic smoke tests do not establish comprehensive correctness or memory safety. These are historical coursework implementations.
