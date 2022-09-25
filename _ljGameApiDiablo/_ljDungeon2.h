#pragma once
#include <_ljGameScene.h>
#include <_ljGameSound.h>


class _ljRandomMap;
class _ljPlayer;
class _ljDungeon18;
class _ljDungeon2 : public _ljGameScene
{
public:
	_ljDungeon2();
	~_ljDungeon2();

private:
	_ljRandomMap* mMap1;
	_ljRandomMap* mMap2;
	_ljPlayer* mPlayer;
	_ljDungeon18* mDungeon18;
	_ljGameSound::MyGameSoundStream* mBGM;
	class _ljCursor* mMouse;
	class _ljFade* mFade;
	bool mIsFade = false;

public:
	void Loading() override;
	void SceneUpdate() override;

public:
	void MakeMap();
	void Make3RoomsY();
	void Make3RoomsX();
	void SetLevel(int level);
	void SetDungeon18(_ljDungeon18* scene) { mDungeon18 = scene; }
	void ResetPos();
	_ljPlayer* GetPlayer() { return mPlayer; }
	void SpawnMonsters();
	void Init();
	void ResetMap();

private:
	void SetPlayer();

};

// L"Image"
// L"Sound"