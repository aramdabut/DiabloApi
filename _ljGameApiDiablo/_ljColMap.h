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

// DebugRender�� ���ؼ� _ljGameActor ���
// ���߿� ��� Ǯ� ������
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

	// �ε��� x, y ��ġ�� Actor�� ����.
	bool UpdateActorIndex(int x, int y, int prevX, int prevY, _ljMonster* actor);
	TileIndex SetActorIndex(int x, int y, _ljMonster* actor);

	void UnsetUnit(int x, int y);

public:
	class PathNode
	{
	public:
		// �밢�� �̵��� �ǳ� �ȵǳ�?
		float StartDis; // ���������� �������ؼ� �ɸ� �Ÿ�
		float EndDis; // �ִܰŸ�
		float AllDis; // StartDis + EndDis ���� ��ģ �Ÿ�

		PathNode* Parent;
		TileIndex Index;

		void CalData(TileIndex endIndex, PathNode* parent)
		{
			// ���� ù ����� ��� => startDis�� ������� ����
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

	PathNode* OpenListPop(); // Ž���� ���ؼ� �����Ѵ�.
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

	std::multimap<float, PathNode*> mOpenList; // ���� �˻����� ���� ���
	std::set<__int64> mOpenIndexSet; // ���� �˻����� ���� ���

	std::multimap<__int64, PathNode*> mClosedList; // �˻� ���� ���
	std::set<__int64> mClosedIndexSet; // �˻� ���� ���-

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

