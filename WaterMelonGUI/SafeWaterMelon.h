#pragma once
#include <iostream>
#include <stdexcept>

#include "UnsafeWaterMelon.h"

class SafeWaterMelon
{
public:
	SafeWaterMelon();
	~SafeWaterMelon();

	bool MakeMove(Move move);
	bool UnMakeMove();

	int GetPos(int pos);
	int GetPlayerColour();
	void GetMovesCopy(Move* moves);
	Move* GetMovePointer();
	int GetMovesCount();
	//bool IsKingInCheck();

	UnsafeWaterMelon* GetUnsafeBoardPtr();

private:
	UnsafeWaterMelon* _board;
	Move _moves[256];
	int _movesCount = 0;
};