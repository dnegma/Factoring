UNAME := $(shell uname)

CC=g++
ifeq ($(UNAME), Darwin)
CC=clang++
endif
ifeq ($(UNAME), Linux)
CC=g++
endif


FLAGS= -Wall -g -pedantic -lgmpxx -lgmp -pg

default: pollard

pollard:
	$(CC) pollard_brent.cc -o pollard_run $(FLAGS)

quadratic:
	$(CC) quadratic.cc -o quadratic_run $(FLAGS)

clean:
	rm -f a.out *run
	rm -rf *dSYM
