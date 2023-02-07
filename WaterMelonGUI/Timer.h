#pragma once

#include <chrono>
#include <iostream>

using namespace std::chrono;

class Timer
{
	time_point<steady_clock> start, end;
	duration<float> duration;
public:

	Timer()
	{
		start = high_resolution_clock::now();
	}

	~Timer()
	{
		end = high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000;
		std::cout << "Timer took: " << ms << "ms" << std::endl;
	}
};
