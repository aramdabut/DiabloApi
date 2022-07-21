#pragma once
#include <string>
#include <assert.h>

#define BOOM assert(false)

/*
	加己 > C/C++ > 傈贸府扁

	_DEBUG;_CONSOLE;%(PreprocessorDefinitions)
	NDEBUG;_CONSOLE;%(PreprocessorDefinitions)

	UNICODE;_UNICODE; %(PreprocessorDefinitions); X64;DEBUGMODE;
	UNICODE;_UNICODE; %(PreprocessorDefinitions); X64;RELEASEMODE;

*/


//≮
#ifdef UNICODE
namespace std
{
	typedef std::wstring tstring;
}
#else
namespace std
{
	typedef std::string tstring;
}
#endif


class _ljGamePathMgr
{
public:
	_ljGamePathMgr();
	~_ljGamePathMgr();

protected:
	std::wstring mPath;

public:
	static bool IsExist(const wchar_t* _Path)
	{
		if (0 != _waccess_s(_Path, 0))
		{
			return false;
		}
		return true;
	}

	std::wstring GetPath() const { return mPath; }

public:
	void PathSetting(const char* _Path);
	void PathSetting(const wchar_t* _Path);

};

