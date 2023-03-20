#include "Tests.hpp"

void CreateAndUssageOfMoveTest(Assert& assert)
{
	Square start = 14;
	Square target = 4;
	MoveFlag flag = PromoteToKnightCapture;

	Move move = CreateMove(start, target, flag);

	assert.AssertTrue(GetMoveStart(move) == start, "Start move did not match start move after create and get");
	assert.AssertTrue(GetMoveTarget(move) == target, "Target move did not match target move after create and get");

	assert.AssertFalse(GetMoveFlag(move) == PromoteToKnightCapture, "The MoveFlag returned the whole flag with the CapturedBit");

	assert.AssertTrue(IsMoveCapture(move), "The IsMoveCatpure failed on giving back that the move was a capture");
	assert.AssertTrue(IsMovePromotion(move), "The IsMovePromotion failed on giving back that the move was a promotion");

	assert.AssertFalse(IsMovePromotion(MoveFlags::Castling), "IsMovePromotion failed");
	assert.AssertFalse(IsMovePromotion(MoveFlags::NoFlagCapture), "IsMovePromotion failed");
	assert.AssertFalse(IsMovePromotion(MoveFlags::PawnDoubleForward), "IsMovePromotion failed");
	assert.AssertFalse(IsMovePromotion(MoveFlags::EnPassantCapture), "IsMovePromotion failed");

	assert.AssertTrue(IsMovePromotion(MoveFlags::PromoteToQueen), "IsMovePromotion failed (PromoteToQueen)");
	assert.AssertTrue(IsMovePromotion(MoveFlags::PromoteToBishopCapture), "IsMovePromotion failed (PromoteToBishopCapture)");
	assert.AssertTrue(IsMovePromotion(MoveFlags::PromoteToRook), "IsMovePromotion failed (PromoteToRook)");
	assert.AssertTrue(IsMovePromotion(MoveFlags::PromoteToKnightCapture), "IsMovePromotion failed (PromoteToKnightCapture)");


}