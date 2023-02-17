#pragma once

#include "UnsafeWaterMelon.h"

class PerftRunner
{
public:
	PerftRunner(UnsafeWaterMelon* board);
	~PerftRunner();

	UnsafeWaterMelon* boardPtr;

	long GoPerft(int depth);


private:

};

PerftRunner::PerftRunner(UnsafeWaterMelon* board)
{
	boardPtr = board;
}

PerftRunner::~PerftRunner()
{
}

long PerftRunner::GoPerft(int depth)
{
	long Count;

	Move moves[256];
	int movesCount = boardPtr->GetPossibleMoves(moves);

	for (int i = 0; i < movesCount; i++)
	{
		//boardPtr->
	}





	return Count;
}
