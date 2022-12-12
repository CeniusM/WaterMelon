#pragma once

#include <chrono>
#include <iostream>

class Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
public:

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000;
		std::cout << "Timer took: " << ms << "ms" << std::endl;
	}
};
