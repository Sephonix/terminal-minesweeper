#include "Board.h"
#include <iostream>

using namespace std;
int main() {
	int result = 0;
	int rows = 10;
	int cols = 10;
	int numMines = 5;

	//Create the board and mines array
	boolGrid mines = new bool*[rows];
	boolGrid board = new bool*[rows];
	for (int i = 0; i < rows; ++i) {
		mines[i] = new bool[cols];
		board[i] = new bool[cols];
	}

	InitMines(mines, numMines, rows, cols);
	InitBoard(board, rows, cols);
	//ColWrapper(cols);
	PrintBoard(board, mines, rows, cols);

	//Game loop
	while (result == 0) {
		int i, j;
		PrintBoard(board, mines, rows, cols);
		cout << endl;
		cout << "Enter the row and column separated by a space. (e.x. 4 0) ";
		cin >> i >> j;
		result = Select(board, mines, i, j, numMines,rows, cols);
	}
	PrintMines(mines, rows, cols);
	if (result == -1)
		cout << "You Lose! :c";
	else
		cout << "You Win! :)";

	return 0;
}