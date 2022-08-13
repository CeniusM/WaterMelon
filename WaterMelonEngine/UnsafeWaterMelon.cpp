

#include "UnsafeWaterMelon.h"

void UnsafeWaterMelon::MakeMove(Move* move)
{
    int startSquare = move->StartSquare;
    int targetSquare = move->TargetSquare;
    int capturedSquare = move->MoveFlag;
}

void UnsafeWaterMelon::UnMakeMove()
{

}

#pragma region Initilization
UnsafeWaterMelon::UnsafeWaterMelon()
{
    InitFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

UnsafeWaterMelon::UnsafeWaterMelon(std::string FEN)
{
    InitFEN(FEN);
}

UnsafeWaterMelon::~UnsafeWaterMelon()
{

}

void UnsafeWaterMelon::InitFEN(std::string FEN)
{
    // will use the piece as index
    for (int i = 0; i < 24; i++) // BQuenn 23
        allPieceLists[i] = nullptr;
    //9 WKing used with own array
    allPieceLists[10] = &WhitePawnsList;//10 WPawn
    allPieceLists[11] = &WhiteKnightsList;//11 WKnight
    allPieceLists[13] = &WhiteBishopsList;//13 WBishop
    allPieceLists[14] = &WhiteRooksList;//14 WRook
    allPieceLists[15] = &WhiteQueensList;//15 WQueen
    //17 BKing used with own array
    allPieceLists[18] = &BlackPawnsList;//18 BPawn
    allPieceLists[19] = &BlackKnightsList;//19 BKnight
    allPieceLists[21] = &BlackBishopsList;//21 BBishop
    allPieceLists[22] = &BlackRooksList;//22 BRook
    allPieceLists[23] = &BlackQueensList;//23 BQueen


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
                    board[fenBoardPtr] = FENUtility::CharToInt[piece];
                fenBoardPtr++;
            }
            fenPtr++;
        }fenPtr++;

        if (FEN[fenPtr] == 'b')
            playerTurn ^= PlayerTurnSwitch;
        fenPtr++;
        fenPtr++;

        while (true)
        {
            char piece = FEN[fenPtr];
            if (piece == ' ')
                break;
            if (piece == 'K')
                castle |= WhiteKingSideCastleRight;
            else if (piece == 'Q')
                castle |= WhiteQueenSideCastleRight;
            else if (piece == 'k')
                castle |= BlackKingSideCastleRight;
            else if (piece == 'q')
                castle |= BlackQueenSideCastleRight;
            fenPtr++;
        }fenPtr++;


        m_HasInit = true;
    }
    catch (const std::exception&)
    {
        m_HasInit = false;
    }
}
#pragma endregion

std::string UnsafeWaterMelon::GetFEN()
{
    std::string str = "";

    return str;
}