// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0); 
   int i,j;
   int **edges = malloc(nV*sizeof(int *));
   for (i = 0;i < nV;i++) {
      edges[i] = malloc(nV*sizeof(int));
      assert(edges[i] != NULL);
      for (j = 0;j < nV;j++) {
         edges[i][j] = 0;
      }
   } 

   Graph g = malloc(sizeof(GraphRep));
   g->nV = nV;
   g->nE = 0;
   g->edges = edges;
   return g;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
    assert(g != NULL && validV(g,src) && validV(g,dest));
    path = malloc((g->nV)*sizeof(int));
    int i = 0;
	int direct = 0;
    direct = g->edges[src][dest]; 
	
    if (!max){
		path[0] = src;
        path[1] = dest;	
    } else {
		path[0] = src;
	    while (*path != dest){
		    if (direct < max ){
		 	    return dest;
		 	    break;
		    } else {
			    for( i=0;i < (g->nV);i++){
				    if (g->edges[i][src] < max && g->edges[i][src] != 0){
				        g->edges[i][src] = 0;
				        g->edges[src][i] = 0;
					    src = i;       
				 	}
					return i;
				}
		    }
		}
	}
	return *path;  // dummy ... always claims there is no path
}























