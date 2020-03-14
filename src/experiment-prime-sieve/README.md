# Eratosthenes Prime Sieve Experiment

The purpose of the example is to provide multiple implementations of the Eratosthenes Prime Sieve
that differ in the applied optimizations. The exercise is to analyze the impact of the optimizations.

## Implementations

The `basic` and `smart` implementations serve to define the range of implementations considered in the experiment.
The `basic` implementation translates the sieve algorithm directly into code with no regard for efficiency.
The `smart` implementation includes reasonable optimizations that already make the code less easy to read.

The other implementations use two optimizations that trade sieve element access complexity against memory traffic.
The `bitmap` variants store the sieve in an array of bits rather than an array of bytes.
The `checked` variants avoid redundant updates of the sieve elements.

## Running the example

Do not forget to disable frequency scaling for reasonable measurement !
On processors without boosting `cpupower frequency-set --governor performance` suffices.

```shell
make
time ./basic
time ./checked-basic
time ./bitmap
time ./checked-bitmap
time ./smart
time ./checked-smart
```
