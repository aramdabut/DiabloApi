#pragma once
#include <string>
#include <Windows.h>
#include "_ljGameMath.h"



/* �׳� �̹��� ���� �ϳ��� ���� �Դϴ�. */

class _ljGameFile;
class _ljGameTexture
{
private:
	std::wstring mName;
	HDC mImage;
	HBITMAP mHBITMAP;
	HBITMAP mOldHBITMAP;
	BITMAPFILEHEADER mBitFileHeader;
	BITMAPINFOHEADER mBitInfo;

public:
	_ljGameTexture();
	~_ljGameTexture();

public:
	void TextureSize(const std::wstring& path);
	int GetTexturePixel(int x, int y);

	bool Create(int x, int y);

	bool Load(const _ljGameFile& file);
	bool Load(const std::wstring& path);

	HDC TextureDC() { return mImage; }

	_ljVector Size() 
	{
		return { (float)mBitInfo.biWidth, (float)mBitInfo.biHeight };
	}

	void Name(const wchar_t* name) { mName = name; }
	std::wstring Name() { return mName; }

};

