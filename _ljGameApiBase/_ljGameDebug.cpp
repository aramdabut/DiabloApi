#include "_ljGameDebug.h"


void _ljGameDebug::LeakCheckSetting()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

_ljGameDebug::_ljGameDebug() {}
_ljGameDebug::~_ljGameDebug() {}