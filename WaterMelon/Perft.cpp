#include "Perft.hpp"

PerftRunner::PerftRunner()
{
}

PerftRunner::~PerftRunner()
{
}

void PerftRunner::BulkSearchLog(UnsafeWaterMelon* b, int depth)
{
	board = b;
	long Counts[MaxMovesCount]{};
	Move moves[MaxMovesCount]{};
	int movesCount = board->GetPossibleMoves(moves);

	steady_clock::time_point Times[MaxMovesCount][2]{}; // Start and stop time
	auto TotalStart = high_resolution_clock::now();

	for (size_t i = 0; i < movesCount; i++)
	{
		Times[i][0] = high_resolution_clock::now();

		board->MakeMove(moves[i]);
		Counts[i] += Perft(depth - 1);
		board->UnMakeMove();

		Times[i][1] = high_resolution_clock::now();
	}

	auto TotalStop = high_resolution_clock::now();
	auto TotalTime = duration_cast<milliseconds>(TotalStop - TotalStart);

	long totalMoves = 0;
	for (size_t i = 0; i < Counts[i]; i++)
		totalMoves += Counts[i];

	//std::cout << "BulkSearchLog at depth " << depth << "\n";
	//std::cout << "FEN: " << FEN << "\n";
	//std::cout << "Total run time: " << TotalTime.count() << "ms\n";
	//std::cout << "Total nodes: " << totalMoves << "\n";
	//std::cout << "\n";
	//for (size_t i = 0; i < movesCount; i++)
	//{
	//	std::cout <<
	//		"Move: " << GetMoveName(moves[i]) <<
	//		". Run Time: " << duration_cast<milliseconds>(Times[i][1] - Times[i][0]).count() <<
	//		"ms. Nodes: " << Counts[i] <<
	//		". KNs: " << (int)((Counts[i] / (float)duration_cast<microseconds>(Times[i][1] - Times[i][0]).count()) * 1000) <<
	//		"\n";
	//}

	for (size_t i = 0; i < movesCount; i++)
	{
		std::cout << GetMoveName(moves[i]) << ": " << Counts[i] << "\n";
	}
}

long PerftRunner::BulkSearch(UnsafeWaterMelon* b, int depth)
{
	board = b;
	return Perft(depth);
}

void PerftRunner::PerftCountLog(UnsafeWaterMelon* b, int depth)
{
	board = b;
	long Counts[MaxMovesCount]{};
	Move moves[MaxMovesCount]{};
	int movesCount = board->GetPossibleMoves(moves);

	for (size_t i = 0; i < movesCount; i++)
	{
		board->MakeMove(moves[i]);
		Counts[i] += PerftCount(depth - 1);
		board->UnMakeMove();
	}

	long totalMoves = 0;
	for (size_t i = 0; i < Counts[i]; i++)
		totalMoves += Counts[i];

	for (size_t i = 0; i < movesCount; i++)
	{
		std::cout << GetMoveName(moves[i]) << ": " << Counts[i] << "\n";
	}
}

long PerftRunner::GetPerftCount(UnsafeWaterMelon* b, int depth)
{
	board = b;
	return PerftCount(depth);
}

long PerftRunner::PerftCount(int depth)
{
	if (depth == 0)
		return 1;
	long Count = 0;
	Move moves[MaxMovesCount];
	int movesCount = board->GetPossibleMoves(moves);

	if (depth == 1)
		return movesCount;

	for (size_t i = 0; i < movesCount; i++)
	{
		board->MakeMove(moves[i]);
		Count += Perft(depth - 1);
		board->UnMakeMove();
	}

	return Count;
}

long PerftRunner::Perft(int depth)
{
	if (depth == 0)
		return 1;
	long Count = 0;
	Move moves[MaxMovesCount];
	int movesCount = board->GetPossibleMoves(moves);

	for (size_t i = 0; i < movesCount; i++)
	{
		board->MakeMove(moves[i]);
		Count += Perft(depth - 1);
		board->UnMakeMove();
	}

	return Count;
}
