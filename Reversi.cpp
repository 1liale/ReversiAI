#include "RaspberryPi.h"

#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <cmath>

using namespace std;
using namespace RaspberryPi;

class Board
{
	const int size = 8;
	vector<vector<int>> grid;
	set<pair<int, int>> black, white;
	int moves;
public:
	Board() : grid(8, vector<int>(8)) {}
	Board(int s) : size(s),
		grid(s, vector<int>(s)) {}
	int getSize() const { return size; }
	int getMoves() const { return moves; }
	int getStone(int row, int col) const
	{
		return grid[row][col];
	}
	bool hasMove() const
	{
		return !black.empty() || !white.empty();
	}
	bool hasMove(bool side) const
	{
		return !(side ? black : white).empty();
	}
	bool hasMove(int row, int col, bool side) const
	{
		return (side ? black : white).count({ row, col });
	}
	bool contain(int row, int col) const
	{
		return row >= 0 && row < size &&
			col >= 0 && col < size;
	}
	int countStones() const
	{
		int stones = 0;
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				stones += grid[i][j];
			}
		}
		return stones;
	}
	void findMoves(bool side)
	{
		(side ? black : white).clear();
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (canMove(i, j, side))
					(side ? black : white).insert({ i, j });
			}
		}
	}
	bool canMove(int row, int col, bool side) const
	{
		int colour = side ? 1 : -1;
		if (grid[row][col] != 0)
			return false;
		for (int i = 1; row - i >= 0; ++i)
		{
			if (grid[row - i][col] == 0)
				break;
			else if (grid[row - i][col] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; row + i < size; ++i)
		{
			if (grid[row + i][col] == 0)
				break;
			else if (grid[row + i][col] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; col - i >= 0; ++i)
		{
			if (grid[row][col - i] == 0)
				break;
			else if (grid[row][col - i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; col + i < size; ++i)
		{
			if (grid[row][col + i] == 0)
				break;
			else if (grid[row][col + i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; row - i >= 0 && col - i >= 0; ++i)
		{
			if (grid[row - i][col - i] == 0)
				break;
			else if (grid[row - i][col - i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; row + i < size && col - i >= 0; ++i)
		{
			if (grid[row + i][col - i] == 0)
				break;
			else if (grid[row + i][col - i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; row - i >= 0 && col + i < size; ++i)
		{
			if (grid[row - i][col + i] == 0)
				break;
			else if (grid[row - i][col + i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		for (int i = 1; row + i < size && col + i < size; ++i)
		{
			if (grid[row + i][col + i] == 0)
				break;
			else if (grid[row + i][col + i] == colour)
			{
				if (i > 1)
					return true;
				break;
			}
		}
		return false;
	}
	void makeMove(int row, int col, bool side)
	{
		int colour = side ? 1 : -1;
		grid[row][col] = colour;
		set<pair<int, int>> stones;
		for (int i = 1; row - i >= 0; ++i)
		{
			if (grid[row - i][col] == 0)
				break;
			else if (grid[row - i][col] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row - j][col] = colour;
					stones.insert({ row - j, col });
				}
				break;
			}
		}
		for (int i = 1; row + i < size; ++i)
		{
			if (grid[row + i][col] == 0)
				break;
			else if (grid[row + i][col] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row + j][col] = colour;
					stones.insert({ row + j, col });
				}
				break;
			}
		}
		for (int i = 1; col - i >= 0; ++i)
		{
			if (grid[row][col - i] == 0)
				break;
			else if (grid[row][col - i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row][col - j] = colour;
					stones.insert({ row, col - j });
				}
				break;
			}
		}
		for (int i = 1; col + i < size; ++i)
		{
			if (grid[row][col + i] == 0)
				break;
			else if (grid[row][col + i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row][col + j] = colour;
					stones.insert({ row, col + j });
				}
				break;
			}
		}
		for (int i = 1; row - i >= 0 && col - i >= 0; ++i)
		{
			if (grid[row - i][col - i] == 0)
				break;
			else if (grid[row - i][col - i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row - j][col - j] = colour;
					stones.insert({ row - j, col - j });
				}
				break;
			}
		}
		for (int i = 1; row + i < size && col - i >= 0; ++i)
		{
			if (grid[row + i][col - i] == 0)
				break;
			else if (grid[row + i][col - i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row + j][col - j] = colour;
					stones.insert({ row + j, col - j });
				}
				break;
			}
		}
		for (int i = 1; row - i >= 0 && col + i < size; ++i)
		{
			if (grid[row - i][col + i] == 0)
				break;
			else if (grid[row - i][col + i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row - j][col + j] = colour;
					stones.insert({ row - j, col + j });
				}
				break;
			}
		}
		for (int i = 1; row + i < size && col + i < size; ++i)
		{
			if (grid[row + i][col + i] == 0)
				break;
			else if (grid[row + i][col + i] == colour)
			{
				for (int j = 1; j < i; ++j)
				{
					grid[row + j][col + j] = colour;
					stones.insert({ row + j, col + j });
				}
				break;
			}
		}
		++moves;
	}
	void reset()
	{
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				grid[i][j] = 0;
			}
		}
		grid[size / 2][size / 2] = -1;
		grid[size / 2 - 1][size / 2] = 1;
		grid[size / 2][size / 2 - 1] = 1;
		grid[size / 2 - 1][size / 2 - 1] = -1;
		moves = 4;
	}
	void refresh(bool side) const
	{
		//system("cls");
		int black = 0, white = 0;
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				switch (grid[i][j])
				{
				case 1:
					cout << 'B' << ' '; ++black;
					break;
				case -1:
					cout << 'W' << ' '; ++white;
					break;
				case 0:
					cout << (hasMove(i, j, side) ? '@' : '#') << ' ';
					break;
				}
			}
			cout << endl;
		}
		cout << black << ' ' << white << endl;
		cout << (side ? 'B' : 'W') << endl;
	}
};

struct Player { virtual void play(Board& board, bool side) const = 0; };

struct Heuristic { virtual double operator()(const Board &board) const = 0; };

class Minimax : public Player
{
	const int maxDepth;
	const Heuristic *heuristic;
public:
	Minimax(int d, Heuristic *h) :
		maxDepth(d), heuristic(h) {}
	void play(Board& board, bool side) const
	{
		cout << maximize(board, side,
			maxDepth, -INFINITY, INFINITY) << endl;
	}
	double evaluate(const Board& board, bool side) const
	{
		int colour = side ? 1 : -1;
		if (!board.hasMove())
		{
			int stones = board.countStones();
			if (colour * stones > 0)
				return board.getSize() * board.getSize();
			else if (colour * stones < 0)
				return -board.getSize() * board.getSize();
			else
				return 0;
		}
		else
			return colour * (*heuristic)(board);
	}
	double maximize(Board& board, bool side, 
		int depth, double alpha, double beta) const
	{
		board.findMoves(side);
		if (!depth || !board.hasMove())
			return evaluate(board, side);
		if (!board.hasMove(side))
			return minimize(board, side, depth - 1, alpha, beta);
		int maxRow, maxCol;
		double maxScore = -INFINITY;
		for (int i = 0; i < board.getSize(); ++i)
		{
			for (int j = 0; j < board.getSize(); ++j)
			{
				if (board.hasMove(i, j, side))
				{
					Board newBoard = board;
					newBoard.makeMove(i, j, side);
					double score = minimize(newBoard, side, depth - 1, alpha, beta);
					if (score > maxScore)
					{
						maxScore = score;
						maxRow = i; maxCol = j;
					}
					alpha = max(alpha, maxScore);
					if (alpha >= beta)
						return maxScore;
				}
			}
		}
		board.makeMove(maxRow, maxCol, side);
		return maxScore;
	}
	double minimize(Board& board, bool side, 
		int depth, double alpha, double beta) const
	{
		board.findMoves(!side);
		if (!depth || !board.hasMove())
			return evaluate(board, side);
		int minRow, minCol;
		double minScore = INFINITY;
		if (!board.hasMove(!side))
			return maximize(board, side, depth - 1, alpha, beta);
		for (int i = 0; i < board.getSize(); ++i)
		{
			for (int j = 0; j < board.getSize(); ++j)
			{
				if (board.hasMove(i, j, !side))
				{
					Board newBoard = board;
					newBoard.makeMove(i, j, !side);
					double score = maximize(newBoard, side, depth - 1, alpha, beta);
					if (score < minScore)
					{
						minScore = score;
						minRow = i; minCol = j;
					}
					beta = min(beta, minScore);
					if (alpha >= beta)
						return minScore;
				}
			}
		}
		board.makeMove(minRow, minCol, !side);
		return minScore;
	}
};

class Console : public Player
{
public:
	void play(Board& board, bool side) const
	{
		int row, col;
		do
		{
			cin >> row >> col;
		} while (!board.contain(row, col) || !board.hasMove(row, col, side));
		board.makeMove(row, col, side);
	}
};

class Controller : public Player
{
	const int fileDesc;
public:
	Controller(int fd) : fileDesc(fd) {}
	void play(Board& board, bool side) const
	{
		auto map = getMap(board, side);
		pair<int, int> point;
		do
		{
			updateLED(map);
			point = padInput(fileDesc);
			//cout << point.first << ' ' << point.second << endl;
		} while (point.first == -1 || point.second == -1 || 
			!board.hasMove(point.first, point.second, side));
		cout << point.first << ' ' << point.second << endl;
		board.makeMove(point.first, point.second, side);
	}
	array<array<int, 8>, 8> getMap(const Board &board, bool side) const
	{
		array<array<int, 8>, 8> map;
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				if (board.getStone(i, j) == 1)
					map[i][j] = 1;
				else if (board.getStone(i, j) == -1)
					map[i][j] = -1;
				else if (board.hasMove(i, j, side))
					map[i][j] = side ? 2 : -2;
				else
					map[i][j] = 0;
			}
		}
		return map;
	}
};

class Game
{
	Board board;
	Player *black, *white;
public:
	Game(Player* b, Player* w) : 
		board(), black(b), white(w) {}
	void run()
	{
		board.reset();
		bool side = true;
		do
		{
			board.findMoves(side);
			board.refresh(side);
			if (board.hasMove(side))
				(side ? black : white)->play(board, side);
			side = !side;
			//system("pause");
		} while (board.hasMove());
		board.refresh(side ? 1 : -1);
		cout << board.countStones() << endl;
	}
};

struct Constant : public Heuristic
{
	double operator()(const Board& board) const
	{
		double sum = 0;
		for (int i = 0; i < board.getSize(); ++i)
		{
			for (int j = 0; j < board.getSize(); ++j)
			{
				sum += board.getStone(i, j);
			}
		}
		return sum;
	}
};

struct Root : public Heuristic
{
	double operator()(const Board& board) const
	{
		const double c = board.getSize() * board.getSize();
		double sum = 0;
		for (int i = 0; i < board.getSize(); ++i)
		{
			for (int j = 0; j < board.getSize(); ++j)
			{
				if ((i == 0 || i == board.getSize() - 1) &&
					(j == 0 || j == board.getSize() - 1))
				{
					sum += board.getStone(i, j);
				}
				else if (i == 0 || i == board.getSize() - 1 ||
					j == 0 || j == board.getSize() - 1)
				{
					sum += board.getStone(i, j) *
						sqrt(sqrt(board.getMoves() / c));
				}
				else
				{
					sum += board.getStone(i, j) *
						sqrt(board.getMoves() / c);
				}
			}
		}
		return sum;
	}
};

int test()
{
	Board board;
	board.reset();
	int fd = initComponent();
	if (fd == -1)
		return 1;
	Controller controller(fd);
	controller.play(board, true);
	return 0;
}

int main()
{
	Console console;
	Constant func1;
	Root func2;
	Minimax minimax1(8, &func1);
	Minimax minimax2(8, &func2);
	int fd = initComponent();
	if (fd == -1)
		return 1;
	Controller controller(fd);
	Game game(&controller, &minimax2);
	game.run();
	close(fd);
	return 0;
}

