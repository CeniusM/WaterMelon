#include "Evaluator.h"



Evaluation GetFullBoardEval(const  UnsafeWaterMelon& board)
{
    GameStage gameStage = GetLateGameMultiplier(board);
    Evaluation eval = GetPieceMaterialEval(board, gameStage);
    eval += GetPiecePlacementMapEval(board, gameStage);
    eval += GetPawnStructureEval(board, gameStage);
    eval += GetKingSaftyEval(board, gameStage);

    return eval;
}

GameStage GetLateGameMultiplier(const UnsafeWaterMelon& board)
{
    return GameStage();
}

Evaluation GetPieceMaterialEval(const UnsafeWaterMelon& board, float gameStage)
{
    return Eval_Equal;
}

Evaluation GetPiecePlacementMapEval(const UnsafeWaterMelon& board, float gameStage)
{
    return Eval_Equal;
}

Evaluation GetPawnStructureEval(const UnsafeWaterMelon& board, float gameStage)
{
    // Evaluates things like passed pawns, how they defend each other, and how much they attack the enemy
    // If they attack heigh valued peices like queens its good

    return Eval_Equal;
}

Evaluation GetKingSaftyEval(const UnsafeWaterMelon& board, float gameStage)
{
    return Eval_Equal;
}