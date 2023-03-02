

#include "BoardStateStack.h"

BoardStateStack::BoardStateStack(int count)
{
	m_capacity = count;
	m_items = new BoardState[m_capacity];
	m_top = 0;
}

BoardStateStack::~BoardStateStack()
{
	delete m_items;
}

void BoardStateStack::Push(BoardState state)
{
	m_items[m_top++] = state;
	if (m_top == m_capacity)
	{
		delete m_items;
		m_capacity *= 2;
		m_items = new BoardState[m_capacity];
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

