#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include "_ljGameMacro.h"
#include "_ljGameMath.h"


class _ljGameWin
{
public:
	class _ljLoopUpdater
	{
	public:
		virtual void GameInit() = 0;
		virtual void GameUpdate() = 0;
	};

private:
	class _ljGameDefaultWin
	{
	public:
		_ljGameDefaultWin();
		~_ljGameDefaultWin();
	};

public:
	static LRESULT __stdcall MsgFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static bool IsRegistered(const wchar_t* className);
	static void RegisterWindowClass(const WNDCLASSEXW& wcex);
	static _ljGameWin* FindWindowClass(const wchar_t* winName);
	static _ljGameWin* CreateWindowClass(const wchar_t* winName, const wchar_t* className = L"DefaultWindowClass", bool bShow = true);
	static int BaseLoop(_ljLoopUpdater& loopObj);
	static _ljGameWin* MainWindow();
	static HDC MainDC() { return mMainDC; }
	static HWND MainHWND() { return mMainWindow->mHWnd; }

private:
	static void DestroyWindowClass(HWND hWnd);

public:
	void Show();
	_ljVector Size() { return mSize; }
	void Size(int x, int y);
	void Size(_ljVector size);
	_ljVector MousePos();

public:
	static _ljGameDefaultWin Construct;

private:
	static std::map<std::wstring, WNDCLASSEXW> mClassMap;
	static std::map<std::wstring, _ljGameWin*> mWinMap;
	static std::map<HWND, _ljGameWin*> mHWndMap;
	static _ljGameWin* mMainWindow;
	static HDC mMainDC;
	std::wstring mName;
	HWND mHWnd;
	int mStyle;
	_ljVector mSize;

private:
	_ljGameWin();
	_ljGameWin(HWND hWnd);
	virtual ~_ljGameWin();

};

