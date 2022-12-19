// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA3
//  Graph.c
//  This file contains functions of the Graph ADT.
// -----------------------------------------------------------------------------
#include "Graph.h"

// private helper function for DFS
void Visit(Graph G, int x, int *count);

// private GraphObj type
typedef struct GraphObj {
    List *adjList;
    char *vertex_colors;
    GraphElement *parents;
    GraphElement *discovered;
    GraphElement *finished;
    GraphElement order;
    GraphElement size;
} GraphObj;

// newGraph creates a new graph of size n
// Pre: n > 0
Graph newGraph(GraphElement n) {
    if (n <= 0) {
        fprintf(stderr, "CANNOT HAVE GRAPH WITH 0 VERTICES OR LESS!\n");
        exit(1);
    }
    Graph G = malloc(sizeof(GraphObj));

    G->adjList = malloc((n+1)*sizeof(List));
    for (int i = 1; i < n+1; i++) {
        G->adjList[i] = newList();
    }

    G->vertex_colors = malloc((n+1)*sizeof(char));
    for (int i = 1; i < n+1; i++) {
        G->vertex_colors[i] = 'w';
    }

    G->parents = malloc((n+1)*sizeof(GraphElement));
    for (int i = 1; i < n+1; i++) {
        G->parents[i] = NIL;
    }

    G->discovered = malloc((n+1)*sizeof(GraphElement));
    for (int i = 1; i < n+1; i++) {
        G->discovered[i] = UNDEF;
    }

    G->finished = malloc((n+1)*sizeof(GraphElement));
    for (int i = 1; i < n+1; i++) {
        G->finished[i] = UNDEF;
    }

    G->order = n;
    G->size = 0;

    return G;
}

// freeGraph frees all memory allocated for the graph
// Pre: The graph cannot be a null reference
void freeGraph(Graph* pG) {
    // Free all linked lists in adj array
    for (int i = 1; i < (*pG)->order+1; i++) {
        freeList(&((*pG)->adjList[i]));
    }

    // Free the adj array itself
    free((*pG)->adjList);
    (*pG)->adjList = NULL;

    // Free array of vertex colors
    free((*pG)->vertex_colors);
    (*pG)->vertex_colors = NULL;

    // Free array of parents
    free((*pG)->parents);
    (*pG)->parents = NULL;

    // Free discovered array
    free((*pG)->discovered);
    (*pG)->discovered = NULL;

    // Free finished array
    free((*pG)->finished);
    (*pG)->finished = NULL;

    // Free graph obj itself
    free(*pG);
    *pG = NULL;

}

// getOrder gets the number of vertices in the graph.
// Pre: Graph cannot be a null reference.
GraphElement getOrder(Graph G) {
    if (G) {
        return G->order;
    }
	else {
		fprintf(stderr, "Error: Called getOrder on NULL reference.\n");
		exit(1);
	}
}

// getSize gets the number of edges in the graph.
// Pre: Graph cannot be a null reference.
GraphElement getSize(Graph G) {
    if (G) {
        return G->size;
    }
    else {
        fprintf(stderr, "Error: Called getSize on NULL reference.\n");
        exit(1);
    }
}

// getParent gets the parent of u.
// Pre: u has to be between 1 and the order (inclusive)
GraphElement getParent(Graph G, GraphElement u) {
    if (G) {
        if (u >= 1 && u <= G->order) {
            return G->parents[u];
        }
        else {
            fprintf(stderr, "Error: Called getParent with invalid vertex.\n");
            exit(1);
        }
    }

    else {
        fprintf(stderr, "Error: Called getParent on NULL reference.\n");
        exit(1);
    }
}

// getDiscover returns the discover time for
// a particular vertex.
// Pre: G != NULL and u is between 1 and the
// order of the graph (inclusive)
GraphElement getDiscover(Graph G, GraphElement u) {
    if (G) {
        if (u >= 1 && u <= G->order) {
            return G->discovered[u];
        }
        else {
            fprintf(stderr, "Error: Called getDiscover with invalid vertex.\n");
            exit(1);
        }
    }

    else {
        fprintf(stderr, "Error: Called getDiscover on NULL reference.\n");
        exit(1);
    }
}

// getFinish returns the finish time for
// a particular vertex.
// Pre: G != NULL and u is between 1 and the
// order of the graph (inclusive)
GraphElement getFinish(Graph G, GraphElement u) {
    if (G) {
        if (u >= 1 && u <= G->order) {
            return G->finished[u];
        }
        else {
            fprintf(stderr, "Error: Called getFinish with invalid vertex.\n");
            exit(1);
        }
    }

    else {
        fprintf(stderr, "Error: Called getFinish on NULL reference.\n");
        exit(1);
    }
}

// addEdge adds an edge from vertex u to vertex v.
// Pre: u != v, u and v both between 1 and order,
// G is not a NULL reference
void addEdge(Graph G, GraphElement u, GraphElement v) {
    if (G && (getOrder(G) >= 1) && u>=1 && (u<=getOrder(G)) && v>=1 && v<=getOrder(G) && u != v) {
        //List lu = G->adjList[u];
        //printf("%i", length(G->adjList[u]));
        if (length(G->adjList[u]) == 0) {
            //printf("hi");
            append(G->adjList[u], v);
        }

        else {
            moveFront(G->adjList[u]);
            //moveNext(lu);
            bool reach_null = true;
            // char *current_word = words[i];
            while (index(G->adjList[u]) != -1) {
                //printList(stdout, G->adjList[u]);
                if (get(G->adjList[u]) == v) {
                    return;
                }

                else if (get(G->adjList[u]) > v) {
                    insertBefore(G->adjList[u], v);
                    reach_null = false;
                    break;
                }
                moveNext(G->adjList[u]);
            }

            if (reach_null) {
                append(G->adjList[u], v);
            }
        }

        //List lv = G->adjList[v];

        if (length(G->adjList[v]) == 0) {
            append(G->adjList[v], u);
        }

        else {
            moveFront(G->adjList[v]);
            bool reach_null = true;

            while (index(G->adjList[v]) != -1) {
                // Code won't ever reach here if
                // there was duplicate, but
                // will keep anyway.
                if (get(G->adjList[v]) == u) {
                    return;
                }

                else if (get(G->adjList[v]) > u) {
                    insertBefore(G->adjList[v], u);
                    reach_null = false;
                    break;
                }

                moveNext(G->adjList[v]);
            }

            if (reach_null) {
                append(G->adjList[v], u);
            }
        }

        G->size += 1;
    }

    else if (!G) {
        fprintf(stderr, "Can't call addEdge on NULL graph reference.\n");
    }

    else {
        fprintf(stderr, "Either edge u or edge v is not between 1 and %" PRINT_ELEMENT_GRAPH "\n", getOrder(G));
    }

}

// addArc adds an arc from vertex u to vertex v.
// Pre: u and v both between 1 and order,
// G is not a NULL reference
void addArc(Graph G, GraphElement u, GraphElement v) {
    if (G && u>=1 && u<=getOrder(G) && v>=1 && v<=getOrder(G)) {
        //List lu = G->adjList[u];

        if (length(G->adjList[u]) == 0) {
            append(G->adjList[u], v);
        }

        else {
            moveFront(G->adjList[u]);
            //moveNext(lu);
            bool reach_null = true;
            // char *current_word = words[i];
            while (index(G->adjList[u]) != -1) {
                if (get(G->adjList[u]) == v) {
                    return;
                }
                else if (get(G->adjList[u]) > v) {
                    insertBefore(G->adjList[u], v);
                    reach_null = false;
                    break;
                }
                moveNext(G->adjList[u]);
            }

            if (reach_null) {
                append(G->adjList[u], v);
            }
        }

        G->size += 1;
    }

    else if (!G) {
        fprintf(stderr, "Can't call addEdge on NULL graph reference.\n");
    }

    else {
        fprintf(stderr, "Either edge u or edge v is not between 1 and %" PRINT_ELEMENT_GRAPH "\n", getOrder(G));
    }

}

// DFS does a depth first search sorting algorithm
// on a graph. 
// Pre: length(stack) == order of graph
// and stack contains vertices between 1 and order of G inclusive.
void DFS(Graph G, List S) {
    if (length(S) == getOrder(G)) {
        for (int c1 = 1; c1 <= getOrder(G); c1++) {
            G->vertex_colors[c1] = 'w';
            G->parents[c1] = NIL;
        }

        int time = 0;
        moveFront(S);
        while (index(S) != -1) {
            if (G->vertex_colors[get(S)] == 'w') {
                Visit(G, get(S), &time);
            }
            moveNext(S);
        }

        clear(S);
        for (int i = 1; i <= getOrder(G); i++) {
            if (length(S) == 0 ) {
                append(S, i);
            }

            else {
                moveFront(S);
                bool reach_null = true;

                while (index(S) != -1) {
                    if (G->finished[get(S)] <= G->finished[i]) {
                        insertBefore(S, i);
                        reach_null = false;
                        break;
                    }
                    moveNext(S);
                }

                if (reach_null) {
                    append(S, i);
                }
            }
        }
    }

    else if (length(S) != getOrder(G)) {
        fprintf(stderr, "Length of stack does not equal to the order of the graph!\n");
    }
    
}

// Visit function is a private helper
// function that helps with DFS.
// Pre: None
void Visit(Graph G, int x, int *time) {
    G->discovered[x] = ++(*time);
    G->vertex_colors[x] = 'g';

    moveFront(G->adjList[x]);
    while (index(G->adjList[x]) != -1) {
        if (G->vertex_colors[get(G->adjList[x])] == 'w') {
            G->parents[get(G->adjList[x])] = x;
            Visit(G, get(G->adjList[x]), time);
        }
        moveNext(G->adjList[x]);
    }

    G->vertex_colors[x] = 'b';
    G->finished[x] = ++(*time);

}

// This functions reverses the directions
// of the arcs.
// Pre: G is not NULL.
Graph transpose(Graph G) {
    if (G) {
        Graph transpose_graph = newGraph(getOrder(G));

        for (int i = 1; i <= getOrder(G); i++) {
            moveFront(G->adjList[i]);
            while(index(G->adjList[i]) != -1) {
                addArc(transpose_graph, get(G->adjList[i]), i);
                moveNext(G->adjList[i]);
            }
        }
        transpose_graph->size = getSize(G);
        return transpose_graph;
    }

    else {
        fprintf(stderr, "Graph G iS NULL\n");
        exit(1);
    }
}

// This function returns a new copy of
// the Graph G.
// Pre: G is not NULL.
Graph copyGraph(Graph G) {
    if (G) {
        Graph new_graph = newGraph(getOrder(G));

        for (int i = 1; i <= getOrder(G); i++) {

            moveFront(G->adjList[i]);
            while(index(G->adjList[i]) != -1) {
                addArc(new_graph, i, get(G->adjList[i]));
                moveNext(G->adjList[i]);
            }
        }
        new_graph->size = getSize(G);
        return new_graph;
    }
    else {
        fprintf(stderr, "Graph G iS NULL\n");
        exit(1);
    }
}

// printGraph prints the graph to the outfile.
// PRE: Makes sure that G is not NULL.
void printGraph(FILE* out, Graph G) {
    if (G && out) {
        for (int i = 1; i < getOrder(G)+1; i++) {
            fprintf(out, "%" PRINT_ELEMENT_GRAPH ": ", i);
            printList(out, G->adjList[i]);
            fprintf(out, "\n");
        }
    }

    else if (!G) {
        fprintf(stderr, "Cannot call printGraph on a NULL reference.\n");
    }

    else if (!out) {
        fprintf(stderr, "Outfile pointer is NULL.\n");
    }
}