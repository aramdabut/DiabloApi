#pragma once
#include <_ljGameScene.h>

class _ljPlayer;
class _ljRandomMap;
class _ljTestPlayerScene : public _ljGameScene
{
public:
	_ljTestPlayerScene();
	~_ljTestPlayerScene();

	void Loading() override;
	void SceneUpdate() override;
	void MakeMap();
	void Make3RoomsX();
	void Make3RoomsY();


private:
	_ljPlayer* mPlayer;
	_ljRandomMap* mMap;
};

