#pragma once

/* 
	1. ������ �ϰ� �ʹ� > SeedRandomUInt()�� ���� �����Ѵ�. 
	2. OR �����õ�
	3. �õ带 ���� �Է��ϰ� ������ SetSeed()�� ���� 
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