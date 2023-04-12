#pragma once

#include <chrono>

#include "UnsafeWaterMelon.hpp"
#include "MoveMisc.hpp"

using namespace std::chrono;

class PerftRunner
{
public:
	PerftRunner(std::string FEN);
	~PerftRunner();

	//void InitFEN(std::string FEN);

	long BulkSearch(int depth);
	void BulkSearchLog(int depth);

	UnsafeWaterMelon* board;
private:
	bool m_running{ 0 };
	//UnsafeWaterMelon board;
	std::string FEN;

	long Perft(int depth);
};