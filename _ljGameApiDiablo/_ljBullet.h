#pragma once
#include <_ljGameMacro.h>
#include <_ljGameActor.h>


class _ljBullet : public _ljGameActor
{
public:
	_ljBullet();
	_ljBullet(_ljVector cursor);
	~_ljBullet();

private:
	float Time;

private:
	_ljVector mDir;

public:
	void Update() override;
	void DebugRender() override;

};

