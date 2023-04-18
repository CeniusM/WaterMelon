#pragma once

#include <string>
#include <chrono>
#include <thread>

#include "UnsafeWaterMelon.hpp"

using namespace std::chrono;

/// <summary>
/// This does perft and does random moves on the UnsafeWaterMelon board, and keeps track of what have happend for when it fails
/// </summary>
void StartStabilityTest(unsigned long long TimeAllowsToTestms);

struct MoveName
{
public:
	Move move;
	char name[5];
	MoveName();
	MoveName(Move move);

	void SetMove(Move move);
	Move GetMove();
	std::string GetName();
};

class MoveStack
{
public:
	MoveStack();
	~MoveStack();

	void Push(Move move);
	MoveName Pop();
	MoveName GetAt(int index);

	int GetCount();
private:
	int _count = 0;
	int _capacity = 0;
	MoveName* moves;
};