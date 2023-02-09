#pragma once

// Number between [0 - 63], and uses -1 to indicate an invalid pos or none initialized pos
typedef int Pos;

// works between 65535 and -65472 
constexpr bool IsPosInside(Pos pos)
{
	return (pos & 0xFFC0) == 0;
}