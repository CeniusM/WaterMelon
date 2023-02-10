#pragma once

#include "Offset.h"

typedef int DirectionIndex;
typedef Offset DirectionOffset;

enum DirectionIndexs : DirectionIndex
{
	NorthI = 0,
	EastI = 1,
	SouthI = 2,
	WestI = 3,
	NorthEastI = 4,
	SouthEastI = 5,
	SouthWestI = 6,
	NorthWestI = 7,
};

enum DirectionOffsets : DirectionOffset
{
	NorthO = -8,
	EastO = 1,
	SouthO = 8,
	WestO = -1,
	NorthEastO = -7,
	SouthEastO = 9,
	SouthWestO = 7,
	NorthWestO = -9,
};

constexpr Offset offsetsIndexed[]
{
	DirectionOffsets::NorthO,
	DirectionOffsets::EastO,
	DirectionOffsets::SouthO,
	DirectionOffsets::WestO,
	DirectionOffsets::NorthEastO,
	DirectionOffsets::SouthEastO,
	DirectionOffsets::SouthWestO,
	DirectionOffsets::NorthWestO,
};

constexpr DirectionIndex RookStartDirectionIndex = 0;
constexpr DirectionIndex BishopStartDirectionIndex = 4;
constexpr DirectionIndex QueenStartDirectionIndex = 0;
constexpr DirectionIndex RookEndDirectionIndex = 4;
constexpr DirectionIndex BishopEndDirectionIndex = 8;
constexpr DirectionIndex QueenEndDirectionIndex = 8;