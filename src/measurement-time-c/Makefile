.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = g++
CC_OPTS = -std=c++20 -g -Ofast -Wall -Wextra -Werror

# Files

ALL_EX = measure-clock-gettime measure-std-chrono

# Rules

all: $(ALL_EX)

clean:
	rm -f $(ALL_EX)

%: %.cc
	$(CC) $(CC_OPTS) -o $@ $<
