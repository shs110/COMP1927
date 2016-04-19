// return index of celebrity in given graph
int celeb(Graph g)
{
	int i, c;
	// elimination phase
	c = 0;
	for (i = 1; i < g->nV; i++) {
		if (g->edge[c][i]) c = i;  // try i as celebrity
	}
	// testing phase
	int knows = 0, knownBy = 0;
	for (i = 0; i < g->nV; i++) {
		if (g->edge[c][i]) knows++;
		if (g->edge[i][c]) knownBy++;
	}
	return (knows == 0 && knownBy == g->nV-1) ? c : -1;
}
