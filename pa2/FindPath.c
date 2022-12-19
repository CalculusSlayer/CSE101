// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA2
//  FindPath.c
//  This file contains functions of the main file that 
//  reads an input file to create a graph and find
//  different paths and distances.
// -----------------------------------------------------------------------------

#include "Graph.h"

int main(int argc, char *argv[]) {

    FILE *in = NULL;
    FILE *out = NULL;

   if( argc != 3 ){
      fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
      if( in==NULL ){
      fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

    int vertex_number = 0;
    fscanf(in, "%d", &vertex_number);
    //fprintf(out, "Number of vertices = %i", vertex_number);
    Graph sol = newGraph(vertex_number);

    int v1, v2;
    //int count = 1;
    while (fscanf(in, "%d %d", &v1, &v2) == 2) {
        if (v1 == 0 && v2 == 0) {
            break;
        }
        //fprintf(out, "%d) vertex 1 = %d, vertex 2 = %d\n", count, num1, num2);
        //count++;
        addEdge(sol, v1, v2);
    }

    printGraph(out, sol);
    fprintf(out, "\n");

    int dist, check_nil;
    List path = newList();
    while(fscanf(in, "%d %d", &v1, &v2)) {
        if (v1 == 0 && v2 == 0) {
            break;
        }
        BFS(sol, v1);
        dist = getDist(sol, v2);
        
        if (dist == INF) {
            fprintf(out, "The distance from %i to %i is infinity\n", 
            getSource(sol), v2);

        }
        else {
            fprintf(out, "The distance from %i to %i is %i\n", 
            getSource(sol), v2, dist);
        }
        
        getPath(path, sol, v2);
        moveFront(path);
        check_nil = get(path);

        if (check_nil == NIL) {
            fprintf(out, "No %i-%i path exists\n", getSource(sol), v2);
        }

        else {
            fprintf(out, "A shortest %i-%i path is: ", getSource(sol), v2);

            printList(out, path);
            fprintf(out, "\n");
        }
        
        fprintf(out, "\n");
        clear(path);
    }

    freeList(&path);
    freeGraph(&sol);
    fclose(in);
    fclose(out);

    return 0;
}