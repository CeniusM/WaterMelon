#pragma once

#include "TypesIncludes.h"
#include "UnsafeWaterMelon.h"

// Returns an evaluation that uses all the difrent methods of evaluating the board
Evaluation GetFullBoardEval(const UnsafeWaterMelon& board);

// Returns a guess for the game stage
GameStage GetLateGameMultiplier(const UnsafeWaterMelon& board);

// Counts the material coint compared to the gameStage
Evaluation GetPieceMaterialEval(const UnsafeWaterMelon& board, float gameStage);

// Gets the eval for the placement of the peices compared to the gameStage
Evaluation GetPiecePlacementMapEval(const UnsafeWaterMelon& board, float gameStage);

// Gets the eval of the pawn structure of each side
Evaluation GetPawnStructureEval(const UnsafeWaterMelon& board, float gameStage);

// Gets the king safty eval of each side
Evaluation GetKingSaftyEval(const UnsafeWaterMelon& board, float gameStage);

// Evaluates how well sertain peices over see the board like knight defended by pawns
//int GetOutpostEval(const UnsafeWaterMelon& board, float gameStage);

// The more the peices can see the better
//int GetPieceActivationEval(const UnsafeWaterMelon& board, float gameStage);