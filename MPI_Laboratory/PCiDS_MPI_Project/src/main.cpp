#include "mpi.h"
#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(int argc, char* argv[]) {
	std::string inputFile = "data/infile1500_1200.bin";
	const unsigned int inputXDimention = 1500, inputYDimention = 1200;

	std::ifstream inputData(inputFile, std::ios::in | std::ifstream::binary);
	assert(inputData.good());

	std::vector<int> data((std::istreambuf_iterator<char>(inputData)), std::istreambuf_iterator<char>());

	int rank, size;
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	std::cout << "Hello from process " << rank << " out of " << size << std::endl;

	MPI_Finalize();

	return 0;
}
