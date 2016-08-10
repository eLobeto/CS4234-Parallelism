#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Min(a, b) (a > b ? b : a)

int main(int argc, char *argv[])
{
   int myid, numprocs, numcol;
   char* fileA, fileB;
   int  i,j, k, count;
   double mintime, global_min;
   int dim;
   double* matrixA;
   double* matrixB;
   double* matrixC;
   double* tempA;
   double* result;
   clock_t begin, end;
   MPI_Status status;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD,&myid);

   count = 1;

   dim = strtol(argv[1], NULL, 10);
   numcol = dim/numprocs;
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

   //start timing
   MPI_Barrier(MPI_COMM_WORLD);
   begin = clock();

   for(count = 0; count < numprocs; count++){
    //column
    for(k = 0; k < numcol; k++){//C column
      for(j = 0; j < numcol; j++){//A column  
        for(i = 0; i < dim; i++){ //row
          matrixC[k*dim+i] = matrixC[k*dim+i] + tempA[j*dim+i] * matrixB[((myid+count)%numprocs)*numcol+k*dim+j];
        }
      }
    }
    //pass to the left, receive from the right
    //odds send to even
    int pass = myid - 1;
    int recv = (myid + 1) % numprocs;
    if(pass < 0)
      pass = numprocs - 1;

    if(numprocs > 1)
    {
      if(myid%2 == 0)
      {
        MPI_Send(tempA, numcol * dim, MPI_DOUBLE, pass, 0, MPI_COMM_WORLD);  
        MPI_Recv(matrixA, numcol * dim, MPI_DOUBLE, recv, 0, MPI_COMM_WORLD, &status);
      }
      else
      {
        MPI_Recv(matrixA, numcol * dim, MPI_DOUBLE, recv, 0, MPI_COMM_WORLD, &status);
        MPI_Send(tempA, numcol * dim, MPI_DOUBLE, pass, 0, MPI_COMM_WORLD);
      }

      int something;
      for(something = 0; something < dim*numcol; something++){
        tempA[something] = matrixA[something];
      }
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
}