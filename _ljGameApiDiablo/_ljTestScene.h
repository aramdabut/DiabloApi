#pragma once
#include <_ljGameScene.h>
#include <_ljGameSound.h>
#include "_ljValueData.h"


class _ljPlayer;
class _ljRandomMap;
class _ljDungeon2;
class _ljDungeon15;
class _ljMonster;
class _ljCursor;
class _ljTestScene : public _ljGameScene
{
public:
	_ljTestScene();
	~_ljTestScene();

	void Loading() override;
	void SceneUpdate() override;
	void Init();

	void MakeMap();

	void Make3RoomsY();
	void Make3RoomsX();


	void SetLevel(int level);
	void SetDungeon15(_ljDungeon15* scene) { mDungeon15 = scene; }
	void ResetPos();
	_ljPlayer* GetPlayer() { return mPlayer; }
private:
	void SetPlayer();
	void SetMonster();
	void SpawnMonster();

private:
	_ljRandomMap* mMap1;
	_ljRandomMap* mMap2;

	// Dungeon2* mDungeon2;
	_ljDungeon15* mDungeon15;
	_ljPlayer* mPlayer;

	// ���� ���� ��ġ
	TileIndex mNewUpPos;
	TileIndex mNewDownPos;

	int mLevel = 0;

	_ljGameSound::MyGameSoundStream* mBGM;

	// std::vector<Monster*> mMonsterPool;
	_ljCursor* mMouse;

	class _ljFade* mFade;

	bool mIsFade = false;
};