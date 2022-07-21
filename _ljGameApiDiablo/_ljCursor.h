#pragma once
#include <_ljGameActor.h>


class _ljCursor : public _ljGameActor
{
public:
	_ljCursor();
	~_ljCursor();

public:
	_ljGameRenderer* mMouseRenderer;

public:
	void Update();

};

