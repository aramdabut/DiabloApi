#pragma once
#include <map>
#include <Windows.h>
#include "_ljGameMath.h"

class _ljGameTexture;
class _ljGameImage;
class _ljGameFile;
class _ljGameTextureMgr 
{
	/* �� ������ �̱���(singleton) */
public:
	// =============== static function ===============
	static _ljGameTextureMgr& Inst()
	{
		static _ljGameTextureMgr textureInst;
		return textureInst;
	}
	static const _ljVector& BackDCSize() { return mBackDCSize; }
	static const HDC& BackDC() { return mBackDC; }

private:
	_ljGameTextureMgr();
	~_ljGameTextureMgr();

private:
	/* BackBuffer */
	static _ljVector mBackDCSize;
	static HDC mBackDC;

	/* �ε��� �̹���(�ؽ���) ���� */
	std::map<std::wstring, _ljGameTexture*> mAllTexture;


	/* �ε��� �̹���(�ؽ���)���� ������ �̹��� ���� */
	std::map<std::wstring, _ljGameImage*> mAllImage;

	_ljGameTexture* mBackBufferTexture;

public:
	void Init();

public:
	_ljGameTexture* LoadTexture(const _ljGameFile& file);
	_ljGameTexture* CreateTexture(const wchar_t* name, int x, int y);

	_ljGameTexture* FindTexture(const std::wstring& key);

	_ljGameImage* CreateImage(const wchar_t* texName, unsigned int x, unsigned int y);
	_ljGameImage* FindImage(const std::wstring& key);

};

