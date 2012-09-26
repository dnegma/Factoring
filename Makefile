CC=g++
FLAGS= -Wall -g -pedantic -lgmpxx -lgmp

default: test

test:
	$(CC) factor.cc -o run $(FLAGS)
