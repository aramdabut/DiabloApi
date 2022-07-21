#pragma once
#include <_ljGameActor.h>
#include "_ljValueData.h"
#include <vector>



class _ljPlayer;
class _ljObject : public _ljGameActor
{
public:
	_ljObject();
	_ljObject(int index, _ljVector pos, TileIndex tileIndex);
	~_ljObject();

private:
	_ljGameAniRenderer* mAniRenderer1;
	_ljGameAniRenderer* mAniRenderer2;

	_ljGameRenderer* mFogRenderer1;
	_ljGameRenderer* mFogRenderer2;

	_ljGameRenderer* mObjectEdge;

	_ljPlayer* mPlayer;

	CHEST_TYPE mChestType;

	const wchar_t* mAllChestName[CHT_MAX];

	int mX;
	int mY;

	bool mIsOn = false;
	bool mOpenOver = false;

	int mIndex;

	std::wstring mName;

public:
	void Open();
	CHEST_TYPE GetChestType() { return mChestType; }
	std::wstring GetName() { return mName; }

private:
	void SetAnimation();
	void Update();
	void DropItem();
	void DropRealItem();
	void DropMoney();
	void DropMonster();

public:
	static std::vector<_ljObject*> mAllObject;
	static void SetPlayer(_ljPlayer* player);

};

