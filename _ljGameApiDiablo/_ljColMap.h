#pragma once
#include <map>
#include <list>
#include <set>
#include <_ljGameActor.h>
#include "_ljColTile.h"

class _ljMonster;
class _ljRandomMap;
class _ljColTile;
class _ljPlayer;
class _ljItemMgr;

// DebugRender를 위해서 _ljGameActor 상속
// 나중에 상속 풀어도 괜찮음
class _ljColMap : public _ljGameActor
{
	friend _ljItemMgr;

public:
	_ljColMap(_ljRandomMap* map);
	~_ljColMap();

	void Update() override;

	void SetPlayer(_ljPlayer* player);

	_ljColTile* FindTile(int x, int y);
	_ljColTile* FindTile(_ljVector pos);
	_ljColTile* FindTile(TileIndex index);

	_ljColTile* CheckTile(int indexX, int indexY);
	_ljColTile* CheckTile(float winX, float winY);

	_ljColTile* GetTile(float winX, float winY);
	_ljColTile* GetTile(int indexX, int indexY);
	_ljColTile* GetTile(_ljVector pos);

	TileIndex PosToIndex(_ljVector pos);
	TileIndex PosToIndexM(_ljVector pos);

	_ljVector IndexToPos(TileIndex index);
	_ljVector IndexToPosM(TileIndex index);

	void AddTile(int x, int y);
	void SetWalkable(int x, int y);


	void DebugRender() override;

	// 인덱스 x, y 위치에 Actor를 저장.
	bool UpdateActorIndex(int x, int y, int prevX, int prevY, _ljMonster* actor);
	TileIndex SetActorIndex(int x, int y, _ljMonster* actor);

	void UnsetUnit(int x, int y);

public:
	class PathNode
	{
	public:
		// 대각선 이동이 되냐 안되냐?
		float StartDis; // 시작점까지 오기위해서 걸린 거리
		float EndDis; // 최단거리
		float AllDis; // StartDis + EndDis 둘을 합친 거리

		PathNode* Parent;
		TileIndex Index;

		void CalData(TileIndex endIndex, PathNode* parent)
		{
			// 내가 첫 노드인 경우 => startDis를 계산하지 않음
			if (nullptr == parent)
			{
				Parent = nullptr;
				StartDis = 0.0f;
			}
			else
			{
				StartDis = parent->StartDis;
				Parent = parent;
				_ljVector End = { Parent->Index.X, Parent->Index.Y };
				_ljVector Start = { Index.X, Index.Y };
				_ljVector Dis = Start - End;
				StartDis += Dis.Length();
			}

			{
				_ljVector End = { endIndex.X, endIndex.Y };
				_ljVector Start = { Index.X, Index.Y };
				_ljVector Dis = Start - End;
				EndDis = Dis.Length();
				AllDis = StartDis + EndDis;
			}
		}
	};

	std::list<_ljVector> PathFind(_ljVector startPos, _ljVector endPos);
	std::list<_ljVector> PathFind(TileIndex startPos, TileIndex endPos);
	std::list<_ljVector> PathFindSpecial(_ljVector startPos, _ljVector endPos);
	// std::list<_ljVector> PathFindAttack(_ljVector startPos, _ljVector endPos);

	std::list<_ljVector> PathFindM(_ljVector startPos, _ljVector endPos);
	std::list<_ljVector> PathFindAttackM(_ljVector startPos, _ljVector endPos);

private:
	bool IsOpenList(TileIndex index);

	void ResetPool();

	PathNode* OpenListPop(); // 탐색을 위해서 제거한다.
	PathNode* OpenListPopAttack();

	PathNode* CreateOpenPathNode(_ljVector pos, PathNode* parent);
	PathNode* CreateOpenPathNode(TileIndex index, PathNode* parent);
	PathNode* CreatePathNode(_ljVector pos);
	PathNode* CreatePathNode(TileIndex index);

	bool FindAdj(PathNode* node);
	bool FindAdjAttack(PathNode* node);

public:
	static TileIndex mDirArr[8];

private:
	enum TILEDIR
	{
		TILEDIR_MAX = 8
	};

	std::list<PathNode*>::iterator mCurNodeIter;
	std::list<PathNode*> PathNodePool;

	std::multimap<float, PathNode*> mOpenList; // 아직 검사하지 않은 노드
	std::set<__int64> mOpenIndexSet; // 아직 검사하지 않은 노드

	std::multimap<__int64, PathNode*> mClosedList; // 검사 끝낸 노드
	std::set<__int64> mClosedIndexSet; // 검사 끝낸 노드-

	std::map<__int64, _ljColTile*>::iterator mTileIter;
	std::map<__int64, _ljColTile*>::iterator mTileEndIter;
	std::map<__int64, _ljColTile*> mAllTile;


	PathNode* mEndNode;
	TileIndex mEndIndex;
	_ljRandomMap* mRandomMap;

	int mCount;
	_ljPlayer* mPlayer;
	//std::vector<_ljColTile*> mNe

	int mLoopCount = 0;
};

