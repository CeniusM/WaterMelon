#pragma once

// integer offset from pos to a new pos
typedef int Offset;

constexpr Offset Invalid_Offset = -999;

constexpr bool IsOffsetInvalid(Offset os)
{
	return os == Invalid_Offset;
}

constexpr bool IsOffsetValid(Offset os)
{
	return os != Invalid_Offset;
}