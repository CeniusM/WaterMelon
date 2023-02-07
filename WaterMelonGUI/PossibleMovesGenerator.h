#pragma once

#include "UnsafeWaterMelon.h"

#define PieceType(p) (p & 0b00111)
#define Colour(p) (p & 0b11000)

// works between 65535 and -65472 
#define InBounds(pos) ((pos & 0xFFC0) == 0)

#define BitBoardContains(bitboard, pos) (((bitboard << pos) & 0x8000000000000000) == 0x8000000000000000)

#define MaxMovesCount 512




class PossibleMovesGenerator
{
public:
	Move moves[MaxMovesCount]; // not sure what the max amount of moves is
	Move* movesPtr= NULL; // for copying
	int movesCount = 0;

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
	

	Piece board[64]; // stack varible that needs to be coppied
	// Pointer to Generator board
	void* thisBoard;
	// Pointer to UnsafeWaterMelon board
	void* otherBoard;

	int* castlePtr;
	int castle;
	int* EPSquarePtr;
	int EPSquare;
	int* playerTurn;

	// piece lists
	Piece* OurPawns;
	Piece* OurKnights;
	Piece* OurBishops;
	Piece* OurRooks;
	Piece* OurQueens;
	Piece* EnemyPawns;
	Piece* EnemyKnights;
	Piece* EnemyBishops;
	Piece* EnemyRooks;
	Piece* EnemyQueens;

	/// <summary>
	/// Generates the moves...
	/// </summary>
	void GenerateMoves();

	/// <summary>
	/// Used to copy the generated moves into the given pointer
	/// </summary>
	/// <param name="movesPtr">The pointer size is expected to be atlist "MaxMovesCount"</param>
	/// <returns>The moves copied count</returns>
	int GetMovesCopy(Move* movesPtr);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>The currently amount of moves generated</returns>
	int GetCount();

	PossibleMovesGenerator(UnsafeWaterMelon* boardRef);
	~PossibleMovesGenerator();
private:
	void Init();
};


/*
Graveyard for old code

	long long* thisBoardPtr; // boardPtr for copying
	long long* otherBoardPtr; // boardPtr for copying



*/