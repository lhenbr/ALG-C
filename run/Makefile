BINARY=run_length
SOURCES=run_length.c run_length.h main.c
CC=gcc
INCLUDES=.
LIBRARIES=

all:
	$(CC) -o $(BINARY) $(SOURCES) -I$(INCLUDES) $(LIBRARIES)

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
