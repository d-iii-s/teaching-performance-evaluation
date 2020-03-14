# Naive Alternative Selection Experiment

The purpose of the example is to demonstrate how a naive alternative selection experiment can provide misleading results.
The example defines a hypothetical library interface `BenchIface` and two implementations of that interface,
classes `BenchImpl1` and `BenchImpl2`. Without looking at the two implementations,
the experiment should determine which class executes faster.

## Running the example

```shell
javac *.java
java <class>
```

There are multiple experiment implementations, each can run separately, each with some quirks:

- `Main_01_Straightforward` as a naive solution that still gives some results.
- `Main_02_With_Functions` as a solution that separates the measurement code in two separate functions with direct calls.
- `Main_03_With_Interfaces` as a solution that separates the measurement code in one function with call through interface.
- `Main_04_Raw_Printing` prints the results in a CSV friendly format that can be imported into R.
- `Main_05_Long_Iterator` uses `long` rather than `int` in case more iterations are needed.
- `Main_06_With_Local_Warmup` executes warm up iterations before each measurement.
- `Main_07_With_Global_Warmup` executes warm up iterations before both measurements.

A minimum plot in R with CSV header `count,time,version`:

```r
library ('tidyverse')
x <- read_csv ('<file>.csv')
ggplot (x, aes (x = count, y = time, color = version)) + geom_point ()
```
