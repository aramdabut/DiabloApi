#include "_ljGameFile.h"
#include <atlstr.h>


_ljGameFile::_ljGameFile(const wchar_t* _Path, const wchar_t* _Mode) : mFile(nullptr)
{
	Open(_Path, _Mode);
}

_ljGameFile::_ljGameFile() : mFile(nullptr)
{
}

_ljGameFile::_ljGameFile(const _ljGameFile& other)
{
	Copy(other);
}

_ljGameFile::_ljGameFile(const wchar_t* _FileName) : mFile(nullptr)
{
	// mFileName = _FileName;
	PathSetting(_FileName);
}

_ljGameFile::~_ljGameFile()
{
	Close();
}

void _ljGameFile::PathSetting(const char* _Path)
{
	PathSetting(CA2W(_Path).m_psz);
}

void _ljGameFile::PathSetting(const wchar_t* _Path)
{
	mPath = _Path;
	mFileName = mPath;
	size_t LastFolderIndex = mFileName.find_last_of(L"\\");
	mFileName = mFileName.replace(0, LastFolderIndex + 1, L"");

	mExt = mFileName;
	LastFolderIndex = mExt.find_last_of(L".");
	mExt = mExt.replace(0, LastFolderIndex + 1, L"");
}

void _ljGameFile::PathSetting(const std::wstring& path)
{
	PathSetting(path.c_str());
}

bool _ljGameFile::Open()
{
	return Open(mPath.c_str(), mOpenMode.c_str());
}

bool _ljGameFile::Open(const wchar_t* _Path, const wchar_t* _Mode)
{
	PathSetting(_Path);
	mOpenMode = _Mode;
	_wfopen_s(&mFile, mPath.c_str(), mOpenMode.c_str());

	if (nullptr == mFile)
	{
		assert(false);
		return false;
	}

	return true;
}

void _ljGameFile::Close() 
{
	if (nullptr != mFile)
	{
		fclose(mFile);
		mFile = nullptr;
	}
}

void _ljGameFile::Copy(const _ljGameFile& other)
{
	PathSetting(other.mPath);
	mFile = other.mFile;
}
