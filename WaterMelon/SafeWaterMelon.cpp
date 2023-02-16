

#include "SafeWaterMelon.h"

SafeWaterMelon::SafeWaterMelon()
{
	//_board = new UnsafeWaterMelon();
	_board = new UnsafeWaterMelon("k7/4r2q/8/3PPB2/1r1PK3/8/1P6/b7 w - - 0 1");

	_movesCount = _board->GetPossibleMoves(_moves);
}

SafeWaterMelon::~SafeWaterMelon()
{
	delete _board;
}

bool SafeWaterMelon::MakeMove(Move move)
{
	for (int i = 0; i < _movesCount; i++)
	{
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