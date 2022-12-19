// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA4
//  Matrix.c
//  This file contains functions of the Matrix ADT.
// -----------------------------------------------------------------------------
#include "Matrix.h"

// pointer to EntryObj
typedef struct EntryObj *Entry;

// private entryObj object
typedef struct EntryObj {
    double val;
    int column;
} EntryObj;

// private matrixObj object
typedef struct MatrixObj {
    List *rows;
    int size;
    int nonzero;
} MatrixObj;

// newEntry: makes a new entry.
// Pre: none
Entry newEntry(double val, int column) {
    Entry x = malloc(sizeof(EntryObj));
    x->val = val;
    x->column = column;

    return x;
}

// freeEntry: frees an entry.
// Pre: entry cannot be null object.
void freeEntry(Entry *pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

// newMatrix: makes a new matrix.
// Pre: n > 0
Matrix newMatrix(int n) {
    if (n <= 0) {
        fprintf(stderr, "CANNOT HAVE A MATRIX WITH 0 ROWS!\n");
        exit(1);
    }
    Matrix M = malloc(sizeof(MatrixObj));

    M->rows = malloc((n+1) * sizeof(List));
    for (int i = 1; i <= n; i++) {
        (M->rows)[i] = newList();
    }

    M->size = n;
    M->nonzero = 0;

    return M;

}

// freeMatrix: frees the matrix.
// pre: matrix cannot be null.
void freeMatrix(Matrix* pM) {
    if (pM && *pM) {
        makeZero(*pM);
        for (int i = 1; i <= size(*pM); i++) {
            freeList(&((*pM)->rows[i]));
            (*pM)->rows[i] = NULL;
        }
        free((*pM)->rows);
        (*pM)->rows = NULL;
        free(*pM);
        *pM = NULL;
    }
}

// size: returns size of matrix.
// Pre: M is not null.
int size(Matrix M) {
    if (M != NULL) {
        return M->size;
    }
    else {
        fprintf(stderr, "MATRIX IS NULL!!!\n");
        exit(1);
    }
}

// NNZ: return number of nonzeros in Matrix
// M cannot be NULL.
int NNZ(Matrix M) {
    if (M != NULL) {
        return M->nonzero;
    }
    else {
        fprintf(stderr, "MATRIX IS NULL!!!\n");
        exit(1);
    }
}

// equals: Returns 1 or 0 depending on whether the
// two matrices are equal or not.
// Pre: Matrix A and Matrix B have to not be NULL.
int equals(Matrix A, Matrix B) {
    if (!A || !B) {
        fprintf(stderr, "MATRIX A OR MATRIX B IS NULL!!!\n");
        exit(1);
    }
    if (size(A) != size(B)) {
        return 0;
    }

    if (A == B) {
        return 1;
    }

    for (int i = 1; i <= size(A); i++) {
        if (length((A->rows)[i]) != length((B->rows)[i])) {
            return 0;
        }
        moveFront((A->rows)[i]);
        moveFront((B->rows)[i]);
        while(index((A->rows)[i]) >= 0) {
            Entry A1 = (Entry) get((A->rows)[i]);
            Entry B1 = (Entry) get((B->rows)[i]);
            if (A1->val != B1->val) {
                return 0;
            }
            moveNext((A->rows)[i]);
            moveNext((B->rows)[i]);

        }
    }
    
    return 1;
}

// makeZero: clears all the entries in Matrix.
// Pre: M cannot be NULL
void makeZero(Matrix M) {
    if (M) {
        for (int count = 1; count <= size(M); count++) {
            while(length((M->rows)[count]) > 0) {
                moveFront((M->rows)[count]);
                Entry e1 = (Entry) get((M->rows)[count]);
                freeEntry(&e1);
                deleteFront((M->rows)[count]);
                
            }
        }
        M->nonzero = 0;
    }

}

// changeEntry: changes the entry at specific row and column.
// Pre: i and j has to be within a certain range. M != null.
void changeEntry(Matrix M, int i, int j, double x) {
    // if (length((M->rows)[i]) == 0) {
    //     if (x != 0) {
            
    //     }
    //     //append((M->rows)[i], 
    // }
    if (M && 1 <= i  && i <= size(M) && 1 <= j && j <= size(M)) {
        moveFront((M->rows)[i]);
        bool inside = false;
        bool reach_null = false;
        while (true) {
            if (index(M->rows[i]) < 0) {
                reach_null = true;
                break;
            }

            Entry e1 = (Entry) get((M->rows)[i]);

            if (e1->column == j) {
                inside = true;
                if (x == 0) {
                    freeEntry(&e1);
                    delete((M->rows)[i]);
                    M->nonzero -= 1;
                }
                else {
                    e1->val = x;
                }
                break;
            }
            else if (e1->column > j) {
                break;
            }

            moveNext((M->rows)[i]);
        }

        if (!inside && x!=0) {
            Entry e1 = newEntry(x, j);
            if (length(M->rows[i]) == 0 || reach_null) {
                append(M->rows[i], e1);
            }
            else {
                insertBefore((M->rows)[i], e1);
            }
            M->nonzero += 1;
        }
    }
}

// copy: make copy of matrix and return it.
// Pre: A != null
Matrix copy(Matrix A) {
    if (!A) {
        fprintf(stderr, "MATRIX A IS NULL!!!\n");
        exit(1);
    }

    Matrix M = newMatrix(size(A));

    for (int i = 1; i <= size(A); i++) {
        moveFront((A->rows)[i]);
        while(index((A->rows)[i]) >= 0) {
            Entry M1 = (Entry) get((A->rows)[i]);
            Entry e1 = newEntry(M1->val, M1->column);

            append((M->rows)[i], e1);
            M->nonzero += 1;
            moveNext((A->rows)[i]);

        }
    }

    M->nonzero = A->nonzero;

    return M;

}

// transpose: Return transpose of matrix.
// Pre: A != NULL
Matrix transpose(Matrix A) {
    if (!A) {
        fprintf(stderr, "MATRIX A IS NULL!!!\n");
        exit(1);
    }

    Matrix M = newMatrix(size(A));

    for (int i = 1; i <= size(A); i++) {
        moveFront((A->rows)[i]);
        while(index((A->rows)[i]) >= 0) {
            Entry M1 = (Entry) get((A->rows)[i]);
            Entry e1 = newEntry(M1->val, i);

            append((M->rows)[M1->column], e1);
            M->nonzero += 1;
            moveNext((A->rows)[i]);

        }
    }

    M->nonzero = A->nonzero;

    return M;
}

// scalarMult: returns new matrix multiplied by certain float.
// Pre: A!= NULL
Matrix scalarMult(double x, Matrix A) {
    if (!A) {
        fprintf(stderr, "MATRIX A IS NULL!!!\n");
        exit(1);
    }

    Matrix M = newMatrix(size(A));

    for (int i = 1; i <= size(A); i++) {
        moveFront((A->rows)[i]);
        while(index((A->rows)[i]) >= 0) {
            Entry M1 = (Entry) get((A->rows)[i]);
            Entry e1 = newEntry(x * M1->val, M1->column);

            append((M->rows)[i], e1);
            M->nonzero += 1;
            moveNext((A->rows)[i]);

        }
    }

    return M;

}

// sum: returns sum of A and B
// Pre: A and B are not NULL
Matrix sum(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "ERROR!!! Matrices are not the same size.\n");
        exit(1);
    }

    //Matrix B2 = copy(B);
    if (equals(A, B)) {
        Matrix S = scalarMult(2, A);
        return S;
    }

    Matrix C = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        while(index(A->rows[i]) >= 0 && index(B->rows[i]) >= 0) {
            Entry a1 = (Entry) get(A->rows[i]);
            Entry b1 = (Entry) get(B->rows[i]);

            if (a1->column == b1->column) {
                double sum1 = a1->val + b1->val;
                if (sum1 != 0) {
                    Entry e3_s = newEntry(sum1, a1->column);
                    append(C->rows[i], e3_s);
                    C->nonzero += 1;
                }
                moveNext(A->rows[i]);
                moveNext(B->rows[i]);
            }

            else if (a1->column < b1->column) {
                Entry e1 = newEntry(a1->val, a1->column);
                append(C->rows[i], e1);
                C->nonzero += 1;
                moveNext(A->rows[i]);
            }

            else {
                Entry e2 = newEntry(b1->val, b1->column);
                append(C->rows[i], e2);
                C->nonzero += 1;
                moveNext(B->rows[i]);
            }
        }

        while(index(A->rows[i]) >= 0) {
                Entry a1 = (Entry) get(A->rows[i]);
                Entry e1 = newEntry(a1->val, a1->column);
                append(C->rows[i], e1);
                C->nonzero += 1;
                moveNext(A->rows[i]);
        }

        while(index(B->rows[i]) >= 0) {
                Entry b1 = (Entry) get(B->rows[i]);
                Entry e1 = newEntry(b1->val, b1->column);
                append(C->rows[i], e1);
                C->nonzero += 1;
                moveNext(B->rows[i]);
        }


    }
    return C;
}

// diff: Returns difference between A and B.
// Pre: A and B are not NULL.
Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "ERROR!!! Matrices are not the same size.\n");
        exit(1);
    }

    //Matrix B2 = copy(B);
    if (equals(A, B)) {
        Matrix D = newMatrix(size(A));
        return D;
    }
    Matrix C = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        while(index(A->rows[i]) >= 0 && index(B->rows[i]) >= 0) {
            Entry a1 = (Entry) get(A->rows[i]);
            Entry b1 = (Entry) get(B->rows[i]);

            if (a1->column == b1->column) {
                double sum1 = a1->val - b1->val;
                if (sum1 != 0) {
                    Entry e3_s = newEntry(sum1, a1->column);
                    append(C->rows[i], e3_s);
                    C->nonzero += 1;
                }
                moveNext(A->rows[i]);
                moveNext(B->rows[i]);
            }

            else if (a1->column < b1->column) {
                Entry e1 = newEntry(a1->val, a1->column);
                append(C->rows[i], e1);
                C->nonzero += 1;
                moveNext(A->rows[i]);
            }

            else {
                Entry e2 = newEntry(-1 * (b1->val), b1->column);
                append(C->rows[i], e2);
                C->nonzero += 1;
                moveNext(B->rows[i]);
            }
        }

        while(index(A->rows[i]) >= 0) {
                Entry a1 = (Entry) get(A->rows[i]);
                Entry e1 = newEntry(a1->val, a1->column);
                append(C->rows[i], e1);
                C->nonzero += 1;
                moveNext(A->rows[i]);
        }

        while(index(B->rows[i]) >= 0) {
                Entry b1 = (Entry) get(B->rows[i]);
                Entry e1 = newEntry(-1 * (b1->val), b1->column);
                append(C->rows[i], e1);
                C->nonzero += 1;
                moveNext(B->rows[i]);
        }


    }
    return C;

}

// vectorDot: Private functions to compute dot product.
// Pre: P and Q have to not be NULL
double vectorDot(List P, List Q) {
    if ((!P) || (!Q)) {
        fprintf(stderr, "ERROR! One of the lists is NULL\n");
        exit(1);
    }

    moveFront(P);
    moveFront(Q);
    double sum = 0;
    while(index(P) >= 0 && index(Q) >= 0) {
        Entry e1 = (Entry) get(P);
        Entry e2 = (Entry) get(Q);
        if (e1->column == e2->column) {
            sum += (e1->val * e2->val);
            moveNext(P);
            moveNext(Q);
        }

        else if (e1->column < e2->column) {
            moveNext(P);
        }

        else {
            moveNext(Q);
        }
    }

    return sum;
}

// product: Returns product of 2 matrices
// Pre: A and B are not NULL
Matrix product(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        fprintf(stderr, "ERROR!!! Matrices are not the same size.\n");
        exit(1);
    }

    Matrix T = transpose(B);

    Matrix P = newMatrix(size(A));
    for (int i = 1; i <= size(P); i++) {
        if (length(A->rows[i]) == 0) {
            continue;
        }
        for (int j = 1; j <= size(P); j++) {
            if (length(T->rows[j]) == 0) {
                continue;
            }
            double sol = vectorDot(A->rows[i], T->rows[j]);
            if (sol == 0) {
                continue;
            }
            else {
                Entry e1 = newEntry(sol, j);
                append(P->rows[i], e1);
                P->nonzero += 1;
            }
        }
    }
    freeMatrix(&T);
    return P;
}

// printMatrix: prints Matrix in certain form.
// Pre: Matrix is not null.
void printMatrix(FILE* out, Matrix M) {
    if (!M) {
        fprintf(stderr, "MATRIX M IS NULL!!!\n");
        exit(1);
    }

    for (int i = 1; i <= size(M); i++) {
        if (length(M->rows[i]) == 0) {
            continue;
        }
        fprintf(out, "%i:", i);
        moveFront((M->rows)[i]);
        while(index((M->rows)[i]) >= 0) {
            Entry M1 = (Entry) get((M->rows)[i]);
            fprintf(out, " (%i, %.1lf)", M1->column, M1->val);
            moveNext((M->rows)[i]);
        }

        fprintf(out, "\n");
    }
}
