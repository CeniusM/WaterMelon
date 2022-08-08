#pragma once

#include <string>
#include <cctype>

#include "PieceList.h"
#include "FENUtility.h"

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


	char* boardPtr;
	int castle;
	int EPSquare;
	int playerTurn;
	
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

    PieceList allPieceLists;

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



    void InitFEN(std::string FEN);
    std::string GetFEN();

	UnsafeWaterMelon();
	~UnsafeWaterMelon();
private:
    
};

UnsafeWaterMelon::UnsafeWaterMelon()
{
    whitePawnsPtr = WhitePawnsList.occupiedPtr;
    whiteKnightsPtr = WhiteKnightsList.occupiedPtr;
    whiteBishopsPtr = WhiteBishopsList.occupiedPtr;
    whiteRooksPtr = WhiteRooksList.occupiedPtr;
    whiteQueensPtr = WhiteQueensList.occupiedPtr;

    blackPawnsPtr = BlackPawnsList.occupiedPtr;
    blackKnightsPtr = BlackKnightsList.occupiedPtr;
    blackBishopsPtr = BlackBishopsList.occupiedPtr;
    blackRooksPtr = BlackRooksList.occupiedPtr;
    blackQueensPtr = BlackQueensList.occupiedPtr;

    boardPtr = new char[64];

    InitFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

UnsafeWaterMelon::~UnsafeWaterMelon()
{
    delete[] boardPtr;
}

void UnsafeWaterMelon::InitFEN(std::string FEN)
{
    try
    {
    int fenPtr = 0;
    int fenBoardPtr = 0;
    while (true)
    {
        char piece = FEN[fenPtr];
        if (piece == ' ')
            break;
        if (piece != '/')
        {
            if (isdigit(piece))
                fenBoardPtr += piece - '0' - 1;
            else
                boardPtr[fenBoardPtr] = FENUtility::CharToInt[piece];
            fenBoardPtr++;
        }
        fenPtr++;
    }
    }
    catch (const std::exception&)
    {
        std::cout << "INVALID FEN";
    }

    for (int i = 0; i < 64; i++)
        std::cout << FENUtility::IntToChar[boardPtr[i]];
}

std::string UnsafeWaterMelon::GetFEN()
{
    std::string str = "";

    return str;
}