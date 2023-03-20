#include "Assert.hpp"

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

void Assert::AssertTrue(bool val, std::string message)
{
	if (!val)
	{
		Succes = false;
		if (top < MaxErrors)
			errors[top++] = message;
	}
}

void Assert::AssertFalse(bool val, std::string message)
{
	AssertTrue(!val, message);
}

void Assert::AssertInclusiveInBounds(int val, int buttom, int top, std::string message)
{
	AssertTrue(val >= buttom && val <= top, message);
}

std::string Assert::GetError()
{
	if (top == 0)
		return std::string("End");
	return errors[--top];
}

Assert::Assert()
{
	errors = new std::string[MaxErrors];
	top = 0;
}

Assert::~Assert()
{
	delete[] errors;
}
