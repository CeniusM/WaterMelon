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
			str += "   " + line + "\n";
			str += " " + static_cast<char>((8 - i));
			str += " ";
			for (int j = 0; j < 8; j++)
			{
				str += "| " + static_cast<char>(FENUtility::IntToChar[board.boardPtr[i+(j*8)]]);
				str += " ";
			}
			str += "|\n";
		}
		str += "   " + line + "\n";
		str += "     A   B   C   D   E   F   G   H\n";

		return str;
	}
};