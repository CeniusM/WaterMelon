#pragma once

namespace MoveFlag
{
    // in order of what is most likly to happend
    constexpr char None = 0;
    constexpr char PawnTwoForward = 1;
    constexpr char EnPassantCapture = 2;
    constexpr char Castling = 3;
    constexpr char PromoteToQueen = 4;
    constexpr char PromoteToKnight = 5;
    constexpr char PromoteToRook = 6;
    constexpr char PromoteToBishop = 7;
};

struct Move
{
    char StartSquare;
    char TargetSquare;
    char MoveFlag;
    Move(char s, char t, char f)
    {
        StartSquare = s;
        TargetSquare = t;
        MoveFlag = f;
    }
    Move()
    {
        StartSquare = 0;
        TargetSquare = 0;
        MoveFlag = 0;
    }
};