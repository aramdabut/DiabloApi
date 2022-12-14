#include "_ljGameTime.h"
#include <Windows.h>
#include <time.h>
#include <iostream>



_ljGameTime::CTimer		_ljGameTime::mMainTimer;

_ljGameTime::_ljGameTime()	{}
_ljGameTime::~_ljGameTime() {}

_ljGameTime::CTimer::CTimer()
{
	Reset();
}

_ljGameTime::CTimer::~CTimer()
{
}


float _ljGameTime::CTimer::Update()
{
	QueryPerformanceCounter(&mTotalCPUCount);

	mDoubleDeltaTime = ((double)(mTotalCPUCount.QuadPart - mPrevCPUCount.QuadPart)) / ((double)mCPUCount.QuadPart);
	mFloatDeltaTime = (float)mDoubleDeltaTime;

	mPrevCPUCount = mTotalCPUCount;

	if (mTime != time(nullptr))
	{
		//	시간을 Output에 띄우기
		//	wchar_t Arr[200] = {0,};
		//	swprintf_s(Arr, L"FPS : %d\n", mFPS);
		//	OutputDebugStringW(Arr);
		//	FPS 초기화

		mNewFPS = mFPS;
		mFPS = 0;
	}

	++mFPS;
	mTime = (int)time(nullptr);

	return mFloatDeltaTime;
}

void _ljGameTime::CTimer::Reset()
{
	QueryPerformanceFrequency(&mCPUCount);
	QueryPerformanceCounter(&mTotalCPUCount);
	QueryPerformanceCounter(&mPrevCPUCount);

	mFPS = 0;
	mTime = (int)time(nullptr);
}

