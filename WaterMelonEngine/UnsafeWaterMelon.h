#pragma once

#include <string>

#include "PieceList.h"
#include "FENUtility.h"
#include "Move.h"

#pragma region Consts
constexpr int MaxMoves = 200;
constexpr int WhiteIndex = 0;
constexpr int BlackIndex = 1;
     
constexpr int WhiteCastleRights = 0b1100;
constexpr int WhiteKingSideCastleRight = 0b1000;
constexpr int WhiteQueenSideCastleRight = 0b0100;
constexpr int BlackKingSideCastleRight = 0b0010;
constexpr int BlackCastleRights = 0b0011;
constexpr int BlackQueenSideCastleRight = 0b0001;
     
constexpr int PlayerTurnSwitch = 0b11000;
#pragma endregion

class UnsafeWaterMelon
{
public:
    int gameHistory[256];

	char board[64]{};
	int castle{};
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

    int* whitePawnsPtr;
    int* whiteKnightsPtr;
    int* whiteBishopsPtr;
    int* whiteRooksPtr;
    int* whiteQueensPtr;
    int* blackPawnsPtr;
    int* blackKnightsPtr;
    int* blackBishopsPtr;
    int* blackRooksPtr;
    int* blackQueensPtr;
#pragma endregion

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
