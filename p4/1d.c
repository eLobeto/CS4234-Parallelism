#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

double* tempA;
int numprocs, numthreads;
clock_t begin, end;

void* multiply(void* args);

typedef struct{
	int* par;
	double* ptempA;
	double* pmatrixB;
	double* pmatrixC;
}parameter;


int main(int argc, char *argv[])
{
   int myid, numcol;
   int  i,j, count;
   double mintime, global_min;
   int dim;
   double* matrixA;
   double* matrixB;
   double* matrixC;
   double* result;
   MPI_Status status;
   MPI_Request request1, request2;

   //process run time parameters

   dim = strtol(argv[1], NULL, 10);
   numthreads = strtol(argv[2], NULL, 10);

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD,&myid);

   //checks if the dim is valid
   if(dim%numprocs != 0){
	printf("Dimension must be divisible by numprocs. Please try again\n");
	MPI_Finalize();
	return 0;
   }
   count = 1;
   numcol = dim/numprocs;
	//test fail cases dim 16 8 threads
   if(numcol%numthreads != 0){
	   printf("You entered an invalid number of threads. Please Try again\n");
	   MPI_Finalize();
	   return 0;
   }

   result = (double*)malloc(dim*dim*sizeof(double));
   matrixA = (double*)malloc(dim*numcol*sizeof(double));
   tempA = (double*)malloc(dim*numcol*sizeof(double));
   matrixB = (double*)malloc(dim*numcol*sizeof(double));
   matrixC = (double*)malloc(dim*numcol*sizeof(double));
   for(i = 0; i < dim*numcol; i++){
    matrixA[i] = myid+1;
    matrixB[i] = myid;
    matrixC[i] = 0;
   }

   for(i = 0; i < dim*numcol; i++){
      tempA[i] = matrixA[i];
   }

   //number of processors per node
   //start timing
   MPI_Barrier(MPI_COMM_WORLD);
   begin = clock();
   for(count = 0; count < numprocs; count++){

   //create p-threads
   //create parameters
	  int* pam = malloc(sizeof(int)*4);
    pam[0] = myid;
    pam[1] = dim;
    pam[2] = numcol;
    pam[3] = count;
	  parameter * parm = malloc(sizeof(parameter));
  	parm->par = pam;
  	parm->ptempA = tempA;
  	parm->pmatrixB = matrixB;
  	parm->pmatrixC = matrixC;

    #pragma omp parallel num_threads(numthreads)
    multiply(parm);


    //pass to the left, receive from the right
    int pass = myid - 1;
    int recv = (myid + 1) % numprocs;
    if(pass < 0)
      pass = numprocs - 1;

    MPI_Irecv(matrixA, numcol * dim, MPI_DOUBLE, recv, 0, MPI_COMM_WORLD, &request1);
    MPI_Isend(tempA, numcol * dim, MPI_DOUBLE, pass, 0, MPI_COMM_WORLD, &request2);

    MPI_Wait(&request1, &status);
    MPI_Wait(&request2, &status);

    int something;
    for(something = 0; something < dim*numcol; something++){
      tempA[something] = matrixA[something];
    }  
  }

  MPI_Allgather(matrixC, dim*numcol, MPI_DOUBLE, result, dim*numcol, MPI_DOUBLE, MPI_COMM_WORLD);
  
  end = clock();
  mintime = (double)(end - begin) / CLOCKS_PER_SEC;
  MPI_Reduce(&mintime, &global_min, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
  if(myid == 0){
    printf("%lf\n", global_min);
    FILE* fp;
    fp = fopen("output.txt","w");
    for(i = 0; i < dim; i++){
      for(j = 0; j < dim; j++)
      {
        fprintf(fp,"%lf\t",result[j * dim + i]);
      }
      fprintf(fp, "\n");
    }
  }

  free(tempA);
  free(matrixA);
  free(matrixB);
  free(matrixC);
  free(result);

  MPI_Finalize();
  return 0;
}

//we need numcol, dim, myid, count
void* multiply(void* arg){
  parameter *parm = (parameter*)arg;
  int k, j , i, counter;
  int threadnum = omp_get_thread_num();
  int myid = parm->par[0];
  int dim = parm->par[1];
  int numcol = parm->par[2];
  int count = parm->par[3];
  int mycol = threadnum*numcol/numthreads;
  int mynumcol = numcol/numthreads;
  k = mycol;
  /**for(i = 0; i < mynumcol*dim; i++){
	//printf("%d\t%d\n",myid,threadnum);
	printf("%lf\t",parm->ptempA[mycol*dim+i]);
	printf("%lf\t",parm->pmatrixB[mycol*dim+i]);
	printf("%lf\n",parm->pmatrixC[mycol*dim+i]);
  }*/

  for(counter = 0; counter < mynumcol; counter++){//C column
      for(j = 0; j < numcol; j++){//A column  
        for(i = 0; i < dim; i++){ //row
          parm->pmatrixC[k*dim+i] = parm->pmatrixC[k*dim+i] + parm->ptempA[j*dim+i] * parm->pmatrixB[((myid+count)%numprocs)*numcol+k*dim+j];
          if(0){
            printf("%d-%d-%d: %lf * %lf => %lf\n",myid,threadnum,count,parm->ptempA[j*dim+i],parm->pmatrixB[((myid+count)%numprocs)*numcol+k*dim+j],parm->pmatrixC[k*dim+i]);
		printf("%d-%d\n",mycol,mynumcol);
	  }
       }
     }
     k++;
   }
   return NULL;
}
