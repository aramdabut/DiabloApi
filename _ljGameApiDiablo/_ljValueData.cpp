#include "_ljValueData.h"


bool OverCheck(_ljVector pos)
{
	if (pos.X < 0 || pos.X >= MAPCOUNT_X ||
		pos.Y < 0 || pos.Y >= MAPCOUNT_Y)
	{
		return true;
	}

	return false;
}


/* 
* min에서 max까지의 숫자가 나온다.

	int _ljGameRandomNum(int min, int max)
	{
		if (max <= 0)
		{
			max = 1;
		}
	
		srand(++seed);
	
		unsigned int random = rand() << 2;
		random += rand() >> 3;
		random = random * random * random;
		random = (random % max - min + 1) + min;
		return (int)random;
	}
*/

