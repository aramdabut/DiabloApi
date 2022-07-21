#include "_ljGamePath.h"
#include <atlstr.h>
#include "_ljGameFile.h"
#include "_ljGameDir.h"

// HANDLE

_ljGamePath::_ljGamePath()
{
}

_ljGamePath::~_ljGamePath()
{
}

void _ljGamePath::PathSetting(const char* _Path)
{
	PathSetting(CA2W(_Path).m_psz);
}

void _ljGamePath::PathSetting(const wchar_t* _Path)
{
	mPath = _Path;
}
