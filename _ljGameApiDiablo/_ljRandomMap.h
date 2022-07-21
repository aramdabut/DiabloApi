#pragma once
#include <vector>
#include <_ljGameMath.h>
#include "_ljValueData.h"

class _ljTile;
class _ljRoom;
class _ljMapTester;
class _ljColTile;
class _ljColMap;
class _ljMonster;
class _ljPlayer;
class _ljGameActor;
class _ljGameTexture;
class _ljGameScene;
// MapGenerator로 생성된 Map이다.


class _ljRandomMap
{
	friend _ljColMap;
	friend _ljTile;
	friend _ljMonster;
	friend _ljPlayer;

	friend class _ljTestScene;
	friend class _ljDungeon15;
	friend class _ljDungeon18;
	friend class _ljDungeon2;

public:
	_ljRandomMap();
	_ljRandomMap(_ljGameScene* scene);
	_ljRandomMap(const _ljRandomMap& other);
	~_ljRandomMap();

	void On();
	void Off();

	void SetPlayer(_ljPlayer* player);
	_ljPlayer* GetPlayer() const;

	_ljTile* GetTile(int _X, int _Y);
	_ljTile* GetTile(_ljVector pos);

	////////////////////////////////////////////// 맵 생성 관련 /////////////////////////////////////////////////////
	void Make3RoomsY(int level);

	bool MakeARoom(_ljVector basePos, _ljVector size, _ljVector prevPos, _ljVector prevSize, ROOM_TYPE roomType);

	void MakeTopEleven(_ljVector basePos, _ljVector size, _ljVector prevPos, _ljVector prevSize);
	void MakeLeftEleven(_ljVector basePos, _ljVector size, _ljVector prevPos, _ljVector prevSize);

	void MakeArchY(_ljVector basePos, _ljVector size, _ljVector prevPos, _ljVector prevSize);
	void MakeArchX(_ljVector basePos, _ljVector size, _ljVector prevPos, _ljVector prevSize);

	void MakeRandomRooms(_ljVector prevPos, _ljVector prevSize, ROOM_TYPE roomType, int left, int bottom, int right, int top);
	void MakeRandomBRooms(_ljVector prevPos, _ljVector prevSize, ROOM_TYPE roomType, int left, int bottom, int right, int top);
	bool MakeButchersPreRoom(_ljVector basePos, _ljVector size, _ljVector prevPos, _ljVector prevSize, ROOM_TYPE roomType);
	bool MakeButchersRealRoom(_ljVector basePos, _ljVector size, _ljVector prevPos, _ljVector prevSize, ROOM_TYPE roomType);

	bool SetUpstair();
	void SetDownstair();

	void MakeUpstair(_ljVector& basePos);
	void MakeDownstair(_ljVector& basePos);

	bool MakeADoor(_ljVector basePos, _ljVector size, _ljVector prevPos, _ljVector prevSize, ROOM_TYPE roomType);
	bool MakeAConnection(_ljVector basePos, _ljVector size, _ljVector prevPos, _ljVector prevSize, ROOM_TYPE roomType);



	void MakeFloor(_ljVector basePos, _ljVector size);
	void MakeBFloor(_ljVector basePos, _ljVector size);

	void MakeWideFloor(_ljVector basePos, _ljVector size);

	void ResetCount();




	///////////////////////////////////////////// 타일 변환 관련 /////////////////////////////////////////////
	bool MakeIronWall(_ljVector basePos, _ljVector size, ROOM_TYPE type);
	bool UpgradeIronWall();

	void UpgradeWallStyle();

	void UpgradeRoomCorner(_ljVector basePos, _ljVector size);

	void UpgradeAdjCorner(int x, int y, WALL_TYPE type);
	void UpgradeAllAdjCorner();

	void SetFloorAt(int x, int y);
	void SetFloorAt(_ljVector pos);
	// void SetFloorAt(_ljVector pos, wchar_t special);

	void SetWallAt(int x, int y, WALL_TYPE type);
	void SetWallAt(_ljVector pos, WALL_TYPE type);

	void SetDoorAt(_ljVector pos, WALL_TYPE doorType);

	void SetCornerAt(int x, int y, WALL_TYPE type);
	void SetCornerAt(_ljVector pos, WALL_TYPE type);
	void SetNormalCornerAt(_ljVector pos, WALL_TYPE type);

	void SetColumnAt(int x, int y);

	void SetWallAroundAt(int x, int y);
	void SetBWallAroundAt(int x, int y);
	void SetWallAroundAt(_ljVector pos);
	// void SetWallAroundAt(_ljVector pos, wchar_t specialFloor, wchar_t specialWall);

	void SetAllShadow();

	bool CheckIsRoom(_ljVector& roomPos, _ljVector& roomSize);
	_ljVector CheckNorthWall(_ljVector& roomPos, _ljVector& roomSize);
	bool CheckIsTile(int x, int y, WALL_TYPE type);
	bool CheckIsTile(int x, int y, TILE_TYPE type);

	bool IsFloor(int x, int y);
	bool IsFloor(_ljVector pos);
	bool IsWall(int x, int y);
	bool IsWall(_ljVector pos);
	bool IsRoom(int x, int y);
	bool IsRoom(_ljVector pos);
	bool IsUpstair(_ljVector pos);
	bool IsDownstair(_ljVector pos);

	bool HasDownstair() { return mHasDownstair; }

	_ljRandomMap& CopyMap(_ljRandomMap* map);


	void Update();

	///////////////////////////////////////////////////////////////////////////// 타일 스타일 세팅
	WALL_TYPE StyleFloor();
	WALL_TYPE StyleLeftWall();
	WALL_TYPE StyleTopWall();

	void InstallObjects();

	void PlaceBox(int x, int y, CHEST_TYPE index);
	// void PlaceCandle(int x, int y, WALL_TYPE candle);

	void SetIronWallX(_ljVector basePos, int size);
	void SetIronWallY(_ljVector basePos, int size);

	void SetColliderMap();

	bool FinishMap();

	_ljColMap* ColMap() { return mColliderMap; }

	void AddLeft(int x, int y);
	void AddRight(int x, int y);
	void AddAll(int x, int y);
	void AddLT(int x, int y);
	void AddT(int x, int y);
	void AddNone(int x, int y);
	_ljVector SubToDib(int x, int y);
	void AddSubTile(_ljColTile* subTile);

	std::vector<_ljRoom*> GetAllRoom() { return mAllRoom; }

	TileIndex GetStartPos1() const { return mStartPos1; }
	TileIndex GetStartPos2() const { return mStartPos2; }
	TileIndex GetDownPos() const { return mDownPos; }
	TileIndex GetBPos() const { return mBPos; }
	bool GetIsChanging() const { return mIsChanging; }

	void RenderTile();

	////////////////////////////// FINISHING
	void SetBRoom();
	bool HasBRoom() const { return mHasBRoom; }
	void SetStartRoom();
private:
	void SetImageIndex();
	void SetCopyImageIndex();
	void CopyAll();



	// static void MakeBack();

private:
	// static std::vector<_ljRandomMap*> mAllMap;

	_ljTile*** mAllTile;
	_ljTile*** mAllCopyTile;

	_ljRoom* mLastRoom;
	_ljRoom* mStartRoom = nullptr;
	std::vector<_ljRoom*> mAllRoom;
	std::vector<_ljTile*> mAllWall;
	std::vector<_ljTile*> mCorners;

	static int mLevel;

	int mLeftLimit = 3;
	int mBottomLimit = 2;
	int mRightLimit = 0;
	int mTopLimit = 0;

	int mLeftCount = 0;
	int mBottomCount = 0;
	int mRightCount = 0;
	int mTopCount = 0;

	bool mHasUpstair;
	bool mHasDownstair;

	_ljColMap* mColliderMap;

	_ljPlayer* mPlayer;

	_ljGameActor* mBackTile;
	_ljGameTexture* mBackTexture;

	TileIndex mStartPos1;
	TileIndex mStartPos2;

	TileIndex mDownPos;
	TileIndex mBPos;


	_ljGameScene* mCurScene;

	bool mIsChanging = false;
	bool mHasBRoom = false;
};

