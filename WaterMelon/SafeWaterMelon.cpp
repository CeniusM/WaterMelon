

#include "SafeWaterMelon.h"

SafeWaterMelon::SafeWaterMelon()
{
	InitFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

SafeWaterMelon::SafeWaterMelon(std::string FEN)
{
	InitFEN(FEN);
}

SafeWaterMelon::~SafeWaterMelon()
{
	delete _board;
}

void SafeWaterMelon::InitFEN(std::string FEN)
{
	_board = new UnsafeWaterMelon(FEN);

	_movesCount = _board->GetPossibleMoves(_moves);
}

bool SafeWaterMelon::MakeMove(Move move)
{
	move = TransfomMove(move);
	for (int i = 0; i < _movesCount; i++)
	{
		if ((move & 0b111111111111) == (_moves[i] & 0b111111111111)) // not flags
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
	_board->UnMakeMove();
	LoadMoves();
	return false;
}

Piece SafeWaterMelon::GetSquare(Square square)
{
	if (square > 63 || square < 0)
		ThrowOutOfRangeException("Square out of range");
	square = TransformSquare(square);
	return _board->board[square];
}

Color SafeWaterMelon::GetPlayerColour()
{
	return _board->playerTurn;
}

void SafeWaterMelon::GetMovesCopy(Move* moves)
{
	memcpy_s(moves, MaxMovesCount * sizeof(Move), _moves, MaxMovesCount * sizeof(Move));
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
		TransformSquare(GetMoveStart(move)),
		TransformSquare(GetMoveTarget(move)),
		GetMoveFlag(move)
	);
}

Square SafeWaterMelon::TransformSquare(Square square)
{
	if (EnableSquareTransform)
	{
		Square s = FlipSquareY(square);
		if (isBoardRotated180)
			s = FlipSquareXY(s);
		return s;
	}
	else
		return square;
}

void SafeWaterMelon::LoadMoves(bool onlyCaptures)
{
	_movesCount = _board->GetPossibleMoves(_moves, onlyCaptures, false);
}
