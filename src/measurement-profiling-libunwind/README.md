# Collecting Stack Traces

The example demonstrates how the `libunwind` library can be used to walk the stack of an application.

## Implementations

The example implements four functions, `function_0` to `function_3`, which call each other randomly
to build a stack of given depth. Once this depth is reached, the innermost function calls the
`print_stack` function to walk the stack.

Building the example with tail call optimization enabled shows how the stack can be squashed.

## Running the example

```shell
make
./local-stack-trace-no-opt
./local-stack-trace-opt
```

Note how a sampling based profiler would report the squashed stack
while an instrumentation based profiler would report the true call tree.

```shell
CFLAGS=-pg make clean all
./stack-trace-opt
gprof ./stack-trace-opt
```
