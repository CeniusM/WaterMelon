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

	// make attack bitboard for all the pieces
	// also make a bitboard where its the attack pos and end square where it 
	// then returns a bitboard with 1's from the atacking square to the attacked square
	// long long BitboardAttacksFromSquareToSquare[square1][square2]
	// but must allways must be valid direction, must include square 1 and 2 in bitboard
	// so if its like 4x4 and the attack goes from 0-10
	// 1000
	// 0100
	// 0010
	// 00k0
	long long pinningPiecesAttack[64]; // use the pos of the piece as index
	long long pinnedPieces; // bitboard

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

	int* castlePtr;
	int castle;
	int* EPSquarePtr;
	int EPSquare;
	int* playerTurn;

	// piece lists
	int* OurPawns;
	int* OurKnights;
	int* OurBishops;
	int* OurRooks;
	int* OurQueens;
	int* EnemyPawns;
	int* EnemyKnights;
	int* EnemyBishops;
	int* EnemyRooks;
	int* EnemyQueens;

	void GenerateMoves();

	PossibleMovesGenerator(UnsafeWaterMelon& boardRef);
	~PossibleMovesGenerator();
private:
	void Init();
};

PossibleMovesGenerator::PossibleMovesGenerator(UnsafeWaterMelon& boardRef)
{
	for (int i = 0; i < 256; i++)
		moves[i] = Move(0,0,0);

	otherBoardPtr = (long long*) & boardRef.board[0];
	castlePtr = &boardRef.castle;
	EPSquarePtr = &boardRef.EPSquare;	
}

PossibleMovesGenerator::~PossibleMovesGenerator()
{
}