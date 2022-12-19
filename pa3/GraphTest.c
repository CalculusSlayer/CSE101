// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA3
//  GraphTest.c
//  This file contains test cases for the Graph ADT.
// -----------------------------------------------------------------------------

#include "Graph.h"

int main(void) {
    //FILE *outfile = fopen("f1.txt", "w");
    FILE *outfile = stdout;
    Graph g1 = newGraph(6);
    addArc(g1, 1, 2);
    addArc(g1, 1, 4);
    addArc(g1, 1, 5);
    addArc(g1, 2, 3);
    addArc(g1, 2, 6);
    addArc(g1, 3, 6);
    addArc(g1, 5, 2);
    addArc(g1, 5, 4);
    addArc(g1, 5, 6);

    printGraph(outfile, g1);
    fprintf(outfile, "g1 has order of %i\n", getOrder(g1));
    fprintf(outfile, "g1 has size of %i\n", getSize(g1));

    Graph g2 = copyGraph(g1);
    printGraph(outfile, g2);
    fprintf(outfile, "g2 has order of %i\n", getOrder(g2));
    fprintf(outfile, "g2 has size of %i\n", getSize(g2));

    Graph g3 = transpose(g1);
    printGraph(outfile, g3);
    fprintf(outfile, "g3 has order of %i\n", getOrder(g3));
    fprintf(outfile, "g3 has size of %i\n", getSize(g3));

    freeGraph(&g1);
    freeGraph(&g2);
    freeGraph(&g3);

    fprintf(outfile, "\n");
    g1 = newGraph(10);
    addArc(g1, 1, 2);
    addArc(g1, 1, 4);
    addArc(g1, 1, 5);
    addArc(g1, 3, 2);
    addArc(g1, 2, 6);
    addArc(g1, 3, 6);
    addArc(g1, 2, 5);
    addArc(g1, 5, 4);
    addArc(g1, 6, 5);
    addArc(g1, 3, 5);
    addArc(g1, 7, 10);
    addArc(g1, 8, 9);

    printGraph(outfile, g1);
    fprintf(outfile, "g1 has order of %i\n", getOrder(g1));
    fprintf(outfile, "g1 has size of %i\n", getSize(g1));

    g2 = copyGraph(g1);
    printGraph(outfile, g2);
    fprintf(outfile, "g2 has order of %i\n", getOrder(g2));
    fprintf(outfile, "g2 has size of %i\n", getSize(g2));

    g3 = transpose(g1);
    printGraph(outfile, g3);
    fprintf(outfile, "g3 has order of %i\n", getOrder(g3));
    fprintf(outfile, "g3 has size of %i\n", getSize(g3));

    freeGraph(&g1);
    freeGraph(&g2);
    freeGraph(&g3);

    fprintf(outfile, "\n");
    g1 = newGraph(30);
    addArc(g1, 2, 1);
    addArc(g1, 1, 4);
    addArc(g1, 1, 7);
    addArc(g1, 3, 2);
    addArc(g1, 12, 6);
    addArc(g1, 3, 6);
    addArc(g1, 2, 5);
    addArc(g1, 5, 4);
    addArc(g1, 6, 5);
    addArc(g1, 3, 5);
    addArc(g1, 7, 10);
    addArc(g1, 8, 9);
    addArc(g1, 10, 12);
    addArc(g1, 11, 14);
    addArc(g1, 11, 15);
    addArc(g1, 23, 22);
    addArc(g1, 22, 16);
    addArc(g1, 13, 26);
    addArc(g1, 12, 5);
    addArc(g1, 5, 24);
    addArc(g1, 26, 15);
    addArc(g1, 13, 5);
    addArc(g1, 17, 10);
    addArc(g1, 8, 19);

    printGraph(outfile, g1);
    fprintf(outfile, "g1 has order of %i\n", getOrder(g1));
    fprintf(outfile, "g1 has size of %i\n", getSize(g1));

    g2 = copyGraph(g1);
    printGraph(outfile, g2);
    fprintf(outfile, "g2 has order of %i\n", getOrder(g2));
    fprintf(outfile, "g2 has size of %i\n", getSize(g2));

    g3 = transpose(g1);
    printGraph(outfile, g3);
    fprintf(outfile, "g3 has order of %i\n", getOrder(g3));
    fprintf(outfile, "g3 has size of %i\n", getSize(g3));

    List stack1 = newList();
    for (int i = 1; i <= getOrder(g1); i++) {
        append(stack1, i);
    }
    DFS(g1, stack1);

    for (int i = 1; i <= getOrder(g1); i++) {
        fprintf(outfile, "Vertex %i discovered = %i, finished = %i\n", i, getDiscover(g1, i), getDiscover(g1, i));
    }
    fprintf(outfile, "\n");

    freeList(&stack1);
    freeGraph(&g1);
    freeGraph(&g2);
    freeGraph(&g3);
    //fclose(outfile);

    return 0;
}

/*
Output of GraphTest:
1: 2 4 5 
2: 3 6 
3: 6 
4: 
5: 2 4 6 
6: 
g1 has order of 6
g1 has size of 9
1: 2 4 5 
2: 3 6 
3: 6 
4: 
5: 2 4 6 
6: 
g2 has order of 6
g2 has size of 9
1:
2: 1 5
3: 2
4: 1 5
5: 1
6: 2 3 5
g3 has order of 6
g3 has size of 9

1: 2 4 5
2: 5 6
3: 2 5 6
4:
5: 4
6: 5
7: 10
8: 9
9:
10:
g1 has order of 10
g1 has size of 12
1: 2 4 5
2: 5 6
3: 2 5 6
4:
5: 4
6: 5
7: 10
8: 9
9:
10:
g2 has order of 10
g2 has size of 12
1:
2: 1 3
3:
4: 1 5
5: 1 2 3 6
6: 2 3
7:
8:
9: 8
10: 7
g3 has order of 10
g3 has size of 12

1: 4 7
2: 1 5
3: 2 5 6
4:
5: 4 24
6: 5
7: 10
8: 9 19
9:
10: 12
11: 14 15
12: 5 6
13: 5 26
14:
15:
16:
17: 10
18:
19:
20:
21:
22: 16
23: 22
24:
25:
26: 15
27:
28:
29:
30:
g1 has order of 30
g1 has size of 24
1: 4 7
2: 1 5
3: 2 5 6
4:
5: 4 24
6: 5
7: 10
8: 9 19
9:
10: 12
11: 14 15
12: 5 6
13: 5 26
14:
15:
16:
17: 10
18:
19:
20:
21:
22: 16
23: 22
24:
25:
26: 15
27:
28:
29:
30:
g2 has order of 30
g2 has size of 24
1: 2
2: 3
3:
4: 1 5
5: 2 3 6 12 13
6: 3 12
7: 1
8:
9: 8
10: 7 17
11:
12: 10
13:
14: 11
15: 11 26
16: 22
17:
18:
19: 8
20:
21:
22: 23
23:
24: 5
25:
26: 13
27:
28:
29:
30:
g3 has order of 30
g3 has size of 24
Vertex 1 discovered = 1, finished = 1
Vertex 2 discovered = 17, finished = 17
Vertex 3 discovered = 19, finished = 19
Vertex 4 discovered = 2, finished = 2
Vertex 5 discovered = 7, finished = 7
Vertex 6 discovered = 11, finished = 11
Vertex 7 discovered = 4, finished = 4
Vertex 8 discovered = 21, finished = 21
Vertex 9 discovered = 22, finished = 22
Vertex 10 discovered = 5, finished = 5
Vertex 11 discovered = 27, finished = 27
Vertex 12 discovered = 6, finished = 6
Vertex 13 discovered = 33, finished = 33
Vertex 14 discovered = 28, finished = 28
Vertex 15 discovered = 30, finished = 30
Vertex 16 discovered = 37, finished = 37
Vertex 17 discovered = 39, finished = 39
Vertex 18 discovered = 41, finished = 41
Vertex 19 discovered = 24, finished = 24
Vertex 20 discovered = 43, finished = 43
Vertex 21 discovered = 45, finished = 45
Vertex 22 discovered = 47, finished = 47
Vertex 23 discovered = 49, finished = 49
Vertex 24 discovered = 8, finished = 8
Vertex 25 discovered = 51, finished = 51
Vertex 26 discovered = 34, finished = 34
Vertex 27 discovered = 53, finished = 53
Vertex 28 discovered = 55, finished = 55
Vertex 29 discovered = 57, finished = 57
Vertex 30 discovered = 59, finished = 59

*/