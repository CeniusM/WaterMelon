
#include "MoveMisc.hpp"

std::string GetSquareName(Square square)
{
	std::string str{};

	if (!TransformSquareEnabled)
	{
		square = FlipSquareY(square);
	}

	int xSquare = GetCollum(square);
	int ySquare = GetRank(square);

	str += static_cast<char>('a' + xSquare);
	str += static_cast<char>('1' + ySquare);
	
	return str;
}

std::string GetMoveName(Move move)
{
	int start = GetMoveStart(move);
	int target = GetMoveTarget(move);

	if (!TransformSquareEnabled)
	{
		start = FlipSquareY(start);
		target = FlipSquareY(target);
	}

	int xStart = GetCollum(start);
	int yStart = GetRank(start);

	int xTarget = GetCollum(target);
	int yTarget = GetRank(target);

	std::string str{};
	str += static_cast<char>('a' + xStart);
	str += static_cast<char>('1' + yStart);
	//str += " to ";
	str += static_cast<char>('a' + xTarget);
	str += static_cast<char>('1' + yTarget);
	return str;
}