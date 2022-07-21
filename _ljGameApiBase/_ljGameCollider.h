#pragma once
#include "_ljGameActorSub.h"
#include <set>
#include "_ljGameMacro.h"
#include "_ljGameMath.h"



class _ljGameScene;
class _ljGameCollider : public _ljGameActorSub
{
	friend _ljGameScene;
	friend _ljGameActor;

public:
	static bool(__stdcall* CollisionCheckFunc[COL_TYPE::CT_MAX][COL_TYPE::CT_MAX])(const MyRect& _Left, const MyRect& _Right);

	_ljGameCollider();
	~_ljGameCollider();

private:
	COL_LEAGUE mLeague;
	COL_TYPE mColType;
	std::set<_ljGameCollider*> mColSet;

private:
	void Init();

	void DebugRender();
	void(_ljGameCollider::* DebugRenderFunc)();

	void RectRender();
	void CircleRender();
	void PointRender();

	void CollisionCheck(_ljGameCollider* other);

	void Off() override
	{
		_ljGameBaseUpdater::Off();
		EndColCheck();
	}

	void EndColCheck();


};

