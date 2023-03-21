#pragma once

#include "BoardState.hpp"
#include "Checker.hpp"

// Does not do bounds check, so if you pop or peek with less than 1 item, its on you ;), just use GetCount
class BoardStateStack
{
public:
	BoardStateStack(int Capacity);
	~BoardStateStack();

	inline void Push(BoardState state);
	BoardState Peek();
	BoardState Pop();

	int GetCount();

private:
	int m_capacity;
	int m_top;
	BoardState* m_items;
};

inline void BoardStateStack::Push(BoardState state)
{
	m_items[m_top++] = state;
	if (m_top == m_capacity)
	{
		BoardState* temp = 0;
		while (!temp)
			temp = (BoardState*)malloc(m_capacity * 2 * sizeof(BoardState));
		memcpy(temp, m_items, m_capacity * sizeof(BoardState));
		free(m_items);
		m_items = temp;
		m_capacity *= 2;
	}
}