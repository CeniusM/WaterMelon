#include "Memcompare.hpp"

bool* MemCopare(int size, void* obj1, void* obj2)
{
	bool* result = nullptr;
	while (!result)
		result = (bool*)malloc(size);
	char* ptr1 = (char*)obj1;
	char* ptr2 = (char*)obj2;
	for (size_t i = 0; i < size; i++)
	{
		if (ptr1[i] == ptr2[i])
			result[i] = true;
		else
			result[i] = false;
	}
	return result;
}