

#include "PossibleMovesGenerator.h"

void PossibleMovesGenerator::GenerateMoves()
{
	Init();
}

void PossibleMovesGenerator::Init()
{
	// should be faster becous there will be alot of board derfrences otherwise
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