#pragma once

namespace Piece
{
    constexpr char White = 8;
    constexpr char Black = 16;
              
    constexpr char None = 0;
    constexpr char King = 1;
    constexpr char Pawn = 2;
    constexpr char Knight = 3;
    constexpr char Bishop = 5;
    constexpr char Rook = 6;
    constexpr char Queen = 7;
              
    constexpr char WKing = King + White;
    constexpr char WPawn = Pawn + White;
    constexpr char WKnight = Knight + White;
    constexpr char WBishop = Bishop + White;
    constexpr char WRook = Rook + White;
    constexpr char WQueen = Queen + White;
              
    constexpr char BKing = King + Black;
    constexpr char BPawn = Pawn + Black;
    constexpr char BKnight = Knight + Black;
    constexpr char BBishop = Bishop + Black;
    constexpr char BRook = Rook + Black;
    constexpr char BQueen = Queen + Black;
              
    constexpr char typeMask = 0b00111;
    constexpr char blackMask = 0b10000;
    constexpr char whiteMask = 0b01000;
    constexpr char colourMask = whiteMask | blackMask;

    constexpr bool IsColour(int piece, int colour)
    {
        return (piece & colourMask) == colour;
    }

    constexpr char Colour(int piece)
    {
        return piece & colourMask;
    }

    constexpr char PieceType(int piece)
    {
        return piece & typeMask;
    }

    constexpr bool IsKing(int piece)
    {
        return (piece & typeMask) == King;
    }

    constexpr bool IsRookOrQueen(int piece)
    {
        return (piece & 0b110) == 0b110;
    }

    constexpr bool IsBishopOrQueen(int piece)
    {
        return (piece & 0b101) == 0b101;
    }

    constexpr bool IsSlidingPiece(int piece)
    {
        return (piece & 0b100) != 0;
    }
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