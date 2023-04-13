#pragma once

#include <chrono>

#include "UnsafeWaterMelon.hpp"
#include "MoveMisc.hpp"

using namespace std::chrono;

class PerftRunner
{
public:
	PerftRunner();
	~PerftRunner();

	long BulkSearch(UnsafeWaterMelon* b, int depth);
	void BulkSearchLog(UnsafeWaterMelon* b, int depth);

	void PerftCountLog(UnsafeWaterMelon* b, int depth);
	long GetPerftCount(UnsafeWaterMelon* b, int depth);

private:
	bool m_running{ 0 };
	//UnsafeWaterMelon board;
	std::string FEN;

	UnsafeWaterMelon* board;

	long Perft(int depth);
	long PerftCount(int depth);
};