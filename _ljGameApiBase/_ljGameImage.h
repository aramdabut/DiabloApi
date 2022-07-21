#pragma once
#include <vector>
#include "_ljGameTexture.h"

/* ���� : �̹��� ����(Texture)���� ����� �ϳ��� �̹��� */
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

