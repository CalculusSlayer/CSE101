// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA3
//  FindComponents.c
//  This file contains functions of the main file that 
//  reads an input file to create a graph and find
//  different strongly connected components.
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
        //fprintf(out, "%d) vertex 1 = %d, vertex 2 = %d\n", count, num1, num2);
        //count++;
        if (v1 == 0 && v2 == 0) {
            break;
        }
        addArc(sol, v1, v2);
    }

    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, sol);
    fprintf(out, "\n");

    List stack = newList();
    for (int i = 1; i <= getOrder(sol); i++) {
        append(stack, i);
    }

    Graph t_graph = transpose(sol);

    DFS(sol, stack);
    DFS(t_graph, stack);

    int component_number = 0;
    moveFront(stack);
    while(index(stack) != -1) {
        if (getParent(t_graph, get(stack)) == NIL) {
            component_number += 1;
        }
        moveNext(stack);
    }

    fprintf(out, "G contains %i strongly connected components:\n", component_number);
    moveBack(stack);
    List small_stack = newList();

    int component_tracker = 0;
    moveBack(stack);
    while(index(stack) != -1) {
        int x = get(stack);
        prepend(small_stack, x);
        if (getParent(t_graph, x) == NIL) {
            component_tracker += 1;
            fprintf(out, "Component %i:", component_tracker);
            moveFront(small_stack);
            while (index(small_stack) != -1) {
                fprintf(out, " %i", get(small_stack));
                moveNext(small_stack);
            }
            fprintf(out, "\n");
            clear(small_stack);
        }

        movePrev(stack);
    }

    fclose(in);
    fclose(out);
    freeGraph(&sol);
    freeGraph(&t_graph);
    freeList(&stack);
    freeList(&small_stack);

    return 0;
}