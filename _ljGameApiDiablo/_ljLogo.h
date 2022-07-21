#pragma once
#include <_ljGameActor.h>


class _ljLogo : public _ljGameActor
{
public:
	_ljLogo();
	~_ljLogo();

public:
	void Update() override;
	void DebugRender() override;

};

