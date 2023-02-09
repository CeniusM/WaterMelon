#pragma once

#include <iostream>
#include <string>

#define LoggerEnabled DEBUG

#if LoggerEnabled

void Log(std::string str);
void LogLine(std::string str);

#else

#define Log(a)
#define LogLine(a)

#endif