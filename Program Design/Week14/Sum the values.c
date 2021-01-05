void star(int* x, int* y) {
	*y=0;

	for (int i=0;i<5;i++)
		*y+=*(x+i);
}
