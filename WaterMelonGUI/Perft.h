#pragma once

#include "PossibleMovesGenerator.h"

class PerftRunner
{
public:
	PerftRunner(UnsafeWaterMelon* board, PossibleMovesGenerator* generator);
	~PerftRunner();

	UnsafeWaterMelon* boardPtr;
	PossibleMovesGenerator* generatorPtr;
	Move* generatorMovesPtr;

	long GoPerft(int depth);


private:

};

PerftRunner::PerftRunner(UnsafeWaterMelon* board, PossibleMovesGenerator* generator)
{
	boardPtr = board;
	generatorPtr = generator;
}

PerftRunner::~PerftRunner()
{
}

long PerftRunner::GoPerft(int depth)
{
	long Count;

	generatorPtr->GenerateMoves();
	int movesCount = generatorPtr->movesCount;
	Move moves[256];
	for (int i = 0; i < movesCount; i++)
		moves[i] = generatorMovesPtr[i];

	for (int i = 0; i < movesCount; i++)
	{
		//boardPtr->
	}





	return Count;
}
