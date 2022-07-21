#include "_ljMonsterMgr.h"
//
//#include "_ljMonsterMgr.h"
//#include "_ljMonster.h"
//#include "_ljGameManager.h"
//#include "Map.h"
//
//std::vector<_ljMonster*> _ljMonsterMgr::mM1;
//std::vector<_ljMonster*> _ljMonsterMgr::mM2;
//std::vector<_ljMonster*> _ljMonsterMgr::mM3;
//int _ljMonsterMgr::index = 0;
//
//void _ljMonsterMgr::GenerateM1(int dlevel, const wchar_t* name, int level, int maxHp, int armor, int attack, int maxAttack, int toHit, int exp, wchar_t pixel)
//{
//	_ljMonster* mon = new _ljMonster();
//
//	mon->SetName(name);
//	mon->SetData(dlevel, level, maxHp, armor, attack, maxAttack, toHit, exp);
//
//	mon->Pixel(pixel);
//	
//	mM1.push_back(mon);
//
//	++index;
//}
//
//// 복사하여 위치 지정까지
//_ljMonster* _ljMonsterMgr::CloneM1(int index, Position pos)
//{
//	if (0 > index || index >= mM1.size() || true == OverCheck(pos))
//	{
//		BOOM;
//
//		return nullptr;
//	}
//
//	_ljMonster* temp = mM1[index]->CopyMonster(pos);
//
//	// Map::UnsetUnitAt(mPos);
//
//	temp->SetTile(pos);
//	temp->SetHP();
//
//	_ljGameManager::GetMap()->SetUnitAt(pos, temp);
//
//	return temp;
//}
//
//void _ljMonsterMgr::Init()
//{
//	// 레벨 1
//	// _ljFallen ⒡
//	GenerateM1(1, L"_ljFallen One", 1, 2, 10, 1, 4, 15, 52, PIXEL_FALLEN);
//	// _ljScavenger ⒮
//	GenerateM1(2, L"_ljScavenger", 1, 3, 10, 1, 5, 20, 80, PIXEL_SCAVEN);
//	// _ljSkeleton ㏜
//	GenerateM1(2, L"_ljSkeleton", 1, 2, 0, 1, 5, 20, 64, PIXEL_SKEL);
//	// _ljZombie
//	GenerateM1(2, L"_ljZombie", 1, 1, 5, 2, 5, 10, 54, PIXEL_ZOMBIE);
//}
//
//_ljMonsterMgr::_ljMonsterMgr()
//{
//}
//
//
//_ljMonsterMgr::~_ljMonsterMgr()
//{
//
//}
//
//void _ljMonsterMgr::Clear()
//{
//	for (int y = 0; y < mM1.size(); y++)
//	{
//		if (nullptr != mM1[y])
//		{
//			delete mM1[y];
//			mM1[y] = nullptr;
//		}
//	}
//
//	for (int y = 0; y < mM2.size(); y++)
//	{
//		if (nullptr != mM2[y])
//		{
//			delete mM2[y];
//			mM2[y] = nullptr;
//		}
//	}
//
//	for (int y = 0; y < mM3.size(); y++)
//	{
//		if (nullptr != mM3[y])
//		{
//			delete mM3[y];
//			mM3[y] = nullptr;
//		}
//	}
//}
