#pragma once

#include <string>

#include "../WaterMelonEngine/UnsafeWaterMelon.h"

class BoardAsString
{
public:
	static std::string GetStringFromUnsafe(UnsafeWaterMelon& board)
	{
		std::string str = "";

		const std::string line = "+---+---+---+---+---+---+---+---+";

		for (int i = 0; i < 8; i++)
		{
			str += "   ";
			str += line + "\n";
			str += " ";
			str += std::to_string(8-i);
			str += " ";
			for (int j = 0; j < 8; j++)
			{
				char piece = static_cast<char>(FENUtility::IntToChar[board.boardPtr[j + (i*8)]]);
				if (piece == 0)
					piece = ' ';
				str += "| ";
				str += piece;
				str += " ";
			}
			str += "|\n";
		}
		str += "   " + line + "\n";
		str += "     A   B   C   D   E   F   G   H\n";

		return str;
	}
};