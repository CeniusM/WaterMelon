

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
	// Bonus pawns for closing in on promotion, tricky to implement, 
	// early game and good structure, get space, mid have good structure, end game good structure and try promotion
	// Bonus for lategame getting agresiv torwards the enemy king to checkmate
	// Bonus for the bishop on the opesit color of the major pawn structor -
	// -so the fewer pawns the bishop shares space with the better, but this mostly counts for the mid of the board, -
	// -not so much far behind
	// Bonus for moving pawns up the board (unless they defend the king, and bonus for pawns closer to the enemy king -
	// but still the best bonuses for good pawn structure, the mentioned bonuses is just for something to work torwards
	// Negbonus for checks and double checks

	if (movesCount == 0)
	{
		if (KingInCheck) // King in check
			return playerTurn == White ? -999999 : 999999;
		return 0;
	}

	int Evaluation = 0;

	if (true) // early game
	{
		constexpr int PawnEarlyGameValue = 100;
		constexpr int KnightEarlyGameValue = 400;
		constexpr int BishopEarlyGameValue = 440;
		constexpr int RookEarlyGameValue = 450;
		constexpr int QueenEarlyGameValue = 950;

		Evaluation += PieceLists[WPawn].PieceNum * PawnEarlyGameValue;
		Evaluation += PieceLists[WKnight].PieceNum * KnightEarlyGameValue;
		Evaluation += PieceLists[WBishop].PieceNum * BishopEarlyGameValue;
		Evaluation += PieceLists[WRook].PieceNum * RookEarlyGameValue;
		Evaluation += PieceLists[WQueen].PieceNum * QueenEarlyGameValue;

		Evaluation -= PieceLists[BPawn].PieceNum * PawnEarlyGameValue;
		Evaluation -= PieceLists[BKnight].PieceNum * KnightEarlyGameValue;
		Evaluation -= PieceLists[BBishop].PieceNum * BishopEarlyGameValue;
		Evaluation -= PieceLists[BRook].PieceNum * RookEarlyGameValue;
		Evaluation -= PieceLists[BQueen].PieceNum * QueenEarlyGameValue;

		//for (size_t i = 0; i < 64; i++) // For later
		//	Evaluation += GetBonusForPieceOnSquareEarlyGame(board[i], i); // Also use this for pawn collum bonus, and bonuses close to promotion
	}
	else if (false) // mid game
	{
		constexpr int PawnMidGameValue = 100;
		constexpr int KnightMidGameValue = 305;
		constexpr int BishopMidGameValue = 333;
		constexpr int RookMidGameValue = 563;
		constexpr int QueenMidGameValue = 950;
	}
	else // late game
	{
		constexpr int PawnlateGameValue = 100;
		constexpr int KnightlateGameValue = 305;
		constexpr int BishoplateGameValue = 333;
		constexpr int RooklateGameValue = 563;
		constexpr int QueenlateGameValue = 950;


	}


	return 0;
}

#pragma endregion


#pragma region Move generation code

#define PushMove(move) moves[movesCount] = (move); movesCount++;

#define PushMoveCheckKingBlock(move) \
if ((attacksOnKing & DotBiboards[move]) != 0)\
moves[movesCount] = (move); movesCount++;

#define PushMovePinCheck(move) \
if ((pinnedPieces & DotBiboards[move]) != 0)\
if ((attacksOnKing & DotBiboards[move]) != 0)\
moves[movesCount] = (move); movesCount++;

#define PushMovePinCheckAndCheckKingBlock(move) \
if ((pinnedPieces & DotBiboards[move]) != 0)\
moves[movesCount] = (move); movesCount++;




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
	// The sliding pieces will be initilized when they get there moves generated

	pieceAttackBitboards[WPawn] = 0;
	pieceAttackBitboards[WBishop] = 0;
	pieceAttackBitboards[WKnight] = 0;
	pieceAttackBitboards[WQueen] = 0;
	pieceAttackBitboards[WKing] = 0;
	pieceAttackBitboards[BPawn] = 0;
	pieceAttackBitboards[BBishop] = 0;
	pieceAttackBitboards[BKnight] = 0;
	pieceAttackBitboards[BQueen] = 0;
	pieceAttackBitboards[BKing] = 0;

	for (size_t i = 0; i < PieceLists[WPawn].PieceNum; i++)
		pieceAttackBitboards[WPawn] |= GetWhitePawnAttacks(PieceLists[WPawn].OccupiedSquares[i]);

	for (size_t i = 0; i < PieceLists[WKnight].PieceNum; i++)
		pieceAttackBitboards[WKnight] |= GetKnightAllDirBitboard(PieceLists[WKnight].OccupiedSquares[i]);

	for (size_t i = 0; i < PieceLists[WKing].PieceNum; i++)
		pieceAttackBitboards[WKing] |= GetKingAllDirBitboard(PieceLists[WKing].OccupiedSquares[i]);

	for (size_t i = 0; i < PieceLists[BPawn].PieceNum; i++)
		pieceAttackBitboards[BPawn] |= GetBlackPawnAttacks(PieceLists[BPawn].OccupiedSquares[i]);

	for (size_t i = 0; i < PieceLists[BKnight].PieceNum; i++)
		pieceAttackBitboards[BKnight] |= GetKnightAllDirBitboard(PieceLists[BKnight].OccupiedSquares[i]);

	for (size_t i = 0; i < PieceLists[BKing].PieceNum; i++)
		pieceAttackBitboards[BKing] |= GetKingAllDirBitboard(PieceLists[BKing].OccupiedSquares[i]);




	//Logger::Log(whitePawnAttacksBitboard);
	//Logger::Log(blackPawnAttacksBitboard);

	if (whiteToMove)
	{
		allFriendlyAttakcs |= pieceAttackBitboards[WPawn] | pieceAttackBitboards[WKnight] | pieceAttackBitboards[WKing];
		allEnemyAttacks |= pieceAttackBitboards[BPawn] | pieceAttackBitboards[BKnight] | pieceAttackBitboards[BKing];
	}
	else
	{
		allFriendlyAttakcs |= pieceAttackBitboards[BPawn] | pieceAttackBitboards[BKnight] | pieceAttackBitboards[BKing];
		allEnemyAttacks |= pieceAttackBitboards[WPawn] | pieceAttackBitboards[WKnight] | pieceAttackBitboards[WKing];
	}
}

void UnsafeWaterMelon::GeneratePinsAndAttacks()
{
#define AttackOnKingDetected(BitboardAttack) \
	attacksOnKing |= BitboardAttack;\
	if (KingInCheck)\
	{\
		KingInDoubleCheck = true; \
		return;\
	}\
	else\
		KingInCheck = true; \

	pinnedPieces = 0;
	allEnemyAttacks = 0;

	// Check if any queens is hitting the king
	if ((GetQueenAllDirBitboard(ourKingPos) & PieceBitboardPos[Queen & enemyColour]) != 0)
	{
		int queenIndex = -1;
		int queenIndexNumber2 = -1; // never going to need more that 2, becouas of double checks is plenty 
		if (PieceLists[Queen & enemyColour].PieceNum != 1)
		{
			for (size_t i = 0; i < PieceLists[Queen & enemyColour].PieceNum; i++)
				if (BitboardContains(GetQueenAllDirBitboard(ourKingPos), PieceLists[Queen & enemyColour].OccupiedSquares[i]) != 0)
				{
					if (queenIndex == -1)
						queenIndex = i;
					else
					{
						queenIndexNumber2 = i;
						break;
					}
				}
		}
		else
			queenIndex = 0;

		// Note, you can use the allFriendlyPosBitboard to see if there is no or some pieces blokcing
		// And you can also use the allEnemyPosBitboard, beacous if there is any of the enemys pices blocking its all done

		int queenPos = PieceLists[Queen & enemyColour].OccupiedSquares[queenIndex];
	DoQueenAgain:// Oof, goto label
		{
			DirectionIndex dirToQueen = GetDirectionIndexFromSquareToSquare(ourKingPos, queenPos);
			DirectionIndex dirToKing = GetDirectionIndexFromSquareToSquare(queenPos, ourKingPos);

			Bitboard queenLineOfSight = GetQueenBitboardFromInDir(queenPos, dirToKing);
			Bitboard kingLineOfSight = GetQueenBitboardFromInDir(ourKingPos, dirToQueen);

			bool NoEnemyPieceBlocking = (AllEnemyPosBitboard & queenLineOfSight) == 0;
			bool NoTeamPieceBlocking = (allFriendlyAttakcs & queenLineOfSight) == 0;

			if (NoEnemyPieceBlocking && NoTeamPieceBlocking)
			{
				AttackOnKingDetected(kingLineOfSight);
			}
			else if (NoEnemyPieceBlocking)
			{
				// look through line of seight
				Offset queenToKingOffset = offsetsIndexed[dirToKing];
				Square pinnedPiecePos = InvalidSquare;
				bool peiceAllreadyPinned = false;
				bool doublePeiceBlock = false;
				for (size_t i = 0; i < 123123; i++)
				{
					queenPos += queenToKingOffset;
					if (board[queenPos] != 0)
						if (board[queenPos] == ourKingPieceVal)
						{
							break;
						}
						else if (IsPieceColor(board[queenPos], ourColor))
						{
							pinnedPiecePos = queenPos;
							if (peiceAllreadyPinned)
							{
								doublePeiceBlock = true;
								break;
							}
							else
								peiceAllreadyPinned = true;
						}
				}
				if (!doublePeiceBlock) // no double block
				{
					pinnedPieces |= (0b1U << pinnedPiecePos);
					pinningPiecesAttack[pinnedPiecePos] |= kingLineOfSight;

				}
			}
		}
		if (queenIndexNumber2 != -1)
		{
			queenIndexNumber2 = -1;
			queenPos = PieceLists[Queen & enemyColour].OccupiedSquares[queenIndex];
			goto DoQueenAgain; // no good
		}
	}

	// Check if any rooks is hitting the king
	if ((GetRookAllDirBitboard(ourKingPos) & PieceBitboardPos[Rook & enemyColour]) != 0)
	{
		int rookIndex = 0; // rooks cant double check
		if (PieceLists[Rook & enemyColour].PieceNum != 1)
		{
			for (size_t i = 0; i < PieceLists[Rook & enemyColour].PieceNum; i++)
				if (BitboardContains(GetRookAllDirBitboard(ourKingPos), PieceLists[Rook & enemyColour].OccupiedSquares[i]) != 0)
				{
					rookIndex = i;
					break;
				}
		}


	}

	// Check if any bishops is hitting the king
	if ((GetBishopAllDirBitboard(ourKingPos) & PieceBitboardPos[Bishop & enemyColour]) != 0)
	{
		int bishopIndex = 0; // bishops cant double check
		if (PieceLists[Bishop & enemyColour].PieceNum != 1)
		{
			for (size_t i = 0; i < PieceLists[Bishop & enemyColour].PieceNum; i++)
				if (BitboardContains(GetBishopAllDirBitboard(ourKingPos), PieceLists[Bishop & enemyColour].OccupiedSquares[i]) != 0)
				{
					bishopIndex = i;
					break;
				}
		}


	}

	// Now we just check for direct attakcs on the king

	// Enemy king, knight and pawns
	if (BitboardContains(allEnemyAttacks, ourKingPos))
	{
		// Something is hitting king

		// check pawns
		if (BitboardContains(pieceAttackBitboards[Pawn & enemyColour], ourKingPos))
		{

		}

		// check knight
		if (BitboardContains(pieceAttackBitboards[Knight & enemyColour], ourKingPos))
		{

		}

		// king is not relevant
	}
}

void UnsafeWaterMelon::AddKingMoves()
{

}

void UnsafeWaterMelon::AddPawnMoves()
{
	if (whiteToMove)
	{
		Bitboard whitePawnAttacksBitboard = pieceAttackBitboards[WPawn];
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
					if (IsPieceColor(GetColor(board[leftPos]), Black))
						PushMoveCheckKingBlock(CreateMove(pos, leftPos, NoFlagCapture));
				if (BitboardContains(pinningPiecesAttack[pos] & whitePawnAttacksBitboard, rightPos))
					if (IsPieceColor(GetColor(board[rightPos]), Black))
						PushMoveCheckKingBlock(CreateMove(pos, rightPos, NoFlagCapture));

				if (BitboardContains(pinningPiecesAttack[pos], oneMove)) // if one move block pin, two move is also in pin
				{
					if (board[oneMove] == 0)
					{
						PushMoveCheckKingBlock(CreateMove(pos, oneMove, NoFlag));
						if (board[twoMove] == 0 && BitboardContains(WhiteTwoMoveLine, pos))
							PushMoveCheckKingBlock(CreateMove(pos, twoMove, PawnDoubleForward));
					}
				}
			}
			else
			{
				if (BitboardContains(whitePawnAttacksBitboard, leftPos))
					if (IsPieceColor(GetColor(board[leftPos]), Black))
						PushMoveCheckKingBlock(CreateMove(pos, leftPos, NoFlagCapture));
				if (BitboardContains(whitePawnAttacksBitboard, rightPos))
					if (IsPieceColor(GetColor(board[rightPos]), Black))
						PushMoveCheckKingBlock(CreateMove(pos, rightPos, NoFlagCapture));

				if (board[oneMove] == 0)
				{
					PushMoveCheckKingBlock(CreateMove(pos, oneMove, NoFlag));
					if (board[twoMove] == 0 && BitboardContains(WhiteTwoMoveLine, pos))
						PushMoveCheckKingBlock(CreateMove(pos, twoMove, PawnDoubleForward));
				}
			}
		}
		if (EPSquare != EmptyEnPassantPos)
		{
			// becous Enpassant moves two pieces, we do the King check check here.
			// Just check if the king is on the same rank, and if there by chance 
			// also is an enemy queen or rook on the same diagonal


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

	ourColor = playerTurn;
	enemyColour = playerTurn ^ PlayerTurnSwitch;

	ourKingPos = kingPos[ourColor >> 4];
	enemyKingPos = kingPos[enemyColour >> 4];

	GenerateBitboards();

	GeneratePinsAndAttacks();

	AddKingMoves();

	if (KingInDoubleCheck)
		return movesCount;

	AddPawnMoves();

	if (onlyCaptures)
		RemoveNoneCaptures();
	if (moveOrder)
		OrderMoves();

	memcpy_s(movesPtr, MaxMovesCount * sizeof(Move), moves, movesCount * sizeof(Move));
	return movesCount;
}

#pragma endregion




/*

Code for later

// 4 difrent versions
	// pinned with king in check (slowsts...)
	// pinned with king NOT in check
	// no pin with king in check
	// no pin with king NOT in check (fastest...)

	// -- King in check --
	// If king in check, only king moves and moves that block the attack works
	// So would only have to check if moves can block the line or capture the piece
	// So we know only one piece is attacking
	// If the attacking peice is a knight or a pawn, we create a bitmap with only the postision of the piece
	// So only moves where the non pinned piece move to the bitmap
	// And the same can be done with sliding pieces, where you have to move into any of the bitmap squares

	// Here we could combine the pinned piece and the attack on the king so we dont do more bitboard checks than needed

	if (pinnedPieces == 0)
	{
		if (KingInCheck)
		{
		}
		else
		{
		}
	}
	else
	{
		AddPawnMovesPinnedAndKingNotInCheckVersion();
		if (KingInCheck)
		{
		}
		else
		{
		}
	}

*/