#pragma once

#include "Tests.hpp"

unsigned long long PerftCount(UnsafeWaterMelon& board, int depth);

unsigned long long TestPerftPos(std::string fen, int depth);

void TestPos(Assert& assert, std::string fen, int depth, int expectedCount);