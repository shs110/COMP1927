// main.c - manipulate Graphs

#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

int main(int argc, char *argv[])
{
	Graph myGraph = scan(stdin);
	printf("Graph: "); show(myGraph);
	int c = celeb(myGraph);
	if (c < 0)
		printf("Graph has no celebrities\n");
	else
		printf("Graph has %d as a celebrity\n", c);
	return 0;
}
