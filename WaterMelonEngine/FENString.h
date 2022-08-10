#pragma once
#include <string>

// for later

class FENString
{
public:
	FENString(const char* str);
	FENString(std::string str);
	~FENString();


private:
	bool IsValidString{};
	
	int EPSquare{};
	int Castle{};
	int playerTurn{};
};

inline FENString::FENString(const char* str)
{
}

inline FENString::FENString(std::string str)
{
}

FENString::~FENString()
{
}