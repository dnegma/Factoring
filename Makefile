CC=clang++
FLAGS= -Wall -g -pedantic -lgmpxx -lgmp

default: pollard

pollard:
	$(CC) pollard.cc -o pollard_run $(FLAGS)

quadratic:
	$(CC) quadratic.cc -o quadratic_run $(FLAGS)

clean:
	rm -f a.out *run
	rm -rf *dSYM
