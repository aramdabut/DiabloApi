#include "_ljInvenBack.h"
#include "_ljPlayer.h"
#include "_ljItem.h"
#include <_ljGameTextureMgr.h>
#include <_ljGameImage.h>


_ljInvenBack::_ljInvenBack()
{
	Image(L"InvenBack.bmp");
	SetBF(70);
	// SetRenderStyle(RS_ALPHA);
	SubPos({ 0.f, 0.f });
	SubSize({ 28.f, 28.f });
	CamOnOff();
}


_ljInvenBack::~_ljInvenBack()
{
}


void _ljInvenBack::Render()
{
	int x = 0;
	int y = 0;

	if (true == mPlayer->mIsInvenOpen)
	{
		for (int i = 0; i < 40; ++i)
		{
			if (nullptr != mPlayer->mInventory[i])
			{
				y = (int)(i / 10);
				x = i - y * 10;

				AlphaBlend(_ljGameTextureMgr::BackDC()
					, 366 + x * 29 - 29
					, 268 + y * 29 - 45
					, 28
					, 28
					, mImage->ImageHDC()
					, mRect.Pos.IntX() // 이미지의 x에서부터
					, mRect.Pos.IntY() // 이미지의 y에서부터
					, mRect.Size.IntX()  // 여기까지의 x 픽셀
					, mRect.Size.IntY()
					, GetBF()
				);
			}
		}
	}

	if (true == mPlayer->mHasWeapon && true == mPlayer->mIsInvenOpen)
	{
		AlphaBlend(_ljGameTextureMgr::BackDC()
			, 338
			, 76
			, 28 * 2
			, 28 * 3
			, mImage->ImageHDC()
			, mRect.Pos.IntX() // 이미지의 x에서부터
			, mRect.Pos.IntY() // 이미지의 y에서부터
			, mRect.Size.IntX()  // 여기까지의 x 픽셀
			, mRect.Size.IntY()
			, GetBF()
		);
	}

	if (true == mPlayer->mHasArmor && true == mPlayer->mIsInvenOpen)
	{
		AlphaBlend(_ljGameTextureMgr::BackDC()
			, 338 + 29 * 4
			, 76
			, 28 * 2
			, 28 * 3
			, mImage->ImageHDC()
			, mRect.Pos.IntX() // 이미지의 x에서부터
			, mRect.Pos.IntY() // 이미지의 y에서부터
			, mRect.Size.IntX()  // 여기까지의 x 픽셀
			, mRect.Size.IntY()
			, GetBF()
		);
	}

	if (true == mPlayer->mHasShield && true == mPlayer->mIsInvenOpen)
	{
		AlphaBlend(_ljGameTextureMgr::BackDC()
			, 338 + 29 * 8
			, 76
			, 28 * 2
			, 28 * 3
			, mImage->ImageHDC()
			, mRect.Pos.IntX() // 이미지의 x에서부터
			, mRect.Pos.IntY() // 이미지의 y에서부터
			, mRect.Size.IntX()  // 여기까지의 x 픽셀
			, mRect.Size.IntY()
			, GetBF()
		);
	}

	if (true == mPlayer->mHasHelm && true == mPlayer->mIsInvenOpen)
	{
		AlphaBlend(_ljGameTextureMgr::BackDC()
			, 338 + 29 * 4
			, 3
			, 28 * 2
			, 28 * 2
			, mImage->ImageHDC()
			, mRect.Pos.IntX() // 이미지의 x에서부터
			, mRect.Pos.IntY() // 이미지의 y에서부터
			, mRect.Size.IntX()  // 여기까지의 x 픽셀
			, mRect.Size.IntY()
			, GetBF()
		);
	}

	if (true == mPlayer->mHasLeftRing && true == mPlayer->mIsInvenOpen)
	{
		AlphaBlend(_ljGameTextureMgr::BackDC()
			, 338 + 29
			, 76 + (int)(29 * 3.5)
			, 28
			, 28
			, mImage->ImageHDC()
			, mRect.Pos.IntX() // 이미지의 x에서부터
			, mRect.Pos.IntY() // 이미지의 y에서부터
			, mRect.Size.IntX()  // 여기까지의 x 픽셀
			, mRect.Size.IntY()
			, GetBF()
		);
	}



	if (true == mPlayer->mHasRightRing && true == mPlayer->mIsInvenOpen)
	{
		AlphaBlend(_ljGameTextureMgr::BackDC()
			, 338 + 29 * 8
			, 76 + (int)(29 * 3.5)
			, 28
			, 28
			, mImage->ImageHDC()
			, mRect.Pos.IntX() // 이미지의 x에서부터
			, mRect.Pos.IntY() // 이미지의 y에서부터
			, mRect.Size.IntX()  // 여기까지의 x 픽셀
			, mRect.Size.IntY()
			, GetBF()
		);
	}


	if (true == mPlayer->mHasNeck && true == mPlayer->mIsInvenOpen)
	{
		AlphaBlend(_ljGameTextureMgr::BackDC()
			, 338 + (int)(29 * 6.5f)
			, 3 + 29
			, 28
			, 28
			, mImage->ImageHDC()
			, mRect.Pos.IntX() // 이미지의 x에서부터
			, mRect.Pos.IntY() // 이미지의 y에서부터
			, mRect.Size.IntX()  // 여기까지의 x 픽셀
			, mRect.Size.IntY()
			, GetBF()
		);
	}

	std::list<_ljItem*>::iterator iter = mPlayer->mItemList.begin();
	std::list<_ljItem*>::iterator iterEnd = mPlayer->mItemList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (nullptr != *iter)
		{
			if (true == (*iter)->mIsOnBelt)
			{
				AlphaBlend(_ljGameTextureMgr::BackDC()
					, 196 + ((*iter)->mBeltIndex - 1) * 29 + 8
					, 355
					, 28
					, 28
					, mImage->ImageHDC()
					, mRect.Pos.IntX() // 이미지의 x에서부터
					, mRect.Pos.IntY() // 이미지의 y에서부터
					, mRect.Size.IntX()  // 여기까지의 x 픽셀
					, mRect.Size.IntY()
					, GetBF()
				);
			}


		}
	}
}


