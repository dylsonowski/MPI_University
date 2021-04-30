#include <iostream>
#include <sstream>
#include "mpi.h"

int main(int argc, char **argv)
{
	MPI_Request sendRequest, reciveRequest;
	MPI_Status status;
	int rank, size, flag;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	const int sizebuf = 150;
	char buffer[sizebuf];
	sprintf_s(buffer, "Hello from process %d out of %d\n", rank, size);

	//MPI_Barrier(MPI_COMM_WORLD);
	MPI_Isend(buffer, sizebuf, MPI_CHAR, 0, rank, MPI_COMM_WORLD, &sendRequest);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) {
		//MPI_Barrier(MPI_COMM_WORLD);
		printf("%s", buffer);
		//MPI_Barrier(MPI_COMM_WORLD);
		for (int it = 1; it < size; it++) {
			//MPI_Barrier(MPI_COMM_WORLD);
			MPI_Irecv(buffer, sizebuf, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &reciveRequest);
			//MPI_Test(&reciveRequest, &flag, MPI_STATUSES_IGNORE);
			printf("%s", buffer);
		}
	}
		
		//MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();
	return 0;
}