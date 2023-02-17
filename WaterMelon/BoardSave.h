#pragma once

#include "Piece.h" // For define below

#ifdef UsingIntForPiece
"This need to chrash, the given way of checking the 3 repetetion move rule does not work unless the piece size is 1 byte"
#endif

typedef unsigned long long U64;

struct BoardSave
{
	U64 row0;
	U64 row1;
	U64 row2;
	U64 row3;
	U64 row4;
	U64 row5;
	U64 row6;
	U64 row7;

	void Save(Piece* board)
	{
		U64* ptr = (U64*)board;

		row0 = ptr[0];
		row1 = ptr[1];
		row2 = ptr[2];
		row3 = ptr[3];
		row4 = ptr[4];
		row5 = ptr[5];
		row6 = ptr[6];
		row7 = ptr[7];
	}
};

// Dont quiet know if this is the most optimal way of doing it
static bool AllBoardSavesEquel(BoardSave* save1, BoardSave* save2, BoardSave* save3)
{
	// Save 1 and 2
	if (save1->row0 == save2->row0)
		if (save1->row1 == save2->row1)
			if (save1->row2 == save2->row2)
				if (save1->row3 == save2->row3)
					if (save1->row4 == save2->row4)
						if (save1->row5 == save2->row5)
							if (save1->row6 == save2->row6)
								if (save1->row7 == save2->row7)
									// 2 and 3
									if (save2->row0 == save3->row0)
										if (save2->row1 == save3->row1)
											if (save2->row2 == save3->row2)
												if (save2->row3 == save3->row3)
													if (save2->row4 == save3->row4)
														if (save2->row5 == save3->row5)
															if (save2->row6 == save3->row6)
																if (save2->row7 == save3->row7)
																	return true;
	return false;
}