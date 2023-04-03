# Manipulating Binaries with PIN

The example demonstrates how the PIN dynamic binary instrumentation tool can be used to instrument native binaries.

## Running the example

Possibly adjust the `PIN_ROOT` variable in `Makefile` and then use `make` to build the instrumentation libraries.

Use the libraries with `pin`:

```shell
/opt/pin/pin -t obj-intel64/routine-call-count.so -logfile routine-call-count.txt -- ls
/opt/pin/pin -t obj-intel64/system-call-dump.so -logfile system-call-dump.txt -- ls
```
