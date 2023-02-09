#pragma once

#include "Piece.h"

// Number between [0 - 7]
typedef int MoveFlag;

// in order of what is most likly to happend
enum MoveFlags
{
	NoFlag = 0,
	PawnTwoForward = 1,
	EnPassantCapture = 2,
	Castling = 3,
	PromoteToQueen = 4,
	PromoteToRook = 5,
	PromoteToKnight = 6,
	PromoteToBishop = 7,
};

constexpr bool IsPromotion(MoveFlag flag)
{
	return (flag & 0b1110000) != 0;
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
		break;
	}
}

//constexpr MoveFlag NoFlag = 0;
//constexpr MoveFlag PawnTwoForward = 1;
//constexpr MoveFlag EnPassantCapture = 2;
//constexpr MoveFlag Castling = 3;
//constexpr MoveFlag PromoteToQueen = 4;
//constexpr MoveFlag PromoteToKnight = 5;
//constexpr MoveFlag PromoteToRook = 6;
//constexpr MoveFlag PromoteToBishop = 7;