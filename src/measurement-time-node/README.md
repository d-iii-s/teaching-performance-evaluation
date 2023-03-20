# Measuring Node.js Timers

The purpose of this example is to examine basic properties of the available timers in Node.js.
The example does that by collecting and then dumping a large number of consecutive time measurements, which can later be examined.

## Running the example

The `date.js` example prints the time as reported by the `Date.now` method.
The `performance.js` example prints the time as reported by the `performance.now` method.

```shell
node date.js
node performance.js
```

The `difference.js` example prints the difference between the two time sources.

```shell
node difference.js
```

A minimum plot in R:

```r
library ('tidyverse')
x <- read_csv ('<file>.csv')
ggplot (x, aes (x = index, y = time)) + geom_point ()
```

## Trivia

Note that the precision provided by `Performance.now ()`
may depend on script site properties, see the documentation
for [`crossOriginIsolated`](https://developer.mozilla.org/en-US/docs/Web/API/crossOriginIsolated).
