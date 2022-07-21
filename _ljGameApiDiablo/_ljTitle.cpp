#include "_ljTitle.h"
#include <_ljGameRenderer.h>
#include <_ljGameAniRenderer.h>
#include <_ljGameWin.h>
#include <_ljGameInput.h>
#include "_ljDemoDiablo.h"
#include "_ljCursor.h"
#include "_ljFade.h"

_ljTitle::_ljTitle()
{
}


_ljTitle::~_ljTitle()
{
}

void _ljTitle::Loading()
{
	mMouse = new _ljCursor();

	mStartX = 140;
	mStartY = 190;

	mMain = new _ljGameActor();
	mMain->Pos({ 640 / 2.f, 480 / 2.f });
	mMainRenderer = mMain->CreateRenderer<_ljGameRenderer>(LO_BBG);
	mMainRenderer->Image(L"Select.bmp");
	mMainRenderer->SubPos({ 0 , 0 });
	mMainRenderer->SubSize({ 640 , 480 });
	mMainRenderer->SetRenderStyle(RS_BIT);

	mFire = mMain->CreateAniRenderer(LO_BG);
	mFire->SubPos({ 0 , -160 });
	mFire->SubSize({ 390 , 154 });
	mFire->CreateAnimation(L"Fire", L"SmallFire.bmp", 0, 14, true);
	mFire->TransColor(255, 255, 255);

	mStar1 = mMain->CreateAniRenderer(LO_BG);
	mStar1->SubPos({ -200 , -25 });
	mStar1->SubSize({ 49 , 48 });
	mStar1->CreateAnimation(L"Star1", L"Pentagram.bmp", 0, 8, true);
	mStar1->TransColor(255, 255, 255);

	mStar2 = mMain->CreateAniRenderer(LO_BG);
	mStar2->SubPos({ 200 , -25 });
	mStar2->SubSize({ 49 , 48 });
	mStar2->CreateAnimation(L"Star2", L"Pentagram.bmp", 0, 8, true);
	mStar2->TransColor(255, 255, 255);

	mFade = mMouse->CreateRenderer<_ljFade>(LO_DEBUG);
}

void _ljTitle::SceneUpdate()
{
	if (true == mIsNext)
	{
		mIsFade = mFade->StartFadeOut();

		if (mIsFade == true)
		{
			mIsFade = false;
			SetCurScene(L"TestScene");
		}
	}


	mMousePos = _ljGameWin::MainWindow()->MousePos();

	// SINGLE PLAYER
	if (mMousePos.IntX() >= mStartX && mMousePos.IntX() < mStartX + mGapX && 
		mMousePos.IntY() >= mStartY && mMousePos.IntY() < mStartY + mGapY)
	{
		if (false == mMoveOn1)
		{
			SSmove = _ljGameSound::SoundPlay(L"titlemov.wav");
			mStar1->SubPos({ -200 , -25 });
			mStar2->SubPos({ 200 , -25 });
			mStar1->On();
			mStar2->On();
			mMoveOn1 = true;
			mMoveOn2 = false;
			mMoveOn3 = false;
			mMoveOn4 = false;
			mMoveOn5 = false;
			return;
		}
		else
		{
			if (true == _ljGameInput::Down(L"LMOUSEBTN"))
			{
				if (true == mSelectOn)
				{
					SSselect->Stop();
					mSelectOn = false;
				}

				SSselect = _ljGameSound::SoundPlay(L"titlslct.wav");
				mSelectOn = true;

				mOpening->GetSound()->Stop();

				mIsNext = true;
			}
		}
	}

	// MULTI PLAYER
	else if (mMousePos.IntX() >= mStartX && mMousePos.IntX() < mStartX + mGapX && 
			mMousePos.IntY() >= mStartY + mGapY && mMousePos.IntY() < mStartY + mGapY * 2)
	{
		if (false == mMoveOn2)
		{
			SSmove = _ljGameSound::SoundPlay(L"titlemov.wav");
			mStar1->SubPos({ -200, 24 });
			mStar2->SubPos({ 200, 24 });
			mStar1->On();
			mStar2->On();
			mMoveOn1 = false;
			mMoveOn2 = true;
			mMoveOn3 = false;
			mMoveOn4 = false;
			mMoveOn5 = false;
			return;
		}
	}

	// REPLAY
	else if (mMousePos.IntX() >= mStartX && mMousePos.IntX() < mStartX + mGapX &&
			mMousePos.IntY() >= mStartY + mGapY * 2 && mMousePos.IntY() < mStartY + mGapY * 3)
	{
		if (false == mMoveOn3)
		{
			SSmove = _ljGameSound::SoundPlay(L"titlemov.wav");
			mStar1->SubPos({ -200, 24 + mStartGap });
			mStar2->SubPos({ 200, 24 + mStartGap });
			mStar1->On();
			mStar2->On();
			mMoveOn1 = false;
			mMoveOn2 = false;
			mMoveOn3 = true;
			mMoveOn4 = false;
			mMoveOn5 = false;

			return;
		}
	}

	// CREDIT
	else if (mMousePos.IntX() >= mStartX && mMousePos.IntX() < mStartX + mGapX && 
			mMousePos.IntY() >= mStartY + mGapY * 3 && mMousePos.IntY() < mStartY + mGapY * 4)
	{
		if (false == mMoveOn4)
		{
			SSmove = _ljGameSound::SoundPlay(L"titlemov.wav");
			mStar1->SubPos({ -200, 24 + mStartGap * 2 });
			mStar2->SubPos({ 200, 24 + mStartGap * 2 });
			mStar1->On();
			mStar2->On();
			mMoveOn1 = false;
			mMoveOn2 = false;
			mMoveOn3 = false;
			mMoveOn4 = true;
			mMoveOn5 = false;

			return;
		}
	}

	// EXIT
	else if (mMousePos.IntX() >= mStartX && mMousePos.IntX() < mStartX + mGapX &&
			mMousePos.IntY() >= mStartY + mGapY * 4 && mMousePos.IntY() < mStartY + mGapY * 5)
	{
		if (false == mMoveOn5)
		{
			SSmove = _ljGameSound::SoundPlay(L"titlemov.wav");
			mStar1->SubPos({ -200, 24 + mStartGap * 3 });
			mStar2->SubPos({ 200, 24 + mStartGap * 3 });
			mStar1->On();
			mStar2->On();
			mMoveOn1 = false;
			mMoveOn2 = false;
			mMoveOn3 = false;
			mMoveOn4 = false;
			mMoveOn5 = true;

			return;
		}
	}

	if (true == _ljGameInput::Down(L"LMOUSEBTN"))
	{
		if (true == mSelectOn)
		{
			SSselect->Stop();
			mSelectOn = false;
		}

		SSselect = _ljGameSound::SoundPlay(L"titlslct.wav");
		mSelectOn = true;
	}

}

void _ljTitle::Init()
{
	mFire->SetCurrentAnimation(L"Fire");
	mStar1->SetCurrentAnimation(L"Star1");
	mStar2->SetCurrentAnimation(L"Star2");

	mStar1->Off();
	mStar2->Off();

}
