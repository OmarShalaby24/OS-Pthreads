#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#define MAX 4


void *mult(void* arg)
{
	int *data = (int *)arg;
	int k = 0, i = 0;

	int x = data[0];
	for (i = 1; i <= x; i++)
		k += data[i]*data[i+x];

	int *p = (int*)malloc(sizeof(int));
		*p = k;

	pthread_exit(p);
}

int main()
{
    clock_t element_time,row_time;
    FILE *fp = fopen("input.txt","r");
    printf("Matrix 1\n");
    char row[9],col[9];
    fscanf(fp,"%s %s",row,col);
    int row1 = atoi(row);
    int col1 = atoi(col);
    printf("row = %d ",row1);
    printf("col = %d\n",col1);

    int matrix_1[row1][col1];
    int i,j;
    char temp[10];
    for(i=0;i<row1;i++)
    {
        for(j=0;j<col1;j++)
        {
            fscanf(fp,"%s",temp);
            matrix_1[i][j] = atoi(temp);
        }
    }
    for(i=0;i<row1;i++)
    {
        for(j=0;j<col1;j++)
        {
            printf("%d ",matrix_1[i][j]);
        }
        printf("\n");
    }

    printf("Matrix 2\n");

    fscanf(fp,"%s %s",row,col);
    int row2 = atoi(row);
    int col2 = atoi(col);
    printf("row = %d ",row2);
    printf("col = %d\n",col2);
    int matrix_2[row2][col2];

    for(i=0;i<row2;i++)
    {
        for(j=0;j<col2;j++)
        {
            fscanf(fp,"%s",temp);
            matrix_2[i][j] = atoi(temp);
        }
    }
    for(i=0;i<row2;i++)
    {
        for(j=0;j<col2;j++)
        {
            printf("%d ",matrix_2[i][j]);
        }
        printf("\n");
    }
    fclose(fp);


	int r1=row1,c1=col1,r2=row2,c2=col2,k;


	int max = r1*c2;



	double time_taken,sum;
    element_time = clock();
	pthread_t *threads;
	threads = (pthread_t*)malloc(max*sizeof(pthread_t));

	int count = 0;
	int* data = NULL;
	for (i = 0; i < r1; i++){
		for (j = 0; j < c2; j++)
			{
			data = (int *)malloc((max)*sizeof(int));
			data[0] = c1;

			for (k = 0; k < c1; k++)
				data[k+1] = matrix_1[i][k];

			for (k = 0; k < r2; k++)
				data[k+c1+1] = matrix_2[k][j];


				pthread_create(&threads[count++], NULL,mult, (void*)(data));
            }
    }

	printf("RESULTANT MATRIX IS :- \n");

	FILE *fout = fopen("output.txt","w");
	for (i = 0; i < max; i++)
	{
	void *k;

	pthread_join(threads[i], &k);
    element_time = clock()-element_time;
    time_taken = ((double)element_time)/CLOCKS_PER_SEC;


		int *p = (int *)k;
	printf("%d ",*p);
	fprintf(fout,"%d ",*p);
	if ((i + 1) % c2 == 0)
    {
        fprintf(fout,"\n");
		printf("\n");
    }
	}
	fclose(fout);
    printf("\nElapsed time = %f seconds \n",time_taken);



return 0;
}
