#include <cstdlib>
#include <iostream>

#include "PossibleMovesGenerator.h"

void PossibleMovesGenerator::Init()
{
	//_memccpy(thisBoard, otherBoard, INT32_MAX, sizeof(Piece) * 64);
	memcpy_s(thisBoard, sizeof(Piece) * 64, otherBoard, sizeof(Piece) * 64);

	movesCount = 0;
	pinnedPieces = 0;

	KingInCheck = false;
	KingInDoubleCheck = false;

	ourColour = *playerTurn;
	whiteToMove = (ourColour == White);
	enemyColour = ourColour ^ PlayerTurnSwitch;
	castle = *castlePtr;

	if (whiteToMove)
	{
		ourKingPos = unsafeBoard->kingPos[0];
		enemyKingPos = unsafeBoard->kingPos[1];
		OurPawns = unsafeBoard->whitePawnsPtr;
		OurKnights = unsafeBoard->whiteKnightsPtr;
		OurBishops = unsafeBoard->whiteBishopsPtr;
		OurRooks = unsafeBoard->whiteRooksPtr;
		OurQueens = unsafeBoard->whiteQueensPtr;
		EnemyPawns = unsafeBoard->blackPawnsPtr;
		EnemyKnights = unsafeBoard->blackKnightsPtr;
		EnemyBishops = unsafeBoard->blackBishopsPtr;
		EnemyRooks = unsafeBoard->blackRooksPtr;
		EnemyQueens = unsafeBoard->blackQueensPtr;
	}
	else
	{
		ourKingPos = unsafeBoard->kingPos[1];
		enemyKingPos = unsafeBoard->kingPos[0];
		EnemyPawns = unsafeBoard->whitePawnsPtr;
		EnemyKnights = unsafeBoard->whiteKnightsPtr;
		EnemyBishops = unsafeBoard->whiteBishopsPtr;
		EnemyRooks = unsafeBoard->whiteRooksPtr;
		EnemyQueens = unsafeBoard->whiteQueensPtr;
		OurPawns = unsafeBoard->blackPawnsPtr;
		OurKnights = unsafeBoard->blackKnightsPtr;
		OurBishops = unsafeBoard->blackBishopsPtr;
		OurRooks = unsafeBoard->blackRooksPtr;
		OurQueens = unsafeBoard->blackQueensPtr;
	}
}

int PossibleMovesGenerator::GetMovesCopy(Move* movesPtr)
{
	/*for (int i = 0; i < movesCount; i++)
		movesPtr[i] = moves[i];*/
		//_memccpy(movesPtr, moves, 0, sizeof(Move) * movesCount);
	memcpy_s(movesPtr, sizeof(Move) * MaxMovesCount, moves, sizeof(Move) * movesCount);
	return movesCount;
}

int PossibleMovesGenerator::GetCount()
{
	return movesCount;
}

PossibleMovesGenerator::PossibleMovesGenerator(UnsafeWaterMelon* boardRef)
{
	unsafeBoard = boardRef;

	for (int i = 0; i < 256; i++)
		//moves[i] = Move(0, 0, 0);
		moves[i] = InvalidPos;

	thisBoard = board;
	otherBoard = boardRef->board;

	playerTurn = &(*boardRef).playerTurn;
	castlePtr = &(*boardRef).castle;
	EPSquarePtr = &(*boardRef).EPSquare;
}

PossibleMovesGenerator::~PossibleMovesGenerator()
{
}

#pragma region Move_Generation

void PossibleMovesGenerator::GeneratePawnMoves()
{
	int count = OurPawns[-1];
	for (size_t i = 0; i < count; i++)
	{
		moves[movesCount] = CreateMove(OurPawns[i], OurPawns[i] - 8, NoFlag);
		movesCount++;
	}
}

void PossibleMovesGenerator::GenerateKnightMoves()
{
	int count = OurKnights[-1];
	for (size_t i = 0; i < count; i++)
	{
		moves[movesCount] = CreateMove(OurKnights[i], OurKnights[i] - 16, NoFlag);
		movesCount++;
	}
}

void PossibleMovesGenerator::GenerateMoves()
{
	Init();

	GeneratePawnMoves();
	GenerateKnightMoves();

	// first to generate random moves to test all the other stuff
	/*for (int i = 0; i < 64; i++)
	{
		if (Colour(board[i]) == ourColour)
		{
			for (int forMoveCount = 0; forMoveCount < 10; forMoveCount++)
			{
				int move = rand() % ExclusiveUpperBoundPos;
				if (move == i)
					continue;
				moves[movesCount] = GetMove(i, move, NoFlag);
				movesCount++;
			}
		}
	}*/

	for (size_t i = 0; i < movesCount; i++)
	{
		//std::cout << FENUtility::IntToChar[board[i]];
		std::cout << moves[movesCount];
	}
}

#pragma endregion

/*
Graveyard for old code

	otherBoardPtr = (long long*)&(*boardRef).board[0];
	thisBoardPtr = (long long*)&board[0];

	// should be faster becous there will be alot of board derfrences otherwise
	// this still takes 10 * 8 operations
	// and stack board vs board ptr only saves one operation per call
	// No idea if this is faster that memcopy :P, memcopy is probaly faster..., and looks better
#ifdef UsingIntForPiece
	thisBoardPtr[0] = otherBoardPtr[0];
	thisBoardPtr[1] = otherBoardPtr[1];
	thisBoardPtr[2] = otherBoardPtr[2];
	thisBoardPtr[3] = otherBoardPtr[3];
	thisBoardPtr[4] = otherBoardPtr[4];
	thisBoardPtr[5] = otherBoardPtr[5];
	thisBoardPtr[6] = otherBoardPtr[6];
	thisBoardPtr[7] = otherBoardPtr[7];
	thisBoardPtr[0 + 8] = otherBoardPtr[0 + 8];
	thisBoardPtr[1 + 8] = otherBoardPtr[1 + 8];
	thisBoardPtr[2 + 8] = otherBoardPtr[2 + 8];
	thisBoardPtr[3 + 8] = otherBoardPtr[3 + 8];
	thisBoardPtr[4 + 8] = otherBoardPtr[4 + 8];
	thisBoardPtr[5 + 8] = otherBoardPtr[5 + 8];
	thisBoardPtr[6 + 8] = otherBoardPtr[6 + 8];
	thisBoardPtr[7 + 8] = otherBoardPtr[7 + 8];
	thisBoardPtr[0 + 8 + 8] = otherBoardPtr[0 + 8 + 8];
	thisBoardPtr[1 + 8 + 8] = otherBoardPtr[1 + 8 + 8];
	thisBoardPtr[2 + 8 + 8] = otherBoardPtr[2 + 8 + 8];
	thisBoardPtr[3 + 8 + 8] = otherBoardPtr[3 + 8 + 8];
	thisBoardPtr[4 + 8 + 8] = otherBoardPtr[4 + 8 + 8];
	thisBoardPtr[5 + 8 + 8] = otherBoardPtr[5 + 8 + 8];
	thisBoardPtr[6 + 8 + 8] = otherBoardPtr[6 + 8 + 8];
	thisBoardPtr[7 + 8 + 8] = otherBoardPtr[7 + 8 + 8];
	thisBoardPtr[0 + 8 + 8 + 8] = otherBoardPtr[0 + 8 + 8 + 8];
	thisBoardPtr[1 + 8 + 8 + 8] = otherBoardPtr[1 + 8 + 8 + 8];
	thisBoardPtr[2 + 8 + 8 + 8] = otherBoardPtr[2 + 8 + 8 + 8];
	thisBoardPtr[3 + 8 + 8 + 8] = otherBoardPtr[3 + 8 + 8 + 8];
	thisBoardPtr[4 + 8 + 8 + 8] = otherBoardPtr[4 + 8 + 8 + 8];
	thisBoardPtr[5 + 8 + 8 + 8] = otherBoardPtr[5 + 8 + 8 + 8];
	thisBoardPtr[6 + 8 + 8 + 8] = otherBoardPtr[6 + 8 + 8 + 8];
	thisBoardPtr[7 + 8 + 8 + 8] = otherBoardPtr[7 + 8 + 8 + 8];
#else
	thisBoardPtr[0] = otherBoardPtr[0];
	thisBoardPtr[1] = otherBoardPtr[1];
	thisBoardPtr[2] = otherBoardPtr[2];
	thisBoardPtr[3] = otherBoardPtr[3];
	thisBoardPtr[4] = otherBoardPtr[4];
	thisBoardPtr[5] = otherBoardPtr[5];
	thisBoardPtr[6] = otherBoardPtr[6];
	thisBoardPtr[7] = otherBoardPtr[7];
#endif





*/