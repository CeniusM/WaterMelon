#include "StabilityTest.h"


bool CheckTime(time_point<steady_clock>& start, unsigned long long TimeAllowedToThink)
{
	duration<long long, std::milli>  timeSpent = duration_cast<milliseconds>(high_resolution_clock::now() - start);
	return TimeAllowedToThink > timeSpent.count();
}

// Prints all the info need for debugging
void Failed(std::string message, MoveStack movesStack, UnsafeWaterMelon& board)
{

}

// Later implement it so test by using stockfish and comparing
int DoPerft(int startDepth, UnsafeWaterMelon* startBoard, int depth, MoveStack& movesMade, UnsafeWaterMelon* board)
{
	if (board == nullptr)
	{
		// Start of perft, make copy of startBoard
	}

	return 0;
}

void StartStabilityTest(unsigned long long TimeAllowedToTestms)
{
	steady_clock::time_point c;
	srand(duration_cast<milliseconds>(high_resolution_clock::now() - c).count());

	MoveStack movesMade;

	time_point<steady_clock> start, end;
	start = high_resolution_clock::now();

	UnsafeWaterMelon* board = new UnsafeWaterMelon{};
	int movesToNextPerft = 4;
	Move moves[MaxMovesCount];

	while (CheckTime(start, TimeAllowedToTestms))
	{
		int count = board->GetPossibleMoves(moves);
		if (count == 0)
		{
			// Reset board
			delete board;
			board = new UnsafeWaterMelon{};
			while (movesMade.GetCount() != 0)
				movesMade.Pop();
			movesToNextPerft = 20;
			continue;
		}
		
		if (movesToNextPerft == 0)
		{
			DoPerft(3, board, 3, movesMade, nullptr);
			movesToNextPerft = 4;
			continue;
		}

		// Do move
		

		movesToNextPerft--;
	}
}

































#pragma region Code
MoveName::MoveName()
{
	move = 0;
	name[0] = 'n';
	name[1] = 'u';
	name[2] = 'l';
	name[3] = 'l';
	name[4] = '\0';
}

MoveName::MoveName(Move move)
{
	SetMove(move);
}

void MoveName::SetMove(Move move)
{
	this->move = move;

	int startSquare = GetMoveStart(move);
	int targetSquare = GetMoveTarget(move);

	int startX = GetRank(FlipSquareY(startSquare));
	int startY = GetCollum(startSquare);

	int targetX = GetRank(FlipSquareY(targetSquare));
	int targetY = GetCollum(targetSquare);

	name[0] = 'a' + startY;
	name[1] = '0' + startX;
	name[2] = 'a' + targetY;
	name[3] = '0' + targetX;
}

Move MoveName::GetMove()
{
	return move;
}

std::string MoveName::GetName()
{
	return std::string(name);
}


MoveStack::MoveStack()
{
	_capacity = 10;
	_count = 0;
	moves = new MoveName[_capacity];
}

MoveStack::~MoveStack()
{
	delete[] moves;
}

void MoveStack::Push(Move move)
{
	if (_count == _capacity)
	{
		_capacity *= 3;
		MoveName* newMoves = new MoveName[_capacity];
		for (size_t i = 0; i < _count; i++)
			newMoves[i] = moves[i];
		delete[] moves;
		moves = newMoves;
	}
	moves[_count++] = MoveName{ move };
}

MoveName MoveStack::Pop()
{
	if (_count == 0)
		ThrowInvalidArgumentException("Can not pop when there is 0 items left");
	return moves[--_count];
}

inline MoveName MoveStack::GetAt(int index)
{
	if (index < 0 || index >= _count)
		ThrowInvalidArgumentException("Index out of bounds");
	return moves[index];
}

inline int MoveStack::GetCount()
{
	return _count;
}
#pragma endregion
