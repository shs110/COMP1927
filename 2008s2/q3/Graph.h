// Graph.h ... directed graph interface

typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct { Vertex src; Vertex dest; } Edge;
Edge mkEdge(Vertex, Vertex);

// graph representation is hidden
typedef struct graphRep *Graph;

// operations on graphs
Graph newGraph(int nV);  // #vertices
void  insertE(Graph g, Edge e);
void  removeE(Graph g, Edge e);
int   celeb(Graph g);
Graph scan(FILE *inf);
void  show(Graph g);

