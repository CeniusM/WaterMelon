#include "Evaluator.h"



EvaluationF GetFullBoardEval(const  UnsafeWaterMelon& board)
{
	GameStage gameStage = GetLateGameMultiplier(board);
	EvaluationF eval = Eval_Equal;
	eval += GetMaterialEval(board, gameStage);
	eval += GetPiecePlacementMapEval(board, gameStage);
	eval += GetPawnStructureEval(board, gameStage);
	eval += GetKingSaftyEval(board, gameStage);
	eval += GetOutpostEval(board, gameStage);
	eval += GetPieceActivationEval(board, gameStage);

	return eval;
}

GameStage GetLateGameMultiplier(const UnsafeWaterMelon& board)
{
	return GameStage();
}

EvaluationF GetMaterialEval(const UnsafeWaterMelon& board, float gameStage)
{
	EvaluationF eval = 0;

	constexpr EvaluationF PawnEarlyGameValue = 100;
	constexpr EvaluationF KnightEarlyGameValue = 400;
	constexpr EvaluationF BishopEarlyGameValue = 440;
	constexpr EvaluationF RookEarlyGameValue = 450;
	constexpr EvaluationF QueenEarlyGameValue = 950;

	constexpr EvaluationF PawnMidGameValue = 100;
	constexpr EvaluationF KnightMidGameValue = 305;
	constexpr EvaluationF BishopMidGameValue = 333;
	constexpr EvaluationF RookMidGameValue = 563;
	constexpr EvaluationF QueenMidGameValue = 950;

	constexpr EvaluationF PawnLateGameValue = 100;
	constexpr EvaluationF KnightLateGameValue = 305;
	constexpr EvaluationF BishopLateGameValue = 333;
	constexpr EvaluationF RookLateGameValue = 563;
	constexpr EvaluationF QueenLateGameValue = 950;

	if (gameStage < 0.33f) // early game
	{
		eval += board.PieceLists[WPawn].PieceNum * PawnEarlyGameValue;
		eval += board.PieceLists[WKnight].PieceNum * KnightEarlyGameValue;
		eval += board.PieceLists[WBishop].PieceNum * BishopEarlyGameValue;
		eval += board.PieceLists[WRook].PieceNum * RookEarlyGameValue;
		eval += board.PieceLists[WQueen].PieceNum * QueenEarlyGameValue;

		eval -= board.PieceLists[BPawn].PieceNum * PawnEarlyGameValue;
		eval -= board.PieceLists[BKnight].PieceNum * KnightEarlyGameValue;
		eval -= board.PieceLists[BBishop].PieceNum * BishopEarlyGameValue;
		eval -= board.PieceLists[BRook].PieceNum * RookEarlyGameValue;
		eval -= board.PieceLists[BQueen].PieceNum * QueenEarlyGameValue;
	}
	else if (gameStage < 0.66f) // mid game
	{
		eval += board.PieceLists[WPawn].PieceNum * PawnMidGameValue;
		eval += board.PieceLists[WKnight].PieceNum * KnightMidGameValue;
		eval += board.PieceLists[WBishop].PieceNum * BishopMidGameValue;
		eval += board.PieceLists[WRook].PieceNum * RookMidGameValue;
		eval += board.PieceLists[WQueen].PieceNum * QueenMidGameValue;

		eval -= board.PieceLists[BPawn].PieceNum * PawnMidGameValue;
		eval -= board.PieceLists[BKnight].PieceNum * KnightMidGameValue;
		eval -= board.PieceLists[BBishop].PieceNum * BishopMidGameValue;
		eval -= board.PieceLists[BRook].PieceNum * RookMidGameValue;
		eval -= board.PieceLists[BQueen].PieceNum * QueenMidGameValue;
	}
	else // late game
	{
		eval += board.PieceLists[WPawn].PieceNum * PawnLateGameValue;
		eval += board.PieceLists[WKnight].PieceNum * KnightLateGameValue;
		eval += board.PieceLists[WBishop].PieceNum * BishopLateGameValue;
		eval += board.PieceLists[WRook].PieceNum * RookLateGameValue;
		eval += board.PieceLists[WQueen].PieceNum * QueenLateGameValue;

		eval -= board.PieceLists[BPawn].PieceNum * PawnLateGameValue;
		eval -= board.PieceLists[BKnight].PieceNum * KnightLateGameValue;
		eval -= board.PieceLists[BBishop].PieceNum * BishopLateGameValue;
		eval -= board.PieceLists[BRook].PieceNum * RookLateGameValue;
		eval -= board.PieceLists[BQueen].PieceNum * QueenLateGameValue;
	}

	return Eval_Equal;
}

EvaluationF GetPiecePlacementMapEval(const UnsafeWaterMelon& board, float gameStage)
{
	EvaluationF eval = 0;

	for (size_t pieceType = 9; pieceType < 24; pieceType++) // From WKing to BQueen
	{
		int count = board.PieceLists[pieceType].PieceNum;
		for (size_t num = 0; num < count; num++)
		{
			int pos = board.PieceLists->OccupiedSquares[num];
			eval += GetPiecePlacementBonus(pieceType, pos);
		}
	}

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

EvaluationF GetOutpostEval(const UnsafeWaterMelon& board, float gameStage)
{
	return Eval_Equal;
}

EvaluationF GetPieceActivationEval(const UnsafeWaterMelon& board, float gameStage)
{
	// Bishops attacking the long files is good, bishop close together is good
	// Also rook open files are really good

	return Eval_Equal;
}
