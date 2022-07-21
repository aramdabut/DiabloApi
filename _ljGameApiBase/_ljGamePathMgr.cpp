#include "_ljGamePathMgr.h"
#include <atlstr.h>
#include "_ljGameFile.h"
#include "_ljGameDir.h"


_ljGamePathMgr::_ljGamePathMgr()
{
}


_ljGamePathMgr::~_ljGamePathMgr()
{
}


void _ljGamePathMgr::PathSetting(const char* _Path)
{
	PathSetting(CA2W(_Path).m_psz);
}


void _ljGamePathMgr::PathSetting(const wchar_t* _Path)
{
	mPath = _Path;
}
