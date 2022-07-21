#pragma once
#include <_ljGameScene.h>
#include <_ljGameSound.h>


class _ljTitleBlizzard;
class _ljDemoBlizzard : public _ljGameScene
{
public:
	_ljDemoBlizzard();
	~_ljDemoBlizzard();

private:
	_ljTitleBlizzard* mOpening;
	_ljGameSound::MyGameSoundStream* HSS;

public:
	void Loading() override;
	void SceneUpdate() override;

public:
	void Init();
	void MakeMap() {}

};

