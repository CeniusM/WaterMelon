#pragma once

#include "UnsafeWaterMelon.h"

class SafeWaterMelon
{
public:
	SafeWaterMelon();
	SafeWaterMelon(std::string FEN);
	~SafeWaterMelon();

	bool MakeMove(Move move);
	bool UnMakeMove();

	Piece GetSquare(Square square);
	Color GetPlayerColour();
	void GetMovesCopy(Move* moves);
	Move* GetMovePointer();
	int GetMovesCount();
	void TurnBoard180();
	//bool IsKingInCheck();

	UnsafeWaterMelon* GetUnsafeBoardPtr();

private:
	UnsafeWaterMelon* _board;
	Move _moves[MaxMovesCount];
	int _movesCount = 0;

	/// Transforms the move Start and Target square
	Move TransfomMove(Move move);

	/// Turns a human square into a unsafe square
	Square TransformSquareToUnsafe(Square square);
	/// Turns a unsafe square into a human square
	Square TransformSquareToHuman(Square square);
	bool isBoardRotated180 = true;
};