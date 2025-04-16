.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = gcc
CC_OPTS = $(CFLAGS) -g -O0 -Wall -Wextra -Werror -Wno-return-local-addr -Wno-free-nonheap-object -Wno-use-after-free

# Files

ALL_EX = double-free-heap invalid-free-stack leak-heap use-after-free-heap use-after-free-stack write-past-end-heap

# Rules

all: $(ALL_EX)

clean:
	rm -f $(ALL_EX)

%: %.c
	$(CC) $(CC_OPTS) -o $@ $<
