

#include "UnsafeWaterMelon.hpp"

// Can NOT use any of the data that get initilized at the GetPossibleMoves, beacous this could be called after a UnMakeMove
void UnsafeWaterMelon::MakeMove(Move move)
{
	Square startSquare = GetMoveStart(move);
	Square targetSquare = GetMoveTarget(move);
	MoveFlag flag = GetMoveFlag(move);

	Bitboard startBit = BitboardFromSquare(startSquare);
	Bitboard targetBit = BitboardFromSquare(targetSquare);

	Piece movingPiece = board[startSquare];
	PieceType movingPieceType = GetPieceType(movingPiece);
	Piece capturedPiece = board[targetSquare];
	PieceType capturedPieceType = GetPieceType(capturedPiece);

	Bitboard moveBitboard = startBit | targetBit;

	Color OurColor = playerTurn;
	int OurColorIndex = playerTurn >> 4;
	bool IsWhiteToMove = !(bool)OurColorIndex;

	BoardState stateSave{ move, capturedPiece, EPSquare, castle, 0, KingInCheck, KingInDoubleCheck };


	// Debbuging
	//if (targetSquare == kingPos[0])
	//	std::cout << "king capture";
	//if (targetSquare == kingPos[1])
	//	std::cout << "king capture";
	// ~Debbuging


	if (capturedPiece)
	{
		PieceLists[capturedPiece].RemovePieceAtSquare(targetSquare);
		AllPiecePosBitboard ^= targetBit;
		PieceBitboardPos[capturedPiece] ^= targetBit;
		if (IsWhiteToMove)
			AllBlackPosBitboard ^= targetBit;
		else
			AllWhitePosBitboard ^= targetBit;
	}
	PieceLists[movingPiece].MovePiece(startSquare, targetSquare);
	AllPiecePosBitboard ^= moveBitboard;
	PieceBitboardPos[movingPiece] ^= moveBitboard;

	if (movingPieceType == Pawn)
	{
		if (IsWhiteToMove)
		{
			WhitePawnCounts[GetCollum(startSquare)]--;
			WhitePawnCounts[GetCollum(targetSquare)]++;
		}
		else
		{
			BlackPawnCounts[GetCollum(startSquare)]--;
			BlackPawnCounts[GetCollum(targetSquare)]++;
		}
	}

	if (capturedPieceType == Pawn)
	{
		if (IsWhiteToMove)
			BlackPawnCounts[GetCollum(targetSquare)]--;
		else
			WhitePawnCounts[GetCollum(targetSquare)]--;
	}

	if (IsWhiteToMove)
	{
		AllWhitePosBitboard ^= moveBitboard;

		// USE BITBOARDS TO CHECK castle 
		// also use bitboards to check in the move generation code, and just bitshift after a move
		// use like whitePeicePoses and black instead of checking board[]


		/*
		
		
		
		
		
		
		
		THIS DOES NOT WORK. CANT STILL CASTLE IF PEICE WAS CAPTURED. USE BITBOARDS TO SEE IF THE DIFRENT PLACES ARE GETTING MOVED/HIT
		
		
		
		
		
		
		
		
		*/

		if (startSquare == 0) // queen rook
			castle &= CastleRights::AllBlack | CastleRights::WhiteKingSide;
		else if (startSquare == 7) // king rook
			castle &= CastleRights::AllBlack | CastleRights::WhiteQueenSide;
		else if (startSquare == 4) // king move
			castle &= CastleRights::AllBlack;
	}
	else
	{
		AllBlackPosBitboard ^= moveBitboard;

		if (startSquare == 56) // queen rook
			castle &= CastleRights::AllWhite | CastleRights::BlackKingSide;
		else if (startSquare == 63) // king rook
			castle &= CastleRights::AllWhite | CastleRights::BlackQueenSide;
		else if (startSquare == 60) // king move
			castle &= CastleRights::AllWhite;
	}

	board[startSquare] = 0;
	board[targetSquare] = movingPiece;

	if (movingPiece == (King | OurColor))
		kingPos[OurColorIndex] = targetSquare;

	EPSquare = EmptyEnPassantPos;

	if (flag == MoveFlags::PawnDoubleForward)
	{
		if (IsWhiteToMove)
			EPSquare = startSquare - 8;
		else
			EPSquare = startSquare + 8;
	}
	else if (flag == MoveFlags::EnPassantCapture)
	{
		if (IsWhiteToMove)
		{
			capturedPiece = BPawn;
			stateSave.capturedPiece = BPawn;
			PieceLists[BPawn].RemovePieceAtSquare(targetSquare - 8);
			AllPiecePosBitboard ^= (targetBit >> 8);
			PieceBitboardPos[BPawn] ^= (targetBit >> 8);
			stateSave.capturedPiece = BPawn;
		}
		else
		{
			capturedPiece = WPawn;
			stateSave.capturedPiece = WPawn;
			PieceLists[WPawn].RemovePieceAtSquare(targetSquare + 8);
			AllPiecePosBitboard ^= (targetBit << 8);
			PieceBitboardPos[WPawn] ^= (targetBit << 8);
			stateSave.capturedPiece = WPawn;
		}
	}
	else if (flag == MoveFlags::Castling)
	{
		if (targetSquare == 2) // WhiteQueenSide
		{
			board[0] = 0;
			board[3] = WRook;
			PieceLists[WRook].MovePiece(0, 3);
			Bitboard rookmove = (0b1ULL << 0) | (0b1ULL << 3);
			AllPiecePosBitboard ^= rookmove;
			AllWhitePosBitboard ^= rookmove;
			PieceBitboardPos[WRook] ^= rookmove;
		}
		else if (targetSquare == 6) // WhiteKingSide
		{
			board[7] = 0;
			board[5] = WRook;
			PieceLists[WRook].MovePiece(7, 5);
			Bitboard rookmove = (0b1ULL << 7) | (0b1ULL << 5);
			AllPiecePosBitboard ^= rookmove;
			AllWhitePosBitboard ^= rookmove;
			PieceBitboardPos[WRook] ^= rookmove;
		}
		else if (targetSquare == 58) // BlackQueenSide
		{
			board[56] = 0;
			board[59] = BRook;
			PieceLists[BRook].MovePiece(56, 59);
			Bitboard rookmove = (0b1ULL << 56) | (0b1ULL << 59);
			AllPiecePosBitboard ^= rookmove;
			AllBlackPosBitboard ^= rookmove;
			PieceBitboardPos[BRook] ^= rookmove;
		}
		else if (targetSquare == 62) // BlackKingSide
		{
			board[63] = 0;
			board[61] = BRook;
			PieceLists[BRook].MovePiece(63, 61);
			Bitboard rookmove = (0b1ULL << 63) | (0b1ULL << 61);
			AllPiecePosBitboard ^= rookmove;
			AllBlackPosBitboard ^= rookmove;
			PieceBitboardPos[BRook] ^= rookmove;
		}
	}
	else if (flag != MoveFlags::NoFlag) // Is promotion
	{
		// remove pawn and replace it with the given promotion piece
		PieceLists[movingPiece].RemovePieceAtSquare(targetSquare);
		Piece promotionPiece = GetPromotionPieceType(flag) | OurColor;
		PieceLists[promotionPiece].AddPieceAtSquare(targetSquare);
		PieceBitboardPos[movingPiece] ^= targetBit;
		PieceBitboardPos[promotionPiece] ^= targetBit;
		board[targetSquare] = promotionPiece;
	}


	// debuging
	//int kingsFound = 0;
	//for (size_t i = 0; i < 64; i++)
	//	if (board[i] == BKing)
	//		kingsFound++;
	//if (kingsFound > 1)
	//	std::cout << "huh";

	playerTurn ^= PlayerTurnSwitch;

	//Logger::Log("White King Side " + std::to_string(castle & CastleRights::WhiteKingSide) + "\n");
	//Logger::Log("White Queen Side " + std::to_string(castle & CastleRights::WhiteQueenSide) + "\n");
	//Logger::Log("Black King Side " + std::to_string(castle & CastleRights::BlackKingSide) + "\n");
	//Logger::Log("Black Queen Side " + std::to_string(castle & CastleRights::BlackQueenSide) + "\n");
	//Logger::Log(castle & CastleRights::WhiteKingSide);


	// Save state
	boardStateStack.Push(stateSave);
}

// Just have to undo what MakeMove did
void UnsafeWaterMelon::UnMakeMove()
{
	// Testing ideer
	// Copy all the raw data over into another file, 
	// than make a move,
	// than unmake the move,
	// copy the board again
	// compare, repeat
	// if you dont run GetPossibleMoves(), all the bytes should be complety equal 
	// (EXEPT FOR the stack item pointer and capacity)

	//if (boardStateStack.GetCount() == 0)
		//ThrowInvalidArgumentException("Can't UnMakeMove when there is not any moves to unmake");
	if (boardStateStack.GetCount() == 0)
		return;

	playerTurn ^= PlayerTurnSwitch;

	BoardState state = boardStateStack.Pop();

	castle = state.castles;
	EPSquare = state.epPos;
	//state.KingInCheck;
	//state.KingInDoubleCheck;
	//state.move;
	//state._50MoveRule;

	// Load State and reverse
	Square startSquare = GetMoveStart(state.move);
	Square targetSquare = GetMoveTarget(state.move);
	MoveFlag flag = GetMoveFlag(state.move);

	Bitboard startBit = BitboardFromSquare(startSquare);
	Bitboard targetBit = BitboardFromSquare(targetSquare);

	Piece movingPiece = board[targetSquare];
	PieceType movingPieceType = GetPieceType(movingPiece);
	Piece capturedPiece = state.capturedPiece;
	PieceType capturedPieceType = GetPieceType(capturedPiece);

	Bitboard moveBitboard = startBit | targetBit;

	Color OurColor = playerTurn;
	int OurColorIndex = playerTurn >> 4;
	bool IsWhiteToMove = !(bool)OurColorIndex;

	if (movingPieceType == Pawn)
	{
		if (IsWhiteToMove)
		{
			WhitePawnCounts[GetCollum(startSquare)]++;
			WhitePawnCounts[GetCollum(targetSquare)]--;
		}
		else
		{
			BlackPawnCounts[GetCollum(startSquare)]++;
			BlackPawnCounts[GetCollum(targetSquare)]--;
		}
	}

	if (capturedPieceType == Pawn)
	{
		if (IsWhiteToMove)
			BlackPawnCounts[GetCollum(targetSquare)]++;
		else
			WhitePawnCounts[GetCollum(targetSquare)]++;
	}

	if (movingPiece == (King | OurColor))
		kingPos[OurColorIndex] = startSquare;

	if (flag == MoveFlags::PawnDoubleForward)
	{
	}
	else if (flag == MoveFlags::EnPassantCapture)
	{
		if (IsWhiteToMove)
		{
			PieceLists[BPawn].AddPieceAtSquare(targetSquare - 8);
			AllPiecePosBitboard ^= (targetBit >> 8);
			PieceBitboardPos[BPawn] ^= (targetBit >> 8);
			capturedPiece = 0;
		}
		else
		{
			PieceLists[WPawn].AddPieceAtSquare(targetSquare + 8);
			AllPiecePosBitboard ^= (targetBit << 8);
			PieceBitboardPos[WPawn] ^= (targetBit << 8);
			capturedPiece = 0;
		}
	}
	else if (flag == MoveFlags::Castling)
	{
		if (targetSquare == 2) // WhiteQueenSide
		{
			board[3] = 0;
			board[0] = WRook;
			PieceLists[WRook].MovePiece(3, 0);
			Bitboard rookmove = (0b1ULL << 0) | (0b1ULL << 3);
			AllPiecePosBitboard ^= rookmove;
			AllWhitePosBitboard ^= rookmove;
			PieceBitboardPos[WRook] ^= rookmove;
		}
		else if (targetSquare == 6) // WhiteKingSide
		{
			board[5] = 0;
			board[7] = WRook;
			PieceLists[WRook].MovePiece(5, 7);
			Bitboard rookmove = (0b1ULL << 7) | (0b1ULL << 5);
			AllPiecePosBitboard ^= rookmove;
			AllWhitePosBitboard ^= rookmove;
			PieceBitboardPos[WRook] ^= rookmove;
		}
		else if (targetSquare == 58) // BlackQueenSide
		{
			board[59] = 0;
			board[56] = BRook;
			PieceLists[BRook].MovePiece(59, 56);
			Bitboard rookmove = (0b1ULL << 56) | (0b1ULL << 59);
			AllPiecePosBitboard ^= rookmove;
			AllBlackPosBitboard ^= rookmove;
			PieceBitboardPos[BRook] ^= rookmove;
		}
		else if (targetSquare == 62) // BlackKingSide
		{
			board[61] = 0;
			board[63] = BRook;
			PieceLists[BRook].MovePiece(61, 63);
			Bitboard rookmove = (0b1ULL << 63) | (0b1ULL << 61);
			AllPiecePosBitboard ^= rookmove;
			AllBlackPosBitboard ^= rookmove;
			PieceBitboardPos[BRook] ^= rookmove;
		}
	}
	else if (flag != MoveFlags::NoFlag) // Is promotion
	{
		movingPiece = Pawn | OurColor;
		// remove pawn and replace it with the given promotion piece
		Piece promotionPiece = GetPromotionPieceType(flag) | OurColor;
		PieceLists[promotionPiece].RemovePieceAtSquare(targetSquare);
		PieceLists[movingPiece].AddPieceAtSquare(targetSquare);
		PieceBitboardPos[promotionPiece] ^= targetBit;
		PieceBitboardPos[movingPiece] ^= targetBit;
		board[targetSquare] = movingPiece;
	}



	board[startSquare] = movingPiece;
	PieceLists[movingPiece].MovePiece(targetSquare, startSquare);
	AllPiecePosBitboard ^= moveBitboard;
	PieceBitboardPos[movingPiece] ^= moveBitboard;

	if (capturedPiece)
	{
		PieceLists[capturedPiece].AddPieceAtSquare(targetSquare);
		AllPiecePosBitboard ^= targetBit;
		PieceBitboardPos[capturedPiece] ^= targetBit;
		board[targetSquare] = capturedPiece;
		if (IsWhiteToMove)
			AllBlackPosBitboard ^= targetBit;
		else
			AllWhitePosBitboard ^= targetBit;
	}
	else
		board[targetSquare] = 0;

	if (IsWhiteToMove)
		AllWhitePosBitboard ^= moveBitboard;
	else
		AllBlackPosBitboard ^= moveBitboard;







	gameState = Running;
}

void UnsafeWaterMelon::InitSimpleBitboards()
{
	GenerateBitboards();
}


#pragma region Initilization
UnsafeWaterMelon::UnsafeWaterMelon()
{
	InitFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

UnsafeWaterMelon::UnsafeWaterMelon(const std::string FEN)
{
	InitFEN(FEN);
}

UnsafeWaterMelon::~UnsafeWaterMelon()
{

}

void UnsafeWaterMelon::InitFEN(const std::string FEN)
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
					int boardPos = FlipSquareY(fenBoardPtr);
					board[boardPos] = pieceVal;

					if (pieceVal == WKing)
						kingPos[0] = boardPos;
					else if (pieceVal == BKing)
						kingPos[1] = boardPos;
					else
						PieceLists[pieceVal].AddPieceAtSquare(boardPos);

					if (IsPieceColor(pieceVal, White))
						AllWhitePosBitboard |= 0b1ULL << boardPos;
					else
						AllBlackPosBitboard |= 0b1ULL << boardPos;
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
				AllPiecePosBitboard |= 0b1ULL << i;
				PieceBitboardPos[board[i]] |= 0b1ULL << i;
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

void UnsafeWaterMelon::CheckDraw()
{
	// Check repetition and 50 move rule
	if (false)
		gameState = Draw;
}

void UnsafeWaterMelon::GenerateBitboards()
{
	// NOTE* The non sliding attacks can maby be changed at make and unmake moves

	allFriendlyAttakcsNonSliding = 0;
	allEnemyAttacksNonSliding = 0;

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
		allFriendlyAttakcsNonSliding |= pieceAttackBitboards[WPawn] | pieceAttackBitboards[WKnight] | pieceAttackBitboards[WKing];
		allEnemyAttacksNonSliding |= pieceAttackBitboards[BPawn] | pieceAttackBitboards[BKnight] | pieceAttackBitboards[BKing];
	}
	else
	{
		allFriendlyAttakcsNonSliding |= pieceAttackBitboards[BPawn] | pieceAttackBitboards[BKnight] | pieceAttackBitboards[BKing];
		allEnemyAttacksNonSliding |= pieceAttackBitboards[WPawn] | pieceAttackBitboards[WKnight] | pieceAttackBitboards[WKing];
	}
}

void UnsafeWaterMelon::GeneratePinsAndAttacksOnKing() // This method cast a ray out in each direction
{
	pinnedPieces = 0;
	attacksOnKing = 0;

	Bitboard slidingPieces =
		PieceBitboardPos[EnemyQueenKey] |
		PieceBitboardPos[EnemyRookKey] |
		PieceBitboardPos[EnemyBishopKey];

	for (DirectionIndex dir = 0; dir < 8; dir++) // The directions
	{
		if (GetSlidingPieceBitboardFromInDir(ourKingPos, dir) & slidingPieces) // There is something there
		{
			//if (dir == DirectionIndexs::SouthWestI)
				//std::cout << "";
			//std::cout << dir;

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
							rayBoard |= (0b1ULL << rayPos);
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
							rayBoard |= (0b1ULL << rayPos);
							pinnedPieces |= DotBiboards[OurPiecePos];
							pinningPiecesAttack[OurPiecePos] = rayBoard;
						}
						break;
					}
				}
				rayBoard |= (0b1ULL << rayPos);
			}

			//Logger::LogBitboard(pinnedPieces);
		}
	}

	if (pieceAttackBitboards[EnemyKnightKey] & ourKingBitboard)
	{
		if (KingInCheck) // no need to know where the attack comes from
		{
			KingInDoubleCheck = true;
			return;
		}
		Bitboard attacksBitboard = GetKnightAllDirBitboard(ourKingPos);
		// There cant be more than 1 knight attacking the king
		for (size_t i = 0; i < 8; i++)
		{
			Square squareChecked = ourKingPos + KnightOffsetsIndexed[i];
			if (BitboardContains(attacksBitboard, squareChecked))
				if (board[squareChecked] == EnemyKnightKey)
				{
					KingInCheck = true;
					attacksOnKing |= 0b1ULL << squareChecked;
					break;
				}
		}
	}

	if (pieceAttackBitboards[EnemyPawnKey] & ourKingBitboard)
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
				attacksOnKing |= 0b1ULL << (ourKingPos + 7);
			}
			else
			{
				KingInCheck = true;
				attacksOnKing |= 0b1ULL << (ourKingPos + 9);
			}
		}
		else
		{
			if (board[ourKingPos - 7] == BPawn)
			{
				KingInCheck = true;
				attacksOnKing |= 0b1ULL << (ourKingPos - 7);
			}
			else
			{
				KingInCheck = true;
				attacksOnKing |= 0b1ULL << (ourKingPos - 9);
			}
		}

	}

#ifdef SquareToRender
	SquaresToRenderByGUIForDebuing.clear();
#endif

	//if (KingInDoubleCheck)
	//	Logger::Log("King under double attack");
	//else if (KingInCheck)
	//	Logger::Log("King under attack");
	//else
	//	Logger::Log("King NOT under attack");
	//Logger::Log("AttacksOnKing:\n");
	//Logger::LogBitboard(attacksOnKing);
	//Logger::Log("PinnedPieces:\n");
	//Logger::LogBitboard(pinnedPieces);
#ifdef SquareToRender
	for (size_t i = 0; i < 64; i++)
	{
		if (pinnedPieces & (0b1ULL << i))
		{
			//Logger::Log(std::to_string(i) + "\n");
			//Logger::LogBitboard(pinningPiecesAttack[i]);
			//Logger::Log("\n");

			SquaresToRenderByGUIForDebuing.push_front(ColoredSquare(i, 255, 0, 0));
		}

	}
#endif
}

void UnsafeWaterMelon::AddKingMoves()
{
	constexpr Offset Kingmoves[]
	{ -9,-8,-7,-1,1,7,8,9 };
	constexpr Offset KingmovesLineoffsets[]
	{ -1,-1,-1,0,0,1,1,1 };
	Bitboard KingAttacksBitboard = GetKingAllDirBitboard(ourKingPos);
	// plz unwrap mister compiler
	for (size_t i = 0; i < 8; i++)
	{
		int newPos = ourKingPos + Kingmoves[i];
		//if ((newPos >> 3) - KingmovesLineoffsets[i] != ourKingPos >> 3)
			//continue;
		if (KingAttacksBitboard & 0b1ULL << newPos)
		{
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
}

inline void UnsafeWaterMelon::AddPormotionMoves(int from, int to, unsigned short captureBit)
{
	PushMove(CreateMove(from, to, MoveFlags::PromoteToQueenCapture | captureBit));
	PushMove(CreateMove(from, to, MoveFlags::PromoteToKnightCapture | captureBit));
	PushMove(CreateMove(from, to, MoveFlags::PromoteToRookCapture | captureBit));
	PushMove(CreateMove(from, to, MoveFlags::PromoteToBishopCapture | captureBit));
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
			bool isPromotion = BitboardContains(WhitePromotionLine, oneMove);
			Bitboard AND = pinnedPieces & (0b1ULL << pos);

			if (isPromotion)
			{
				if (BitboardContains(whitePawnAttacksBitboard, leftPos))
					if (IsPieceColor(GetColor(board[leftPos]), Black))
					{
						if (AND) // Is pinned
						{
							if (pinningPiecesAttack[pos] & (0b1ULL << leftPos)) // Blocks pin
								if (BitboardContains(attacksOnKing, leftPos) || !KingInCheck) // blocks check
								{
									PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToQueenCapture));
									PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToKnightCapture));
									PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToRookCapture));
									PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToBishopCapture));
								}
						}
						else
						{
							if (BitboardContains(attacksOnKing, leftPos))
							{
								PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToQueenCapture));
								PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToKnightCapture));
								PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToRookCapture));
								PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToBishopCapture));
							}
						}
					}
				if (BitboardContains(whitePawnAttacksBitboard, rightPos))
					if (IsPieceColor(GetColor(board[rightPos]), Black))
					{
						if (AND) // Is pinned
						{
							if (pinningPiecesAttack[pos] & (0b1ULL << rightPos)) // Blocks pin
								if (BitboardContains(attacksOnKing, rightPos) || !KingInCheck) // blocks check
								{
									PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToQueenCapture));
									PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToKnightCapture));
									PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToRookCapture));
									PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToBishopCapture));
								}
						}
						else
						{
							if (BitboardContains(attacksOnKing, rightPos))
							{
								PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToQueenCapture));
								PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToKnightCapture));
								PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToRookCapture));
								PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToBishopCapture));
							}
						}
					}

				if (board[oneMove] == 0)
				{
					if (AND) // Is pinned
					{
						if (pinningPiecesAttack[pos] & (0b1ULL << oneMove)) // Blocks pin
							if (BitboardContains(attacksOnKing, oneMove) || !KingInCheck) // blocks check
							{
								PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToQueen));
								PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToKnight));
								PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToRook));
								PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToBishop));
							}
					}
					else
					{
						if (BitboardContains(attacksOnKing, oneMove))
						{
							PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToQueen));
							PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToKnight));
							PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToRook));
							PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToBishop));
						}
					}
				}
			}
			else
			{
				if (BitboardContains(whitePawnAttacksBitboard, leftPos))
					if (IsPieceColor(GetColor(board[leftPos]), Black))
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, leftPos, NoFlagCapture));
				if (BitboardContains(whitePawnAttacksBitboard, rightPos))
					if (IsPieceColor(GetColor(board[rightPos]), Black))
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, rightPos, NoFlagCapture));

				if (board[oneMove] == 0)
				{
					PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, oneMove, NoFlag));
					if (board[twoMove] == 0 && BitboardContains(WhiteTwoMoveLine, pos))
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, twoMove, PawnDoubleForward));
				}
			}
		}
		if (EPSquare != EmptyEnPassantPos)
		{
			// becous Enpassant moves two pieces, we do the King check check here.
			// Just check if the king is on the same rank, and if there by chance 
			// also is an enemy queen or rook on the same rank now not blocked


		}
	}
	else
	{
		Bitboard blackPawnAttacksBitboard = pieceAttackBitboards[BPawn];
		for (size_t i = 0; i < PieceLists[BPawn].PieceNum; i++)
		{
			int pos = PieceLists[BPawn].OccupiedSquares[i];
			int leftPos = pos - 9;
			int rightPos = pos - 7;
			int oneMove = pos - 8;
			int twoMove = pos - 16;
			bool isPromotion = BitboardContains(BlackPromotionLine, oneMove);
			Bitboard AND = pinnedPieces & (0b1ULL << pos);

			if (isPromotion)
			{
				if (BitboardContains(blackPawnAttacksBitboard, leftPos))
					if (IsPieceColor(GetColor(board[leftPos]), White)) // this could again just be with bitboards
					{
						if (AND) // Is pinned
						{
							if (pinningPiecesAttack[pos] & (0b1ULL << leftPos)) // Blocks pin
								if (BitboardContains(attacksOnKing, leftPos) || !KingInCheck) // blocks check
								{
									PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToQueenCapture));
									PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToKnightCapture));
									PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToRookCapture));
									PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToBishopCapture));
								}
						}
						else
						{
							if (BitboardContains(attacksOnKing, leftPos))
							{
								PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToQueenCapture));
								PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToKnightCapture));
								PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToRookCapture));
								PushMove(CreateMove(pos, leftPos, MoveFlags::PromoteToBishopCapture));
							}
						}
					}
				if (BitboardContains(blackPawnAttacksBitboard, rightPos))
					if (IsPieceColor(GetColor(board[rightPos]), White))
					{
						if (AND) // Is pinned
						{
							if (pinningPiecesAttack[pos] & (0b1ULL << rightPos)) // Blocks pin
								if (BitboardContains(attacksOnKing, rightPos) || !KingInCheck) // blocks check
								{
									PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToQueenCapture));
									PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToKnightCapture));
									PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToRookCapture));
									PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToBishopCapture));
								}
						}
						else
						{
							if (BitboardContains(attacksOnKing, rightPos))
							{
								PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToQueenCapture));
								PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToKnightCapture));
								PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToRookCapture));
								PushMove(CreateMove(pos, rightPos, MoveFlags::PromoteToBishopCapture));
							}
						}
					}

				if (board[oneMove] == 0)
				{
					if (AND) // Is pinned
					{
						if (pinningPiecesAttack[pos] & (0b1ULL << oneMove)) // Blocks pin
							if (BitboardContains(attacksOnKing, oneMove) || !KingInCheck) // blocks check
							{
								PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToQueen));
								PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToKnight));
								PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToRook));
								PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToBishop));
							}
					}
					else
					{
						if (BitboardContains(attacksOnKing, oneMove))
						{
							PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToQueen));
							PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToKnight));
							PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToRook));
							PushMove(CreateMove(pos, oneMove, MoveFlags::PromoteToBishop));
						}
					}
				}
			}
			else
			{
				if (BitboardContains(blackPawnAttacksBitboard, leftPos))
					if (IsPieceColor(GetColor(board[leftPos]), White))
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, leftPos, NoFlagCapture));
				if (BitboardContains(blackPawnAttacksBitboard, rightPos))
					if (IsPieceColor(GetColor(board[rightPos]), White))
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, rightPos, NoFlagCapture));

				if (board[oneMove] == 0)
				{
					PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, oneMove, NoFlag));
					if (board[twoMove] == 0 && BitboardContains(BlackTwoMoveLine, pos))
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, twoMove, PawnDoubleForward));
				}
			}
		}
		if (EPSquare != EmptyEnPassantPos)
		{
			// becous Enpassant moves two pieces, we do the King check check here.
			// Just check if the king is on the same rank, and if there by chance 
			// also is an enemy queen or rook on the same rank now not blocked


		}
	}
}

void UnsafeWaterMelon::AddKnightMoves()
{
	//Logger::Log("All friends\n");
	//Logger::LogBitboard(AllFriendlyPosBitboard);
	//Logger::Log("");
	Bitboard FreeOfFriendlies = AllFriendlyPosBitboard ^ 0xffffffffffffffff;
	for (size_t i = 0; i < PieceLists[OurKnightKey].PieceNum; i++)
	{
		Square pos = PieceLists[OurKnightKey].OccupiedSquares[i];
		Bitboard attacksBitboard = GetKnightAllDirBitboard(pos);
		for (size_t i = 0; i < 8; i++)
		{
			Square newPos = pos + KnightOffsetsIndexed[i];
			if (BitboardContains(attacksBitboard & FreeOfFriendlies, newPos))
			{
				if (board[newPos])
					PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, newPos, NoFlag));
				else
					PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, newPos, NoFlagCapture));
			}
		}
	}
}

bool UnsafeWaterMelon::IsSquareSafe(Square square)
{
	//Logger::LogBitboard(allEnemyAttacks);

	if (BitboardContains(allEnemyAttacksNonSliding, square))
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

void UnsafeWaterMelon::AddRookMoves()
{
	Piece pieceKey = OurRookKey;
	int count = PieceLists[pieceKey].PieceNum;
	for (size_t num = 0; num < count; num++)
	{
		Square pos = PieceLists[pieceKey].OccupiedSquares[num];
		for (size_t dir = RookStartDirectionIndex; dir < RookEndDirectionIndex; dir++)
		{
			Offset offset = offsetsIndexed[dir];
			int distance = GetDistanceToBoardInDirection(pos, dir);
			int ray = pos;
			for (size_t i = 0; i < distance; i++)
			{
				ray += offset;
				Piece hitPiece = board[ray];
				if (hitPiece)
				{
					if (IsPieceColor(hitPiece, enemyColour))
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, ray, NoFlagCapture));
					break;
				}
				else
				{
					PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, ray, NoFlag));
				}
			}
		}
	}
}

void UnsafeWaterMelon::AddBishopMoves()
{
	Piece pieceKey = OurBishopKey;
	int count = PieceLists[pieceKey].PieceNum;
	for (size_t num = 0; num < count; num++)
	{
		Square pos = PieceLists[pieceKey].OccupiedSquares[num];
		for (size_t dir = BishopStartDirectionIndex; dir < BishopEndDirectionIndex; dir++)
		{
			Offset offset = offsetsIndexed[dir];
			int distance = GetDistanceToBoardInDirection(pos, dir);
			int ray = pos;
			for (size_t i = 0; i < distance; i++)
			{
				ray += offset;
				Piece hitPiece = board[ray];
				if (hitPiece)
				{
					if (IsPieceColor(hitPiece, enemyColour))
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, ray, NoFlagCapture));
					break;
				}
				else
				{
					PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, ray, NoFlag));
				}
			}
		}
	}
}

void UnsafeWaterMelon::AddQueenMoves()
{
	Piece pieceKey = OurQueenKey;
	int count = PieceLists[pieceKey].PieceNum;
	for (size_t num = 0; num < count; num++)
	{
		Square pos = PieceLists[pieceKey].OccupiedSquares[num];
		for (size_t dir = 0; dir < 8; dir++)
		{
			Offset offset = offsetsIndexed[dir];
			int distance = GetDistanceToBoardInDirection(pos, dir);
			int ray = pos;
			for (size_t i = 0; i < distance; i++)
			{
				ray += offset;

				if (BitboardContains(AllPiecePosBitboard, ray))
				{
					if (BitboardContains(AllEnemyPosBitboard, ray))
						PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, ray, NoFlagCapture));
					break;
				}
				else
				{
					PushMoveIfPinnsAllowAndKingNotInCheck(CreateMove(pos, ray, NoFlag));
				}
			}
		}
	}
}

void UnsafeWaterMelon::AddCastleMoves()
{
	if (whiteToMove)
	{
		if ((castle & CastleRights::WhiteKingSide) && (board[5] == 0) && (board[6] == 0))
			// clear path
			if (IsSquareSafe(5) && IsSquareSafe(6))
				// safe path
				PushMove(CreateMove(4, 6, MoveFlags::Castling));

		if ((castle & CastleRights::WhiteQueenSide) && (board[3] == 0) && (board[2] == 0) && (board[1] == 0))
			if (IsSquareSafe(3) && IsSquareSafe(2))
				PushMove(CreateMove(4, 2, MoveFlags::Castling));
	}
	else
	{
		if ((castle & CastleRights::BlackKingSide) && (board[61] == 0) && (board[62] == 0))
			if (IsSquareSafe(61) && IsSquareSafe(62))
				PushMove(CreateMove(60, 62, MoveFlags::Castling));

		if ((castle & CastleRights::BlackQueenSide) && (board[59] == 0) && (board[58] == 0) && (board[57] == 0))
			if (IsSquareSafe(59) && IsSquareSafe(58))
				PushMove(CreateMove(60, 58, MoveFlags::Castling));
	}
}

void UnsafeWaterMelon::PushMove(Move move)
{
	moves[movesCount++] = move;
}

void UnsafeWaterMelon::PushMoveIfPinnsAllow(Move move)
{
	Square start = GetMoveStart(move);
	Square target = GetMoveTarget(move);
	Bitboard AND = pinnedPieces & (0b1ULL << start);
	if (AND) // Is pinned
	{
		if (pinningPiecesAttack[start] & (0b1ULL << target)) // Blocks pin
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
	Bitboard AND = pinnedPieces & (0b1ULL << start);
	if (AND) // Is pinned
	{
		if (pinningPiecesAttack[start] & (0b1ULL << target)) // Blocks pin
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
	InitBoard();
	if (gameState == Draw)
		return 0;

	AddKingMoves();

	if (KingInDoubleCheck)
	{
#ifdef SquareToRender
		for (size_t i = 0; i < movesCount; i++)
			SquaresToRenderByGUIForDebuing.push_front(ColoredSquare(GetMoveTarget(moves[i]), 0, 0, 200));
#endif
		//Logger::Log(std::to_string(movesCount));
		memcpy_s(movesPtr, MaxMovesCount * sizeof(Move), moves, movesCount * sizeof(Move));
		return movesCount;
	}
	else if (!KingInCheck)
		attacksOnKing = 0xffffffffffffffff;

	AddPawnMoves();
	AddKnightMoves();
	AddRookMoves();
	AddBishopMoves();
	AddQueenMoves();
	AddCastleMoves();


	if (onlyCaptures)
		RemoveNoneCaptures();
	if (moveOrder)
		OrderMoves();


#ifdef SquareToRender
	for (size_t i = 0; i < movesCount; i++)
		SquaresToRenderByGUIForDebuing.push_front(ColoredSquare(GetMoveTarget(moves[i]), 0, 0, 200));
#endif
	//Logger::Log(std::to_string(movesCount));

	// Testing
	//movesCount = 0;
	//PushMove(CreateMove(4, 24, MoveFlags::Castling));

	memcpy_s(movesPtr, MaxMovesCount * sizeof(Move), moves, movesCount * sizeof(Move));
	return movesCount;
}

void UnsafeWaterMelon::InitBoard()
{
#ifdef SquareToRender
	SquaresToRenderByGUIForDebuing.clear();
#endif

	/*for (size_t i = 0; i < 24; i++)
		for (size_t j = 0; j < PieceLists[i].PieceNum; j++)
			SquaresToRenderByGUIForDebuing.push_back(PieceLists[i].OccupiedSquares[j]);
	return 0;*/

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

		AllFriendlyPosBitboard = AllWhitePosBitboard;
		AllEnemyPosBitboard = AllBlackPosBitboard;
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

		AllFriendlyPosBitboard = AllBlackPosBitboard;
		AllEnemyPosBitboard = AllWhitePosBitboard;
	}
	ourKingBitboard = PieceBitboardPos[OurKingKey];

	GenerateBitboards();

	GeneratePinsAndAttacksOnKing();

	CheckDraw();
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