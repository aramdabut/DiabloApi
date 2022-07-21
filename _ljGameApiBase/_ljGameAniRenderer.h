#pragma once
#include "_ljGameRenderer.h"
#include <map>




class _ljGameAniRenderer : public _ljGameRenderer
{
	class CGameAni
	{
	public:
		_ljGameImage* mImage;

		unsigned int mStartFrame;
		unsigned int mEndFrame;
		float mFrameTimeGap; // ( = m_fFrameTime)
		float mCurFrameTime;
		int mCurFrame;

		bool mIsLoop;
		bool mIsEnd;
	};

public:
	_ljGameAniRenderer();
	~_ljGameAniRenderer();

private:
	std::map<std::wstring, CGameAni*>::iterator mFindIter;
	std::map<std::wstring, CGameAni*>::iterator mAniIter;
	std::map<std::wstring, CGameAni*> mAnimationMap;
	CGameAni* mCurrentAnimation;

private:
	bool mIsAlpha;

public:
	bool CreateAnimation(const wchar_t* name, const wchar_t* imageName, unsigned int start, unsigned int end, bool loop, float frameTimeGap = 0.1f);
	bool SetCurrentAnimation(const wchar_t* name);

	bool IsCurrentAnimationEnd()
	{
		return mCurrentAnimation->mIsEnd;
	}

	std::wstring CurImageName();
	int CurFrame() { return mCurrentAnimation->mCurFrame; }
	void CurFrame(int frame) { mCurrentAnimation->mCurFrame = frame; }

	void FinishAnimation() { mCurrentAnimation->mCurFrame = mCurrentAnimation->mEndFrame; }
	void SetAlpha() { mIsAlpha = true; }

private:
	CGameAni* FindAnimation(const wchar_t* name);
	void Render();

};

