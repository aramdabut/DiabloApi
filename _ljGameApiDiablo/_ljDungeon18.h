#pragma once
#include <_ljGameScene.h>
#include <_ljGameSound.h>
#include "_ljValueData.h"


class _ljPlayer;
class _ljRandomMap;
class _ljDungeon2;
class _ljDungeon15;
class _ljMonster;
class _ljDungeon18 : public _ljGameScene
{
public:
	_ljDungeon18();
	~_ljDungeon18();

private:
	_ljRandomMap* mMap1;
	_ljRandomMap* mMap2;
	_ljDungeon2* mDungeon2;
	_ljDungeon15* mDungeon15;
	_ljPlayer* mPlayer;
	// 실제 스폰 위치
	TileIndex mNewUpPos;
	TileIndex mNewDownPos;
	int mLevel = 0;
	_ljGameSound::MyGameSoundStream* mBGM;
	class _ljCursor* mMouse;
	class _ljFade* mFade;
	bool mIsFade = false;

public:
	void Loading() override;
	void SceneUpdate() override;
	void Init();
	void MakeMap();
	void Make3RoomsY();
	void Make3RoomsX();
	void SetLevel(int level);
	void SetDungeon2(_ljDungeon2* scene) { mDungeon2 = scene; }
	void SetDungeon15(_ljDungeon15* scene) { mDungeon15 = scene; }
	void ResetPosFrom15();
	void ResetPosFrom2();
	_ljPlayer* GetPlayer() { return mPlayer; }

private:
	void SetPlayer();
	void SetMonster();
	void SpawnMonster();

};