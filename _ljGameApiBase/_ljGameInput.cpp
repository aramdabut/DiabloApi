#include "_ljGameInput.h"


/* 
	속성 > C/C++ > 전처리기 

	_DEBUG;_CONSOLE;%(PreprocessorDefinitions)
	NDEBUG;_CONSOLE;%(PreprocessorDefinitions)

	_UNICODE;UNICODE;%(PreprocessorDefinitions);X64;DEBUGMODE;
	_UNICODE;UNICODE;%(PreprocessorDefinitions);X64;RELEASEMODE;

	UNICODE;_UNICODE;_DEBUG;_CONSOLE;%(PreprocessorDefinitions);X64;DEBUGMODE;
	UNICODE;_UNICODE;NDEBUG;_CONSOLE;%(PreprocessorDefinitions);X64;RELEASEMODE;

	UNICODE;_UNICODE; %(PreprocessorDefinitions); X64;DEBUGMODE;
	UNICODE;_UNICODE; %(PreprocessorDefinitions); X64;RELEASEMODE;

	_D64
*/

std::map<std::wstring, _ljGameInput::GameKey*> _ljGameInput::mAllKey;
_ljGameInput::GameKey* _ljGameInput::TempKey;

std::map<std::wstring, _ljGameInput::GameKey*>::iterator _ljGameInput::mInputIter;
std::map<std::wstring, _ljGameInput::GameKey*>::iterator _ljGameInput::mInputEndIter;


// ========================== Condes ==========================


_ljGameInput::StaticConDes _ljGameInput::mConDes;

_ljGameInput::StaticConDes::~StaticConDes()
{
	std::map<std::wstring, _ljGameInput::GameKey*>::iterator StartIter = _ljGameInput::mAllKey.begin();
	std::map<std::wstring, _ljGameInput::GameKey*>::iterator EndIter = _ljGameInput::mAllKey.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	mAllKey.clear();
}


// ============================ Condes over ============================


void _ljGameInput::Update()
{
	mInputIter = _ljGameInput::mAllKey.begin();
	mInputEndIter = _ljGameInput::mAllKey.end();

	for (; mInputIter != mInputEndIter; ++mInputIter)
	{
		if (nullptr != mInputIter->second)
		{
			mInputIter->second->Update();
		}
	}
}

bool _ljGameInput::Press(const wchar_t* keyName)
{
	GameKey* key = FindKey(keyName);

	if (nullptr == key)
	{
		BOOM;
	}

	return key->mIsPress;
}

bool _ljGameInput::Down(const wchar_t* keyName)
{
	GameKey* key = FindKey(keyName);

	if (nullptr == key)
	{
		BOOM;
	}

	return key->mIsDown;
}

bool _ljGameInput::Up(const wchar_t* keyName)
{
	GameKey* key = FindKey(keyName);

	if (nullptr == key)
	{
		BOOM;
	}

	return key->mIsUp;
}

bool _ljGameInput::Release(const wchar_t* keyName)
{
	GameKey* key = FindKey(keyName);

	if (nullptr == key)
	{
		BOOM;
	}

	return key->mIsRelease;
}

_ljGameInput::_ljGameInput()
{
}


_ljGameInput::~_ljGameInput()
{
}


_ljGameInput::GameKey* _ljGameInput::FindKey(const wchar_t* name)
{
	auto iter = mAllKey.find(name);

	if (iter == mAllKey.end())
	{
		return nullptr;
	}

	return iter->second;
}

bool _ljGameInput::IsKey(const wchar_t* name)
{
	if (mAllKey.end() == mAllKey.find(name))
	{
		return false;
	}

	return true;
}

// =========================== GameKey 구현부 ===========================

void _ljGameInput::GameKey::Update()
{
	if (true == AllKeyCheck())
	{
		if (true == mIsRelease)
		{
			mIsUp = false;
			mIsDown = true;
			mIsPress = true;
			mIsRelease = false;
		}
		else if (false == mIsRelease)
		{
			mIsUp = false;
			mIsDown = false;
			mIsPress = true;
			mIsRelease = false;
		}
	}
	// 키가 안눌린 케이스 
	else
	{
		if (true == mIsDown || true == mIsPress)
		{
			mIsUp = true;
			mIsDown = false;
			mIsPress = false;
			mIsRelease = true;
		}
		else if (true == mIsUp)
		{
			mIsUp = false;
			mIsDown = false;
			mIsPress = false;
			mIsRelease = true;
		}
	}
}


bool _ljGameInput::GameKey::AllKeyCheck()
{
	for (size_t i = 0; i < mKeyVec.size(); i++)
	{
		if (0 == GetAsyncKeyState(mKeyVec[i]))
		{
			return false;
		}
	}

	return true;
}


