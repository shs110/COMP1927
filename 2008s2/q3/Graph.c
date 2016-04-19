// Graph.c ... directed graph implementation

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"

typedef struct graphRep GraphRep;

struct graphRep {
	int   nV;     // #vertices
	int   nE;     // #edges
	int **edge;   // adjacency matrix
};

// is vertex valid for a given graph
static int validV(Graph g, Vertex v)
{
	return (v >= 0 && v < g->nV);
}

// make an edge from src,dest vertices
Edge mkEdge(Vertex src, Vertex dest)
{
	assert(src >= 0 && dest >= 0 && src != dest);
	Edge e = {src, dest};
	return e;
}

// create a new empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int i, j, nbytes = 0;
	int **e = malloc(nV * sizeof(int *));
	nbytes += (nV * sizeof(int *));
	assert(e != NULL);
	for (i = 0; i < nV; i++) {
		e[i] = malloc(nV * sizeof(int));
		nbytes += (nV * sizeof(int));
		assert(e[i] != NULL);
		for (j = 0; j < nV; j++)
			e[i][j] = 0;
	}
	Graph g = malloc(sizeof(GraphRep));
	nbytes += sizeof(GraphRep);
	assert(g != NULL);
	g->nV = nV;  g->nE = 0;  g->edge = e;
	return g;
}

// insert a new edge into a graph (no effect if already there)
void insertE(Graph g, Edge e)
{
	assert(g != NULL && validV(g,e.src) && validV(g,e.dest));
	if (g->edge[e.src][e.dest]) return;
	g->edge[e.src][e.dest] = 1;
	g->nE++;
}

// remove an edge from a graph (no effect if not already there)
void removeE(Graph g, Edge e)
{
	assert(g != NULL && validV(g,e.src) && validV(g,e.dest));
	if (!g->edge[e.src][e.dest]) return;
	g->edge[e.src][e.dest] = 0;
	g->nE--;
}

#include "q3.c"

// scan edges from inf and use them to create a graph
// first line of inf says how many vertices, rest of inf is edges
Graph scan(FILE *inf)
{
	int nV = 0;
	fscanf(inf,"%d",&nV);
	assert(nV > 1);
	Graph g = newGraph(nV);
	Vertex s,d;
	while (fscanf(inf,"%d->%d",&s,&d) == 2)
		insertE(g, mkEdge(s,d));
	return g;
}

// display a graph
void show(Graph g)
{
	assert(g != NULL);
	printf("V=%d, E=%d\n", g->nV, g->nE);
	int i, j;
	for (i = 0; i < g->nV; i++) {
		int nshown = 0;
		for (j = 0; j < g->nV; j++) {
			if (g->edge[i][j] != 0) {
				printf("%d->%d  ",i,j);
				nshown++;
			}
		}
		if (nshown > 0) printf("\n");
	}
}
