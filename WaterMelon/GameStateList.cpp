

#include "GameStateList.h"

GaneStateList::GaneStateList(int startingBytes)
{
	m_maxCount = startingBytes / sizeof(GameState);
	m_items = new GameState[m_maxCount];
	m_currentCount = 0;
}

GaneStateList::~GaneStateList()
{
}

void GaneStateList::Push(GameState state)
{
}

GameState GaneStateList::Peek()
{
	return GameState();
}

GameState GaneStateList::Pop()
{
	return GameState();
}

int GaneStateList::GetCount()
{
	return 0;
}

