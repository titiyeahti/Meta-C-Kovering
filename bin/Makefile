CC=gcc
SRC=../src/
INCLUDES=-lm
OPT=-O3
FLAGS=-ansi -Wall -Wextra -g $(OPT)
OBJ=file-handler.o graph.o queue.o problem.o algo.o

all: test-graph.out test-problem.out test-file-handler.out test-greedy.out

test-%.out : $(SRC)test-%.c $(OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $^ -o $@

test-ind.out : $(SRC)test-ind.c $(SRC)indicator.h
	$(CC) $(FLAGS) $(INCLUDES) $< -o $@

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDES)

clean :
	rm -rf *.o *.out 


