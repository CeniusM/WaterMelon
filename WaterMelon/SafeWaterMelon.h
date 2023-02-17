#pragma once

#include "UnsafeWaterMelon.h"

class SafeWaterMelon
{
public:
	SafeWaterMelon();
	~SafeWaterMelon();

	bool MakeMove(Move move);
	bool UnMakeMove();

	Piece GetSquare(Square square);
	Color GetPlayerColour();
	void GetMovesCopy(Move* moves);
	Move* GetMovePointer();
	int GetMovesCount();
	//void TurnBoard180();
	//bool IsKingInCheck();

	UnsafeWaterMelon* GetUnsafeBoardPtr();

private:
	UnsafeWaterMelon* _board;
	Move _moves[MaxMovesCount];
	int _movesCount = 0;
};