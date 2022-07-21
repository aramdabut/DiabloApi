#include "_ljGameWin.h"
#include "_ljGameTime.h"
#include "_ljGameInput.h"
#include "_ljGameSound.h"


std::map<std::wstring, WNDCLASSEXW> _ljGameWin::mClassMap;
std::map<std::wstring, _ljGameWin*> _ljGameWin::mWinMap;
std::map<HWND, _ljGameWin*> _ljGameWin::mHWndMap;
_ljGameWin* _ljGameWin::mMainWindow = nullptr;
HDC _ljGameWin::mMainDC;


_ljGameWin::_ljGameDefaultWin _ljGameWin::Construct = _ljGameWin::_ljGameDefaultWin();


_ljGameWin::_ljGameWin() {}
_ljGameWin::_ljGameWin(HWND hWnd) : mHWnd(hWnd)
{
	mMainDC = GetDC(hWnd);
}
_ljGameWin::~_ljGameWin() {}


void _ljGameWin::DestroyWindowClass(HWND hWnd)
{
	std::map<HWND, _ljGameWin*>::iterator FindIter = mHWndMap.find(hWnd);

	if (mHWndMap.end() == FindIter)
	{
		BOOM;
	}

	std::map<std::wstring, _ljGameWin*>::iterator NameFindIter = mWinMap.find(FindIter->second->mName);

	delete FindIter->second;
	mWinMap.erase(NameFindIter);
	mHWndMap.erase(FindIter);
}

LRESULT __stdcall _ljGameWin::MsgFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		DestroyWindowClass(hWnd);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}


bool _ljGameWin::IsRegistered(const wchar_t* className)
{
	std::map<std::wstring, WNDCLASSEXW>::iterator FindIter = mClassMap.find(className);

	if (mClassMap.end() == FindIter)
	{
		return false;
	}

	return true;
}


void _ljGameWin::RegisterWindowClass(const WNDCLASSEXW& wcex)
{
	if (true == IsRegistered(wcex.lpszClassName) || 0 == RegisterClassExW(&wcex))
	{
		BOOM;
	}

	mClassMap.insert(std::map<std::wstring, WNDCLASSEXW>::value_type(wcex.lpszClassName, wcex));
}


_ljGameWin* _ljGameWin::FindWindowClass(const wchar_t* winName)
{
	std::map<std::wstring, _ljGameWin*>::iterator FindIter = mWinMap.find(winName);

	if (mWinMap.end() == FindIter)
	{
		return nullptr;
	}

	return FindIter->second;
}


_ljGameWin* _ljGameWin::CreateWindowClass(const wchar_t* winName
										, const wchar_t* className /*= L"DefaultWindowClass"*/
										, bool bShow /* = true*/)
{
	if (nullptr != FindWindowClass(winName) || false == IsRegistered(className))
	{
		BOOM;
	}

	HWND hWnd = CreateWindowW(className, winName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, 0, nullptr);

	if (0 == hWnd)
	{
		return FALSE;
	}

	_ljGameWin* newWin = new _ljGameWin(hWnd);
	newWin->mStyle = WS_OVERLAPPEDWINDOW;
	newWin->mName = winName;
	mWinMap.insert(std::map<std::wstring, _ljGameWin*>::value_type(winName, newWin));
	mHWndMap.insert(std::map<HWND, _ljGameWin*>::value_type(hWnd, newWin));

	if (1 == mWinMap.size())
	{
		mMainWindow = newWin;
	}

	if (true == bShow)
	{
		newWin->Show();
	}

	return newWin;
}

_ljGameWin* _ljGameWin::MainWindow()
{
	return mMainWindow;
}

/* ================================= MESSAGE CALL ================================= */


int _ljGameWin::BaseLoop(_ljLoopUpdater& loopObj)
{
	MSG msg;

	loopObj.GameInit();

	while (0 != mWinMap.size())
	{
		if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
		/* 게임로직 */
			_ljGameTime::Update();
			_ljVector::DirUpdate();
			_ljGameInput::Update();
			_ljGameSound::SoundUpdate();
			loopObj.GameUpdate();
		}

	}

	_ljGameSound::SoundEnd();

	return (int)msg.wParam;
}

void _ljGameWin::Show()
{
	ShowWindow(mHWnd, SW_SHOW);
}

void _ljGameWin::Size(int x, int y)
{
	mSize = { (float)x, (float)y };

	RECT rc = { 0, 0, mSize.IntX(), mSize.IntY() };

	HMENU menu = GetMenu(mHWnd);

	if (nullptr == menu)
	{
		AdjustWindowRect(&rc, mStyle, FALSE);
	}
	else
	{
		AdjustWindowRect(&rc, mStyle, TRUE);
	}

	SetWindowPos(mHWnd, 0, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
}

void _ljGameWin::Size(_ljVector size)
{
	mSize = size;

	RECT rc = { 0, 0, mSize.IntX(), mSize.IntY() };

	HMENU menu = GetMenu(mHWnd);

	if (nullptr == menu)
	{
		AdjustWindowRect(&rc, mStyle, FALSE);
	}
	else
	{
		AdjustWindowRect(&rc, mStyle, TRUE);
	}

	SetWindowPos(mHWnd, 0, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

}

_ljVector _ljGameWin::MousePos()
{
	POINT Point;

	GetCursorPos(&Point);
	ScreenToClient(mHWnd, &Point);

	_ljVector ReturnPos;

	ReturnPos.X = (float)Point.x;
	ReturnPos.Y = (float)Point.y;

	return ReturnPos;
}

_ljGameWin::_ljGameDefaultWin::_ljGameDefaultWin()
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = _ljGameWin::MsgFunc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = 0;
	wcex.hIcon = 0;/*LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTAPI))*/;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 4);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"DefaultWindowClass";
	wcex.hIconSm = 0;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterWindowClass(wcex);
}

_ljGameWin::_ljGameDefaultWin::~_ljGameDefaultWin()
{
}
