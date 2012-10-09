CC=g++
FLAGS= -Wall -g -pedantic -lgmpxx -lgmp -pg

default: pollard

pollard:
	$(CC) pollard_brent.cc -o pollard_run $(FLAGS)

quadratic:
	$(CC) quadratic.cc -o quadratic_run $(FLAGS)

clean:
	rm -f a.out *run
	rm -rf *dSYM
