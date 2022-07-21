#pragma once
#include "_ljGameMacro.h"
#include <Windows.h>
#include <map>
#include <vector>
#include <string> /*★*/


class _ljGameInput
{
private:
	_ljGameInput();
	~_ljGameInput();

	/* 여기(변수)에서는 선언이 안되었으니 당연히 링커에 잡힌다.  */
	/* 
private:
	static std::map<std::wstring, GameKey*> mAllKey;
	static GameKey* TempKey;
	static std::map<std::wstring, _ljGameInput::GameKey*>::iterator mInputIter;
	static std::map<std::wstring, _ljGameInput::GameKey*>::iterator mInputEndIter;
	*/

private:
	class StaticConDes
	{
	public:
		~StaticConDes();
	};

	friend StaticConDes;
	static StaticConDes mConDes;

	class GameKey 
	{
		friend _ljGameInput;

	public:
		void Update();
		bool AllKeyCheck();

		void PushKey(int value)
		{
			mKeyVec.push_back(value);
		}

	private:
		std::vector<int> mKeyVec;
		bool mIsUp = true;
		bool mIsDown = false;
		bool mIsPress = false;
		bool mIsRelease = true;
	};


private:
	static std::map<std::wstring, GameKey*> mAllKey;
	static GameKey* TempKey;
	static std::map<std::wstring, _ljGameInput::GameKey*>::iterator mInputIter;
	static std::map<std::wstring, _ljGameInput::GameKey*>::iterator mInputEndIter;


	/* public static */ 
public:
	template<typename ...REST>
	static bool CreateKey(const wchar_t* name, REST... value)
	{
		if (true == IsKey(name))
		{
			BOOM;
			return false;
		}

		TempKey = new GameKey();

		CreateKeyRec(value ...);

		mAllKey.insert(std::map<std::wstring, GameKey*>::value_type(name, TempKey));

		return true;
	}

	static void Update();
	static bool Press(const wchar_t* keyName);
	static bool Down(const wchar_t* keyName);
	static bool Up(const wchar_t* keyName);
	static bool Release(const wchar_t* keyName);

	/* private static */
private:
	template<typename ...REST>
	static void CreateKeyRec(int pushValue, REST... value)
	{
		TempKey->mKeyVec.push_back(pushValue);
		CreateKeyRec(value ...);
	}

	static void CreateKeyRec() {}


private:
	static GameKey* FindKey(const wchar_t* name);
	static bool IsKey(const wchar_t* name);


};

