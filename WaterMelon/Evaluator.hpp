#pragma once

#include "TypesIncludes.hpp"
#include "UnsafeWaterMelon.hpp"

// Returns an evaluation that uses all the difrent methods of evaluating the board
Eval GetFullBoardEval(const UnsafeWaterMelon& board);

// Returns a guess for the game stage
GameStage GetLateGameMultiplier(const UnsafeWaterMelon& board);

// Counts the material coint compared to the gameStage
Eval GetMaterialEval(const UnsafeWaterMelon& board, float gameStage);

// Gets the eval for the placement of the peices compared to the gameStage
Eval GetPiecePlacementMapEval(const UnsafeWaterMelon& board, float gameStage);

// Gets the eval of the pawn structure of each side
Eval GetPawnStructureEval(const UnsafeWaterMelon& board, float gameStage);

// Gets the king safety eval of each side
Eval GetKingSafetyEval(const UnsafeWaterMelon& board, float gameStage);

// Evaluates how well sertain peices over see the board like knight defended by pawns
Eval GetOutpostEval(const UnsafeWaterMelon& board, float gameStage);

// The more the peices can see the better, this also looks at what can attack each other
Eval GetPieceActivationEval(const UnsafeWaterMelon& board, float gameStage);
