#pragma once
#include <_ljGameMath.h>


class Map;
class _ljPlayer;
class _ljGameManager
{
public:
	static _ljVector ScreenSize() { return mScreenSize; }

	static void Init(_ljVector _Size);
	static void Clear();
	static void Print(int _Frame);
	static void SetPixel(_ljVector _Pos, wchar_t _Pixel);

	// static Map* GetMap() { return mMap; }
	// static Player* GetPlayer() { return mPlayer; }

	static void SetPlayer(_ljPlayer* player);
	static void SetMap(Map* map);
	//static MyArr<MyArr<class Object*>>* GetAll() 
	//{ 
	//	return &mAllObject; 
	//}

	//static class Object* GetGameObject(int _X, int _Y) 
	//{
	//	return mAllObject[_Y][_X];
	//}
	static void PrintPlayerStatus();
	static void PrintMonster();
private:
	_ljGameManager();
	~_ljGameManager();

	static void DeleteScreen();
	static void CreateWall();


private:
	static _ljVector mScreenSize;



	// static wchar_t m_BaseChar;
	// static class Player* mPlayer;
	// static Map* mMap;
};

