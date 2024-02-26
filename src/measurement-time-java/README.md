# Measuring Java Timers

The purpose of this example is to examine basic properties of the available timers in Java.
The example does that by collecting and then dumping a large number of consecutive time measurements, which can later be examined.

## Simple timer measurements

The `SimpleMillitime` and `SimpleNanotime` examples execute repeated calls to `currentTimeMillis` or `nanoTime` and print the results.
Worth trying with older versions of Java, on Linux Java 5 uses microsecond rather than nanosecond resolution in `nanoTime`.

```shell
/opt/java-1.5.0-*/bin/javac SimpleNanotime.java
/opt/java-1.5.0-*/bin/java SimpleNanotime
```

```text
index,time
...
1000,1489565833646609000
1001,1489565833646609000
1002,1489565833646609000
1003,1489565833646610000
1004,1489565833646610000
1005,1489565833646610000
...
```

A minimum plot in R:

```r
library ('tidyverse')
x <- read_csv ('<file>.csv')
ggplot (x, aes (x = index, y = time)) + geom_point ()
```

Note that importing data into R will convert large integer values to floats, possibly losing accuracy.
Remember that a standard double precision floating point number uses 53 bits to represent significant digits.
Decimal integers will therefore start losing accuracy during conversion when between 15 and 16 decimal digits long.

```r
old <- 1489565833646609000
new <- 1489565833646610000
new - old
```

```text
[1] 1024
```

## Relative timer measurements

To avoid the numerical accuracy issues, the `RelativeMillitime` and `RelativeNanotime` examples print the results
as deltas relative to the first measurement. A simple plot may reveal changes in sampling speed, a look at
differences between consecutive measurements may also hint at the timer resolution.

```r
library ('tidyverse')
x <- read_csv ('<file>.csv')
x <- x %>% mutate (delta = c (NA, diff (time)))
x %>% distinct (delta) %>% arrange (delta) %>% pull (delta)
```

```text
  [1]     23     24     25     26     27     28     29     30     31     32
 [11]     33     34     35     36     37     38     39     41     42     43
 [21]     44     45     46     47     48     49     50     51     52     53
...
```

## Trivia

Adding `-XX:+UnlockDiagnosticVMOptions` and `-XX:+PrintCompilation` and `-XX:+PrintAssembly` shows the runtime compilation activity.
The [hsdis plugin](https://blogs.oracle.com/javamagazine/post/java-hotspot-hsdis-disassembler) must be present otherwise the output is not complete.
