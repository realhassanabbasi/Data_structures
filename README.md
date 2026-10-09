# Data Structures in C++

A collection of classic data structures implemented from scratch in C++, written
while studying 3rd-semester Data Structures (BS Artificial Intelligence) at
**Air University Islamabad** by Hassan Abbasi.

Every implementation is written without STL containers, so the internals —
nodes, pointers, memory management — are all visible and easy to study.

## What's inside

| File | Data structure | What it does |
|---|---|---|
| `SinglyList.cpp` | Singly Linked List | Integer-based linked list with push/pop at front and end, erase by value, size and count helpers, and a full 11-case test harness in `main()` covering empty-list errors and head/tail/middle deletion. |
| `CircularList.cpp` | Circular Linked List | Template-based circular list kept with a tail pointer; supports push/pop at front and end, element erase, display, and automatic cleanup in the destructor. |
| `doublyList.cpp` | Doubly Linked List | Template-based list whose nodes carry both `next` and `previous` pointers; push/pop at front and end plus erase-by-value with two-way traversal. |
| `Stack.cpp` | Stack (two versions) | `StackList` — a stack built on a template linked list — and `StackArray` — a stack on a fixed-capacity dynamic array; both provide push, pop, top, and empty checks with underflow protection. |
| `queues.cpp` | Queue (two versions) | `Queue` — a linked-list FIFO queue — and `QueueArray` — a circular-buffer queue using wrap-around indices so enqueue/dequeue stay O(1); includes a traverse display. |
| `AbstractTree.cpp` | General Tree | `SimpleTree` — a template tree where nodes keep a list of children; supports attach/detach of subtrees, root and leaf checks, degree, size, height, and child access, with a demo `main()` that builds and queries a small tree. |
| `HashMap.cpp` | Hash Map | Template hash table with separate chaining (linked lists per bucket); auto-rehashes when the load factor passes 0.75; insert/update, get, contains, and remove; the demo `main()` shows collisions, rehashing in action, and a real word-frequency counter. |

## Requirements

- A C++ compiler with C++11 support (g++ 7 or newer).
- No external libraries — only the C++ standard library is used.

On Windows, install [MinGW-w64](https://www.mingw-w64.org/) and use `g++` from the terminal.

## Compile & run

Each file is self-contained and compiles on its own:

```bash
g++ SinglyList.cpp -o singlylist
./singlylist
```

```bash
g++ AbstractTree.cpp -o tree
./tree
```

```bash
g++ Stack.cpp -o stack
./stack
```

```bash
g++ queues.cpp -o queue
./queue
```

```bash
g++ CircularList.cpp -o circularlist
./circularlist
```

```bash
g++ doublyList.cpp -o doublylist
./doublylist
```

```bash
g++ HashMap.cpp -o hashmap
./hashmap
```

On Windows (PowerShell / cmd), run the produced `.exe` instead of `./name`:

```bash
g++ Stack.cpp -o stack.exe
stack.exe
```

## What I learned

- How nodes and pointers actually work — allocating, linking, and deleting memory by hand.
- The difference between `O(1)` operations (push at front) and `O(n)` ones (push at end without a tail pointer).
- Why a tail pointer makes circular lists clean, and how a circular array buffer keeps a queue fast without relinking nodes.
- Exception safety basics: throwing on underflow instead of silently returning garbage.
- That the same ADT (stack, queue) can sit on two very different backings — a linked list or an array — and the trade-offs of each.
- How hashing buys near-O(1) lookups, and why a 0.75 load factor with rehashing keeps the table fast even when keys collide.

## Testing

Every structure in this repo is covered by one assertion-based test driver —
137 checks across normal operations, edge cases (empty pops, missing erases,
rehash boundaries), and structural integrity (backward links, ring order).

```bash
g++ -std=c++11 -Wall -Wextra tests/test_all.cpp -o tests/test_all
./tests/test_all
```

A green run ends with `==== RESULT: 137 passed, 0 failed ====` and exits with
code `0` (non-zero on failure, so it works in CI). See
[`tests/README.md`](tests/README.md) for details.
