//-----------------------------------------------------------------------------
// GraphClient.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
    Graph A = newGraph(100);

    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);

    List L = newList();
    for (int i = 1; i <= 100; i++) {
      prepend(L, i);
    }
    DFS(A, L);

    if (getDiscover(A, 100) != 1)
      fprintf(stderr, "2\n");
    if (getDiscover(A, 64) != 73)
      fprintf(stderr, "3\n");
    if (getDiscover(A, 4) != 80)
      fprintf(stderr, "4\n");

    DFS(A, L);
    // if (getDiscover(A, 4) != 126)
    //   fprintf(stderr, "5\n");
    printf("%i\n", getDiscover(A, 4));

   return(0);
}