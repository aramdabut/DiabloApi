#include "_ljBullet.h"
#include <_ljGameScene.h>
#include <_ljGameInput.h>
#include <_ljGameTime.h>
#include <_ljGameRenderer.h>
#include <_ljGameMacro.h>


_ljBullet::_ljBullet() : Time(0.0f)
{
	//_ljGameRenderer* newRender = CreateRenderer<_ljGameRenderer>(LO_BULLET);
	//newRender->SubSize({ 30, 30 });
}

_ljBullet::_ljBullet(_ljVector cursor) : Time(0.0f), mDir(cursor)
{
	//_ljGameRenderer* newRender = CreateRenderer<_ljGameRenderer>(LO_BULLET);
	//newRender->SubSize({ 30, 30 });
}

_ljBullet::~_ljBullet()
{
}

void _ljBullet::Update()
{
	Time += _ljGameTime::DeltaTime();

	if (Time >= 1)
	{
		KillThis();
	}

	Move(mDir * _ljGameTime::DeltaTime() * 500.f);
}

void _ljBullet::DebugRender()
{
}
