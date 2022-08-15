#pragma once
#include <iostream>
#include <stdexcept>

#include "UnsafeWaterMelon.h"
#include "PossibleMovesGenerator.h"


class SafeWaterMelon
{
public:
	SafeWaterMelon();
	~SafeWaterMelon();

	bool MakeMove(Move move);
	bool UnMakeMove();

	int GetPiece(int pos);
	int GetPlayerColour();
	void GetMoves(Move* moves);
	int GetMovesCount();
	bool IsKingInCheck();

	UnsafeWaterMelon* GetUnsafeBoardPtr();
	PossibleMovesGenerator* GetUnsafeGeneratorPtr();

private:
	UnsafeWaterMelon* _board;
	PossibleMovesGenerator* _movesGenerator;
	Move _moves[256];
	int Count = 0;


};