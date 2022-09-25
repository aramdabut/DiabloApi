#pragma once
#include <_ljGameMath.h>


class _ljItem;
class _ljColMap;
class _ljItemMgr
{
private:
	_ljItemMgr();
	~_ljItemMgr();

public:
	static _ljItemMgr* Inst()
	{
		if (nullptr == instance)
		{
			instance = new _ljItemMgr();
		}

		return instance;
	}

	static void Init(_ljColMap* map);
	// static void AddItem(_ljItem* item);
	static _ljItem* RandomItem(int level);
	static void GenerateItem1(std::wstring name, int damage, int maxDamage, int armor, int maxArmor, int dura,
		CHAR_STATS require1, int require1Amount, CHAR_STATS require2, int require2Amount,
		int price, int level, ITEM_TYPE type, int index);

	// static void GenerateItem2(std::wstring name, int price, int level, ITEM_TYPE type);
	// static _ljItem* CloneItem(int index);
	static _ljItem* CloneItem(std::wstring name, int level);
	static _ljItem* CloneAndDrop(int index, _ljVector pos, int level);
	static _ljItem* CloneAndDrop(std::wstring name, _ljVector pos, int level);
	static void DropMoney(TileIndex index, int amount, int level);
	static void DropItem(TileIndex tileIndex, const wchar_t* name, int itemIndex, int level);
	static void DropItem(_ljItem* item, TileIndex tileIndex);
	static void SetCurColMap(_ljColMap* map) { mColMap = map; }
	static _ljColMap* GetColMap() { return mColMap; }
	static void SetLevel(int level) { mLevel = level; }

private:
	static _ljItemMgr* instance;
	static std::vector<_ljItem*> mItemVec;
	static _ljColMap* mColMap;
	// static _ljColMap* mColMap2;
	// static std::map<>
	// static std::vector<_ljItem*> mItem2;
	// static std::vector<_ljItem*> mItem3;

	static int mLevel;


};
