// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA2
//  Graph.c
//  This file contains functions of the Graph ADT.
// -----------------------------------------------------------------------------
#include "Graph.h"

// private GraphObj type
typedef struct GraphObj {
    List *adjList;
    char *vertex_colors;
    GraphElement *parents;
    GraphElement *distances;
    GraphElement order;
    GraphElement size;
    GraphElement source;
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

    G->distances = malloc((n+1)*sizeof(GraphElement));
    for (int i = 1; i < n+1; i++) {
        G->distances[i] = INF;
    }

    G->order = n;
    G->size = 0;
    G->source = NIL;

    return G;
}

// freeGraph frees all memory allocated for the graph
// Pre: The graph cannot be a null reference
void freeGraph(Graph* pG) {
    for (int i = 1; i < (*pG)->order+1; i++) {
        freeList(&((*pG)->adjList[i]));
    }

    free((*pG)->adjList);
    (*pG)->adjList = NULL;

    free((*pG)->vertex_colors);
    (*pG)->vertex_colors = NULL;

    free((*pG)->parents);
    (*pG)->parents = NULL;

    free((*pG)->distances);
    (*pG)->distances = NULL;

    free(*pG);
    *pG = NULL;

    // not done yet
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

// getSource gets the source of the graph.
// Pre: Graph cannot be NULL reference.
GraphElement getSource(Graph G) {
    if (G) {
        return G->source;
    }
    else {
        fprintf(stderr, "Error: Called getSource on NULL reference.\n");
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

// getDist gets the distance of the from the source to u.
// Pre: u has to be between 1 and the order (inclusive) 
GraphElement getDist(Graph G, GraphElement u) {
    if (G) {
        if (u >= 1 && u <= G->order) {
            return G->distances[u];
        }
        else {
            fprintf(stderr, "Error: Called getDist with invalid vertex.\n");
            exit(1);
        }
    }

    else {
        fprintf(stderr, "Error: Called getDist on NULL reference.\n");
        exit(1);
    }
}

// getPath appends the shortest path to List L
// if one exits. Otherwise, NIL is appended.
// Pre: Source is not equal to NIL
void getPath(List L, Graph G, GraphElement u) {
    if (L && G && getSource(G) != NIL) {
        if (u == getSource(G)) {
            append(L, u);
        }
        else if (G->parents[u] == NIL) {
            append(L, NIL);
        }
        else {
            getPath(L, G, G->parents[u]);
            if (back(L) != NIL) {
                append(L, u);
            }
        }
    }
    
    else if (!L || !G) {
        fprintf(stderr, "Either List or Graph is NULL.\n");
    }

    else {
        fprintf(stderr, "BFS was not called on graph yet.\n");
        exit(-1);
    }
}

// makeNull resets the graph to its initial condition.
// Pre: G is not a NULL reference.
void makeNull (Graph G) {
    for (int i = 1; i < getOrder(G)+1; i++) {
        clear(G->adjList[i]);
    }
    
    for (int i = 1; i < getOrder(G)+1; i++) {
        G->vertex_colors[i] = 'w';
    }
    
    for (int i = 1; i < getOrder(G)+1; i++) {
        G->parents[i] = NIL;
    }

    for (int i = 1; i < getOrder(G)+1; i++) {
        G->distances[i] = INF;
    }

    G->size = 0;
    G->source = NIL;

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
            //printf("hi");
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

// BFS performs the algorithm and sets the distance
// parents, and the source.
// PRE: G is not a NULL reference.
void BFS(Graph G, GraphElement s) {
    
    for (int i = 1; i < getOrder(G)+1; i++) {
        G->vertex_colors[i] = 'w';
    }
    
    for (int i = 1; i < getOrder(G)+1; i++) {
        G->parents[i] = NIL;
    }

    for (int i = 1; i < getOrder(G)+1; i++) {
        G->distances[i] = INF;
    }

    G->vertex_colors[s] = 'g';
    G->distances[s] = 0;
    G->parents[s] = NIL;

    List queue = newList();
    append(queue, s);
    
    while(length(queue) > 0) {
        moveFront(queue);
        GraphElement x = get(queue);
        delete(queue);

        moveFront(G->adjList[x]);
        while(index(G->adjList[x]) != -1) {
            GraphElement y = get(G->adjList[x]);
            if (G->vertex_colors[y] == 'w') {
                G->vertex_colors[y] = 'g';
                G->distances[y] = G->distances[x] + 1;
                G->parents[y] = x;
                append(queue, y);
            }
            moveNext(G->adjList[x]);
        }

        G->vertex_colors[x] = 'b';

    }
    G->source = s;
    freeList(&queue);
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