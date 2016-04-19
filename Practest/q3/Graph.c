// Graph.c ... implementation of Graph ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

// type for small +ve int values
typedef unsigned char bool;

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	bool **edges; // matrix of booleans
} GraphRep;

// validV ... check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// mkEdge ... create an Edge value
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(validV(g,v) && validV(g,w));
	Edge e; e.v = v; e.w = w;
	return e;
}

// newGraph ... create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int i, j;
	bool **e = malloc(nV * sizeof(bool *));
	assert(e != NULL);
	for (i = 0; i < nV; i++) {
		e[i] = malloc(nV * sizeof(bool));
		assert(e[i] != NULL);
		for (j = 0; j < nV; j++)
			e[i][j] = 0;
	}
	Graph g = malloc(sizeof(GraphRep));
	assert(g != NULL);
	g->nV = nV;  g->nE = 0;  g->edges = e;
	return g;
}

// readGraph ... read graph contents from file
static void readError()
{
	fprintf(stderr,"Bad graph data file\n");
	exit(1);
}
Graph readGraph(FILE *in)
{
	Graph g;
	char line[100];
	// get #vertices and create graph
	int nV = 0;
	if (fgets(line,100,in) == NULL) readError();
	if (sscanf(line,"%d",&nV) != 1) readError();
	if (nV < 2) readError();
	g = newGraph(nV);
	// read edge data and add edges
	Vertex v, w;
	while (fgets(line,100,in) != NULL) {
		sscanf(line,"%d-%d",&v,&w);
		insertE(g, mkEdge(g,v,w));
	}
	return g;
}

// showGraph ... display a graph
void showGraph(Graph g)
{
	assert(g != NULL);
	printf("# vertices = %d, # edges = %d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d is connected to",v);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf(" %d",w);
			}
		}
		printf("\n");
	}
}

// insertE ... add a new edge
void  insertE(Graph g, Edge e)
{
	assert(g != NULL);
	assert(validV(g,e.v) && validV(g,e.w));
	if (g->edges[e.v][e.w]) return;
	g->edges[e.v][e.w] = 1;
	g->edges[e.w][e.v] = 1;
	g->nE++;
}

// removeE ... delete an edge
void  removeE(Graph g, Edge e)
{
	assert(g != NULL);
	assert(validV(g,e.v) && validV(g,e.w));
	if (!g->edges[e.v][e.w]) return;
	g->edges[e.v][e.w] = 0;
	g->edges[e.w][e.v] = 0;
	g->nE--;
}

// nComponents ... number of connected components
/*
CountComponents:
   initialise global ComponentOf[] array to all unassigned
   while (not all vertices have been assigned to a component) {
      find an unassigned vertex V
      count a new component
      do a depth first search of the graph starting from V
   }

DepthFirstSearch:
   assign current vertex to component
   for each unassigned neighbour N of current vertex
      do a depth first search of the graph on N
*/

int *componentOf;  // array of component ids
                   // indexed by vertex 0..V-1
int ncounted;      // # vertices included so far

int nComponents(Graph g)
{
	int i = 0;
	int comp = 0;
    componentOf = malloc(g->nV*sizeof(int));
    for (i = 0; i < g->nV; i++) componentOf[i] = -1;
	ncounted = 0;
    while (ncounted < g->nV) {
        Vertex v;
        for (v = 0; v < g->nV; v++)
			if (componentOf[v] == -1) break;
			dfsComponents(g, v, comp);
			comp++;
   }
   free(componentOf);
	/*int *ComponentOf = malloc(sizeof(int*(g->nv));
	int i ; //Element of cocponenetof[]
	Vertex v;
	for ( i=0 ; i < g->nv ; i++)
	{
		ComponentOf[i] = UNASSIGNED;
	}
	while (g->*/
	return comp; // remove this line
}

void dfsComponents(Graph g, Vertex v, int c)
{
   componentOf[v] = c;
   ncounted++;
   Vertex w;
   for (w = 0; w < g->nV; w++) {
      if (g->edges[v][w] && componentOf[w] == -1)
         dfsComponents(g, w, c);
   }
}