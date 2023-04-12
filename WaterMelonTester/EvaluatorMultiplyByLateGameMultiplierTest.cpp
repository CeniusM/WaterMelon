#include "Tests.hpp"

void EvaluatorMultiplyByLateGameMultiplierTest(Assert& assert)
{
	{
		int value = 123;
		int lateGameMultiplier = 1024;
		int expectedValue = 123;
		assert.AssertTrue(MultiplyByLateGameMultiplier(value, lateGameMultiplier) == expectedValue, "Did not get expected value of " + std::to_string(expectedValue) + ". Got " + std::to_string(MultiplyByLateGameMultiplier(value, lateGameMultiplier)));
	}
	{
		int value = 512;
		int lateGameMultiplier = 512;
		int expectedValue = 256;
		assert.AssertTrue(MultiplyByLateGameMultiplier(value, lateGameMultiplier) == expectedValue, "Did not get expected value of " + std::to_string(expectedValue) + ". Got " + std::to_string(MultiplyByLateGameMultiplier(value, lateGameMultiplier)));
	}
	{
		int value = -123;
		int lateGameMultiplier = 1024;
		int expectedValue = -123;
		assert.AssertTrue(MultiplyByLateGameMultiplier(value, lateGameMultiplier) == expectedValue, "Did not get expected value of " + std::to_string(expectedValue) + ". Got " + std::to_string(MultiplyByLateGameMultiplier(value, lateGameMultiplier)));
	}
	{
		int value = -400;
		int lateGameMultiplier = 256;
		int expectedValue = -100;
		assert.AssertTrue(MultiplyByLateGameMultiplier(value, lateGameMultiplier) == expectedValue, "Did not get expected value of " + std::to_string(expectedValue) + ". Got " + std::to_string(MultiplyByLateGameMultiplier(value, lateGameMultiplier)));
	}

}