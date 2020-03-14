# Measuring RDTSC Timer

## Running the example

```shell
make
./measure-rdtsc > measure-rdtsc.csv
./measure-rdtscp-empty > measure-rdtscp-empty.csv
./measure-rdtscp-yield > measure-rdtscp-yield.csv
```

A minimum plot in R for the `RDTSC` version:

```r
library ('tidyverse')
data <- read_csv ('<file>.csv')
ggplot (data, aes (x = index, y = time)) + geom_point ()
```

A minimum plot in R for the `RDTSCP` versions:

```r
library ('tidyverse')
data <- read_csv ('<file>.csv')
ggplot (data, aes (x = index, y = time, color = factor (magic))) + geom_point ()
```

It is also useful to look at difference between neighboring samples:

```r
library ('tidyverse')
data <- read_csv ('<file>.csv')
data <- data %>% mutate (step = c (NA, diff (time)))
step_size <- median (data $ step, na.rm = TRUE) * 3
ggplot (data, aes (x = step)) + geom_histogram (bins = 128) + lims (x = c (0, step_size))
```
