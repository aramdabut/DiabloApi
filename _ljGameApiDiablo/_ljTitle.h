#pragma once
#include <_ljGameScene.h>
#include <_ljGameActor.h>
#include <_ljGameSound.h>


class _ljDemoDiablo;
class _ljTitle : public _ljGameScene
{
public:
	_ljTitle();
	~_ljTitle();

private:
	_ljGameActor* mMain;
	_ljGameRenderer* mMainRenderer;
	_ljGameAniRenderer* mFire;
	_ljGameAniRenderer* mStar1;
	_ljGameAniRenderer* mStar2;

	_ljGameSound::MyGameSoundStream* SSselect;
	_ljGameSound::MyGameSoundStream* SSmove;
	_ljGameSound::MyGameSoundStream* HSS;

	bool mSelectOn = false;;
	bool mMoveOn1 = false;
	bool mMoveOn2 = false;
	bool mMoveOn3 = false;
	bool mMoveOn4 = false;
	bool mMoveOn5 = false;

	int mStartX;
	int mStartY;
	int mGapY = 40;
	int mGapX = 360;
	int mStartGap = 40;

	_ljVector mMousePos;
	_ljDemoDiablo* mOpening;

	class _ljCursor* mMouse;
	class _ljFade* mFade;

	bool mIsFade = false;
	bool mIsNext = false;

public:
	void Loading() override;
	void SceneUpdate() override;
	void Init();
	void MakeMap() {}
	void SetOpening(_ljDemoDiablo* dia) { mOpening = dia; }

};

