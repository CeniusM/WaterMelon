#pragma once

#include "Defines.h"

// Number between [0 - 63], and uses -1 to indicate an invalid pos or none initialized pos
#define Pos int
// Number between [0 - 7]
#define MoveFlag int

// in order of what is most likly to happend
constexpr MoveFlag NoFlag = 0;
constexpr MoveFlag PawnTwoForward = 1;
constexpr MoveFlag EnPassantCapture = 2;
constexpr MoveFlag Castling = 3;
constexpr MoveFlag PromoteToQueen = 4;
constexpr MoveFlag PromoteToKnight = 5;
constexpr MoveFlag PromoteToRook = 6;
constexpr MoveFlag PromoteToBishop = 7;

constexpr Pos InvalidPos = -1;
constexpr Pos InclusiveLowerBoundPos = 0;
constexpr Pos InclusiveUpperBoundPos = 63;
constexpr Pos ExclusiveLowerBoundPos = -1;
constexpr Pos ExclusiveUpperBoundPos = 64;

#define Move int
#define GetMoveStart(move) ((move) & 0x3f) // Get 0 - 6 bits
#define GetMoveTarget(move) (((move) >> 6) & 0x3f) // Get 7 - 12 bits 
#define GetMoveFlag(move) (((move)>> 12) & 0x3c00) // Get 13 - 14 bits

#ifdef DEBUG_DoChecks
//#undef int __cdecl CreateMove(int,int,int)
constexpr Move CreateMove(Pos start, Pos target, MoveFlag flag)
{
	//if (start < 0 || start > 63)
		
	return ((start) | ((target) << 6) | ((flag) << 12));
}
#else
#define CreateMove(start, target, flag) ((start) | ((target) << 6) | ((flag) << 12))
#endif
