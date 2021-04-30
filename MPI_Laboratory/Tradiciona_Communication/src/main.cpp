#include <iostream>
#include <sstream>
#include "mpi.h"

int main(int argc, char **argv)
{
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	const int sizebuf = 150;
	char buffer[sizebuf];
	sprintf_s(buffer, "Hello from process %d out of %d\n", rank, size);

	if (rank == 0) {
		printf("%s", buffer);
		for (int it = 1; it < size; it++) {
			MPI_Recv(buffer, sizebuf, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			printf("%s", buffer);
		}
	}
	else
		MPI_Send(buffer, sizebuf, MPI_CHAR, 0, rank, MPI_COMM_WORLD);

	MPI_Finalize();
	return 0;
}