#pragma once

#include "Evaluation.h"
#include "Piece.h"
#include "Square.h";

// 15 * 64
constexpr EvaluationF PiecePlacementBonuses[]
{
	1.2f,
};
// not sure about this
constexpr EvaluationF GetPiecePlacementBonus(Piece piece, Square square)
{
	piece -= 9; // WKing i 9, so we have nothing from 0 til 8
	piece << 6; // * 64
	return PiecePlacementBonuses[square | piece];
}