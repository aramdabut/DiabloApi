#include "_ljColMap.h"
#include <_ljGameMacro.h>
#include <_ljGameTextureMgr.h>
#include <_ljGameWin.h>
#include <_ljGameInput.h>
#include "_ljRandomMap.h"
#include "_ljValueData.h"
#include "_ljMonster.h"
#include "_ljPlayer.h"

//TileIndex _ljColMap::mDirArr[8]
//{
//	{1, 0},   // R
//	{1, -1},  // RT
//	{0, -1},  // T
//	{-1, -1}, // LT
//	{-1, 0},  // L
//	{-1, 1},  // LB
//	{0, 1},   // B
//	{1, 1},   // RB
//};

TileIndex _ljColMap::mDirArr[8]
{
	{1, 1},   // RB
	{0, 1},   // B
	{-1, 1},  // LB
	{-1, 0},  // L
	{-1, -1}, // LT
	{0, -1},  // T
	{1, -1},  // RT
	{1, 0},   // R
};


//RB,
//B,
//LB,
//L,
//LT,
//T,
//RT,
//R,


_ljColMap::_ljColMap(_ljRandomMap* map)
	: mRandomMap(map)
	, mCount(0)
{
	for (size_t i = 0; i < 300; i++)
	{
		// POP FRONT
		PathNodePool.push_back(new PathNode());
	}

	// PathNodePool.pop_front();
	mCurNodeIter = PathNodePool.begin();
}

_ljColMap::~_ljColMap()
{
	{
		std::list<PathNode*>::iterator Start = PathNodePool.begin();
		std::list<PathNode*>::iterator End = PathNodePool.end();

		for (; Start != End; ++Start)
		{
			delete (*Start);
		}
	}

	//std::map<__int64, _ljColTile*>::iterator Start = mAllTile.begin();
	//std::map<__int64, _ljColTile*>::iterator End = mAllTile.end();

	//for (; Start != End; ++Start)
	//{
	//	if (nullptr != Start->second)
	//	{
	//		delete Start->second;
	//		Start->second = nullptr;
	//	}
	//}
}

void _ljColMap::Update()
{
	_ljColTile::TileDebugSwitch();
}

void _ljColMap::SetPlayer(_ljPlayer* player)
{
	std::map<__int64, _ljColTile*>::iterator iter = mAllTile.begin();
	std::map<__int64, _ljColTile*>::iterator iterEnd = mAllTile.end();

	mPlayer = player;

	for (; iter != iterEnd; ++iter)
	{
		if (nullptr != iter->second)
		{
			iter->second->SetPlayer(player);
		}
	}

	int a = 0;
}

_ljColTile* _ljColMap::FindTile(int x, int y)
{
	TileIndex index = { x, y };

	std::map<__int64, _ljColTile*>::iterator iter = mAllTile.find(index.Index);

	if (iter == mAllTile.end())
	{
		return nullptr;
	}

	return iter->second;
}

_ljColTile* _ljColMap::FindTile(_ljVector pos)
{
	return FindTile(pos.IntX(), pos.IntY());
}

_ljColTile* _ljColMap::FindTile(TileIndex index)
{
	return FindTile(index.X, index.Y);
}

_ljColTile* _ljColMap::CheckTile(int indexX, int indexY)
{
	_ljColTile* temp = FindTile(indexX, indexY);

	// 타일에 누군가 있으면 역시 nullptr;
	if (nullptr == temp || nullptr != temp->GetActor())
	{
		return nullptr;
	}

	if (false == temp->IsMovable())
	{
		return nullptr;
	}

	return temp;
}

_ljColTile* _ljColMap::CheckTile(float winX, float winY)
{
	_ljColTile* temp = FindTile((int)winX, (int)winY);

	// 타일에 누군가 있으면 역시 nullptr;
	if (nullptr != temp->GetActor())
	{
		return nullptr;
	}

	return temp;
}

void _ljColMap::AddTile(int x, int y)
{
	_ljColTile* findTile = FindTile(x, y);

	if (nullptr == findTile)
	{
		TileIndex indexKey = { x, y };
		findTile = CreateRenderer<_ljColTile>(LO_DEBUG);

		findTile->Image(L"TileDebug.bmp");
		findTile->SetTileIndex(indexKey);
		// findTile->SetPlayer(mRandomMap->GetPlayer());

		mRandomMap->AddSubTile(findTile);

		mAllTile.insert(std::map<__int64, _ljColTile*>::value_type(indexKey.Index, findTile));
	}
}

void _ljColMap::SetWalkable(int x, int y)
{
	_ljColTile* findTile = FindTile(x, y);

	if (nullptr != findTile)
	{
		findTile->IsMovable(true);
		findTile->mIsFog = true;
	}
}

// 윈도우 좌표 -> 타일 좌표
_ljColTile* _ljColMap::GetTile(float winX, float winY)
{
	int X = 0;
	int Y = 0;

	_ljVector windowPos = { winX - CalPos().X/* - 2*/, winY - CalPos().Y + 32 };

	X = (int)std::roundf((windowPos.X / QUARTER_TILE_WIDTH + windowPos.Y / QUARTER_TILE_HEIGHT) / 2);
	Y = (int)std::roundf((windowPos.Y / QUARTER_TILE_HEIGHT + -(windowPos.X / QUARTER_TILE_WIDTH)) / 2);

	return FindTile(X, Y);
}

_ljColTile* _ljColMap::GetTile(_ljVector pos)
{
	int X = 0;
	int Y = 0;

	_ljVector windowPos = { pos.X - CalPos().X/* - 2*/, pos.Y - CalPos().Y + 32 };

	X = (int)std::roundf((windowPos.X / QUARTER_TILE_WIDTH + windowPos.Y / QUARTER_TILE_HEIGHT) / 2);
	Y = (int)std::roundf((windowPos.Y / QUARTER_TILE_HEIGHT + -(windowPos.X / QUARTER_TILE_WIDTH)) / 2);

	return FindTile(X, Y);
}

_ljColTile* _ljColMap::GetTile(int indexX, int indexY)
{
	return FindTile(indexX, indexY);
}

TileIndex _ljColMap::PosToIndex(_ljVector pos)
{
	_ljVector windowPos = { pos.X - CalPos().X, pos.Y - CalPos().Y + 32 };

	int x = (int)std::roundf((windowPos.X / QUARTER_TILE_WIDTH + windowPos.Y / QUARTER_TILE_HEIGHT) / 2);
	int y = (int)std::roundf((windowPos.Y / QUARTER_TILE_HEIGHT + -(windowPos.X / QUARTER_TILE_WIDTH)) / 2);

	TileIndex returnIndex;
	returnIndex.X = x;
	returnIndex.Y = y;

	return returnIndex;
}

TileIndex _ljColMap::PosToIndexM(_ljVector pos)
{
	_ljVector windowPos = { pos.X - CalPos().X/* - 2*/, pos.Y - CalPos().Y + 32 };

	int x = (int)std::roundf((windowPos.X / QUARTER_TILE_WIDTH + windowPos.Y / QUARTER_TILE_HEIGHT) / 2);
	int y = (int)std::roundf((windowPos.Y / QUARTER_TILE_HEIGHT + -(windowPos.X / QUARTER_TILE_WIDTH)) / 2);

	TileIndex returnIndex;
	returnIndex.X = x;
	returnIndex.Y = y;

	return returnIndex;
}

_ljVector _ljColMap::IndexToPos(TileIndex index)
{
	_ljVector returnVec;

	returnVec.X = (index.X * QUARTER_TILE_WIDTH) + (index.Y * -QUARTER_TILE_WIDTH) + TILE_SUBOFFSETX - 32;
	returnVec.Y = (index.X * QUARTER_TILE_HEIGHT) + (index.Y * QUARTER_TILE_HEIGHT) + TILE_SUBOFFSETY - 10 - 64 - 32;

	return returnVec;
}

_ljVector _ljColMap::IndexToPosM(TileIndex index)
{
	_ljVector returnVec;

	returnVec.X = (index.X * QUARTER_TILE_WIDTH) + (index.Y * -QUARTER_TILE_WIDTH) + TILE_SUBOFFSETX;
	returnVec.Y = (index.X * QUARTER_TILE_HEIGHT) + (index.Y * QUARTER_TILE_HEIGHT) + TILE_SUBOFFSETY - 64 - 32;

	//returnVec.X = (index.X * QUARTER_TILE_WIDTH) + (index.Y * -QUARTER_TILE_WIDTH);
	//returnVec.Y = (index.X * QUARTER_TILE_HEIGHT) + (index.Y * QUARTER_TILE_HEIGHT);

	return returnVec;
}

void _ljColMap::DebugRender()
{
	_ljVector mouse = _ljGameWin::MainWindow()->MousePos();

	_ljColTile* tempIndex = GetTile(mouse.X, mouse.Y);

	if (nullptr == tempIndex)
	{
		return;
	}

	wchar_t Arr[256] = { 0, };


	if (true == tempIndex->IsMovable())
	{
		swprintf_s(Arr, L"IsWalkable : true");
		TextOutW(_ljGameTextureMgr::BackDC(), 0, 75, Arr, lstrlen(Arr));
	}
	else
	{
		swprintf_s(Arr, L"IsWalkable : false");
		TextOutW(_ljGameTextureMgr::BackDC(), 0, 90, Arr, lstrlen(Arr));
	}

	if (true == _ljGameInput::Press(L"RMOUSEBTN"))
	{
		swprintf_s(Arr, L"%d, %d", tempIndex->GetTileIndex().X, tempIndex->GetTileIndex().Y);
		TextOutW(_ljGameTextureMgr::BackDC(), 0, 105, Arr, lstrlen(Arr));

		swprintf_s(Arr, L"tile pos : %f, %f", tempIndex->CalPos().X, tempIndex->CalPos().Y);
		TextOutW(_ljGameTextureMgr::BackDC(), 0, 120, Arr, lstrlen(Arr));

		swprintf_s(Arr, L"mPos : %f, %f", tempIndex->mPos.X, tempIndex->mPos.Y);
		TextOutW(_ljGameTextureMgr::BackDC(), 0, 135, Arr, lstrlen(Arr));
	}
}


bool _ljColMap::UpdateActorIndex(int x, int y, int prevX, int prevY, _ljMonster* actor)
{
	_ljColTile* newTile = FindTile(x, y);
	_ljColTile* prevTile = FindTile(prevX, prevY);

	if (nullptr == newTile || nullptr == prevTile)
	{
		return false;
	}

	newTile->SetActor(actor);
	prevTile->UnsetActor();

	return true;
}

TileIndex _ljColMap::SetActorIndex(int x, int y, _ljMonster* actor)
{
	if (y >= 80 || x >= 80)
	{
		return { -1, -1 };
	}

	_ljColTile* newTile = FindTile(x, y);

	if (nullptr == newTile || false == newTile->IsMovable() || nullptr != newTile->GetActor())
	{
		return { -1, -1 };
	}



	newTile->SetActor(actor);

	return { x, y };
}

void _ljColMap::UnsetUnit(int x, int y)
{
	_ljColTile* newTile = FindTile(x, y);

	if (nullptr == newTile)
	{
		BOOM;
	}

	newTile->UnsetActor();
}


///////////////////////////////////////////////////////////////////////////////// _ljMapPathFind //////////////////////////////////////////////////////////



bool _ljColMap::IsOpenList(TileIndex index)
{
	return mOpenIndexSet.find(index.Index) != mOpenIndexSet.end();
}



_ljColMap::PathNode* _ljColMap::CreatePathNode(_ljVector pos)
{
	return CreatePathNode(PosToIndex(pos));
}

_ljColMap::PathNode* _ljColMap::CreatePathNode(TileIndex index)
{
	_ljColMap::PathNode* newNode = *mCurNodeIter;
	newNode->Index = index;

	++mCurNodeIter;

	if (mCurNodeIter == PathNodePool.end())
	{
		mCurNodeIter = PathNodePool.begin();
	}

	return newNode;
}





_ljColMap::PathNode* _ljColMap::CreateOpenPathNode(_ljVector pos, PathNode* parent)
{
	return CreateOpenPathNode(PosToIndex(pos), parent);
}

_ljColMap::PathNode* _ljColMap::CreateOpenPathNode(TileIndex index, PathNode* parent)
{
	PathNode* startNode = CreatePathNode(index);
	startNode->CalData(mEndIndex, parent);

	mOpenList.insert(std::multimap<float, PathNode*>::value_type(startNode->AllDis, startNode));
	mOpenIndexSet.insert(startNode->Index.Index);

	return startNode;
}





bool _ljColMap::FindAdj(PathNode* node)
{
	// 4방향인가 8방향인가를 결정할 수 있다.
	TileIndex curIndex = node->Index;
	TileIndex checkIndex;
	std::map<__int64, _ljColTile*>::iterator TileDataIter;

	for (size_t i = 0; i < TILEDIR_MAX; ++i)
	{
		checkIndex = curIndex + mDirArr[i];

		if (mOpenIndexSet.end() != mOpenIndexSet.find(checkIndex.Index))
		{
			continue;
		}

		if (mClosedIndexSet.end() != mClosedIndexSet.find(checkIndex.Index))
		{
			continue;
		}

		mTileIter = mAllTile.find(checkIndex.Index);

		if (mAllTile.end() == mTileIter)
		{
			continue;
		}

		// 갈 수 없는 타일
		if (false == mTileIter->second->IsMovable())
		{
			continue;
		}

		// 이미 다른 캐릭터가 있다.
		if (nullptr != mTileIter->second->GetActor())
		{
			// 목적지에 사람이 있다.
			if (checkIndex == mEndIndex)
			{
				mEndNode = CreateOpenPathNode(checkIndex, node);

				return true;

			}
			continue;
		}

		mEndNode = CreateOpenPathNode(checkIndex, node);

		if (checkIndex == mEndIndex)
		{
			return true;
		}
	}

	mEndNode = nullptr;

	return false;
}

bool _ljColMap::FindAdjAttack(PathNode* node)
{
	// 4방향인가 8방향인가를 결정할 수 있다.
	TileIndex curIndex = node->Index;
	TileIndex checkIndex;
	std::map<__int64, _ljColTile*>::iterator TileDataIter;

	for (size_t i = 0; i < TILEDIR_MAX; ++i)
	{
		checkIndex = curIndex + mDirArr[i];

		if (mOpenIndexSet.end() != mOpenIndexSet.find(checkIndex.Index))
		{
			continue;
		}

		if (mClosedIndexSet.end() != mClosedIndexSet.find(checkIndex.Index))
		{
			continue;
		}

		mTileIter = mAllTile.find(checkIndex.Index);

		if (mAllTile.end() == mTileIter)
		{
			continue;
		}

		// 갈 수 없는 타일
		if (false == mTileIter->second->IsMovable())
		{
			continue;
		}

		// 이미 다른 캐릭터가 있다.
		if (nullptr != mTileIter->second->GetActor())
		{
			if (checkIndex == mEndIndex)
			{
				return true;
			}

			continue;
		}

		mEndNode = CreateOpenPathNode(checkIndex, node);

		if (checkIndex == mEndIndex)
		{
			return true;
		}
	}

	mEndNode = nullptr;

	return false;
}





_ljColMap::PathNode* _ljColMap::OpenListPop()
{
	if (0 >= mOpenList.size())
	{
		return nullptr;
	}

	std::multimap<float, PathNode*>::iterator popNode = mOpenList.begin();
	PathNode* returnNode = popNode->second;
	mOpenList.erase(popNode);
	mOpenIndexSet.erase(returnNode->Index.Index);

	mClosedList.insert(std::multimap<__int64, PathNode*>::value_type(returnNode->Index.Index, returnNode));

	FindAdj(returnNode);

	return returnNode;
}

_ljColMap::PathNode* _ljColMap::OpenListPopAttack()
{
	if (0 >= mOpenList.size())
	{
		return nullptr;
	}

	std::multimap<float, PathNode*>::iterator popNode = mOpenList.begin();
	PathNode* returnNode = popNode->second;
	mOpenList.erase(popNode);
	mOpenIndexSet.erase(returnNode->Index.Index);

	mClosedList.insert(std::multimap<__int64, PathNode*>::value_type(returnNode->Index.Index, returnNode));

	FindAdjAttack(returnNode);

	return returnNode;
}





void _ljColMap::ResetPool()
{
	mCount = 0;

	mCurNodeIter = PathNodePool.begin();

	mOpenList.clear();
	mOpenIndexSet.clear();
	mClosedList.clear();
}

// 둘다 월드 포지션
std::list<_ljVector> _ljColMap::PathFind(_ljVector startPos, _ljVector endPos)
{
	mOpenList;
	mClosedList;

	std::list<_ljVector> tempPath;

	if (PosToIndex(startPos) == PosToIndex(endPos))
	{
		return tempPath;
	}

	TileIndex startIndex = PosToIndex(startPos);
	mEndIndex = PosToIndex(endPos);

	// 찍은 곳이 갈수 없는 곳이라면 아웃
	if (nullptr == GetTile(mEndIndex.X, mEndIndex.Y) ||
		false == GetTile(mEndIndex.X, mEndIndex.Y)->IsMovable())
	{
		return tempPath;
	}

	CreateOpenPathNode(startPos, nullptr);

	while (nullptr == mEndNode && 0 < mOpenList.size())
	{
		OpenListPop();

		++mCount;

		if (600 < mCount)
		{
			mEndNode = nullptr;
			ResetPool();

			tempPath.clear();

			return tempPath;
		}
	}

	while (nullptr != mEndNode)
	{
		TileIndex endIndex = mEndNode->Index;

		// 타일의 월드 포지션
		_ljVector pos;

		pos.X = (endIndex.X * QUARTER_TILE_WIDTH) + (endIndex.Y * -QUARTER_TILE_WIDTH);
		pos.Y = (endIndex.X * QUARTER_TILE_HEIGHT) + (endIndex.Y * QUARTER_TILE_HEIGHT) - TILE_SUBOFFSETY / 2;

		/*_ljColTile* tempTile = FindTile(endIndex.X, endIndex.Y);
		pos = tempTile->mPos;*/

		tempPath.push_front(pos);

		mEndNode = mEndNode->Parent;

		if (600 < tempPath.size())
		{
			mEndNode = nullptr;
			ResetPool();

			tempPath.clear();

			return tempPath;
		}
	}

	mEndNode = nullptr;

	ResetPool();

	return tempPath;
}

std::list<_ljVector> _ljColMap::PathFind(TileIndex startPos, TileIndex endPos)
{
	std::list<_ljVector> tempPath;

	if (startPos == endPos)
	{
		return tempPath;
	}

	TileIndex startIndex = startPos;
	mEndIndex = endPos;

	// 찍은 곳이 갈수 없는 곳이라면 아웃
	if (nullptr == GetTile(mEndIndex.X, mEndIndex.Y) ||
		false == GetTile(mEndIndex.X, mEndIndex.Y)->IsMovable())
	{
		return tempPath;
	}

	CreateOpenPathNode(startPos, nullptr);

	while (nullptr == mEndNode && 0 < mOpenList.size())
	{
		OpenListPop();

		++mCount;

		if (600 < mCount)
		{
			mEndNode = nullptr;
			ResetPool();

			tempPath.clear();

			return tempPath;
		}
	}

	while (nullptr != mEndNode)
	{
		TileIndex endIndex = mEndNode->Index;

		// 타일의 월드 포지션
		_ljVector pos;

		pos.X = (endIndex.X * QUARTER_TILE_WIDTH) + (endIndex.Y * -QUARTER_TILE_WIDTH);
		pos.Y = (endIndex.X * QUARTER_TILE_HEIGHT) + (endIndex.Y * QUARTER_TILE_HEIGHT) - TILE_SUBOFFSETY / 2;

		/*_ljColTile* tempTile = FindTile(endIndex.X, endIndex.Y);
		pos = tempTile->mPos;*/

		tempPath.push_front(pos);

		mEndNode = mEndNode->Parent;

		if (600 < tempPath.size())
		{
			mEndNode = nullptr;
			ResetPool();

			tempPath.clear();

			return tempPath;
		}
	}

	mEndNode = nullptr;

	ResetPool();

	return tempPath;
}

std::list<_ljVector> _ljColMap::PathFindSpecial(_ljVector startPos, _ljVector endPos)
{
	mOpenList;
	mClosedList;

	std::list<_ljVector> tempPath;

	if (PosToIndex(startPos) == PosToIndex(endPos))
	{
		return tempPath;
	}

	TileIndex startIndex = PosToIndex(startPos);
	mEndIndex = PosToIndex(endPos);

	// 찍은 곳이 갈수 없는 곳이라면 아웃
	if (nullptr == GetTile(mEndIndex.X, mEndIndex.Y))
	{
		return tempPath;
	}

	CreateOpenPathNode(startPos, nullptr);

	while (nullptr == mEndNode && 0 < mOpenList.size())
	{
		OpenListPop();

		++mCount;

		if (600 < mCount)
		{
			mEndNode = nullptr;
			ResetPool();

			tempPath.clear();

			return tempPath;
		}
	}

	while (nullptr != mEndNode)
	{
		TileIndex endIndex = mEndNode->Index;

		// 타일의 월드 포지션
		_ljVector pos;

		pos.X = (endIndex.X * QUARTER_TILE_WIDTH) + (endIndex.Y * -QUARTER_TILE_WIDTH);
		pos.Y = (endIndex.X * QUARTER_TILE_HEIGHT) + (endIndex.Y * QUARTER_TILE_HEIGHT) - TILE_SUBOFFSETY / 2;

		/*_ljColTile* tempTile = FindTile(endIndex.X, endIndex.Y);
		pos = tempTile->mPos;*/

		tempPath.push_front(pos);

		mEndNode = mEndNode->Parent;

		if (600 < tempPath.size())
		{
			mEndNode = nullptr;
			ResetPool();

			tempPath.clear();

			return tempPath;
		}
	}

	mEndNode = nullptr;

	ResetPool();

	return tempPath;
}

std::list<_ljVector> _ljColMap::PathFindM(_ljVector startPos, _ljVector endPos)
{
	mOpenList;
	mClosedList;

	std::list<_ljVector> tempPath;

	// PathFindM의 이유
	if (PosToIndexM(startPos) == PosToIndex(endPos))
	{
		return tempPath;
	}

	// PathFindM의 이유
	TileIndex startIndex = PosToIndexM(startPos);
	mEndIndex = PosToIndex(endPos);

	// 찍은 곳이 갈수 없는 곳이라면 아웃
	if (nullptr == GetTile(mEndIndex.X, mEndIndex.Y) || false == GetTile(mEndIndex.X, mEndIndex.Y)->IsMovable())
	{
		return tempPath;
	}

	CreateOpenPathNode(startPos, nullptr);

	while (nullptr == mEndNode && 0 < mOpenList.size())
	{
		OpenListPop();

		++mCount;

		if (600 < mCount)
		{
			mEndNode = nullptr;
			ResetPool();

			tempPath.clear();

			return tempPath;
		}
	}

	while (nullptr != mEndNode)
	{
		TileIndex endIndex = mEndNode->Index;

		// 타일의 월드 포지션
		_ljVector pos;

		pos.X = (endIndex.X * QUARTER_TILE_WIDTH) + (endIndex.Y * -QUARTER_TILE_WIDTH);
		pos.Y = (endIndex.X * QUARTER_TILE_HEIGHT) + (endIndex.Y * QUARTER_TILE_HEIGHT) - TILE_SUBOFFSETY / 2;

		tempPath.push_front(pos);

		mEndNode = mEndNode->Parent;

		if (600 < tempPath.size())
		{
			mEndNode = nullptr;
			ResetPool();

			tempPath.clear();

			return tempPath;
		}
	}

	mEndNode = nullptr;

	ResetPool();

	return tempPath;
}

std::list<_ljVector> _ljColMap::PathFindAttackM(_ljVector startPos, _ljVector endPos)
{
	mOpenList;
	mClosedList;

	std::list<_ljVector> tempPath;

	if (PosToIndexM(startPos) == PosToIndex(endPos))
	{
		return tempPath;
	}

	TileIndex startIndex = PosToIndexM(startPos);
	mEndIndex = PosToIndex(endPos);



	if (nullptr == GetTile(mEndIndex.X, mEndIndex.Y) || false == GetTile(mEndIndex.X, mEndIndex.Y)->IsMovable())
	{
		return tempPath;
	}


	CreateOpenPathNode(startPos, nullptr);

	while (nullptr == mEndNode && 0 < mOpenList.size())
	{
		OpenListPopAttack();
	}

	while (nullptr != mEndNode)
	{
		TileIndex endIndex = mEndNode->Index;

		// 타일의 월드 포지션
		_ljVector pos;

		pos.X = (endIndex.X * QUARTER_TILE_WIDTH) + (endIndex.Y * -QUARTER_TILE_WIDTH);
		pos.Y = (endIndex.X * QUARTER_TILE_HEIGHT) + (endIndex.Y * QUARTER_TILE_HEIGHT) - TILE_SUBOFFSETY / 2;

		/*_ljColTile* tempTile = FindTile(endIndex.X, endIndex.Y);
		pos = tempTile->mPos;*/

		tempPath.push_front(pos);

		mEndNode = mEndNode->Parent;
	}

	mEndNode = nullptr;

	ResetPool();

	return tempPath;
}
