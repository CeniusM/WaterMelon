#pragma once

#include "Square.h"
#include "Piece.h"

typedef unsigned long long ZobristKey;

// 24 * 64
// First is piece type and second is square index
constexpr ZobristKey KeysForXOR[] =
{
	9
};

constexpr ZobristKey HashKeyMove(ZobristKey key, Square start, Square target, Piece startPiece, Piece targetPiece, int gameMoveCount)
{
	key ^= KeysForXOR[gameMoveCount];
	key ^= KeysForXOR[24 * 64 - 1]; // side to move
	key ^= KeysForXOR[startPiece * 64 + start];
	key ^= KeysForXOR[startPiece * 64 + target];
	if (targetPiece != 0)
		key ^= KeysForXOR[targetPiece * 64 + target];
	return key;
}

// Used for castle, enpassant, twopawnmove
//constexpr ZobristKey HashKeyMisc(ZobristKey key, int Index)
//{
//	key ^= KeysForXOR[startPiece * 64 + start];
//}