#pragma once
#include "_ljGamePath.h"
#include <vector>
#include <filesystem>


/* 
	디렉토리의 개념을 형상화한 클래스. 
*/
class _ljGameFile;
class _ljGameDir : public _ljGamePath
{
public:
	_ljGameDir();
	~_ljGameDir();

public:
	void SetCurrentPath();
	void PathSetting(const char* _Path);
	void PathSetting(const wchar_t* _Path);
	_ljGameFile CreateMyFile(const wchar_t* _FileName);
	bool Move(const wchar_t* _Name);
	void MoveParent();
	bool IsFile(const wchar_t* _FileName);
	std::vector<_ljGameFile> DirToAllFile();
	std::vector<_ljGameFile> DirToAllFile(const wchar_t* _Delimiter);

};

