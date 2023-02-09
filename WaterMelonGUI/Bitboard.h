#pragma once

#include "Pos.h"

typedef unsigned long long Bitboard;

constexpr Bitboard SignificantBit = 0x8000000000000000;
constexpr Bitboard LeftSide = 0x8080808080808080;
constexpr Bitboard RightSide = 0x0101010101010101;
constexpr Bitboard TopSide = 0xff;
constexpr Bitboard ButtomSide = 0xff00000000000000;

constexpr bool BitboardContains(Bitboard bitboard, Pos pos)
{
	return ((bitboard << pos) & SignificantBit) == SignificantBit;
}

constexpr bool PosOnLeftSide(Pos pos)
{
	return ((LeftSide << pos) & SignificantBit) == SignificantBit;
}

constexpr bool PosOnRightSide(Pos pos)
{
	return ((RightSide << pos) & SignificantBit) == SignificantBit;
}

// Black side
constexpr bool OnTop(Pos pos)
{
	return ((TopSide << pos) & SignificantBit) == SignificantBit;
}

// White side
constexpr bool OnButtom(Pos pos)
{
	return ((ButtomSide << pos) & SignificantBit) == SignificantBit;
}