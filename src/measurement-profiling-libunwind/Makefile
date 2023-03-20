.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = gcc
CC_OPTS = $(CFLAGS) -g -Wall -Wextra -Werror
CC_OPTS_LOCAL = $(CC_OPTS) $(shell pkg-config --cflags libunwind)
CC_OPTS_REMOTE = $(CC_OPTS) $(shell pkg-config --cflags libunwind-ptrace)
LD_OPTS =
LD_OPTS_LOCAL = $(CC_OPTS) $(shell pkg-config --libs libunwind)
LD_OPTS_REMOTE = $(CC_OPTS) $(shell pkg-config --libs libunwind-ptrace)


# Files

ALL_EX = local-stack-trace-no-opt local-stack-trace-opt remote-stack-trace

# Rules

all: $(ALL_EX)

clean:
	rm -f $(ALL_EX)

local-%-opt: local-%.c
	$(CC) $(CC_OPTS_LOCAL) -O3 -o $@ $< $(LD_OPTS_LOCAL)

local-%-no-opt: local-%.c
	$(CC) $(CC_OPTS_LOCAL) -O0 -o $@ $< $(LD_OPTS_LOCAL)

remote-%: remote-%.c
	$(CC) $(CC_OPTS_REMOTE) -O3 -o $@ $< $(LD_OPTS_REMOTE)
