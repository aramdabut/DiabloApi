#include "_ljCursor.h"
#include <_ljGameWin.h>

_ljCursor::_ljCursor()
{
	ShowCursor(false);

	mMouseRenderer = CreateRenderer<_ljGameRenderer>(LO_MAX);
	mMouseRenderer->Image(L"NormalCursor.bmp");
	mMouseRenderer->SubSize({ 33, 33 });
	mMouseRenderer->SubPos({ 16, 16 });

	mMouseRenderer->TransColor(255, 255, 255);
	mMouseRenderer->SetRenderStyle(RS_TRANS);
	mMouseRenderer->On();
}

_ljCursor::~_ljCursor()
{
}

void _ljCursor::Update()
{
	Pos(_ljGameWin::MainWindow()->MousePos() + CamPos());
}
