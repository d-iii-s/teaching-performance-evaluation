# Memory Corruption

The example implements multiple memory corruption patterns, used to demonstrate
how various memory corruption detection tools work. The name of each executable
describes the memory corruption pattern.

## Analyzing the example

Before running the individual executables, state what you think should happen.
Each of the memory corruption patterns has the potential to crash the program,
but only some do here. Consider for how long the failure can remain
undetected, and whether the failure can even be silently remedied.

## Running the example

With no error checking:

```shell
make
./double-free-heap
./invalid-free-stack
./leak-heap
./use-after-free-heap
./use-after-free-stack
./write-past-end-heap
```

With error checking `malloc`:

```shell
make
MALLOC_CHECK_=3 ./double-free-heap
MALLOC_CHECK_=3 ./invalid-free-stack
MALLOC_CHECK_=3 ./leak-heap
MALLOC_CHECK_=3 ./use-after-free-heap
MALLOC_CHECK_=3 ./use-after-free-stack
MALLOC_CHECK_=3 ./write-past-end-heap
```

With `valgrind` `memcheck` tool:

```shell
make
valgrind ./double-free-heap
valgrind ./invalid-free-stack
valgrind ./leak-heap
valgrind ./use-after-free-heap
valgrind ./use-after-free-stack
valgrind ./write-past-end-heap
```
