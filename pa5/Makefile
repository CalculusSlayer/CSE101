#------------------------------------------------------------------------------
#  Nayeel Imtiaz, naimtiaz
#  2022 Spring CSE101 PA5
#  Makefile
#  Makefile for CSE 101 Programming Assignment 5
#
#  make                makes Shuffle and ListTest
#  make Shuffle        makes Shuffle
#  make ListTest       make ListTest
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

all : Shuffle ListTest

Shuffle : Shuffle.o List.o
	g++ -std=c++17 -Wall -o Shuffle Shuffle.o List.o -g

Shuffle.o : List.h Shuffle.cpp
	g++ -std=c++17 -Wall -c Shuffle.cpp -g

ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -o ListTest ListTest.o List.o -g

ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -c ListTest.cpp -g

# ListClient : ListClient.o List.o
# 	g++ -std=c++17 -Wall -o ListClient ListClient.o List.o -g

# ListClient.o : List.h ListClient.cpp
# 	g++ -std=c++17 -Wall -c ListClient.cpp -g

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -c List.cpp -g

clean :
	rm -f *.o Shuffle ListTest

check1 : ListTest
	valgrind --leak-check=full ListTest

check2 : Shuffle
	valgrind --leak-check=full Shuffle 35