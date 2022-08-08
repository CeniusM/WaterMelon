#include <iostream>
#include <string>

#include "../WaterMelonEngine/SafeWaterMelon.h"
#include "../WaterMelonEngine/UnsafeWaterMelon.h"
#include "BoardAsString.h"

int main()
{
    UnsafeWaterMelon engine{};
    std::cout << BoardAsString::GetStringFromUnsafe(engine);
    std::cout << "Hello World!, im the ui\n";
}