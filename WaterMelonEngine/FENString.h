#pragma once
#include <string>

// for later, used for loading and saving boards both has varibles and a fen

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