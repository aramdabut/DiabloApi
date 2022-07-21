#pragma once
#include <_ljGameRenderer.h>

class _ljGameTexture;
class _ljPlayer;
class _ljLevel : public _ljGameRenderer
{
public:
	_ljLevel();
	~_ljLevel();

public:
	void Render() override;
	void SetPlayer(_ljPlayer* player);

private:
	_ljPlayer* mPlayer;
	int start = 0;
};

