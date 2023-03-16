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

void AssertTrue(bool val, std::string message, bool* Succes);
void AssertFalse(bool val, std::string message, bool* Succes);
void AssertInclusiveInBounds(int val, int buttom, int top, std::string message, bool* Succes);
