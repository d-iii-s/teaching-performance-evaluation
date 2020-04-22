# Race Condition

The example implements multiple race condition patterns, used to demonstrate
how various race condition detection tools work. The name of each executable
describes the race condition pattern.

## Analyzing the example

Before running the individual executables, state what you think should happen.

## Running the example

With no error checking:

```shell
make
./possible-deadlock
./racing-variable-access
```

With `valgrind` `helgrind` tool:

```shell
make
valgrind ./possible-deadlock
valgrind ./racing-variable-access
```
