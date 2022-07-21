#include "_ljGameRandomNum.h"
#include <time.h>
#include <Windows.h>


int _ljGameRandomNum::mSeed = 0;
int _ljGameRandomNum::mTimeSeed = 0;

void _ljGameRandomNum::Init()
{
	srand((unsigned int)time(nullptr));
}

unsigned int _ljGameRandomNum::SeedRandomUInt()
{
	int randomNumber = 0;

	for (int i = 0; i < 32; i++)
	{
		randomNumber = randomNumber << 1;

		srand(mSeed++);
		int temp = rand() % 2;

		randomNumber = randomNumber | temp;
	}

	return randomNumber;
}

unsigned int _ljGameRandomNum::TimeRandomUInt()
{
	int randomNumber = 0;

	for (int i = 0; i < 32; i++)
	{
		randomNumber = randomNumber << 1;

		int temp = rand() % 2;

		randomNumber = randomNumber | temp;
	}

	return randomNumber;
}

void _ljGameRandomNum::SetSeed(unsigned int seed)
{
	mSeed = seed;
}

int _ljGameRandomNum::GetRandomNumber(int min, int max)
{
	if (max <= 0)
	{
		max = 1;
	}

	srand(++mSeed);

	unsigned int random = SeedRandomUInt();

	random = random % max + min;

	return (int)random;
}
