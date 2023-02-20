#include "Logger.h"

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Log(unsigned long long board)
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			int num = (board >> (i * 8 + j) & 0b1);
			std::cout << num;
			//std::cout << (num >> 63);
		}
		std::cout << "\n";
	}
}

void Logger::Log(char* message)
{
	std::cout << message;
}