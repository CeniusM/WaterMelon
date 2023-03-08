
/*

Board:

	a	b	c	d	e	f	g	h
1  WR  WN  WB  WQ  WK  WB  WN  WR
2  WB  WB  WB  WB  WB  WB  WB  WB
3
4
5
6
7  BB  BB  BB  BB  BB  BB  BB  BB
8  BR  BN  BB  BQ  BK  BB  BN  BR

	a	b	c	d	e	f	g	h
1  [00][01][02][03][04][05][06][07]
2  [08][09][10][11][12][13][14][15]
3  [16][17][18][19][20][21][22][23]
4  [24][25][26][27][28][29][30][31]
5  [32][33][34][35][36][37][38][39]
6  [40][41][42][43][44][45][46][47]
7  [48][49][50][51][52][53][54][55]
8  [56][57][58][59][60][61][62][63]

*/

#pragma once

#include "Square.h"

typedef int Rank;
typedef int Collum;


enum Ranks
{
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
};

enum Collums
{
	_a,
	_b,
	_c,
	_d,
	_e,
	_f,
	_g,
	_h,
};

constexpr Rank GetRank(Square sq)
{
	return sq >> 3;
}

constexpr Collum GetCollum(Square sq)
{
	return sq % 8;
}

constexpr Square GetSquareFromRankAndCollum(Rank rank, Collum collum)
{
	return (rank << 3) + collum;
}


/// <summary>
/// Flips the board since the unsafe board and the human board is not oriantated together.
/// It just flips the y axis
/// </summary>
constexpr int FlipSquareY(Square square)
{
	Rank rank = GetRank(square);
	Collum col = GetCollum(square);
	return GetSquareFromRankAndCollum(7 - rank, col);
}

/// <summary>
/// Flips the square on the X axis
/// </summary>
constexpr int FlipSquareX(Square square)
{
	Rank rank = GetRank(square);
	Collum col = GetCollum(square);
	return GetSquareFromRankAndCollum(rank, 7 - col);
}

/// <summary>
/// Also rotates the board 180
/// </summary>
constexpr int FlipSquareXY(Square square)
{
	Rank rank = GetRank(square);
	Collum col = GetCollum(square);
	return GetSquareFromRankAndCollum(7 - rank, 7 - col);
}