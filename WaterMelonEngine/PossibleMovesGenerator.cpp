#include <cstdlib>

#include "PossibleMovesGenerator.h"

void PossibleMovesGenerator::GenerateMoves()
{
	Init();

	// first to generate random moves to test all the other stuff
	for (int i = 0; i < 64; i++)
	{
		if (Colour(board[i]) == ourColour)
		{
			for (int forMoveCount = 0; forMoveCount < 10; forMoveCount++)
			{
				int move = rand() % 64;
				if (move == i)
					continue;
				moves[movesCount] = Move(i, move, 0);
				movesCount++;
			}
		}
	}
}

void PossibleMovesGenerator::GetMoves(Move* movesPtr)
{
	for (int i = 0; i < movesCount; i++)
		movesPtr[i] = moves[i];
}

int PossibleMovesGenerator::GetCount()
{
	return movesCount;
}


void PossibleMovesGenerator::Init()
{
	// should be faster becous there will be alot of board derfrences otherwise
	// this still takes 10 * 8 operations
	// and stack board vs board ptr only saves one operation per call
	thisBoardPtr[0] = otherBoardPtr[0];
	thisBoardPtr[1] = otherBoardPtr[1];
	thisBoardPtr[2] = otherBoardPtr[2];
	thisBoardPtr[3] = otherBoardPtr[3];
	thisBoardPtr[4] = otherBoardPtr[4];
	thisBoardPtr[5] = otherBoardPtr[5];
	thisBoardPtr[6] = otherBoardPtr[6];
	thisBoardPtr[7] = otherBoardPtr[7];


	movesCount = 0;
	pinnedPieces = 0;

	KingInCheck = false;
	KingInDoubleCheck = false;

	ourColour = *playerTurn;
	whiteToMove = (ourColour == 8);
	enemyColour = ourColour ^ PlayerTurnSwitch;
	castle = *castlePtr;
}

PossibleMovesGenerator::PossibleMovesGenerator(UnsafeWaterMelon* boardRef)
{
	for (int i = 0; i < 256; i++)
		moves[i] = Move(0, 0, 0);

	otherBoardPtr = (long long*)&(*boardRef).board[0];
	thisBoardPtr = (long long*)&board[0];
	playerTurn = &(*boardRef).playerTurn;
	castlePtr = &(*boardRef).castle;
	EPSquarePtr = &(*boardRef).EPSquare;
}

PossibleMovesGenerator::~PossibleMovesGenerator()
{
}