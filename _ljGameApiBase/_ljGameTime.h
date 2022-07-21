#pragma once
#include <windows.h>


class _ljGameTime
{
private:
	_ljGameTime();
	~_ljGameTime();

private:
	class CTimer
	{
	public:
		friend _ljGameTime;

	public:
		float Update();
		void Reset();

	private:
		CTimer();
		~CTimer();

	private:
		LARGE_INTEGER mCPUCount;
		LARGE_INTEGER mTotalCPUCount;
		LARGE_INTEGER mPrevCPUCount;
		double mDoubleDeltaTime;
		float mFloatDeltaTime;
		int mFPS;
		int mNewFPS;
		int mTime;
	};

private:
	static CTimer mMainTimer;

public:
	static float Update()
	{
		return mMainTimer.Update();
	}

	static float DeltaTime()
	{
		return mMainTimer.mFloatDeltaTime;
	}

	static int FPS()
	{
		return mMainTimer.mNewFPS;
	}


};

