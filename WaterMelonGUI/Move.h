#pragma once

#include "Square.h"
#include "MoveFlag.h"

//#define DEBUG_DoChecks

constexpr Square InvalidPos = -1;
constexpr Square InclusiveLowerBoundPos = 0;
constexpr Square InclusiveUpperBoundPos = 63;
constexpr Square ExclusiveLowerBoundPos = -1;
constexpr Square ExclusiveUpperBoundPos = 64;

/// <summary>
/// 0-6 bits is the StartSquare. 7-12 bits is the TargetSquare. 13-15 bits is the Flag.
/// </summary>
typedef int Move;

// Get 0 - 6 bits
constexpr Square GetMoveStart(Move move)
{
	return move & 0x3f;
}
// Get 7 - 12 bits 
constexpr Square GetMoveTarget(Move move)
{
	return (move >> 6) & 0x3f;
}
// Get 13 - 15 bits
constexpr MoveFlag GetMoveFlag(Move move)
{
	return (move >> 12) & 0x3c00;
}

#ifdef DEBUG_DoChecks
constexpr Move CreateMove(Pos start, Pos target, MoveFlag flag)
{
	//if (start & 0b111111 != 0)
	// error
	//if (target & 0b111111000000 != 0)
	// error
	//if (flag & 0b11100000000000000 != 0)
	// error
		
	return ((start) | ((target) << 6) | ((flag) << 12));
}
#else
constexpr Move CreateMove(Square start, Square target, MoveFlag flag)
{
	return start | (target << 6) | (flag << 12);
}
#endif
