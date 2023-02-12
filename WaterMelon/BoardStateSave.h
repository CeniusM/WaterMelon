#pragma once

#include "Move.h"
#include "CastleRight.h"
#include "EnPassantPos.h"

struct BoardStateSave
{
	Move move;
	CastleRight castleRights;
	EnPassantPos epPos;
};