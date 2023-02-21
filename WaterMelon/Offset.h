#pragma once

// integer offset from square to a new square
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