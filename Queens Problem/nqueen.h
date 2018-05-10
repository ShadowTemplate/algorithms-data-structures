#ifndef NQUEEN_H_
#define NQUEEN_H_

#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

using std::vector;
using std::cout;
using std::endl;

struct Board
{
	int n_queens;
	vector<int> board;

	Board(int n = 4)
	{
		if (n > 20)
			n_queens = 20;
		else
			n_queens = n;

		board.resize(n_queens);

		board[0] = 0;

	}

	~Board()
	{
	}

	void printBoard()
	{
		static int num_solutions = 1;

		cout << "Solution # " << num_solutions << ":" << endl;
		for (int i = 0; i < n_queens; i++)
		{
			for (int j = 0; j < n_queens; j++)
				if (board[j] == i)
					cout << "Q ";
				else
					cout << "+ ";
			cout << endl;
		}
		cout << endl;

		num_solutions++;
	}
};

bool underAttack(int i, int j, int col, const Board& b)
{
	return (b.board[j] == i || abs(b.board[j] - i) == abs(col - j));
}

void insertQueens(Board& b, int col)
{

	if (col == b.n_queens)
		b.printBoard();
	else
	{
		int i, j;

		for (i = 0; i < b.n_queens; i++)
		{
			for (j = 0; j < col && !underAttack(i, j, col, b); j++) // Search the first available free position on that row
				;

			if (j >= col) // The queen isn't under attack
			{
				b.board[col] = i; // Insert the queen
				insertQueens(b, col + 1); // Try to add another queen
			}
		}
	}
}

void generateSolutions(Board& b)
{
	insertQueens(b, 0);
}

#endif /* NQUEEN_H_ */
