.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = g++
CC_OPTS = $(CXXFLAGS) -std=c++11 -Wall -Wextra -Werror -lpapi

# Files

ALL_EX = list-counters papi-counters native-counters multiplexed-counters measure-cycle-frequency measure-clock-overheads list-counters
ALL_O0 = $(addsuffix -o0, $(ALL_EX))
ALL_O1 = $(addsuffix -o1, $(ALL_EX))
ALL_O2 = $(addsuffix -o2, $(ALL_EX))
ALL_O3 = $(addsuffix -o3, $(ALL_EX))
ALL = $(ALL_O0) $(ALL_O1) $(ALL_O2) $(ALL_O3)

# Rules

all: $(ALL)

clean:
	rm -f $(ALL)

%-o0: %.cc
	$(CC) -O0 $(CC_OPTS) -o $@ $<

%-o1: %.cc
	$(CC) -O1 $(CC_OPTS) -o $@ $<

%-o2: %.cc
	$(CC) -O2 $(CC_OPTS) -o $@ $<

%-o3: %.cc
	$(CC) -O3 $(CC_OPTS) -o $@ $<
