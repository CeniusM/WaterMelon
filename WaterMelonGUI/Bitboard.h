#pragma once

#include "Square.h"

typedef unsigned long long Bitboard;

constexpr Bitboard SignificantBit = 0b1;//0x8000000000000000
constexpr Bitboard LeftSide = 0x8080808080808080;
constexpr Bitboard RightSide = 0x0101010101010101;
constexpr Bitboard TopSide = 0xff;
constexpr Bitboard ButtomSide = 0xff00000000000000;

constexpr Bitboard WhitePromotionLine = 0xFF;
constexpr Bitboard WhiteTwoMoveLine = 0xFF000000000000;
constexpr Bitboard BlackPromotionLine = 0xFF00000000000000;
constexpr Bitboard BlackTwoMoveLine = 0xFF00;

constexpr Bitboard RightSideIs0 = 0b0111111101111111011111110111111101111111011111110111111101111111;
constexpr Bitboard LeftSideIs0 = 0b1111111011111110111111101111111011111110111111101111111011111110;

constexpr bool BitboardContains(Bitboard bitboard, Square pos)
{
	return ((bitboard >> pos) & SignificantBit) == SignificantBit;
}

constexpr bool PosOnLeftSide(Square pos)
{
	return ((LeftSide >> pos) & SignificantBit) == SignificantBit;
}

constexpr bool PosOnRightSide(Square pos)
{
	return ((RightSide >> pos) & SignificantBit) == SignificantBit;
}

// Black side
constexpr bool OnTop(Square pos)
{
	return ((TopSide >> pos) & SignificantBit) == SignificantBit;
}

// White side
constexpr bool OnButtom(Square pos)
{
	return ((ButtomSide >> pos) & SignificantBit) == SignificantBit;
}