#pragma once
#include <_ljGameWin.h>

class _ljClient : public _ljGameWin::_ljLoopUpdater
{
public:
	_ljClient();
	~_ljClient();

public:
	virtual void GameInit() override;
	virtual void GameUpdate() override;

public:
	MyRect Rect;

};


