#pragma once
#include <map>
#include <_ljGameMath.h>
#include <_ljGameRenderer.h>
#include "_ljValueData.h"
#include "_ljTile.h"
#include "_ljMonster.h"
#include "_ljColMap.h"

class _ljMonster;
class _ljPlayer;
class _ljItem;
class _ljObject;
class _ljColTile : public _ljGameRenderer
{
	friend _ljColMap;
	friend _ljTile;

public:
	_ljColTile();
	~_ljColTile();

public:
	void SetPlayer(_ljPlayer* player);
	void SetActor(_ljMonster* actor);
	void SetItem(_ljItem* item) { mItem = item; }
	void UnsetItem() { mItem = nullptr; }
	void UnsetActor() { mMyActor = nullptr; }

	_ljItem* GetItem() { return mItem; }

	_ljMonster* GetActor() { return mMyActor; }

	_ljMonster* MoveOutActor() { _ljMonster* temp = mMyActor; mMyActor = nullptr; return temp; }


	void Render() override;
	void DebugRender() override;
	void Image(const wchar_t* name, int index = 0) override;

	void IsMovable(bool movable) { mIsMovable = movable; }
	bool IsMovable() { return mIsMovable; }

	static void TileDebugSwitch();


	_ljVector Pos() const { return _ljGameActorSub::GetPos(); }

	void SetObject(_ljObject* obj) { mObject = obj; }
	_ljObject* GetDibObject() { return mObject; }

private:
	static bool mIsDebugging;

	bool mIsFog;
	bool mIsMovable = false;
	_ljMonster* mMyActor = nullptr;
	_ljVector mPos;

	_ljPlayer* mPlayer;
	_ljItem* mItem = nullptr;
	_ljObject* mObject = nullptr;
};

