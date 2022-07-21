#pragma once
#include <fmod.hpp>	// 포함 디렉토리 >> FMOD.hpp 
#include <map>
#include <list>
#include "_ljGameFile.h"



class _ljGameSound
{
public:
	_ljGameSound();
	~_ljGameSound();

public:
	class MyGameSoundStream
	{
	private:
		friend _ljGameSound;
		FMOD::Channel* mChannel;
		bool mIsActive;

	private:
		void Init(FMOD::Channel* _Ch);

	public:
		void Stop();
		void Paused();
		void ReStart();

		void PlayOnOff();

	private:
		MyGameSoundStream();
		~MyGameSoundStream();
	};

	friend MyGameSoundStream;

private:
	static FMOD::System* mSoundSystem;

public:
	static std::map<std::wstring, _ljGameSound*> mAllSound;
	static std::list<MyGameSoundStream*> mAllStream;
	static std::list<MyGameSoundStream*> mActiveStream;

private:
	static MyGameSoundStream* PopSoundStream();

public:
	static void SoundPlayCount();
	static void SoundInit(int Count = 1000);
	static void SoundEnd();
	static void SoundUpdate();	// 이벤트 체크용
	static void SoundDestroy(); // 메모리 정리
	static void SoundLoad(const _ljGameFile& _File); // 메모리 정리

	// 0 넣으면 터집니다(ERROR). 
	static MyGameSoundStream* SoundPlay(const wchar_t* _Name, int _Loop = 1);	// 메모리 정리
	static void SoundPlayToInst(const wchar_t* _Name, int _Loop = 1);			// 메모리 정리


private:
	FMOD::Sound* mSound;

private:
	bool Load(const wchar_t* _Path);


};

