#include "_ljFallen2.h"
#include <_ljGameAniRenderer.h>
#include <_ljGameTextureMgr.h>
#include <_ljGameInput.h>
#include <_ljGameWin.h>
#include <_ljGameActor.h>
#include <_ljGameRandomNum.h>
#include "_ljColMap.h"
#include "_ljPlayer.h"
#include "_ljTile.h"
#include "_ljColTile.h"


int _ljFallen2::mCount = 0;


_ljFallen2::_ljFallen2(_ljColMap* colmap, _ljRandomMap* randomMap, _ljPlayer* player, TileIndex index)
	: _ljMonster(colmap, randomMap)
	, mPlayer(player)
	, mIsPlayerAround(true)
	, mIsExpDone(false)
{
	mVision = 5;

	mAttackSpeed = 0.05f;
	mMaxResting = 1.f;

	mData.name = L"fallen one";
	mData.dlevel = 1;
	mData.mLevel = 1;

	mData.mMaxHP = 3;
	mData.armor = 0;
	mData.toHit = 30;
	mData.attackMin = 5;
	mData.attackMax = 5;
	mData.exp = 64;

	mCurHP = mData.mMaxHP;

	SetCurPos(index.X, index.Y);

	mAnimationRenderer = CreateAniRenderer(LO_UPTILE);
	mSubRenderer = CreateAniRenderer(LO_DOWNTILE);
	mBlackRenderer = CreateRenderer<_ljGameRenderer>(LO_BIGFOG);
	mBlackRenderer->SetRenderStyle(RS_ALPHA);


	SetAnimation();

	mAnimationRenderer->SubSize({ 128, 128 });
	mAnimationRenderer->TransColor(255, 255, 255);
	mAnimationRenderer->SubPos({ (float)0, (float)-32 });
	mAnimationRenderer->SetCurrentAnimation(L"RB_F2_IDLE");

	mSubRenderer->SubSize({ 128, 128 });
	mSubRenderer->TransColor(255, 255, 255);
	mSubRenderer->SubPos({ (float)0, (float)-32 });
	mSubRenderer->SetCurrentAnimation(L"RB_F2_IDLE");

	mBlackRenderer->SubSize({ 128, 128 });
	mBlackRenderer->TransColor(255, 255, 255);
	mBlackRenderer->SubPos({ (float)0, (float)-32 });

	mAnimationRenderer->Off();
	mSubRenderer->Off();
	mBlackRenderer->Off();

	mDir = RB;

	mIncrease = 30;
	mBase = 40;
}


_ljFallen2::~_ljFallen2()
{
}

void _ljFallen2::DebugRender()
{
	wchar_t Arr[256] = { 0, };

	swprintf_s(Arr, L"Fallen2 HP : %d / %d", mCurHP, mData.mMaxHP);
	TextOutW(_ljGameTextureMgr::BackDC(), 550, 0, Arr, lstrlen(Arr));

	swprintf_s(Arr, L"Fallen2 Index : X = %d , Y = %d", mTileIndex.X, mTileIndex.Y);
	TextOutW(_ljGameTextureMgr::BackDC(), 550, 15, Arr, lstrlen(Arr));

	swprintf_s(Arr, L"Fallen2 DibIndex : X = %d , Y = %d", mX, mY);
	TextOutW(_ljGameTextureMgr::BackDC(), 550, 30, Arr, lstrlen(Arr));
}

void _ljFallen2::Update()
{
	mKillCount = mCount;

	FindPlayer();

	if (false == CheckDir())
	{
		Idle();


		{
			std::wstring Name = L"";
			int Index = 0;

			if (true == mSubRenderer->IsOn())
			{
				Name = mSubRenderer->CurImageName();
				Index = mSubRenderer->CurFrame();
			}
			else {
				Name = mAnimationRenderer->CurImageName();
				Index = mAnimationRenderer->CurFrame();
			}

			size_t Dot = Name.find_last_of('.');
			Name = Name.replace(Dot, Name.size() - 1, L"");
			Name += L"&BLACK.bmp";
			mBlackRenderer->Image(Name.c_str(), Index);
		}

		return;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////// ???? ???? ????

	TileIndex tileIndex = GetTileIndex();

	TileIndex playerTileIndex = mPlayer->GetTileIndex();

	TileIndex tileDis = tileIndex - playerTileIndex;
	TileIndex lastDis;

	lastDis.X = abs(tileDis.X);
	lastDis.Y = abs(tileDis.Y);

	int gap = lastDis.X + lastDis.Y;

	gap = abs(gap);

	if (18 < gap)
	{
		mAnimationRenderer->Off();
		mSubRenderer->Off();
		mBlackRenderer->Off();
		return;
	}



	mBlackRenderer->On();

	if (1 >= gap)
	{

	}
	else if (2 == gap)
	{
		mBlackRenderer->SetBF(mBase);
	}
	else if (3 == gap)
	{
		mBlackRenderer->SetBF(mBase + mIncrease * 1);
	}
	else if (4 == gap)
	{
		mBlackRenderer->SetBF(mBase + mIncrease * 2);
	}
	else if (5 == gap)
	{
		mBlackRenderer->SetBF(mBase + mIncrease * 3);
	}
	else if (6 == gap)
	{
		mBlackRenderer->SetBF(mBase + (int)(mIncrease * 3.7));
	}
	else if (7 == gap)
	{
		mBlackRenderer->SetBF(mBase + (int)(mIncrease * 4.5));
	}
	else if (8 == gap)
	{
		mBlackRenderer->SetBF(mBase + (int)mIncrease * 5);
	}
	else if (9 == gap)
	{
		mBlackRenderer->SetBF(mBase + (int)(mIncrease * 5.5));
	}
	else if (10 == gap)
	{
		mBlackRenderer->SetBF(mBase + (int)(mIncrease * 5.8));
	}
	else if (11 == gap)
	{
		mBlackRenderer->SetBF(mBase + mIncrease * 6);
	}
	else if (12 == gap)
	{
		mBlackRenderer->SetBF(mBase + (int)(mIncrease * 6.2));
	}
	else if (13 == gap)
	{
		mBlackRenderer->SetBF(mBase + (int)(mIncrease * 6.4));
	}
	else if (14 == gap)
	{
		mBlackRenderer->SetBF(mBase + (int)(mIncrease * 6.6));
	}
	else if (15 == gap)
	{
		mBlackRenderer->SetBF(mBase + (int)(mIncrease * 6.8));
	}
	else if (16 == gap)
	{
		mBlackRenderer->SetBF(mBase + mIncrease * 7);
	}
	else
	{

	}





	///////////////////////////////////////////////////////////////////////////////////////////////////

	if (false == mIsDying)
	{
		// ???????????? ?????????? ?? ???????? ?????? ???? ?? ???? ??????
		// ?????????? ???? ????
		bool renderOrder = (mPlayer->GetTileIndex().X < GetTileIndex().X || mPlayer->GetTileIndex().Y < GetTileIndex().Y);

		if (true == renderOrder)
		{
			mAnimationRenderer->Off();
		}
		else
		{
			mAnimationRenderer->On();
		}

		if (false == renderOrder)
		{
			mSubRenderer->Off();
		}
		else
		{
			mSubRenderer->On();
		}
	}
	else
	{
		Die();


		{
			std::wstring Name = L"";
			int Index = 0;

			if (true == mSubRenderer->IsOn())
			{
				Name = mSubRenderer->CurImageName();
				Index = mSubRenderer->CurFrame();
			}
			else {
				Name = mAnimationRenderer->CurImageName();
				Index = mAnimationRenderer->CurFrame();
			}

			size_t Dot = Name.find_last_of('.');
			Name = Name.replace(Dot, Name.size() - 1, L"");
			Name += L"&BLACK.bmp";
			mBlackRenderer->Image(Name.c_str(), Index);
		}

		return;
	}

	CheckDirChange();
	SetUnit();

	StateUpdate();

	switch (mState)
	{
	case MS_IDLE:
		Idle();
		break;
	case MS_WALK:
		Walk();
		break;
	case MS_ATTACK:
		Attack();
		break;
	case MS_DIE:
		Die();
		break;
	case MS_GETHIT:
		GetHit();
		break;
	case MS_SPECIAL:
		Special();
		break;
	case MS_REST:
		Rest();
		break;
	case MS_MAX:
		BOOM;
		break;
	default:
		break;
	}

	{
		std::wstring Name = L"";
		int Index = 0;

		if (true == mSubRenderer->IsOn())
		{
			Name = mSubRenderer->CurImageName();
			Index = mSubRenderer->CurFrame();
		}
		else {
			Name = mAnimationRenderer->CurImageName();
			Index = mAnimationRenderer->CurFrame();
		}

		size_t Dot = Name.find_last_of('.');
		Name = Name.replace(Dot, Name.size() - 1, L"");
		Name += L"&BLACK.bmp";
		mBlackRenderer->Image(Name.c_str(), Index);
	}

}

void _ljFallen2::StateUpdate()
{
	// ????
	if (0 >= mCurHP && false == mIsDead)
	{
		int ran = _ljGameRandomNum::GetRandomNumber(1, 2);

		if (1 == ran)
		{
			_ljGameSound::SoundPlay(L"phalld1.wav");
		}
		else
		{
			_ljGameSound::SoundPlay(L"phalld2.wav");
		}

		SetCurrentState(MS_DIE);
		mIsDying = true;

		CalIndex();

		mColMap->UnsetUnit(mTileIndex.X, mTileIndex.Y);
		++mCount;
		_ljMonster::mKillCount = mCount;
		ResetPosM(this);
	}
}

void _ljFallen2::FindPlayer()
{
	TileIndex tileIndex = GetTileIndex();
	TileIndex playerTileIndex = mPlayer->GetTileIndex();

	TileIndex tileDis = tileIndex - playerTileIndex;
	TileIndex lastDis;

	lastDis.X = abs(tileDis.X);
	lastDis.Y = abs(tileDis.Y);

	if (mVision >= lastDis.X && mVision >= lastDis.Y)
	{
		mIsPlayerAround = true;

		return;
	}

	mIsPlayerAround = false;
}

void _ljFallen2::CheckDirChange()
{
	if (mDir != mPrevDir && false == mIsAttacking)
	{
		if (MS_REST != mState)
		{
			SetCurrentState(mState);
		}

		mPrevDir = mDir;
	}
}

bool _ljFallen2::CheckDir()
{
	if (mCurDestination == _ljVector::ZERO)
	{
		mDir = RB;

		return true;
	}

	_ljVector test = Pos();

	float x = Pos().X - mCurDestination.X;
	float y = Pos().Y - mCurDestination.Y;

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

	int a = 0;

	// ???????? ???? ???????? ???? ???????? ???? ???? ??

	if (0 == mPathList.size() && true == mGoingToAttack)
	{
		_ljColTile* temp = mDestDibTile;

		_ljMonster::SetDir(mDestDibTile);

		MONSTER_DIR tempDir = mDir;

		if (nullptr != mDestDibTile)
		{
			mMonster = mDestDibTile->GetActor();
		}
	}

	return true;
}

void _ljFallen2::Idle()
{
	// Rest ????????
	if (true == mIsResting)
	{
		mIsAttacking = false;
		Rest();
	}
	// ????????
	else if (true == mIsPlayerAround)
	{
		_ljVector playerPos = mPlayer->CalPos();

		GoingToAttack(playerPos);
	}
}



void _ljFallen2::Walk()
{
	_ljVector temp = _ljGameMath::Lerp(mStart, mCurDestination, _ljGameTime::DeltaTime());

	mIsMoving = true;

	Move(temp * mMoveSpeed);

	if (L == mDir ||
		LT == mDir ||
		LB == mDir)
	{
		if (Pos() <= mCurDestination)
		{
			WalkTask();
		}
	}
	else if (T == mDir)
	{
		if (Pos().X >= mCurDestination.X &&
			Pos().Y <= mCurDestination.Y)
		{
			WalkTask();
		}
	}
	else if (B == mDir)
	{
		if (Pos().X <= mCurDestination.X &&
			Pos().Y >= mCurDestination.Y)
		{
			WalkTask();
		}
	}
	else
	{
		if (Pos() >= mCurDestination)
		{
			WalkTask();
		}
	}

	_ljColTile* nextTile = mColMap->GetTile(mCurDestination - Scene()->CamPos());

	if (this != nextTile->GetActor())
	{
		mPathList.clear();
		Pos(mStart);
		Rest();
	}
}


// ???? ???? ?? ????
void _ljFallen2::WalkTask()
{
	// ?????? ???????? ???? deltaTime?????? ?????? ???????? ?????? ????????.
	Pos(mCurDestination);
	// ?????? ?????? ???? ??????
	// Scene()->CamPos(Pos() + _ljVector(-400.f, -300.f));
	mStart = Pos();

	// ???? 1
	// ???? ????! => Idle
	if (0 == mPathList.size())
	{
		// ???? 1-2 ?????????? ?????? ???? ????!!!!
		if (true == mGoingToAttack)
		{
			// ???? 1-2-1 ??????...
			// ?? ???? dest ????
			TileIndex destIndex = mPlayer->GetTileIndex();
			// ?? ???? ???????? ????
			_ljColTile* temp = mColMap->GetTile(destIndex.X, destIndex.Y);


			if (nullptr != mDestDibTile->GetActor() || this != mDestDibTile->GetActor())
			{
				if (temp->GetTileIndex() == mDestDibTile->GetTileIndex())
				{
					SetDir(temp);

					int ran = _ljGameRandomNum::GetRandomNumber(1, 2);

					if (1 == ran)
					{
						SetCurrentState(MS_ATTACK);
					}
					else
					{
						SetCurrentState(MS_SPECIAL);
					}

					mGoingToAttack = false;

					return;
				}

			}
			// ???? 1-2-2 ?????? PS_IDLE		
		}

		Rest();
	}
	// ???? 2
	// ???? ?????? ????!
	else
	{
		// ???????? ?????? ???? ?????? ???? ????.
		// mCurDestination?? ????????!
		mCurDestination = (*mPathList.begin());
		mPathList.pop_front();

		// -------------------------------------------------------------------------------------------
		// ?? ???? ???? ?????? ???? ????!!!
		// ???? ?????? ??????.
		_ljColTile* nextTile = mColMap->GetTile(mCurDestination - Scene()->CamPos());

		if (nullptr == nextTile)
		{
			Rest();
			mIsMoving = false;
			return;
		}

		if (nullptr != nextTile->GetActor() && this != nextTile->GetActor())
		{
			Rest();
			mIsMoving = false;
			return;
		}

		// ???? ????????
		SetDir(mCurDestination);
		// -------------------------------------------------------------------------------------------

		// ???? ?????? ???????? ?????? ???? ????!
		PreMove();
	}
}

void _ljFallen2::Attack()
{
	// ?? ??????
	if (false == mIsAttacking)
	{
		if (nullptr == mDestDibTile)
		{
			Rest();
		}

		if (nullptr == mDestDibTile->GetActor())
		{
			Rest();
		}
	}


	if (true == mAnimationRenderer->IsCurrentAnimationEnd())
	{
		mIsAttacking = false;
		mGoingToAttack = false;
		mAttacked = false;
		mMonster = nullptr;
		SetCurrentState(MS_IDLE);
		mPathList.clear();

		mSubRenderer->FinishAnimation();


		Rest();
	}
	else if (true == mSubRenderer->IsCurrentAnimationEnd())
	{
		mIsAttacking = false;
		mGoingToAttack = false;
		mAttacked = false;
		mMonster = nullptr;
		SetCurrentState(MS_IDLE);
		mPathList.clear();

		mAnimationRenderer->FinishAnimation();


		Rest();
	}
	else
	{
		// ???? ??????...
		// SetDir(mDestDibTile);

		// ???? ???? ?? ????
		CheckDirChange();
		int ran = _ljGameRandomNum::GetRandomNumber(1, 100);
		mIsAttacking = true;

		if (0 != mAnimationRenderer->CurFrame() - mDir * 13 &&
			9 == (mAnimationRenderer->CurFrame() - mDir * 13) &&
			false == mAttacked)
		{
			int a = mAnimationRenderer->CurFrame();

			int ran = _ljGameRandomNum::GetRandomNumber(1, 2);

			if (1 == ran)
			{
				_ljGameSound::SoundPlay(L"phalla1.wav");
			}
			else
			{
				_ljGameSound::SoundPlay(L"phalla2.wav");
			}

			switch (mDir)
			{
			case B:
				mMonster = mColMap->GetTile(mTileIndex.X, mTileIndex.Y + 1)->GetActor();
				break;
			case LB:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y + 1)->GetActor();
				break;
			case L:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y)->GetActor();
				break;
			case LT:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y - 1)->GetActor();
				break;
			case T:
				mMonster = mColMap->GetTile(mTileIndex.X, mTileIndex.Y - 1)->GetActor();
				break;
			case RT:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y - 1)->GetActor();
				break;
			case R:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y)->GetActor();
				break;
			case RB:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y + 1)->GetActor();
				break;
			case MD_MAX:
				BOOM;
				break;
			default:
				break;
			}
			mAttacked = true;

			if (nullptr != mMonster)
			{
				if (ran <= mData.toHit)
				{
					mMonster->GetDamage(mData.attackMin);
				}
			}
		}
		else if (0 != mSubRenderer->CurFrame() - mDir * 13 &&
			9 == (mSubRenderer->CurFrame() - mDir * 13) &&
			false == mAttacked)
		{
			int a = mSubRenderer->CurFrame();

			int ran = _ljGameRandomNum::GetRandomNumber(1, 2);

			if (1 == ran)
			{
				_ljGameSound::SoundPlay(L"phalla1.wav");
			}
			else
			{
				_ljGameSound::SoundPlay(L"phalla2.wav");
			}

			switch (mDir)
			{
			case B:
				mMonster = mColMap->GetTile(mTileIndex.X, mTileIndex.Y + 1)->GetActor();
				break;
			case LB:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y + 1)->GetActor();
				break;
			case L:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y)->GetActor();
				break;
			case LT:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y - 1)->GetActor();
				break;
			case T:
				mMonster = mColMap->GetTile(mTileIndex.X, mTileIndex.Y - 1)->GetActor();
				break;
			case RT:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y - 1)->GetActor();
				break;
			case R:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y)->GetActor();
				break;
			case RB:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y + 1)->GetActor();
				break;
			case MD_MAX:
				BOOM;
				break;
			default:
				break;
			}
			mAttacked = true;

			if (nullptr != mMonster)
			{
				if (ran <= mData.toHit)
				{
					mMonster->GetDamage(mData.attackMin);
				}
			}
		}
	}
}

void _ljFallen2::Die()
{
	if (true == mAnimationRenderer->IsCurrentAnimationEnd())
	{
		mIsDying = false;
		mIsDead = true;
		mSubRenderer->FinishAnimation();

	}
	else if (true == mSubRenderer->IsCurrentAnimationEnd())
	{
		mIsDying = false;
		mIsDead = true;
		mAnimationRenderer->FinishAnimation();

	}
	// SetCurrentState(F_DIE);
	if (false == mIsExpDone)
	{
		mPlayer->GetExp(mData.exp);
		mIsExpDone = true;
	}

	if (false == mIsDropped)
	{
		NormalDrop();
		mIsDropped = true;
	}
}

void _ljFallen2::GetHit()
{

	if (true == mAnimationRenderer->IsCurrentAnimationEnd() || true == mSubRenderer->IsCurrentAnimationEnd())
	{
		SetCurrentState(MS_IDLE);
	}

	Pos(mStart);
}

void _ljFallen2::Special()
{

	// ?? ??????
	if (false == mIsAttacking)
	{


		if (nullptr == mDestDibTile)
		{
			Rest();
		}

		if (nullptr == mDestDibTile->GetActor())
		{
			Rest();
		}
	}


	if (true == mAnimationRenderer->IsCurrentAnimationEnd())
	{
		mIsAttacking = false;
		mGoingToAttack = false;
		mAttacked = false;
		mMonster = nullptr;
		SetCurrentState(MS_IDLE);
		mPathList.clear();

		mSubRenderer->FinishAnimation();


		Rest();
	}
	else if (true == mSubRenderer->IsCurrentAnimationEnd())
	{
		mIsAttacking = false;
		mGoingToAttack = false;
		mAttacked = false;
		mMonster = nullptr;
		SetCurrentState(MS_IDLE);
		mPathList.clear();

		mAnimationRenderer->FinishAnimation();


		Rest();
	}
	else
	{
		// ???? ??????...
		// SetDir(mDestDibTile);

		// ???? ???? ?? ????
		CheckDirChange();
		int ran = _ljGameRandomNum::GetRandomNumber(1, 100);
		mIsAttacking = true;

		if (0 != mAnimationRenderer->CurFrame() - mDir * 15 &&
			12 == (mAnimationRenderer->CurFrame() - mDir * 15) &&
			false == mAttacked)
		{
			int ran = _ljGameRandomNum::GetRandomNumber(1, 2);

			if (1 == ran)
			{
				_ljGameSound::SoundPlay(L"phalls1.wav");
			}
			else
			{
				_ljGameSound::SoundPlay(L"phalls2.wav");
			}

			int a = mAnimationRenderer->CurFrame();

			switch (mDir)
			{
			case B:
				mMonster = mColMap->GetTile(mTileIndex.X, mTileIndex.Y + 1)->GetActor();
				break;
			case LB:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y + 1)->GetActor();
				break;
			case L:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y)->GetActor();
				break;
			case LT:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y - 1)->GetActor();
				break;
			case T:
				mMonster = mColMap->GetTile(mTileIndex.X, mTileIndex.Y - 1)->GetActor();
				break;
			case RT:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y - 1)->GetActor();
				break;
			case R:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y)->GetActor();
				break;
			case RB:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y + 1)->GetActor();
				break;
			case MD_MAX:
				BOOM;
				break;
			default:
				break;
			}
			mAttacked = true;

			if (nullptr != mMonster)
			{
				if (ran <= mData.toHit * 2)
				{
					mMonster->GetDamage(mData.attackMin * 2);
				}
			}
		}
		else if (0 != mSubRenderer->CurFrame() - mDir * 15 &&
			12 == (mSubRenderer->CurFrame() - mDir * 15) &&
			false == mAttacked)
		{
			int a = mSubRenderer->CurFrame();

			int ran = _ljGameRandomNum::GetRandomNumber(1, 2);

			if (1 == ran)
			{
				_ljGameSound::SoundPlay(L"phalls1.wav");
			}
			else
			{
				_ljGameSound::SoundPlay(L"phalls2.wav");
			}

			switch (mDir)
			{
			case B:
				mMonster = mColMap->GetTile(mTileIndex.X, mTileIndex.Y + 1)->GetActor();
				break;
			case LB:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y + 1)->GetActor();
				break;
			case L:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y)->GetActor();
				break;
			case LT:
				mMonster = mColMap->GetTile(mTileIndex.X - 1, mTileIndex.Y - 1)->GetActor();
				break;
			case T:
				mMonster = mColMap->GetTile(mTileIndex.X, mTileIndex.Y - 1)->GetActor();
				break;
			case RT:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y - 1)->GetActor();
				break;
			case R:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y)->GetActor();
				break;
			case RB:
				mMonster = mColMap->GetTile(mTileIndex.X + 1, mTileIndex.Y + 1)->GetActor();
				break;
			case MD_MAX:
				BOOM;
				break;
			default:
				break;
			}
			mAttacked = true;

			if (nullptr != mMonster)
			{
				if (ran <= mData.toHit * 2)
				{
					mMonster->GetDamage(mData.attackMin * 2);
				}
			}
		}
	}
}

void _ljFallen2::Rest()
{
	mIsAttacking = false;

	mState = MS_REST;

	// ?? ????
	if (false == mIsResting)
	{
		std::wstring newState = mAllDirName[mDir];

		newState.append(L"_");
		newState.append(L"F2_IDLE");

		mAnimationRenderer->SetCurrentAnimation(newState.c_str());
		mSubRenderer->SetCurrentAnimation(newState.c_str());
	}



	mIsResting = true;

	mRestingCount += _ljGameTime::DeltaTime();

	mPathList.clear();

	if (mMaxResting <= mRestingCount)
	{
		mRestingCount = 0.0f;
		mIsResting = false;
		SetCurrentState(MS_IDLE);
	}
}

void _ljFallen2::SetCurrentState(MONSTER_STATE state, bool noneDir /*= false*/)
{
	mState = state;

	std::wstring newState = mAllDirName[mDir];

	if (true == noneDir)
	{
		newState = L"";
	}

	newState.append(L"_");
	newState.append(mAllStateName[state]);

	mAnimationRenderer->SetCurrentAnimation(newState.c_str());
	mSubRenderer->SetCurrentAnimation(newState.c_str());
}

void _ljFallen2::GetDamage(int damage)
{
	int ran = _ljGameRandomNum::GetRandomNumber(1, 2);

	if (1 == ran)
	{
		_ljGameSound::SoundPlay(L"phallh1.wav");
	}
	else
	{
		_ljGameSound::SoundPlay(L"phallh2.wav");
	}

	mCurHP -= damage;

	mIsAttacking = false;

	SetCurrentState(MS_GETHIT);

	_ljMonster::ResetPosM(this);
}

void _ljFallen2::SetAnimation()
{
	// SetAnimation
	mAllDirName[T] = L"T";
	mAllDirName[LT] = L"LT";
	mAllDirName[L] = L"L";
	mAllDirName[LB] = L"LB";
	mAllDirName[B] = L"B";
	mAllDirName[RB] = L"RB";
	mAllDirName[R] = L"R";
	mAllDirName[RT] = L"RT";

	mAllStateName[MS_IDLE] = L"F2_IDLE";
	mAllStateName[MS_WALK] = L"F2_WALK";
	mAllStateName[MS_ATTACK] = L"F2_ATTACK";
	mAllStateName[MS_DIE] = L"F2_DIE";
	mAllStateName[MS_GETHIT] = L"F2_GETHIT";
	mAllStateName[MS_SPECIAL] = L"F2_SPECIAL";

	AutoAnimation(L"ATTACK", 12, mAttackSpeed);
	AutoAnimation(L"DIE", 13, false, 0.05f);
	AutoAnimation(L"GETHIT", 10, 0.05f);
	AutoAnimation(L"IDLE", 11, 0.1f);
	AutoAnimation(L"SPECIAL", 14);
	AutoAnimation(L"WALK", 11);
}

// ???? ??????
void _ljFallen2::AutoAnimation(const wchar_t* name, int index, float frameSpeed)
{
	// mAnimationRenderer->CreateAnimation(L"RB_F2_IDLE", L"F&IDLE.bmp", 0, 12, true);
	// mAnimationRenderer->CreateAnimation(L"RB_F2_GETHIT", L"F&GETHIT.bmp", 0, 7, true);

	int start = 0;
	int next = index;

	std::wstring fileName = L"F2&";
	fileName.append(name);
	fileName.append(L".bmp");

	std::wstring blackName = L"F2&";
	blackName.append(name);
	blackName.append(L"&BLACK.bmp");

	for (int i = 0; i < 8; ++i)
	{
		std::wstring aniName = mAllDirName[i];

		aniName.append(L"_F2_");
		aniName.append(name);

		mAnimationRenderer->CreateAnimation(aniName.c_str(), fileName.c_str(), start, next, true, frameSpeed);
		mSubRenderer->CreateAnimation(aniName.c_str(), fileName.c_str(), start, next, true, frameSpeed);

		start = next + 1;
		next = start + index;

		/////////////////////////////////////////////////////////////////
	}
}

void _ljFallen2::AutoAnimation(const wchar_t* name, int index, bool loop, float frameSpeed)
{

	int start = 0;
	int next = index;

	std::wstring fileName = L"F2&";
	fileName.append(name);
	fileName.append(L".bmp");

	std::wstring blackName = L"F2&";
	blackName.append(name);
	blackName.append(L"&BLACK.bmp");

	for (int i = 0; i < 8; ++i)
	{
		std::wstring aniName = mAllDirName[i];

		aniName.append(L"_F2_");
		aniName.append(name);

		mAnimationRenderer->CreateAnimation(aniName.c_str(), fileName.c_str(), start, next, loop, frameSpeed);
		mSubRenderer->CreateAnimation(aniName.c_str(), fileName.c_str(), start, next, loop, frameSpeed);

		start = next + 1;
		next = start + index;
	}
}

//---------------------------------------------------------------------------------------------------------------------------------------------------

// 1. mCurDestination => ???? ???? ?????? ????????.
// 2. ???? ?????? ???? ????????.(???? ?????? ?????? ????)
// ???? ???? -> ?????????? ???? ???? ?????? ???? ?????????? ?????? ????
// ???? ???????? ?????? ?????? ?????? ?????? ???? Reset????. => ResetPos();
void _ljFallen2::GoingToMove(_ljVector mousePos)
{
	mPathList.clear();
	// ??????
	mPathList = mColMap->PathFindM(CalPos(), mousePos);

	// ???? ?? ????
	if (0 == mPathList.size())
	{
		SetCurrentState(MS_IDLE);

		return;
	}

	// ???? ?????? ????...
	mPathList.pop_front();

	// ???? ???? ????
	mCurDestination = (*mPathList.begin());
	// ???? ???? ???? ?????????? ?? ????
	mPathList.pop_front();

	SetDir(mCurDestination);
	// ????
	SetCurrentState(MS_WALK);

	// ???? ?????? ???????? ?????? ???? ????!
	PreMove();
}

// ???? ???? ???????? ??????.
// ?????? ?????? pop_back????.
void _ljFallen2::GoingToAttack(_ljVector mousePos)
{
	mPathList.clear();
	// ??????
	mPathList = mColMap->PathFindM(CalPos(), mousePos);

	// ???? ?? ????
	if (0 == mPathList.size())
	{
		SetCurrentState(MS_IDLE);

		return;
	}

	// ???? ???? ??!!!
	if (2 == mPathList.size())
	{
		SetDir((*--mPathList.end()));

		mIsAttacking = true;

		int ran = _ljGameRandomNum::GetRandomNumber(1, 2);

		if (1 == ran)
		{
			SetCurrentState(MS_ATTACK);
		}
		else
		{
			SetCurrentState(MS_SPECIAL);
		}

		return;
	}

	// ???? ?????? ????...
	mPathList.pop_front();

	// ???? ???? ????
	mCurDestination = (*mPathList.begin());
	// ???? ???? ???? ?????????? ?? ????
	mPathList.pop_front();

	//-----------------------------------------------------------------------------------------

	// GoingToMove?? ???? ??!!! ?????? ???? = ???????? ????
	// ?????? ???????? ???????? ?? ?????? ????. 
	// ?????? ?????? ???? ??????
	TileIndex destIndex = mColMap->PosToIndex(mousePos);
	// ?? ???? ???????? ????
	mDestDibTile = mColMap->GetTile(destIndex.X, destIndex.Y);

	// ?????? ???? ????
	mPathList.pop_back();

	// ???????? ???? ?????????? ??
	mGoingToAttack = true;

	//-----------------------------------------------------------------------------------------

	// ????
	SetDir(mCurDestination);
	SetCurrentState(MS_WALK);

	// ???? ?????? ???????? ?????? ???? ????!
	PreMove();
}

// ???? ?????? ???????? ?????? ???? ????!
void _ljFallen2::PreMove()
{
	_ljVector first = mCurDestination;
	first -= CamPos();
	_ljColTile* firstTile = mColMap->GetTile(first.X, first.Y);
	firstTile->SetActor(this);
}
