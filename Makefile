CC=g++
FLAGS= -Wall -g -pedantic -lgmpxx -lgmp

default: test

test:
	$(CC) $(FLAGS) factor.cc -o run