# Author: Andre D'Souza

# Variables of all object files
BIN = ./bin/
LIB = ./lib/
SRC = ./src/

# Code snippet referenced from https://stackoverflow.com/a/14061796
ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

# Override Default Variables
CC = gcc																	# Compiler
CFLAGS = -c -g -Wall -Wpedantic --std=gnu99 -Iinclude 	# C Compiler Flags

# Defualt Rule
all: simcpu.o heapPriorityQueue.o utilities.o
	$(CC) $(BIN)simcpu.o $(BIN)heapPriorityQueue.o $(BIN)utilities.o -o $(BIN)simcpu

simcpu.o:
	$(CC) $(CFLAGS) -c $(SRC)simcpu.c -o $(BIN)simcpu.o

heapPriorityQueue.o:
	$(CC) $(CFLAGS) -c $(SRC)heapPriorityQueue.c -o $(BIN)heapPriorityQueue.o

utilities.o:
	$(CC) $(CFLAGS) -c $(SRC)utilities.c -o $(BIN)utilities.o

# Cleaning Up All Artifacts
.PHONY: clean
clean:
	rm -f -r $(BIN)*

run:
	$(BIN)simcpu $(RUN_ARGS)

valgrind:
	valgrind --leak-check=yes $(BIN)simcpu $(RUN_ARGS)
