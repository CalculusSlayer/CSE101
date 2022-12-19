# #------------------------------------------------------------------------------
# #  Nayeel Imtiaz, naimtiaz
# #  2022 Spring CSE101 PA4
# #  Makefile
# #  Makefile for CSE 101 Programming Assignment 4
# #
# #  make                     makes Sparse, MatrixTest, and ListTest
# #  make Sparse              makes Sparse
# #  make MatrixTest          makes MatrixTest
# #  make ListTest            makes ListTest
# #  make clean               removes all binaries and object files
# #  make SparseCheck         runs Sparse in valgrind on an input file
# #  make MatrixCheck         runs MatrixTest in valgrind
# #  make ListCheck           runs ListTest in valgrind
# #------------------------------------------------------------------------------

all: Sparse ListTest MatrixTest

Sparse : Sparse.o Matrix.o List.o
	gcc -std=c17 -Wall -o Sparse Sparse.o Matrix.o List.o

Sparse.o : Sparse.c Matrix.h List.h
	gcc -std=c17 -Wall -c Sparse.c

ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o

ListTest.o: ListTest.c List.h
	gcc -std=c17 -Wall -c ListTest.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

MatrixTest: MatrixTest.o Matrix.o List.o 
	gcc -std=c17 -Wall -o MatrixTest MatrixTest.o Matrix.o List.o

MatrixTest.o: MatrixTest.c Matrix.h List.h
	gcc -std=c17 -Wall -c MatrixTest.c

Matrix.o: Matrix.c Matrix.h List.h
	gcc -std=c17 -Wall -c Matrix.c

clean :
	rm -f *.o ListTest MatrixTest Sparse