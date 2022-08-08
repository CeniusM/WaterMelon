#pragma once
// --- by Sebastian Lague ---

class PieceList
{

    // Indices of squares occupied by given piece type (only elements up to Count are valid, the rest are unused/garbage)
    int occupiedSquares[65]{};
    // Map to go from index of a square, to the index in the occupiedSquares array where that square is stored
    int map[64]{};

public:
    /// <summary>
    /// the index of -1 will have the pieceNumber
    /// </summary>
    int* occupiedPtr;

    PieceList()
    {
        occupiedPtr = &occupiedSquares[1];
    }

    void AddPieceAtSquare(int square)
    {
        occupiedPtr[occupiedPtr[-1]] = square;
        map[square] = occupiedPtr[-1];
        occupiedPtr[-1]++;
    }

    void RemovePieceAtSquare(int square)
    {
        int pieceIndex = map[square]; // get the index of this element in the occupiedSquares array
        occupiedPtr[pieceIndex] = occupiedPtr[occupiedPtr[-1] - 1]; // move last element in array to the place of the removed element
        map[occupiedPtr[pieceIndex]] = pieceIndex; // update map to point to the moved element's new location in the array
        occupiedPtr[-1]--;
    }

    void MovePiece(int startSquare, int targetSquare)
    {
        int pieceIndex = map[startSquare]; // get the index of this element in the occupiedSquares array
        occupiedPtr[pieceIndex] = targetSquare;
        map[targetSquare] = pieceIndex;
    }
};