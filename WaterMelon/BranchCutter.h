#pragma once

#include "UnsafeWaterMelon.h"

// This will tell the seach how much depth to cut of a tree
// This could cut of 1 or 2 depth if for example the queen walks into an enemy pawn attack
// IT COULD also the the oppesite, if for example the enemy king is under attack, or under double check,
// the branch might benefit from going one depth deeper
int GetBranchDepthCut(const UnsafeWaterMelon& board);