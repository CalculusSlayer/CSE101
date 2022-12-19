// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA1
//  ListTest.c
//  This file contains tests for the List ADT
// -----------------------------------------------------------------------------
#include "List.h"

int main(void) {
    printf("TESTING LIST ADT!!!\n");
    List l1 = newList();
    append(l1, 4);
    append(l1, 5);
    append(l1, 6);
    append(l1, 7);
    append(l1, 8);
    
    //FILE *outfile = fopen(stdout, "w");
    moveFront(l1);
    moveNext(l1);
    printList(stdout, l1);
    printf("%i\n", length(l1));
    printf("%i\n", get(l1));
    printf("%i\n", front(l1));
    printf("%i\n", back(l1));

    
    moveBack(l1);
    printf("%i\n", get(l1));
    printf("%i\n", index(l1));
    prepend(l1, 4220);
    printList(stdout, l1);
    printf("\n");

    append(l1, 169);
    printList(stdout, l1);
    printf("\n");
    append(l1, 10000);
    printList(stdout, l1);
    printf("\n");

    insertBefore(l1, 33);
    insertAfter(l1, 34);
    printList(stdout, l1);
    printf("\n");

    deleteFront(l1);
    printList(stdout, l1);
    printf("\n");
    deleteBack(l1);
    printList(stdout, l1);
    printf("\n");

    delete(l1);
    printList(stdout, l1);
    printf("\n");

    List l2 = newList();
    append(l2, 4);
    append(l2, 55);
    append(l2, 69);
    printList(stdout, l2);
    printf("\n");

    if (equals(l1, l2)) {
        printf("l1 and l2 are equal\n");
    }
    else {
        printf("l1 and l2 are NOT equal\n");
    }

    List l3 = copyList(l2);
    if (equals(l2, l3)) {
        printf("l2 and l3 and equal\n");
    }
    else {
        printf("l2 and l3 and NOT equal\n");
    }

    prepend(l2, 100);
    moveFront(l3);
    insertBefore(l3, 100);

    if (equals(l2, l3)) {
        printf("l2 and l3 are equal\n");
    }
    else {
        printf("l2 and l3 are NOT equal\n");
    }


    //clear(l1);
    moveFront(l1);
    clear(l1);
    printList(stdout, l1);
    printf("\n");

    freeList(&l1);
    freeList(&l2);
    freeList(&l3);
    //fclose(outfile);

    return 0;
}

/*
Output of this program:
TESTING LIST ADT!!!
4 5 6 7 8 5
4220 4 5 6 7 33 8 34 169 10000
4 5 6 7 33 8 34 169 10000
4 5 6 7 33 8 34 169
4 5 6 7 33 34 169
4 55 69
l1 and l2 are NOT equal
l2 and l3 and equal
l2 and l3 are equal

*/