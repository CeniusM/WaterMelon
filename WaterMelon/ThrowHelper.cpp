#include "ThrowHelper.h"

void ThrowNotImplementedException(std::string message)
{
	throw std::logic_error("__NotImplementedException__ " + message);
}

void ThrowInvalidArgumentException(std::string message)
{
	throw std::invalid_argument("__InvalidArgumentException__ " + message);
}

void ThrowOutOfRangeException(std::string message)
{
	throw std::out_of_range("__OutOfRangeException__ " + message);
}

