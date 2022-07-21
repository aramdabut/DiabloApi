#pragma once
#include <vector>
#include "_ljGameTexture.h"

/* 개념 : 이미지 파일(Texture)에서 추출된 하나의 이미지 */
class _ljGameTextureMgr;
class _ljGameImage
{
	friend _ljGameTextureMgr;

public:
	_ljGameImage();
	~_ljGameImage();

public:
	void Cut(_ljGameTexture* texture, int x, int y);

public:
	MyRect GetRect(int index) { return mAllCutData[index]; }
	HDC ImageHDC() { return mDC; }
	size_t CutCount() { return mAllCutData.size(); }

private:
	_ljGameTexture* mTexture;
	HDC mDC;
	std::vector<MyRect> mAllCutData;

public:
	_ljGameTexture* Texture() 
	{
		return mTexture;
	}

};

