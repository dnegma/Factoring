UNAME := $(shell uname)

CC=g++
ifeq ($(UNAME), Darwin)
CC=clang++
endif
ifeq ($(UNAME), Linux)
CC=g++
endif


FLAGS= -Wall -g -pedantic -lgmpxx -lgmp -pg

default: pollard_brent

pollard_old:
	$(CC) pollard_old.cc -o pollard_run $(FLAGS)

pollard:
	$(CC) pollard.cc -o pollard_run $(FLAGS)

pollard_brent:
	$(CC) pollard_brent.cc -o pollard_run $(FLAGS)

quadratic:
	$(CC) quadratic.cc -o quadratic_run $(FLAGS)

clean:
	rm -f a.out *run
	rm -rf *dSYM
