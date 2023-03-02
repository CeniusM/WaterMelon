#pragma once

// not sure if this should be a float or an int
typedef float EvaluationF;

constexpr EvaluationF Eval_Equal = 0;
constexpr EvaluationF Eval_Infinit = 999999;
constexpr EvaluationF Eval_NegInfinit = -999999;

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