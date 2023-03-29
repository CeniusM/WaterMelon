#pragma once

// not sure if this should be a float or an int
typedef int Eval;

constexpr Eval Eval_Equal = 0;
constexpr Eval Eval_Infinit = 999999;
constexpr Eval Eval_NegInfinit = -999999;

#pragma region Material

constexpr Eval PawnEarlyGameValue = 100;
constexpr Eval KnightEarlyGameValue = 400;
constexpr Eval BishopEarlyGameValue = 440;
constexpr Eval RookEarlyGameValue = 450;
constexpr Eval QueenEarlyGameValue = 950;

constexpr Eval PawnMidGameValue = 100;
constexpr Eval KnightMidGameValue = 305;
constexpr Eval BishopMidGameValue = 333;
constexpr Eval RookMidGameValue = 563;
constexpr Eval QueenMidGameValue = 950;

constexpr Eval PawnLateGameValue = 100;
constexpr Eval KnightLateGameValue = 305;
constexpr Eval BishopLateGameValue = 333;
constexpr Eval RookLateGameValue = 563;
constexpr Eval QueenLateGameValue = 950;

#pragma endregion

#pragma region PiecePlacmentMap

#pragma endregion

#pragma region PawnStructure

constexpr Eval DoublePawnPenelty = -80;
constexpr Eval TriplePawnPenelty = -120;

constexpr Eval PawnLinkBonus = 20;

#pragma endregion

#pragma region KingSafty

#pragma endregion

#pragma region Outpos

#pragma endregion

#pragma region PieceActivation

#pragma endregion


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

