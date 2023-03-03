#include "Assert.h"

void _SetErrorColor()
{
	HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hnd, 12);
}

void _SetPassedColor()
{
	HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hnd, 10);
}

void _ResetColor()
{
	HANDLE hnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hnd, 15);
}

void Write(std::string message)
{
	std::cout << message;
}

void WriteLine(std::string message)
{
	std::cout << message << "\n";
}

void WriteErrorMessage(std::string message)
{
	_SetErrorColor();
	WriteLine(message);
	_ResetColor();
}

void WritePassedTest(std::string nameOfTest)
{
	_SetPassedColor();
	WriteLine(nameOfTest + " Passed");
	_ResetColor();
}

void AssertTrue(bool val, std::string message, bool* Succes)
{
	if (!val)
	{
		*Succes = false;
		WriteErrorMessage(message);
	}
}

void AssertFalse(bool val, std::string message, bool* Succes)
{
	AssertTrue(!val, message, Succes);
}

void AssertInclusiveInBounds(int val, int buttom, int top, std::string message, bool* Succes)
{
	AssertTrue(val >= buttom && val <= top, message, Succes);
}
