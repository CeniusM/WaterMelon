#pragma once

#define EnableSquareTransform false

#include "UnsafeWaterMelon.h"

/// <summary>
/// This created to be used as an interface between the fast and very unsafe engine UnsafeWaterMelon
/// </summary>
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

	/// Flips the square between Unsafe and UI square
	Square TransformSquare(Square square);
	bool isBoardRotated180 = false;
};