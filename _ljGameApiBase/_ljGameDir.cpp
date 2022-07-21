#include "_ljGameDir.h"
#include <Windows.h>
#include <atlstr.h>
#include "_ljGameFile.h"
//#include <filesystem> // 컴파일러마다 다르다. 
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem::v1;


_ljGameDir::_ljGameDir()
{
	wchar_t directory[1024];

	if (0 == GetCurrentDirectoryW(1024, directory))
	{
		BOOM;
	}

	PathSetting(directory);
}

_ljGameDir::~_ljGameDir()
{
}

bool _ljGameDir::Move(const wchar_t* _Name)
{
	for (const auto& entry : fs::directory_iterator(mPath))
	{
		if (entry.path() == mPath + L"\\" + _Name)
		{
			mPath.append(L"\\");
			mPath.append(_Name);

			return true;
		}
	}

	return false;
}

void _ljGameDir::MoveParent()
{
	size_t LastFolderIndex = mPath.find_last_of(L"\\");
	mPath = mPath.replace(LastFolderIndex, mPath.size(), L"");
}

bool _ljGameDir::IsFile(const wchar_t* _FileName)
{
	for (const auto& entry : fs::directory_iterator(mPath))
	{
		if (entry.path() == mPath + L"\\" + _FileName)
		{
			return true;
		}
	}

	return false;
}

std::vector<_ljGameFile> _ljGameDir::DirToAllFile()
{
	if (false == IsExist(mPath.c_str()))
	{
		BOOM;
	}

	//std::experimental::filesystem::v1::create_directories

	std::wstring path = mPath;
	std::vector<_ljGameFile> tempFiles;

	for (const auto& entry : fs::directory_iterator(mPath))
	{
		_ljGameFile tempFile = _ljGameFile(entry.path().c_str());

		tempFiles.push_back(tempFile);
	}

	// std::cout << entry.path() << std::endl;

	return tempFiles;
}

std::vector<_ljGameFile> _ljGameDir::DirToAllFile(const wchar_t* _Delimiter)
{

	if (_Delimiter == L"*.*")
	{
		return DirToAllFile();
	}
	else if (L'*' == _Delimiter[0])
	{
		std::wstring tempDeli = _Delimiter;
		
		size_t LastFolderIndex = tempDeli.find_last_of(L".");

		std::wstring ext = tempDeli.replace(0, LastFolderIndex + 1, L"");

		std::vector<_ljGameFile> tempFiles = DirToAllFile();
		std::vector<_ljGameFile> resultFiles;
		
		for (int i = 0; i < (int)tempFiles.size(); ++i)
		{
			std::wstring tempPath = tempFiles[i].GetPath();
			size_t LastFolderIndex = tempPath.find_last_of(L".");
			std::wstring tempExt = tempPath.replace(0, LastFolderIndex + 1, L"");

			if (ext == tempExt)
			{
				resultFiles.push_back(tempFiles[i]);
			}
		}

		return resultFiles;
	}
	else
	{
		for (const auto& entry : fs::directory_iterator(mPath))
		{
			if (entry.path() == mPath + L"\\" + _Delimiter)
			{
				std::vector<_ljGameFile> temp;
				_ljGameFile tempFile = _ljGameFile(_Delimiter);
				temp.push_back(tempFile);
				return temp;
			}
		}
	}

	return std::vector<_ljGameFile>();
}

void _ljGameDir::SetCurrentPath()
{
	mPath = fs::current_path();
}

void _ljGameDir::PathSetting(const char* _Path)
{
	PathSetting(CA2W(_Path).m_psz);
}

void _ljGameDir::PathSetting(const wchar_t* _Path)
{
	// 이 함수를 아직 믿는건 아니다.
	if (0 != (FILE_ATTRIBUTE_DIRECTORY & GetFileAttributesW(_Path)))
	{
		mPath = _Path;
		return;
	}

	mPath = _Path;
	size_t LastFolderIndex = mPath.find_last_of(L"\\");
	mPath.replace(LastFolderIndex, mPath.size() - 1, L"");
}

_ljGameFile _ljGameDir::CreateMyFile(const wchar_t* _FileName)
{
	if (false == IsExist(mPath.c_str()))
	{
		return _ljGameFile();
	}

	std::wstring tempPath = mPath + L"\\" + _FileName;

	if (true == IsFile(tempPath.c_str()))
	{
		return _ljGameFile(_FileName);
	}

	//std::experimental::filesystem::v1::create_directories

	_ljGameFile tempFile = _ljGameFile(_FileName);

	FILE* file = tempFile.GetFile();

	if (_wfopen_s(&file, _FileName, L"wb") != NULL)
	{
		std::wcout << mPath << std::endl;
	}

	// fclose(file);

	return tempFile;
}
