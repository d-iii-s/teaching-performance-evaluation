.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = g++
CC_OPTS = -std=c++11 -g -O3 -Wall -Wextra -Werror

# Files

ALL_EX = basic checked-basic bitmap checked-bitmap smart checked-smart

# Rules

all: $(ALL_EX)

clean:
	rm -f $(ALL_EX)

%: %.cc
	$(CC) $(CC_OPTS) -o $@ $<
