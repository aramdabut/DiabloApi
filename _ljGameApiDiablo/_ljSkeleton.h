#pragma once
#include "_ljMonster.h"


class _ljPlayer;
class _ljSkeleton : public _ljMonster
{
public:
	_ljSkeleton(_ljColMap* colmap, _ljRandomMap* randomMap, _ljPlayer* player);
	_ljSkeleton(_ljColMap* colmap, _ljRandomMap* randomMap, _ljPlayer* player, TileIndex index);
	virtual ~_ljSkeleton();

	void DebugRender() override;
	void Update() override;
	void StateUpdate();

	void FindPlayer();


	void CheckDirChange();
	bool CheckDir();

	void WalkTask();

	void Idle();
	void Walk();
	void Attack();
	void Die();
	void GetHit();
	void Special();
	void Rest();

	void SetCurrentState(MONSTER_STATE state, bool noneDir = false);

	void GetDamage(int damage) override;

	// void GoingToMoveInTheMiddle();
	// void GoingToMoveFromIdle();

	void SetAnimation();
	void AutoAnimation(const wchar_t* name, int index, float frameSpeed = 0.05f);

	void GoingToMove(_ljVector mousePos);
	void GoingToAttack(_ljVector mousePos);
	void PreMove();

private:
	_ljGameAniRenderer* mAnimationRenderer;
	_ljGameAniRenderer* mSubRenderer;
	// _ljGameAniRenderer* mBlackRenderer;
	_ljGameRenderer* mBlackRenderer;

	MONSTER_STATE mState;

	_ljPlayer* mPlayer;
	_ljMonster* mMonster;

	bool mIsPlayerAround;
	bool mIsExpDone;

	static int mCount;
};

