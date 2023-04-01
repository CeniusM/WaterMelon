#include "Evaluator.hpp"



Eval GetFullBoardEval(UnsafeWaterMelon& board)
{
	board.GenerateBitboards();

	// Check if it is a draw
	

	bool isEndGame = GetLateGameMultiplier(board);
	Eval eval = Eval_Equal;
	eval += GetMaterialEval(board, isEndGame);
	eval += GetPiecePlacementMapEval(board, isEndGame);
	eval += GetPawnStructureEval(board, isEndGame);
	eval += GetKingSafetyEval(board, isEndGame);
	eval += GetOutpostEval(board, isEndGame);
	eval += GetPieceActivationEval(board, isEndGame);

	return eval;
}

bool GetLateGameMultiplier(const UnsafeWaterMelon& board)
{
	return 0;
}

Eval GetMaterialEval(const UnsafeWaterMelon& board, bool isEndGame)
{
	Eval eval = 0;

	if (!isEndGame) // early to mid game
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

Eval GetPiecePlacementMapEval(const UnsafeWaterMelon& board, bool isEndGame)
{
	Eval eval = 0;

	for (size_t pieceType = 9; pieceType < 24; pieceType++) // From WKing to BQueen
	{
		bool count = board.PieceLists[pieceType].PieceNum;
		for (size_t num = 0; num < count; num++)
		{
			bool pos = board.PieceLists->OccupiedSquares[num];
			eval += GetPiecePlacementBonus(pieceType, pos);
		}
	}

	return Eval_Equal;
}

Eval GetPawnStructureEval(const UnsafeWaterMelon& board, bool isEndGame)
{
	// Evaluates things like passed pawns, how they defend each other, and how much they attack the enemy
	// If they attack heigh valued peices like queens its good

	Eval eval = 0;

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

	const bool whitePawnCount = board.PieceLists[WPawn].PieceNum;
	const bool blackPawnCount = board.PieceLists[BPawn].PieceNum;

	for (size_t i = 0; i < whitePawnCount; i++)
		if (BitboardContains(whitePawnAttacks, board.PieceLists[WPawn].OccupiedSquares[i]))
			eval += PawnLinkBonus;

	for (size_t i = 0; i < blackPawnCount; i++)
		if (BitboardContains(blackPawnAttacks, board.PieceLists[WPawn].OccupiedSquares[i]))
			eval -= PawnLinkBonus;

	return Eval_Equal;
}

Eval GetKingSafetyEval(const UnsafeWaterMelon& board, bool isEndGame)
{
	// this is tricky beacous it also changes between the difrent game stages
	// in the begining the enemy cant attack the king to much
	// mid game the king needs to be defended from the enemy active pieces
	// late game the king needs to come out and help, 
	// it does not help the king just stands with 3 pawns in the cornor not promoting

	Eval kingSafetyEval = 0; // important early game, but more so mid
	Eval kingActivationEval = 0; // more and more imporatan the later the game



	return 0;
}

Eval GetOutpostEval(const UnsafeWaterMelon& board, bool isEndGame)
{
	return Eval_Equal;
}

Eval GetPieceActivationEval(const UnsafeWaterMelon& board, bool isEndGame)
{
	// Bishops attacking the long files is good, bishop close together is good
	// Also rook open files are really good

	// Another thing is if there for example is a queen inside the enemy pawn attacks
	// this will give a bad eval for when its the queens turn, and even worse if the pawns turn
	// This does that for all the pieces EXECPT pawns (that is allready done)

	return Eval_Equal;
}

#pragma region GetNonPawnPieceActivity

Eval GetNonPawnPieceActivity(const UnsafeWaterMelon& board, bool isEndGame)
{
	// For testing
	int ActivationBonus[] = { 5, 6 };

	Eval eval = 0;

	// King, king works difrently tho, we would like around 1-4 mg, and 5+ in eg, so just counting wont work
	int wKing = board.kingPos[0];
	int bKing = board.kingPos[1];
	Bitboard wPieces = board.AllWhitePosBitboard;
	Bitboard bPieces = board.AllBlackPosBitboard;

	int wKingCount = 0;
	for (size_t i = 0; i < 8; i++)
		if (!BitboardContains(wPieces, wKing + offsetsIndexed[i]))
			wKingCount++;

	int bKingCount = 0;
	for (size_t i = 0; i < 8; i++)
		if (!BitboardContains(bPieces, bKing + offsetsIndexed[i]))
			bKingCount--;


	// Knight


	// Bishop

	// Rook

	// Queen



	//if (isEndGame)
		//return count * ActivationBonus[1];
	//return count * ActivationBonus[0];
	ThrowNotImplementedException("GetNonPawnPieceActivity");
	return 0;
}

#pragma endregion