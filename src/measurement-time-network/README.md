# Measuring Network Timers

The purpose of this example is to demonstrate issues with passing time measurements across networks.
The example collects `CLOCK_MONOTONIC_RAW` measurements on a local and a remote machine
and dumps the results.

## Running the example

Run the client and the server on two different machines.
The example may require opening the server firewall:

```shell
nft add rule inet main input tcp dport 8888 accept
```

```shell
make
./server
```

```shell
make
./client <server>:8888
```

The measurements are relative to the first sample to avoid numerical precision errors.

```text
index,local,remote
...
1000,89745265,85191632
1001,89827906,85279322
1002,89921626,85364932
1003,90000076,85451762
1004,90095426,85541212
1005,90176246,85629552
...
```

A minimum plot in R:

```r
library ('tidyverse')
x <- read_csv ('<file>.csv')
ggplot (x, aes (x = index, y = local - remote)) + geom_point ()
```
