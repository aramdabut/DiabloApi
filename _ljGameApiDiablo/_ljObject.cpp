#include "_ljObject.h"
#include <_ljGameAniRenderer.h>
#include "_ljPlayer.h"
#include <_ljGameSound.h>
#include <_ljGameRandomNum.h>
#include "_ljItemMgr.h"



std::vector<_ljObject*> _ljObject::mAllObject;


_ljObject::_ljObject()
{
	mAllObject.push_back(this);

	mAniRenderer1 = CreateAniRenderer(LO_UPTILE);
	mAniRenderer1->Image(L"DibDoor.bmp");
	mAniRenderer1->TransColor(255, 255, 255);
	mAniRenderer1->SubSize({ 129, 193 });

	mAniRenderer1->SubPos({ 44 + 3, -64 });
	mAniRenderer1->SetRenderStyle(RS_TRANS);
	mAniRenderer1->Off();

	mAniRenderer2 = CreateAniRenderer(LO_DOWNTILE);
	mAniRenderer2->Image(L"DibDoor.bmp");
	mAniRenderer2->TransColor(255, 255, 255);
	mAniRenderer2->SubSize({ 129, 193 });

	mAniRenderer2->SetRenderStyle(RS_TRANS);
	mAniRenderer2->Off();

	mFogRenderer1 = CreateRenderer<_ljGameRenderer>(LO_UPTILE);
	mFogRenderer1->SubSize({ TILE_WIDTH, TILE_HEIGHT + 2 });
	mFogRenderer1->Image(L"DibDoor.bmp");
	mFogRenderer1->TransColor(255, 255, 255);

	mFogRenderer1->SetRenderStyle(RS_ALPHA);
	mFogRenderer1->Off();

	mFogRenderer2 = CreateRenderer<_ljGameRenderer>(LO_DOWNTILE);
	mFogRenderer2->SubSize({ TILE_WIDTH, TILE_HEIGHT + 2 });
	mFogRenderer2->Image(L"DibDoor.bmp");
	mFogRenderer2->TransColor(255, 255, 255);
	mFogRenderer2->SubPos({ 44 + 3, -64 });
	mFogRenderer2->SetRenderStyle(RS_ALPHA);
	mFogRenderer2->Off();

	mObjectEdge = CreateRenderer<_ljGameRenderer>(LO_ITEMBACK);
	mObjectEdge->SubSize({ TILE_WIDTH, TILE_HEIGHT + 2 });
	mObjectEdge->Image(L"DibDoorEdge.bmp");
	mObjectEdge->TransColor(255, 255, 255);
	mObjectEdge->SubPos({ 44 + 3, -64 });
	mObjectEdge->SetRenderStyle(RS_BIT);
	mObjectEdge->Off();

	SetAnimation();
}

_ljObject::_ljObject(int index, _ljVector pos, TileIndex tileIndex)
{
	mAllObject.push_back(this);

	mAniRenderer1 = CreateAniRenderer(LO_UPTILE);
	mAniRenderer1->Image(L"DibDoor.bmp");
	mAniRenderer1->TransColor(255, 255, 255);
	mAniRenderer1->SubSize({ 129, 193 });
	mAniRenderer1->SubPos({ 44 + 3, -64 - 14 });
	mAniRenderer1->SetRenderStyle(RS_TRANS);
	mAniRenderer1->Off();

	mAniRenderer2 = CreateAniRenderer(LO_DOWNTILE);
	mAniRenderer2->Image(L"DibDoor.bmp");
	mAniRenderer2->TransColor(255, 255, 255);
	mAniRenderer2->SubSize({ 129, 193 });
	mAniRenderer2->SubPos({ 44 + 3, -64 - 14 });
	mAniRenderer2->SetRenderStyle(RS_TRANS);
	mAniRenderer2->Off();

	mFogRenderer1 = CreateRenderer<_ljGameRenderer>(LO_UPTILE);
	mFogRenderer1->SubSize({ TILE_WIDTH, TILE_HEIGHT + 2 });
	mFogRenderer1->Image(L"DibDoorBlack.bmp");
	mFogRenderer1->TransColor(255, 255, 255);
	mFogRenderer1->SubPos({ 44 + 3, -64 - 14 });
	mFogRenderer1->SetRenderStyle(RS_ALPHA);
	mFogRenderer1->Off();

	mFogRenderer2 = CreateRenderer<_ljGameRenderer>(LO_DOWNTILE);
	mFogRenderer2->SubSize({ TILE_WIDTH, TILE_HEIGHT + 2 });
	mFogRenderer2->Image(L"DibDoorBlack.bmp");
	mFogRenderer2->TransColor(255, 255, 255);
	mFogRenderer2->SubPos({ 44 + 3, -64 - 14 });
	mFogRenderer2->SetRenderStyle(RS_ALPHA);
	mFogRenderer2->Off();

	mObjectEdge = CreateRenderer<_ljGameRenderer>(LO_ITEMUP);
	mObjectEdge->SubSize({ TILE_WIDTH, TILE_HEIGHT + 2 });
	mObjectEdge->Image(L"DibDoorEdge.bmp");
	mObjectEdge->TransColor(255, 255, 255);
	mObjectEdge->SubPos({ 44 + 3, -64 - 14 });
	mObjectEdge->SetRenderStyle(RS_TRANS);
	mObjectEdge->Off();

	SetAnimation();

	mChestType = (CHEST_TYPE)index;

	Pos(pos);

	mX = tileIndex.X / 2;
	mY = tileIndex.Y / 2;
	
	mTileIndex = tileIndex;

	switch (mChestType)
	{
	case CHT_LDOOR:
		mIndex = 1;
		mAniRenderer1->SetCurrentAnimation(L"LDOOR");
		mAniRenderer2->SetCurrentAnimation(L"LDOOR");
		mName = L"closed door";
		break;
	case CHT_RDOOR:
		mIndex = 2;
		mAniRenderer1->SetCurrentAnimation(L"RDOOR");
		mAniRenderer2->SetCurrentAnimation(L"RDOOR");
		mName = L"closed door";
		break;
	case CHT_BARREL:
		mAniRenderer1->SetCurrentAnimation(L"BARREL");
		mAniRenderer2->SetCurrentAnimation(L"BARREL");
		mIndex = 15;
		mName = L"barrel";
		break;
	case CHT_SARCO:
		mAniRenderer1->SetCurrentAnimation(L"SARCO");
		mAniRenderer2->SetCurrentAnimation(L"SARCO");
		mIndex = 4;
		mName = L"sarcophagus";
		break;
	case CHT_SMALL:
		mIndex = 13;
		mAniRenderer1->SetCurrentAnimation(L"SMALL");
		mAniRenderer2->SetCurrentAnimation(L"SMALL");
		mName = L"small chest";
		break;
	case CHT_BIG:
		mAniRenderer1->SetCurrentAnimation(L"BIG");
		mAniRenderer2->SetCurrentAnimation(L"BIG");
		mIndex = 9;
		mName = L"large chest";
		break;
	case CHT_SILVER:
		mAniRenderer1->SetCurrentAnimation(L"SILVER");
		mAniRenderer2->SetCurrentAnimation(L"SILVER");
		mIndex = 11;
		mName = L"silver chest";
		break;
	case CHT_MAX:
		break;
	default:
		break;
	}

}


_ljObject::~_ljObject()
{
}

void _ljObject::Open()
{
	mIsOn = true;
}


void _ljObject::Update()
{
	if (mPlayer == nullptr)
	{
		return;
	}

	TileIndex tileIndex = { mX, mY };

	TileIndex playerTileIndex = mPlayer->DibTileIndex();


	TileIndex tileDis = tileIndex - playerTileIndex;
	TileIndex lastDis;

	lastDis.X = abs(tileDis.X);
	lastDis.Y = abs(tileDis.Y);

	int gap = lastDis.X + lastDis.Y;

	gap = abs(gap);

	if (10 < gap)
	{
		mFogRenderer1->Off();
		mAniRenderer1->Off();
		mAniRenderer2->Off();
		mFogRenderer2->Off();
		return;
	}

	if (mPlayer->GetDibTile()->mX < mX || mPlayer->GetDibTile()->mY < mY)
	{
		mAniRenderer1->Off();
		mFogRenderer1->Off();
	}
	else
	{
		mAniRenderer1->On();
		mFogRenderer1->On();
	}


	if (mPlayer->GetDibTile()->mX >= mX && mPlayer->GetDibTile()->mY >= mY)
	{
		mAniRenderer2->Off();
		mFogRenderer2->Off();
	}
	else
	{
		mAniRenderer2->On();
		mFogRenderer2->On();
	}

	int mIncrease = 30;
	int mBase = 15;

	{
		if (1 >= gap)
		{
			mFogRenderer1->SetBF(15);
			mFogRenderer2->SetBF(15);
		}
		else if (2 >= gap)
		{
			mFogRenderer1->SetBF(mBase + mIncrease * 1);
			mFogRenderer2->SetBF(mBase + mIncrease * 1);
		}
		else if (3 >= gap)
		{
			mFogRenderer1->SetBF(mBase + mIncrease * 3);
			mFogRenderer2->SetBF(mBase + mIncrease * 3);
		}
		else if (4 >= gap)
		{
			mFogRenderer1->SetBF(mBase + mIncrease * 4);
			mFogRenderer2->SetBF(mBase + mIncrease * 4);
		}
		else if (5 >= gap)
		{
			mFogRenderer1->SetBF(mBase + mIncrease * 5);
			mFogRenderer2->SetBF(mBase + mIncrease * 5);
		}
		else if (6 >= gap)
		{
			mFogRenderer1->SetBF((int)(mBase + mIncrease * 6.5));
			mFogRenderer2->SetBF((int)(mBase + mIncrease * 6.5));
		}
		else if (7 >= gap)
		{
			mFogRenderer1->SetBF(mBase + mIncrease * 7);
			mFogRenderer2->SetBF(mBase + mIncrease * 7);
		}
		else
		{
			mFogRenderer1->SetBF(mBase + mIncrease * 7);
			mFogRenderer2->SetBF(mBase + mIncrease * 7);
		}

		if (mPlayer->GetMouseIndex() == GetTileIndex() && mOpenOver == false)
		{
			mObjectEdge->On();
		}
		else
		{
			mObjectEdge->Off();
		}
	}

	if (true == mOpenOver)
	{
		if (CHT_LDOOR == GetChestType() || CHT_RDOOR == GetChestType())
		{
			mAniRenderer1->CurFrame(mIndex);
			mAniRenderer2->CurFrame(mIndex);

			return;
		}

		if (true == mAniRenderer1->IsCurrentAnimationEnd())
		{
			mAniRenderer2->FinishAnimation();
			mFogRenderer1->ImageIndex(mAniRenderer2->CurFrame());
			mFogRenderer2->ImageIndex(mAniRenderer2->CurFrame());
		}
		if (true == mAniRenderer2->IsCurrentAnimationEnd())
		{
			mAniRenderer1->FinishAnimation();
			mFogRenderer1->ImageIndex(mAniRenderer1->CurFrame());
			mFogRenderer2->ImageIndex(mAniRenderer1->CurFrame());
		}

		return;
	}

	// ¿­¸²
	if (true == mIsOn)
	{
		switch (mChestType)
		{
		case CHT_LDOOR:
			_ljGameSound::SoundPlayToInst(L"dooropen.wav");
			mIndex = 0;
			mIsOn = false;
			mOpenOver = true;
			break;
		case CHT_RDOOR:
			_ljGameSound::SoundPlayToInst(L"dooropen.wav");
			mIndex = 3;
			mIsOn = false;
			mOpenOver = true;
			break;
		case CHT_BARREL:
			_ljGameSound::SoundPlayToInst(L"barrel.wav");
			mAniRenderer1->SetCurrentAnimation(L"BARREL");
			mAniRenderer2->SetCurrentAnimation(L"BARREL");
			mIsOn = false;
			mOpenOver = true;
			DropItem();
			break;
		case CHT_SARCO:
			_ljGameSound::SoundPlayToInst(L"sarc.wav");
			mAniRenderer1->SetCurrentAnimation(L"SARCO");
			mAniRenderer2->SetCurrentAnimation(L"SARCO");
			mIsOn = false;
			mOpenOver = true;
			DropItem();
			break;
		case CHT_SMALL:
			_ljGameSound::SoundPlayToInst(L"chest.wav");
			mIndex = 14;
			mIsOn = false;
			mOpenOver = true;
			DropItem();
			break;
		case CHT_BIG:
			_ljGameSound::SoundPlayToInst(L"chest.wav");
			mIndex = 10;
			mIsOn = false;
			mOpenOver = true;
			DropItem();
			break;
		case CHT_SILVER:
			_ljGameSound::SoundPlayToInst(L"chest.wav");
			mIndex = 12;
			mIsOn = false;
			mOpenOver = true;
			DropItem();
			break;
		case CHT_MAX:
			break;
		default:
			break;
		}


		mObjectEdge->Off();
	}


	mFogRenderer1->ImageIndex(mIndex);
	mFogRenderer2->ImageIndex(mIndex);
	mAniRenderer1->CurFrame(mIndex);
	mAniRenderer2->CurFrame(mIndex);

	mFogRenderer1->ImageIndex(mIndex);
	mFogRenderer2->ImageIndex(mIndex);

	mObjectEdge->ImageIndex(mIndex);
}

void _ljObject::DropItem()
{
	int rand = _ljGameRandomNum::GetRandomNumber(1, 100);
	{
		if (rand >= 75)
		{
			DropRealItem();
		}
		if (rand >= 50)
		{
			DropMoney();
		}
	}
	return;
}

void _ljObject::DropRealItem()
{
	TileIndex myIndex = GetTileIndex();
	_ljColTile* myTile = mPlayer->mColMap->FindTile(myIndex.X, myIndex.Y);

	TileIndex newIndex = myIndex + TileIndex({ 1, -1 });

	myTile = mPlayer->mColMap->FindTile(newIndex);

	if (nullptr == myTile->GetItem() && true == myTile->IsMovable())
	{
		int ran = 0;

		_ljItemMgr::DropItem(newIndex, L"potion of healing", 24, mPlayer->mLevel);

		if (false)
		{
			if (1 == mPlayer->mLevel || 2 == mPlayer->mLevel)
			{
				ran = _ljGameRandomNum::GetRandomNumber(1, 13);
				ran -= 1;
			}
			else
			{
				ran = _ljGameRandomNum::GetRandomNumber(1, 24);
				ran -= 1;
			}

			switch (ran)
			{
			case 0:
				// _ljGameSound::SoundPlay(L"flipswor.wav");
				_ljItemMgr::DropItem(newIndex, L"axe", 5, mPlayer->mLevel);
				break;
			case 1:
				// _ljGameSound::SoundPlay(L"flipswor.wav");
				_ljItemMgr::DropItem(newIndex, L"short sword", 0, mPlayer->mLevel);
				break;
			case 2:
				// _ljGameSound::SoundPlay(L"flipswor.wav");
				_ljItemMgr::DropItem(newIndex, L"sabre", 1, mPlayer->mLevel);
				break;
			case 3:
				// _ljGameSound::SoundPlay(L"fliplarm.wav");
				_ljItemMgr::DropItem(newIndex, L"rags", 6, mPlayer->mLevel);
				break;
			case 4:
				// _ljGameSound::SoundPlay(L"fliplarm.wav");
				_ljItemMgr::DropItem(newIndex, L"robe", 7, mPlayer->mLevel);
				break;
			case 5:
				// _ljGameSound::SoundPlay(L"flipcap.wav");
				_ljItemMgr::DropItem(newIndex, L"cap", 18, mPlayer->mLevel);
				break;
			case 6:
				// _ljGameSound::SoundPlay(L"flipcap.wav");
				_ljItemMgr::DropItem(newIndex, L"skull cap", 19, mPlayer->mLevel);
				break;
			case 7:
				// _ljGameSound::SoundPlay(L"flipshld.wav");
				_ljItemMgr::DropItem(newIndex, L"buckler", 12, mPlayer->mLevel);
				break;
			case 8:
				// _ljGameSound::SoundPlay(L"flipshld.wav");
				_ljItemMgr::DropItem(newIndex, L"small shield", 19, mPlayer->mLevel);
				break;
			case 9:
				// _ljGameSound::SoundPlay(L"flipring.wav");
				_ljItemMgr::DropItem(newIndex, L"ring", 21, mPlayer->mLevel);
				break;
			case 10:

				// _ljGameSound::SoundPlay(L"flippot.wav");
				_ljItemMgr::DropItem(newIndex, L"potion of healing", 24, mPlayer->mLevel);
				break;
			case 11:
				// _ljGameSound::SoundPlay(L"flippot.wav");
				_ljItemMgr::DropItem(newIndex, L"potion of mana", 25, mPlayer->mLevel);
				break;
			case 12:
				// 	_ljGameSound::SoundPlay(L"flippot.wav");
				_ljItemMgr::DropItem(newIndex, L"potion of rejuvenation", 26, mPlayer->mLevel);
				break;
			case 13:
				// _ljGameSound::SoundPlay(L"flipscrl.wav");
				_ljItemMgr::DropItem(newIndex, L"scroll of identify", 27, mPlayer->mLevel);
				break;
			case 14:
				// _ljGameSound::SoundPlay(L"flipscrl.wav");
				_ljItemMgr::DropItem(newIndex, L"scroll of town portal", 28, mPlayer->mLevel);
				break;
			case 15:
				// _ljGameSound::SoundPlay(L"flipswor.wav");
				_ljItemMgr::DropItem(newIndex, L"scimitar", 2, mPlayer->mLevel);
				break;
			case 16:
				// _ljGameSound::SoundPlay(L"flipswor.wav");
				_ljItemMgr::DropItem(newIndex, L"long sword", 3, mPlayer->mLevel);
				break;
			case 17:
				// _ljGameSound::SoundPlay(L"flipswor.wav");
				_ljItemMgr::DropItem(newIndex, L"bastard sword", 4, mPlayer->mLevel);
				break;
			case 18:
				// _ljGameSound::SoundPlay(L"fliplarm.wav");
				_ljItemMgr::DropItem(newIndex, L"leather armor", 8, mPlayer->mLevel);
				break;
			case 19:
				// _ljGameSound::SoundPlay(L"fliplarm.wav");
				_ljItemMgr::DropItem(newIndex, L"studded leather armor", 9, mPlayer->mLevel);
				break;
			case 20:
				// _ljGameSound::SoundPlay(L"flipcap.wav");
				_ljItemMgr::DropItem(newIndex, L"helm", 20, mPlayer->mLevel);
				break;
			case 21:
				// _ljGameSound::SoundPlay(L"flipshld.wav");
				_ljItemMgr::DropItem(newIndex, L"large shield", 14, mPlayer->mLevel);
				break;
			case 22:
				// _ljGameSound::SoundPlay(L"flipring.wav");
				_ljItemMgr::DropItem(newIndex, L"amulet", 22, mPlayer->mLevel);
				break;
			case 23:
				// _ljGameSound::SoundPlay(L"flipharm.wav");
				_ljItemMgr::DropItem(newIndex, L"chain mail", 10, mPlayer->mLevel);
				break;
			default:
				BOOM;
				break;
			}
		}

		return;
	}
}

void _ljObject::DropMoney()
{
	TileIndex myIndex = GetTileIndex();
	_ljColTile* myTile = mPlayer->mColMap->FindTile(myIndex.X, myIndex.Y);
	TileIndex newIndex = myIndex + TileIndex({ 1, -1 });

	for (int i = 0; i < 8; ++i)
	{
		myTile = mPlayer->mColMap->FindTile(newIndex);

		if (nullptr == myTile->GetItem() && true == myTile->IsMovable())
		{
			int ran = _ljGameRandomNum::GetRandomNumber(mPlayer->mLevel * 2, mPlayer->mLevel * 21);
			_ljItemMgr::DropMoney(newIndex, ran, mPlayer->mLevel);

			return;
		}
	}
}

void _ljObject::DropMonster()
{

}

void _ljObject::SetPlayer(_ljPlayer* player)
{
	for (size_t i = 0; i < mAllObject.size(); ++i)
	{
		mAllObject[i]->mPlayer = player;
	}
}


void _ljObject::SetAnimation()
{
	mAllChestName[CHT_BARREL] = L"BARREL";
	mAllChestName[CHT_SARCO] = L"SARCO";
	mAllChestName[CHT_SMALL] = L"SMALL";
	mAllChestName[CHT_BIG] = L"BIG";
	mAllChestName[CHT_SILVER] = L"SILVER";

	mAniRenderer1->CreateAnimation(L"LDOOR", L"DibDoor.bmp", 0, 1, false);
	mAniRenderer1->CreateAnimation(L"RDOOR", L"DibDoor.bmp", 2, 3, false);
	mAniRenderer1->CreateAnimation(L"SARCO", L"DibDoor.bmp", 4, 8, false);
	mAniRenderer1->CreateAnimation(L"BIG", L"DibDoor.bmp", 9, 10, false);
	mAniRenderer1->CreateAnimation(L"SILVER", L"DibDoor.bmp", 11, 12, false);
	mAniRenderer1->CreateAnimation(L"SMALL", L"DibDoor.bmp", 13, 14, false);
	mAniRenderer1->CreateAnimation(L"BARREL", L"DibDoor.bmp", 15, 23, false, 0.05f);

	mAniRenderer2->CreateAnimation(L"LDOOR", L"DibDoor.bmp", 0, 1, false);
	mAniRenderer2->CreateAnimation(L"RDOOR", L"DibDoor.bmp", 2, 3, false);
	mAniRenderer2->CreateAnimation(L"SARCO", L"DibDoor.bmp", 4, 8, false);
	mAniRenderer2->CreateAnimation(L"BIG", L"DibDoor.bmp", 9, 10, false);
	mAniRenderer2->CreateAnimation(L"SILVER", L"DibDoor.bmp", 11, 12, false);
	mAniRenderer2->CreateAnimation(L"SMALL", L"DibDoor.bmp", 13, 14, false);
	mAniRenderer2->CreateAnimation(L"BARREL", L"DibDoor.bmp", 15, 23, false, 0.05f);

}
