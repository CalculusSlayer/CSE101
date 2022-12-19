// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA4
//  Matrix.c
//  This file contains the test cases for List ADT.
// -----------------------------------------------------------------------------
#include "List.h"

int main(void) {
    printf("TESTING LIST ADT!!!\n");
    List l1 = newList();
    int z[] = {4, 5, 6, 7, 8};
    append(l1, &z[0]);
    append(l1, &z[1]);
    append(l1, &z[2]);
    append(l1, &z[3]);
    append(l1, &z[4]);
    
    //FILE *outfile = fopen(stdout, "w");
    moveFront(l1);
    moveNext(l1);
    printf("%i\n", length(l1));
    printf("%i\n", *(int *) get(l1));
    printf("%i\n", *(int *)front(l1));
    printf("%i\n", *(int *) back(l1));

    
    moveBack(l1);
    printf("%i\n", *(int *)get(l1));
    printf("%i\n", index(l1));
    prepend(l1, &z[0]);
    printf("\n");

    append(l1, &z[1]);
    printf("\n");
    append(l1, &z[0]);
    // printList(stdout, l1);
    printf("\n");

    insertBefore(l1, &z[2]);
    insertAfter(l1, &z[3]);
    // printList(stdout, l1);
    printf("\n");

    deleteFront(l1);
    // printList(stdout, l1);
    printf("\n");
    deleteBack(l1);
    // printList(stdout, l1);
    printf("\n");

    delete(l1);
    // printList(stdout, l1);
    printf("\n");

    List l2 = newList();
    append(l2, &z[3]);
    append(l2, &z[3]);
    append(l2, &z[2]);
    // printList(stdout, l2);
    printf("hi");

    //clear(l1);
    prepend(l2, &z[4]);
    prepend(l2, &z[4]);
    prepend(l2, &z[4]);
    prepend(l2, &z[4]);
    prepend(l2, &z[4]);
    prepend(l2, &z[4]);
    moveFront(l1);
    //clear(l1);
    printf("\n");

    prepend(l2, &z[4]);
    prepend(l2, &z[3]);
    prepend(l2, &z[4]);
    prepend(l2, &z[1]);
    prepend(l2, &z[4]);
    prepend(l2, &z[0]);

    printf("%i\n", length(l1));
    printf("%i\n", *(int *) get(l1));
    printf("%i\n", *(int *)front(l1));
    printf("%i\n", *(int *) back(l1));

    insertBefore(l1, &z[2]);
    insertAfter(l1, &z[3]);
    insertBefore(l1, &z[2]);
    insertAfter(l1, &z[3]);
    insertBefore(l1, &z[1]);
    insertAfter(l1, &z[3]);
    insertBefore(l1, &z[4]);
    insertAfter(l1, &z[3]);
    insertBefore(l1, &z[2]);
    insertAfter(l1, &z[0]);

    moveFront(l1);
    while(index(l1) >= 0) {
        fprintf(stdout, "%i\n", *(int *) get(l1));
        moveNext(l1);
    }

    moveFront(l2);
    while(index(l2) >= 0) {
        fprintf(stdout, "%i\n", *(int *) get(l2));
        moveNext(l2);
    }

    freeList(&l1);
    freeList(&l2);
    //fclose(outfile);


    return 0;
}