#pragma once

#include "UnsafeWaterMelon.hpp"
#include <chrono>
using namespace std::chrono;


class PerftRunner
{
public:
	PerftRunner(std::string FEN);
	~PerftRunner();

	//void InitFEN(std::string FEN);

	long BulkSearch(int depth);
	void BulkSearchLog(int depth);

	UnsafeWaterMelon board{};
private:
	bool m_running{ 0 };
	//UnsafeWaterMelon board;
	std::string FEN;

	long Perft(int depth);
};

PerftRunner::PerftRunner(std::string FEN)
{
	this->FEN = FEN;
	//UnsafeWaterMelon temp{ FEN };
	//memcpy_s(&board, sizeof(UnsafeWaterMelon), &temp, sizeof(UnsafeWaterMelon));
}

PerftRunner::~PerftRunner()
{
}

void PerftRunner::BulkSearchLog(int depth)
{
	long Counts[MaxMovesCount]{};
	Move moves[MaxMovesCount]{};
	int movesCount = board.GetPossibleMoves(moves);

	steady_clock::time_point Times[MaxMovesCount][2]{}; // Start and stop time
	auto TotalStart = high_resolution_clock::now();

	for (size_t i = 0; i < movesCount; i++)
	{
		Times[i][0] = high_resolution_clock::now();

		board.MakeMove(moves[i]);
		Counts[i] += Perft(depth - 1);
		board.UnMakeMove();

		Times[i][1] = high_resolution_clock::now();
	}

	auto TotalStop = high_resolution_clock::now();
	auto TotalTime = duration_cast<milliseconds>(TotalStop - TotalStart);

	std::cout << "BulkSearchLog at depth " << depth << "\n";
	std::cout << "FEN: " << FEN << "\n";
	std::cout << "Total run time: " << TotalTime.count() << "ms\n";
	std::cout << "\n";
	for (size_t i = 0; i < movesCount; i++)
	{
		std::cout <<
			//"Move: " << GetMoveName(moves[i]) <<
			"Move: " << GetMoveStart(moves[i]) << " to " << GetMoveTarget(moves[i]) <<
			". Run Time: " << duration_cast<milliseconds>(Times[i][1] - Times[i][0]).count() <<
			"ms. Nodes: " << Counts[i] <<
			". KNs: " << (Counts[i] / duration_cast<milliseconds>(Times[i][1] - Times[i][0]).count()) <<
			"\n";
	}

}

long PerftRunner::BulkSearch(int depth)
{
	return Perft(depth);
}

long PerftRunner::Perft(int depth)
{
	if (depth == 0)
		return 1;
	long Count = 0;
	Move moves[MaxMovesCount];
	int movesCount = board.GetPossibleMoves(moves);

	for (size_t i = 0; i < movesCount; i++)
	{
		board.MakeMove(moves[i]);
		Count += Perft(depth - 1);
		board.UnMakeMove();
	}

	return Count;
}
