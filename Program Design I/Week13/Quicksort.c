void quicksort(int a[], int low, int high) {
	int i=low, j=high, pivot=a[(low+high)>>1], tmp;
	
	while (i<=j) {
		while (a[i]<pivot) i++;
		while (a[j]>pivot) j--;

		if (i<=j) tmp=a[i], a[i]=a[j], a[j]=tmp, i++, j--;	
	}	
	
	if (i<high) quicksort(a, i, high);
	if (j>low) quicksort(a, low, j);
}
