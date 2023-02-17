

#include "SafeWaterMelon.h"

SafeWaterMelon::SafeWaterMelon()
{
	_board = new UnsafeWaterMelon();

	_movesCount = _board->GetPossibleMoves(_moves);
}

SafeWaterMelon::SafeWaterMelon(std::string FEN)
{
	_board = new UnsafeWaterMelon(FEN);
}

SafeWaterMelon::~SafeWaterMelon()
{
	delete _board;
}

bool SafeWaterMelon::MakeMove(Move move)
{
	move = TransfomMove(move);
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
	square = TransformSquareToUnsafe(square);
	return _board->board[square];
}

int SafeWaterMelon::GetPlayerColour()
{
	return _board->playerTurn;
}

void SafeWaterMelon::GetMovesCopy(Move* moves)
{
	memcpy_s(moves, MaxMoves * sizeof(Move), _moves, MaxMoves * sizeof(Move));
	for (size_t i = 0; i < _movesCount; i++)
	{
		moves[i] = TransfomMove(moves[i]);
	}
}

Move* SafeWaterMelon::GetMovePointer()
{
	return &_moves[0];
}

int SafeWaterMelon::GetMovesCount()
{
	return _movesCount;
}

void SafeWaterMelon::TurnBoard180()
{
	isBoardRotated180 = !isBoardRotated180;
}

UnsafeWaterMelon* SafeWaterMelon::GetUnsafeBoardPtr()
{
	return _board;
}



Move SafeWaterMelon::TransfomMove(Move move)
{
	return CreateMove(
		TransformSquareToHuman(GetMoveStart(move)),
		TransformSquareToHuman(GetMoveTarget(move)),
		GetMoveFlag(move)
	);
}

Square SafeWaterMelon::TransformSquareToUnsafe(Square square)
{
	Square s = FlipSquareY(square);
	if (isBoardRotated180)
		s = FlipSquareXY(s);
	return s;
}

Square SafeWaterMelon::TransformSquareToHuman(Square square)
{
	Square s = FlipSquareY(square);
	if (isBoardRotated180)
		s = FlipSquareXY(s);
	return s;
}
