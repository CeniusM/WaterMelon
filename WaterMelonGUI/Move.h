#pragma once

#define Move int
#define MoveFlag int

//namespace MoveFlag
//{
	// in order of what is most likly to happend
constexpr MoveFlag None = 0;
constexpr MoveFlag PawnTwoForward = 1;
constexpr MoveFlag EnPassantCapture = 2;
constexpr MoveFlag Castling = 3;
constexpr MoveFlag PromoteToQueen = 4;
constexpr MoveFlag PromoteToKnight = 5;
constexpr MoveFlag PromoteToRook = 6;
constexpr MoveFlag PromoteToBishop = 7;
//};

struct MoveUtil
{
public:
	Move GetMove(int Start, int End, MoveFlag flag)
	{

	}
};

//struct Move
//{
//private:
//	int m_val;
//	Move(char s, char t, char f)
//	{
//		StartSquare = s;
//		TargetSquare = t;
//		MoveFlag = f;
//	}
//	Move()
//	{
//		StartSquare = 0;
//		TargetSquare = 0;
//		MoveFlag = 0;
//	}
//};

//struct Move
//{
//    char StartSquare;
//    char TargetSquare;
//    char MoveFlag;
//    Move(char s, char t, char f)
//    {
//        StartSquare = s;
//        TargetSquare = t;
//        MoveFlag = f;
//    }
//    Move()
//    {
//        StartSquare = 0;
//        TargetSquare = 0;
//        MoveFlag = 0;
//    }
//};