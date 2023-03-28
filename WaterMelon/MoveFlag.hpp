#pragma once

#include "Move.hpp"
#include "Piece.hpp"
#include "ThrowHelper.hpp"

// Number between [0 - 7] // Maby 15 later so we can see if it was a capture
typedef unsigned short MoveFlag;

constexpr unsigned short CapturedPieceBitFlag = 0b1000000000000000;
constexpr unsigned short MoveFlagMask = 0b111000000000000;

// in order of what is most likly to happend, well kinda ok
enum MoveFlags : unsigned short
{
	NoFlag = 0,
	PawnDoubleForward = 0b001 << 12,
	EnPassantCapture = 0b010 << 12 | CapturedPieceBitFlag,
	Castling = 0b011 << 12,
	PromoteToQueen = 0b100 << 12,
	PromoteToRook = 0b101 << 12,
	PromoteToKnight = 0b110 << 12,
	PromoteToBishop = 0b111 << 12,

	NoFlagCapture = 0 | CapturedPieceBitFlag,
	PromoteToQueenCapture = PromoteToQueen | CapturedPieceBitFlag,
	PromoteToRookCapture = PromoteToRook | CapturedPieceBitFlag,
	PromoteToKnightCapture = PromoteToKnight | CapturedPieceBitFlag,
	PromoteToBishopCapture = PromoteToBishop | CapturedPieceBitFlag,
};