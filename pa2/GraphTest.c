// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA2
//  GraphTest.c
//  This file contains the test cases for the graph ADT.
// -----------------------------------------------------------------------------
#include "Graph.h"

void doAll(FILE *out, Graph g, int s);
void printDistances(FILE *out, Graph g);
void printParents(FILE *out, Graph g);

// Run BFS algorithm for a particular source
// and check conditions of distances, parents, 
// and adjacency lists.
void doAll(FILE *out, Graph g, int s) {
    BFS(g, s);
    printGraph(out, g);
    fprintf(out, "\n");
    printDistances(out, g);
    fprintf(out, "\n");
    printParents(out, g);
    fprintf(out, "\n");
}

// Run BFS function before using this
void printDistances(FILE *out, Graph g) {
    for (int i = 1; i <= getOrder(g); i++) {
        int dist = getDist(g, i);
        if (dist != INF) {
            fprintf(out, "Distance from %i to %i is %i.\n", getSource(g), i, dist);
        }
        else {
            fprintf(out, "Distance from %i to %i is infinity.\n", getSource(g), i);
        }
    }
}

// Run BFS function before using this
void printParents(FILE *out, Graph g) {
    for (int i = 1; i <= getOrder(g); ++i) {
        int parent = getParent(g, i);
        if (parent != NIL) {
            fprintf(out, "Parent of %i is %i.\n", i, parent);
        }
        else {
            fprintf(out, "No parent of %i.\n", i);
        }

    }
}

int main(void) {
    FILE *out1 = stdout;

    GraphElement size = 10;
    Graph a = newGraph(size);
    fprintf(out1, "Information about new graph:\n"
    "Order of graph = %i\n"
    "Size of graph = %i\n"
    "Source of graph = %i\n",
    getOrder(a), getSize(a), getSource(a));
    fprintf(out1, "Creating graph with %i vertices.\n", size);
    for (int i = 1; i < size; ++i) {
        addEdge(a, i, i+1);
    }
    for (int i = 1; i < size-1; i++) {
        addEdge(a, i, i+2);
    }
    printGraph(out1, a);
    fprintf(out1, "\n");
    fprintf(out1, "Size of graph after adding undirected edges = %i\n", getSize(a));

    makeNull(a);
    printGraph(out1, a);
    fprintf(out1, "\n");

    for (int i = 1; i < size; ++i) {
        addArc(a, i, i+1);
    }
    for (int i = 1; i < size-1; i++) {
        addArc(a, i, i+2);
    }
    printGraph(out1, a);
    fprintf(out1, "\n");

    fprintf(out1, "Size of graph after adding directed edges = %i\n", getSize(a));

    makeNull(a);
    printGraph(out1, a);
    fprintf(out1, "\n");

    fprintf(out1, "Information about graph before being freed:\n"
    "Order of graph = %i\n"
    "Size of graph = %i\n"
    "Source of graph = %i\n",
    getOrder(a), getSize(a), getSource(a));

    freeGraph(&a);

    Graph ex1 = newGraph(6);
    addEdge(ex1, 1, 2);
    addEdge(ex1, 1, 3);
    addEdge(ex1, 3, 4);
    addEdge(ex1, 2, 4);
    addEdge(ex1, 2, 5);
    addEdge(ex1, 2, 6);
    addEdge(ex1, 4, 5);
    addEdge(ex1, 5, 6);

    fprintf(out1, "\n");

    for (int count = 1; count <= getOrder(ex1); count++) {
        fprintf(out1, "Printing example 1 graph, source = %i\n", count);
        doAll(out1, ex1, count);
    }

    freeGraph(&ex1);
    //fclose(out1);

    return 0;
}

/* ~~~~~~~~~~ EXPECTED OUTPUT ~~~~~~~~~~
Information about new graph:
Order of graph = 10
Size of graph = 0
Source of graph = 0
Creating graph with 10 vertices.
1: 2 3 
2: 1 3 4 
3: 1 2 4 5 
4: 2 3 5 6 
5: 3 4 6 7 
6: 4 5 7 8 
7: 5 6 8 9 
8: 6 7 9 10
9: 7 8 10
10: 8 9

Size of graph after adding undirected edges = 17
1:
2:
3:
4:
5:
6:
7:
8:
9:
10:

1: 2 3
2: 3 4
3: 4 5
4: 5 6
5: 6 7
6: 7 8
7: 8 9
8: 9 10
9: 10
10:

Size of graph after adding directed edges = 17
1:
2:
3:
4:
5:
6:
7:
8:
9:
10:

Information about graph before being freed:
Order of graph = 10
Size of graph = 0
Source of graph = 0

Printing example 1 graph, source = 1
1: 2 3
2: 1 4 5 6
3: 1 4
4: 2 3 5
5: 2 4 6
6: 2 5

Distance from 1 to 1 is 0.
Distance from 1 to 2 is 1.
Distance from 1 to 3 is 1.
Distance from 1 to 4 is 2.
Distance from 1 to 5 is 2.
Distance from 1 to 6 is 2.

No parent of 1.
Parent of 2 is 1.
Parent of 3 is 1.
Parent of 4 is 2.
Parent of 5 is 2.
Parent of 6 is 2.

Printing example 1 graph, source = 2
1: 2 3
2: 1 4 5 6
3: 1 4
4: 2 3 5
5: 2 4 6
6: 2 5

Distance from 2 to 1 is 1.
Distance from 2 to 2 is 0.
Distance from 2 to 3 is 2.
Distance from 2 to 4 is 1.
Distance from 2 to 5 is 1.
Distance from 2 to 6 is 1.

Parent of 1 is 2.
No parent of 2.
Parent of 3 is 1.
Parent of 4 is 2.
Parent of 5 is 2.
Parent of 6 is 2.

Printing example 1 graph, source = 3
1: 2 3
2: 1 4 5 6
3: 1 4
4: 2 3 5
5: 2 4 6
6: 2 5

Distance from 3 to 1 is 1.
Distance from 3 to 2 is 2.
Distance from 3 to 3 is 0.
Distance from 3 to 4 is 1.
Distance from 3 to 5 is 2.
Distance from 3 to 6 is 3.

Parent of 1 is 3.
Parent of 2 is 1.
No parent of 3.
Parent of 4 is 3.
Parent of 5 is 4.
Parent of 6 is 2.

Printing example 1 graph, source = 4
1: 2 3
2: 1 4 5 6
3: 1 4
4: 2 3 5
5: 2 4 6
6: 2 5

Distance from 4 to 1 is 2.
Distance from 4 to 2 is 1.
Distance from 4 to 3 is 1.
Distance from 4 to 4 is 0.
Distance from 4 to 5 is 1.
Distance from 4 to 6 is 2.

Parent of 1 is 2.
Parent of 2 is 4.
Parent of 3 is 4.
No parent of 4.
Parent of 5 is 4.
Parent of 6 is 2.

Printing example 1 graph, source = 5
1: 2 3
2: 1 4 5 6
3: 1 4
4: 2 3 5
5: 2 4 6
6: 2 5

Distance from 5 to 1 is 2.
Distance from 5 to 2 is 1.
Distance from 5 to 3 is 2.
Distance from 5 to 4 is 1.
Distance from 5 to 5 is 0.
Distance from 5 to 6 is 1.

Parent of 1 is 2.
Parent of 2 is 5.
Parent of 3 is 4.
Parent of 4 is 5.
No parent of 5.
Parent of 6 is 5.

Printing example 1 graph, source = 6
1: 2 3
2: 1 4 5 6
3: 1 4
4: 2 3 5
5: 2 4 6
6: 2 5

Distance from 6 to 1 is 2.
Distance from 6 to 2 is 1.
Distance from 6 to 3 is 3.
Distance from 6 to 4 is 2.
Distance from 6 to 5 is 1.
Distance from 6 to 6 is 0.

Parent of 1 is 2.
Parent of 2 is 6.
Parent of 3 is 1.
Parent of 4 is 2.
Parent of 5 is 6.
No parent of 6.

*/