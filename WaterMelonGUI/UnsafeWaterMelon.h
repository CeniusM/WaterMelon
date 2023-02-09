#pragma once

#include <string>

#include "PieceList.h"
#include "FENUtility.h"
#include "Logger.h"
#include "TypesIncludes.h"


#pragma region Consts
constexpr int MaxMoves = 200;
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

	Move gameHistory[256];

	Piece board[64]{};
	CastleRight castle{};
	int EPSquare{};
	int playerTurn{};

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

	// Will consider the move completly valid, this can be done by making sure it comes from the generated moves
	void MakeMove(Move move);
	void UnMakeMove();

	void InitFEN(std::string FEN);
	std::string GetFEN();

	UnsafeWaterMelon();
	UnsafeWaterMelon(std::string FEN);
	~UnsafeWaterMelon();

	bool HasInit() { return m_HasInit; }
private:
	bool m_HasInit = false;
};

//#ifndef UsafeWaterMelonCPP
//#   include "UnsafeWaterMelon.cpp"
//#endif