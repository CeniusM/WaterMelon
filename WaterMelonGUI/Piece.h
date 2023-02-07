#pragma once

#define UsingIntForPiece

#ifdef UsingIntForPiece
#define Piece int
#else
#define Piece char
#endif


constexpr Piece White = 8;
constexpr Piece Black = 16;

constexpr Piece NoPiece = 0;
constexpr Piece King = 1;
constexpr Piece Pawn = 2;
constexpr Piece Knight = 3;
constexpr Piece Bishop = 5;
constexpr Piece Rook = 6;
constexpr Piece Queen = 7;

constexpr Piece WKing = King + White;
constexpr Piece WPawn = Pawn + White;
constexpr Piece WKnight = Knight + White;
constexpr Piece WBishop = Bishop + White;
constexpr Piece WRook = Rook + White;
constexpr Piece WQueen = Queen + White;

constexpr Piece BKing = King + Black;
constexpr Piece BPawn = Pawn + Black;
constexpr Piece BKnight = Knight + Black;
constexpr Piece BBishop = Bishop + Black;
constexpr Piece BRook = Rook + Black;
constexpr Piece BQueen = Queen + Black;

constexpr Piece typeMask = 0b00111;
constexpr Piece blackMask = 0b10000;
constexpr Piece whiteMask = 0b01000;
constexpr Piece colourMask = whiteMask | blackMask;

constexpr bool IsColour(Piece piece, Piece colour)
{
	return (piece & colourMask) == colour;
}

constexpr Piece Colour(Piece piece)
{
	return piece & colourMask;
}

constexpr Piece PieceType(Piece piece)
{
	return piece & typeMask;
}

constexpr bool IsKing(Piece piece)
{
	return (piece & typeMask) == King;
}

constexpr bool IsRookOrQueen(Piece piece)
{
	return (piece & 0b110) == 0b110;
}

constexpr bool IsBishopOrQueen(Piece piece)
{
	return (piece & 0b101) == 0b101;
}

constexpr bool IsSlidingPiece(Piece piece)
{
	return (piece & 0b100) != 0;
}


/*
King	= 0b001
Pawn	= 0b010
Knight	= 0b011
Bishop	= 0b101
Rook	= 0b110
Queen	= 0b111

White   = 0b01000
Black   = 0b10000
*/