#pragma once

#include "Square.h"

// The square behind the pawn that just moved 2 moves forward, so the one move of a two moved pawn
typedef Square EnPassantPos;

constexpr EnPassantPos EmptyEnPassantPos = InvalidSquare;