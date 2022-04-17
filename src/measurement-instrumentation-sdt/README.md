# Instrumented Eratosthenes Prime Sieve Experiment

This is a version of the prime sieve experiment instrumented with static user mode probes.

## Running the example

Use `make` to build the binary.

Using the user mode probes with `perf`:

```shell
perf buildid-cache --add ./checked-basic
perf probe --cache --list "sdt_primes:*"
perf probe sdt_primes:found
...
```

Using the user mode probes with `bpftrace`:

```shell
bpftrace -e 'usdt:./checked-basic:found { printf ("Prime %d\n", arg0); }'
...
```
