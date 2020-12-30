int* Returns(int n) {
   int* ptr=(int*)malloc(n*sizeof(int));

  for (int i=0;i<n;i++)
     ptr[i]=i*i;

    return ptr; 
}
