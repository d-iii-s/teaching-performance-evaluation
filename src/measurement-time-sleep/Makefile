.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = g++
CC_OPTS = -std=c++11 -g -Wall -Wextra -Werror

# Files

ALL_EX = sleep-short-simple sleep-short-random sleep-long-random

# Rules

all: $(ALL_EX)

clean:
	rm -f $(ALL_EX)

%: %.cc
	$(CC) $(CC_OPTS) -o $@ $<
