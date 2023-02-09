#pragma once

typedef int CastleRight;

enum CastleRights
{
	AllRights = 0b1111,

	AllWhite = 0b1100,
	AllBlack = 0b0011,

	WhiteKingSide = 0b1000,
	WhiteQueenSide = 0b0100,
	BlackKingSide = 0b0010,
	BlackQueenSide = 0b0001,
};

