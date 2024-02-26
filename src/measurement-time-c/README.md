# Measuring C Timers

The purpose of this example is to examine basic properties of the available timers in Java.
The example does that by collecting and then dumping a large number of consecutive time measurements, which can later be examined.

## Running the example

```shell
make
./measure-std-chrono
./measure-clock-gettime
```

The measurements are relative to the first sample to avoid numerical precision errors.

```text
index,time
...
1000,22600
1001,22610
1002,22630
1003,22650
1004,22670
1005,22690
...
```

A minimum plot in R:

```r
library ('tidyverse')
x <- read_csv ('<file>.csv')
ggplot (x, aes (x = index, y = time)) + geom_point ()
```
