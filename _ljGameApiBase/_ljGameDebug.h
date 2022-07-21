#pragma once
#include <crtdbg.h>

class _ljGameDebug
{
public:
	static void LeakCheckSetting();

private:
	_ljGameDebug();
	~_ljGameDebug();
};

