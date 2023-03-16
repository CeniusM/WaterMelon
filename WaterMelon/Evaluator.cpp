#include "Evaluator.hpp"



EvaluationF GetFullBoardEval(const  UnsafeWaterMelon& board)
{
	GameStage gameStage = GetLateGameMultiplier(board);
	EvaluationF eval = Eval_Equal;
	eval += GetMaterialEval(board, gameStage);
	eval += GetPiecePlacementMapEval(board, gameStage);
	eval += GetPawnStructureEval(board, gameStage);
	eval += GetKingSafetyEval(board, gameStage);
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

	EvaluationF eval = 0;

	const Bitboard whitePawnAttacks = board.pieceAttackBitboards[WPawn];
	const Bitboard blackPawnAttacks = board.pieceAttackBitboards[BPawn];

	for (size_t i = 0; i < 8; i++)
	{
		if (board.WhitePawnCounts[i] == 2)
			eval += DoublePawnPenelty;
		else if (board.WhitePawnCounts[i] == 3)
			eval += TriplePawnPenelty;

		if (board.BlackPawnCounts[i] == 2)
			eval -= DoublePawnPenelty;
		else if (board.BlackPawnCounts[i] == 3)
			eval -= TriplePawnPenelty;
	}

	const int whitePawnCount = board.PieceLists[WPawn].PieceNum;
	const int blackPawnCount = board.PieceLists[BPawn].PieceNum;

	for (size_t i = 0; i < whitePawnCount; i++)
		if (BitboardContains(whitePawnAttacks, board.PieceLists[WPawn].OccupiedSquares[i]))
			eval += PawnLinkBonus;

	for (size_t i = 0; i < blackPawnCount; i++)
		if (BitboardContains(blackPawnAttacks, board.PieceLists[WPawn].OccupiedSquares[i]))
			eval -= PawnLinkBonus;

	return Eval_Equal;
}

EvaluationF GetKingSafetyEval(const UnsafeWaterMelon& board, float gameStage)
{
	// this is tricky beacous it also changes between the difrent game stages
	// in the begining the enemy cant attack the king to much
	// mid game the king needs to be defended from the enemy active pieces
	// late game the king needs to come out and help, 
	// it does not help the king just stands with 3 pawns in the cornor not promoting

	EvaluationF kingSafetyEval = 0; // important early game, but more so mid
	EvaluationF kingActivationEval = 0; // more and more imporatan the later the game



	return 0;
}

EvaluationF GetOutpostEval(const UnsafeWaterMelon& board, float gameStage)
{
	return Eval_Equal;
}

EvaluationF GetPieceActivationEval(const UnsafeWaterMelon& board, float gameStage)
{
	// Bishops attacking the long files is good, bishop close together is good
	// Also rook open files are really good

	// Another thing is if there for example is a queen inside the enemy pawn attacks
	// this will give a bad eval for when its the queens turn, and even worse if the pawns turn
	// This does that for all the pieces EXECPT pawns (that is allready done)

	return Eval_Equal;
}
