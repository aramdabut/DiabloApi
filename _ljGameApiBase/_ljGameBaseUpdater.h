#pragma once
#include "_ljGameMacro.h"


class _ljGameBaseUpdater /* ON, OFF ��� */
{
public:
	_ljGameBaseUpdater();
	// ���� / �Ҹ� �Ұ�
	virtual ~_ljGameBaseUpdater() = 0;

protected:
	TileIndex mTileIndex;

private:
	bool mIsUpdated;
	bool mIsDead;

public:
	bool IsOff() { return false == mIsUpdated; }
	bool IsOn() { return true == mIsUpdated; }
	void On() { mIsUpdated = true; }
	virtual void Off() { mIsUpdated = false; }
	void KillThis() { mIsDead = true; }

	virtual bool IsUpdated() { return (false == mIsDead) && (true == mIsUpdated); }
	virtual bool IsDead() { return mIsDead; }

public:
	TileIndex GetTileIndex() 
	{ 
		return mTileIndex; 
	}
	
	void SetTileIndex(TileIndex index)
	{
		mTileIndex.X = index.X;
		mTileIndex.Y = index.Y;
	}

};
