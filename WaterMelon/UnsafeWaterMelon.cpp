

#include "UnsafeWaterMelon.h"

void UnsafeWaterMelon::MakeMove(Move move)
{
	Square startSquare = GetMoveStart(move);
	Square targetSquare = GetMoveTarget(move);
	MoveFlag flag = GetMoveFlag(move);

	Piece movingPiece = board[startSquare];
	PieceType movingPieceType = GetPieceType(movingPiece);
	Piece capturedPiece = board[targetSquare];
	PieceType capturedPieceType = GetPieceType(capturedPiece);

	whiteToMove = (playerTurn == 8);

	board[startSquare] = 0;
	board[targetSquare] = movingPiece;



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
	// Validate the FEN String...

	// will use the piece as index
	whitePawnsPtr = PieceLists[WPawn].OccupiedSquares;
	whiteKnightsPtr = PieceLists[WKnight].OccupiedSquares;
	whiteBishopsPtr = PieceLists[WBishop].OccupiedSquares;
	whiteRooksPtr = PieceLists[WRook].OccupiedSquares;
	whiteQueensPtr = PieceLists[WQueen].OccupiedSquares;

	blackPawnsPtr = PieceLists[BPawn].OccupiedSquares;
	blackKnightsPtr = PieceLists[BKnight].OccupiedSquares;
	blackBishopsPtr = PieceLists[BBishop].OccupiedSquares;
	blackRooksPtr = PieceLists[BRook].OccupiedSquares;
	blackQueensPtr = PieceLists[BQueen].OccupiedSquares;

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
					board[FlipSquareY(fenBoardPtr)] = pieceVal;

					if (pieceVal == WKing)
						kingPos[0] = FlipSquareY(fenBoardPtr);
					else if (pieceVal == BKing)
						kingPos[1] = FlipSquareY(fenBoardPtr);
					else
						PieceLists[pieceVal].AddPieceAtSquare(FlipSquareY(fenBoardPtr));
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

#pragma region Evaluation code

int UnsafeWaterMelon::GetEvaluation()
{
	// Bonus for material
	// Bonus for placement
	// Bonus for king safty, like maby bonus for pieces infront of the king early/mid game atlist
	// Bonus for being in team pawn attacks, and negBonus for being in oponent pawn -
	// - and use allready created bitboards
	// Early/Mid game, very low and heigh king moves count is bad, just need something in the middle -
	// -to many moves means its probely not protected enough, and less than 2 is probely also pretty bad
	// Ideer, give negBonus for pieces that have not moved, but a little tricky to implement
	// Bonus pawns for closing in on promotion, tricky to implement
	// Bonus for lategame getting agresiv torwards the enemy king to checkmate
	// Bonus for the bishop on the opesit color of the major pawn structor -
	// -so the fewer pawns the bishop shares space with the better, but this mostly counts for the mid of the board, -
	// -not so much far behind
	// Bonus for moving pawns up the board (unless they defend the king, and bonus for pawns closer to the enemy king -
	// but still the best bonuses for good pawn structure, the mentioned bonuses is just for something to work torwards

	if (movesCount == 0)
	{
		if (KingInCheck) // King in check
			return playerTurn == White ? -999999 : 999999;
		return 0;
	}





	return 0;
}

#pragma endregion


#pragma region Move generation code

#define PushMove(move) moves[movesCount] = (move); movesCount++;

void UnsafeWaterMelon::RemoveNoneCaptures()
{
	int newMovesCount = 0;
	for (size_t i = 0; i < movesCount; i++)
	{
		if (IsMoveCapture(moves[i]))
		{
			moves[newMovesCount] = moves[i];
			newMovesCount++;
		}
	}
	movesCount = newMovesCount;
}

void UnsafeWaterMelon::OrderMoves()
{
	int MovesGoneOver = 0;
	Move tempMove = 0;
#define SwapMoves(index1, index2) \
tempMove = moves[index1]; \
moves[index1] = moves[index2]; \
moves[index2] = tempMove; \
MovesGoneOver++;

	for (size_t i = MovesGoneOver; i < movesCount; i++) // QueenPromotions
	{
		if (GetMoveFlag(moves[i]) == MoveFlags::PromoteToQueen)
			SwapMoves(i, MovesGoneOver);
	}
	for (size_t i = MovesGoneOver; i < movesCount; i++) // Captures
	{
		if (IsMoveCapture(moves[i]))
			SwapMoves(i, MovesGoneOver);
	}
	for (size_t i = MovesGoneOver; i < movesCount; i++) // EnPassent
	{
		if (GetMoveFlag(moves[i]) == MoveFlags::EnPassantCapture)
			SwapMoves(i, MovesGoneOver);
	}
	for (size_t i = MovesGoneOver; i < movesCount; i++) // RestOfThePromotions
	{
		if (IsMovePromotion(moves[i]))
			SwapMoves(i, MovesGoneOver);
	}
	// Rest of moves
}

void UnsafeWaterMelon::GenerateBitboards()
{
	whitePawnAttacksBitboard = 0;
	blackPawnAttacksBitboard = 0;
	for (size_t i = 0; i < PieceLists[WPawn].PieceNum; i++)
		whitePawnAttacksBitboard |= GetWhitePawnAttacks(PieceLists[WPawn].OccupiedSquares[i]);
	for (size_t i = 0; i < PieceLists[BPawn].PieceNum; i++)
		blackPawnAttacksBitboard |= GetBlackPawnAttacks(PieceLists[BPawn].OccupiedSquares[i]);
	//Logger::Log(whitePawnAttacksBitboard);
	//Logger::Log(blackPawnAttacksBitboard);


}

void UnsafeWaterMelon::GeneratePinsAndAttacks()
{
	pinnedPieces = 0;
	allEnemyAttacks = 0;


}

void UnsafeWaterMelon::AddKingMoves()
{

}

void UnsafeWaterMelon::AddPawnMoves()
{
	if (whiteToMove)
	{
		for (size_t i = 0; i < PieceLists[WPawn].PieceNum; i++)
		{
			int pos = PieceLists[WPawn].OccupiedSquares[i];
			int leftPos = pos + 7;
			int rightPos = pos + 9;
			int oneMove = pos + 8;
			int twoMove = pos + 16;

			if (IsPiecePinned(pos))
			{
				if (BitboardContains(pinningPiecesAttack[pos] & whitePawnAttacksBitboard, leftPos)) // check valid attack and still block pin
					if (IsColor(GetColor(board[leftPos]), Black))
						PushMove(CreateMove(pos, leftPos, NoFlagCapture));
				if (BitboardContains(pinningPiecesAttack[pos] & whitePawnAttacksBitboard, rightPos))
					if (IsColor(GetColor(board[rightPos]), Black))
						PushMove(CreateMove(pos, rightPos, NoFlagCapture));

				if (BitboardContains(pinningPiecesAttack[pos], oneMove)) // if one move block pin, two move is also in pin
				{
					if (board[oneMove] == 0)
					{
						PushMove(CreateMove(pos, oneMove, NoFlag));
						if (board[twoMove] == 0 && BitboardContains(WhiteTwoMoveLine, pos))
							PushMove(CreateMove(pos, twoMove, PawnDoubleForward));
					}
				}
			}
			else
			{
				if (BitboardContains(whitePawnAttacksBitboard, leftPos))
					if (IsColor(GetColor(board[leftPos]), Black))
						PushMove(CreateMove(pos, leftPos, NoFlagCapture));
				if (BitboardContains(whitePawnAttacksBitboard, rightPos))
					if (IsColor(GetColor(board[rightPos]), Black))
						PushMove(CreateMove(pos, rightPos, NoFlagCapture));

				if (board[oneMove] == 0)
				{
					PushMove(CreateMove(pos, oneMove, NoFlag));
					if (board[twoMove] == 0 && BitboardContains(WhiteTwoMoveLine, pos))
						PushMove(CreateMove(pos, twoMove, PawnDoubleForward));
				}
			}
		}
		if (EPSquare != EmptyEnPassantPos)
		{

		}
	}
}

int UnsafeWaterMelon::GetPossibleMoves(Move* movesPtr, bool onlyCaptures, bool moveOrder)
{
	// -- Init --
	movesCount = 0;

	KingInCheck = false;
	KingInDoubleCheck = false;
	whiteToMove = playerTurn == 8;

	ourColorIndex = (int)whiteToMove;
	enemyColorIndex = (int)!whiteToMove;

	ourColour = playerTurn;
	enemyColour = playerTurn ^ PlayerTurnSwitch;

	ourKingPos = kingPos[ourColour >> 4];
	enemyKingPos = kingPos[enemyColour >> 4];

	GenerateBitboards();

	GeneratePinsAndAttacks();

	AddKingMoves();

	if (KingInDoubleCheck)
		return movesCount;

	if (KingInCheck)
	{
		// If king in check, only king moves and moves that block the attack works
		// So would only have to check if moves can block the line or capture the piece
		// So we know only one piece is attacking
		// If the attacking peice is a knight or a pawn, we create a bitmap with only the postision of the piece
		// So only moves where the non pinned piece move to the bitmap
		// And the same can be done with sliding pieces, where you have to move into any of the bitmap squares

		// Here we could combine the pinned piece and the attack on the king so we dont do more bitboard checks than needed
	}
	else
	{
		AddPawnMoves();
	}


	if (onlyCaptures)
		RemoveNoneCaptures();
	if (moveOrder)
		OrderMoves();

	memcpy_s(movesPtr, MaxMovesCount * sizeof(Move), moves, movesCount * sizeof(Move));
	return movesCount;
}

#pragma endregion