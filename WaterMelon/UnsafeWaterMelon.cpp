

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

	Bitboard moveBitboard = ((Bitboard)0b1 << startSquare) | ((Bitboard)0b1 << targetSquare);

	if (capturedPiece)
		PieceLists[capturedPiece].RemovePieceAtSquare(targetSquare);
	PieceLists[movingPiece].MovePiece(startSquare, targetSquare);

	if (capturedPiece)
	{
		AllPiecePosBitboard ^= (Bitboard)0b1 << targetSquare;
		PieceBitboardPos[capturedPiece] ^= (Bitboard)0b1 << targetSquare;
	}
	AllPiecePosBitboard ^= moveBitboard;
	PieceBitboardPos[movingPiece] ^= moveBitboard;

	board[startSquare] = 0;
	board[targetSquare] = movingPiece;

	if (movingPiece == OurKingKey)
		kingPos[ourColorIndex] = targetSquare;

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

	GetPossibleMoves(moves); // init boards
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

//#define PushMove(move) moves[movesCount] = (move); movesCount++;
//
//#define PushMoveCheckKingBlock(move) \
//if ((attacksOnKing & DotBiboards[move]) == 0)\
//moves[movesCount] = (move); movesCount++;
//
//#define PushMovePinCheck(move) \
//if ((pinnedPieces & DotBiboards[move]) == 0)\
//if ((attacksOnKing & DotBiboards[move]) == 0)\
//moves[movesCount] = (move); movesCount++;
//
//#define PushMovePinCheckAndCheckKingBlock(move) \
//if ((pinnedPieces & DotBiboards[move]) == 0)\
//moves[movesCount] = (move); movesCount++;




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

	allFriendlyAttakcs = 0;
	allEnemyAttacks = 0;

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

	pieceAttackBitboards[WKing] |= GetKingAllDirBitboard(kingPos[0]);

	for (size_t i = 0; i < PieceLists[BPawn].PieceNum; i++)
		pieceAttackBitboards[BPawn] |= GetBlackPawnAttacks(PieceLists[BPawn].OccupiedSquares[i]);

	for (size_t i = 0; i < PieceLists[BKnight].PieceNum; i++)
		pieceAttackBitboards[BKnight] |= GetKnightAllDirBitboard(PieceLists[BKnight].OccupiedSquares[i]);

	pieceAttackBitboards[BKing] |= GetKingAllDirBitboard(kingPos[1]);




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
	pinnedPieces = 0;

	Bitboard slidingPieces =
		PieceBitboardPos[Queen | enemyColour] |
		PieceBitboardPos[Rook | enemyColour] |
		PieceBitboardPos[Bishop | enemyColour];

	for (DirectionIndex dir = 0; dir < 8; dir++) // The directions
	{
		if (GetSlidingPieceBitboardFromInDir(ourKingPos, dir) & slidingPieces) // There is something there
		{
			if (dir == DirectionIndexs::SouthWestI)
				std::cout << "";
			std::cout << dir;

			Bitboard rayBoard = 0;

			Square rayPos = ourKingPos;
			Offset offset = offsetsIndexed[dir];
			int DistanceToSide = GetDistanceToBoardInDirection(rayPos, dir);

			bool DoublePiece = false;
			bool AttackBehindPiece = false;
			Square OurPiecePos = InvalidSquare;

			while (DistanceToSide--)
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
						if (dir & 0b100) // Diagonal
						{
							if (!IsBishopOrQueen(piece))
								break;
						}
						else // Not Diagonal...
							if (!IsRookOrQueen(piece))
								break;

						if (OurPiecePos == InvalidSquare) // Attack On King
						{
							//attacksOnKing = GetGetBitboardFromSquareToSquare(ourKingPos + offset, rayPos);
							attacksOnKing = rayBoard;
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
							rayBoard |= ((Bitboard)0b1 << rayPos);
							pinnedPieces |= DotBiboards[OurPiecePos];
							pinningPiecesAttack[OurPiecePos] = rayBoard;
						}
						break;
					}
				}
				rayBoard |= ((Bitboard)0b1 << rayPos);
			}

			Logger::LogBitboard(pinnedPieces);
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

	SquaresToRenderByGUIForDebuing.clear();
	if (KingInDoubleCheck)
		Logger::Log("King under double attack");
	else if (KingInCheck)
		Logger::Log("King under attack");
	else
		Logger::Log("King NOT under attack");
	Logger::Log("AttacksOnKing:\n");
	Logger::LogBitboard(attacksOnKing);
	Logger::Log("PinnedPieces:\n");
	Logger::LogBitboard(pinnedPieces);
	for (size_t i = 0; i < 64; i++)
	{
		if (pinnedPieces & ((Bitboard)0b1 << i))
		{
			Logger::Log(std::to_string(i) + "\n");
			Logger::LogBitboard(pinningPiecesAttack[i]);
			Logger::Log("\n");

			SquaresToRenderByGUIForDebuing.push_front(i);
		}

	}
}

void UnsafeWaterMelon::AddKingMoves()
{
	constexpr Offset Kingmoves[]
	{ -9,-8,-7,-1,1,7,8,9 };
	constexpr Offset KingmovesLineoffsets[]
	{ -1,-1,-1,0,0,1,1,1 };
	// plz unwrap mister compiler
	for (size_t i = 0; i < 8; i++)
	{
		int newPos = ourKingPos + Kingmoves[i];
		if ((newPos >> 3) - KingmovesLineoffsets[i] != ourKingPos >> 3)
			continue;
		if (IsSquareInBounds(newPos))
		{
			if (board[newPos])
			{
				if (board[newPos] & enemyColour)
				{
					board[ourKingPos] = 0;
					if (IsSquareSafe(newPos))
						PushMove(CreateMove(ourKingPos, newPos, MoveFlags::NoFlagCapture));
					board[ourKingPos] = OurKingKey;
				}
			}
			else
			{
				board[ourKingPos] = 0;
				if (IsSquareSafe(newPos))
					PushMove(CreateMove(ourKingPos, newPos, MoveFlags::NoFlag));
				board[ourKingPos] = OurKingKey;
			}
		}
	}
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
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, leftPos, NoFlagCapture));
				if (BitboardContains(pinningPiecesAttack[pos] & whitePawnAttacksBitboard, rightPos))
					if (IsPieceColor(GetColor(board[rightPos]), Black))
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, rightPos, NoFlagCapture));

				if (BitboardContains(pinningPiecesAttack[pos], oneMove)) // if one move block pin, two move is also in pin
				{
					if (board[oneMove] == 0)
					{
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, oneMove, NoFlag));
						if (board[twoMove] == 0 && BitboardContains(WhiteTwoMoveLine, pos))
							PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, twoMove, PawnDoubleForward));
					}
				}
			}
			else
			{
				if (BitboardContains(whitePawnAttacksBitboard, leftPos))
					if (IsPieceColor(GetColor(board[leftPos]), Black))
						PushMoveIfKingNotInCheck(CreateMove(pos, leftPos, NoFlagCapture));
				if (BitboardContains(whitePawnAttacksBitboard, rightPos))
					if (IsPieceColor(GetColor(board[rightPos]), Black))
						PushMoveIfKingNotInCheck(CreateMove(pos, rightPos, NoFlagCapture));

				if (board[oneMove] == 0)
				{
					PushMoveIfKingNotInCheck(CreateMove(pos, oneMove, NoFlag));
					if (board[twoMove] == 0 && BitboardContains(WhiteTwoMoveLine, pos))
						PushMoveIfKingNotInCheck(CreateMove(pos, twoMove, PawnDoubleForward));
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

bool UnsafeWaterMelon::IsSquareSafe(Square square)
{
	//Logger::LogBitboard(allEnemyAttacks);

	if (BitboardContains(allEnemyAttacks, square))
		return false;

	//Logger::LogBitboard(PieceBitboardPos[EnemyQueenKey]);
	Bitboard kingQueenRays = GetSlidingPieceAllDirBitboard(square);
	if (BitboardsCollide(kingQueenRays, PieceBitboardPos[EnemyQueenKey]))
	{
		// Queen hitting

		// Method 1, use a loop to find all the queens around in the difrent directions
		for (DirectionIndex i = QueenStartDirectionIndex; i < QueenEndDirectionIndex; i++)
		{
			if (BitboardsCollide(GetSlidingPieceBitboardFromInDir(square, i), PieceBitboardPos[EnemyQueenKey]))
			{
				// Is a hit
				Offset offset = offsetsIndexed[i];
				Square ray = square;
				int distance = GetDistanceToBoardInDirection(square, i);
				for (size_t i = 0; i < distance; i++)
				{
					ray += offset;
					Square piece = board[ray];
					if (piece)
					{
						if (piece == EnemyQueenKey)
							return false;
						break; // Hit someting else
					}
				}
			}
		}

		// Method 2, find the queen and index into pre data to find the direction
		//int count = PieceLists[EnemyQueenKey].PieceNum;
		//for (size_t i = 0; i < count; i++)
		//{
		//	if (BitboardContains(kingQueenRays, PieceLists[EnemyQueenKey].OccupiedSquares[i])) // hit by king rays
		//	{
		//		// Then get the bitboard with squares BETWEEN the two pieces and check that AllPiecesBitboard does not colide with it
		//	}
		//}
	}
	//Logger::LogBitboard(GetBishopAllDirBitboard(square));
	//Logger::LogBitboard(PieceBitboardPos[EnemyBishopKey]);
	if (BitboardsCollide(GetBishopAllDirBitboard(square), PieceBitboardPos[EnemyBishopKey]))
	{
		// Bishop hitting
		for (DirectionIndex i = BishopStartDirectionIndex; i < BishopEndDirectionIndex; i++)
		{
			//Logger::Log("--------");
			//Logger::LogBitboard(GetSlidingPieceBitboardFromInDir(square, i));
			//Logger::Log("--------");
			if (BitboardsCollide(GetSlidingPieceBitboardFromInDir(square, i), PieceBitboardPos[EnemyBishopKey]))
			{
				// Is a hit
				Offset offset = offsetsIndexed[i];
				Square ray = square;
				int distance = GetDistanceToBoardInDirection(square, i);
				for (size_t i = 0; i < distance; i++)
				{
					ray += offset;
					Square piece = board[ray];
					if (piece)
					{
						if (piece == EnemyBishopKey)
							return false;
						break; // Hit someting else
					}
				}
			}
		}
	}
	//Logger::Log("--------");
	//Logger::LogBitboard(PieceBitboardPos[EnemyRookKey]);
	//Logger::Log("--------");
	//Logger::LogBitboard(GetRookAllDirBitboard(square));
	//Logger::Log("--------");
	if (BitboardsCollide(GetRookAllDirBitboard(square), PieceBitboardPos[EnemyRookKey]))
	{
		// Rook hitting
		for (DirectionIndex i = RookStartDirectionIndex; i < RookEndDirectionIndex; i++)
		{
			//Logger::Log("--------");
			//Logger::LogBitboard(GetSlidingPieceBitboardFromInDir(square, i));
			//Logger::Log("--------");
			if (BitboardsCollide(GetSlidingPieceBitboardFromInDir(square, i), PieceBitboardPos[EnemyRookKey]))
			{
				// Is a hit
				Offset offset = offsetsIndexed[i];
				Square ray = square;
				int distance = GetDistanceToBoardInDirection(square, i);
				for (size_t i = 0; i < distance; i++)
				{
					ray += offset;
					Square piece = board[ray];
					if (piece)
					{
						if (piece == EnemyRookKey)
							return false;
						break; // Hit someting else
					}
				}
			}
		}
	}

	return true;
}

void UnsafeWaterMelon::AddQueenMoves()
{
	Piece pieceKey = Queen | ourColor;
	int count = PieceLists[pieceKey].PieceNum;
	for (size_t i = 0; i < count; i++)
	{
		Square pos = PieceLists[pieceKey].OccupiedSquares[i];

	}
}

void UnsafeWaterMelon::PushMove(Move move)
{
	moves[movesCount++] = move;
}

void UnsafeWaterMelon::PushMoveIfPinnsAllow(Move move)
{
	Square start = GetMoveStart(move);
	Bitboard AND = pinnedPieces & ((Bitboard)0b1 << start);
	if (AND) // Is pinned
	{
		if (pinningPiecesAttack[start] & AND) // Blocks pin
			PushMove(move);
	}
	else
	{
		PushMove(move);
	}
}

void UnsafeWaterMelon::PushMoveIfPinnsAllowAndKingNotInCheck(Move move)
{
	Square start = GetMoveStart(move);
	Square target = GetMoveTarget(move);
	Bitboard AND = pinnedPieces & ((Bitboard)0b1 << start);
	if (AND) // Is pinned
	{
		if (pinningPiecesAttack[start] & AND) // Blocks pin
			if (BitboardContains(attacksOnKing, target) || !KingInCheck) // blocks check
				PushMove(move);
	}
	else
	{
		if (BitboardContains(attacksOnKing, target))
			PushMove(move);
	}
}

void UnsafeWaterMelon::PushMoveIfKingNotInCheck(Move move)
{
	if (!KingInCheck)
		PushMove(move);
	Square target = GetMoveTarget(move);
	if (BitboardContains(attacksOnKing, target) || !KingInCheck) // blocks check
		PushMove(move);
}

int UnsafeWaterMelon::GetPossibleMoves(Move* movesPtr, bool onlyCaptures, bool moveOrder)
{
	//SquaresToRenderByGUIForDebuing.clear();
	// -- Init --
	movesCount = 0;

	KingInCheck = false;
	KingInDoubleCheck = false;
	whiteToMove = playerTurn == 8;

	ourColorIndex = (int)!whiteToMove;
	enemyColorIndex = (int)whiteToMove;

	ourColor = playerTurn;
	enemyColour = playerTurn ^ PlayerTurnSwitch;

	ourKingPos = kingPos[ourColor >> 4];
	enemyKingPos = kingPos[enemyColour >> 4];

	if (whiteToMove)
	{
		OurPawnKey = WPawn;
		OurKnightKey = WKnight;
		OurBishopKey = WBishop;
		OurRookKey = WRook;
		OurQueenKey = WQueen;
		OurKingKey = WKing;
		EnemyPawnKey = BPawn;
		EnemyKnightKey = BKnight;
		EnemyBishopKey = BBishop;
		EnemyRookKey = BRook;
		EnemyQueenKey = BQueen;
		EnemyKingKey = BKing;
	}
	else
	{
		EnemyPawnKey = WPawn;
		EnemyKnightKey = WKnight;
		EnemyBishopKey = WBishop;
		EnemyRookKey = WRook;
		EnemyQueenKey = WQueen;
		EnemyKingKey = WKing;
		OurPawnKey = BPawn;
		OurKnightKey = BKnight;
		OurBishopKey = BBishop;
		OurRookKey = BRook;
		OurQueenKey = BQueen;
		OurKingKey = BKing;
	}



	GenerateBitboards();

	GeneratePinsAndAttacksOnKing();

	AddKingMoves();

	if (KingInDoubleCheck)
	{
		memcpy_s(movesPtr, MaxMovesCount * sizeof(Move), moves, movesCount * sizeof(Move));
		return movesCount;
	}

	AddPawnMoves();

	for (size_t i = 0; i < movesCount; i++)
		SquaresToRenderByGUIForDebuing.push_front(GetMoveTarget(moves[i]));

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