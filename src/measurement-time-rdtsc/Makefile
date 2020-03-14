.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = g++
CC_OPTS = -std=c++11 -g -Wall -Wextra -Werror -lpthread

# Files

ALL_EX = measure-rdtsc measure-rdtscp-empty measure-rdtscp-yield

# Rules

all: $(ALL_EX)

clean:
	rm -f $(ALL_EX)

%: %.cc
	$(CC) $(CC_OPTS) -o $@ $<
