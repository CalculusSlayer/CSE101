// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA4
//  Sparse.c
//  This file contains the main program that does different matrix operations.
// -----------------------------------------------------------------------------
#include "Matrix.h"

int main(int argc, char *argv[]) {
    FILE *infile = NULL;
    FILE *outfile = NULL;

   if( argc != 3 ){
      fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   infile = fopen(argv[1], "r");
      if( infile==NULL ){
      fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   outfile = fopen(argv[2], "w");
   if( outfile==NULL ){
      fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   int n, a, b;
   fscanf(infile, "%i %i %i", &n, &a, &b);

   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);

    int row, col;
    double val;
   for (int i = 0; i < a; i++) {
       fscanf(infile, "%i %i %lf", &row, &col, &val);
       changeEntry(A, row, col, val);
   }

    for (int i = 0; i < b; i++) {
       fscanf(infile, "%i %i %lf", &row, &col, &val);
       changeEntry(B, row, col, val);
   }

   fprintf(outfile, "A has %i non-zero entries:\n", NNZ(A));
   printMatrix(outfile, A);
    fprintf(outfile, "\n");

    fprintf(outfile, "B has %i non-zero entries:\n", NNZ(B));
    printMatrix(outfile, B);
    fprintf(outfile, "\n");  

    fprintf(outfile, "(1.5)*A =\n");
    Matrix C = scalarMult(1.5, A);
    printMatrix(outfile, C);
    fprintf(outfile, "\n"); 

    fprintf(outfile, "A+B =\n");
    Matrix D = sum(A, B);
    printMatrix(outfile, D);
    fprintf(outfile, "\n"); 

    fprintf(outfile, "A+A =\n");
    Matrix E = sum(A, A);
    printMatrix(outfile, E);
    fprintf(outfile, "\n"); 

    fprintf(outfile, "B-A =\n");
    Matrix F = diff(B, A);
    printMatrix(outfile, F);
    fprintf(outfile, "\n"); 

    fprintf(outfile, "A-A =\n");
    Matrix G = diff(A, A);
    printMatrix(outfile, G);
    fprintf(outfile, "\n"); 

    fprintf(outfile, "Transpose(A) =\n");
    Matrix H = transpose(A);
    printMatrix(outfile, H);
    fprintf(outfile, "\n"); 

    fprintf(outfile, "A*B =\n");
    Matrix I = product(A, B);
    printMatrix(outfile, I);
    fprintf(outfile, "\n"); 

    fprintf(outfile, "B*B =\n");
    Matrix J = product(B, B);
    printMatrix(outfile, J);
    fprintf(outfile, "\n"); 

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);

    fclose(infile);
    fclose(outfile);

   
    return 0;
}