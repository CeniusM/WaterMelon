#pragma once

#include "Eval.hpp"
#include "Piece.hpp"
#include "Square.hpp";

// 15 * 64
constexpr Eval PiecePlacementBonuses[]
{
	1.2f,
};
// not sure about this
constexpr Eval GetPiecePlacementBonus(Piece piece, Square square)
{
	piece -= 9; // WKing i 9, so we have nothing from 0 til 8
	piece << 6; // * 64
	return PiecePlacementBonuses[square | piece];
}