#pragma warning(disable : 4996)
#include "mpi.h"
#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

int main(int argc, char* argv[]) {
	std::string inputFile = "../../PCiDS_MPI_Project/data/infile1500_1200.bin";
	const unsigned int inputXDimention = 1500, inputYDimention = 1200;
	int rank, size;
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	std::cout << "Hello from process " << rank << " out of " << size << std::endl;

	if (rank == 0) {
		std::ifstream inputData(inputFile, std::ios::in | std::ifstream::binary);
		assert(inputData.good());

		std::vector<uint8_t> data((std::istreambuf_iterator<char>(inputData)), std::istreambuf_iterator<char>());
		inputData.close();
		std::cout << static_cast<unsigned int>(*std::max_element(data.begin(), data.end())) << std::endl;

		while (!data.empty()) {
			MPI_Bcast(&data, data.size(), MPI_UINT8_T, rank, MPI_COMM_WORLD);
		}
	}
	else {

	}

	MPI_Finalize();

	return 0;
}
