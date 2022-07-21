#include "_ljMapTester.h"
#include <_ljGameInput.h>
#include "_ljRandomMap.h"


_ljMapTester::_ljMapTester() : mMapIndex(0)
{
}

_ljMapTester::~_ljMapTester()
{
	// mAllMap.clear(); 
}

void _ljMapTester::Update()
{
	if (_ljGameInput::Down(L"MakeARoom"))
	{
		++mMapIndex;
	}

	if (true == mAllMap.empty())
	{
		return;
	}

	mAllMap[mMapIndex].Update();
}

void _ljMapTester::DebugRender()
{
}

void _ljMapTester::SetRandomMap(_ljRandomMap* map)
{
	mRandomMap = map;
}

void _ljMapTester::MakeAMap()
{

}