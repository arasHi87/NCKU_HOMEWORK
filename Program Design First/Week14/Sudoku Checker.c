void check_sudoku(int (*grid_p)[NUM]){
	int arr[NUM][NUM], vis[NUM];

	for (int i=0;i<NUM;i++)
		for (int j=0;j<NUM;j++)
			arr[i][j]=0;
	
	for (int sx=0, sy=0;sx<NUM && sy<NUM;) {
		for (int i=0;i<NUM;i++)
			vis[i]=0;

		/* printf("%d %d\n", sx, sy); */
		for (int i=sx;i<sx+3;i++)
			for (int j=sy;j<sy+3;j++) {
				vis[(i-sx)*3+j-sy]=grid_p[i][j];

				for (int k=0;k<NUM;k++)
					if (vis[k]==grid_p[i][j] && ((i-sx)*3+j-sy)!=k)
						arr[i][j]=1, arr[k/3+sx][k%3+sy]=1;
			}
		sy+=3;

		if (sy>6) sx+=3, sy=0;
	}

	for (int i=0;i<NUM;i++) {
		for (int j=0;j<NUM;j++) {
			for (int k=i+1;k<NUM;k++)
				if (grid_p[i][j]==grid_p[k][j])
					arr[i][j]=1, arr[k][j]=1;
			for (int k=j+1;k<NUM;k++)
				if (grid_p[i][j]==grid_p[i][k])
					arr[i][j]=1, arr[i][k]=1;	
		}
	}

	for (int i=0;i<NUM;i++)
		for (int j=0;j<NUM;j++)
			if (arr[i][j])
				printf("(%d,%d)\n", i, j);
}
