#pragma once
#include <_ljGameActor.h>

class _ljChest : public _ljGameActor
{
public:
	_ljChest();
	~_ljChest();

public:
	void DebugRender() override;

private:
	// Skeleton : 20 %
	// Gold : 22.5%
	// Item : 7.5%
	// Nothing : 50 %
	float mOpenRate;
};

