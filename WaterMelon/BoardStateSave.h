#pragma once

#include "Move.h"
#include "CastleRight.h"
#include "EnPassantPos.h"

// [0,15] Bits Move
// [16-20] Captured Piece
// [21,26] ep pos
// [25,31] castle
// 50 move rule
// 
typedef unsigned long long BoardStateSave;