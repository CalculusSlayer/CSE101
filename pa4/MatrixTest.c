// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA4
//  MatrixTest.c
//  This file contains test cases for the Matrix ADT.
// -----------------------------------------------------------------------------

#include "Matrix.h"

int main(void) {
    Matrix a = newMatrix(10);
    fprintf(stdout, "size of matrix 'a' is %i\n", size(a));
    fprintf(stdout, "number of nonzero entries in matrix 'a' is %i\n", NNZ(a));
    printMatrix(stdout, a);

    for (int i = 1; i <= size(a); i++) {
        for (int j = 1; j <= size(a); j++) {
            changeEntry(a, i, j, 69);
        }
    }

    fprintf(stdout, "size of matrix 'a' is %i\n", size(a));
    fprintf(stdout, "number of nonzero entries in matrix 'a' is %i\n", NNZ(a));
    printMatrix(stdout, a);

    Matrix b = newMatrix(10);
    for (int i = 1; i <= size(a); i++) {
        for (int j = 1; j <= size(a); j++) {
            changeEntry(b, i, j, 42);
        }
    }

    fprintf(stdout, "size of matrix 'b' is %i\n", size(b));
    fprintf(stdout, "number of nonzero entries in matrix 'b' is %i\n", NNZ(b));
    printMatrix(stdout, b);

    if (equals(a, b)) {
        fprintf(stdout,"a and b are equal\n");
    }
    else {
        fprintf(stdout, "a and b are NOT equal\n");
    }

    Matrix c = scalarMult(3, a);
    printMatrix(stdout, c);

    Matrix d = newMatrix(2);
    changeEntry(d, 1, 1, 1);
    changeEntry(d, 1, 2, 2);
    changeEntry(d, 2, 1, 3);
    changeEntry(d, 2, 2, 4);
    printMatrix(stdout, d);

    fprintf(stdout, "Copy Test!\n");
    Matrix e = copy(d);
    printMatrix(stdout, e);

    Matrix a1 = sum(a, a);
    printMatrix(stdout, a1);
    fprintf(stdout, "number of nonz: %i\n", NNZ(a1));

    changeEntry(b, 1, 1, -69);
    Matrix a2 = sum(a, b);
    printMatrix(stdout, a2);
    fprintf(stdout, "number of nons: %i\n", NNZ(a2));

    fprintf(stdout, "Transpose Test!\n");
    Matrix f = transpose(d);
    printMatrix(stdout, f);

    fprintf(stdout, "jsdflkajdslkfj\n");
    Matrix A = newMatrix(10);
    changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);
    Matrix z1 = sum(A, A);
    // if (NNZ(*pC) != 4 || NNZ(A) != 4)
    //   return 1;
    fprintf(stdout, "%i\n", NNZ(z1));
    printMatrix(stdout, z1);

    Matrix B = newMatrix(10);
    changeEntry(B, 1, 1, -4);
    changeEntry(B, 1, 2, 0);
    changeEntry(B, 2, 1, 0);
    changeEntry(B, 2, 2, -2);
    changeEntry(B, 2, 4, 2);
    changeEntry(B, 3, 1, 0);
    changeEntry(B, 3, 2, 2);
    changeEntry(B, 7, 8, 5);
    Matrix z2 = sum(A, B);
    // if (NNZ(*pD) != 5)
    //   return 2;
    // return 0;
    fprintf(stdout, "\n\n");
    printMatrix(stdout, z2);
    fprintf(stdout, "%i\n", NNZ(z2));

    freeMatrix(&a);
    freeMatrix(&b);
    freeMatrix(&c);
    freeMatrix(&d);
    freeMatrix(&e);
    freeMatrix(&f);
    freeMatrix(&z1);
    freeMatrix(&z2);
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&a1);
    freeMatrix(&a2);

    // DEBUG difference
    A = newMatrix(10);
    B = newMatrix(10);
    changeEntry(A, 1, 1, -4);
    changeEntry(A, 1, 2, -2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 5, 4);
    changeEntry(A, 2, 1, -2);
    changeEntry(A, 3, 1, 2);
    changeEntry(A, 2, 2, -2);
    changeEntry(A, 3, 3, 0);
    Matrix C = sum(A, A);
    printMatrix(stdout, C);
    fprintf(stdout, "%i\n", NNZ(C));

    changeEntry(B, 1, 1, -4);
    changeEntry(B, 1, 2, 0);
    changeEntry(B, 2, 1, 0);
    changeEntry(B, 2, 2, -2);
    changeEntry(B, 2, 4, 2);
    changeEntry(B, 3, 1, 2);
    changeEntry(B, 3, 2, 2);
    changeEntry(B, 7, 8, 5);

    // changeEntry(B, 2, 3, -9);
    //     changeEntry(B, 2, 1, -9);
    //         changeEntry(B, 2, 5, -9);
    //             changeEntry(B, 2, 7, -9);
    //                 changeEntry(B, 2, 6, -9);




    Matrix D = sum(A, B);
    printMatrix(stdout, D);
    fprintf(stdout, "%i\n", NNZ(D));
    fprintf(stdout, "\n\n");

    makeZero(A);

    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 5);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 5); // ???
    changeEntry(A, 1, 1, 4);
    changeEntry(A, 2, 2, 2); // ???
    changeEntry(A, 2, 5, 0);
    changeEntry(A, 2, 3, 0);
    changeEntry(A, 3, 3, 5); // ???
    // 7

    printMatrix(stdout, A);
    fprintf(stdout, "%i\n", NNZ(A));

    changeEntry(A, 1, 3, 0);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 3, 3, 0);

    // 4
    printMatrix(stdout, A);
    fprintf(stdout, "%i\n", NNZ(A));
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    return 0;
}