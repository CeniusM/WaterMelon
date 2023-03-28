#pragma once

#include <string>
#include <iostream>

//#define DoChecks

void DoCheck(bool succes, const char* message);



#ifdef DoChecks
#define Check(x, y) DoCheck(x, y);
#else
#define Check(x, y)
#endif