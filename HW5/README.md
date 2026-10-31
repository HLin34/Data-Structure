# Homework 5 — Graph Traversal and Shortest Paths

Original C++ coursework for the Data Structures course at National Tsing Hua University.

## Programs

| Source | Implementation | Input / execution |
|---|---|---|
| [`HW5-1_109070025.cpp`](<HW5-1_109070025.cpp>) | Breadth-first search, depth-first search, components, DfnLow | Built-in graph examples |
| [`HW5-2_109070025.cpp`](<HW5-2_109070025.cpp>) | ShortestPath, BellmanFord, and AllLengths methods | Built-in weighted graph examples |

## Compilation

Compile each source individually because each contains its own program entry point. For example, from this directory:

```bash
g++ -std=gnu++17 -Wall -Wextra "HW5-1_109070025.cpp" -o homework_demo
./homework_demo
```

Replace the source filename to compile other examples. On Windows with MinGW, run `homework_demo.exe`.

## Supporting files

Original course reports are preserved in [`docs/`](docs/), with submission ZIP archives under [`docs/submissions/`](docs/submissions/).

Original headers: Graph.h, ShortestPath.h.

## Known limitations

The separate headers are kept alongside independent .cpp implementations. Algorithm names describe demonstrated functions, not exhaustive correctness guarantees.

> Compilation and basic smoke tests do not establish comprehensive correctness or memory safety. These are historical coursework implementations.
