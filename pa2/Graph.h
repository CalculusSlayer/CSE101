// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA2
//  Graph.h
//  This file contains function prototypes of the Graph ADT
// -----------------------------------------------------------------------------
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define NIL 0
#define INF -5
#define PRINT_ELEMENT_GRAPH "i"    // Change this to change format specifier for printGraph
typedef int GraphElement; // Change this to change the type of List.

// exported Graph type
typedef struct GraphObj *Graph;  // Pointer to GraphObj

/*** Constructors-Destructors ***/
Graph newGraph(GraphElement n);  // Creates a new graph
void freeGraph(Graph* pG);      // Frees memory allocated for graph

/*** Access functions ***/
GraphElement getOrder(Graph G); // Get the number of vertices
GraphElement getSize(Graph G);  // Get the number of edges
GraphElement getSource(Graph G); // Get the source of the graph
GraphElement getParent(Graph G, GraphElement u); // Get the parent of element u
GraphElement getDist(Graph G, GraphElement u);  // get the distance from the source to u
void getPath(List L, Graph G, GraphElement u);  // Appends path to list L

/*** Manipulation procedures ***/
void makeNull(Graph G);  // Reset to initial conditions of the graph
void addEdge(Graph G, GraphElement u, GraphElement v);  // Add an edge from u to v
void addArc(Graph G, GraphElement u, GraphElement v);  // Add an arc from u to v
void BFS(Graph G, GraphElement s);  // Performs the BFS algorithm

/*** Other operations ***/
void printGraph(FILE* out, Graph G); // Print the graph to outfile
