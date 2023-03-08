#pragma once

#include <string>
#include "Square.h"
#include "MoveFlag.h"

//#define DEBUG_DoChecks

/// <summary>
/// [0-5] bits is the StartSquare. [6-11] bits is the TargetSquare. [12-14] bits is the Flag. 15 bit for is capture
/// the 15th bit could be used as a flag for if the move was a caputure
/// </summary>
typedef unsigned short Move;

// Get 0 - 5 bits
constexpr Square GetMoveStart(Move move)
{
	return move & 0x3f;
}
// Get 6 - 11 bits 
constexpr Square GetMoveTarget(Move move)
{
	return (move >> 6) & 0x3f;
}
// Get 12 - 14 bits
constexpr MoveFlag GetMoveFlag(Move move)
{
	return move & MoveFlagMask;
}

constexpr bool IsMovePromotion(Move flag)
{
	return (flag & 0b100000000000000) == 0b100000000000000;
}

constexpr PieceType GetPromotionPieceType(MoveFlag flag)
{
	switch (flag)
	{
	case MoveFlags::PromoteToQueen:
		return Queen;
	case MoveFlags::PromoteToRook:
		return Rook;
	case MoveFlags::PromoteToKnight:
		return Knight;
	case MoveFlags::PromoteToBishop:
		return Bishop;
	default:
		ThrowNotImplementedException("Invalid Move Flag");
	}
}

// Get 15 bit
constexpr MoveFlag IsMoveCapture(Move move)
{
	return (move & CapturedPieceBitFlag) == CapturedPieceBitFlag;
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

	return start | (target << 6) | flag;
}
#else
constexpr Move CreateMove(Square start, Square target, MoveFlag flag)
{
	return start | (target << 6) | flag;
}
#endif

//constexpr std::string GetMoveName(Move move)
//{
//	int start = GetMoveStart(move);
//	int target = GetMoveTarget(move);
//	std::string str;
//	str += start;
//	str += " to ";
//	str += target;
//	return str;
//}