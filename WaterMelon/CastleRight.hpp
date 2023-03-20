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

// Index into this with both start and target squares. Then &= the castle with the array value.
// This way any rights get removed beacous that square either moved or got moved-to/captured
constexpr CastleRight CastleRightAndRemoverForSquare[]
{
	AllRights ^ WhiteQueenSide, // White Queen side
	AllRights,
	AllRights,
	AllRights,
	AllRights ^ AllWhite,
	AllRights,
	AllRights,
	AllRights ^ WhiteKingSide,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights,
	AllRights ^ BlackQueenSide,
	AllRights,
	AllRights,
	AllRights,
	AllRights ^ AllBlack,
	AllRights,
	AllRights,
	AllRights ^ BlackKingSide,
};

//constexpr CastleRight CheckCastle(CastleRight castle, Square startSquare, Square targetSquare, bool whiteToMove)
//{
//	if (whiteToMove)
//	{
//		if (startSquare == 0) // queen rook
//			castle &= CastleRights::AllBlack | CastleRights::WhiteKingSide;
//		else if (startSquare == 7) // king rook
//			castle &= CastleRights::AllBlack | CastleRights::WhiteQueenSide;
//		else if (startSquare == 4) // king move
//			castle &= CastleRights::AllBlack;
//	}
//	else
//	{
//		if (startSquare == 56) // queen rook
//			castle &= CastleRights::AllWhite | CastleRights::BlackKingSide;
//		else if (startSquare == 63) // king rook
//			castle &= CastleRights::AllWhite | CastleRights::BlackQueenSide;
//		else if (startSquare == 60) // king move
//			castle &= CastleRights::AllWhite;
//	}
//}