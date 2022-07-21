#include "_ljGameSound.h"
#include "_ljGameMacro.h"
#include "_ljGameDir.h"
#include <atlstr.h>



/* 어떤 방식으로 라이브러리를 사용하고 체크하는지 똑같이 익혀야 한다. */

/*
	속성 > C/C++ > 전처리기

	_DEBUG;_CONSOLE;%(PreprocessorDefinitions)
	NDEBUG;_CONSOLE;%(PreprocessorDefinitions)

	UNICODE;_UNICODE; %(PreprocessorDefinitions); X64;DEBUGMODE;
	UNICODE;_UNICODE; %(PreprocessorDefinitions); X64;RELEASEMODE;

*/

// ★
#ifdef RELEASEMODE
#ifdef X32
#pragma comment(lib, "fmod_vc")
#else X64
#pragma comment(lib, "fmod_vc")
#endif
#else DEBUGMODE
#ifdef X32
#pragma comment(lib, "fmodL_vc")
#else X64
#pragma comment(lib, "fmodL_vc")
#endif
#endif


FMOD::System* _ljGameSound::mSoundSystem;
std::map<std::wstring, _ljGameSound*> _ljGameSound::mAllSound;
std::list<_ljGameSound::MyGameSoundStream*> _ljGameSound::mAllStream;
std::list<_ljGameSound::MyGameSoundStream*> _ljGameSound::mActiveStream;



_ljGameSound::_ljGameSound()
{
}


_ljGameSound::~_ljGameSound()
{
	if (nullptr != mSound)
	{
		mSound->release();
	}
}


void _ljGameSound::MyGameSoundStream::Init(FMOD::Channel* _Ch)
{
	mIsActive = true;
	mChannel = _Ch;
}

void _ljGameSound::MyGameSoundStream::Stop()
{
	mChannel->stop();
	mIsActive = false;

	/* 
		값을 넣어주면 안에서 검색한다.  
		일반적인 함수보다 느리다. 
	*/

	mActiveStream.remove(this);
	mAllStream.push_back(this);
}

void _ljGameSound::MyGameSoundStream::Paused()
{
	mChannel->setPaused(true);
}

void _ljGameSound::MyGameSoundStream::ReStart()
{
	mChannel->setPaused(false);
}

void _ljGameSound::MyGameSoundStream::PlayOnOff()
{
	bool Check;

	mChannel->getPaused(&Check);

	if (false == Check)
	{
		Paused();
	}
	else {
		ReStart();
	}
}

_ljGameSound::MyGameSoundStream* _ljGameSound::PopSoundStream()
{
	if (0 == mAllStream.size())
	{
		return nullptr;
	}

	_ljGameSound::MyGameSoundStream* pHGSS = mAllStream.front();
	mAllStream.pop_front();
	return pHGSS;
}

_ljGameSound::MyGameSoundStream::MyGameSoundStream() : mIsActive(false)
{
}

_ljGameSound::MyGameSoundStream::~MyGameSoundStream()
{
}

void _ljGameSound::SoundInit(int Count /*= 100*/)
{
	FMOD::System_Create(&mSoundSystem);

	// >>> 여기서 사운드 드라이버와 연결되었다. 

	if (nullptr == mSoundSystem)
	{
		BOOM;
	}

	if (FMOD_OK != mSoundSystem->init(32, FMOD_DEFAULT, nullptr))
	{
		BOOM;
	}

	for (int i = 0; i < 5000; i++)
	{
		mAllStream.push_back(new MyGameSoundStream());
	}

}

void _ljGameSound::SoundEnd() 
{

	/* 
	>>> iterator 활용  
		std::map<std::wstring, _ljGameSound*>::iterator Start = m_AllSound.begin();
		std::map<std::wstring, _ljGameSound*>::iterator End = m_AllSound.end();
		for (size_t i = 0; i < length; i++)
		{
		}
	*/

	while ( 0 < mAllSound.size() )
	{
		if (nullptr != mAllSound.begin()->second)
		{
			delete mAllSound.begin()->second;
			mAllSound.erase(mAllSound.begin());
		}
	}

	for (MyGameSoundStream* HSS : mAllStream)
	{
		delete HSS;
	}

	for (MyGameSoundStream* HSS : mActiveStream)
	{
		delete HSS;
	}

}

void _ljGameSound::SoundUpdate()
{
	mSoundSystem->update();
}

void _ljGameSound::SoundDestroy()
{
}

void _ljGameSound::SoundLoad(const _ljGameFile& _File)
{
	if (mAllSound.end() != mAllSound.find(_File.FileName()))
	{
		BOOM;
		return;
	}

	_ljGameSound* NewSound = new _ljGameSound();

	if (false == NewSound->Load(_File.GetPath().c_str()))
	{
		BOOM;
	}

	mAllSound.insert(std::map<std::wstring, _ljGameSound*>::value_type(_File.FileName(), NewSound));

}

_ljGameSound::MyGameSoundStream* _ljGameSound::SoundPlay(const wchar_t* _Name, int _Loop)
{
	std::map<std::wstring, _ljGameSound*>::iterator FindSoundIter = mAllSound.find(_Name);

	if (mAllSound.end() == FindSoundIter)
	{
		BOOM;
		return nullptr;
	}

	MyGameSoundStream* pStream = PopSoundStream();

	if (nullptr == pStream)
	{
		return nullptr;
	}

	/* 
		>>> 재생 스트림을 넘겨준다. 
		>>> 진행중인 것
		>>> CH->setLoopCount(_Loop);
	*/

	mSoundSystem->playSound(FindSoundIter->second->mSound, nullptr, false, &pStream->mChannel);

	FindSoundIter->second->mSound->setLoopCount(_Loop);

	if (_Loop == 0)
	{
		BOOM;
	}

	if (1 != _Loop)
	{
		pStream->mChannel->setMode(FMOD_LOOP_NORMAL);
		pStream->mChannel->setLoopCount(_Loop);
	}

	mActiveStream.push_back(pStream);

	return pStream;

	/* 
		CH->setLoopPoints()
		CH->getPosition  >> 현재 재생된 위치 
		CH->getPitch  >> 속력옵션
	*/

}

void _ljGameSound::SoundPlayToInst(const wchar_t* _Name, int _Loop) 
{

	std::map<std::wstring, _ljGameSound*>::iterator FindSoundIter = mAllSound.find(_Name);

	if (mAllSound.end() == FindSoundIter)
	{
		BOOM;
		return;
	}

	// CH->setLoopCount(_Loop);
	mSoundSystem->playSound(FindSoundIter->second->mSound, nullptr, false, nullptr);
	FindSoundIter->second->mSound->setLoopCount(_Loop);

	return;

}

bool _ljGameSound::Load(const wchar_t* _Path)
{
	// m_pSound->getLength()

	if (FMOD_OK != mSoundSystem->createSound(CW2A(_Path, CP_UTF8).m_psz, FMOD_DEFAULT, nullptr, &mSound))
	{
		BOOM;
		return false;
	}

	return true;
}