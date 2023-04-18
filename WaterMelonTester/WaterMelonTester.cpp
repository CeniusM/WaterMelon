#include "Tests.hpp"

void RunTest(void(*TestFunc)(Assert&), std::string name)
{
	Assert a{};
	TestFunc(a);
	if (a.Succes)
		_SetPassedColor();
	else
		_SetErrorColor();
	std::cout << "---------- " << name << " ----------\n";
	//if (a.Succes)
		//std::cout << "Succes\n";
	//else
		//std::cout << "! Failed !\n";

	if (!a.Succes)
	{
		bool errorsLeft = true;
		while (errorsLeft)
		{
			std::string str = a.GetError();
			if (str == "End")
			{
				errorsLeft = false;
				break;
			}
			WriteLine(str);
		}
	}

	//std::cout << "^^^^^^^^^^ " << name << " ^^^^^^^^^^\n\n";
	std::cout << "\n";
	_ResetColor();

}

int main()
{
	std::cout << sizeof(UnsafeWaterMelon) << "\n";
	StartStabilityTest(10000);
	return 0;
	RunTest(&BoardStateStackTest, "BoardStateStackTest");
	RunTest(&CreateAndUssageOfMoveTest, "CreateAndUssageOfMoveTest");
	RunTest(&EvaluatorEarlyCheckmatesBetterTest, "EvaluatorEarlyCheckmatesBetterTest");
	RunTest(&EvaluatorMultiplyByLateGameMultiplierTest, "EvaluatorMultiplyByLateGameMultiplierTest");
	RunTest(&GetNextBitTest, "GetNextBitTest");
	RunTest(&PerftQuickTest, "PerftQuickTest");
	//RunTest(&PerftFullTest, "PerftFullTest");
	RunTest(&PieceMaterialCountingTest, "PieceMaterialCountingTest");
}