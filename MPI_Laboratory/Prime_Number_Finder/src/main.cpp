#include <iostream>
#include <string>
#include <math.h>
#include "mpi.h";

bool IsPrime(int value);

int main(int argc, char** argv) {
	try {
		if (argc <= 1)
			throw 401;

		int rank, size, lowerRange, upperRange, interval;
		MPI_Init(&argc, &argv);
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		while (true) {
			if (rank == 0) {
				for (int it = 0; it < argc; it++) {
					if (static_cast<std::string>(argv[it]) == "-d")
						lowerRange = std::stoi(argv[it + 1]);

					if (static_cast<std::string>(argv[it]) == "-u")
						upperRange = std::stoi(argv[it + 1]);
				}

				interval = ceil(abs(upperRange - lowerRange) / (size - 1));
			}

		}
		MPI_Finalize();
	}
	catch (int messageCode) { std::cout << "ERROR" << messageCode << "\n"; }
	return 0;
}

bool IsPrime(int value) {
	if (value % 2 == 0)
		return false;

	for (int it = 3; it < sqrt(value); it += 2) {
		if (value % it == 0)
			return false;
	}

	return true;
}