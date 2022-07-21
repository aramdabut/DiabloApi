#include "_ljFade.h"
#include <_ljGameTime.h>


_ljFade::_ljFade()
{
	Image(L"BackBuffer.bmp");
	SetRenderStyle(RS_ALPHA);
	SubSize({ 640.f * 1.3f , 640 * 1.3f });
	mBright = 0;
	mTimer = 0;
	SetBF(0);
	mTime = 3.f;
	mGap = 0.005f;
}


_ljFade::~_ljFade()
{
}

bool _ljFade::StartFadeOut()
{
	mGap -= _ljGameTime::DeltaTime();

	if (mGap <= 0)
	{
		mBright += 2;
		mTimer += 2;
		mGap = 0.005f;
	}

	if (mBright >= 200)
	{
		mBright = 255;
	}

	if (mTimer >= 255)
	{
		mBright = 0;
		mTimer = 0;
		SetBF(0);
		return true;
	}

	SetBF(mBright);

	return false;
}

