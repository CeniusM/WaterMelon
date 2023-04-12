#pragma once

#include "TypesIncludes.hpp"
#include "UnsafeWaterMelon.hpp"

// Returns an evaluation that uses all the difrent methods of evaluating the board
Eval GetFullBoardEval(const UnsafeWaterMelon& board, bool noMoves = false);

// Returns a guess for the game stage, It is a range between 0 and 1024, wich we can use as a 0-1 range, just with integers
int GetLateGameMultiplier(const UnsafeWaterMelon& board);

// Multiplies the value that is influenced by LateGameMultiplier
int MultiplyByLateGameMultiplier(int value, int lateGameMultiplier);

// Counts the material coint compared to the lateGameMultiplier
Eval GetMaterialEval(const UnsafeWaterMelon& board, int lateGameMultiplier);

// Gets the eval for the placement of the peices compared to the lateGameMultiplier
Eval GetPiecePlacementMapEval(const UnsafeWaterMelon& board, int lateGameMultiplier);

// Gets the eval of the pawn structure of each side
Eval GetPawnStructureEval(const UnsafeWaterMelon& board, int lateGameMultiplier);

// Gets the king safety eval of each side
Eval GetKingSafetyEval(const UnsafeWaterMelon& board, int lateGameMultiplier);

// Evaluates how well sertain peices over see the board like knight defended by pawns
Eval GetOutpostEval(const UnsafeWaterMelon& board, int lateGameMultiplier);

// The more the peices can see the better, this also looks at what can attack each other
Eval GetPieceActivationEval(const UnsafeWaterMelon& board, int lateGameMultiplier);

// Gets the piece activity of all the none pawn material
Eval GetNonPawnPieceActivity(const UnsafeWaterMelon& board, int lateGameMultiplier);

// Get the eval for how much the two sides are controling
Eval GetSpaceEval(const UnsafeWaterMelon& board, int lateGameMultiplier);