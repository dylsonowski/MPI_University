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

	if (rank == 0) {
		printf("%s", buffer);
		for (int it = 1; it < size; it++) {
			MPI_Irecv(buffer, sizebuf, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &reciveRequest);
			MPI_Wait(&reciveRequest, &status);
			printf("%s", buffer);
		}
	}
	else {
			MPI_Isend(buffer, sizebuf, MPI_CHAR, 0, rank, MPI_COMM_WORLD, &sendRequest);
			MPI_Test(&sendRequest, &flag, MPI_STATUSES_IGNORE);
	}

	MPI_Finalize();
	return 0;
}