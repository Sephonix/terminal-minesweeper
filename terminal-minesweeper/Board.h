#pragma once

typedef bool** boolGrid;

void InitMines(boolGrid mines, int numMines, int row, int col);
void InitBoard(boolGrid board, int rows, int cols);
void ColWrapper(int cols);
void PrintMines(boolGrid mines, int rows, int cols);
void PrintBoard(boolGrid board, boolGrid mines, int rows, int cols);
int CountAdjMines(boolGrid mines, int i, int j, int rows, int cols);
int Select(boolGrid board, boolGrid mines, int i, int j, int numMines, int rows, int cols);