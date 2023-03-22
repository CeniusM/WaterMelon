#include "PerftUtil.hpp"

unsigned long long PerftCount(UnsafeWaterMelon& board, int depth)
{
	long Count = 0;
	Move moves[MaxMovesCount];
	int movesCount = board.GetPossibleMoves(moves);

	if (depth == 1)
		return movesCount;

	for (size_t i = 0; i < movesCount; i++)
	{
		board.MakeMove(moves[i]);
		Count += PerftCount(board, depth - 1);
		board.UnMakeMove();
	}

	return Count;
}

unsigned long long TestPerftPos(std::string fen, int depth)
{
	UnsafeWaterMelon board{ fen };

	return PerftCount(board, depth);
}

void TestPos(Assert& assert, std::string fen, int depth, int expectedCount)
{
	unsigned long long count = TestPerftPos(fen, depth);
	assert.AssertTrue(count == expectedCount, "Count recorded: " + std::to_string(count) + ". Expected: " + std::to_string(expectedCount) + ". Depth " + std::to_string(depth) + ". FEN: " + fen);
}
