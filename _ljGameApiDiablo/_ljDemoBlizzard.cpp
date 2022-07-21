#include "_ljDemoBlizzard.h"
#include <_ljGameWin.h>
#include <_ljGameInput.h>
#include "_ljPlayer.h"
#include "_ljTitleBlizzard.h"


_ljDemoBlizzard::_ljDemoBlizzard()
{
}

_ljDemoBlizzard::~_ljDemoBlizzard()
{
}

void _ljDemoBlizzard::Loading()
{
	mOpening = new _ljTitleBlizzard();
}

void _ljDemoBlizzard::SceneUpdate()
{
	if (true == mOpening->IsOpeningOver())
	{
		SetCurScene(L"DemoDiablo");
	}

	if (true == _ljGameInput::Down(L"GoToNextScene") || true == _ljGameInput::Down(L"LMOUSEBTN"))
	{
		SetCurScene(L"DemoDiablo");
		HSS->Stop();
	}
}

void _ljDemoBlizzard::Init()
{
	HSS = _ljGameSound::SoundPlay(L"dlogo.mp3");
}
