#pragma once

#include <string>

#include "PieceList.h"
#include "FENUtility.h"
#include "Logger.h"
#include "TypesIncludes.h"
#include "ThrowHelper.h"

#define MaxMovesCount 256

#pragma region Consts
constexpr int MaxMoves = MaxMovesCount;
constexpr int WhiteIndex = 0;
constexpr int BlackIndex = 1;

constexpr int PlayerTurnSwitch = 0b11000;
#pragma endregion

/// <summary>
/// Used to make moves on the board, and can generate possible moves from the given position, and evaluate a position.
/// And is very very error prone, so be care full. Very much optimized for speed.
/// Use the SafeWaterMelon for error handling and eas of use.
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
	int GetPossibleMoves(Move* movesPtr, bool onlyCaptures = false, bool moveOrder = false);

	/// WARNING: ONLY CALL THIS AFTER GetPossibleMoves() IS CALLED. Positiv is good for white and negativ is good for black.
	int GetEvaluation();


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

	Move moves[MaxMovesCount];
	int movesCount;

#pragma region Bitboards

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

	Bitboard whitePawnAttacksBitboard = 0;
	Bitboard blackPawnAttacksBitboard = 0;

	Bitboard allEnemyAttacks;

	Bitboard kingPins{};
#pragma endregion

	bool KingInCheck;
	bool KingInDoubleCheck;

	bool whiteToMove;

	int ourColour;
	int ourKingPos;
	int ourColorIndex;

	int enemyColour;
	int enemyKingPos;
	int enemyColorIndex;


	// -- Work In Progress --
	// 50 move rule and 3 repetetion rule
	// Ideer, for when we are unmaking moves, we can just make a long array somewhere else to store the BoardSave, and one by one load them back in
	// An array of like 1000 or somewhere to store them, maby in a stack
	BoardSave boardSaves[6];
	int boardSaveIndex = 0; // used to go around the array from start to end and back around again
#define Is3RepetionRuleMet()\
(AllBoardSavesEquel(board[0], board[2], board[4]) && AllBoardSavesEquel(board[1], board[3], board[5]))

	// 50 move rule, increament by one every move, and set to 0 at pawn move or capture, pretty simple
	int MoveWithoutCaptureOrPawnMove = 0;

#pragma endregion

	bool HasInit() { return m_HasInit; }
private:
	bool m_HasInit = false;

	void RemoveNoneCaptures();
	void OrderMoves();

	/// <summary>
	/// Generate the bitboards for the pinned pieces to the king. AND the bitboard for all the enemy attacks, wich the evaluator could also use
	/// </summary>
	void GeneratePinsAndAttacks();
	void AddKingMoves();
	void AddPawnMoves();
};