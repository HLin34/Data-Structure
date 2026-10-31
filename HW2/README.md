# Homework 2 — Linear Collections and Maze Traversal

Original C++ coursework for the Data Structures course at National Tsing Hua University.

## Programs

| Source | Implementation | Input / execution |
|---|---|---|
| [`HW2-1_109070025.cpp`](<HW2-1_109070025.cpp>) | Queue operations | Built-in demonstration data |
| [`HW2-2_109070025.cpp`](<HW2-2_109070025.cpp>) | Queue reversal and stack-related operations | Built-in demonstration data |
| [`HW2-3_109070025.cpp`](<HW2-3_109070025.cpp>) | Bag, stack, queue, and deque operations | Built-in demonstration data |
| [`HW2-4_109070025.cpp`](<HW2-4_109070025.cpp>) | Stack-based maze traversal | Requires maze.txt; run from HW2 directory |

## Compilation

Compile each source individually because each contains its own program entry point. For example, from this directory:

```bash
g++ -std=gnu++17 -Wall -Wextra "HW2-1_109070025.cpp" -o homework_demo
./homework_demo
```

Replace the source filename to compile other examples. On Windows with MinGW, run `homework_demo.exe`.

For the maze, run from `HW2/` so the program can read `maze.txt`:

```bash
g++ -std=gnu++17 -Wall -Wextra HW2-4_109070025.cpp -o maze
./maze
```

## Supporting files

Original course reports are preserved in [`docs/`](docs/), with submission ZIP archives under [`docs/submissions/`](docs/submissions/).

Original headers: ChangeSize1D.h, Queue_1.h, Stack_1.h.

## Known limitations

Queue_1.h refers to Stack.h, whereas the sibling file is Stack_1.h. This header is not directly included by the standalone programs. The maze uses variable-length arrays (a GNU C++ extension).

> Compilation and basic smoke tests do not establish comprehensive correctness or memory safety. These are historical coursework implementations.
