#pragma once

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

//#define UsingMoveClass

#ifdef UsingMoveClass

struct Move
{
	Pos StartSquare;
	Pos TargetSquare;
	MoveFlag Flag;

	Move(Pos s, Pos t, MoveFlag f)
	{
		StartSquare = s;
		TargetSquare = t;
		Flag = f;
	}
	Move()
	{
		StartSquare = 0;
		TargetSquare = 0;
		Flag = 0;
	}
};

#else

#define Move int
#define GetMoveStart(move) (move & 0x3f) // Get 0 - 5 bits
#define GetMoveTarget(move) ((move & 0x7e0) >> 5) // Get 6 - 10 bits 
#define GetMoveFlag(move) ((move & 0x3c00) >> 10) // Get 11 - 14 bits
#define GetMove(start, target, flag) (start | (target << 5) | (flag << 10))

#endif
