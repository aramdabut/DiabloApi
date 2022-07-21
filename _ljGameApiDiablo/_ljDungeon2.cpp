#include "_ljDungeon2.h"
#include <_ljGameInput.h>
#include <_ljGameRandomNum.h>
#include <_ljGameWin.h>
#include <_ljGameTextureMgr.h>
#include "_ljItemMgr.h"
#include "_ljItem.h"
#include "_ljPlayer.h"
#include "_ljMapTester.h"
#include "_ljRandomMap.h"
#include "_ljColMap.h"
#include "_ljMonster.h"
#include "_ljSkeleton.h"
#include "_ljDungeon18.h"
#include "_ljTile.h"
#include "_ljRoom.h"
#include "_ljObject.h"
#include "_ljSkeleton.h"
#include "_ljSkeleton2.h"
#include "_ljButcher.h"
#include "_ljFallen.h"
#include "_ljFallen2.h"
#include "_ljGoatMan.h"
#include "_ljScavenger.h"
#include "_ljZombie.h"
#include "_ljBat.h"
#include "_ljCursor.h"
#include "_ljFade.h"


_ljDungeon2::_ljDungeon2()
{
}


_ljDungeon2::~_ljDungeon2()
{
	if (nullptr != mMap1)
	{
		delete mMap1;
		mMap1 = nullptr;
	}

	if (nullptr != mMap2)
	{
		delete mMap2;
		mMap2 = nullptr;
	}
}

void _ljDungeon2::Loading()
{
	mMouse = new _ljCursor();

	mLevel = 4;

	_ljGameScene::Loading();

	SortOnOff(LO_UPTILE);
	SortOnOff(LO_DOWNTILE);

	mMap1 = new _ljRandomMap(this);

	MakeMap();

	mPlayer->SetLevel(mLevel);

	SetPlayer();

	SpawnMonsters();

	mFade = mPlayer->CreateRenderer<_ljFade>(LO_DEBUG);
}

void _ljDungeon2::SceneUpdate()
{
	if (true == mPlayer->mIsAllOver)
	{
		mIsFade = mFade->StartFadeOut();
	}

	_ljVector mouse = _ljGameWin::MainWindow()->MousePos();

	if (mMap1->ColMap() != _ljItemMgr::Inst()->GetColMap())
	{
		_ljItemMgr::Inst()->SetCurColMap(mMap1->ColMap());
	}

	if (_ljGameInput::Down(L"MOVET"))
	{
		mPlayer->SetCurPos(mMap1->GetBPos().X, mMap1->GetBPos().Y);
	}

	if (_ljGameInput::Down(L"MOVEB"))
	{
		ResetPos();
	}

	if (mPlayer->GetTileIndex().X == mMap1->GetStartPos1().X && mPlayer->GetTileIndex().Y == mMap1->GetStartPos1().Y)
	{
		mBGM->Stop();
		mIsFade = mFade->StartFadeOut();

		if (mIsFade == true)
		{
			mIsFade = false;
			SetCurScene(L"_ljDungeon18");

			mDungeon18->ResetPosFrom2();
		}

	}
	else if (mPlayer->GetTileIndex().X == mMap1->GetStartPos2().X && mPlayer->GetTileIndex().Y == mMap1->GetStartPos2().Y)
	{
		mBGM->Stop();

		mIsFade = mFade->StartFadeOut();

		if (mIsFade == true)
		{
			mIsFade = false;
			SetCurScene(L"_ljDungeon18");

			mDungeon18->ResetPosFrom2();
		}

	}
}

void _ljDungeon2::MakeMap()
{
	Make3RoomsY();

	// 윗방 가지치기
	mMap1->MakeRandomBRooms({ 15, 0 }, { 10, 10 }, RT_LEFT, 3, 3, 3, 3);
	mMap1->ResetCount();

	if (true == mMap1->HasBRoom())
	{
		mMap1->MakeRandomRooms({ 15, 0 }, { 10, 10 }, RT_RIGHT, 3, 3, 3, 3);
		mMap1->ResetCount();
	}
	else
	{
		mMap1->MakeRandomBRooms({ 15, 0 }, { 10, 10 }, RT_RIGHT, 3, 3, 3, 3);
		mMap1->ResetCount();
	}

	if (true == mMap1->HasBRoom())
	{
		// 중간방 가지치기
		mMap1->MakeRandomRooms({ 15, 14 }, { 10, 10 }, RT_LEFT, 3, 3, 3, 3);
		mMap1->ResetCount();
	}
	else
	{
		// 중간방 가지치기
		mMap1->MakeRandomBRooms({ 15, 14 }, { 10, 10 }, RT_LEFT, 3, 3, 3, 3);
		mMap1->ResetCount();
	}

	if (true == mMap1->HasBRoom())
	{
		mMap1->MakeRandomRooms({ 15, 14 }, { 10, 10 }, RT_RIGHT, 3, 3, 3, 3);
		mMap1->ResetCount();
	}
	else
	{
		mMap1->MakeRandomBRooms({ 15, 14 }, { 10, 10 }, RT_RIGHT, 3, 3, 3, 3);
		mMap1->ResetCount();
	}


	if (true == mMap1->HasBRoom())
	{
		// 막방 가지치기
		mMap1->MakeRandomRooms({ 15, 28 }, { 10, 10 }, RT_LEFT, 3, 3, 3, 3);
		mMap1->ResetCount();
	}
	else
	{
		// 막방 가지치기
		mMap1->MakeRandomBRooms({ 15, 28 }, { 10, 10 }, RT_LEFT, 3, 3, 3, 3);
		mMap1->ResetCount();
	}

	if (true == mMap1->HasBRoom())
	{
		mMap1->MakeRandomRooms({ 15, 28 }, { 10, 10 }, RT_RIGHT, 3, 3, 3, 3);
		mMap1->ResetCount();
	}
	else
	{
		mMap1->MakeRandomBRooms({ 15, 28 }, { 10, 10 }, RT_RIGHT, 3, 3, 3, 3);
		mMap1->ResetCount();
	}

	if (false == mMap1->HasBRoom())
	{
		mMap1->SetBRoom();
	}

	if (false == mMap1->HasBRoom())
	{
		BOOM;
	}

	// 마무리 (반드시 호출)
	mMap1->FinishMap();

	// 마무리 계단
	if (false == mMap1->HasDownstair())
	{
		_ljVector temp = _ljVector(15, 14);

		mMap1->MakeDownstair(temp);
	}

	if (nullptr == mPlayer)
	{
		mPlayer = new _ljPlayer(mMap1->ColMap(), mMap1);
	}
	else
	{
		mPlayer->Reset();
	}

	if (false == mPlayer->IsPosSet())
	{
		MakeMap();
	}
}

void _ljDungeon2::Make3RoomsY()
{
	// 상
	mMap1->MakeARoom({ 15, 0 }, { 10, 10 }, { 0, 0 }, { 0, 0 }, RT_MAX);
	mMap1->MakeTopEleven({ 17, 11 }, { 6, 2 }, { 15, 0 }, { 10, 10 });
	
	// 중
	mMap1->MakeARoom({ 15, 14 }, { 10, 10 }, { 0, 0 }, { 0, 0 }, RT_MAX);
	mMap1->MakeAConnection({ 15, 14 }, { 10, 10 }, { 17, 11 }, { 6, 2 }, RT_BOTTOM);
	mMap1->MakeTopEleven({ 17, 25 }, { 6, 2 }, { 15, 14 }, { 10, 10 });
	
	// 하
	mMap1->MakeARoom({ 15, 28 }, { 10, 10 }, { 0, 0 }, { 0, 0 }, RT_MAX);
	mMap1->MakeAConnection({ 15, 28 }, { 10, 10 }, { 17, 25 }, { 6, 2 }, RT_BOTTOM);

	mMap1->MakeArchY({ 17, 11 }, { 6, 2 }, { 15, 0 }, { 10, 10 });

	mMap1->MakeArchY({ 17, 25 }, { 6, 2 }, { 15, 14 }, { 10, 10 });

	mMap1->SetColumnAt(19, 4);
	mMap1->SetColumnAt(22, 4);

	mMap1->SetColumnAt(19, 7);
	mMap1->SetColumnAt(22, 7);

	mMap1->SetColumnAt(19, 18);
	mMap1->SetColumnAt(22, 18);

	mMap1->SetColumnAt(19, 21);
	mMap1->SetColumnAt(22, 21);

	mMap1->SetColumnAt(19, 32);
	mMap1->SetColumnAt(22, 32);

	mMap1->SetColumnAt(19, 35);
	mMap1->SetColumnAt(22, 35);


}

void _ljDungeon2::Make3RoomsX()
{
	mMap1->MakeARoom({ 0, 14 }, { 10, 10 }, { 0, 0 }, { 0, 0 }, RT_MAX);
	mMap1->MakeARoom({ 11, 16 }, { 2, 6 }, { 0, 0 }, { 0, 0 }, RT_MAX);

	mMap1->MakeARoom({ 14, 14 }, { 10, 10 }, { 0, 0 }, { 0, 0 }, RT_MAX);
	mMap1->MakeARoom({ 25, 16 }, { 2, 6 }, { 0, 0 }, { 0, 0 }, RT_MAX);

	mMap1->MakeARoom({ 28, 14 }, { 10, 10 }, { 0, 0 }, { 0, 0 }, RT_MAX);

	mMap1->SetColumnAt(4, 18);
	mMap1->SetColumnAt(8, 18);

	mMap1->SetColumnAt(4, 21);
	mMap1->SetColumnAt(8, 21);

	mMap1->SetColumnAt(18, 18);
	mMap1->SetColumnAt(21, 18);

	mMap1->SetColumnAt(18, 21);
	mMap1->SetColumnAt(21, 21);

	mMap1->SetColumnAt(32, 18);
	mMap1->SetColumnAt(35, 18);

	mMap1->SetColumnAt(32, 21);
	mMap1->SetColumnAt(35, 21);

}

void _ljDungeon2::SetPlayer()
{
	_ljColMap* colMap = mMap1->ColMap();

	colMap->SetPlayer(mPlayer);
}

void _ljDungeon2::SetLevel(int level)
{
	// int a = 0;
}

// 넘어올때 1층에서 호출한다.
void _ljDungeon2::ResetPos()
{
	// TestScene에서의 플레이어 정보를 받아온다.
	_ljPlayer* tempP = mDungeon18->GetPlayer();

	mPlayer->CopyPlayer(tempP);
	_ljObject::SetPlayer(mPlayer);
	std::list<_ljItem*>::iterator iter = tempP->mItemList.begin();
	std::list<_ljItem*>::iterator iterEnd = tempP->mItemList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (nullptr != *iter)
		{
			_ljItem* tempI = new _ljItem(*(*iter));
			tempI->mPlayer = mPlayer;
			mPlayer->SuperAcquire(tempI, tempI->mBase);
			// tempI->SetInven(tempI->mInven->SubPos());
		}
	}

	mPlayer->ResetDir();
	mPlayer->SetCurPos(mMap1->GetStartPos1().X, mMap1->GetStartPos1().Y + 1);

	_ljItemMgr::Inst()->SetCurColMap(mMap1->ColMap());

	if (nullptr != tempP->mWeapon)
	{
		_ljItem* tempI = new _ljItem(*tempP->mWeapon);
		tempI->mPlayer = mPlayer;
		tempI->mIsTaken = true;
		tempI->ArmWeapon();
	}


	if (nullptr != tempP->mArmor)
	{
		_ljItem* tempI = new _ljItem(*tempP->mArmor);
		tempI->mPlayer = mPlayer;
		tempI->mIsTaken = true;
		tempI->ArmArmor();
	}

	if (nullptr != tempP->mShield)
	{
		_ljItem* tempI = new _ljItem(*tempP->mShield);
		tempI->mPlayer = mPlayer;
		tempI->mIsTaken = true;
		tempI->ArmShield();
	}

	if (nullptr != tempP->mHelm)
	{
		_ljItem* tempI = new _ljItem(*tempP->mHelm);
		tempI->mPlayer = mPlayer;
		tempI->mIsTaken = true;
		tempI->ArmHelm();
	}

	if (nullptr != tempP->mLRing)
	{
		_ljItem* tempI = new _ljItem(*tempP->mLRing);
		tempI->mPlayer = mPlayer;
		tempI->mIsTaken = true;
		tempI->ArmLRing();
	}

	if (nullptr != tempP->mRRing)
	{
		_ljItem* tempI = new _ljItem(*tempP->mRRing);
		tempI->mPlayer = mPlayer;
		tempI->mIsTaken = true;
		tempI->ArmRRing();
	}

	if (nullptr != tempP->mNeck)
	{
		_ljItem* tempI = new _ljItem(*tempP->mNeck);
		tempI->mPlayer = mPlayer;
		tempI->mIsTaken = true;
		tempI->ArmNeck();
	}
}

void _ljDungeon2::SpawnMonsters()
{
	int size = 0;
	int ran = 0;
	int x = 0;
	int y = 0;

	int roomSize = (mMap1->GetAllRoom()).size();

	for (size_t i = 0; i < roomSize; ++i)
	{
		if (true == mMap1->GetAllRoom()[i]->mIsStartRoom)
		{
			continue;
		}

		int temp = mMap1->GetAllRoom()[i]->Size.IntX();

		size = _ljGameRandomNum::GetRandomNumber(2, mMap1->GetAllRoom()[i]->Size.IntX());

		if (size > 8)
		{
			size = 8;
		}

		for (int j = 0; j < size; ++j)
		{
			ran = _ljGameRandomNum::GetRandomNumber(1, 8);

			x = mMap1->GetAllRoom()[i]->LeftTop().IntX() * 2 + ran + j;
			y = mMap1->GetAllRoom()[i]->LeftTop().IntY() * 2 + ran + j;

			if (true == mMap1->GetAllRoom()[i]->mIsButcher)
			{
				continue;
			}

			_ljMonster* sk = nullptr;

			switch (ran)
			{
			case 1:
				sk = new _ljFallen(mMap1->ColMap(), mMap1, mPlayer, { x,y });
				break;

			case 2:
				sk = new _ljSkeleton(mMap1->ColMap(), mMap1, mPlayer, { x,y });
				break;

			case 3:
				sk = new _ljGoatMan(mMap1->ColMap(), mMap1, mPlayer, { x,y });
				//sk = new _ljZombie(mMap1->ColMap(), mMap1, mPlayer, { x,y });
				break;

			case 4:
				sk = new _ljFallen2(mMap1->ColMap(), mMap1, mPlayer, { x,y });
				// sk = new _ljScavenger(mMap1->ColMap(), mMap1, mPlayer, { x,y });
				break;

			case 5:
				sk = new _ljBat(mMap1->ColMap(), mMap1, mPlayer, { x,y });
				break;
			case 6:
				sk = new _ljSkeleton2(mMap1->ColMap(), mMap1, mPlayer, { x,y });
				break;
			case 7:
				sk = new _ljGoatMan(mMap1->ColMap(), mMap1, mPlayer, { x,y });
				break;
			case 8:
				sk = new _ljGoatMan(mMap1->ColMap(), mMap1, mPlayer, { x,y });
				break;

			default:
				BOOM;
				break;
			}

		}
	}

	_ljMonster* sk = new _ljButcher(mMap1->ColMap(), mMap1, mPlayer, mMap1->mBPos + TileIndex({ -2, -2 }));
}

void _ljDungeon2::Init()
{
	mBGM = _ljGameSound::SoundPlay(L"dlvld.mp3");
}

void _ljDungeon2::ResetMap()
{

	for (int i = 0; i < MAPCOUNT_Y; i++)
	{
		for (int j = 0; j < MAPCOUNT_X; j++)
		{
			mMap1->mAllTile[i][j]->mIsWall = true;
			mMap1->mAllTile[i][j]->mRoom = nullptr;
			mMap1->mAllTile[i][j]->mIsUpstair = false;
			mMap1->mAllTile[i][j]->mIsDownstair = false;
			mMap1->mAllTile[i][j]->mWallType = WT_NONE;
			mMap1->mAllTile[i][j]->mTileType = TT_INWALL;

			mMap1->mAllCopyTile[i][j]->mIsWall = true;
			mMap1->mAllCopyTile[i][j]->mRoom = nullptr;
			mMap1->mAllCopyTile[i][j]->mIsUpstair = false;
			mMap1->mAllCopyTile[i][j]->mIsDownstair = false;
			mMap1->mAllCopyTile[i][j]->mWallType = WT_NONE;
			mMap1->mAllCopyTile[i][j]->mTileType = TT_INWALL;
		}
	}

}
