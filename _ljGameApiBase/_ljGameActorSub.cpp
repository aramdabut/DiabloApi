#include "_ljGameActorSub.h"
#include "_ljGameActor.h"




_ljGameActorSub::_ljGameActorSub()
	: mSubPos(_ljVector::ZERO)
	, mSubSize(_ljVector::ZERO)
	, mIsCam(true)
{
}

_ljGameActorSub::~_ljGameActorSub()
{
}

_ljVector _ljGameActorSub::GetPos() const
{
	return mActor->Pos() + mSubPos;
}

_ljVector _ljGameActorSub::CalPos()
{
	/* 오차를 생각한다. */
	if (true == mIsCam)
	{
		_ljVector Vec = mActor->Pos() + mSubPos - (mActor->Scene()->CamPos());
		Vec.X = floorf(Vec.X);
		Vec.Y = floorf(Vec.Y);
		return Vec;
	}
	else
	{
		mSubPos.X = floorf(mSubPos.X);
		mSubPos.Y = floorf(mSubPos.Y);
		return mSubPos;
	}

	_ljVector RVec = mActor->Pos() + mSubPos;

	RVec.X = floorf(RVec.X);
	RVec.Y = floorf(RVec.Y);

	return RVec;
}

MyRect _ljGameActorSub::CalRect()
{
	return { CalPos(), mSubSize };
}

bool _ljGameActorSub::IsUpdated()
{
	return mActor->IsUpdated() && _ljGameBaseUpdater::IsUpdated();
}

bool _ljGameActorSub::IsDead()
{
	return mActor->IsDead() || _ljGameBaseUpdater::IsDead();
}

void _ljGameActorSub::CamOnOff()
{
	mIsCam = !mIsCam;
}

//void _ljGameActorSub::CalIndex()
//{
//	_ljVector pos = CalPos();
//
//	mTileIndex.X = (int)roundf((pos.X / QUARTER_TILE_WIDTH + pos.Y / QUARTER_TILE_HEIGHT) / 2);
//	mTileIndex.Y = (int)roundf((pos.Y / QUARTER_TILE_HEIGHT + -(pos.X / QUARTER_TILE_WIDTH)) / 2);
//
//}
//
//void _ljGameActorSub::CalIndex(_ljVector newPos)
//{
//	_ljVector pos = newPos;
//
//	mTileIndex.X = (int)roundf((pos.X / QUARTER_TILE_WIDTH + pos.Y / QUARTER_TILE_HEIGHT) / 2);
//	mTileIndex.Y = (int)roundf((pos.Y / QUARTER_TILE_HEIGHT + -(pos.X / QUARTER_TILE_WIDTH)) / 2);
//
//}
//
