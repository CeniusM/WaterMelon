
#include "MoveMisc.hpp"

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
	str += " to ";
	str += static_cast<char>('a' + xTarget);
	str += static_cast<char>('1' + yTarget);
	return str;
}