#pragma once
#include "_ljMonster.h"
#include "_ljValueData.h"
#include <vector>
#include "_ljTile.h"



class _ljGameRenderer;
class _ljColMap;
class _ljFog;
class _ljRoom;
class _ljStat;
class _ljGameFile;
class _ljItem;
class _ljInvenBack;
class _ljLevel;
class _ljTestScene;
class _ljDungeon2;
class _ljDungeon15;
class _ljDungeon18;
class _ljFont;
class _ljYFont;
class _ljPlayer : public _ljMonster
{
	friend _ljStat;
	friend _ljFog;
	friend _ljInvenBack;
	friend _ljItem;
	friend _ljColMap;
	friend _ljTestScene;
	friend _ljDungeon2;
	friend _ljDungeon15;
	friend _ljDungeon18;

	friend class _ljObject;
	friend class _ljButcher;


public:
	_ljPlayer* Inst() { return this; }

public:
	_ljPlayer(_ljColMap* colmap, _ljRandomMap* randomMap);
	virtual ~_ljPlayer();
	void CopyPlayer(_ljPlayer* player);

	void GetDamage(int damage) override;

	void SetCurPos(int indexX, int indexY);

	void SetCurrentState(PLAYER_STATE state, bool noneDir = false);
	void Update() override;
	void DebugRender() override;

	void SetDestination();

	const MONSTER_DIR PlayerDir() const { return mDir; }
	void PlayerDir(MONSTER_DIR dir) { mDir = dir; }

	bool CheckDir();
	void CheckDirChange();
	// void SetDir(_ljColTile* dest);

	void WalkTask();

	void Idle();
	void Walk();
	void Attack();
	void Block();
	void Die();
	void RedSkill();
	void BlueSkill();
	void GetHit();

	void Fire();
	void StandingAttack(_ljVector pos);

	//////////////////////////////////////// ColliderMap과 연동
	void SetColPosition(int indexX, int indexY);

	bool CheckWalkableTile();

	_ljTile* GetDibTile() const { return mDibTile; }

	int DibTileX() const { return mDibTile->mX; }
	int DibTileY() const { return mDibTile->mY; }
	void GetExp(int exp) { mData.exp += exp; }

	TileIndex GetMouseIndex() { return mMouseIndex; }
	bool IsInvenOpen() { return mIsInvenOpen; }
	void ResetDir() { mDir = B; }
	void SetLevel(int level) { mLevel = level; }
	int GetLevel() { return mLevel; }
	bool IsStatOpen() { return mIsStatOpen; }
	///////////////////////////////////////// 아이템 폰트 관련
	void DescOn(std::wstring string1) { mIsShowing1 = true; mString1 = string1; }
	void DescOn(std::wstring string1, std::wstring string2) { mIsShowing2 = true; mString1 = string1; mString2 = string2; }
	void DescOn(std::wstring string1, std::wstring string2, std::wstring string3) { mIsShowing3 = true; mString1 = string1; mString2 = string2; mString3 = string3; }
	void DescYOn(std::wstring string1) { mIsYShowing1 = true; mString1 = string1; }
	void DescYOn(std::wstring string1, std::wstring string2) { mIsYShowing2 = true; mString1 = string1; mString2 = string2; }
	void DescYOn(std::wstring string1, std::wstring string2, std::wstring string3) { mIsYShowing3 = true; mString1 = string1; mString2 = string2; mString3 = string3; }


	void ShowDescription(std::wstring string1);
	void ShowDescription(std::wstring string1, std::wstring string2);
	void ShowDescription(std::wstring string1, std::wstring string2, std::wstring string3);
	void ShowYDescription(std::wstring string1);
	void ShowYDescription(std::wstring string1, std::wstring string2);
	void ShowYDescription(std::wstring string1, std::wstring string2, std::wstring string3);
	void UnshowDescription();
	bool IsPosSet() const { return mIsPosSet; }
private:
	void SetAnimation();
	void AutoAnimation(const wchar_t* name, int index, float frameSpeed = 0.05f, bool isLoop = true);
	void AutoAnimationAxe(const wchar_t* name, int index, float frameSpeed = 0.05f, bool isLoop = true);

	void GoingToMove(_ljVector mousePos);
	void GoingToAttack(_ljVector mousePos);
	void GoingToPick(_ljVector mousePos, bool Open);
	bool GoingToPick(TileIndex index, CHEST_TYPE type, bool isRight);

	void OpenBox(_ljVector mousePos);
	void OpenBox(_ljColTile* tile);
	void OpenBox(TileIndex index);

	void PickItem(_ljVector mousePos);
	void PickItem(_ljColTile* tile);
	void PreMove();

	void CheckInRoom();
	bool CheckButton();
	bool CheckMouse();

	void OpenCloseInven();
	void OpenCloseStat();
	bool CheckMouse(_ljVector mouse);
	void UpdateStat();
	void ResetPos(_ljMonster* player);
	void Reset();
	///////////////////////// 인벤토리
	int CheckAcquire(_ljItem* item);
	void Acquire(_ljItem* item, int base);
	void SuperAcquire(_ljItem* item, int base);

	void ApplyItem(_ljItem* data);
	void UnapplyItem(_ljItem* data);
	///////////////////////// 경험치


	////////////////////// 스탯
	void CheckExp();

	void LevelUp();

	void LoadEXP();

	void SetMouseMonster();
private:
	_ljGameAniRenderer* mAnimationRenderer;
	_ljGameAniRenderer* mLevelUpRenderer;
	////////////////////// UI RENDERER /////////////////////////////////////
	_ljGameRenderer* mUI;
	_ljGameRenderer* mHP;
	_ljGameRenderer* mMP;

	_ljGameRenderer* mInven;
	_ljGameRenderer* mStats;

	_ljGameRenderer* mButton;
	_ljGameRenderer* mPointButton;

	_ljGameRenderer* mStrButton;
	_ljGameRenderer* mMagButton;
	_ljGameRenderer* mDexButton;
	_ljGameRenderer* mVitButton;

	_ljGameRenderer* mMouseRenderer;

	_ljLevel* mLevelRender;

	_ljMonster* mMonster;

	_ljFog* mFog;
	_ljInvenBack* mInvenBack;
	_ljStat* mStatRenderer;

	_ljFont* mFontRenderer;
	_ljYFont* mYFontRenderer;
	// 플레이어 이동 관련

	PLAYER_STATE mState;

	bool mIsDirKey;

	int mDebugCount;

	bool mIsStandingAttack;

	_ljVector mLastMouse;


	_ljVector mNewDestination;

	_ljRoom* mLastRoom;

	bool mIsInvenOpen;
	bool mIsStatOpen;
	bool mGoingToPick;
	bool mGoingToOpen = false;

	int mButtonOffset;

	///////////////////////////////////////// STAT
	_ljGameFile* mExpFile;
	std::vector<int> mExpVec;
	std::list<_ljItem*> mItemList;
	int mBaseHP = 50;
	int mBaseMP = 20;

	int mItemAttack = 0;
	int mItemMaxAttack = 0;

	int mItemArmor = 0;
	int mItemToHit = 0;
	int mItemHP = 0;
	int mItemMP = 0;
	int mItemStr = 0;
	int mItemDex = 0;
	int mItemVit = 0;
	int mItemInt = 0;
	int mItemMag = 0;

	int mStr = 30;
	int mDex = 20;
	int mVit = 25;
	int mMag = 10;
	int mPoint = 0;

	int mCurStr = 30;
	int mCurDex = 20;
	int mCurVit = 25;
	int mCurMag = 10;

	bool mIsPoint;

	_ljItem** mInventory;

	//std::vector<_ljItem*> mInventory1;
	//std::vector<_ljItem*> mInventory2;
	//std::vector<_ljItem*> mInventory3;
	//std::vector<_ljItem*> mInventory4;

	_ljItem* mTileItem;
	TileIndex mMouseIndex;

	int mNextInvenIndex;

	/////////////////////////// 인벤토리 마우스
	bool mIsClicked;
	bool mIsItemOn;

	bool mHasWeapon = false;
	bool mHasHelm = false;
	bool mHasArmor = false;
	bool mHasShield = false;
	bool mHasLeftRing = false;
	bool mHasRightRing = false;
	bool mHasNeck = false;

	ItemData mItemData;

	_ljItem* mWeapon = nullptr;
	_ljItem* mArmor = nullptr;
	_ljItem* mShield = nullptr;
	_ljItem* mHelm = nullptr;
	_ljItem* mLRing = nullptr;
	_ljItem* mRRing = nullptr;
	_ljItem* mNeck = nullptr;

	_ljItem* mMouseItem = nullptr;

	int mLevel = 0;
	float mStepTime = 0.1f;
	int mStepCount = 0;
	int mStepMax = 4;

	// bool mAttackSound = false;
	bool mIsShowing1 = false;
	bool mIsShowing2 = false;
	bool mIsShowing3 = false;
	bool mIsYShowing1 = false;
	bool mIsYShowing2 = false;
	bool mIsYShowing3 = false;

	std::wstring mString1;
	std::wstring mString2;
	std::wstring mString3;

	_ljMonster* mMouseMonster;

	std::wstring mTC;
	std::wstring mImune;

	bool mIsPosSet = false;

	bool mAxe = false;
	bool mUpdate = false;

	bool mIsBlock = false;
	int mBlockRate = 15;

	HCURSOR g_hNumCursor;

	TileIndex debugMouse;

	_ljObject* mDibObject = nullptr;

	bool mIsNoMove = false;

	bool mIsButcherDead = false;
	bool mIsAllOver = false;
};


