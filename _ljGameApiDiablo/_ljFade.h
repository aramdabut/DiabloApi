#pragma once
#include <_ljGameRenderer.h>

class _ljFade : public _ljGameRenderer
{
public:
	_ljFade();
	~_ljFade();
	bool StartFadeOut();

private:
	_ljGameRenderer* mRenderer;
	float mTime;
	float mGap;
	int mTimer;
	int mBright;
};

