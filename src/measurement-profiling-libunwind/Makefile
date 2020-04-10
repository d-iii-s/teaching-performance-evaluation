.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = gcc
CC_OPTS = $(CFLAGS) -g -Wall -Wextra -Werror -lunwind

# Files

ALL_EX = stack-trace-no-opt stack-trace-opt

# Rules

all: $(ALL_EX)

clean:
	rm -f $(ALL_EX)

%-opt: %.c
	$(CC) $(CC_OPTS) -O3 -o $@ $<

%-no-opt: %.c
	$(CC) $(CC_OPTS) -O0 -o $@ $<
