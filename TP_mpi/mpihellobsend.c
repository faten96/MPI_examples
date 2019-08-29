/******************************************************************************
* FILE: mpi_helloBsend.c
* DESCRIPTION:
*   MPI tutorial example code: Simple hello world program that uses blocking
*   send/receive routines.
******************************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER		0

int main (int argc, char *argv[])
{
int  nbprocess, processid, len, partner, message;
char hostname[MPI_MAX_PROCESSOR_NAME];
MPI_Status status;

MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &processid);
MPI_Comm_size(MPI_COMM_WORLD, &nbprocess);

/* need an even number of tasks  */
if (nbprocess % 2 != 0) {
   if (processid == MASTER) 
      printf("Quitting. Need an even number of tasks: nbprocess=%d\n", nbprocess);
   } 

else {
   if (processid == MASTER) 
      printf("MASTER: Number of MPI tasks is: %d\n",nbprocess);

   MPI_Get_processor_name(hostname, &len);
   printf ("Hello from task %d on %s!\n", processid, hostname);

   /* determine partner and then send/receive with partner */
   if (processid < nbprocess/2) {
     partner = nbprocess/2 + processid;
     MPI_Send(&processid, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
     MPI_Recv(&message, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
     }
   else if (processid >= nbprocess/2) {
     partner = processid - nbprocess/2;
     MPI_Recv(&message, 1, MPI_INT, partner, 1, MPI_COMM_WORLD, &status);
     MPI_Send(&processid, 1, MPI_INT, partner, 1, MPI_COMM_WORLD);
     }

   /* print partner info and exit*/
   printf("Process %d is partner with %d\n",processid,message);
   }

MPI_Finalize();

}

