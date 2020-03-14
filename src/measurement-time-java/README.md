# Measuring Java Timers

## Simple timer measurements

* SimpleMillitime
* SimpleNanotime

Execute repeated calls to `currentTimeMillis` or `nanoTime` and print results.
Worth trying with older versions of Java, on Linux Java 5 uses microsecond
rather than nanosecond resolution in `nanoTime`.

```shell
/opt/java-1.5.0-*/bin/javac SimpleNanotime.java
/opt/java-1.5.0-*/bin/java SimpleNanotime.java
```

```text
1489565833646609000
1489565833646609000
1489565833646609000
1489565833646610000
1489565833646610000
1489565833646610000
...
```

When importing data into R, long integer values are converted to floats, possibly losing accuracy.

```r
old <- 1489565833646609000
new <- 1489565833646610000
new - old
```

```text
[1] 1024
```

## Relative timer measurements

* RelativeMillitime
* RelativeNanotime

Provided to avoid accuracy issues when importing data into R.
A simple plot sometimes reveals changes in sampling speed
when JIT optimizes the measurement loop.

```r
data <- scan ('<file>.txt')
plot (data)
...
```

This may or may not reveal minimum timer resolution.
With current hardware and compilers it usually does.

```r
data <- scan ('<file>.txt')
step <- diff (data)
sort (unique (step))
```

```text
  [1]     23     24     25     26     27     28     29     30     31     32
 [11]     33     34     35     36     37     38     39     41     42     43
 [21]     44     45     46     47     48     49     50     51     52     53
...
```
