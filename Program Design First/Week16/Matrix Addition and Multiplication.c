void add_mat(const struct mat *m1_p, const struct mat *m2_p, struct mat *result_p) { // matrix addition
    result_p->row=m1_p->row;
    result_p->col=m1_p->col;

    for (int i=0;i<m1_p->row;i++)
        for (int j=0;j<m1_p->col;j++)
            result_p->value[i][j]=(m1_p->value[i][j]+m2_p->value[i][j]);
}

void mul_mat(const struct mat *m1_p, const struct mat *m2_p, struct mat *result_p) { // matrix multiplication
    result_p->row=m1_p->row;
    result_p->col=m2_p->col;
    
    for (int i=0;i<result_p->row;i++)
        for (int j=0;j<result_p->col;j++)
            result_p->value[i][j]=0;

    for (int i=0;i<m1_p->row;i++)
        for (int j=0;j<m2_p->col;j++)
            for (int k=0;k<m1_p->col;k++)
                result_p->value[i][j]+=m1_p->value[i][k]*m2_p->value[k][j];
}
