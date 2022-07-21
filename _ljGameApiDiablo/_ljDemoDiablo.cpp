#include "_ljDemoDiablo.h"
#include <_ljGameInput.h>
#include "_ljTitleDiablo.h"

_ljDemoDiablo::_ljDemoDiablo()
{
}

_ljDemoDiablo::~_ljDemoDiablo()
{
}

void _ljDemoDiablo::Loading()
{
	mDiablo = new _ljTitleDiablo();
}

void _ljDemoDiablo::SceneUpdate()
{
	if (true == _ljGameInput::Down(L"GoToNextScene") || true == _ljGameInput::Down(L"LMOUSEBTN"))
	{
		SetCurScene(L"Title");
	}
}

void _ljDemoDiablo::Init()
{
	HSS = _ljGameSound::SoundPlay(L"dintro.mp3");
}
