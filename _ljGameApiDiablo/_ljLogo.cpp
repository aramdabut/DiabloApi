#include "_ljLogo.h"
#include <_ljGameRenderer.h>
#include <_ljGameMacro.h>


_ljLogo::_ljLogo()
{
	_ljGameRenderer* title = CreateRenderer<_ljGameRenderer>(LO_BG);
}

_ljLogo::~_ljLogo()
{
}

void _ljLogo::Update()
{
}

void _ljLogo::DebugRender()
{
}
