

#include "BoardStateStack.hpp"

BoardStateStack::BoardStateStack(int Capacity)
{
	m_capacity = Capacity;
	m_items = (BoardState*)malloc(m_capacity * sizeof(BoardState));
	m_top = 0;
}

BoardStateStack::~BoardStateStack()
{
	free(m_items);
}

void BoardStateStack::Push(const BoardState& state)
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

BoardState BoardStateStack::Peek()
{
	return m_items[m_top - 1];
}

BoardState BoardStateStack::Pop()
{
	return m_items[--m_top];
}

int BoardStateStack::GetCount()
{
	return m_top;
}

