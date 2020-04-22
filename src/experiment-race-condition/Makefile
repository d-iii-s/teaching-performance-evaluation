.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = gcc
CC_OPTS = $(CFLAGS) -g -O0 -Wall -Wextra -Werror -lpthread

# Files

ALL_EX = possible-deadlock racing-variable-access

# Rules

all: $(ALL_EX)

clean:
	rm -f $(ALL_EX)

%: %.c
	$(CC) $(CC_OPTS) -o $@ $<
