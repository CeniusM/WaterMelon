#include "ThrowHelper.h"

void ThrowNotImplementedException(std::string message)
{
	throw std::logic_error("__NotImplementedException__ " + message);
}

void ThrowInvalidArgumentException(std::string message)
{
	throw std::logic_error("__InvalidArgumentException__ " + message);
}

