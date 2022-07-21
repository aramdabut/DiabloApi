#pragma once
#include "_ljValueData.h"


class Map;
class _ljMonster;
class _ljStageMgr
{
public:
	// static Map* GetCurrentMap() { return mAllMap[currentIndex]; }
	static void ClearMaps();
	static void AddMap(Map* map);
	static Map* GoToNextLevel();
	static Map* GoToPrevLevel();

private:
	_ljStageMgr();
	~_ljStageMgr();

private:
	// static std::vector<Map*> mAllMap;
	// static int currentIndex;
};

