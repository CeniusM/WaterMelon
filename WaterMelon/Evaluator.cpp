#include "Evaluator.h"



EvaluationF GetFullBoardEval(const  UnsafeWaterMelon& board)
{
    GameStage gameStage = GetLateGameMultiplier(board);
    EvaluationF eval = GetPieceMaterialEval(board, gameStage);
    eval += GetPiecePlacementMapEval(board, gameStage);
    eval += GetPawnStructureEval(board, gameStage);
    eval += GetKingSaftyEval(board, gameStage);

    return eval;
}

GameStage GetLateGameMultiplier(const UnsafeWaterMelon& board)
{
    return GameStage();
}

EvaluationF GetPieceMaterialEval(const UnsafeWaterMelon& board, float gameStage)
{
    return Eval_Equal;
}

EvaluationF GetPiecePlacementMapEval(const UnsafeWaterMelon& board, float gameStage)
{
    return Eval_Equal;
}

EvaluationF GetPawnStructureEval(const UnsafeWaterMelon& board, float gameStage)
{
    // Evaluates things like passed pawns, how they defend each other, and how much they attack the enemy
    // If they attack heigh valued peices like queens its good

    return Eval_Equal;
}

EvaluationF GetKingSaftyEval(const UnsafeWaterMelon& board, float gameStage)
{
    return Eval_Equal;
}

EvaluationF GetPieceActivationEval(const UnsafeWaterMelon& board, float gameStage)
{
    // Bishops attacking the long files is good, bishop close together is good
    // Also rook open files are really good

    return Eval_Equal;
}
