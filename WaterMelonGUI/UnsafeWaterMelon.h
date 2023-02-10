#pragma once

#include <string>

#include "PieceList.h"
#include "FENUtility.h"
#include "Logger.h"
#include "TypesIncludes.h"

#define MaxMovesCount 512


#pragma region Consts
constexpr int MaxMoves = MaxMovesCount;
constexpr int WhiteIndex = 0;
constexpr int BlackIndex = 1;

constexpr int PlayerTurnSwitch = 0b11000;
#pragma endregion



/// <summary>
/// Used to make moves on the board, and can generate possible moves from the given position
/// </summary>
class UnsafeWaterMelon
{
public:
	GameState gameState = GameStates::Running;

	BoardStateSave boardStateHistory[256];

	Piece board[64]{};
	CastleRight castle{};
	int EPSquare{};
	int playerTurn{};


	// Will consider the move completly valid, this can be done by making sure it comes from the generated moves
	void MakeMove(Move move);
	void UnMakeMove();

	/// This will generate the moves and copy them to the pointer, and return the count. The pointer size is expected to be atlist "MaxMovesCount"
	int GetPossibleMoves(Move* moves);

	void InitFEN(std::string FEN);
	std::string GetFEN();

	UnsafeWaterMelon();
	UnsafeWaterMelon(std::string FEN);
	~UnsafeWaterMelon();

	bool HasInit() { return m_HasInit; }
	bool m_HasInit = false;


#pragma region Move generation code

	int kingPos[2]{};

#pragma region Everything PieceList
	PieceList WhitePawnsList{};
	PieceList WhiteKnightsList{};
	PieceList WhiteBishopsList{};
	PieceList WhiteRooksList{};
	PieceList WhiteQueensList{};

	PieceList BlackPawnsList{};
	PieceList BlackKnightsList{};
	PieceList BlackBishopsList{};
	PieceList BlackRooksList{};
	PieceList BlackQueensList{};

	PieceList* allPieceLists[24]; // BQueen 23

	Piece* whitePawnsPtr;
	Piece* whiteKnightsPtr;
	Piece* whiteBishopsPtr;
	Piece* whiteRooksPtr;
	Piece* whiteQueensPtr;
	Piece* blackPawnsPtr;
	Piece* blackKnightsPtr;
	Piece* blackBishopsPtr;
	Piece* blackRooksPtr;
	Piece* blackQueensPtr;
#pragma endregion

	Bitboard kingPins{};

	Move* tempMoves;
	int tempMovesCount;

#pragma endregion
private:
};

//#ifndef UsafeWaterMelonCPP
//#   include "UnsafeWaterMelon.cpp"
//#endif