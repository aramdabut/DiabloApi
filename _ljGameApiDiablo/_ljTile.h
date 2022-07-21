#pragma once
#include <vector>
#include <_ljGameActor.h>
#include "_ljColTile.h"
#include "_ljValueData.h"
#include "_ljRoom.h"

class _ljMonster;
class _ljRandomMap;
class _ljColTile;
class _ljPlayer;
class _ljObject;
class _ljTile : public _ljGameActor
{
	friend _ljRandomMap;
	friend _ljPlayer;
	friend _ljMonster;

	friend class _ljDungeon15;
	friend class _ljDungeon18;
	friend class _ljDungeon2;
	friend class _ljTestScene;

	friend _ljObject;
	class TileData
	{
	public:
		TileIndex mIndex;
		_ljVector mPos;
		_ljVector mSize;
		int mBF;
	};

	class WallData
	{
	public:
		TileIndex mIndex;
		_ljVector mPos;
		_ljVector mSize;
		int mBF;
	};

	class BigFogData
	{
	public:
		TileIndex mIndex;
		_ljVector mPos;
		_ljVector mSize;
		int mBF;
	};

	/*class TileRenderer : public _ljGameRenderer
	{
	public:

	private:

	};

	class WallRenderer : public _ljGameRenderer
	{

	};

	class BigFogRenderer : public _ljGameRenderer
	{

	};*/

private:
	_ljTile();
	_ljTile(const _ljTile& other);
	_ljTile(_ljRandomMap* map, int x, int y, LEAGUE_ORDER order);
	~_ljTile();

	// void Init();

	void Update() override;
	// void FindNeighbors();

	TILE_TYPE TileType() { return mTileType; }
	
	void TileType(TILE_TYPE type)
	{
		mTileType = type;
	}

	WALL_TYPE WallType()
	{
		return mWallType;
	}

	void WallType(WALL_TYPE type)
	{
		mIsWall = true;
		mTileType = TT_WALL;
		mWallType = type;
	}

	void FloorType(WALL_TYPE type)
	{
		mIsWall = false;
		mTileType = TT_FLOOR;
		mWallType = type;
	}

	/*CORNER_TYPE CornerType() { return mCornerType; }
	void CornerType(CORNER_TYPE type)
	{
		mIsWall = true;
		mTileType = TT_CORNER;
		mCornerType = type;
	}*/

	void SetRenderOrder(LEAGUE_ORDER order) { mRenderOrder = order; }

	void SetFloor();
	void SetUpstair();
	void SetDownstair();
	void SetRoom(_ljRoom* room) { mRoom = room; }
	_ljRoom* GetRoom() { return mRoom; }

	bool IsWall() { return mIsWall; }
	bool IsUpstair() { return mIsUpstair; }
	bool IsDownstair() { return mIsDownstair; }
	bool IsRoom();

	void DebugSwitch();


	void DebugRender();
	void DebugOutputTile();
	void DebugSetPosition();
	void DebugSetTypeName();



	// void Update() override;

	void LastCheck1();
	void LastCheck2();

	_ljObject* PutBox(int index);
private:
	// _ljGameRenderer* mTileRenderer;
	_ljGameRenderer* mWallRenderer;
	_ljGameRenderer* mFogRenderer;

	_ljGameRenderer* mDebugRenderer;

	_ljRandomMap* mMap;
	_ljRoom* mRoom;
	_ljObject* mObject = nullptr;

	TILE_TYPE mTileType;
	WALL_TYPE mWallType;
	// CORNER_TYPE mCornerType;

	bool mIsT = false;

	bool mIsWall;
	bool mIsUpstair;
	bool mIsDownstair;

	int mX;
	int mY;

	static int mUpstairCount;
	static int mDownstairCount;

	float mMoveSpeed;

	///////////////////// Debug
	bool mIsDebug = false;
	const wchar_t* mAllTileType[WT_MAX];

	// Sub Tiles
	std::vector<_ljColTile*> mSubTiles;

	// 모든 타일이 플레이어를 
	_ljPlayer* mPlayer;

	LEAGUE_ORDER mRenderOrder;

	std::vector<BigFogData*> mAllBigFog;
	std::vector<WallData*> mAllWall;
	std::vector<TileData*> mAllTile;

	bool mIsInRoom;

	int mIncrease;
	int mBase;

	template <typename F>
	F* Init(int x, int y)
	{
		F* temp = new F();

		temp->mIndex.X = x;
		temp->mIndex.Y = y;

		float offsetX = (TILE_OFFSETX) / 2.f;
		float offsetY = offsetX / 2.f;

		float startX = MAPSIZE_X / 2.f - offsetX - (y * offsetX);
		float startY = y * offsetY;

		float newX = (startX + x * offsetX);
		float newY = startY + (x * offsetY);

		temp->mPos = _ljVector(newX, newY);

		temp->mSize = { TILE_WIDTH, TILE_HEIGHT };

		return temp;
	}
};

