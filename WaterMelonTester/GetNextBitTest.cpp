#include "Tests.hpp"

void GetNextBitTest(Assert& assert)
{
	std::string error = "Distance to bit did not show the right distance";
	Bitboard b = 0b1000ULL;
	assert.AssertTrue(GetNextBit(b) == 3, error + ", expected: " + std::to_string(3) + ", and got: " + std::to_string(GetNextBit(b)));
	b = 0b1000000ULL;
	assert.AssertTrue(GetNextBit(b) == 6, error + ", expected: " + std::to_string(6) + ", and got: " + std::to_string(GetNextBit(b)));
	b = 0b10ULL;
	assert.AssertTrue(GetNextBit(b) == 1, error + ", expected: " + std::to_string(1) + ", and got: " + std::to_string(GetNextBit(b)));
	b = 0b1000000000ULL;
	assert.AssertTrue(GetNextBit(b) == 9, error + ", expected: " + std::to_string(9) + ", and got: " + std::to_string(GetNextBit(b)));
	b = 0b1ULL;
	assert.AssertTrue(GetNextBit(b) == 0, error + ", expected: " + std::to_string(0) + ", and got: " + std::to_string(GetNextBit(b)));
	b = 0b100ULL;
	assert.AssertTrue(GetNextBit(b) == 2, error + ", expected: " + std::to_string(2) + ", and got: " + std::to_string(GetNextBit(b)));
	b = 0b1000000000000000000000000000000ULL;
	assert.AssertTrue(GetNextBit(b) == 30, error + ", expected: " + std::to_string(30) + ", and got: " + std::to_string(GetNextBit(b)));
}