#------------------------------------------------------------------------------
#  Nayeel Imtiaz, naimtiaz
#  2022 Spring CSE101 PA6
#  Makefile
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                 makes Arimetic, BigIntegerTest, and ListTest
#  make Arithmetic      makes Arithmetic
#  make BigIntegerTest  makes BigIntegerTest
#  make ListTest        makes ListTest
#  make clean           removes binary files and object files
#  make check1          runs valgrind on ListTest
#  make check2          runs valgrind on BigIntegerTest
#  make check3          runs valgrind on all input and output files for Arithmetic
#------------------------------------------------------------------------------

all : Arithmetic BigIntegerTest ListTest

Arithmetic : Arithmetic.o BigInteger.o List.o
	g++ -std=c++17 -Wall -o Arithmetic Arithmetic.o BigInteger.o List.o -g

Arithmetic.o : List.h BigInteger.h Arithmetic.cpp
	g++ -std=c++17 -Wall -c Arithmetic.cpp -g

BigIntegerTest : BigIntegerTest.o BigInteger.o List.o
	g++ -std=c++17 -Wall -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o -g

BigIntegerTest.o : List.h BigInteger.h BigIntegerTest.cpp
	g++ -std=c++17 -Wall -c BigIntegerTest.cpp -g

BigInteger.o : List.h BigInteger.h BigInteger.cpp
	g++ -std=c++17 -Wall -c BigInteger.cpp -g

ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -o ListTest ListTest.o List.o -g

ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -c ListTest.cpp -g

List.o : List.h List.cpp
	g++ -std=c++17 -Wall -c List.cpp -g

clean :
	rm -f *.o ListTest BigIntegerTest Arithmetic

check1 : ListTest
	valgrind --leak-check=full ListTest

check2 : BigIntegerTest
	valgrind --leak-check=full BigIntegerTest

check3 : Arithmetic
	valgrind --leak-check=full Arithmetic in1 out1