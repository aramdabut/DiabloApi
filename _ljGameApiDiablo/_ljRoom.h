#pragma once
#include "_ljValueData.h"
#include <_ljGameMath.h>

class _ljRoom
{
	friend class _ljDungoen15;
	friend class _ljDungoen18;
	friend class _ljDungoen2;
	friend class _ljTestScene;

public:
	_ljRoom();
	~_ljRoom();

	_ljVector LeftTop() const;
	_ljVector RightTop() const;
	_ljVector LeftDown() const;
	_ljVector RightDown() const;

public:
	_ljVector Pos;
	_ljVector Size;

	bool mIsStartRoom = false;
	bool mIsButcher = false;
};

