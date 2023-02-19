#pragma once

#include "Move.h"
#include "Piece.h"
#include "ThrowHelper.h"

// Number between [0 - 7] // Maby 15 later so we can see if it was a capture
typedef unsigned short MoveFlag;

constexpr unsigned short CapturedPieceBitFlag = 0b1000000000000000;
constexpr unsigned short MoveFlagMask = 0b111000000000000;

// in order of what is most likly to happend
enum MoveFlags : unsigned short
{
	NoFlag = 0,
	PawnDoubleForward = 0b001000000000000,
	EnPassantCapture = 0b010000000000000 | CapturedPieceBitFlag,
	Castling = 0b011000000000000,
	PromoteToQueen = 0b100000000000000,
	PromoteToRook = 0b101000000000000,
	PromoteToKnight = 0b110000000000000,
	PromoteToBishop = 0b111000000000000,

	NoFlagCapture = 0 | CapturedPieceBitFlag,
	PromoteToQueenCapture = 0b100000000000000 | CapturedPieceBitFlag,
	PromoteToRookCapture = 0b101000000000000 | CapturedPieceBitFlag,
	PromoteToKnightCapture = 0b110000000000000 | CapturedPieceBitFlag,
	PromoteToBishopCapture = 0b111000000000000 | CapturedPieceBitFlag,
};