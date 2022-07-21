#pragma once
#include <_ljGameScene.h>
#include <_ljGameSound.h>
#include "_ljValueData.h"


class _ljPlayer;
class _ljRandomMap;
class _ljDungeon2;
class _ljDungeon18;
class _ljMonster;
class _ljTestScene;
class _ljDungeon15 : public _ljGameScene
{
public:
	_ljDungeon15();
	~_ljDungeon15();

private:
	_ljRandomMap* mMap1;
	_ljRandomMap* mMap2;
	_ljDungeon18* mDungeon18;
	_ljTestScene* mTestScene;
	_ljPlayer* mPlayer;
	// 실제 스폰 위치
	TileIndex mNewUpPos;
	TileIndex mNewDownPos;
	int mLevel = 0;
	_ljGameSound::MyGameSoundStream* mBGM;
	class _ljCursor* mMouse;
	bool mIsFade = false;
	class _ljFade* mFade;

public:
	void Loading() override;
	void SceneUpdate() override;
	
public:
	void Init();
	void MakeMap();
	void Make3RoomsY();
	void Make3RoomsX();
	void SetLevel(int level);
	void SetDungeon18(_ljDungeon18* scene) { mDungeon18 = scene; }
	void SetTestScene(_ljTestScene* scene) { mTestScene = scene; }
	void ResetPosFromTest();
	void ResetPosFrom18();
	_ljPlayer* GetPlayer() { return mPlayer; }

private:
	void SetPlayer();
	void SetMonster();
	void SpawnMonster();

};