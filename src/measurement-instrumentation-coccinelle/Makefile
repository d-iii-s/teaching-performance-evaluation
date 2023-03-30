.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

SP = spatch
SP_OPTS = -no-show-diff
CC = g++
CC_OPTS = $(CXXFLAGS) -std=c++11 -g -O3 -Wall -Wextra -Werror

# Files

ALL_PT = example.patched.c
ALL_EX = example.patched

# Rules

all: $(ALL_EX)

clean:
	rm -f $(ALL_PT)
	rm -f $(ALL_EX)


%.patched.c: %.c logging.cocci logging.h
	$(SP) $(SP_OPTS) logging.cocci $< -o $*.patched.c

%: %.c
	$(CC) $(CC_OPTS) -o $@ $<
