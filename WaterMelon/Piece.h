#pragma once

#define UsingIntForPiece

#ifdef UsingIntForPiece
typedef int Piece;
typedef int Color;
typedef int PieceType;
typedef int Mask;
#else
typedef char Piece;
typedef char Color;
typedef char PieceType;
typedef char Mask;
#endif
#define SizeOfPiece sizeof(Piece);

constexpr Color White = 8;
constexpr Color Black = 16;

constexpr PieceType NoPiece = 0;
constexpr PieceType King = 1;
constexpr PieceType Pawn = 2;
constexpr PieceType Knight = 3;
constexpr PieceType Bishop = 5;
constexpr PieceType Rook = 6;
constexpr PieceType Queen = 7;

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

constexpr Mask typeMask = 0b00111;
constexpr Mask blackMask = 0b10000;
constexpr Mask whiteMask = 0b01000;
constexpr Mask colorMask = whiteMask | blackMask;

constexpr Piece CreatePiece(PieceType type, Color color)
{
	return type | color;
}

constexpr bool IsColor(Color piece, Color color)
{
	return (piece & colorMask) == color;
}

constexpr Color GetColor(Piece piece)
{
	return piece & colorMask;
}

constexpr PieceType GetPieceType(Piece piece)
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