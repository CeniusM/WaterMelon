

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
	bool IsWhiteToMove = OurColorIndex ^ 0b1;

	BoardState stateSave{ move, capturedPiece, EPSquare, castle, 0, KingInCheck, KingInDoubleCheck };
	//BoardState stateSave =
	//	(BoardState)move |
	//	((BoardState)capturedPiece << (sizeof(Move) * 8)) |
	//	((BoardState)EPSquare << (sizeof(Move) + 1) * 8) |
	//	((BoardState)castle << (sizeof(Move) + 2) * 8);


	Check(targetSquare == kingPos[0], "king capture");
	Check(targetSquare == kingPos[1], "king capture");


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

	// Very unsafe... AllWhitePosBitboard have to be right above AllBlackPosBitboard
	(&AllWhitePosBitboard)[OurColorIndex] ^= moveBitboard;

	castle &= CastleRightAndRemoverForSquare[startSquare];
	castle &= CastleRightAndRemoverForSquare[targetSquare];


	board[startSquare] = 0;
	board[targetSquare] = movingPiece;

	if (movingPiece == (King | OurColor))
		kingPos[OurColorIndex] = targetSquare;

	EPSquare = EmptyEnPassantPos;

	if (flag == MoveFlags::PawnDoubleForward)
	{
		if (IsWhiteToMove)
			EPSquare = targetSquare - 8;
		else
			EPSquare = targetSquare + 8;
	}
	else if ((flag | CapturedPieceBitFlag) == MoveFlags::EnPassantCapture)
	{
		if (IsWhiteToMove)
		{
			capturedPiece = BPawn;
			stateSave.capturedPiece = BPawn;
			PieceLists[BPawn].RemovePieceAtSquare(targetSquare - 8);
			AllPiecePosBitboard ^= (targetBit >> 8);
			PieceBitboardPos[BPawn] ^= (targetBit >> 8);
			board[targetSquare - 8] = 0;
			stateSave.capturedPiece = BPawn;
		}
		else
		{
			capturedPiece = WPawn;
			stateSave.capturedPiece = WPawn;
			PieceLists[WPawn].RemovePieceAtSquare(targetSquare + 8);
			AllPiecePosBitboard ^= (targetBit << 8);
			PieceBitboardPos[WPawn] ^= (targetBit << 8);
			board[targetSquare + 8] = 0;
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


#ifdef DoChecks
	int kingsFound = 0;
	for (size_t i = 0; i < 64; i++)
		if ((board[i] & typeMask) == King)
			kingsFound++;
	Check(kingsFound == 2, "Found more or less than 2 kings");
#endif

	playerTurn ^= PlayerTurnSwitch;

	//Logger::Log("White King Side " + std::to_string(castle & CastleRights::WhiteKingSide) + "\n");
	//Logger::Log("White Queen Side " + std::to_string(castle & CastleRights::WhiteQueenSide) + "\n");
	//Logger::Log("Black King Side " + std::to_string(castle & CastleRights::BlackKingSide) + "\n");
	//Logger::Log("Black Queen Side " + std::to_string(castle & CastleRights::BlackQueenSide) + "\n");
	//Logger::Log(castle & CastleRights::WhiteKingSide);


	// Save state
	boardStateStack.Push(stateSave); // Use a Cache instead of going out to heap memory again and again
	AllEmptyPosBitboard = (FullBitboardBoard ^ AllPiecePosBitboard);
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

	gameState = Running;

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
	else if ((flag | CapturedPieceBitFlag) == MoveFlags::EnPassantCapture)
	{
		if (IsWhiteToMove)
		{
			PieceLists[BPawn].AddPieceAtSquare(targetSquare - 8);
			AllPiecePosBitboard ^= (targetBit >> 8);
			PieceBitboardPos[BPawn] ^= (targetBit >> 8);
			board[targetSquare - 8] = BPawn;
			capturedPiece = 0;
		}
		else
		{
			PieceLists[WPawn].AddPieceAtSquare(targetSquare + 8);
			AllPiecePosBitboard ^= (targetBit << 8);
			PieceBitboardPos[WPawn] ^= (targetBit << 8);
			board[targetSquare + 8] = WPawn;
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
	board[startSquare] = movingPiece;

	// Very unsafe... AllWhitePosBitboard have to be right above AllBlackPosBitboard
	(&AllWhitePosBitboard)[OurColorIndex] ^= moveBitboard;

	AllEmptyPosBitboard = (FullBitboardBoard ^ AllPiecePosBitboard);
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
	if (m_HasInit)
		return;
	// Validate the FEN String...

	// Clear everything
	//void* self = this;
	//memset(self, 0, sizeof(UnsafeWaterMelon));

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

	EPSquare = EmptyEnPassantPos;

	GetPossibleMoves(moves); // init boards
}
#pragma endregion

std::string UnsafeWaterMelon::GetFEN() const
{
	//ThrowNotImplementedException("The GetFEN function is not implemented");
	std::string str = "";

	int space = 0;
	for (size_t j = 0; j < 64; j++)
	{
		int i = FlipSquareY(j);
		if (board[i] != 0)
		{
			if (space != 0)
			{
				str += std::to_string(space);
				space = 0;
			}
			str += FENUtility::IntToChar[board[i]];
		}
		else
		{
			space++;
		}

		if ((j+1) % 8 == 0 && j != 63)
		{
			if (space != 0)
			{
				str += std::to_string(space);
				space = 0;
			}
			str += "/";
		}
	}
	
	str += " ";
	
	if (playerTurn == White)
		str += "w";
	else
		str += "b";

	str += " ";

	bool wasCastle = false;
	if (castle & CastleRights::WhiteKingSide)
	{
		wasCastle = true;
		str += "K";
	}
	if (castle & CastleRights::WhiteQueenSide)
	{
		wasCastle = true;
		str += "Q";
	}
	if (castle & CastleRights::BlackKingSide)
	{
		wasCastle = true;
		str += "k";
	}
	if (castle & CastleRights::BlackQueenSide)
	{
		wasCastle = true;
		str += "q";
	}

	str += " ";


	if (EPSquare != 0)
	{
		//int v = FlipSquareY(EPSquare);
		int v = EPSquare;
		int xSquare = GetCollum(v);
		int ySquare = GetRank(v);
		str += static_cast<char>('a' + xSquare);
		str += static_cast<char>('1' + ySquare);
	}
	else str += "-";

	//str += std::to_string(EPSquare);
	//str += GetSquareName(EPSquare);



	str += " 0 0";

	return str;
}

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
	// and for stalemate if it is possible without GenerateMoves
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

	//for (size_t i = 0; i < PieceLists[WPawn].PieceNum; i++)
		//pieceAttackBitboards[WPawn] |= GetWhitePawnAttacks(PieceLists[WPawn].OccupiedSquares[i]);

	//for (size_t i = 0; i < PieceLists[BPawn].PieceNum; i++)
		//pieceAttackBitboards[BPawn] |= GetBlackPawnAttacks(PieceLists[BPawn].OccupiedSquares[i]);


	pieceAttackBitboards[WPawn] = ((PieceBitboardPos[WPawn] & RightSideIs0) << 9) | ((PieceBitboardPos[WPawn] & LeftSideIs0) << 7);
	pieceAttackBitboards[BPawn] = ((PieceBitboardPos[BPawn] & RightSideIs0) >> 7) | ((PieceBitboardPos[BPawn] & LeftSideIs0) >> 9);

	for (size_t i = 0; i < PieceLists[WKnight].PieceNum; i++)
		pieceAttackBitboards[WKnight] |= GetKnightAllDirBitboard(PieceLists[WKnight].OccupiedSquares[i]);

	for (size_t i = 0; i < PieceLists[BKnight].PieceNum; i++)
		pieceAttackBitboards[BKnight] |= GetKnightAllDirBitboard(PieceLists[BKnight].OccupiedSquares[i]);

	pieceAttackBitboards[WKing] |= GetKingAllDirBitboard(kingPos[0]) & (FullBitboardBoard ^ AllWhitePosBitboard);

	pieceAttackBitboards[BKing] |= GetKingAllDirBitboard(kingPos[1]) & (FullBitboardBoard ^ AllBlackPosBitboard);




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
	Bitboard KingAttacksBitboard = pieceAttackBitboards[OurKingKey];
	// plz unwrap mister compiler
	for (size_t i = 0; i < 8; i++)
	{
		int newPos = ourKingPos + Kingmoves[i];
		//if ((newPos >> 3) - KingmovesLineoffsets[i] != ourKingPos >> 3)
			//continue;
		if (KingAttacksBitboard & (0b1ULL << newPos))
		{
			if (board[newPos] & enemyColour)
			{
				board[ourKingPos] = 0;
				if (IsSquareSafe(newPos))
					PushMove(ourKingPos, newPos, MoveFlags::NoFlagCapture);
				board[ourKingPos] = OurKingKey;
			}
			else
			{
				board[ourKingPos] = 0;
				if (IsSquareSafe(newPos))
					PushMove(ourKingPos, newPos, MoveFlags::NoFlag);
				board[ourKingPos] = OurKingKey;
			}
		}
	}
}

template <bool CAPTURE>
inline void UnsafeWaterMelon::AddPromotionMoves(int from, int to)
{
	if constexpr (CAPTURE)
	{
		PushMove(from, to, MoveFlags::PromoteToQueenCapture);
		PushMove(from, to, MoveFlags::PromoteToKnightCapture);
		PushMove(from, to, MoveFlags::PromoteToRookCapture);
		PushMove(from, to, MoveFlags::PromoteToBishopCapture);
	}
	else
	{
		PushMove(from, to, MoveFlags::PromoteToQueen);
		PushMove(from, to, MoveFlags::PromoteToKnight);
		PushMove(from, to, MoveFlags::PromoteToRook);
		PushMove(from, to, MoveFlags::PromoteToBishop);
	}
}

void UnsafeWaterMelon::AddPawnMoves()
{
	// Use magic bitboards to generate the pawn moves

	if (whiteToMove)
	{
		Bitboard whitePawnAttacksBitboard = pieceAttackBitboards[WPawn];
		for (size_t i = 0; i < PieceLists[WPawn].PieceNum; i++)
		{
			int pos = PieceLists[WPawn].OccupiedSquares[i];
			Bitboard posBoard = BitboardFromSquare(pos);
			int leftPos = pos + 7;
			int rightPos = pos + 9;
			int oneMove = pos + 8;
			int twoMove = pos + 16;
			bool isPromotion = BitboardContains(WhitePromotionLine, oneMove);

			if (isPromotion)
			{
				if ((posBoard & LeftSideIs0) << 7 & AllBlackPosBitboard)
					AddPromotionMoves<true>(pos, leftPos);

				if ((posBoard & RightSideIs0) << 9 & AllBlackPosBitboard)
					AddPromotionMoves<true>(pos, rightPos);

				if (board[oneMove] == 0)
					AddPromotionMoves<false>(pos, oneMove);
			}
			else
			{
				if ((posBoard & LeftSideIs0) << 7 & AllBlackPosBitboard)
					PushMove(pos, leftPos, NoFlagCapture);

				if ((posBoard & RightSideIs0) << 9 & AllBlackPosBitboard)
					PushMove(pos, rightPos, NoFlagCapture);

				if (board[oneMove] == 0)
				{
					PushMove(pos, oneMove, NoFlag);
					if (BitboardContains(WhiteTwoMoveLine, pos) && board[twoMove] == 0)
						PushMove(pos, twoMove, PawnDoubleForward);
				}
			}
		}
	}
	else
	{
		Bitboard blackPawnAttacksBitboard = pieceAttackBitboards[BPawn];
		for (size_t i = 0; i < PieceLists[BPawn].PieceNum; i++)
		{
			int pos = PieceLists[BPawn].OccupiedSquares[i];
			Bitboard posBoard = BitboardFromSquare(pos);
			int leftPos = pos - 9;
			int rightPos = pos - 7;
			int oneMove = pos - 8;
			int twoMove = pos - 16;
			bool isPromotion = BitboardContains(BlackPromotionLine, oneMove);

			if (isPromotion)
			{
				if ((posBoard & LeftSideIs0) >> 9 & AllWhitePosBitboard)
					AddPromotionMoves<true>(pos, leftPos);

				if ((posBoard & RightSideIs0) >> 7 & AllWhitePosBitboard)
					AddPromotionMoves<true>(pos, rightPos);

				if (board[oneMove] == 0)
					AddPromotionMoves<false>(pos, oneMove);
			}
			else
			{
				if ((posBoard & LeftSideIs0) >> 9 & AllWhitePosBitboard)
					PushMove(pos, leftPos, NoFlagCapture);

				if ((posBoard & RightSideIs0) >> 7 & AllWhitePosBitboard)
					PushMove(pos, rightPos, NoFlagCapture);

				if (board[oneMove] == 0)
				{
					PushMove(pos, oneMove, NoFlag);
					if (BitboardContains(BlackTwoMoveLine, pos) && board[twoMove] == 0)
						PushMove(pos, twoMove, PawnDoubleForward);
				}
			}
		}

		/*
		int pos = PieceLists[BPawn].OccupiedSquares[i];
			Bitboard posBitboard = BitboardFromSquare(pos);
			Bitboard leftPos = (posBitboard & LeftSideIs0) >> 9;
			Bitboard rightPos = (posBitboard & RightSideIs0) >> 7;
			Bitboard oneMove = (posBitboard & AllEmptyPosBitboard) >> 8;
			Bitboard twoMove = (posBitboard & AllEmptyPosBitboard) >> 16;
			bool isPromotion = BitboardsCollide(BlackPromotionLine, oneMove);

			if (isPromotion)
			{
				if (BitboardsCollide(blackPawnAttacksBitboard & AllWhitePosBitboard, leftPos))
					AddPromotionMoves<true>(pos, pos - 9);

				if (BitboardsCollide(blackPawnAttacksBitboard & AllWhitePosBitboard, rightPos))
					AddPromotionMoves<true>(pos, pos - 7);

				if (oneMove == 0)
					AddPromotionMoves<false>(pos, pos - 8);
			}
			else
			{
				if (BitboardsCollide(blackPawnAttacksBitboard & AllWhitePosBitboard, leftPos))
					PushMove(pos, pos - 9, NoFlagCapture);

				if (BitboardsCollide(blackPawnAttacksBitboard & AllWhitePosBitboard, rightPos))
					PushMove(pos, pos - 7, NoFlagCapture);

				if (oneMove == 0)
				{
					PushMove(pos, pos - 8, NoFlag);
					if (BitboardsCollide(BlackTwoMoveLine, posBitboard) && twoMove == 0)
						PushMove(pos, pos - 16, PawnDoubleForward);
				}
			}
		*/
	}

	if (EPSquare != EmptyEnPassantPos)
	{
		if (whiteToMove)
		{
			TryEnpassantMove(EPSquare - 9, 4);
			TryEnpassantMove(EPSquare - 7, 4);
		}
		else
		{
			TryEnpassantMove(EPSquare + 9, 3);
			TryEnpassantMove(EPSquare + 7, 3);
		}
	}
}

void UnsafeWaterMelon::AddPawnMovesFastTest()
{
	// Use magic bitboards to generate the pawn moves
	if (whiteToMove)
	{
		for (size_t i = 0; i < PieceLists[BPawn].PieceNum; i++)
		{
			int pos = PieceLists[BPawn].OccupiedSquares[i];
			bool isPromotion = BitboardContains(WhitePromotionLine, pos + 8);

			int doubleMoveLine = BitboardFromSquare(pos) & WhiteTwoMoveLine;
			if (((doubleMoveLine << 8) | (doubleMoveLine << 16)) & (AllPiecePosBitboard ^ FullBitboardBoard))
				PushMove(pos, pos + 16, MoveFlags::PawnDoubleForward);

			if ((BitboardFromSquare(pos) << 8) & (AllPiecePosBitboard ^ FullBitboardBoard))
				PushMove(pos, pos + 16, MoveFlags::NoFlag);

			Bitboard PawnAttacks = (((PieceBitboardPos[WPawn] & RightSideIs0) << 9) & AllEnemyPosBitboard) | (((PieceBitboardPos[WPawn] & LeftSideIs0) << 7) & AllEnemyPosBitboard);

		}
	}
	else
	{
		//PawnAttacks = (((PieceBitboardPos[BPawn] & RightSideIs0) >> 7) & AllEnemyPosBitboard) | (((PieceBitboardPos[BPawn] & LeftSideIs0) >> 9) & AllEnemyPosBitboard);

	}

	if (EPSquare != EmptyEnPassantPos)
	{
		if (whiteToMove)
		{
			TryEnpassantMove(EPSquare - 9, 4);
			TryEnpassantMove(EPSquare - 7, 4);
		}
		else
		{
			TryEnpassantMove(EPSquare + 9, 3);
			TryEnpassantMove(EPSquare + 7, 3);
		}
	}
}

void UnsafeWaterMelon::AddPawnMovesBitboardTest()
{
	// Use magic bitboards to generate the pawn moves
	if (whiteToMove)
	{
		Bitboard pawns = PieceBitboardPos[WPawn];
		//Bitboard piece2MoveGap = 
		Bitboard rightAttackPawns = ((pawns & RightSideIs0) << 9) & AllEnemyPosBitboard;
		Bitboard leftAttackPawns = ((pawns & LeftSideIs0) << 7) & AllEnemyPosBitboard;
		Bitboard singlePawnMove = (pawns << 8) & (AllPiecePosBitboard ^ FullBitboardBoard);
		Bitboard doublePawnMove = ((pawns & WhiteTwoMoveLine) << 16) & ((AllPiecePosBitboard | (AllPiecePosBitboard >> 8)) ^ FullBitboardBoard);

		Bitboard rightAttackPawnsPromotion = rightAttackPawns & WhitePromotionLine;
		Bitboard leftAttackPawnsPromotion = leftAttackPawns & WhitePromotionLine;
		Bitboard singlePawnMovePromotion = singlePawnMove & WhitePromotionLine;

		rightAttackPawns &= FullBitboardBoard ^ WhitePromotionLine;
		leftAttackPawns &= FullBitboardBoard ^ WhitePromotionLine;
		singlePawnMove &= FullBitboardBoard ^ WhitePromotionLine;

		Bitboard allStanderd = rightAttackPawns | leftAttackPawns | singlePawnMove | doublePawnMove;
		Bitboard allPromotion = rightAttackPawnsPromotion | leftAttackPawnsPromotion | singlePawnMovePromotion;

		int index = 16; // In standerd chess cant there be any moves to before 16
		rightAttackPawns >>= 16;
		leftAttackPawns >>= 16;
		singlePawnMove >>= 16;
		doublePawnMove >>= 16;
		allStanderd >>= 16;
		while (allStanderd)
		{
			if (allStanderd & 1)
			{
				if (rightAttackPawns & 1)
					PushMove(index - 9, index, MoveFlags::NoFlagCapture);
				if (leftAttackPawns & 1)
					PushMove(index - 7, index, MoveFlags::NoFlagCapture);
				if (singlePawnMove & 1)
					PushMove(index - 8, index, MoveFlags::NoFlag);
				if (doublePawnMove & 1)
					PushMove(index - 16, index, MoveFlags::PawnDoubleForward);
			}
			index++;
			rightAttackPawns >>= 1;
			leftAttackPawns >>= 1;
			singlePawnMove >>= 1;
			doublePawnMove >>= 1;
			allStanderd >>= 1;
		}

		index = 56; // There is no promotions before number 56 aka PromotionLine
		rightAttackPawnsPromotion >>= 56;
		leftAttackPawnsPromotion >>= 56;
		singlePawnMovePromotion >>= 56;
		allStanderd >>= 56;
		while (allPromotion)
		{
			if (allPromotion & 1)
			{
				if (rightAttackPawns & 1)
				{
					AddPromotionMoves<true>(index - 9, index);
				}
				if (leftAttackPawns & 1)
				{
					AddPromotionMoves<true>(index - 7, index);
				}
				if (singlePawnMove & 1)
				{
					AddPromotionMoves<false>(index - 8, index);
				}
			}
			index++;
			rightAttackPawnsPromotion >>= 1;
			leftAttackPawnsPromotion >>= 1;
			singlePawnMovePromotion >>= 1;
			allPromotion >>= 1;
		}
	}

	if (EPSquare != EmptyEnPassantPos)
	{
		if (whiteToMove)
		{
			TryEnpassantMove(EPSquare - 9, 4);
			TryEnpassantMove(EPSquare - 7, 4);
		}
		else
		{
			TryEnpassantMove(EPSquare + 9, 3);
			TryEnpassantMove(EPSquare + 7, 3);
		}
	}
}


void UnsafeWaterMelon::TryEnpassantMove(int movingSquare, int row)
{
	if (GetRank(movingSquare) != row)
		return;

	// becous Enpassant moves two pieces, we do the King check check here.
	// Just check if the king is on the same rank, and if there by chance 
	// also is an enemy queen or rook on the same rank now not blocked

	// Check for pawns behind
	// Move like black pawn
	if (BitboardContains(PieceBitboardPos[OurPawnKey], movingSquare))
	{
		// pawn found and check if king is on line
		if (BitboardContains(RowBitboards[row], ourKingPos))
		{
			// Found king on line
			// now gotta run a line through the two pawns to see if there is a rook or queen on other side attacking
			// check if king on left side, otherwise on right side
			DirectionIndex direction = ourKingPos < EPSquare ? DirectionIndexs::EastI : DirectionIndexs::WestI;
			Bitboard enemySliders = PieceBitboardPos[EnemyRookKey] | PieceBitboardPos[EnemyRookKey];
			if (BitboardsCollide(enemySliders, GetSlidingPieceBitboardFromInDir(ourKingPos, direction)))
			{
				Square pos = ourKingPos;
				Offset offset = offsetsIndexed[direction];
				int pieceCount = 0;
				int distance = GetDistanceToBoardInDirection(ourKingPos, direction);
				for (size_t i = 0; i < distance; i++)
				{
					pos += offset;
					if (BitboardContains(enemySliders, pos))
						break;
					else if (BitboardContains(AllPiecePosBitboard, pos))
						pieceCount++;
				}
				Check(pieceCount > 1, "To few pieces detected");
				if (pieceCount > 2)
					PushMove(movingSquare, EPSquare, EnPassantCapture);
			}
			else
			{
				PushMove(movingSquare, EPSquare, EnPassantCapture);
			}
		}
		else
			PushMove(movingSquare, EPSquare, EnPassantCapture);
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
				if (BitboardContains(AllEnemyPosBitboard, newPos))
					PushMove(pos, newPos, NoFlag);
				else
					PushMove(pos, newPos, NoFlagCapture);
			}
		}
	}
}

bool UnsafeWaterMelon::IsSquareSafe(Square square) const
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
					if (IsPieceColor(hitPiece, enemyColour)) // Use bitboard like with the queen
						PushMove(pos, ray, NoFlagCapture);
					break;
				}
				else
				{
					PushMove(pos, ray, NoFlag);
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
					if (IsPieceColor(hitPiece, enemyColour)) // Use bitboard like with the queen
						PushMove(pos, ray, NoFlagCapture);
					break;
				}
				else
				{
					PushMove(pos, ray, NoFlag);
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
						PushMove(pos, ray, NoFlagCapture);
					break;
				}
				else
				{
					PushMove(pos, ray, NoFlag);
				}
			}
		}
	}
}

void UnsafeWaterMelon::AddCastleMoves()
{
	if (whiteToMove)
	{
		if ((castle & CastleRights::WhiteKingSide) && !BitboardsCollide(AllPiecePosBitboard, 96/*5,6*/))
			// clear path
			if (IsSquareSafe(5) && IsSquareSafe(6))
				// safe path
				PushMove(4, 6, MoveFlags::Castling);

		if ((castle & CastleRights::WhiteQueenSide) && !BitboardsCollide(AllPiecePosBitboard, 14/*3,2,1*/))
			if (IsSquareSafe(3) && IsSquareSafe(2))
				PushMove(4, 2, MoveFlags::Castling);
	}
	else
	{
		if ((castle & CastleRights::BlackKingSide) && !BitboardsCollide(AllPiecePosBitboard, 6917529027641081856/*61,62*/))
			if (IsSquareSafe(61) && IsSquareSafe(62))
				PushMove(60, 62, MoveFlags::Castling);

		if ((castle & CastleRights::BlackQueenSide) && !BitboardsCollide(AllPiecePosBitboard, 1008806316530991104/*57,58,59*/))
			if (IsSquareSafe(59) && IsSquareSafe(58))
				PushMove(60, 58, MoveFlags::Castling);
	}
}

inline void UnsafeWaterMelon::PushMove(Square start, Square target, MoveFlag flag)
{
	moves[movesCount++] = CreateMove(start, target, flag);
}

template<MoveType type, MoveOrderingTypes order>
int UnsafeWaterMelon::GetPossibleMoves(Move* movesPtr)
{
	/*

		*Other then the king moves
		When we add the moves we just use the normal PushMove, then at the end we
		do the quad if statement check to see what we acually have to check for (checks and pins)
		and if there is none we dont even have to do anything with it.
		But if we have to check for pins or checks or both, we make a while loop to remove all
		the invalid moves by moving the last move into the removed move space until we are at the end

	*/


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

	int kingMovesCount = movesCount;

	AddPawnMoves();
	AddKnightMoves();
	AddRookMoves();
	AddBishopMoves();
	AddQueenMoves();
	AddCastleMoves();


	// Remove invalid moves
	if (KingInCheck)
	{
		if (pinnedPieces)
		{
			// Pinned and in check
			for (size_t i = kingMovesCount; i < movesCount; i++)
			{
				int start = GetMoveStart(moves[i]);
				int target = GetMoveTarget(moves[i]);
				if (!BitboardContains(attacksOnKing, target))
				{
					moves[i--] = moves[--movesCount];
					continue;
				}
				if (BitboardContains(pinnedPieces, start))
				{
					if (!BitboardContains(pinningPiecesAttack[start], target))
					{
						moves[i--] = moves[--movesCount];
						continue;
					}
				}
			}
		}
		else
		{
			// Just in check
			for (size_t i = kingMovesCount; i < movesCount; i++)
			{
				int target = GetMoveTarget(moves[i]);
				if (!BitboardContains(attacksOnKing, target))
				{
					moves[i--] = moves[--movesCount];
					continue;
				}
			}
		}
	}
	else if (pinnedPieces)
	{
		// Just pinned
		for (size_t i = kingMovesCount; i < movesCount; i++)
		{
			int start = GetMoveStart(moves[i]);
			int target = GetMoveTarget(moves[i]);
			if (BitboardContains(pinnedPieces, start))
			{
				if (!BitboardContains(pinningPiecesAttack[start], target))
				{
					moves[i--] = moves[--movesCount];
					continue;
				}
			}
		}
	}

	if constexpr (type == CAPTURE_Moves)
		RemoveNoneCaptures(); // Only temperary, later use a more effictive method where itergrate the Catpures only into the AddPiece methods

	if constexpr (order == SIMPLE_MoveOrder)
		OrderMoves();
	if constexpr (order == ADVANCED_MoveOrder)
		ThrowNotImplementedException("ADVANCED_MoveOrder have not been implemented");

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
		if (KingInCheck)
		{
		}
		else
		{
		}
	}

*/