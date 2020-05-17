BINARY=esparsa
SOURCES= esparsa.c main.c
CC=gcc
INCLUDES=.
LIBRARIES= -lm

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
