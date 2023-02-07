#pragma once

#include "Piece.h"
#include "Move.h"

// --- by Sebastian Lague ---

class PieceList
{
public:
    int PieceNum = 0;
    // Indices of squares occupied by given piece type (only elements up to Count are valid, the rest are unused/garbage)
    int OccupiedSquares[64]{};
    // Map to go from index of a square, to the index in the occupiedSquares array where that square is stored
    Pos Map[64]{};

    PieceList()
    {
    }

    void AddPieceAtSquare(Pos square)
    {
        OccupiedSquares[PieceNum] = square;
        Map[square] = PieceNum;
        PieceNum++;
    }

    void RemovePieceAtSquare(Pos square)
    {
        Pos pieceIndex = Map[square]; // get the index of this element in the occupiedSquares array
        OccupiedSquares[pieceIndex] = OccupiedSquares[PieceNum - 1]; // move last element in array to the place of the removed element
        Map[OccupiedSquares[pieceIndex]] = pieceIndex; // update map to point to the moved element's new location in the array
        PieceNum--;
    }

    void MovePiece(Pos startSquare, Pos targetSquare)
    {
        Pos pieceIndex = Map[startSquare]; // get the index of this element in the occupiedSquares array
        OccupiedSquares[pieceIndex] = targetSquare;
        Map[targetSquare] = pieceIndex;
    }
};