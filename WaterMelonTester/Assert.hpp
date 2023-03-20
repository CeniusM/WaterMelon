#pragma once

#include <iostream>
#include <Windows.h>
#include <string>

void _SetErrorColor();
void _SetPassedColor();
void _ResetColor();

void Write(std::string message);
void WriteLine(std::string message);

void WriteErrorMessage(std::string message);
void WritePassedTest(std::string nameOfTest);

class Assert
{
public:
	const int MaxErrors = 10;

	Assert();
	~Assert();

	void AssertTrue(bool val, std::string message);
	void AssertFalse(bool val, std::string message);
	void AssertInclusiveInBounds(int val, int buttom, int top, std::string message);

	// Returns "End" if non left
	std::string GetError();

	bool Succes = true;
private:
	std::string* errors;
	int top;
};