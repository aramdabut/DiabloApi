#include "_ljGameTextureMgr.h"
#include "_ljGameTexture.h"
#include "_ljGameImage.h"
#include "_ljGameFile.h"
#include "_ljGameWin.h"



_ljVector _ljGameTextureMgr::mBackDCSize;
HDC _ljGameTextureMgr::mBackDC = nullptr;

_ljGameTextureMgr::_ljGameTextureMgr()
{
}

_ljGameTextureMgr::~_ljGameTextureMgr()
{
	// 모든 텍스쳐 삭제
	std::map<std::wstring, _ljGameTexture*>::iterator iter = mAllTexture.begin();
	std::map<std::wstring, _ljGameTexture*>::iterator endIter = mAllTexture.end();

	for (; iter != endIter; ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	mAllTexture.clear();

	// 모든 이미지 삭제
	std::map<std::wstring, _ljGameImage*>::iterator ImgStart = mAllImage.begin();
	std::map<std::wstring, _ljGameImage*>::iterator ImgEnd = mAllImage.end();

	for (; ImgStart != ImgEnd; ++ImgStart)
	{
		if (nullptr != ImgStart->second)
		{
			delete ImgStart->second;
			ImgStart->second = nullptr;
		}
	}
	mAllImage.clear();

	// 백버퍼 삭제
	if (nullptr != mBackBufferTexture)
	{
		delete mBackBufferTexture;
		mBackBufferTexture = nullptr;
	}
}

void _ljGameTextureMgr::Init()
{
	mBackBufferTexture = new _ljGameTexture();

	// 백버퍼 만들기 실패
	if (false == mBackBufferTexture->Create(
		_ljGameWin::MainWindow()->Size().IntX(), _ljGameWin::MainWindow()->Size().IntY()))
	{
		BOOM;
	}

	mBackDC = mBackBufferTexture->TextureDC();
	mBackDCSize = _ljGameWin::MainWindow()->Size();
}

_ljGameTexture* _ljGameTextureMgr::LoadTexture(const _ljGameFile& file)
{
	_ljGameTexture* newTex = new _ljGameTexture();

	if (false == newTex->Load(file.GetPath()))
	{
		BOOM;
	}

	newTex->Name(file.FileName().c_str());
	mAllTexture.insert(std::map<std::wstring, _ljGameTexture*>::value_type(file.FileName(), newTex));

	return newTex;
}

_ljGameTexture* _ljGameTextureMgr::CreateTexture(const wchar_t* name, int x, int y)
{
	_ljGameTexture* newTex = new _ljGameTexture();

	if (false == newTex->Create(x, y))
	{
		BOOM;
	}

	newTex->Name(name);
	mAllTexture.insert(std::map<std::wstring, _ljGameTexture*>::value_type(name, newTex));

	return newTex;
}

_ljGameTexture* _ljGameTextureMgr::FindTexture(const std::wstring& key)
{
	std::map<std::wstring, _ljGameTexture*>::iterator texIter = mAllTexture.find(key);

	if (mAllTexture.end() == texIter)
	{
		return nullptr;
	}

	if (nullptr == texIter->second)
	{
		BOOM;
	}

	return texIter->second;
}

_ljGameImage* _ljGameTextureMgr::CreateImage(const wchar_t* texName, unsigned int x, unsigned int y)
{
	_ljGameTexture* findTex = FindTexture(texName);


	if (nullptr == findTex || nullptr != FindImage(findTex->Name()))
	{
		BOOM;
		return nullptr;
	}

	_ljGameImage* newImage = new _ljGameImage();

	newImage->Cut(findTex, x, y);

	mAllImage.insert(std::map<std::wstring, _ljGameImage*>::value_type(findTex->Name(), newImage));

	return newImage;
}

_ljGameImage* _ljGameTextureMgr::FindImage(const std::wstring& key)
{
	std::map<std::wstring, _ljGameImage*>::iterator findImage = mAllImage.find(key);

	if (mAllImage.end() == findImage)
	{
		return nullptr;
	}

	return findImage->second;
}

