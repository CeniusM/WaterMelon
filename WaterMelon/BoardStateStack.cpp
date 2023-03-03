

#include "BoardStateStack.h"

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

void BoardStateStack::Push(BoardState state)
{
	m_items[m_top++] = state;
	if (m_top == m_capacity)
	{
		free(m_items);
		m_capacity *= 2;
		m_items = (BoardState*)malloc(m_capacity * sizeof(BoardState));
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

