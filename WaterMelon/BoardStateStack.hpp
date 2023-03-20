#pragma once

#include "BoardState.hpp"
#include "Checker.hpp"

// Does not do bounds check, so if you pop or peek with less than 1 item, its on you ;), just use GetCount
class BoardStateStack
{
public:
	BoardStateStack(int Capacity);
	~BoardStateStack();

	void Push(const BoardState& state);
	BoardState Peek();
	BoardState Pop();

	int GetCount();

private:
	int m_capacity;
	int m_top;
	BoardState* m_items;
};