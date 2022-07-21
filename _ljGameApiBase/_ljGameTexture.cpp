#include "_ljGameTexture.h"
#include "_ljGameMacro.h"
#include "_ljGameFile.h"
#include "_ljGameWin.h"

_ljGameTexture::_ljGameTexture()
	: mImage(nullptr)
	, mHBITMAP(nullptr)
	, mOldHBITMAP(nullptr)
{
}
 
_ljGameTexture::~_ljGameTexture()
{
	DeleteObject(mOldHBITMAP);
	DeleteObject(mImage);
}

void _ljGameTexture::TextureSize(const std::wstring& path)
{
	_ljGameFile file = _ljGameFile(path.c_str(), L"rb");

	file.Read(mBitFileHeader);
	file.Read(mBitInfo);
}

int _ljGameTexture::GetTexturePixel(int x, int y)
{
	return GetPixel(mImage, x, y);
}

bool _ljGameTexture::Create(int x, int y)
{
	mImage = CreateCompatibleDC(nullptr);
	mHBITMAP = CreateCompatibleBitmap(_ljGameWin::MainDC(), x, y);

	mOldHBITMAP = (HBITMAP)SelectObject(mImage, mHBITMAP);

	if (nullptr == mImage)
	{
		BOOM;
		return false;
	}

	return true;
}

bool _ljGameTexture::Load(const _ljGameFile& file)
{
	return Load(file.GetPath());
}

bool _ljGameTexture::Load(const std::wstring& path)
{
	mHBITMAP = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == mHBITMAP)
	{
		BOOM;
		return false;
	}

	// ����ִ� HDC�� ������ִ� �Լ�
	mImage = CreateCompatibleDC(nullptr);

	// ����ִ� HDC�� �ε��� �̹��� HDC�� �ٲ۴�. 
	mOldHBITMAP = (HBITMAP)SelectObject(mImage, mHBITMAP);

	if (nullptr == mImage)
	{
		BOOM;
		return false;
	}

	TextureSize(path);

	return true;
}
