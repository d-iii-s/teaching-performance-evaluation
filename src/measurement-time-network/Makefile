.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

PC = $(shell pkg-config --variable=prefix protobuf)/bin/protoc
PC_OPTS = --plugin=protoc-gen-grpc=$(shell pkg-config --variable=prefix grpc++)/bin/grpc_cpp_plugin
CC = g++
CC_OPTS = -std=c++20 $(shell pkg-config --cflags protobuf grpc++) -Wall -Wextra -Wno-unused-parameter -Werror
LD = g++
LD_OPTS = -std=c++20 $(shell pkg-config --libs protobuf grpc++)

# Files

ALL_EX = client server
ALL_OO = $(addsuffix .o, $(ALL_EX))
ALL_DD = $(addsuffix .dep, $(ALL_EX))

ALL_IF = clock
ALL_PB = $(addsuffix .pb.h, $(ALL_IF)) $(addsuffix .pb.cc, $(ALL_IF)) $(addsuffix .grpc.pb.h, $(ALL_IF)) $(addsuffix .grpc.pb.cc, $(ALL_IF))

# Rules

all: $(ALL_EX)

clean:
	rm -f *.o
	rm -f *.dep
	rm -f $(ALL_PB)
	rm -f $(ALL_EX)

client: client.o clock.pb.o clock.grpc.pb.o
	$(LD) $^ $(LD_OPTS) -o $@

server: server.o clock.pb.o clock.grpc.pb.o
	$(LD) $^ $(LD_OPTS) -o $@

client.cc: clock.pb.h clock.grpc.pb.h

server.cc: clock.pb.h clock.grpc.pb.h

%.o: %.cc
	$(CC) $(CC_OPTS) -c -o $@ $<

%.pb.h %.pb.cc %.grpc.pb.h %.grpc.pb.cc: %.proto
	$(PC) $(PC_OPTS) --cpp_out="." --grpc_out="." $<

# Deps

-include $(ALL_DD)

%.dep: %.cc
	$(CC) $(CC_OPTS) -MM -MT "$@ $(basename $@).o" -o $@ $<
