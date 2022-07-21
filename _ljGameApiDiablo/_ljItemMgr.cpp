#include "_ljItemMgr.h"
#include <vector>
#include "_ljColMap.h"
#include "_ljItem.h"
#include "_ljColTile.h"
#include <_ljGameRandomNum.h>
#include <_ljGameAniRenderer.h>



std::vector<_ljItem*> _ljItemMgr::mItemVec;
_ljItemMgr* _ljItemMgr::instance = nullptr;
_ljColMap* _ljItemMgr::mColMap = nullptr;
int _ljItemMgr::mLevel = 0;


_ljItemMgr::_ljItemMgr()
{
}


_ljItemMgr::~_ljItemMgr()
{
}


void _ljItemMgr::Init(_ljColMap* map)
{
	mColMap = map;

	mItemVec.reserve(20);


	// µ·
	GenerateItem1(L"gold", 0, 0, 0, 0, 99, CS_MAX, 0, CS_MAX, 0, 1, 1, IT_GOLD, 15);

	// Ä®
	GenerateItem1(L"short sword", 2, 6, 0, 0, 24, CS_STR, 15, CS_DEX, 20, 60, 1, IT_WEAPON_SWORD, 0);
	GenerateItem1(L"sabre", 1, 8, 0, 0, 25, CS_STR, 17, CS_MAX, 0, 170, 1, IT_WEAPON_SWORD, 1);
	GenerateItem1(L"scimitar", 3, 7, 0, 0, 28, CS_STR, 23, CS_DEX, 23, 200, 2, IT_WEAPON_SWORD, 2);
	GenerateItem1(L"long sword", 2, 10, 0, 0, 40, CS_STR, 30, CS_DEX, 30, 350, 2, IT_WEAPON_SWORD, 3);
	GenerateItem1(L"bastard sword", 6, 15, 0, 0, 60, CS_STR, 50, CS_MAX, 0, 1000, 3, IT_WEAPON_SWORD, 4);

	// °©¿Ê
	GenerateItem1(L"rags", 0, 0, 2, 6, 6, CS_MAX, 0, CS_MAX, 0, 5, 1, IT_ARMOR_LIGHT, 6);
	GenerateItem1(L"robe", 0, 0, 4, 7, 24, CS_MAX, 0, CS_MAX, 0, 75, 1, IT_ARMOR_LIGHT, 7);
	GenerateItem1(L"leather armor", 0, 0, 7, 10, 30, CS_MAX, 0, CS_MAX, 0, 200, 2, IT_ARMOR_LIGHT, 8);
	GenerateItem1(L"studded leather armor", 0, 0, 10, 13, 35, CS_STR, 20, CS_MAX, 0, 700, 2, IT_ARMOR_LIGHT, 9);
	GenerateItem1(L"chain mail", 0, 0, 10, 15, 17, CS_STR, 35, CS_MAX, 0, 1250, 3, IT_ARMOR_HEAVY, 10);

	// µµ³¢
	GenerateItem1(L"axe", 4, 12, 0, 0, 32, CS_STR, 25, CS_MAX, 0, 250, 1, IT_WEAPON_AXE, 5);
	GenerateItem1(L"cleaver", 4, 24, 0, 0, 10, CS_STR, 50, CS_MAX, 0, 2000, 2, IT_WEAPON_CLEAVER, 11);

	// Åõ±¸
	GenerateItem1(L"cap", 0, 0, 1, 3, 15, CS_MAX, 0, CS_MAX, 0, 15, 1, IT_HELM, 18);
	GenerateItem1(L"skull cap", 0, 0, 2, 4, 20, CS_MAX, 0, CS_MAX, 0, 25, 1, IT_HELM, 19);
	GenerateItem1(L"helm", 0, 0, 4, 6, 30, CS_STR, 25, CS_MAX, 0, 40, 2, IT_HELM, 20);

	// ¹æÆÐ
	GenerateItem1(L"buckler", 0, 0, 1, 5, 16, CS_MAX, 0, CS_MAX, 0, 30, 1, IT_SHIELD, 12);
	GenerateItem1(L"small shield", 0, 0, 3, 8, 24, CS_STR, 25, CS_MAX, 0, 90, 1, IT_SHIELD, 13);
	GenerateItem1(L"large shield", 0, 0, 5, 10, 32, CS_STR, 40, CS_MAX, 0, 200, 2, IT_SHIELD, 14);

	// ¾×¼¼¼­¸®
	GenerateItem1(L"ring", 0, 0, 0, 0, 99, CS_MAX, 0, CS_MAX, 0, 1000, 1, IT_RING, 21);
	GenerateItem1(L"amulet", 0, 0, 0, 0, 99, CS_MAX, 0, CS_MAX, 0, 1500, 1, IT_NECK, 22);

	// Æ÷¼Ç
	GenerateItem1(L"potion of healing", 0, 0, 0, 0, 99, CS_MAX, 0, CS_MAX, 0, 50, 1, IT_HPOTION, 24);
	GenerateItem1(L"potion of mana", 0, 0, 0, 0, 99, CS_MAX, 0, CS_MAX, 0, 50, 1, IT_MPOTION, 25);
	GenerateItem1(L"potion of rejuvenation", 0, 0, 0, 0, 99, CS_MAX, 0, CS_MAX, 0, 50, 1, IT_RPOTION, 26);
	GenerateItem1(L"scroll of identify", 0, 0, 0, 0, 99, CS_MAX, 0, CS_MAX, 0, 50, 1, IT_ISCROLL, 27);
	GenerateItem1(L"scroll of town portal", 0, 0, 0, 0, 99, CS_MAX, 0, CS_MAX, 0, 50, 1, IT_PSCROLL, 28);
}

_ljItem* _ljItemMgr::RandomItem(int level)
{
	return nullptr;
}

void _ljItemMgr::GenerateItem1(std::wstring name, int damage, int maxDamage, int armor, int maxArmor, int dura,
	CHAR_STATS require1, int require1Amount, CHAR_STATS require2, int require2Amount,
	int price, int level, ITEM_TYPE type, int index)
{
	_ljItem* temp = new _ljItem();

	temp->mItemData.mName = name;
	temp->mItemData.mDamage = damage;
	temp->mItemData.mMaxDamage = maxDamage;
	temp->mItemData.mArmor = armor;
	temp->mItemData.mMaxArmor = maxArmor;
	temp->mItemData.mDurability = dura;
	temp->mItemData.mRequire1 = require1;
	temp->mItemData.mRequire1Amount = require1Amount;
	temp->mItemData.mRequire2 = require2;
	temp->mItemData.mRequire2Amount = require2Amount;
	temp->mItemData.mPrice = price;
	temp->mItemData.mItemLevel = level;
	temp->mItemData.mType = type;

	temp->mIndex = index;

	switch (type)
	{
	case IT_GOLD:
		temp->mItemData.X = 1;
		temp->mItemData.Y = 1;
		temp->mAniName = L"MONEY";
		break;
	case IT_WEAPON_CLEAVER:
		temp->mItemData.X = 2;
		temp->mItemData.Y = 3;
		temp->mAniName = L"CLEAVER";
		break;
	case IT_WEAPON_AXE:
		temp->mItemData.X = 2;
		temp->mItemData.Y = 3;
		temp->mAniName = L"AXE";
		break;
	case IT_WEAPON_SWORD:
		temp->mItemData.X = 1;
		temp->mItemData.Y = 3;
		temp->mAniName = L"SWORD";
		break;
	case IT_WEAPON_BOW:
		break;
	case IT_ARMOR_LIGHT:
		temp->mItemData.X = 2;
		temp->mItemData.Y = 3;
		temp->mAniName = L"LARMOR";
		break;
	case IT_ARMOR_HEAVY:
		temp->mItemData.X = 2;
		temp->mItemData.Y = 3;
		temp->mAniName = L"HARMOR";
		break;
	case IT_HELM:
		temp->mItemData.X = 2;
		temp->mItemData.Y = 2;
		temp->mAniName = L"HELM";
		break;
	case IT_SHIELD:
		temp->mItemData.X = 2;
		temp->mItemData.Y = 3;
		temp->mAniName = L"SHIELD";
		break;
	case IT_RING:
		temp->mItemData.X = 1;
		temp->mItemData.Y = 1;
		temp->mAniName = L"RING";
		break;
	case IT_NECK:
		temp->mItemData.X = 1;
		temp->mItemData.Y = 1;
		temp->mAniName = L"RING";
		break;
	case IT_BOOK:
		temp->mItemData.X = 2;
		temp->mItemData.Y = 2;

		break;
	case IT_HPOTION:
		temp->mItemData.X = 1;
		temp->mItemData.Y = 1;
		temp->mAniName = L"HPOTION";
		break;
	case IT_MPOTION:
		temp->mItemData.X = 1;
		temp->mItemData.Y = 1;
		temp->mAniName = L"MPOTION";
		break;
	case IT_RPOTION:
		temp->mItemData.X = 1;
		temp->mItemData.Y = 1;
		temp->mAniName = L"RPOTION";
		break;
	case IT_ISCROLL:
	case IT_PSCROLL:
		temp->mItemData.X = 1;
		temp->mItemData.Y = 1;
		temp->mAniName = L"SCROLL";
		break;
	case IT_MAX:
		break;
	default:
		break;
	}

	mItemVec.push_back(temp);
}

//_ljItem* _ljItemMgr::CloneItem(int index)
//{
//	if (0 > index || index >= mItemVec.size())
//	{
//		BOOM;
//
//		return nullptr;
//	}
//
//	_ljItem* temp = mItemVec[index]->CopyItem();
//
//	// _ljGameManager::GetMap()->SetUnitAt(pos, temp);
//
//	return temp;
//}
//
_ljItem* _ljItemMgr::CloneItem(std::wstring name, int level)
{
	for (size_t i = 0; i < mItemVec.size(); ++i)
	{
		if (mItemVec[i]->mItemData.mName == name)
		{
			_ljItem* temp = mItemVec[i]->CopyItem(level);
			temp->mPlayer = mColMap->mPlayer;
			return temp;
		}
	}

	return nullptr;
}

// 0ÀÌ¸é µ·, 1ÀÌ¸é ¾ÆÀÌÅÛ
_ljItem* _ljItemMgr::CloneAndDrop(int index, _ljVector pos, int level)
{
	if (0 > index || index >= mItemVec.size() || true == OverCheck(pos))
	{
		BOOM;

		return nullptr;
	}

	_ljItem* temp = nullptr;

	if (0 == index)
	{
		temp = mItemVec[index]->CopyItem(level);

		temp->SetTile(pos);
	}
	else
	{
		int random = _ljGameRandomNum::GetRandomNumber(1, (int)mItemVec.size() - 1);

		temp = mItemVec[random]->CopyItem(level);

		temp->SetTile(pos);
	}

	return temp;
}

_ljItem* _ljItemMgr::CloneAndDrop(std::wstring name, _ljVector pos, int level)
{
	//_ljItem* temp = CloneItem(name);

	//// Ã£´Â °Ô ¾øÀ¸¸é
	//if (nullptr == temp)
	//{
	//	BOOM;
	//}
	//else
	//{
	//	int random = _ljGameRandomNum::GetRandomNumber(1, (int)mItemVec.size() - 1);

	//	temp = mItemVec[random]->CopyItem();

	//	temp->SetTile(pos);
	//}

	return nullptr;
}

void _ljItemMgr::DropMoney(TileIndex index, int amount, int level)
{
	_ljItem* money = CloneItem(L"gold", level);
	money->mLevel = level;
	money->mItemData.gold = amount;

	_ljVector offset = _ljVector(0.f, -64.f);
	_ljVector offset2 = _ljVector(1.f, -7.f);
	money->mInGame->SetCurrentAnimation(L"MONEY");
	money->mInGame->SubPos(mColMap->IndexToPosM(index) + offset);

	money->mInGame2->SetCurrentAnimation(L"MONEY");
	money->mInGame2->SubPos(mColMap->IndexToPosM(index) + offset);

	money->mInGameBack->SetCurrentAnimation(L"MONEY");
	money->mInGameBack->SubPos(mColMap->IndexToPosM(index) + offset);

	money->mInGame->On();

	money->mTileIndex = index;

	_ljColTile* tempTile = mColMap->FindTile(index.X, index.Y);

	tempTile->SetItem(money);
}

void _ljItemMgr::DropItem(TileIndex tileIndex, const wchar_t* name, int itemIndex, int level)
{
	_ljItem* temp = CloneItem(name, level);
	temp->mLevel = level;
	_ljVector offset = _ljVector(0.f, -64.f);
	_ljVector offset2 = _ljVector(1.f, -7.f);

	ITEM_TYPE type = temp->mItemData.mType;

	switch (type)
	{
	case IT_GOLD:
		BOOM;
		break;
	case IT_WEAPON_AXE:
		temp->mInGame->SetCurrentAnimation(L"AXE");
		temp->mInGame2->SetCurrentAnimation(L"AXE");
		temp->mInGameBack->SetCurrentAnimation(L"AXE");
		break;
	case IT_WEAPON_CLEAVER:
		temp->mInGame->SetCurrentAnimation(L"CLEAVER");
		temp->mInGame2->SetCurrentAnimation(L"CLEAVER");
		temp->mInGameBack->SetCurrentAnimation(L"CLEAVER");
		break;
	case IT_WEAPON_SWORD:
		temp->mInGame->SetCurrentAnimation(L"SWORD");
		temp->mInGame2->SetCurrentAnimation(L"SWORD");
		temp->mInGameBack->SetCurrentAnimation(L"SWORD");
		break;
	case IT_WEAPON_BOW:
		break;
	case IT_ARMOR_LIGHT:
		temp->mInGame->SetCurrentAnimation(L"LARMOR");
		temp->mInGame2->SetCurrentAnimation(L"LARMOR");
		temp->mInGameBack->SetCurrentAnimation(L"LARMOR");
		break;
	case IT_ARMOR_HEAVY:
		temp->mInGame->SetCurrentAnimation(L"HARMOR");
		temp->mInGame2->SetCurrentAnimation(L"HARMOR");
		temp->mInGameBack->SetCurrentAnimation(L"HARMOR");
		break;
	case IT_HELM:
		temp->mInGame->SetCurrentAnimation(L"HELM");
		temp->mInGame2->SetCurrentAnimation(L"HELM");
		temp->mInGameBack->SetCurrentAnimation(L"HELM");
		break;
	case IT_SHIELD:
		temp->mInGame->SetCurrentAnimation(L"SHIELD");
		temp->mInGame2->SetCurrentAnimation(L"SHIELD");
		temp->mInGameBack->SetCurrentAnimation(L"SHIELD");
		break;
	case IT_RING:
		temp->mInGame->SetCurrentAnimation(L"RING");
		temp->mInGame2->SetCurrentAnimation(L"RING");
		temp->mInGameBack->SetCurrentAnimation(L"RING");
		break;
	case IT_NECK:
		temp->mInGame->SetCurrentAnimation(L"RING");
		temp->mInGame2->SetCurrentAnimation(L"RING");
		temp->mInGameBack->SetCurrentAnimation(L"RING");
		break;
	case IT_BOOK:
		break;
	case IT_HPOTION:
		temp->mInGame->SetCurrentAnimation(L"HPOTION");
		temp->mInGame2->SetCurrentAnimation(L"HPOTION");
		temp->mInGameBack->SetCurrentAnimation(L"HPOTION");
		break;
	case IT_MPOTION:
		temp->mInGame->SetCurrentAnimation(L"MPOTION");
		temp->mInGame2->SetCurrentAnimation(L"MPOTION");
		temp->mInGameBack->SetCurrentAnimation(L"MPOTION");
		break;
	case IT_RPOTION:
		temp->mInGame->SetCurrentAnimation(L"RPOTION");
		temp->mInGame2->SetCurrentAnimation(L"RPOTION");
		temp->mInGameBack->SetCurrentAnimation(L"RPOTION");
		break;
	case IT_ISCROLL:
		temp->mInGame->SetCurrentAnimation(L"SCROLL");
		temp->mInGame2->SetCurrentAnimation(L"SCROLL");
		temp->mInGameBack->SetCurrentAnimation(L"SCROLL");
		break;
	case IT_PSCROLL:
		temp->mInGame->SetCurrentAnimation(L"SCROLL");
		temp->mInGame2->SetCurrentAnimation(L"SCROLL");
		temp->mInGameBack->SetCurrentAnimation(L"SCROLL");
		break;
	case IT_MAX:
		break;
	default:
		break;
	}

	temp->mInGame->SubPos(mColMap->IndexToPosM(tileIndex) + offset);
	temp->mInGame2->SubPos(mColMap->IndexToPosM(tileIndex) + offset);
	temp->mInGameBack->SubPos(mColMap->IndexToPosM(tileIndex) + offset);

	temp->mInGame->On();

	temp->mTileIndex = tileIndex;

	_ljColTile* tempTile = mColMap->FindTile(tileIndex.X, tileIndex.Y);

	tempTile->SetItem(temp);
}

void _ljItemMgr::DropItem(_ljItem* item, TileIndex tileIndex)
{
	_ljItem* temp = item;

	_ljVector offset = _ljVector(0.f, -64.f);
	_ljVector offset2 = _ljVector(1.f, -7.f);

	ITEM_TYPE type = temp->mItemData.mType;

	for (int i = 0; i < 8; ++i)
	{
		TileIndex tempIndex = tileIndex + mColMap->mDirArr[i];

		_ljColTile* myTile = mColMap->FindTile(tempIndex);

		if (nullptr == myTile->GetItem() && true == myTile->IsMovable())
		{
			switch (type)
			{
			case IT_GOLD:
				BOOM;
				break;
			case IT_WEAPON_AXE:
				temp->mInGame->SetCurrentAnimation(L"AXE");
				temp->mInGame2->SetCurrentAnimation(L"AXE");
				temp->mInGameBack->SetCurrentAnimation(L"AXE");
				break;
			case IT_WEAPON_CLEAVER:
				temp->mInGame->SetCurrentAnimation(L"CLEAVER");
				temp->mInGame2->SetCurrentAnimation(L"CLEAVER");
				temp->mInGameBack->SetCurrentAnimation(L"CLEAVER");
				break;
			case IT_WEAPON_SWORD:
				temp->mInGame->SetCurrentAnimation(L"SWORD");
				temp->mInGame2->SetCurrentAnimation(L"SWORD");
				temp->mInGameBack->SetCurrentAnimation(L"SWORD");
				break;
			case IT_WEAPON_BOW:
				break;
			case IT_ARMOR_LIGHT:
				temp->mInGame->SetCurrentAnimation(L"LARMOR");
				temp->mInGame2->SetCurrentAnimation(L"LARMOR");
				temp->mInGameBack->SetCurrentAnimation(L"LARMOR");
				break;
			case IT_ARMOR_HEAVY:
				temp->mInGame->SetCurrentAnimation(L"HARMOR");
				temp->mInGame2->SetCurrentAnimation(L"HARMOR");
				temp->mInGameBack->SetCurrentAnimation(L"HARMOR");
				break;
			case IT_HELM:
				temp->mInGame->SetCurrentAnimation(L"HELM");
				temp->mInGame2->SetCurrentAnimation(L"HELM");
				temp->mInGameBack->SetCurrentAnimation(L"HELM");
				break;
			case IT_SHIELD:
				temp->mInGame->SetCurrentAnimation(L"SHIELD");
				temp->mInGame2->SetCurrentAnimation(L"SHIELD");
				temp->mInGameBack->SetCurrentAnimation(L"SHIELD");
				break;
			case IT_RING:
				temp->mInGame->SetCurrentAnimation(L"RING");
				temp->mInGame2->SetCurrentAnimation(L"RING");
				temp->mInGameBack->SetCurrentAnimation(L"RING");
				break;
			case IT_NECK:
				temp->mInGame->SetCurrentAnimation(L"RING");
				temp->mInGame2->SetCurrentAnimation(L"RING");
				temp->mInGameBack->SetCurrentAnimation(L"RING");
				break;
			case IT_BOOK:
				break;
			case IT_HPOTION:
				temp->mInGame->SetCurrentAnimation(L"HPOTION");
				temp->mInGame2->SetCurrentAnimation(L"HPOTION");
				temp->mInGameBack->SetCurrentAnimation(L"HPOTION");
				break;
			case IT_MPOTION:
				temp->mInGame->SetCurrentAnimation(L"MPOTION");
				temp->mInGame2->SetCurrentAnimation(L"MPOTION");
				temp->mInGameBack->SetCurrentAnimation(L"MPOTION");
				break;
			case IT_RPOTION:
				temp->mInGame->SetCurrentAnimation(L"RPOTION");
				temp->mInGame2->SetCurrentAnimation(L"RPOTION");
				temp->mInGameBack->SetCurrentAnimation(L"RPOTION");
				break;
			case IT_ISCROLL:
				temp->mInGame->SetCurrentAnimation(L"SCROLL");
				temp->mInGame2->SetCurrentAnimation(L"SCROLL");
				temp->mInGameBack->SetCurrentAnimation(L"SCROLL");
				break;
			case IT_PSCROLL:
				temp->mInGame->SetCurrentAnimation(L"SCROLL");
				temp->mInGame2->SetCurrentAnimation(L"SCROLL");
				temp->mInGameBack->SetCurrentAnimation(L"SCROLL");
				break;
			case IT_MAX:
				break;
			default:
				break;
			}

			temp->mInGame->SubPos(mColMap->IndexToPosM(tempIndex) + offset);
			temp->mInGame2->SubPos(mColMap->IndexToPosM(tempIndex) + offset);
			temp->mInGameBack->SubPos(mColMap->IndexToPosM(tempIndex) + offset);

			temp->mInGame->On();

			temp->mTileIndex = tempIndex;

			_ljColTile* tempTile = mColMap->FindTile(tempIndex.X, tempIndex.Y);

			tempTile->SetItem(temp);

			return;
		}
	}

}
