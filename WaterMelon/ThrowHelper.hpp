#pragma once

#include <exception>
#include <stdexcept>
#include <string>

void ThrowNotImplementedException(std::string message);
void ThrowInvalidArgumentException(std::string message);
void ThrowOutOfRangeException(std::string message);
void ThrowException(std::string message);
