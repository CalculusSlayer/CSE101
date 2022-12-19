#-----------------------------------------------------------------------------
# Nayeel Imtiaz, naimtiaz
# 2022 Spring CSE101 PA1
# Makefile
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex and ListTest
# make Lex               makes Lex
# make ListTest          makes ListTest
# make clean             removes all binaries
# make checkTest         checks ListTest for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------
all: Lex ListTest

Lex : Lex.o List.o
	gcc -std=c17 -Wall -o Lex Lex.o List.o -g

Lex.o : Lex.c List.h
	gcc -std=c17 -Wall -c Lex.c -g

ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o -g

ListTest.o: ListTest.c List.h
	gcc -std=c17 -Wall -c ListTest.c -g

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c -g 

clean :
	rm -f Lex ListTest Lex.o ListTest.o List.o

checkTest : 
	valgrind --leak-check=full ListTest

checkLex :
	valgrind --leak-check=full Lex in3 blah3