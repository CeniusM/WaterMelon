#pragma once

#include <iostream>
#include <string>

#define LoggerEnabled

#ifdef LoggerEnabled

class Logger
{
public:
	Logger();
	~Logger();

	static void LogBitboard(unsigned long long board);
	static void Log(char* message);
	static void Log(std::string str);
private:

};


//void Log(unsigned long long num)
//{
//	std::cout << num;
//}
//constexpr void Log(char* message)
//{
//	std::cout << message;
//}
//constexpr void LogLine(char* message)
//{
//	std::cout << message << '\n';
//}

#else

#define Log(a)
#define LogLine(a)

#endif