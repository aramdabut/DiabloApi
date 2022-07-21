#include "_ljGameCollider.h"
#include <Windows.h>
#include "_ljGameTextureMgr.h"
#include "_ljGameActor.h"



bool(__stdcall* _ljGameCollider::CollisionCheckFunc[COL_TYPE::CT_MAX][COL_TYPE::CT_MAX])(const MyRect& _Left, const MyRect& _Right)
{
	{ &_ljGameMath::RectToRect, & _ljGameMath::RectToCircle, & _ljGameMath::RectToPoint },
	{ &_ljGameMath::CircleToRect, &_ljGameMath::CircleToCircle, &_ljGameMath::CircleToPoint },
	{ &_ljGameMath::PointToRect, &_ljGameMath::PointToCircle, &_ljGameMath::PointToPoint }
};

_ljGameCollider::_ljGameCollider()
{
}

_ljGameCollider::~_ljGameCollider()
{
	EndColCheck();
}

void _ljGameCollider::Init()
{
	switch (mColType)
	{
	case CT_RECT2D:
		DebugRenderFunc = &_ljGameCollider::RectRender;
		break;
	case CT_CIRCLE2D:
		DebugRenderFunc = &_ljGameCollider::CircleRender;
		break;
	case CT_POINT2D:
		DebugRenderFunc = &_ljGameCollider::PointRender;
		break;
	case CT_MAX:
		BOOM;
		break;
	default:
		break;
	}
}

void _ljGameCollider::DebugRender()
{
	(this->*DebugRenderFunc)();
}

void _ljGameCollider::RectRender()
{
	MyRect rc = CalRect();
	Rectangle(_ljGameTextureMgr::BackDC(), rc.IntLeft(), rc.IntTop(), rc.IntRight(), rc.IntBottom());
}

void _ljGameCollider::CircleRender()
{
}

void _ljGameCollider::PointRender()
{
}

void _ljGameCollider::CollisionCheck(_ljGameCollider* other)
{

	if (true == CollisionCheckFunc[mColType][other->mColType](CalRect(), other->CalRect()))
	{
		// 상대편의 충돌체이다.

		if (mColSet.end() == mColSet.find(other))
		{
			mColSet.insert(other);
			other->mColSet.insert(this);
			Actor()->ColEnter(this, other);
			other->Actor()->ColEnter(other, this);
		}
		else 
		{
			Actor()->ColStay(this, other);
			other->Actor()->ColStay(other, this);
		}
		// 객체와 객체가 소통하는 일반적인 방식.
	}
	else
	{
		if (mColSet.end() != mColSet.find(other))
		{
			mColSet.erase(other);
			other->mColSet.erase(this);
			Actor()->ColExit(this, other);
			other->Actor()->ColExit(other, this);
		}
	}
}

void _ljGameCollider::EndColCheck()
{
	std::set<_ljGameCollider*>::iterator start = mColSet.begin();
	std::set<_ljGameCollider*>::iterator end = mColSet.end();

	for (; start != end; ++start)
	{
		(*start)->mColSet.erase(this);
		(*start)->Actor()->ColExit((*start), this);
		Actor()->ColExit(this, (*start));
	}

	mColSet.clear();
}
