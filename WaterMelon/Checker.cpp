#include "Checker.hpp"

void Check(bool succes, const char* message)
{
#ifdef  DoChecks
	if (!succes)
		std::cout << message << "\n";
#endif
}
