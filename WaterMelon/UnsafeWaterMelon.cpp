

#include "UnsafeWaterMelon.h"

void UnsafeWaterMelon::MakeMove(Move move)
{
	Square startSquare = GetMoveStart(move);
	Square targetSquare = GetMoveTarget(move);
	MoveFlag flag = GetMoveFlag(move);

	Piece movingPiece = GetPieceType(board[startSquare]);
	Piece capturedPiece = GetPieceType(board[targetSquare]);

	whiteToMove = (playerTurn == 8);





	playerTurn ^= PlayerTurnSwitch;
}

void UnsafeWaterMelon::UnMakeMove()
{

	playerTurn ^= PlayerTurnSwitch;
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

	whitePawnsPtr = WhitePawnsList.OccupiedSquares;
	whiteKnightsPtr = WhiteKnightsList.OccupiedSquares;
	whiteBishopsPtr = WhiteBishopsList.OccupiedSquares;
	whiteRooksPtr = WhiteRooksList.OccupiedSquares;
	whiteQueensPtr = WhiteQueensList.OccupiedSquares;

	blackPawnsPtr = BlackPawnsList.OccupiedSquares;
	blackKnightsPtr = BlackKnightsList.OccupiedSquares;
	blackBishopsPtr = BlackBishopsList.OccupiedSquares;
	blackRooksPtr = BlackRooksList.OccupiedSquares;
	blackQueensPtr = BlackQueensList.OccupiedSquares;

	playerTurn = 8;
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
				{
					Piece pieceVal = FENUtility::CharToInt[piece];
					board[fenBoardPtr] = pieceVal;

					if (pieceVal == WKing)
						kingPos[0] = fenBoardPtr;
					else if (pieceVal == BKing)
						kingPos[1] = fenBoardPtr;
					else
						allPieceLists[pieceVal]->AddPieceAtSquare(fenBoardPtr);
				}
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
				castle |= CastleRights::WhiteKingSide;
			else if (piece == 'Q')
				castle |= CastleRights::WhiteQueenSide;
			else if (piece == 'k')
				castle |= CastleRights::BlackKingSide;
			else if (piece == 'q')
				castle |= CastleRights::BlackQueenSide;
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
	ThrowNotImplementedException("The GetFEN function is not implemented");
	std::string str = "";

	return str;
}

#pragma region Move generation code

#define PushMove(move) tempMoves[tempMovesCount] = (move); tempMovesCount++;

int UnsafeWaterMelon::GetPossibleMoves(Move* moves)
{
	tempMovesCount = 0;

	for (size_t i = 0; i < 63; i++)
	{
		PushMove(CreateMove(i, 16, 0));
	}

	memcpy_s(moves, MaxMovesCount * sizeof(Move), tempMoves, tempMovesCount * sizeof(Move));
	return tempMovesCount;
}

#pragma endregion