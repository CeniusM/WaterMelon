

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

BoardState BoardStateStack::Peek()
{
	return m_items[m_top - 1];
}

BoardState BoardStateStack::Pop()
{
	Check(m_top > 0, "BoardStateStack.Pop() at under 1");
	return m_items[--m_top];
}

int BoardStateStack::GetCount() const
{
	return m_top;
}

