int change(char* graph, char meow, int x, int y) {
	if (graph[x*N+y]=='X' || graph[x*N+y]==meow)
		return graph[x*N+y]=meow;

	return 0;
}

void spread(char* graph, int row, int col) {
	char meow=graph[row*N+col];
	
	for (int i=col;i<N;i++)
		if (!change(graph, meow, row, i))
			break;
	for (int i=col;i>=0;i--)
		if (!change(graph, meow, row, i))
			break;
	for (int i=row;i<M;i++)
		if (!change(graph, meow, i, col))
			break;
	for (int i=row;i>=0;i--)
		if (!change(graph, meow, i, col))
			break;
}
