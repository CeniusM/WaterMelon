#pragma once

// Number between [0 - 63], and uses -1 to indicate an invalid square or none initialized square
typedef int Square;

constexpr Square InvalidPos = -1;
constexpr Square InclusiveLowerBoundPos = 0;
constexpr Square InclusiveUpperBoundPos = 63;
constexpr Square ExclusiveLowerBoundPos = -1;
constexpr Square ExclusiveUpperBoundPos = 64;

// works between 65535 and -65472 
constexpr bool IsSquareInside(Square square)
{
	return (square & 0xFFC0) == 0;
}

enum Squares : Square
{
	a8 = 0, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1,
};

