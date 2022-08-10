#pragma once

#include "Move.h"
#include "UnsafeWaterMelon.h"

#define PieceType(p) (p & 0b00111)
#define Colour(p) (p & 0b11000)

// works between 65535 and -65472 
#define InBounds(pos) ((pos & 0xFFC0) == 0)

#define BitBoardContains(bitboard, pos) (((bitboard << pos) & 0x8000000000000000) == 0x8000000000000000)






class PossibleMovesGenerator
{
public:
	Move moves[256]; // not sure what the max amount of moves is
	Move* movesPtr= NULL; // for copying
	int movesCount;

	unsigned long pinnedPiecesBitBoard = 0;

	int* castlePtr;
	int* EPSquare;
	int playerTurn;

	bool KingInCheck;
	bool KingInDoubleCheck;
	
	bool whiteToMove;

	int ourColour;
	int ourKingPos;

	int enemyColour;
	int enemyKingPos;
	
	

	char board[64]; // stack var that needs to be coppied
	long long* thisBoardPtr; // boardPtr for copying
	long long* otherBoardPtr; // boardPtr for copying





	void GenerateMoves();
	PossibleMovesGenerator(UnsafeWaterMelon& boardRef);
	~PossibleMovesGenerator();
private:

};

PossibleMovesGenerator::PossibleMovesGenerator(UnsafeWaterMelon& boardRef)
{
	for (int i = 0; i < 256; i++)
		moves[i] = Move(0,0,0);

}

PossibleMovesGenerator::~PossibleMovesGenerator()
{
}