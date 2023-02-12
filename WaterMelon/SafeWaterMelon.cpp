

#include "SafeWaterMelon.h"

SafeWaterMelon::SafeWaterMelon()
{
	_board = new UnsafeWaterMelon();
}

SafeWaterMelon::~SafeWaterMelon()
{
	delete _board;
}

bool SafeWaterMelon::MakeMove(Move move)
{
	for (int i = 0; i < _movesCount; i++)
	{
		//if (GetMoveStart(move) == GetMoveStart(_moves[i]) &&
		//	GetMoveTarget(move) == GetMoveTarget(_moves[i]) &&
		//	GetMoveFlag(move) == GetMoveFlag(_moves[i]))
		if ((move & 0b1111111111111) == (_moves[i] & 0b1111111111111)) // not flags
		{
			move = _moves[i]; // Get flag
			_board->MakeMove(move);
			_movesCount = _board->GetPossibleMoves(_moves);

			return true;
		}
	}
	return false;
}

bool SafeWaterMelon::UnMakeMove()
{
	return false;
}

int SafeWaterMelon::GetSquare(int square)
{
	if (square > 63 || square < 0)
		ThrowOutOfRangeException("Square out of range");

	return _board->board[square];
}

int SafeWaterMelon::GetPlayerColour()
{
	return _board->playerTurn;
}

void SafeWaterMelon::GetMovesCopy(Move* moves)
{
	memcpy_s(moves, MaxMoves * sizeof(Move), _moves, MaxMoves * sizeof(Move));
}

Move* SafeWaterMelon::GetMovePointer()
{
	return &_moves[0];
}

int SafeWaterMelon::GetMovesCount()
{
	return _movesCount;
}

UnsafeWaterMelon* SafeWaterMelon::GetUnsafeBoardPtr()
{
	return _board;
}