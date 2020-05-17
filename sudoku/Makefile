BINARY= sudoku
SOURCES= sudoku.c main.c
CC=gcc
INCLUDES=.
LIBRARIES= -Wall -Wextra

all:
	$(CC) -o $(BINARY) $(SOURCES) -I$(INCLUDES) $(LIBRARIES) 
teste:
	$(CC) -o teste sudoku.c teste.c -I$(INCLUDES) $(LIBRARIES) 

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
runt:
	./teste
