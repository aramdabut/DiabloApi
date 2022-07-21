#include "_ljMonster.h"
#include <_ljGameScene.h>
#include <_ljGameInput.h>
#include <_ljGameTime.h>
#include <_ljGameAniRenderer.h>
#include <_ljGameCollider.h>
#include <_ljGameWin.h>
#include <_ljGameRandomNum.h>
#include "_ljColMap.h"
#include "_ljRandomMap.h"
#include "_ljColTile.h"
#include "_ljItemMgr.h"

//★

/*
	속성 > C/C++ > 전처리기

	_DEBUG;_CONSOLE;%(PreprocessorDefinitions)
	NDEBUG;_CONSOLE;%(PreprocessorDefinitions)

	UNICODE;_UNICODE; %(PreprocessorDefinitions); X64;DEBUGMODE;
	UNICODE;_UNICODE; %(PreprocessorDefinitions); X64;RELEASEMODE;

*/

// #pragma comment(lib, "_ljGameApiBase.lib")
// #pragma comment(lib, "_ljGameApiBase_D64.lib")

//#ifdef RELEASEMODE
//#ifdef X32
//#pragma comment(lib, "_ljGameApiBase_R32.lib")
//#else X64
//#pragma comment(lib, "_ljGameApiBase_R64.lib")
//#endif
//#else DEBUGMODE
//#ifdef X32
//#pragma comment(lib, "_ljGameApiBase_D32.lib")
//#else X64
//#pragma comment(lib, "_ljGameApiBase_D64.lib")
//#endif
//#endif


_ljMonster::_ljMonster(_ljColMap* colmap, _ljRandomMap* randomMap)
	: mColMap(colmap)
	, mRandomMap(randomMap)
	, mIsDying(false)
	, mIsChangingPath(false)
	, mMoveSpeed(3.f)
	, mCurDestination(_ljVector::ZERO)
	, mDestDibTile(nullptr)
	, mStart(_ljVector::ZERO)
	, mIsMoving(false)
	, mIsAttacking(false)
	, mAttacked(false)
	, mIsResting(false)
	, mGoingToAttack(false)
	, mVision(0)
{

}

_ljMonster::_ljMonster(const _ljMonster& other)
{

}


_ljMonster::~_ljMonster()
{



}

// 자신의 위치에 따라서 Index를 계산한다.
void _ljMonster::CalIndex()
{
	_ljVector pos = CalPos();

	_ljColTile* temp = mColMap->GetTile(pos.X, pos.Y);

	if (nullptr == temp)
	{
		return;
	}


	mTileIndex = temp->GetTileIndex();

	_ljVector tempDib = mRandomMap->SubToDib(mTileIndex.X, mTileIndex.Y);

	mDibTile = mRandomMap->mAllTile[tempDib.IntY()][tempDib.IntX()];
}

void _ljMonster::Update()
{
}

void _ljMonster::DebugRender()
{
}

void _ljMonster::SetCurPos(int indexX, int indexY)
{
	// 만들 곳을 못 찾으면 삭제

	TileIndex temp = mColMap->SetActorIndex(indexX, indexY, this);

	if (TileIndex({ -1,-1 }) == temp)
	{
		KillThis();

		return;
	}

	mTileIndex.X = temp.X;
	mTileIndex.Y = temp.Y;

	mPrevTileIndex = mTileIndex;

	float x = (mTileIndex.X * QUARTER_TILE_WIDTH) + (mTileIndex.Y * -QUARTER_TILE_WIDTH);
	float y = (mTileIndex.X * QUARTER_TILE_HEIGHT) + (mTileIndex.Y * QUARTER_TILE_HEIGHT) - TILE_SUBOFFSETY / 2;

	Pos({ x, y });
	mStart = Pos();
	// Scene()->CamMove({ x, y });
}


bool _ljMonster::SetUnit()
{
	// 플레이어의 현재 위치에 따른 Index 얻어내기

	if (true == mIsDead)
	{
		return false;
	}

	CalIndex();

	if (mPrevTileIndex.Index != mTileIndex.Index)
	{
		if (mTileIndex.X <= 0)
		{
			return false;
		}

		if (mTileIndex.Y <= 0)
		{
			return false;
		}

		// 지도의 타일에 플레이어를 설정, 해제 해준다. 
		bool set = mColMap->UpdateActorIndex(mTileIndex.X, mTileIndex.Y, mPrevTileIndex.X, mPrevTileIndex.Y, this);

		if (false == set)
		{
			return set;
		}

		mPrevTileIndex = mTileIndex;

	}

	SetTileIndex(mTileIndex);

	mX = mDibTile->mX;
	mY = mDibTile->mY;

	//mRandomMap->mAllTile[mY + 1][mX]->mWallRenderer->SetBF(20);
	//// mRandomMap->mAllTile[mY][mX + 1]->mWallRenderer->SetBF(20);
	//// mRandomMap->mAllTile[mY - 1][mX]->mWallRenderer->SetBF(20);
	//// mRandomMap->mAllTile[mY][mX - 1]->mWallRenderer->SetBF(20);
	//mRandomMap->mAllTile[mY + 1][mX + 1]->mWallRenderer->SetBF(20);
	//// mRandomMap->mAllTile[mY - 1][mX - 1]->mWallRenderer->SetBF(20);
	//// mRandomMap->mAllTile[mY - 1][mX + 1]->mWallRenderer->SetBF(20);
	//mRandomMap->mAllTile[mY + 1][mX - 1]->mWallRenderer->SetBF(20);

	return true;
}


bool _ljMonster::SetDir(TileIndex index)
{
	TileIndex test = index;

	_ljVector dest;

	dest.X = (test.X * QUARTER_TILE_WIDTH) + (test.Y * -QUARTER_TILE_WIDTH);
	dest.Y = (test.X * QUARTER_TILE_HEIGHT) + (test.Y * QUARTER_TILE_HEIGHT) - TILE_SUBOFFSETY / 2;

	float x = Pos().X - dest.X;
	float y = Pos().Y - dest.Y;

	float temp = sqrtf(x * x + y * y);

	float newX = x / temp;
	float newY = y / temp;

	_ljVector newDir = _ljVector(newX, newY);

	if (_ljVector(-1.f, 0.f) == newDir)
	{
		mDir = RT;
	}
	else if (_ljVector(1.f, 0.f) == newDir)
	{
		mDir = LB;
	}
	else if (_ljVector(0.f, -1.f) == newDir)
	{
		mDir = RB;
	}
	else if (_ljVector(0.f, 1.f) == newDir)
	{
		mDir = LT;
	}
	else if (_ljVector(0.894427180f, 0.447213590f) == newDir)
	{
		mDir = L;
	}
	else if (_ljVector(-0.894427180f, 0.447213590f) == newDir)
	{
		mDir = T;
	}
	else if (_ljVector(-0.894427180f, -0.447213590f) == newDir)
	{
		mDir = R;
	}
	else if (_ljVector(0.894427180f, -0.447213590f) == newDir)
	{
		mDir = B;
	}
	else
	{

	}

	return true;
}

bool _ljMonster::SetDir(_ljColTile* tile)
{
	if (nullptr == tile)
	{
		return false;
	}

	TileIndex test = tile->GetTileIndex();

	_ljVector dest;

	dest.X = (tile->GetTileIndex().X * QUARTER_TILE_WIDTH) + (tile->GetTileIndex().Y * -QUARTER_TILE_WIDTH);
	dest.Y = (tile->GetTileIndex().X * QUARTER_TILE_HEIGHT) + (tile->GetTileIndex().Y * QUARTER_TILE_HEIGHT) - TILE_SUBOFFSETY / 2;

	float x = Pos().X - dest.X;
	float y = Pos().Y - dest.Y;

	float temp = sqrtf(x * x + y * y);

	float newX = x / temp;
	float newY = y / temp;

	_ljVector newDir = _ljVector(newX, newY);

	if (_ljVector(-1.f, 0.f) == newDir)
	{
		mDir = RT;
	}
	else if (_ljVector(1.f, 0.f) == newDir)
	{
		mDir = LB;
	}
	else if (_ljVector(0.f, -1.f) == newDir)
	{
		mDir = RB;
	}
	else if (_ljVector(0.f, 1.f) == newDir)
	{
		mDir = LT;
	}
	else if (_ljVector(0.894427180f, 0.447213590f) == newDir)
	{
		mDir = L;
	}
	else if (_ljVector(-0.894427180f, 0.447213590f) == newDir)
	{
		mDir = T;
	}
	else if (_ljVector(-0.894427180f, -0.447213590f) == newDir)
	{
		mDir = R;
	}
	else if (_ljVector(0.894427180f, -0.447213590f) == newDir)
	{
		mDir = B;
	}
	else
	{

	}

	return true;
}

bool _ljMonster::SetDir(_ljVector pos)
{
	mIsAttacking = false;

	float x = Pos().X - pos.X;
	float y = Pos().Y - pos.Y;

	float temp = sqrtf(x * x + y * y);

	float newX = x / temp;
	float newY = y / temp;

	_ljVector newDir = _ljVector(newX, newY);

	if (_ljVector(-1.f, 0.f) == newDir)
	{
		mDir = RT;
	}
	else if (_ljVector(1.f, 0.f) == newDir)
	{
		mDir = LB;
	}
	else if (_ljVector(0.f, -1.f) == newDir)
	{
		mDir = RB;
	}
	else if (_ljVector(0.f, 1.f) == newDir)
	{
		mDir = LT;
	}
	else if (_ljVector(0.894427180f, 0.447213590f) == newDir)
	{
		mDir = L;
	}
	else if (_ljVector(-0.894427180f, 0.447213590f) == newDir)
	{
		mDir = T;
	}
	else if (_ljVector(-0.894427180f, -0.447213590f) == newDir)
	{
		mDir = R;
	}
	else if (_ljVector(0.894427180f, -0.447213590f) == newDir)
	{
		mDir = B;
	}
	else
	{
		mDir = RB;
		Pos(mStart);
		//////////////////////////////////////// 버그지만 자연스럽게 넘기자
	}

	return true;
}

void _ljMonster::CalDir(_ljVector pos)
{
	mIsAttacking = false;

	_ljVector newPos = { pos.X - 32, pos.Y - 16 };

	_ljVector tempPos = CalPos() - _ljVector(32.f, 10.f);

	float x = tempPos.X - newPos.X;
	float y = tempPos.Y - newPos.Y;

	float temp = sqrtf(x * x + y * y);

	float newX = x / temp;
	float newY = y / temp;

	_ljVector newDir = _ljVector(-newX, -newY);

	_ljVector newOffset = { newDir.X * 40, newDir.Y * 32 };
	_ljVector test = newOffset;

	//////////////////////////////////////////////////////////////////////////////
	int intX = (int)std::roundf((test.X / QUARTER_TILE_WIDTH + test.Y / QUARTER_TILE_HEIGHT) / 2);
	int intY = (int)std::roundf((test.Y / QUARTER_TILE_HEIGHT + -(test.X / QUARTER_TILE_WIDTH)) / 2);

	TileIndex returnIndex;
	returnIndex.X = intX;
	returnIndex.Y = intY;
	//////////////////////////////////////////////////////////////////////////////

	int testX = (int)roundf(-newX);
	int testY = (int)roundf(-newY);

	TileIndex tempIndex = GetTileIndex() + returnIndex;
	_ljColTile* tempTile = mColMap->FindTile(tempIndex.X, tempIndex.Y);

	_ljVector dirPos = mColMap->IndexToPosM(tempIndex);

	SetDir(dirPos);
}



void _ljMonster::ResetPosM(_ljMonster* monster)
{
	Pos(mStart);

	TileIndex cur = GetTileIndex();

	for (size_t i = 0; i < 8; ++i)
	{
		TileIndex temp = cur + _ljColMap::mDirArr[i];

		if (monster == mColMap->GetTile(temp.X, temp.Y)->GetActor())
		{
			mColMap->GetTile(temp.X, temp.Y)->UnsetActor();
		}
	}

	mPathList.clear();
}


void _ljMonster::GoingToAttackM(_ljMonster* player)
{
	_ljVector playerPos = player->CalPos();
	TileIndex playerIndex = player->GetTileIndex();
	_ljColTile* destTile = mColMap->GetTile(playerIndex.X, playerIndex.Y);

	// 클릭한 타일에 몬스터가 있다면!
	// 주변 타일 중 가장 가까운 타일로 간다.
	if (nullptr != destTile && nullptr != destTile->GetActor())
	{
		// mPathList = mColMap->PathFindAttack(CalPos(), playerPos);

		if (0 != mPathList.size())
		{
			mDestDibTile = mColMap->GetTile(playerIndex.X, playerIndex.Y);

			mPathList.pop_back();

			// 미리 한칸을 움직여서 겹치는 것을 방지!
			_ljVector first = mCurDestination;
			first -= CamPos();
			_ljColTile* firstTile = mColMap->GetTile(first.X, first.Y);
			firstTile->SetActor(this);

			mIsChangingPath = false;

			mGoingToAttack = true;
		}
	}
	else
	{
		mPathList = mColMap->PathFind(CalPos(), playerPos);

		if (0 != mPathList.size())
		{
			mPathList.pop_front();

			// 미리 한칸을 움직여서 겹치는 것을 방지!
			_ljVector first = mCurDestination;
			first -= CamPos();
			_ljColTile* firstTile = mColMap->GetTile(first.X, first.Y);
			firstTile->SetActor(this);

			mIsChangingPath = false;
		}
	}
}

void _ljMonster::SetMove()
{
}

void _ljMonster::SetMoveM()
{
}

void _ljMonster::NormalDrop()
{
	int ran = _ljGameRandomNum::GetRandomNumber(1, 100);

	if (ran <= 60)
	{
		return;
	}
	else if (ran <= 90)
	{
		DropMoney();
	}
	else
	{
		DropItem();
	}
}

void _ljMonster::DropMoney()
{
	TileIndex myIndex = GetTileIndex();
	_ljColTile* myTile = mColMap->FindTile(myIndex.X, myIndex.Y);

	for (int i = 0; i < 8; ++i)
	{
		myTile = mColMap->FindTile(myIndex + mColMap->mDirArr[i]);

		if (nullptr == myTile->GetItem() && true == myTile->IsMovable())
		{
			int ran = _ljGameRandomNum::GetRandomNumber(1, 36);
			if (ran == 0)
			{
				ran = 2;
			}
			_ljItemMgr::DropMoney(myIndex + mColMap->mDirArr[i], ran, mLevel);

			return;
		}
	}
}

void _ljMonster::DropItem()
{
	TileIndex myIndex = GetTileIndex();
	_ljColTile* myTile = mColMap->FindTile(myIndex.X, myIndex.Y);

	for (int i = 0; i < 8; ++i)
	{
		myTile = mColMap->FindTile(myIndex + mColMap->mDirArr[i]);

		if (nullptr == myTile->GetItem() && true == myTile->IsMovable())
		{
			if (1 == mData.dlevel)
			{
				int ran = _ljGameRandomNum::GetRandomNumber(1, 14);
				ran -= 1;
				switch (ran)
				{
				case 0:
					// _ljGameSound::SoundPlay(L"flipswor.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"axe", 5, mLevel);
					break;
				case 1:
					// 	_ljGameSound::SoundPlay(L"flipswor.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"short sword", 0, mLevel);

					break;
				case 2:
					// 	_ljGameSound::SoundPlay(L"flipswor.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"sabre", 1, mLevel);
					break;
				case 3:
					// 	_ljGameSound::SoundPlay(L"fliplarm.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"rags", 6, mLevel);
					break;
				case 4:
					// 	_ljGameSound::SoundPlay(L"fliplarm.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"robe", 7, mLevel);
					break;
				case 5:
					// 	_ljGameSound::SoundPlay(L"flipcap.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"cap", 18, mLevel);
					break;
				case 6:
					// 	_ljGameSound::SoundPlay(L"flipcap.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"skull cap", 19, mLevel);
					break;
				case 7:
					// 	_ljGameSound::SoundPlay(L"flipshld.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"buckler", 12, mLevel);
					break;
				case 8:
					// 	_ljGameSound::SoundPlay(L"flipshld.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"small shield", 19, mLevel);
					break;
				case 9:
					// 	_ljGameSound::SoundPlay(L"flipring.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"ring", 21, mLevel);
					break;
				case 10:
					// 	_ljGameSound::SoundPlay(L"flippot.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"potion of healing", 24, mLevel);
					break;
				case 11:
					// 	_ljGameSound::SoundPlay(L"flippot.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"potion of mana", 25, mLevel);
					break;
				case 12:
					// _ljGameSound::SoundPlay(L"flippot.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"potion of rejuvenation", 26, mLevel);
					break;
				case 13:
					// _ljGameSound::SoundPlay(L"flipscrl.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"scroll of identify", 27, mLevel);
					break;
				case 14:
					// 	_ljGameSound::SoundPlay(L"flipscrl.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"scroll of town portal", 28, mLevel);
					break;
				default:
					BOOM;
					break;
				}
			}
			else
			{
				int ran = _ljGameRandomNum::GetRandomNumber(1, 23);
				ran -= 1;
				switch (ran)
				{
				case 0:
					// _ljGameSound::SoundPlay(L"flipswor.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"axe", 5, mLevel);
					break;
				case 1:
					// _ljGameSound::SoundPlay(L"flipswor.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"short sword", 0, mLevel);
					break;
				case 2:
					// _ljGameSound::SoundPlay(L"flipswor.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"sabre", 1, mLevel);
					break;
				case 3:
					// _ljGameSound::SoundPlay(L"fliplarm.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"rags", 6, mLevel);
					break;
				case 4:
					// _ljGameSound::SoundPlay(L"fliplarm.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"robe", 7, mLevel);
					break;
				case 5:
					// _ljGameSound::SoundPlay(L"flipcap.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"cap", 18, mLevel);
					break;
				case 6:
					// _ljGameSound::SoundPlay(L"flipcap.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"skull cap", 19, mLevel);
					break;
				case 7:
					// _ljGameSound::SoundPlay(L"flipshld.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"buckler", 12, mLevel);
					break;
				case 8:
					// _ljGameSound::SoundPlay(L"flipshld.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"small shield", 19, mLevel);
					break;
				case 9:
					// _ljGameSound::SoundPlay(L"flipring.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"ring", 21, mLevel);
					break;
				case 10:

					// _ljGameSound::SoundPlay(L"flippot.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"potion of healing", 24, mLevel);
					break;
				case 11:
					// _ljGameSound::SoundPlay(L"flippot.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"potion of mana", 25, mLevel);
					break;
				case 12:
					// 	_ljGameSound::SoundPlay(L"flippot.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"potion of rejuvenation", 26, mLevel);
					break;
				case 13:
					// _ljGameSound::SoundPlay(L"flipscrl.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"scroll of identify", 27, mLevel);
					break;
				case 14:
					// _ljGameSound::SoundPlay(L"flipscrl.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"scroll of town portal", 28, mLevel);
					break;
				case 15:
					// _ljGameSound::SoundPlay(L"flipswor.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"scimitar", 2, mLevel);
					break;
				case 16:
					// _ljGameSound::SoundPlay(L"flipswor.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"long sword", 3, mLevel);
					break;
				case 17:
					// _ljGameSound::SoundPlay(L"flipswor.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"bastard sword", 4, mLevel);
					break;
				case 18:
					// _ljGameSound::SoundPlay(L"fliplarm.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"leather armor", 8, mLevel);
					break;
				case 19:
					// _ljGameSound::SoundPlay(L"fliplarm.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"studded leather armor", 9, mLevel);
					break;
				case 20:
					// _ljGameSound::SoundPlay(L"flipcap.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"helm", 20, mLevel);
					break;
				case 21:
					// _ljGameSound::SoundPlay(L"flipshld.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"large shield", 14, mLevel);
					break;
				case 22:
					// _ljGameSound::SoundPlay(L"flipring.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"amulet", 22, mLevel);
					break;
				case 23:
					// _ljGameSound::SoundPlay(L"flipharm.wav");
					_ljItemMgr::DropItem(myIndex + mColMap->mDirArr[i], L"chain mail", 10, mLevel);
					break;
				default:
					BOOM;
					break;
				}
			}

			return;
		}

		return;
	}
}
