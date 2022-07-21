#pragma once

/* 
	1. 랜덤을 하고 싶다 > SeedRandomUInt()을 먼저 선언한다. 
	2. OR 고정시드
	3. 시드를 직접 입력하고 싶으면 SetSeed()를 선언 
*/


class _ljGameRandomNum
{
private:
	_ljGameRandomNum() {}
	~_ljGameRandomNum() {}

private:
	static int mSeed;
	static int mTimeSeed;

public:
	static void Init();
	static unsigned int SeedRandomUInt();
	static unsigned int TimeRandomUInt();
	static void SetSeed(unsigned int seed);
	static int GetRandomNumber(int min, int max);


};