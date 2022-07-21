#pragma once
#include <_ljGameActor.h>


class _ljGameAniRenderer;
class _ljTitleBlizzard : public _ljGameActor
{
public:
	_ljTitleBlizzard();
	~_ljTitleBlizzard();

private:
	_ljGameAniRenderer* mAnimationRenderer;
	_ljGameRenderer* mBack;

public:
	void Update() override;
	void DebugRender() override;

	bool IsOpeningOver();

};

