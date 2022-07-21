#pragma once
#include <_ljGameRenderer.h>

class _ljGameTexture;
class _ljPlayer;
class _ljStat : public _ljGameRenderer
{
public:
	_ljStat();
	~_ljStat();

	void Render() override;

	void SetPlayer(_ljPlayer* player);

	void ClassRender();
	void StatRender();
	void LevelUpRender();

private:
	_ljPlayer* mPlayer;
	int space;

	_ljGameActor* mRed;
	_ljGameRenderer* mRedRenderer;

};

