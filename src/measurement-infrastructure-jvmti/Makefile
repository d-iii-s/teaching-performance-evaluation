.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = g++
CC_OPTS = -std=c++11 -O2 -g -Wall -Wextra -Werror -Wno-unused-parameter -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -fPIC -shared -lpthread -lrt

# Files

ALL_EX = libheaplivesize.so libvmallocations.so

# Rules

all: $(ALL_EX)

clean:
	rm -f $(ALL_EX)

%.so: %.cc
	$(CC) $(CC_OPTS) -o $@ $<
