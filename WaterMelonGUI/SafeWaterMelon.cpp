

#include "SafeWaterMelon.h"

SafeWaterMelon::SafeWaterMelon()
{
	_board = new UnsafeWaterMelon();
	_movesGenerator = new PossibleMovesGenerator(_board);
	_movesGenerator->GenerateMoves();
	_movesGenerator->GetMovesCopy(_moves);
	_movesCount = _movesGenerator->GetCount();
}

SafeWaterMelon::~SafeWaterMelon()
{
	delete _board;
	delete _movesGenerator;
}

bool SafeWaterMelon::MakeMove(Move move)
{
	for (int i = 0; i < _movesCount; i++)
	{
		//if (GetMoveStart(move) == GetMoveStart(_moves[i]) &&
		//	GetMoveTarget(move) == GetMoveTarget(_moves[i]) &&
		//	GetMoveFlag(move) == GetMoveFlag(_moves[i]))
		if (move == _moves[i])
		{
			_board->MakeMove(move);
			_movesGenerator->GenerateMoves();
			_movesGenerator->GetMovesCopy(_moves);
			_movesCount = _movesGenerator->GetCount();

			return true;
		}
	}
	return false;
}

bool SafeWaterMelon::UnMakeMove()
{
	return false;
}

int SafeWaterMelon::GetPos(int pos)
{
	if (pos > 63 || pos < 0)
		throw std::out_of_range("pos out of range");

	return _board->board[pos];
}

int SafeWaterMelon::GetPlayerColour()
{
	return _board->playerTurn;
}

void SafeWaterMelon::GetMovesCopy(Move* moves)
{
	_movesGenerator->GetMovesCopy(moves);
}

Move* SafeWaterMelon::GetMovePointer()
{
	return &_moves[0];
}

int SafeWaterMelon::GetMovesCount()
{
	return _movesGenerator->GetCount();
}

bool SafeWaterMelon::IsKingInCheck()
{
	return _movesGenerator->KingInCheck;
}

UnsafeWaterMelon* SafeWaterMelon::GetUnsafeBoardPtr()
{
	return _board;
}

PossibleMovesGenerator* SafeWaterMelon::GetUnsafeGeneratorPtr()
{
	return _movesGenerator;
}
