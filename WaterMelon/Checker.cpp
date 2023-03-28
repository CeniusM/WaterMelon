#include "Checker.hpp"

void DoCheck(bool succes, const char* message)
{
	if (!succes)
		std::cout << message << "\n";
}
