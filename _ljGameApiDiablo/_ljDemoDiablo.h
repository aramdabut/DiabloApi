#pragma once
#include <_ljGameScene.h>
#include <_ljGameSound.h>


class _ljTitleDiablo;
class _ljDemoDiablo : public _ljGameScene
{
public:
	_ljDemoDiablo();
	~_ljDemoDiablo();

public:
	void Loading() override;
	void SceneUpdate() override;

public:
	void Init();
	void MakeMap() {}

public:
	_ljGameSound::MyGameSoundStream* GetSound() { return HSS; }

private:
	_ljTitleDiablo* mDiablo;
	_ljGameSound::MyGameSoundStream* HSS;

};

