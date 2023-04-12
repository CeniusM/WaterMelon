#include "Tests.hpp"

void EvaluatorEarlyCheckmatesBetterTest(Assert& assert)
{
	UnsafeWaterMelon* a = new UnsafeWaterMelon{};
	UnsafeWaterMelon* b = new UnsafeWaterMelon{};
	UnsafeWaterMelon* c = new UnsafeWaterMelon{};
	Move moves[MaxMovesCount];

	for (size_t i = 0; i < 3; i++)
	{
		int count = a->GetPossibleMoves(moves);
		a->MakeMove(moves[rand() % count]);
	}
	for (size_t i = 0; i < 2; i++)
	{
		int count = b->GetPossibleMoves(moves);
		b->MakeMove(moves[rand() % count]);
	}
	for (size_t i = 0; i < 1; i++)
	{
		int count = c->GetPossibleMoves(moves);
		c->MakeMove(moves[rand() % count]);
	}

	int aVal = GetFullBoardEval(*a, true);
	int bVal = GetFullBoardEval(*b, true);
	int cVal = GetFullBoardEval(*c, true);

	assert.AssertTrue(cVal > bVal, "Incorrect eval of draw");
	assert.AssertTrue(cVal > aVal, "Incorrect eval of draw");
	assert.AssertTrue(bVal > aVal, "Incorrect eval of draw");

	delete a;
	delete b;
	delete c;
}