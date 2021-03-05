# Measuring Sleep Functions

Sleep functions are essential for generating timed benchmark workloads,
where the workload generator approximates for example realistic
network traffic or realistic users.

The examples measure the actual time interval elapsed between calling and returning from various sleep functions.

## Running the example

```shell
make
./sleep-short-simple > sleep-short-simple.csv
./sleep-short-random > sleep-short-random.csv
./sleep-long-random > sleep-long-random.csv
javac Sleep.java
java Sleep > sleep.csv
```

A minimum plot in R:

```r
library ('tidyverse')
data <- read_csv ('<file>.csv')
ggplot (data, aes (x = sleep, y = time)) + geom_point () + geom_abline (intercept = 0, slope = 1, linetype = 'dotted')
```

Note the difference between `sleep-short-simple` and `sleep-short-random`.
When return from sleep is synchronized with scheduler quantum,
next call of sleep is synchronized too unless random delay
is inserted. Such synchronization may impact results.
