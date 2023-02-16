#pragma once

#include <string>

#include "PieceList.h"
#include "FENUtility.h"
#include "Logger.h"
#include "TypesIncludes.h"
#include "ThrowHelper.h"

#define MaxMovesCount 512


#pragma region Consts
constexpr int MaxMoves = MaxMovesCount;
constexpr int WhiteIndex = 0;
constexpr int BlackIndex = 1;

constexpr int PlayerTurnSwitch = 0b11000;
#pragma endregion



/// <summary>
/// Used to make moves on the board, and can generate possible moves from the given position
/// </summary>
class UnsafeWaterMelon
{
public:
	GameState gameState = GameStates::Running;

	BoardStateSave boardStateHistory[256];

	Piece board[64]{};
	CastleRight castle{};
	int EPSquare{};
	int playerTurn{};


	// Will consider the move completly valid, this can be done by making sure it comes from the generated moves
	void MakeMove(Move move);
	void UnMakeMove();

	/// This will generate the moves and copy them to the pointer, and return the count. The pointer size is expected to be atlist "MaxMovesCount"
	int GetPossibleMoves(Move* moves);

	void InitFEN(std::string FEN);
	std::string GetFEN();

	UnsafeWaterMelon();
	UnsafeWaterMelon(std::string FEN);
	~UnsafeWaterMelon();



#pragma region Move generation code

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

	Piece* whitePawnsPtr;
	Piece* whiteKnightsPtr;
	Piece* whiteBishopsPtr;
	Piece* whiteRooksPtr;
	Piece* whiteQueensPtr;
	Piece* blackPawnsPtr;
	Piece* blackKnightsPtr;
	Piece* blackBishopsPtr;
	Piece* blackRooksPtr;
	Piece* blackQueensPtr;
#pragma endregion

	Move tempMoves[MaxMovesCount];
	int tempMovesCount;


	// make attack bitboard for all the pieces
	// also make a bitboard where its the attack pos and end square where it 
	// then returns a bitboard with 1's from the atacking square to the attacked square
	// Bitboard BitboardAttacksFromSquareToSquare[square1][square2]
	// but must allways must be valid direction, must include square 1 and 2 in bitboard
	// so if its like 4x4 and the attack goes from 0-10
	// 1000
	// 0100
	// 0010
	// 000k
	Bitboard pinningPiecesAttack[64]; // use the pos of the piece as index
	Bitboard pinnedPieces;

	Bitboard allEnemyAttacks;

	Bitboard kingPins{};

	bool KingInCheck;
	bool KingInDoubleCheck;

	bool whiteToMove;

	int ourColour;
	int ourKingPos;
	int ourColorIndex;

	int enemyColour;
	int enemyKingPos;
	int enemyColorIndex;

#pragma endregion

	bool HasInit() { return m_HasInit; }
private:
	bool m_HasInit = false;

	/// <summary>
	/// Generate the bitboards for the pinned pieces to the king. AND the bitboard for all the enemy attacks, wich the evaluator could also use
	/// </summary>
	void GeneratePinsAndAttacks();
	void AddKingMoves();
};

//#ifndef UsafeWaterMelonCPP
//#   include "UnsafeWaterMelon.cpp"
//#endif




/*




void PossibleMovesGenerator::Init()
{
	//_memccpy(thisBoard, otherBoard, INT32_MAX, sizeof(Piece) * 64);
	memcpy_s(thisBoard, sizeof(Piece) * 64, otherBoard, sizeof(Piece) * 64);

	movesCount = 0;
	pinnedPieces = 0;

	KingInCheck = false;
	KingInDoubleCheck = false;

	ourColour = *playerTurn;
	whiteToMove = (ourColour == White);
	enemyColour = ourColour ^ PlayerTurnSwitch;
	castle = *castlePtr;

	if (whiteToMove)
	{
		ourKingPos = unsafeBoard->kingPos[0];
		enemyKingPos = unsafeBoard->kingPos[1];
		OurPawns = unsafeBoard->whitePawnsPtr;
		OurKnights = unsafeBoard->whiteKnightsPtr;
		OurBishops = unsafeBoard->whiteBishopsPtr;
		OurRooks = unsafeBoard->whiteRooksPtr;
		OurQueens = unsafeBoard->whiteQueensPtr;
		EnemyPawns = unsafeBoard->blackPawnsPtr;
		EnemyKnights = unsafeBoard->blackKnightsPtr;
		EnemyBishops = unsafeBoard->blackBishopsPtr;
		EnemyRooks = unsafeBoard->blackRooksPtr;
		EnemyQueens = unsafeBoard->blackQueensPtr;
	}
	else
	{
		ourKingPos = unsafeBoard->kingPos[1];
		enemyKingPos = unsafeBoard->kingPos[0];
		EnemyPawns = unsafeBoard->whitePawnsPtr;
		EnemyKnights = unsafeBoard->whiteKnightsPtr;
		EnemyBishops = unsafeBoard->whiteBishopsPtr;
		EnemyRooks = unsafeBoard->whiteRooksPtr;
		EnemyQueens = unsafeBoard->whiteQueensPtr;
		OurPawns = unsafeBoard->blackPawnsPtr;
		OurKnights = unsafeBoard->blackKnightsPtr;
		OurBishops = unsafeBoard->blackBishopsPtr;
		OurRooks = unsafeBoard->blackRooksPtr;
		OurQueens = unsafeBoard->blackQueensPtr;
	}
}

int PossibleMovesGenerator::GetMovesCopy(Move* movesPtr)
{
	//for (int i = 0; i < movesCount; i++)
	//	movesPtr[i] = moves[i];
		//_memccpy(movesPtr, moves, 0, sizeof(Move) * movesCount);
memcpy_s(movesPtr, sizeof(Move)* MaxMovesCount, moves, sizeof(Move)* movesCount);
return movesCount;
}

int PossibleMovesGenerator::GetCount()
{
	return movesCount;
}

PossibleMovesGenerator::PossibleMovesGenerator(UnsafeWaterMelon* boardRef)
{
	unsafeBoard = boardRef;

	for (int i = 0; i < 256; i++)
		//moves[i] = Move(0, 0, 0);
		moves[i] = InvalidPos;

	thisBoard = board;
	otherBoard = boardRef->board;

	playerTurn = &(*boardRef).playerTurn;
	castlePtr = &(*boardRef).castle;
	EPSquarePtr = &(*boardRef).EPSquare;
}

PossibleMovesGenerator::~PossibleMovesGenerator()
{
}

#pragma region Move_Generation

void PossibleMovesGenerator::GeneratePawnMoves()
{
	int count = OurPawns[-1];
	for (size_t i = 0; i < count; i++)
	{
		moves[movesCount] = CreateMove(OurPawns[i], OurPawns[i] - 8, NoFlag);
		movesCount++;
	}
}

void PossibleMovesGenerator::GenerateKnightMoves()
{
	int count = OurKnights[-1];
	for (size_t i = 0; i < count; i++)
	{
		moves[movesCount] = CreateMove(OurKnights[i], OurKnights[i] - 16, NoFlag);
		movesCount++;
	}
}


*/