# Using Hardware Performance Counters with PAPI

These are just simple code snippets that illustrate various PAPI functions.

## Implementations

The `papi-counters` code measures PAPI events.
The `native-counters` code measures native events.
The `multiplexed-counters` code enables multiplexing.

The `measure-clock-overheads` code attempts to measure the overhead of the `clock_gettime` call in several ways.
The `measure-cycle-frequency` code attempts to measure how many processor clock cycles fit in one second.
Both are meant as case studies to discuss potential measurement pitfalls.

## Running the example

The examples are compiled multiple times with various optimization levels.

```shell
make
./papi-counters-o0
./papi-counters-o1
./papi-counters-o2
./papi-counters-o3
./native-counters-o0
...
```

Note the variance in the measurement results.
