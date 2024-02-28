#include "Board.h"
#include <random>
#include <iostream>

void InitMines(boolGrid mines, int numMines, int rows, int cols) {
	//initialize all mines to false
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			mines[i][j] = false;

	//create the RNG
	std::random_device randRowDevice;
	std::default_random_engine randRowGenerator(randRowDevice());
	std::uniform_int_distribution<int> randRowDistribution(0, (rows-1));

	std::random_device randColDevice;
	std::default_random_engine randColGenerator(randColDevice());
	std::uniform_int_distribution<int> randColDistribution(0, (cols-1));

	//place mines
	for (int n = 0; n < numMines; ++n) {
		int i = randRowDistribution(randRowGenerator);
		int j = randColDistribution(randColGenerator);
		if (!(mines[i][j])) 
			mines[i][j] = true;
	}
}

void InitBoard(boolGrid board, int rows, int cols) {
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			board[i][j] = false;
}

void ColWrapper(int cols) {
	system("CLS");
	std::cout << "   ";
	for (int i = 0; i < cols; i++) {
		std::cout << " " << i % 10 <<" ";
	}
	std::cout << std::endl << "   ";

	for (int i = 0; i < cols; i++) {
		std::cout << "---";
	}
	std::cout << std::endl;

}

void PrintMines(boolGrid mines, int rows, int cols) {
	ColWrapper(cols);
	for (int i = 0; i < rows; ++i) {
		std::cout << "" << i % 10 << " |";
		for (int j = 0; j < cols; ++j) {
			if (mines[i][j]) {
				std::cout << " X ";
			}
			else {
				std::cout << "   ";
			}
		}
		std::cout << std::endl;
	}
}

void PrintBoard(boolGrid board, boolGrid mines, int rows, int cols) {
	ColWrapper(cols);
	for (int i = 0; i < rows; ++i) {
		std::cout << "" << i % 10 << " |";
		for (int j = 0; j < cols; ++j) {
			if (!board[i][j]) {
				std::cout << " O ";
			}
			else if (mines[i][j]) {
				std::cout << " X ";
			}
			else {
				int numMines = CountAdjMines(mines, i, j, rows, cols);
				if (numMines == 0)
					std::cout << "   ";
				else
					std::cout << " " << numMines << " ";
			}
		}
		std::cout << std::endl;
	}
}

int CountAdjMines(boolGrid mines, int i, int j, int rows, int cols) {
	int count = 0;
	int rowMax = std::max(0, i - 1);
	int rowMin = std::min((rows - 1), (i + 1));
	int colMax = std::max(0, j - 1);
	int colMin = std::min((cols - 1), (j + 1));

	for (int k = rowMax; k <= rowMin; k++) {
		for (int l = colMax; l <= colMin; l++) {
			if (mines[k][l]) {
				count++;
			}
		}
	}
	return (count);
}

int Select(boolGrid board, boolGrid mines, int i, int j, int numMines, int rows, int cols) {
	static int numTries = 0;
	if (!board[i][j]) {
		board[i][j] = true;
		numTries++;
		if (!mines[i][j]) {
			int count = CountAdjMines(mines, i, j, rows, cols);
			if (count == 0) {
				for (int k = std::max(0, i - 1); k <= std::min(rows - 1, i + 1); k++)
					for (int l = std::max(0, j - 1); l <= std::min(cols - 1, j + 1); l++) {
						if (!board[k][l])
							Select(board, mines, k, l, numMines, rows, cols);
					}
			}
		}
		else 
			return -1;

		if (numTries == (rows*cols - numMines)) 
			return 1;
		else 
			return 0;
		
	}
	return 0;
}