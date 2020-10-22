CC=gcc
SRC=../src/
INCLUDES=
FLAGS=-ansi -Wall -Wextra -g
OPT=-O3

all: 

test-ind.out : $(SRC)test-ind.c $(SRC)indicator.h
	$(CC) $(FLAGS) $(INCLUDES) $< -o $@

test-file-handler.out : file-handler.o $(SRC)test-file-handler.c
	$(CC) $^ -o $@ $(FLAGS) $(INCLUDES)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDES)

clean :
	rm -rf *.o *.out 


