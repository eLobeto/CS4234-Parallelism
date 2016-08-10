#include "mpi.h"
#include <stdlib.h>

void Vector_sum(double x[], double y[], double z[], int n)
{
  int elemsPerProc = n / comm_sz;
  int extraElems = n % comm_sz;

  //create recv buffers
  double* recvbuffx = (double *) calloc((elemsPerProc + extraElems), sizeof(double));
  double* recvbuffy = (double *) calloc((elemsPerProc + extraElems), sizeof(double));
  double* sumBuff = (double *) calloc((elemsPerProc + extraElems), sizeof(double));
    
  //create sendcounts array
  int* displs = (int *) malloc(sizeof(int) * numprocs);
   int* sendcounts = (int *) malloc(sizeof(int) * numprocs);
   int ctr = 0;
   for(ctr; ctr < numprocs; ctr++)
   {
      //populate sendcounts
      if(myid < extraElems)
      {
         sendcounts[ctr] = elemsPerProc + 1;
         displs[ctr] = elemsPerProc + 1;
      }
      else
      {
         sendcounts[ctr] = elemsPerProc;
         displs[ctr] = elemsPerProc; 
      }
   }

  //scatters elements
  MPI_Scatterv(x, sendcounts, displs, MPI_Double, recvbuffx, elemsPerProc + extraElems, 
      MPI_Double, 0, MPI_COMM_WORLD);
  MPI_Scatterv(y, sendcounts, displs, MPI_Double, recvbuffy, elemsPerProc + extraElems, 
      MPI_Double, 0, MPI_COMM_WORLD);

  //perform summation
  //sum master with extra elems
  if(myid == 0)
  {
    int sumCtrM = 0;
    for(sumCtrM; sumCtrM < elemsPerProc + extraElems; sumCtr++)
    {
      sumBuff[sumCtrM] = recvbuffx[sumCtrM] + recvbuffy[sumCtrM];
    }
  }
  //sum with normal amount of elements
  else
  {
    int sumCtr = 0;
    for(sumCtr; sumCtr < elemsPerProc; sumCtr++)
    {
      sumBuff[sumCtr] = recvbuffx[sumCtr] + recvbuffy[sumCtr];
    }
  }

  //gather elements
  MPI_Gatherv(sumBuff, elemsPerProc + extraElems, MPI_Double, z, 
      sendcounts, displs, MPI_Double, 0, MPI_COMM_WORLD);

  free(sendcounts);
  free(displs);
  free(recvbuffy);
  free(recvbuffy);
  free(sumBuff);

  MPI_Finalize();
}