#pragma once

#include "GameState.h"

class GaneStateList
{
public:
	GaneStateList(int startingBytes);
	~GaneStateList();

	void Push(GameState state);
	GameState Peek();
	GameState Pop();

	int GetCount();

private:
	int m_maxCount;
	int m_currentCount;
	GameState* m_items;


};