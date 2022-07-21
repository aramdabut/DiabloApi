#pragma once
#include <_ljGameMath.h>
#include <_ljGameActor.h>
#include "_ljValueData.h"



class _ljPlayer;
class _ljTestScene;
class _ljDungeon2;
class _ljDungeon15;
class _ljDungeon18;
class _ljItem : public _ljGameActor
{
	friend class _ljItemMgr;
	friend _ljPlayer;
	friend _ljTestScene;
	friend _ljDungeon2;
	friend _ljDungeon15;
	friend _ljDungeon18;
	friend class _ljInvenBack;

public:
	_ljItem();
	_ljItem(const _ljItem& other);
	~_ljItem();

private:
	_ljGameAniRenderer* mInGame;
	// _ljGameAniRenderer* mSubInGame;

	// 바닥에 다 떨어지면 다른 RENDER_LEAGUE의 애니렌더러를 사용
	_ljGameAniRenderer* mInGame2;
	_ljGameAniRenderer* mInGameBack;

	_ljGameRenderer* mInven;
	_ljGameRenderer* mInvenEdge;

	ItemData mItemData;

	// 애니메이션 확인용
	bool mIsOver = false;
	bool mIsTaken = false;

	_ljPlayer* mPlayer;

	int mIndex;

	std::wstring mAniName;

	int mX;
	int mY;

	bool mIsOn = false;
	bool mIsSet = false;
	bool mWillBeOn = false;
	bool mWillBeOff = false;
	bool mWillBeSet = false;

	// 무기를 바꾸고 있는 중이다.
	static bool mIsChanging;

	bool mIsEquiped = false;

	int mBase;

	bool mHasWeapon = false;
	bool mHasArmor = false;
	bool mHasHelm = false;
	bool mHasLeftRing = false;
	bool mHasRightRing = false;
	bool mHasNeck = false;
	bool mHasShield = false;

	_ljItem* mMouseItem;

	int mLevel = 0;

	bool mIsDropped = false;

	std::wstring mDamage;
	std::wstring mArmor;

	std::wstring mDur;
	std::wstring mIden;

	bool mIsOnBelt;
	bool mIsOffset = true;
	int mBeltIndex;

public:
	_ljItem* CopyItem(int level);

public:
	void SetTile(_ljVector pos);
	void Update() override;
	void AllOff();
	void ResetPosition(int x, int y);
	void SetPosition(int x, int y);
	void ResetAni();
	void DebugRender() override;
	void UseItem();

private:
	void Unarm();
	bool CheckMouse();
	void SetInven(_ljVector mousePos);
	void UnsetInven();
	int	CheckInven(_ljVector mousePos);
	void ArmWeapon();
	void ArmArmor();
	void ArmShield();
	void ArmHelm();
	void ArmLRing();
	void ArmRRing();
	void ArmNeck();
	void SetPotion(int x, int y);
	void UnsetPotion();

};