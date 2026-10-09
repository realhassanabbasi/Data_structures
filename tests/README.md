# Tests

One assertion-based test driver covering every data structure in this repo:
singly linked list, circular list, doubly linked list, both stack variants,
both queue variants, the general tree, and the hash map.

## Run them

From the repo root:

```bash
g++ -std=c++11 -Wall -Wextra tests/test_all.cpp -o tests/test_all
./tests/test_all
```

On Windows (PowerShell / cmd), run `tests\test_all.exe` instead of `./tests/test_all`.

A green run ends with:

```
==== RESULT: 137 passed, 0 failed ====
```

The driver exits with code `0` when everything passes and `1` otherwise, so it
works in CI too.

## What the tests check

- **Normal operations** — push/pop at both ends, insert/get/remove, attach/detach,
  enqueue/dequeue in FIFO order.
- **Edge cases** — popping or reading from an empty structure (must throw
  `"underflow"`), erasing a missing value (list stays intact), single-element
  lists, and the hash map's rehash boundary (50 inserts into a 4-bucket table —
  every key must survive growth).
- **Structural integrity** — backward links in the doubly linked list, ring order
  in the circular list and circular-buffer queue.

## How it works

`test_all.cpp` is dependency-free — just a hand-rolled `CHECK` macro, no test
framework. Each implementation from the repo root is included verbatim (minus
its own `main()` demo) inside its own namespace, so the whole suite compiles as
a single file.

Note: the implementations print a little as they run (`Element not found`,
`[rehash] table grew to N buckets`) — that output comes from the structures
themselves, not from the test harness.
