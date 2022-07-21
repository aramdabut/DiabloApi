#include "_ljStageMgr.h"
//#include "_ljGameManager.h"
//
//#include "Map.h"
//
//std::vector<Map*> _ljStageMgr::mAllMap = std::vector<Map*>();
//int _ljStageMgr::currentIndex = 0;
//
//void _ljStageMgr::ClearMaps()
//{
//	for (int i = 0; i < mAllMap.capacity(); i++)
//	{
//		if (nullptr != mAllMap[i])
//		{
//			delete mAllMap[i];
//			mAllMap[i] = nullptr;
//		}
//	}
//}
//
//_ljStageMgr::_ljStageMgr()
//{
//}
//
//
//_ljStageMgr::~_ljStageMgr()
//{
//}
//
//void _ljStageMgr::AddMap(Map* map)
//{
//	mAllMap.push_back(map);
//
//	//for (int y = 0; y < _ljGameManager::ScreenSize().Y; y++)
//	//{
//	//	for (int x = 0; x < _ljGameManager::ScreenSize().X; x++)
//	//	{
//	//		mAllTile[y][x].FindNeighbor();
//	//	}
//	//}
//}
//
//
//Map* _ljStageMgr::GoToNextLevel()
//{
//	++currentIndex;
//
//	if (mAllMap.size() <= currentIndex)
//	{
//		return nullptr;
//	}
//
//	return mAllMap[currentIndex];
//}
//
//Map* _ljStageMgr::GoToPrevLevel()
//{
//	--currentIndex;
//
//	if (0 > currentIndex)
//	{
//		return nullptr;
//	}
//
//
//
//	return mAllMap[currentIndex];
//}