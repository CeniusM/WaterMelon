#pragma once

#include "Move.hpp"
#include "CastleRight.hpp"
#include "EnPassantPos.hpp"

// [0,15] Bits Move
// [16-20] Captured Piece
// [21,26] ep pos
// [25,31] castle
// 50 move rule
// 
//typedef unsigned long long BoardState;

struct BoardState
{
	Move move;
	Piece capturedPiece; // use this as a boolean
	EnPassantPos epPos;
	CastleRight castles;
	short _50MoveRule;
	bool KingInCheck;
	bool KingInDoubleCheck;

	BoardState(Move inMove, Piece inCapturedPiece, EnPassantPos inEPPos, CastleRight inCastle, 
		short in_50MoveRule, bool inKingInCheck, bool inKingInDoubleCheck)
	{
		move = inMove;
		capturedPiece = inCapturedPiece;
		epPos = inEPPos;
		castles = inCastle;
		_50MoveRule = in_50MoveRule;
		KingInCheck = inKingInCheck;
		KingInDoubleCheck = inKingInDoubleCheck;
	}
};