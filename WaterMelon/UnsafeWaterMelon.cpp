

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


		for (size_t i = 0; i < 64; i++)
		{
			if (board[i])
			{
				AllPiecePosBitboard |= (Bitboard)0b1 << i;
				PieceBitboardPos[board[i]] |= (Bitboard)0b1 << i;
			}
		}

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
if ((attacksOnKing & DotBiboards[move]) == 0)\
moves[movesCount] = (move); movesCount++;

#define PushMovePinCheck(move) \
if ((pinnedPieces & DotBiboards[move]) == 0)\
if ((attacksOnKing & DotBiboards[move]) == 0)\
moves[movesCount] = (move); movesCount++;

#define PushMovePinCheckAndCheckKingBlock(move) \
if ((pinnedPieces & DotBiboards[move]) == 0)\
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

void UnsafeWaterMelon::GeneratePinsAndAttacksOnKing() // This method cast a ray out in each direction
{
	Bitboard slidingPieces =
		PieceBitboardPos[Queen | enemyColour] |
		PieceBitboardPos[Rook | enemyColour] |
		PieceBitboardPos[Bishop | enemyColour];

	for (DirectionIndex i = 0; i < 8; i++) // The directions
	{
		if (GetQueenBitboardFromInDir(ourKingPos, i) & slidingPieces) // There is something there
		{
			Square rayPos = ourKingPos;
			Offset offset = offsetsIndexed[i];
			int DistanceToSide = GetDistanceToBoardInDirection(rayPos, i);

			bool DoublePiece = false;
			bool AttackBehindPiece = false;
			Square OurPiecePos = InvalidSquare;

			for (size_t i = 0; i < DistanceToSide; i++)
			{
				rayPos += offset;
				Piece piece = board[rayPos];
				if (piece) // piece is not empty
				{
					if (GetColor(piece) == ourColor)
					{
						if (OurPiecePos == InvalidSquare)
							OurPiecePos = rayPos;
						else
						{
							DoublePiece = true;
							break;
						}
					}
					else // Enemy
					{
						if (i & 0b100) // Diagonal
						{
							if (!IsBishopOrQueen(piece))
								continue;
						}
						else // Not Diagonal...
							if (!IsRookOrQueen(piece))
								continue;

						if (OurPiecePos == 0) // Attack On King
						{
							attacksOnKing = GetGetBitboardFromSquareToSquare(ourKingPos + offset, rayPos);
							if (KingInCheck)
							{
								KingInDoubleCheck = true;
								return;
							}
							else
								KingInCheck = true;
						}
						else // Piece Pinned
						{
							pinnedPieces |= DotBiboards[OurPiecePos];
							pinningPiecesAttack[OurPiecePos] |=
								GetGetBitboardFromSquareToSquare(ourKingPos + offset, rayPos);
						}
						break;
					}
				}
			}
		}

		if (pieceAttackBitboards[Knight | enemyColour] & ((Bitboard)0b1 << ourKingPos))
		{
			if (KingInCheck) // no need to know where the attack comes from
			{
				KingInDoubleCheck = true;
				return;
			}

			// There cant be more than 1 knight attacking the king
			for (size_t i = 0; i < 8; i++)
			{
				Square squareChecked = ourKingPos + KnightOffsetsIndexed[i];
				if (board[squareChecked] == (Knight & enemyColour))
				{
					KingInCheck = true;
					attacksOnKing |= (Bitboard)0b1 << squareChecked;
					break;
				}
			}
		}

		if (pieceAttackBitboards[Pawn | enemyColour] & ((Bitboard)0b1 << ourKingPos))
		{
			if (KingInCheck) // no need to know where the attack comes from
			{
				KingInDoubleCheck = true;
				return;
			}

			// There cant be more than 1 pawn attacking the king
			if (whiteToMove)
			{
				if (board[ourKingPos + 7] == BPawn)
				{
					KingInCheck = true;
					attacksOnKing |= (Bitboard)0b1 << ourKingPos + 7;
				}
				else
				{
					KingInCheck = true;
					attacksOnKing |= (Bitboard)0b1 << ourKingPos + 9;
				}
			}
			else
			{
				if (board[ourKingPos - 7] == BPawn)
				{
					KingInCheck = true;
					attacksOnKing |= (Bitboard)0b1 << ourKingPos - 7;
				}
				else
				{
					KingInCheck = true;
					attacksOnKing |= (Bitboard)0b1 << ourKingPos - 9;
				}
			}

		}
	}


	SquaresToRenderByGUIForDebuing.clear();
	for (size_t i = 0; i < 64; i++)
	{
		if (pinnedPieces & ((Bitboard)0b1 << i))
			SquaresToRenderByGUIForDebuing.push_front(i);
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

	GeneratePinsAndAttacksOnKing();

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