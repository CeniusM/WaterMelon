#pragma once

#include "TypesIncludes.hpp"
#include "UnsafeWaterMelon.hpp"

// Returns an evaluation that uses all the difrent methods of evaluating the board
Eval GetFullBoardEval(const UnsafeWaterMelon& board);

// Returns a guess for the game stage
int GetLateGameMultiplier(const UnsafeWaterMelon& board);

// Counts the material coint compared to the isEndGame
Eval GetMaterialEval(const UnsafeWaterMelon& board, bool isEndGame);

// Gets the eval for the placement of the peices compared to the isEndGame
Eval GetPiecePlacementMapEval(const UnsafeWaterMelon& board, bool isEndGame);

// Gets the eval of the pawn structure of each side
Eval GetPawnStructureEval(const UnsafeWaterMelon& board, bool isEndGame);

// Gets the king safety eval of each side
Eval GetKingSafetyEval(const UnsafeWaterMelon& board, bool isEndGame);

// Evaluates how well sertain peices over see the board like knight defended by pawns
Eval GetOutpostEval(const UnsafeWaterMelon& board, bool isEndGame);

// The more the peices can see the better, this also looks at what can attack each other
Eval GetPieceActivationEval(const UnsafeWaterMelon& board, bool isEndGame);

// Gets the piece activity of all the none pawn material
Eval GetNonPawnPieceActivity(const UnsafeWaterMelon& board, bool isEndGame);
