#pragma once

#include <string>
#include <iterator> // for debuging
#include <list> // for debuging

#include "PieceList.h"
#include "FENUtility.h"
#include "Logger.h"
#include "TypesIncludes.h"
#include "ThrowHelper.h"

#define MaxMovesCount 256
//512, if each side had half an hour, they have 7 seconds for each move, this hould be enough
#define MaxGameMovesCount 512

#pragma region Consts
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

	// --- DEBUGING ---

	std::list<Square> SquaresToRenderByGUIForDebuing{}; // Don't mind the name

	// ^^^ DEBGUING ^^^

	GameState gameState = GameStates::Running;

	BoardStateSave boardStateHistory[MaxGameMovesCount];
	int currentBoardStateCount = 0;

	Piece board[64]{};
	CastleRight castle{};
	EnPassantPos EPSquare{};
	Color playerTurn{};


	// Will consider the move completly valid, this can be done by making sure it comes from the generated moves
	void MakeMove(Move move);
	void UnMakeMove();

	/// This will generate the moves and copy them to the pointer, and return the count. The pointer size is expected to be atlist "MaxMovesCount"
	int GetPossibleMoves(Move* movesPtr, bool onlyCaptures = false, bool moveOrder = false);

	// Checks for the current enemy, and only works after GenerateBitboards() or GetPossibleMoves()
	bool IsSquareSafe(Square square);

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
	//PieceList WhitePawnsList{};
	//PieceList WhiteKnightsList{};
	//PieceList WhiteBishopsList{};
	//PieceList WhiteRooksList{};
	//PieceList WhiteQueensList{};

	//PieceList BlackPawnsList{};
	//PieceList BlackKnightsList{};
	//PieceList BlackBishopsList{};
	//PieceList BlackRooksList{};
	//PieceList BlackQueensList{};

	//PieceList* allPieceLists[24]; // BQueen 23
	PieceList PieceLists[24]{};
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
	Bitboard pinningPiecesAttack[64]{ 0 }; // use the pos of the piece as index
	Bitboard pinnedPieces;

	// All the bitboard of the piece attacks
	Bitboard pieceAttackBitboards[24]{};
	Bitboard allFriendlyAttakcs{};
	Bitboard allEnemyAttacks{};

	// This will have a line from the enemy piece to right infron of the king if is a sliding peice,
	// If it is a knight or a pawn, it will just show its pos, so when you move to that pos
	// you have captured the attacking enemy piece, or block the attack
	Bitboard attacksOnKing;


	// -- For all the bitboard poses, it is just 3 XOR operations for the start to target square bitboard
	// Bitboard of all the posses, use piece value as index
	Bitboard PieceBitboardPos[24]{ 0 };
	Bitboard AllFriendlyPiecePosBitboard;
	Bitboard AllEnemyPosBitboard;
	Bitboard AllPiecePosBitboard;

#pragma endregion

	bool KingInCheck;
	bool KingInDoubleCheck;

	bool whiteToMove;

	int ourColor;
	int ourKingPos;
	int ourColorIndex;

	int enemyColour;
	int enemyKingPos;
	int enemyColorIndex;

	int ourKingPieceVal;
	int enemyKingPieceVal;


	Piece OurPawnKey;
	Piece OurKnightKey;
	Piece OurBishopKey;
	Piece OurRookKey;
	Piece OurQueenKey;
	Piece OurKingKey;
	Piece EnemyPawnKey;
	Piece EnemyKnightKey;
	Piece EnemyBishopKey;
	Piece EnemyRookKey;
	Piece EnemyQueenKey;
	Piece EnemyKingKey;


	/*
	*
	*  ---- This is stupid, i think i can do better than copying the board every time ----
	* Im not sure, but my intuition tells me that i can just use moves to find out if we have repated moves
	* instead of this copy board and way to many if statements for comparing, comparing 10 moves and copying one move per move
	* is Wayyyy faster than copying a whole board again and again and doing 32 if statements in a row to check for repetetion
	*
	// -- Work In Progress -- Very very much a work in progress, need to read up on some rules....
	// 50 move rule and 3 repetetion rule
	// Ideer, for when we are unmaking moves, we can just make a long array somewhere else to store the BoardSave, and one by one load them back in
	// An array of like 1000 or somewhere to store them, maby in a stack
	BoardSave boardSaves[6];
	int boardSaveIndex = 0; // used to go around the array from start to end and back around again
#define Is3RepetionRuleMet()\
(AllBoardSavesEquel(board[0], board[2], board[4]) && AllBoardSavesEquel(board[1], board[3], board[5]))

	// 50 move rule, increament by one every move, and set to 0 at pawn move or capture, pretty simple
	// BUT, it has to go to 100 beacous its 50 moves for EACH side
	int MoveWithoutCaptureOrPawnMove = 0;*/

#pragma endregion

	bool HasInit() { return m_HasInit; }
private:
	bool m_HasInit = false;

	void RemoveNoneCaptures();
	void OrderMoves();

	void GenerateBitboards();
	/// <summary>
	/// Generate the bitboards for the pinned pieces to the king.
	/// </summary>
	void GeneratePinsAndAttacksOnKing();
	void AddKingMoves();
	void AddPawnMoves();
	void AddQueenMoves();

	void PushMove(Move move);
	void PushMoveIfPinnsAllow(Move move);
	void PushMoveIfPinnsAllowAndKingNotInCheck(Move move);
	void PushMoveIfKingNotInCheck(Move move);

	constexpr bool IsPiecePinned(Square pos)
	{
		return BitboardContains(pinnedPieces, pos);
	}

	constexpr bool IsPieceClearOfPin(Square pos)
	{
		return (DotBiboards[pos] & pinnedPieces) == 0;
	}
};