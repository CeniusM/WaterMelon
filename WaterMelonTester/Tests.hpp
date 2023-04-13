#pragma once

#include "Assert.hpp"
#include "UnsafeWaterMelon.hpp"
#include "Evaluator.hpp"
#include "PerftUtil.hpp"

void PieceMaterialCountingTest(Assert& assert);
void CreateAndUssageOfMoveTest(Assert& assert);
void EvaluatorEarlyCheckmatesBetterTest(Assert& assert);
void EvaluatorMultiplyByLateGameMultiplierTest(Assert& assert);
void GetNextBitTest(Assert& assert);
void PerftQuickTest(Assert& assert);
void PerftFullTest(Assert& assert);
void BoardStateStackTest(Assert& assert);
