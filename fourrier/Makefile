BINARY=fourier
SOURCES= fourier.c main.c
CC=gcc
INCLUDES=.
LIBRARIES=

all:
	$(CC) -o $(BINARY) $(SOURCES) -I$(INCLUDES) $(LIBRARIES) -Wall -Wextra -lm

debug:
	$(CC) -g -o $(BINARY) $(SOURCES) -I$(INCLUDES) $(LIBRARIES)
	# gdb
	# exec-file ./test
	# run

profiler:
	$(CC) -pg -o $(BINARY) $(SOURCES) -I$(INCLUDES) $(LIBRARIES)
	# ./test
	# gprof test

run:
	./$(BINARY)
