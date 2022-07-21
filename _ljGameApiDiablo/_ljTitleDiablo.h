#pragma once
#include <_ljGameActor.h>
#include <_ljGameSound.h>


class _ljGameAniRenderer;
class _ljTitleDiablo : public _ljGameActor
{
public:
	_ljTitleDiablo();
	~_ljTitleDiablo();

private:
	_ljGameAniRenderer* mTitle;
	_ljGameAniRenderer* mFire;
	_ljGameSound::MyGameSoundStream* HSS;

public:
	void DebugRender() override;

};

