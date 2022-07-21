#include "_ljGameAniRenderer.h"
#include "_ljGameTextureMgr.h"
#include "_ljGameTime.h"
#include "_ljGameImage.h"




_ljGameAniRenderer::_ljGameAniRenderer()
	: mCurrentAnimation(nullptr)
	, mIsAlpha(false)
{
}

_ljGameAniRenderer::~_ljGameAniRenderer()
{
	std::map<std::wstring, CGameAni*>::iterator iter = mAnimationMap.begin();
	std::map<std::wstring, CGameAni*>::iterator endIter = mAnimationMap.end();

	for (; iter != endIter; ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
}


_ljGameAniRenderer::CGameAni* _ljGameAniRenderer::FindAnimation(const wchar_t* name)
{
	mFindIter = mAnimationMap.find(name);

	if (mAnimationMap.end() == mFindIter)
	{
		return nullptr;
	}

	return mFindIter->second;
}


bool _ljGameAniRenderer::CreateAnimation(const wchar_t* name, const wchar_t* imageName, unsigned int start, unsigned int end, bool loop, float frameTimeGap /*= 0.1f*/)
{
	CGameAni* ani = FindAnimation(name);

	// 있으면 안된다. 
	if (nullptr != ani)
	{
		BOOM;

		return false;
	}

	_ljGameImage* image = _ljGameTextureMgr::Inst().FindImage(imageName);

	if (nullptr == image)
	{
		BOOM;

		return false;
	}

	ani = new CGameAni();
	ani->mImage = image;
	ani->mIsLoop = loop;

	ani->mStartFrame = start;
	ani->mEndFrame = end;
	ani->mFrameTimeGap = frameTimeGap;

	mAnimationMap.insert(std::map<std::wstring, CGameAni*>::value_type(name, ani));

	return true;
}

bool _ljGameAniRenderer::SetCurrentAnimation(const wchar_t* name)
{
	mCurrentAnimation = FindAnimation(name);

	if (nullptr == mCurrentAnimation)
	{
		BOOM;
		return false;
	}

	mImage = mCurrentAnimation->mImage;
	mCurrentAnimation->mIsEnd = false;
	mCurrentAnimation->mCurFrame = mCurrentAnimation->mStartFrame;
	mCurrentAnimation->mCurFrameTime = mCurrentAnimation->mFrameTimeGap;

	return true;
}



void _ljGameAniRenderer::Render()
{
	if (nullptr == mActor)
	{
		BOOM;
	}

	MyRect rc = CalRect();

	mRect = mImage->GetRect(mCurrentAnimation->mCurFrame);

	mCurrentAnimation->mCurFrameTime -= _ljGameTime::DeltaTime();

	if (0.0f >= mCurrentAnimation->mCurFrameTime)
	{
		++mCurrentAnimation->mCurFrame;
		mCurrentAnimation->mCurFrameTime = mCurrentAnimation->mFrameTimeGap;

		if (mCurrentAnimation->mCurFrame > (int)mCurrentAnimation->mEndFrame)
		{
			mCurrentAnimation->mIsEnd = true;

			if (true == mCurrentAnimation->mIsLoop)
			{
				mCurrentAnimation->mCurFrame = mCurrentAnimation->mStartFrame;
			}
			else
			{
				mCurrentAnimation->mCurFrame = mCurrentAnimation->mEndFrame;
			}
		}
	}

	if (true == mIsAlpha)
	{
		AlphaBlend(_ljGameTextureMgr::BackDC()
			, rc.IntLeft()
			, rc.IntTop()
			, rc.Size.IntX()
			, rc.Size.IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()		// 이미지의 x에서부터
			, mRect.Pos.IntY()		// 이미지의 y에서부터
			, mRect.Size.IntX()		// 여기까지의 x 픽셀
			, mRect.Size.IntY()
			, GetBF()
		);
	}
	else
	{
		TransparentBlt(_ljGameTextureMgr::BackDC()
			, rc.IntLeft()
			, rc.IntTop()
			, rc.Size.IntX()
			, rc.Size.IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()
			, mRect.Pos.IntY()
			, mRect.Size.IntX()
			, mRect.Size.IntY()
			, mTransColor);
	}


}


std::wstring _ljGameAniRenderer::CurImageName()
{
	return mCurrentAnimation->mImage->Texture()->Name();
}