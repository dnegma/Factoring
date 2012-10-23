UNAME := $(shell uname)

CC=g++
ifeq ($(UNAME), Darwin)
CC=clang++
endif
ifeq ($(UNAME), Linux)
CC=g++
endif


FLAGS= -Wall -g -pedantic -lgmpxx -lgmp -pg -Wno-variadic-macros

default: pollard_brent

pollard_new:
	$(CC) pollard_new.cc -o pollard_run $(FLAGS)

pollard_old:
	$(CC) pollard_old.cc -o pollard_run $(FLAGS)

pollard:
	$(CC) pollard.cc -o pollard_run $(FLAGS)

pollard_brent:
	$(CC) pollard_brent.cc -o pollard_run $(FLAGS)

quadratic:
	$(CC) quadratic.cc -o quadratic_run $(FLAGS)

test_output:
	$(CC) test_output.cc -o test_output.out $(FLAGS)

test: pollard_brent test_output
	ruby run_tests.rb n > test_output.txt
	./test_output.out

clean:
	rm -f *out *run
	rm -rf *dSYM
