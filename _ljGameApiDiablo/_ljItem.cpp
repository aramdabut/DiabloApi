#include "_ljItem.h"
#include "_ljPlayer.h"
#include <_ljGameRenderer.h>
#include <_ljGameAniRenderer.h>
#include <_ljGameWin.h>
#include <_ljGameInput.h>
#include <_ljGameTextureMgr.h>
#include "_ljItemMgr.h"
#include "_ljInvenBack.h"
#include <_ljGameSound.h>


bool _ljItem::mIsChanging = false;


_ljItem::_ljItem()
{
	mArmor = L"armor: ";
	mDamage = L"damage: ";
	mDur = L"dur: ";
	mIden = L"not identified";
	mMouseItem = nullptr;

	mInGame = CreateRenderer<_ljGameAniRenderer>(LO_TILE);
	mInGame->Image(L"InGameItem.bmp");
	mInGame->TransColor(255, 255, 255);
	mInGame->SetRenderStyle(RS_TRANS);

	float speed = 0.05f;

	mInGame->CreateAnimation(L"HARMOR", L"InGameItem.bmp", 0, 14, false, speed);
	mInGame->CreateAnimation(L"AXE", L"InGameItem.bmp", 20, 32, false, speed);
	mInGame->CreateAnimation(L"CLEAVER", L"InGameItem.bmp", 80, 92, false, speed);
	mInGame->CreateAnimation(L"HPOTION", L"InGameItem.bmp", 140, 156, false, speed); // 16
	mInGame->CreateAnimation(L"MPOTION", L"InGameItem.bmp", 180, 196, false, speed);
	mInGame->CreateAnimation(L"RPOTION", L"InGameItem.bmp", 280, 296, false, speed);
	mInGame->CreateAnimation(L"MONEY", L"InGameItem.bmp", 480, 489, false, speed);
	mInGame->CreateAnimation(L"HELM", L"InGameItem.bmp", 500, 512, false, speed);
	mInGame->CreateAnimation(L"LARMOR", L"InGameItem.bmp", 520, 532, false, speed);
	mInGame->CreateAnimation(L"RING", L"InGameItem.bmp", 580, 592, false, speed);
	mInGame->CreateAnimation(L"SCROLL", L"InGameItem.bmp", 600, 612, false, speed);
	mInGame->CreateAnimation(L"SHIELD", L"InGameItem.bmp", 620, 632, false, speed);
	mInGame->CreateAnimation(L"SWORD", L"InGameItem.bmp", 660, 672, false, speed);
	mInGame->CreateAnimation(L"SSHEILD", L"InGameItem.bmp", 700, 712, false, speed);
	mInGame->SubSize({ 96, 161 });
	mInGame->Off();

	mInven = CreateRenderer<_ljGameRenderer>(LO_UI4);
	mInven->Image(L"Items.bmp");
	mInven->SetRenderStyle(RS_TRANS);
	mInven->Off();
	mInven->SubSize({ 56.f, 84.f });
	mInven->TransColor(255, 255, 255);
	mInven->SubPos({ -100.f, -100.f });
}

_ljItem::_ljItem(const _ljItem& other)
{
	mArmor = L"armor: ";
	mDamage = L"damage: ";
	mDur = L"dur: ";
	mIden = L"not identified";

	mX = other.mX;
	mX = other.mY;

	mBase = other.mBase;

	mMouseItem = nullptr;

	// 애니메이션 확인용
	mIsOver = false;
	mIndex = other.mIndex;
	mAniName = other.mAniName;
	float speed = 0.05f;

	mItemData.mName = other.mItemData.mName;
	mItemData.mDamage = other.mItemData.mDamage;
	mItemData.mMaxDamage = other.mItemData.mMaxDamage;
	mItemData.mArmor = other.mItemData.mArmor;
	mItemData.mMaxArmor = other.mItemData.mMaxArmor;
	mItemData.mDurability = other.mItemData.mDurability;
	mItemData.mRequire1 = other.mItemData.mRequire1;
	mItemData.mRequire1Amount = other.mItemData.mRequire1Amount;
	mItemData.mRequire2 = other.mItemData.mRequire2;
	mItemData.mRequire2Amount = other.mItemData.mRequire2Amount;
	mItemData.mPrice = other.mItemData.mPrice;
	mItemData.mItemLevel = other.mItemData.mItemLevel;
	mItemData.mType = other.mItemData.mType;
	mItemData.X = other.mItemData.X;
	mItemData.Y = other.mItemData.Y;

	mInGame = CreateRenderer<_ljGameAniRenderer>(LO_UPTILE);
	mInGame->Image(L"InGameItem.bmp");
	mInGame->TransColor(255, 255, 255);
	mInGame->SetRenderStyle(RS_TRANS);

	//mSubInGame = CreateRenderer<_ljGameAniRenderer>(LO_DOWNTILE);
	//mSubInGame->Image(L"InGameItem.bmp");
	//mSubInGame->TransColor(255, 255, 255);
	//mSubInGame->SetRenderStyle(RS_TRANS);

	mInGame2 = CreateRenderer<_ljGameAniRenderer>(LO_ITEM);
	mInGame2->Image(L"InGameItem.bmp");
	mInGame2->TransColor(255, 255, 255);
	mInGame2->SetRenderStyle(RS_TRANS);

	mInGameBack = CreateRenderer<_ljGameAniRenderer>(LO_ITEMBACK);
	mInGameBack->Image(L"InGameItemB.bmp");
	mInGameBack->TransColor(255, 255, 255);
	mInGameBack->SetRenderStyle(RS_TRANS);

	mInGame->CreateAnimation(L"HARMOR", L"InGameItem.bmp", 0, 14, false, speed);
	mInGame->CreateAnimation(L"AXE", L"InGameItem.bmp", 20, 32, false, speed);
	mInGame->CreateAnimation(L"CLEAVER", L"InGameItem.bmp", 80, 92, false, speed);
	mInGame->CreateAnimation(L"HPOTION", L"InGameItem.bmp", 140, 155, false, speed); // 7
	mInGame->CreateAnimation(L"MPOTION", L"InGameItem.bmp", 180, 195, false, speed); // 9
	mInGame->CreateAnimation(L"RPOTION", L"InGameItem.bmp", 280, 295, false, speed); // 14
	mInGame->CreateAnimation(L"MONEY", L"InGameItem.bmp", 480, 489, false, speed);
	mInGame->CreateAnimation(L"HELM", L"InGameItem.bmp", 500, 512, false, speed);
	mInGame->CreateAnimation(L"LARMOR", L"InGameItem.bmp", 540, 552, false, speed);
	mInGame->CreateAnimation(L"RING", L"InGameItem.bmp", 580, 592, false, speed);
	mInGame->CreateAnimation(L"SCROLL", L"InGameItem.bmp", 600, 612, false, speed);
	mInGame->CreateAnimation(L"SHIELD", L"InGameItem.bmp", 620, 632, false, speed);
	mInGame->CreateAnimation(L"SWORD", L"InGameItem.bmp", 640, 652, false, speed);
	mInGame->CreateAnimation(L"SSHEILD", L"InGameItem.bmp", 700, 712, false, speed);
	mInGame->SubSize({ 96, 192 });
	mInGame->Off();

	mInGame2->CreateAnimation(L"HARMOR", L"InGameItem.bmp", 0, 14, false, speed);
	mInGame2->CreateAnimation(L"AXE", L"InGameItem.bmp", 20, 32, false, speed);
	mInGame2->CreateAnimation(L"CLEAVER", L"InGameItem.bmp", 80, 92, false, speed);
	mInGame2->CreateAnimation(L"HPOTION", L"InGameItem.bmp", 140, 155, false, speed); // 16
	mInGame2->CreateAnimation(L"MPOTION", L"InGameItem.bmp", 180, 195, false, speed);
	mInGame2->CreateAnimation(L"RPOTION", L"InGameItem.bmp", 280, 295, false, speed);
	mInGame2->CreateAnimation(L"MONEY", L"InGameItem.bmp", 480, 489, false, speed);
	mInGame2->CreateAnimation(L"HELM", L"InGameItem.bmp", 500, 512, false, speed);
	mInGame2->CreateAnimation(L"LARMOR", L"InGameItem.bmp", 540, 552, false, speed);
	mInGame2->CreateAnimation(L"RING", L"InGameItem.bmp", 580, 592, false, speed);
	mInGame2->CreateAnimation(L"SCROLL", L"InGameItem.bmp", 600, 612, false, speed);
	mInGame2->CreateAnimation(L"SHIELD", L"InGameItem.bmp", 620, 632, false, speed);
	mInGame2->CreateAnimation(L"SWORD", L"InGameItem.bmp", 640, 652, false, speed);
	mInGame2->CreateAnimation(L"SSHEILD", L"InGameItem.bmp", 700, 712, false, speed);
	mInGame2->SubSize({ 96, 192 });
	mInGame2->Off();

	mInGameBack->CreateAnimation(L"HARMOR", L"InGameItemB.bmp", 0, 14, false, speed);
	mInGameBack->CreateAnimation(L"AXE", L"InGameItemB.bmp", 20, 32, false, speed);
	mInGameBack->CreateAnimation(L"CLEAVER", L"InGameItemB.bmp", 80, 92, false, speed);
	mInGameBack->CreateAnimation(L"HPOTION", L"InGameItemB.bmp", 140, 155, false, speed); // 16
	mInGameBack->CreateAnimation(L"MPOTION", L"InGameItemB.bmp", 180, 195, false, speed);
	mInGameBack->CreateAnimation(L"RPOTION", L"InGameItemB.bmp", 280, 295, false, speed);
	mInGameBack->CreateAnimation(L"MONEY", L"InGameItemB.bmp", 480, 489, false, speed);
	mInGameBack->CreateAnimation(L"HELM", L"InGameItemB.bmp", 500, 512, false, speed);
	mInGameBack->CreateAnimation(L"LARMOR", L"InGameItemB.bmp", 540, 552, false, speed);
	mInGameBack->CreateAnimation(L"RING", L"InGameItemB.bmp", 580, 592, false, speed);
	mInGameBack->CreateAnimation(L"SCROLL", L"InGameItemB.bmp", 600, 612, false, speed);
	mInGameBack->CreateAnimation(L"SHIELD", L"InGameItemB.bmp", 620, 632, false, speed);
	mInGameBack->CreateAnimation(L"SWORD", L"InGameItemB.bmp", 640, 652, false, speed);
	mInGameBack->CreateAnimation(L"SSHEILD", L"InGameItemB.bmp", 700, 712, false, speed);
	mInGameBack->SubSize({ 96 , 192 });
	mInGameBack->Off();

	

	mInven = CreateRenderer<_ljGameRenderer>(LO_UI4);

	mInven->Image(L"Items.bmp");
	mInven->SetRenderStyle(RS_TRANS);
	mInven->SubSize({ 56.f, 84.f });
	mInven->TransColor(255, 255, 255);
	mInven->Off();
	mInven->ImageIndex(mIndex);
	mInven->CamOnOff();

	if (nullptr != other.mInven)
	{
		mInven->SubPos(other.mInven->SubPos());
	}


	mInvenEdge = CreateRenderer<_ljGameRenderer>(LO_UI5);
	mInvenEdge->Image(L"ItemsEdge.bmp");
	mInvenEdge->SetRenderStyle(RS_TRANS);
	mInvenEdge->SubSize({ 56.f, 84.f });
	mInvenEdge->TransColor(255, 255, 255);
	mInvenEdge->Off();
	mInvenEdge->ImageIndex(mIndex);
	mInvenEdge->CamOnOff();

	if (nullptr != other.mInvenEdge)
	{
		mInvenEdge->SubPos(other.mInvenEdge->SubPos());
	}
}



_ljItem::~_ljItem()
{
}

_ljItem* _ljItem::CopyItem(int level)
{
	_ljItem* temp = new _ljItem(*this);
	temp->mLevel = level;

	return temp;
}

void _ljItem::SetTile(_ljVector pos)
{

}

void _ljItem::Update()
{

	/*if (true == mIsOnBelt && false == mPlayer->mIsInvenOpen)
	{
		if (true == mIsOffset)
		{
			mInven->SubPos(mInven->SubPos() + _ljVector({ 320, 0 }));
			mIsOffset = false;
		}
	}
	else if(true == mIsOnBelt && true == mPlayer->mIsInvenOpen)
	{
		if (false == mIsOffset)
		{
			mInven->SubPos(mInven->SubPos() + _ljVector({ -160, 0 }));
			mIsOffset = true;
		}
	}*/

	if (true == mInGame->IsOn())
	{
		if (true == mInGame->IsCurrentAnimationEnd() && false == mIsOver)
		{
			mInGame->Off();

			mInGame2->FinishAnimation();
			mInGame2->On();
			mInGameBack->FinishAnimation();
			// mInGameBack->On();

			mIsOver = true;
		}
		else
		{
			int index = 0;

			switch (mItemData.mType)
			{
			case IT_GOLD:
				index = 24;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (5 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"gold1.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_WEAPON_AXE:
				index = 1;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flipaxe.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_WEAPON_CLEAVER:
				index = 4;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flipaxe.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_WEAPON_SWORD:
				index = 32;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flipswor.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_WEAPON_BOW:
				index = 32;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flipbow.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_ARMOR_LIGHT:
				index = 27;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"fliplarm.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_ARMOR_HEAVY:
				index = 32;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flipharm.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_HELM:
				index = 25;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flipcap.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_SHIELD:
				index = 31;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flipshld.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_RING:
			case IT_NECK:
				index = 27;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flipring.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_BOOK:
				index = 32;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flipbook.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_HPOTION:
				index = 7;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flippot.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_MPOTION:
				index = 9;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flippot.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_RPOTION:
				index = 14;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flippot.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_ISCROLL:
			case IT_PSCROLL:
				index = 30;
				if (false == mIsDropped)
				{
					if (0 != mInGame->CurFrame() || 0 != mInGame2->CurFrame())
					{
						if (6 == (mInGame->CurFrame() - index * 20))
						{
							_ljGameSound::SoundPlayToInst(L"flipscrl.wav");
							mIsDropped = true;
						}
					}
				}
				break;
			case IT_MAX:
				break;
			default:
				break;
			}
		}

	}

	// 마우스 위치에 따라서 불 들어옴
	// 바닥에 있을 때
	if (mPlayer != nullptr && nullptr != mInGameBack && false == mIsTaken && true == mIsOver)
	{
		if (mTileIndex == mPlayer->GetMouseIndex())
		{
			mInGameBack->FinishAnimation();
			mInGameBack->On();

			// 아이템 이름 띄우기
			if (IT_WEAPON_CLEAVER == mItemData.mType)
			{
				mPlayer->DescYOn(mItemData.mName);
			}
			else if (IT_GOLD == mItemData.mType)
			{
				wchar_t amount[5];
				int gold = mItemData.gold;
				_itow_s(gold, amount, 5, 10);

				std::wstring temp = amount;
				temp.append(L" ");
				temp.append(mItemData.mName);
				temp.append(L" ");
				temp.append(L"pieces");
				mPlayer->DescOn(temp);
			}
			else
			{
				mPlayer->DescOn(mItemData.mName);
			}
		}
		else
		{
			// mPlayer->UnshowDescription();
			mInGameBack->Off();
		}
	}

	if (mItemData.mType == IT_GOLD)
	{
		if (mItemData.gold < 2500)
		{
			mInven->ImageIndex(15);
		}
		else if (mItemData.gold < 5000)
		{
			mInven->ImageIndex(16);
		}
		else
		{
			mInven->ImageIndex(17);
		}
	}

	if (nullptr != mPlayer)
	{
		if (true == mPlayer->IsInvenOpen() && true == mIsTaken)
		{
			mInven->On();
		}
		else
		{
			if (true == mIsOnBelt)
			{
				mInven->On();
			}
			else
			{
				mInven->Off();
			}

		}

		// 인벤 아이템 마우스에 불 들어옴
		if (true == CheckMouse() && true == mPlayer->IsInvenOpen() && true == mIsTaken && false == mIsOn)
		{
			mInvenEdge->On();

			// 아이템 이름 띄우기
			if (IT_WEAPON_CLEAVER == mItemData.mType)
			{
				wchar_t amount1[5];
				int min = mItemData.mDamage;
				_itow_s(min, amount1, 5, 10);

				std::wstring damage = mDamage;
				damage.append(amount1);
				damage.append(L"-");

				wchar_t amount2[5];
				int max = mItemData.mMaxDamage;
				_itow_s(max, amount2, 5, 10);

				damage.append(amount2);
				damage.append(L"   ");
				damage.append(mDur);

				wchar_t amount3[5];
				int dur = mItemData.mDurability;
				_itow_s(dur, amount3, 5, 10);

				damage.append(amount3);
				damage.append(L"/");
				damage.append(amount3);

				mPlayer->DescYOn(mItemData.mName, damage, mIden);
			}
			else if (IT_GOLD == mItemData.mType)
			{
				wchar_t amount[5];
				int gold = mItemData.gold;
				_itow_s(gold, amount, 5, 10);

				std::wstring temp = amount;
				temp.append(L" ");
				temp.append(mItemData.mName);
				temp.append(L" ");
				temp.append(L"pieces");
				mPlayer->DescOn(temp);
			}
			else if (IT_WEAPON_AXE == mItemData.mType || IT_WEAPON_SWORD == mItemData.mType)
			{
				wchar_t amount1[5];
				int min = mItemData.mDamage;
				_itow_s(min, amount1, 5, 10);

				std::wstring damage = mDamage;
				damage.append(amount1);
				damage.append(L"-");

				wchar_t amount2[5];
				int max = mItemData.mMaxDamage;
				_itow_s(max, amount2, 5, 10);

				damage.append(amount2);
				damage.append(L"   ");
				damage.append(mDur);

				wchar_t amount3[5];
				int dur = mItemData.mDurability;
				_itow_s(dur, amount3, 5, 10);

				damage.append(amount3);
				damage.append(L"/");
				damage.append(amount3);

				mPlayer->DescOn(mItemData.mName, damage);
			}
			else if (IT_ARMOR_LIGHT == mItemData.mType || IT_ARMOR_HEAVY == mItemData.mType || IT_HELM == mItemData.mType || IT_SHIELD == mItemData.mType)
			{
				wchar_t amount1[5];
				int min = mItemData.mArmor;
				_itow_s(min, amount1, 5, 10);

				std::wstring damage = mArmor;
				damage.append(amount1);

				damage.append(L"   ");
				damage.append(mDur);

				wchar_t amount3[5];
				int dur = mItemData.mDurability;
				_itow_s(dur, amount3, 5, 10);

				damage.append(amount3);
				damage.append(L"/");
				damage.append(amount3);

				mPlayer->DescOn(mItemData.mName, damage);
			}
			else
			{
				mPlayer->DescOn(mItemData.mName);

				if (IT_HPOTION == mItemData.mType || IT_MPOTION == mItemData.mType || IT_MPOTION == mItemData.mType)
				{
					if (true == _ljGameInput::Down(L"RMOUSEBTN"))
					{
						UseItem();
						return;
					}
				}
			}
		}
		else
		{
			mInvenEdge->Off();
		}

		if (true == CheckMouse() && true == mIsOnBelt && true == mIsTaken && false == mIsOn)
		{
			mInvenEdge->On();

			mPlayer->DescOn(mItemData.mName);

			if (true == _ljGameInput::Down(L"RMOUSEBTN"))
			{
				UseItem();
				return;
			}
			if (true == _ljGameInput::Down(L"LMOUSEBTN"))
			{
				UnsetPotion();
				return;
			}
		}
		else
		{
			mInvenEdge->Off();
		}

		// 올리기
		if (true == CheckMouse() && true == mPlayer->IsInvenOpen() && true == mIsTaken
			&& true == _ljGameInput::Down(L"LMOUSEBTN") && false == mIsOn && true == mIsSet)
		{
			Unarm();
		}
		// 내리기
		else if (true == mIsOn && false == mIsSet)
		{
			mInven->SubPos(_ljGameWin::MainWindow()->MousePos());

			if (true == _ljGameInput::Down(L"LMOUSEBTN") && false == mWillBeSet)
			{
				mPlayer->mIsNoMove = true;

				mWillBeSet = true;
				// SetInven(MyWindowClass::MainWindow()->MousePos());
			}
			// 내리기 예정
			else if (true == mWillBeSet)
			{
				SetInven(_ljGameWin::MainWindow()->MousePos());
				mWillBeSet = false;
			}
		}
	}

	if (true == mWillBeOn)
	{
		mIsOn = true;
		mWillBeOn = false;
	}

	if (true == mWillBeOff)
	{
		mIsOn = false;
		mWillBeOff = false;
	}

	// if()
}

// 올릴때
void _ljItem::Unarm()
{
	// 올리려는데 (마우스에) 이미 누가 있다! 두둥
	ITEM_TYPE type = mItemData.mType;

	// 이미 있다면
	if (nullptr != mPlayer->mMouseItem && this != mPlayer->mMouseItem)
	{
		// 	 mPlayer->mMouseItem->SetInven(MyWindowClass::MainWindow()->MousePos());
		mPlayer->mMouseItem->mWillBeSet = true;
	}

	mInvenEdge->Off();
	// mPlayer->mInvenBack->Off();
	UnsetInven();


	mInven->SubPos(_ljGameWin::MainWindow()->MousePos());






	mIsOn = true;

	mIsSet = false;

	//if (true == mPlayer->mIsItemOn)
	//{
	//	if (mPlayer->mMouseItem != this)
	//	{
	//		BOOM;
	//	}
	//}
	//else
	//{
	mPlayer->mMouseItem = this;
	mPlayer->mIsItemOn = true;
	// }

	if (true == mIsEquiped)
	{
		mIsEquiped = false;
		mPlayer->UnapplyItem(this);

		switch (type)
		{
		case IT_GOLD:
			break;
		case IT_WEAPON_AXE:
		case IT_WEAPON_CLEAVER:
			mHasShield = false;
			mPlayer->mHasShield = false;
			mPlayer->mShield = nullptr;
		case IT_WEAPON_SWORD:
		case IT_WEAPON_BOW:
			mHasWeapon = false;
			mPlayer->mHasWeapon = false;
			mPlayer->mWeapon = nullptr;
			break;
		case IT_ARMOR_LIGHT:
		case IT_ARMOR_HEAVY:
			mHasArmor = false;
			mPlayer->mHasArmor = false;
			mPlayer->mArmor = nullptr;
			break;
		case IT_HELM:
			mHasHelm = false;
			mPlayer->mHasHelm = false;
			mPlayer->mHelm = nullptr;
			break;
		case IT_SHIELD:
			mHasShield = false;
			mPlayer->mHasShield = false;
			mPlayer->mShield = nullptr;
			break;
		case IT_RING:
			if (true == mHasLeftRing)
			{
				mHasLeftRing = false;
				mPlayer->mHasLeftRing = false;
				mPlayer->mLRing = nullptr;
			}
			else if (true == mHasRightRing)
			{
				mHasRightRing = false;
				mPlayer->mHasRightRing = false;
				mPlayer->mRRing = nullptr;
			}
			break;
		case IT_NECK:
			mHasNeck = false;
			mPlayer->mHasNeck = false;
			mPlayer->mNeck = nullptr;
			break;
		default:
			BOOM;
			break;
		}
	}

	_ljGameSound::SoundPlayToInst(L"invgrab.wav");
}


// 내릴때
void _ljItem::SetInven(_ljVector mousePos)
{
	ITEM_TYPE type = mItemData.mType;

	// 사운드 세팅
	switch (type)
	{
	case IT_GOLD:
		_ljGameSound::SoundPlayToInst(L"gold.wav");
		break;
	case IT_WEAPON_AXE:
		_ljGameSound::SoundPlayToInst(L"invaxe.wav");
		break;
	case IT_WEAPON_CLEAVER:
		_ljGameSound::SoundPlayToInst(L"invaxe.wav");
		break;
	case IT_WEAPON_SWORD:
		_ljGameSound::SoundPlayToInst(L"invsword.wav");
		break;
	case IT_WEAPON_BOW:
		_ljGameSound::SoundPlayToInst(L"invbow.wav");
		break;
	case IT_ARMOR_LIGHT:
		_ljGameSound::SoundPlayToInst(L"invlarm.wav");
		break;
	case IT_ARMOR_HEAVY:
		_ljGameSound::SoundPlayToInst(L"invharm.wav");
		break;
	case IT_HELM:
		_ljGameSound::SoundPlayToInst(L"invcap.wav");
		break;
	case IT_SHIELD:
		_ljGameSound::SoundPlayToInst(L"invshiel.wav");
		break;
	case IT_RING:
	case IT_NECK:
		_ljGameSound::SoundPlayToInst(L"invring.wav");
		break;
	case IT_BOOK:
		_ljGameSound::SoundPlayToInst(L"invbook.wav");
		break;
	case IT_HPOTION:
	case IT_MPOTION:
	case IT_RPOTION:
		_ljGameSound::SoundPlayToInst(L"invpot.wav");
		break;
	case IT_ISCROLL:
	case IT_PSCROLL:
		_ljGameSound::SoundPlayToInst(L"invscrol.wav");
		break;
	case IT_MAX:
		break;
	default:
		break;
	}

	int newX = mousePos.IntX();
	int newY = (int)(mousePos.Y);

	if (1 == mItemData.X && 1 == mItemData.Y)
	{
		for (int x = 0; x < 10 - mItemData.X + 1; ++x)
		{
			for (int y = 0; y < 4 - mItemData.Y + 1; ++y)
			{
				if (newX >= 366.f + (x - 1) * 29 && newX < 366.f + (x - 1) * 29 + 29)
				{
					if (newY >= 260.f + (y - 1.5) * 29 && newY < 266.f + (y - 1.5) * 29 + 29)
					{
						ResetPosition(x, y);
						mInvenEdge->On();

						mWillBeOff = true;

						mPlayer->mIsItemOn = false;

						if (this == mPlayer->mMouseItem)
						{
							mPlayer->mMouseItem = nullptr;
						}

						return;
					}
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 10 - mItemData.X + 1; ++x)
		{
			for (int y = 0; y < 4 - mItemData.Y + 1; ++y)
			{
				if (newX >= 366.f + (x - 1.5f) * 29 && newX < 366.f + (x - 1.5f) * 29 + mItemData.X * 29)
				{
					if (newY >= 260.f + (y - 1) * 29 && newY < 266.f + (y - 1) * 29 + mItemData.Y * 29 / 2)
					{
						ResetPosition(x, y);
						mInvenEdge->On();

						mWillBeOff = true;

						mPlayer->mIsItemOn = false;

						if (this == mPlayer->mMouseItem)
						{
							mPlayer->mMouseItem = nullptr;
						}

						return;
					}
				}
			}
		}
	}

	/////////////////////////////////////////////// 장착하는 부분 ///////////////////////////////////
	///////// 무기
	if (IT_WEAPON_AXE == mItemData.mType || IT_WEAPON_SWORD == mItemData.mType || IT_WEAPON_CLEAVER == mItemData.mType)
	{
		if (false == mPlayer->mHasWeapon)
		{
			if (newX >= 338.f && newX < 338.f + 29 * 2)
			{
				if (newY >= 76 && newY < 76 + 29 * 3)
				{
					// 만약 이미 장착 중이였다면
					if (mPlayer->mHasWeapon)
					{
						// mPlayer->mWeapon->Unarm();
					}

					ArmWeapon();

					return;
				}
			}
		}

	}

	if (IT_ARMOR_LIGHT == mItemData.mType || IT_ARMOR_HEAVY == mItemData.mType)
	{
		if (false == mPlayer->mHasArmor)
		{
			if (newX >= 338.f + 29 * 4 && newX < 338.f + 29 * 6)
			{
				if (newY >= 76 && newY < 76 + 29 * 3)
				{
					// 만약 이미 장착 중이였다면
					if (mPlayer->mHasArmor)
					{
						// mPlayer->mArmor->Unarm();
					}

					ArmArmor();
					return;
				}
			}
		}
	}

	if (IT_SHIELD == mItemData.mType)
	{
		if (false == mPlayer->mHasShield)
		{
			if (newX >= 338.f + 29 * 8 && newX < 338.f + 29 * 10)
			{
				if (newY >= 76 && newY < 76 + 29 * 3)
				{
					// 만약 이미 장착 중이였다면
					if (mPlayer->mHasShield)
					{
						// mPlayer->mShield->Unarm();
					}

					ArmShield();
					return;
				}
			}
		}
	}

	if (IT_HELM == mItemData.mType)
	{
		if (false == mPlayer->mHasHelm)
		{
			if (newX >= 338.f + 29 * 4 && newX < 338.f + 29 * 6)
			{
				if (newY >= 3 && newY < 3 + 29 * 2)
				{
					// 만약 이미 장착 중이였다면
					if (mPlayer->mHasHelm)
					{
						// mPlayer->mHelm->Unarm();
					}

					ArmHelm();
					return;
				}
			}
		}
	}

	if (IT_RING == mItemData.mType)
	{
		if (false == mPlayer->mHasLeftRing)
		{
			if (newX >= 338.f + 29 && newX < 338.f + 29 * 2)
			{
				if (newY >= 76 + 29 * 3.5 && newY < 76 + 29 * 4.5)
				{
					// 만약 이미 장착 중이였다면
					if (mPlayer->mHasLeftRing)
					{
						// mPlayer->mLRing->Unarm();
					}

					ArmLRing();
					return;
				}
			}
		}

		if (false == mPlayer->mHasRightRing)
		{
			if (newX >= 338.f + 29 * 8 && newX < 338.f + 29 * 9)
			{
				if (newY >= 76 + 29 * 3.5 && newY < 76 + 29 * 4.5)
				{
					// 만약 이미 장착 중이였다면
					if (mPlayer->mHasRightRing)
					{
						// mPlayer->mRRing->Unarm();
					}

					ArmRRing();
					return;
				}
			}
		}
	}

	if (IT_NECK == mItemData.mType)
	{
		if (false == mPlayer->mHasNeck)
		{
			if (newX >= 338.f + 29 * 6.5f && newX < 338.f + 29 * 7.5f)
			{
				if (newY >= 3 + 29 && newY < 3 + 29 * 2)
				{
					// 만약 이미 장착 중이였다면
					if (mPlayer->mHasNeck)
					{
						// mPlayer->mNeck->Unarm();
					}

					ArmNeck();
					return;
				}
			}
		}
	}

	///////////////////////////////////////////////////////// 물약 부분
	{
		if (IT_HPOTION == mItemData.mType || IT_MPOTION == mItemData.mType || IT_MPOTION == mItemData.mType)
		{

			int x = 10;
			int y = 361;
			if (mousePos.X >= x + 195 && mousePos.X <= x + 195 + 26 && mousePos.Y >= y - 3 && mousePos.Y <= y - 3 + 22)
			{
				mBeltIndex = 1;
				SetPotion(x, y);
				mInvenEdge->On();

				mWillBeOff = true;

				mPlayer->mIsItemOn = false;

				if (this == mPlayer->mMouseItem)
				{
					mPlayer->mMouseItem = nullptr;
				}

				return;
			}
			else if (mousePos.X >= x + 195 + 26 + 3 && mousePos.X <= x + 195 + 3 + 26 * 2 && mousePos.Y >= y - 3 && mousePos.Y <= y - 3 + 22)
			{
				SetPotion(x + 29, y);
				mInvenEdge->On();

				mWillBeOff = true;

				mPlayer->mIsItemOn = false;

				if (this == mPlayer->mMouseItem)
				{
					mPlayer->mMouseItem = nullptr;
				}
				mBeltIndex = 2;
				return;
			}
			else if (mousePos.X >= x + 195 + 26 * 2 + 3 * 2 && mousePos.X <= x + 195 + 3 * 2 + 26 * 3 && mousePos.Y >= y - 3 && mousePos.Y <= y - 3 + 22)
			{
				SetPotion(x + 29 * 2, y);
				mInvenEdge->On();

				mWillBeOff = true;

				mPlayer->mIsItemOn = false;

				if (this == mPlayer->mMouseItem)
				{
					mPlayer->mMouseItem = nullptr;
				}
				mBeltIndex = 3;
				return;
			}
			else if (mousePos.X >= x + 195 + 26 * 3 + 3 * 3 && mousePos.X <= x + 195 + 3 * 3 + 26 * 4 && mousePos.Y >= y - 3 && mousePos.Y <= y - 3 + 22)
			{
				SetPotion(x + 29 * 3, y);
				mInvenEdge->On();

				mWillBeOff = true;

				mPlayer->mIsItemOn = false;

				if (this == mPlayer->mMouseItem)
				{
					mPlayer->mMouseItem = nullptr;

				}
				mBeltIndex = 4;
				return;
			}
			else if (mousePos.X >= x + 195 + 26 * 4 + 3 * 4 && mousePos.X <= x + 195 + 4 * 3 + 26 * 5 && mousePos.Y >= y - 3 && mousePos.Y <= y - 3 + 22)
			{
				SetPotion(x + 29 * 4, y);
				mInvenEdge->On();

				mWillBeOff = true;

				mPlayer->mIsItemOn = false;

				if (this == mPlayer->mMouseItem)
				{
					mPlayer->mMouseItem = nullptr;
				}
				mBeltIndex = 5;
				return;

			}
			else if (mousePos.X >= x + 195 + 26 * 5 + 3 * 5 && mousePos.X <= x + 195 + 5 * 3 + 26 * 6 && mousePos.Y >= y - 3 && mousePos.Y <= y - 3 + 22)
			{
				SetPotion(x + 29 * 5, y);
				mInvenEdge->On();

				mWillBeOff = true;

				mPlayer->mIsItemOn = false;

				if (this == mPlayer->mMouseItem)
				{
					mPlayer->mMouseItem = nullptr;
				}
				mBeltIndex = 6;
				return;

			}
			else if (mousePos.X >= x + 195 + 26 * 6 + 3 * 6 && mousePos.X <= x + 195 + 6 * 3 + 26 * 7 && mousePos.Y >= y - 3 && mousePos.Y <= y - 3 + 22)
			{
				SetPotion(x + 29 * 6, y);
				mInvenEdge->On();

				mWillBeOff = true;

				mPlayer->mIsItemOn = false;

				if (this == mPlayer->mMouseItem)
				{
					mPlayer->mMouseItem = nullptr;
				}
				mBeltIndex = 7;
				return;

			}
			else if (mousePos.X >= x + 195 + 26 * 7 + 3 * 7 && mousePos.X <= x + 195 + 7 * 3 + 26 * 8 && mousePos.Y >= y - 3 && mousePos.Y <= y - 3 + 22)
			{
				SetPotion(x + 29 * 7, y);
				mInvenEdge->On();

				mWillBeOff = true;

				mPlayer->mIsItemOn = false;

				if (this == mPlayer->mMouseItem)
				{
					mPlayer->mMouseItem = nullptr;
				}
				mBeltIndex = 8;
				return;
			}



		}
		//////////////////////////////////////////////////////// 버리는 부분
		_ljItemMgr::DropItem(this, mPlayer->GetTileIndex());

		if (this == mPlayer->mMouseItem)
		{
			mPlayer->mMouseItem = nullptr;
		}
		UnsetInven();
		mWillBeOff = true;
		mIsTaken = false;
		mPlayer->mIsNoMove = true;
	}
}

void _ljItem::SetPotion(int x, int y)
{
	mInven->SubPos({ x + 223, y + 38 });
	mInvenEdge->SubPos({ x + 223, y + 38 });

	mIsOnBelt = true;
}

void _ljItem::UnsetPotion()
{
	// 올리려는데 (마우스에) 이미 누가 있다! 두둥
	ITEM_TYPE type = mItemData.mType;

	// 이미 있다면
	if (nullptr != mPlayer->mMouseItem && this != mPlayer->mMouseItem)
	{
		return;
		// 	 mPlayer->mMouseItem->SetInven(MyWindowClass::MainWindow()->MousePos());
		mPlayer->mMouseItem->mWillBeSet = true;
	}

	mInvenEdge->Off();
	// mPlayer->mInvenBack->Off();
	// UnsetInven();


	mInven->SubPos(_ljGameWin::MainWindow()->MousePos());


	mIsOnBelt = false;
	mBeltIndex = 0;



	mIsOn = true;

	mIsSet = false;

	mPlayer->mMouseItem = this;
	mPlayer->mIsItemOn = true;

	_ljGameSound::SoundPlayToInst(L"invgrab.wav");
}

void _ljItem::UnsetInven()
{
	if (mX < 0 || mY < 0)
	{
		return;
	}

	for (int x = mX; x < mX + mItemData.X; ++x)
	{
		for (int y = mY; y < mY + mItemData.Y; ++y)
		{
			mPlayer->mInventory[x + 10 * y] = nullptr;
		}
	}

	mX = -1;
	mY = -1;
}

void _ljItem::ArmWeapon()
{
	if (IT_WEAPON_AXE == mItemData.mType || IT_WEAPON_CLEAVER == mItemData.mType)
	{
		if (true == mPlayer->mHasShield)
		{
			return;
		}
	}

	UnsetInven();

	mIsEquiped = true;

	if (mItemData.X == 2)
	{
		mInven->SubPos({ 338.f + 29, 76.f + 29 * 1.5f });
		mInvenEdge->SubPos({ 338.f + 29, 76.f + 29 * 1.5f });
	}
	else if (mItemData.X == 1)
	{
		mInven->SubPos({ 338.f + 29 * 1.5, 76.f + 29 * 1.5f });
		mInvenEdge->SubPos({ 338.f + 29 * 1.5f, 76.f + 29 * 1.5f });
	}


	mWillBeOff = true;
	mHasWeapon = true;

	mPlayer->mHasWeapon = true;

	// mPlayer->mIsItemOn = false;
	mPlayer->mWeapon = this;
	mPlayer->ApplyItem(this);

	mIsSet = true;

	if (this == mPlayer->mMouseItem)
	{
		mPlayer->mMouseItem = nullptr;
	}
}

void _ljItem::ArmArmor()
{
	UnsetInven();

	mIsEquiped = true;

	mInven->SubPos({ 338.f + 29 * 5, 76.f + 29 * 1.5f });
	mInvenEdge->SubPos({ 338.f + 29 * 5, 76.f + 29 * 1.5f });



	mWillBeOff = true;
	mHasArmor = true;

	mPlayer->mHasArmor = true;
	// mPlayer->mIsItemOn = false;
	mPlayer->mArmor = this;
	mPlayer->ApplyItem(this);

	mIsSet = true;
}

void _ljItem::ArmShield()
{

	if (true == mPlayer->mHasWeapon)
	{
		if (mPlayer->mWeapon->mItemData.mType == IT_WEAPON_AXE || mPlayer->mWeapon->mItemData.mType == IT_WEAPON_CLEAVER)
		{
			return;
		}

	}


	UnsetInven();

	mIsEquiped = true;

	mInven->SubPos({ 338.f + 29 * 9, 76.f + 29 * 1.5f });
	mInvenEdge->SubPos({ 338.f + 29 * 9, 76.f + 29 * 1.5f });

	mWillBeOff = true;
	mHasShield = true;

	mPlayer->mHasShield = true;
	mPlayer->mShield = this;
	mPlayer->ApplyItem(this);
	// mPlayer->mIsItemOn = false;


	mIsSet = true;

	if (this == mPlayer->mMouseItem)
	{
		mPlayer->mMouseItem = nullptr;
	}
}

void _ljItem::ArmHelm()
{
	UnsetInven();

	mIsEquiped = true;

	mInven->SubPos({ 338.f + 29 * 5, 31 * 1.5f });
	mInvenEdge->SubPos({ 338.f + 29 * 5,  31 * 1.5f });

	mWillBeOff = true;
	mHasHelm = true;

	mPlayer->mHasHelm = true;
	mPlayer->ApplyItem(this);
	// mPlayer->mIsItemOn = false;
	mPlayer->mHelm = this;

	mIsSet = true;

	if (this == mPlayer->mMouseItem)
	{
		mPlayer->mMouseItem = nullptr;
	}
}

void _ljItem::ArmLRing()
{
	UnsetInven();

	mIsEquiped = true;

	mInven->SubPos({ 338.f + 2 + 29 * 2.f,  76 + 29 * 5.f });
	mInvenEdge->SubPos({ 338.f + 2 + 29 * 2.f,  76 + 29 * 5.f });

	mWillBeOff = true;
	mHasLeftRing = true;

	mPlayer->mHasLeftRing = true;
	mPlayer->ApplyItem(this);
	// mPlayer->mIsItemOn = false;
	mPlayer->mLRing = this;

	mIsSet = true;

	if (this == mPlayer->mMouseItem)
	{
		mPlayer->mMouseItem = nullptr;
	}
}

void _ljItem::ArmRRing()
{
	UnsetInven();

	mIsEquiped = true;

	mInven->SubPos({ 338.f + 29 * 9.f,  76 + 29 * 5.f });
	mInvenEdge->SubPos({ 338.f + 29 * 9.f,  76 + 29 * 5.f });

	mWillBeOff = true;
	mHasRightRing = true;

	mPlayer->mHasRightRing = true;
	mPlayer->ApplyItem(this);
	// mPlayer->mIsItemOn = false;
	mPlayer->mRRing = this;

	mIsSet = true;

	if (this == mPlayer->mMouseItem)
	{
		mPlayer->mMouseItem = nullptr;
	}
}

void _ljItem::ArmNeck()
{
	UnsetInven();

	mIsEquiped = true;

	mInven->SubPos({ 338.f + 29 * 7.5f, 31 * 2.5f });
	mInvenEdge->SubPos({ 338.f + 29 * 7.5f,  31 * 2.5f });

	mWillBeOff = true;
	mHasNeck = true;

	mPlayer->mHasNeck = true;
	mPlayer->ApplyItem(this);
	// mPlayer->mIsItemOn = false;
	mPlayer->mNeck = this;

	mIsSet = true;

	if (this == mPlayer->mMouseItem)
	{
		mPlayer->mMouseItem = nullptr;
	}
}



// 아이템 짚어가서 바닥에서 사라짐
void _ljItem::AllOff()
{
	mInGameBack->Off();
	mInGame->Off();
	mInGame2->Off();
	mIsTaken = true;

	mTileIndex = { -1, -1 };
}

void _ljItem::ResetPosition(int x, int y)
{
	mInven->SubPos({ 366.f + x * 29, 268.f + y * 29 });
	mInvenEdge->SubPos({ 366.f + x * 29, 268.f + y * 29 });

	mX = x;
	mY = y;

	int baseY = mY + mItemData.Y - 1;
	int baseX = mX + mItemData.X - 1;

	mBase = baseX + baseY * 10;

	int count = 0;

	// mPlayer->mItemList.push_back(this);

	for (int i = x; i < x + mItemData.X; ++i)
	{
		for (int j = y; j < y + mItemData.Y; ++j)
		{
			if (nullptr != mPlayer->mInventory[i + 10 * (j)])
			{
				++count;
				if (count == 1)
				{
					mMouseItem = mPlayer->mInventory[i + 10 * (j)];
					continue;
				}

				if (mPlayer->mInventory[i + 10 * (j)] != nullptr &&
					mMouseItem != mPlayer->mInventory[i + 10 * (j)])
				{
					mMouseItem = nullptr;

					return;
				}
			}
		}
	}

	//if (nullptr != mMouseItem)
	//{
	//	mMouseItem->UnsetInven();
	//	mMouseItem->mWillBeOn = true;
	//	mMouseItem = nullptr;
	//}

	for (int i = x; i < x + mItemData.X; ++i)
	{
		for (int j = y; j < y + mItemData.Y; ++j)
		{
			mPlayer->mInventory[i + 10 * j] = this;
		}
	}

	mIsSet = true;
}

void _ljItem::SetPosition(int x, int y)
{
	mInven->SubPos({ 366.f + x * 29, 268.f + y * 29 });
	mInvenEdge->SubPos({ 366.f + x * 29, 268.f + y * 29 });

	mX = x;
	mY = y;

	for (int i = x; i < x + mItemData.X; ++i)
	{
		for (int j = y; j < y + mItemData.Y; ++j)
		{
			mPlayer->mInventory[i + 10 * j] = this;
		}
	}

	mIsSet = true;
}

void _ljItem::ResetAni()
{
	ITEM_TYPE type = mItemData.mType;

	switch (type)
	{
	case IT_GOLD:
		_ljGameSound::SoundPlayToInst(L"gold1.wav");
		break;
	case IT_WEAPON_AXE:
		_ljGameSound::SoundPlayToInst(L"invaxe.wav");
		break;
	case IT_WEAPON_CLEAVER:
		_ljGameSound::SoundPlayToInst(L"invsign.wav");
		break;
	case IT_WEAPON_SWORD:
		_ljGameSound::SoundPlayToInst(L"invsword.wav");
		break;
	case IT_WEAPON_BOW:
		_ljGameSound::SoundPlayToInst(L"invbow.wav");
		break;
	case IT_ARMOR_LIGHT:
		_ljGameSound::SoundPlayToInst(L"invlarm.wav");
		break;
	case IT_ARMOR_HEAVY:
		_ljGameSound::SoundPlayToInst(L"invharm.wav");
		break;
	case IT_HELM:
		_ljGameSound::SoundPlayToInst(L"invcap.wav");
		break;
	case IT_SHIELD:
		_ljGameSound::SoundPlayToInst(L"invshiel.wav");
		break;
	case IT_RING:
	case IT_NECK:
		_ljGameSound::SoundPlayToInst(L"invring.wav");
		break;
	case IT_BOOK:
		_ljGameSound::SoundPlayToInst(L"invbook.wav");
		break;
	case IT_HPOTION:
	case IT_MPOTION:
	case IT_RPOTION:
		_ljGameSound::SoundPlayToInst(L"invpot.wav");
		break;
	case IT_ISCROLL:
	case IT_PSCROLL:
		_ljGameSound::SoundPlayToInst(L"invscrol.wav");
		break;
	case IT_MAX:
		break;
	default:
		break;
	}

	mInGame->On();
	mInGame2->On();
	mInGameBack->On();
	mInGame->SetCurrentAnimation(mAniName.c_str());
	mInGame2->SetCurrentAnimation(mAniName.c_str());
	mInGameBack->SetCurrentAnimation(mAniName.c_str());
}

// 올릴때 사용된다.
bool _ljItem::CheckMouse()
{
	_ljVector mPos = _ljGameWin::MainWindow()->MousePos();

	int newX = mPos.IntX();
	int newY = mPos.IntY();

	if (false == mIsEquiped)
	{
		if (newX >= 366.f + (mX - 1) * 29 && newX < 366.f + (mX - 1) * 29 + mItemData.X * 29)
		{
			if (newY >= 266.f + (mY - 1.5) * 29 && newY < 266.f + (mY - 1.5) * 29 + mItemData.Y * 29)
			{
				return true;
			}
		}
	}
	else if (true == mHasWeapon)
	{
		if (newX >= 338.f && newX < 338.f + 29 * 2)
		{
			if (newY >= 76.f && newY < 76.f + 29 * 3)
			{
				return true;
			}
		}
	}

	if (IT_ARMOR_LIGHT == mItemData.mType || IT_ARMOR_HEAVY == mItemData.mType)
	{
		if (true == mPlayer->mHasArmor)
		{
			if (newX >= 338.f + 29 * 4 && newX < 338.f + 29 * 6)
			{
				if (newY >= 76 && newY < 76 + 29 * 3)
				{
					return true;
				}
			}
		}
	}

	if (IT_SHIELD == mItemData.mType)
	{
		if (true == mPlayer->mHasShield)
		{
			if (newX >= 338.f + 29 * 8 && newX < 338.f + 29 * 10)
			{
				if (newY >= 76 && newY < 76 + 29 * 3)
				{
					return true;
				}
			}
		}
	}

	if (IT_HELM == mItemData.mType)
	{
		if (true == mPlayer->mHasHelm)
		{
			if (newX >= 338.f + 29 * 4 && newX < 338.f + 29 * 6)
			{
				if (newY >= 3 && newY < 3 + 29 * 2)
				{
					return true;
				}
			}
		}
	}

	if (IT_RING == mItemData.mType)
	{
		if (true == mPlayer->mHasLeftRing)
		{
			if (newX >= 338.f + 29 && newX < 338.f + 29 * 2)
			{
				if (newY >= 76 + 29 * 3.5 && newY < 76 + 29 * 4.5)
				{
					return true;
				}
			}
		}

		if (true == mPlayer->mHasRightRing)
		{
			if (newX >= 338.f + 29 * 8 && newX < 338.f + 29 * 9)
			{
				if (newY >= 76 + 29 * 3.5 && newY < 76 + 29 * 4.5)
				{
					return true;
				}
			}
		}
	}

	if (IT_NECK == mItemData.mType)
	{
		if (true == mPlayer->mHasNeck)
		{
			if (newX >= 338.f + 29 * 6.5f && newX < 338.f + 29 * 7.5f)
			{
				if (newY >= 3 + 29 && newY < 3 + 29 * 2)
				{
					return true;
				}
			}
		}
	}

	int x = 10;
	int y = 361;

	if (true == mIsOnBelt)
	{
		if (newX >= x + 195 && newX <= x + 195 + 26 && newY >= y - 3 && newY <= y - 3 + 22 && mBeltIndex == 1)
		{
			return true;
		}
		else if (newX >= x + 195 + 26 + 3 && newX <= x + 195 + 3 + 26 * 2 && newY >= y - 3 && newY <= y - 3 + 22 && mBeltIndex == 2)
		{
			return true;
		}
		else if (newX >= x + 195 + 26 * 2 + 3 * 2 && newX <= x + 195 + 3 * 2 + 26 * 3 && newY >= y - 3 && newY <= y - 3 + 22 && mBeltIndex == 3)
		{
			return true;
		}
		else if (newX >= x + 195 + 26 * 3 + 3 * 3 && newX <= x + 195 + 3 * 3 + 26 * 4 && newY >= y - 3 && newY <= y - 3 + 22 && mBeltIndex == 4)
		{
			return true;
		}
		else if (newX >= x + 195 + 26 * 4 + 3 * 4 && newX <= x + 195 + 4 * 3 + 26 * 5 && newY >= y - 3 && newY <= y - 3 + 22 && mBeltIndex == 5)
		{
			return true;
		}
		else if (newX >= x + 195 + 26 * 5 + 3 * 5 && newX <= x + 195 + 5 * 3 + 26 * 6 && newY >= y - 3 && newY <= y - 3 + 22 && mBeltIndex == 6)
		{
			return true;
		}
		else if (newX >= x + 195 + 26 * 6 + 3 * 6 && newX <= x + 195 + 6 * 3 + 26 * 7 && newY >= y - 3 && newY <= y - 3 + 22 && mBeltIndex == 7)
		{
			return true;
		}
		else if (newX >= x + 195 + 26 * 7 + 3 * 7 && newX <= x + 195 + 7 * 3 + 26 * 8 && newY >= y - 3 && newY <= y - 3 + 22 && mBeltIndex == 8)
		{
			return true;
		}
	}

	return false;
}


void _ljItem::DebugRender()
{
	wchar_t Arr[256] = { 0, };

	//swprintf_s(Arr, L"mX, mY : %d, %d", mX, mY);
	//TextOutW(_ljGameTextureMgr::BackDC(), 0, 45, Arr, lstrlen(Arr));

	//swprintf_s(Arr, L"mIsOn : %d", mIsOn);
	//TextOutW(_ljGameTextureMgr::BackDC(), 0, 60, Arr, lstrlen(Arr));
}

void _ljItem::UseItem()
{
	_ljGameSound::SoundPlayToInst(L"invpot.wav");

	switch (mItemData.mType)
	{
	case IT_HPOTION:
		mPlayer->mCurHP += 30;
		if (mPlayer->mCurHP >= mPlayer->mData.mMaxHP)
		{
			mPlayer->mCurHP = mPlayer->mData.mMaxHP;
		}
		break;

	case IT_MPOTION:
		mPlayer->mCurMP += 30;
		if (mPlayer->mCurMP >= mPlayer->mData.mMaxMP)
		{
			mPlayer->mCurMP = mPlayer->mData.mMaxMP;
		}
		break;

	case IT_RPOTION:
		mPlayer->mCurHP += 60;
		if (mPlayer->mCurHP >= mPlayer->mData.mMaxHP)
		{
			mPlayer->mCurHP = mPlayer->mData.mMaxHP;
		}

		mPlayer->mCurMP += 30;
		if (mPlayer->mCurMP >= mPlayer->mData.mMaxMP)
		{
			mPlayer->mCurMP = mPlayer->mData.mMaxMP;
		}
		break;
	default:
		break;
	}

	if (true == mIsOnBelt)
	{
		mIsOnBelt = false;
		mBeltIndex = 0;
	}

	UnsetInven();
	KillThis();
}

