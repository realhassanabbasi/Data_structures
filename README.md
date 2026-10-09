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

## Complexity analysis

Every Big-O below was read off the actual code in this repo — not from a
textbook. `n` = number of elements, `d` = a node's number of children,
`h` = tree height, `L` = hash-bucket chain length. Space is extra space per
operation; each structure itself holds `O(n)` nodes (hash map: `O(n + buckets)`).

### Singly Linked List (`SinglyList.cpp`)

No tail pointer and no size counter are kept, so anything touching the end of
the list walks it.

| Operation | Time | Space | Notes |
|---|---|---|---|
| `emptyList` | O(1) | O(1) | — |
| `listSize` | O(n) | O(1) | counts by walking; no counter kept |
| `frontElement` | O(1) | O(1) | — |
| `lastElement` | O(n) | O(1) | walks to the end; no tail pointer |
| `countElement` | O(n) | O(1) | full scan |
| `head` / `tail` | O(1) / O(n) | O(1) | `tail()` walks; no tail pointer |
| `pushAtFront` | O(1) | O(1) | — |
| `pushAtEnd` | O(n) | O(1) | walks to the end (O(1) only on an empty list) |
| `popAtFront` | O(1) | O(1) | — |
| `popAtEnd` | O(n) | O(1) | must find the second-to-last node |
| `eraseElement` | O(n) | O(1) | single pass; a tail match calls `popAtEnd` at most once |
| `display` | O(n) | O(1) | — |
| destructor | O(n) | O(1) | frees node by node |

### Circular Linked List (`CircularList.cpp`)

Kept with a **tail pointer**, so the end of the list is always one hop away —
but there are no backward links.

| Operation | Time | Space | Notes |
|---|---|---|---|
| `emptyList` | O(1) | O(1) | — |
| `listSize` | O(n) | O(1) | no counter kept |
| `frontElement` | O(1) | O(1) | `tail->next()` |
| `lastElement` | O(1) | O(1) | `tail` |
| `pushAtFront` | O(1) | O(1) | — |
| `pushAtEnd` | O(1) | O(1) | push at front, then advance `tail` |
| `popAtFront` | O(1) | O(1) | — |
| `popAtEnd` | O(n) | O(1) | walks to the node before `tail`; no backward links |
| `eraseElement` | O(n) | O(1) | single pass; at most one O(n) `popAtEnd` |
| `display` | O(n) | O(1) | — |
| destructor | O(n) | O(1) | `n` × O(1) `popAtFront` |

### Doubly Linked List (`doublyList.cpp`)

Nodes carry `previous` links, but **no tail pointer is kept** — so the
`previous` links save bookkeeping, not the walk to the end.

| Operation | Time | Space | Notes |
|---|---|---|---|
| `emptyList` | O(1) | O(1) | — |
| `listSize` | O(n) | O(1) | no counter kept |
| `frontElement` | O(1) | O(1) | — |
| `lastElement` | O(n) | O(1) | still walks; no tail pointer |
| `countElement` | O(n) | O(1) | full scan |
| `head` | O(1) | O(1) | — |
| `pushAtFront` | O(1) | O(1) | — |
| `pushAtEnd` | O(n) | O(1) | walks to the end despite the `previous` links |
| `popAtFront` | O(1) | O(1) | — |
| `popAtEnd` | O(n) | O(1) | walks to the end; `previous` only unlinks cheaply |
| `eraseElement` | O(n) | O(1) | one pass; middle splice is O(1), at most one tail `popAtEnd` |
| `display` | O(n) | O(1) | — |
| destructor | O(n) | O(1) | frees node by node |

### Stack — `StackList` (linked-list backed, `Stack.cpp`)

| Operation | Time | Space | Notes |
|---|---|---|---|
| `emptyStack` | O(1) | O(1) | — |
| `top` | O(1) | O(1) | reads the head node |
| `pop` | O(1) | O(1) | pops the head node |
| `push` | O(1) | O(1) | pushes at the head |

### Stack — `StackArray` (dynamic array, `Stack.cpp`)

| Operation | Time | Space | Notes |
|---|---|---|---|
| `emptyStack` / `top` / `pop` | O(1) | O(1) | direct index math |
| `push` | O(1) amortized | O(1) | O(n) on the pushes that trigger growth |
| `doubleCapacity` | O(n) | O(n) | copies all elements into a 2× array |

Array holds `O(capacity)` slots (capacity stays between `n` and `2n`). It only
grows — `pop` never shrinks it. Construct with capacity ≥ 1.

### Queue — `Queue` (linked-list backed, `queues.cpp`)

| Operation | Time | Space | Notes |
|---|---|---|---|
| `emptyQueue` / `top` | O(1) | O(1) | — |
| `pop` | O(1) | O(1) | pops the head |
| `push` | **O(n)** | O(1) | delegates to `pushAtEnd`, which walks — enqueue is the slow op here because no tail pointer is kept |

### Queue — `QueueArray` (circular buffer, `queues.cpp`)

| Operation | Time | Space | Notes |
|---|---|---|---|
| `emptyQueue` / `frontE` | O(1) | O(1) | — |
| `push` | O(1) | O(1) | modulo index math; no shifting |
| `pop` | O(1) | O(1) | modulo index math |
| `traverse` | O(n) | O(1) | — |

Fixed capacity — there is no auto-grow. Pushing into a full queue throws.

### General Tree — `SimpleTree` (`AbstractTree.cpp`)

Children live in a plain list with **no child counter and no tail pointer**,
so child bookkeeping is linear in the degree.

| Operation | Time | Space | Notes |
|---|---|---|---|
| `retrieve` / `parent` / `isRoot` | O(1) | O(1) | — |
| `degree` | O(d) | O(1) | counts children by walking; no counter |
| `isLeaf` | O(d) | O(1) | calls `degree()` |
| `child(n)` | O(d) | O(1) | bounds check walks (`degree()`), then an index walk |
| `insertNode` | O(d) | O(1) | appends via `pushAtEnd` walk |
| `attach` | O(d) | O(1) | detach from old parent + append |
| `detach` | O(d) | O(1) | `eraseElement` on the parent's child list |
| `sizee` | O(n) | O(h) stack | visits every node once |
| `height` | O(n) | O(h) stack | visits every node once |
| `depth_first_traversal` | O(n) | O(h) stack | — |

`sizee`, `height`, and the traversal are recursive: call-stack depth is the
tree height `h` — a degenerate chain-shaped tree uses O(n) stack.

### Hash Map (`HashMap.cpp`)

Separate chaining; auto-rehash at load factor 0.75 keeps chains short.

| Operation | Time | Space | Notes |
|---|---|---|---|
| `insert` | O(1) average, O(n) worst | O(1) | worst case = all keys colliding into one bucket; rehash itself is O(n) |
| `get` / `contains` | O(1) average, O(n) worst | O(1) | chain walk, bounded by `L` |
| `remove` | O(1) average, O(n) worst | O(1) | chain walk, bounded by `L` |
| `rehash` | O(n) average | O(n) | doubles the table, reinserts every node; prints a line to stdout |
| `size` | O(1) | O(1) | counter kept |
| `display` | O(n + buckets) | O(1) | visits every bucket and node |
| destructor | O(n + buckets) | O(1) | — |

"Average" assumes a decent hash spread — real speed follows `std::hash`.

## Edge cases covered

The test suite (`tests/test_all.cpp`, 137 checks, all green) verifies these
edge cases, not just the happy path:

- **Empty structures:** pop/top/front/erase on an empty list, stack, or queue
  throw instead of crashing; erase on an empty circular list prints and leaves
  it empty.
- **Single-element lists:** pop from front and back on one-node lists
  (singly, circular, doubly).
- **Missing values/keys:** erasing an absent value leaves the list untouched;
  hash `get`/`contains`/`remove` on a missing key return false (double-remove
  also returns false).
- **Rehash survival:** 50 inserts into a 4-bucket table — every key is still
  retrievable afterward; re-inserting an existing key updates the value without
  growing the table.
- **Buffer wrap-around:** the circular-buffer queue wraps its indices and keeps
  FIFO order; pushing into a full queue throws.
- **Array-stack growth:** a capacity-2 stack is forced to double twice and all
  values survive, in order.
- **Tree surgery:** `detach` turns a node into a root; re-attaching under a
  new parent updates size/height; out-of-range `child(n)` returns `nullptr`.
- **Link integrity:** doubly-linked `previous` pointers verified across the
  whole list, including after pops; the circular list drains in true ring
  order after mixed push/pop.
