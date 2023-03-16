#include "UnsafeWaterMelonComparerer.hpp"

void Failed(std::string message)
{
	std::cout << "Failed: " << message << "\n";
}

void CompareWaterMelons(UnsafeWaterMelon* mel1, UnsafeWaterMelon* mel2)
{
	if (mel1->AllBlackPosBitboard != mel2->AllBlackPosBitboard)
		Failed("AllBlackPosBitboard");

	if (mel1->allEnemyAttacksNonSliding != mel2->allEnemyAttacksNonSliding)
		Failed("allEnemyAttacksNonSliding");

	if (mel1->AllEnemyPosBitboard != mel2->AllEnemyPosBitboard)
		Failed("AllEnemyPosBitboard");

	if (mel1->allFriendlyAttakcsNonSliding != mel2->allFriendlyAttakcsNonSliding)
		Failed("allFriendlyAttakcsNonSliding");

	if (mel1->AllFriendlyPosBitboard != mel2->AllFriendlyPosBitboard)
		Failed("AllFriendlyPosBitboard");

	if (mel1->AllPiecePosBitboard != mel2->AllPiecePosBitboard)
		Failed("AllPiecePosBitboard");

	if (mel1->AllWhitePosBitboard != mel2->AllWhitePosBitboard)
		Failed("AllWhitePosBitboard");

	if (mel1->attacksOnKing != mel2->attacksOnKing)
		Failed("attacksOnKing");

	for (size_t i = 0; i < 8; i++)
		if (mel1->BlackPawnCounts[i] != mel2->BlackPawnCounts[i])
			Failed("BlackPawnCounts");

	for (size_t i = 0; i < 64; i++)
		if (mel1->board[i] != mel2->board[i])
			Failed("board");

	if (mel1->boardStateStack.GetCount() != mel2->boardStateStack.GetCount())
		Failed("boardStateStack.GetCount()");

	if (mel1->castle != mel2->castle)
		Failed("castle");

	if (mel1->EnemyBishopKey != mel2->EnemyBishopKey)
		Failed("EnemyBishopKey");

	if (mel1->enemyColorIndex != mel2->enemyColorIndex)
		Failed("enemyColorIndex");

	if (mel1->enemyColour != mel2->enemyColour)
		Failed("enemyColour");

	if (mel1->EnemyKingKey != mel2->EnemyKingKey)
		Failed("EnemyKingKey");

	if (mel1->enemyKingPieceVal != mel2->enemyKingPieceVal)
		Failed("enemyKingPieceVal");

	if (mel1->enemyKingPos != mel2->enemyKingPos)
		Failed("enemyKingPos");

	if (mel1->EnemyKnightKey != mel2->EnemyKnightKey)
		Failed("EnemyKnightKey");

	if (mel1->EnemyPawnKey != mel2->EnemyPawnKey)
		Failed("EnemyPawnKey");

	if (mel1->EnemyQueenKey != mel2->EnemyQueenKey)
		Failed("EnemyQueenKey");

	if (mel1->EnemyRookKey != mel2->EnemyRookKey)
		Failed("EnemyRookKey");

	if (mel1->EPSquare != mel2->EPSquare)
		Failed("EPSquare");

	if (mel1->gameState != mel2->gameState)
		Failed("gameState");

	if (mel1->KingInCheck != mel2->KingInCheck)
		Failed("KingInCheck");

	if (mel1->KingInDoubleCheck != mel2->KingInDoubleCheck)
		Failed("KingInDoubleCheck");

	if (mel1->kingPos[0] != mel2->kingPos[0])
		Failed("kingPos[0]");

	if (mel1->kingPos[1] != mel2->kingPos[1])
		Failed("kingPos[1]");

	for (size_t i = 0; i < mel1->movesCount; i++)
		if (mel1->moves[i] != mel2->moves[i])
			Failed("moves");

	if (mel1->movesCount != mel2->movesCount)
		Failed("movesCount");

	if (mel1->OurBishopKey != mel2->OurBishopKey)
		Failed("OurBishopKey");

	if (mel1->ourColor != mel2->ourColor)
		Failed("ourColor");

	if (mel1->ourColorIndex != mel2->ourColorIndex)
		Failed("ourColorIndex");

	if (mel1->ourKingBitboard != mel2->ourKingBitboard)
		Failed("ourKingBitboard");

	if (mel1->OurKingKey != mel2->OurKingKey)
		Failed("OurKingKey");

	if (mel1->ourKingPieceVal != mel2->ourKingPieceVal)
		Failed("ourKingPieceVal");

	if (mel1->ourKingPos != mel2->ourKingPos)
		Failed("ourKingPos");

	if (mel1->OurKnightKey != mel2->OurKnightKey)
		Failed("OurKnightKey");

	if (mel1->OurPawnKey != mel2->OurPawnKey)
		Failed("OurPawnKey");

	if (mel1->OurQueenKey != mel2->OurQueenKey)
		Failed("OurQueenKey");

	if (mel1->OurRookKey != mel2->OurRookKey)
		Failed("OurRookKey");

	for (size_t i = 0; i < 24; i++)
		if (mel1->pieceAttackBitboards[i] != mel2->pieceAttackBitboards[i])
			Failed("pieceAttackBitboards");

	for (size_t i = 0; i < 24; i++)
		if (mel1->PieceBitboardPos[i] != mel2->PieceBitboardPos[i])
			Failed("PieceBitboardPos");

	for (size_t i = 0; i < 24; i++)
	{
		if (mel1->PieceLists[i].PieceNum != mel2->PieceLists[i].PieceNum)
		{
			Failed("PieceLists[i].PieceNum");
		}
		else
		{
			int square1[64]{ 0 };
			int square2[64]{ 0 };
			for (size_t j = 0; j < mel1->PieceLists[i].PieceNum; j++)
			{
				//if (mel1->PieceLists[i].OccupiedSquares[j] != mel2->PieceLists[i].OccupiedSquares[j])
				//{
				//	Failed(std::string("PieceLists[") + FENUtility::IntToChar[i] + "].OccupiedSquares[" + std::to_string(j) + "]");
				//}
				square1[mel1->PieceLists[i].OccupiedSquares[j]]++;
				square2[mel2->PieceLists[i].OccupiedSquares[j]]++;
			}
			for (size_t k = 0; k < 64; k++)
			{
				if (square1[k] != square2[k])
				{
					Failed(std::string("PieceLists[") + FENUtility::IntToChar[i] + "] Square[" + std::to_string(k) + "]");
				}
			}
		}
	}

	if (mel1->pinnedPieces != mel2->pinnedPieces)
		Failed("pinnedPieces");

	for (size_t i = 0; i < 64; i++)
	{
		if (BitboardContains(mel1->pinnedPieces, i))
			if (mel1->pinningPiecesAttack != mel2->pinningPiecesAttack)
				Failed("pinningPiecesAttack");
	}

	if (mel1->playerTurn != mel2->playerTurn)
		Failed("playerTurn");

	for (size_t i = 0; i < 8; i++)
		if (mel1->WhitePawnCounts[i] != mel2->WhitePawnCounts[i])
			Failed("WhitePawnCounts[i]");

	if (mel1->whiteToMove != mel2->whiteToMove)
		Failed("whiteToMove");







	if (mel1->AllBlackPosBitboard != mel2->AllBlackPosBitboard)
		Failed("AllBlackPosBitboard");

}
