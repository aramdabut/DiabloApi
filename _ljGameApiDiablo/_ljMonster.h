#pragma once
#include <_ljGameActor.h>
#include <_ljGameSound.h>
#include "_ljValueData.h"


/*
	속성 > C/C++ > 전처리기

	_DEBUG;_CONSOLE;%(PreprocessorDefinitions)
	NDEBUG;_CONSOLE;%(PreprocessorDefinitions)

	UNICODE;_UNICODE; %(PreprocessorDefinitions); X64;DEBUGMODE;
	UNICODE;_UNICODE; %(PreprocessorDefinitions); X64;RELEASEMODE;

*/

//★
#ifdef RELEASEMODE
#ifdef X32
#pragma comment(lib, "_ljGameApiBase_R32.lib")
#else X64
#pragma comment(lib, "_ljGameApiBase_R64.lib")
#endif
#else DEBUGMODE
#ifdef X32
#pragma comment(lib, "_ljGameApiBase_D32.lib")
#else X64
#pragma comment(lib, "_ljGameApiBase_D64.lib")
#endif
#endif

// #pragma comment(lib, "MyBase_R64.lib")

class _ljColMap;
class _ljTile;
class _ljRandomMap;
class _ljColTile;
class _ljMonster : public _ljGameActor
{
public:
	static _ljMonster* IsMonster(_ljVector _Pos);

	void Update() override;
	void DebugRender() override;

	_ljMonster* CopyMonster(_ljVector pos);

	void SetCurPos(int indexX, int indexY);

	_ljMonster(_ljColMap* colmap, _ljRandomMap* randomMap);
	_ljMonster(const _ljMonster& other);
	virtual ~_ljMonster();

	virtual void GetDamage(int damage) = 0;

	void CalIndex();

	TileIndex DibTileIndex() { return { mX , mY }; }

	void DropMoney();
	void DropItem();
	bool SetDir(_ljColTile* tile);
	bool SetDir(_ljVector pos);
	bool SetDir(TileIndex index);

	UnitData GetUnitData() const { return mData; }
	int MonsterCount() { return mKillCount; }
protected:
	bool SetUnit();



	void CalDir(_ljVector pos);

	void ResetPos(_ljMonster* player);
	void ResetPosM(_ljMonster* monster);

	void GoingToAttackM(_ljMonster* player);

	void SetMove();
	void SetMoveM();

	void NormalDrop();

public:


protected:
	UnitData mData;
	int mCurHP;
	int mCurMP;

	_ljVector mStart;
	bool mIsMoving;

	bool mIsAttacking;
	bool mAttacked;

	_ljColMap* mColMap;
	_ljRandomMap* mRandomMap;

	MONSTER_DIR mDir;
	MONSTER_DIR mPrevDir;

	const wchar_t* mAllStateName[PS_MAX];
	const wchar_t* mAllDirName[MD_MAX];

	bool mIsDead = false;

	TileIndex mPrevTileIndex;
	_ljTile* mDibTile;

	// 공격할 타일
	_ljColTile* mDestDibTile;

	int mX;
	int mY;

	bool mIsDying;
	bool mIsChangingPath;
	bool mIsResting;

	float mRestingCount;
	float mMaxResting;

	bool mGoingToAttack;

	// PathFind
	std::list<_ljVector> mPathList;
	_ljVector mCurDestination;

	float mAttackSpeed;
	float mMoveSpeed;

	int mVision;

	int mIncrease;
	int mBase;

	bool mIsDropped = false;

	_ljGameSound::MyGameSoundStream* mSound;

	int mKillCount = 0;



};
