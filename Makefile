CC=clang++
FLAGS= -Wall -g -pedantic -lgmpxx -lgmp

default: test

test:
	$(CC) pollard.cc -o pollard_run $(FLAGS)

clean:
	rm a.out *run
	rm -r a.out* run*
