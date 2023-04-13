#pragma once

#include "Square.hpp"
#include "Checker.hpp"

typedef unsigned long long Bitboard;

constexpr Bitboard SignificantBit = 0b1ULL;//0x8000000000000000ULL
constexpr Bitboard LeftSide = 0x8080808080808080ULL;
constexpr Bitboard RightSide = 0x0101010101010101ULL;
constexpr Bitboard TopSide = 0xffULL;
constexpr Bitboard ButtomSide = 0xff00000000000000ULL;

constexpr Bitboard WhitePromotionLine = ButtomSide;
constexpr Bitboard WhiteTwoMoveLine = 0xFF00ULL;
constexpr Bitboard BlackPromotionLine = TopSide;
constexpr Bitboard BlackTwoMoveLine = 0xFF000000000000ULL;

constexpr Bitboard FullBitboardBoard = 0xffffffffffffffff;

constexpr Bitboard RightSideIs0 = 0b0111111101111111011111110111111101111111011111110111111101111111ULL;
constexpr Bitboard LeftSideIs0 = 0b1111111011111110111111101111111011111110111111101111111011111110ULL;
constexpr Bitboard RightSideIs1 = FullBitboardBoard ^ RightSideIs0;
constexpr Bitboard LeftSideIs1 = FullBitboardBoard ^ LeftSideIs0;

// Bitboard across a row
constexpr Bitboard RowBitboards[]
{
255,65280,16711680,4278190080,1095216660480,280375465082880,71776119061217280,18374686479671623680
};

constexpr Bitboard CollumBitboards[]
{
72340172838076673,144680345676153346,289360691352306692,578721382704613384,1157442765409226768,2314885530818453536,4629771061636907072,9259542123273814144
};

constexpr int DistanceToNextBit[]
{
	7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0
};

// Only takes in a bitboard that is not 0, returns the bits removed count, and shifts the board
constexpr int GetNextBit(Bitboard& b)
{
	Check(b != 0, "GetNextBit can not take in an empty bitboard");

	//ThrowNotImplementedException("Have not implemented DistanceToNextBit");

	int count = 0;
	do
	{
		int distance = DistanceToNextBit[b & 0xff];
		count += distance;
		b >>= distance;
	} while ((b & 0b1) == 0);

	return count;
}

constexpr bool BitboardContains(Bitboard bitboard, Square pos)
{
	return (bitboard >> pos) & SignificantBit;
}

constexpr Bitboard BitboardFromSquare(Square pos)
{
	return 0b1ULL << pos;
}

constexpr Bitboard BitboardSetSquare(Bitboard bitboard, Square pos)
{
	return bitboard | (0b1ULL << pos);
}

constexpr Bitboard BitboardSetSquares(Bitboard bitboard, Square pos1, Square pos2)
{
	return bitboard | (0b1ULL << pos1) | (0b1ULL << pos2);
}

constexpr Bitboard BitboardsCollide(Bitboard bitboard, Bitboard bitboard2)
{
	return bitboard & bitboard2;
}

constexpr bool PosOnLeftSide(Square pos)
{
	return (LeftSide >> pos) & SignificantBit;
}

constexpr bool PosOnRightSide(Square pos)
{
	return (RightSide >> pos) & SignificantBit;
}

// Black side
constexpr bool OnTop(Square pos)
{
	return (TopSide >> pos) & SignificantBit;
}

// White side
constexpr bool OnButtom(Square pos)
{
	return (ButtomSide >> pos) & SignificantBit;
}

// Just have a one at the given pos
constexpr Bitboard DotBiboards[]
{
1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824,2147483648,4294967296,8589934592,17179869184,34359738368,68719476736,137438953472,274877906944,549755813888,1099511627776,2199023255552,4398046511104,8796093022208,17592186044416,35184372088832,70368744177664,140737488355328,281474976710656,562949953421312,1125899906842624,2251799813685248,4503599627370496,9007199254740992,18014398509481984,36028797018963968,72057594037927936,144115188075855872,288230376151711744,576460752303423488,1152921504606846976,2305843009213693952,4611686018427387904,9223372036854775808
};

// Just have a zero at the given pos
constexpr Bitboard InverseDotBiboards[]
{
18446744073709551614,18446744073709551613,18446744073709551611,18446744073709551607,18446744073709551599,18446744073709551583,18446744073709551551,18446744073709551487,18446744073709551359,18446744073709551103,18446744073709550591,18446744073709549567,18446744073709547519,18446744073709543423,18446744073709535231,18446744073709518847,18446744073709486079,18446744073709420543,18446744073709289471,18446744073709027327,18446744073708503039,18446744073707454463,18446744073705357311,18446744073701163007,18446744073692774399,18446744073675997183,18446744073642442751,18446744073575333887,18446744073441116159,18446744073172680703,18446744072635809791,18446744071562067967,18446744069414584319,18446744065119617023,18446744056529682431,18446744039349813247,18446744004990074879,18446743936270598143,18446743798831644671,18446743523953737727,18446742974197923839,18446741874686296063,18446739675663040511,18446735277616529407,18446726481523507199,18446708889337462783,18446673704965373951,18446603336221196287,18446462598732840959,18446181123756130303,18445618173802708991,18444492273895866367,18442240474082181119,18437736874454810623,18428729675200069631,18410715276690587647,18374686479671623679,18302628885633695743,18158513697557839871,17870283321406128127,17293822569102704639,16140901064495857663,13835058055282163711,9223372036854775807
};