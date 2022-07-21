#include "_ljLevel.h"
#include <_ljGameTextureMgr.h>
#include <_ljGameImage.h>
#include "_ljPlayer.h"

_ljLevel::_ljLevel()
{
	Image(L"NewYellowFont.bmp");

	TransColor(255, 255, 255);
}


_ljLevel::~_ljLevel()
{
}

void _ljLevel::Render()
{
	if (false == mPlayer->IsStatOpen())
	{
		start = 7;


		ImageIndex(11);
		TransparentBlt(_ljGameTextureMgr::BackDC()
			, 10
			, start
			, SubSize().IntX()
			, SubSize().IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()
			, mRect.Pos.IntY()
			, mRect.Size.IntX()
			, mRect.Size.IntY()
			, mTransColor
		);

		ImageIndex(4);
		TransparentBlt(_ljGameTextureMgr::BackDC()
			, start + 12 * 1
			, start
			, SubSize().IntX()
			, SubSize().IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()
			, mRect.Pos.IntY()
			, mRect.Size.IntX()
			, mRect.Size.IntY()
			, mTransColor
		);

		ImageIndex(21);
		TransparentBlt(_ljGameTextureMgr::BackDC()
			, start + 12 * 2
			, start
			, SubSize().IntX()
			, SubSize().IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()
			, mRect.Pos.IntY()
			, mRect.Size.IntX()
			, mRect.Size.IntY()
			, mTransColor
		);

		ImageIndex(4);
		TransparentBlt(_ljGameTextureMgr::BackDC()
			, start + 12 * 3
			, start
			, SubSize().IntX()
			, SubSize().IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()
			, mRect.Pos.IntY()
			, mRect.Size.IntX()
			, mRect.Size.IntY()
			, mTransColor
		);

		ImageIndex(11);
		TransparentBlt(_ljGameTextureMgr::BackDC()
			, start + 12 * 4
			, start
			, SubSize().IntX()
			, SubSize().IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()
			, mRect.Pos.IntY()
			, mRect.Size.IntX()
			, mRect.Size.IntY()
			, mTransColor
		);

		ImageIndex(38);
		TransparentBlt(_ljGameTextureMgr::BackDC()
			, start + 12 * 5
			, start
			, SubSize().IntX()
			, SubSize().IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()
			, mRect.Pos.IntY()
			, mRect.Size.IntX()
			, mRect.Size.IntY()
			, mTransColor
		);

		if (1 == mPlayer->GetLevel())
		{
			ImageIndex(27);
			TransparentBlt(_ljGameTextureMgr::BackDC()
				, start + 12 * 6
				, start
				, SubSize().IntX()
				, SubSize().IntY()
				, mImage->ImageHDC()
				, mRect.Pos.IntX()
				, mRect.Pos.IntY()
				, mRect.Size.IntX()
				, mRect.Size.IntY()
				, mTransColor
			);
		}
		else if (2 == mPlayer->GetLevel())
		{
			ImageIndex(28);
			TransparentBlt(_ljGameTextureMgr::BackDC()
				, start + 12 * 6
				, start
				, SubSize().IntX()
				, SubSize().IntY()
				, mImage->ImageHDC()
				, mRect.Pos.IntX()
				, mRect.Pos.IntY()
				, mRect.Size.IntX()
				, mRect.Size.IntY()
				, mTransColor
			);
		}
		else if (3 == mPlayer->GetLevel())
		{
			ImageIndex(29);
			TransparentBlt(_ljGameTextureMgr::BackDC()
				, start + 12 * 6
				, start
				, SubSize().IntX()
				, SubSize().IntY()
				, mImage->ImageHDC()
				, mRect.Pos.IntX()
				, mRect.Pos.IntY()
				, mRect.Size.IntX()
				, mRect.Size.IntY()
				, mTransColor
			);
		}
		else if (4 == mPlayer->GetLevel())
		{
			ImageIndex(30);
			TransparentBlt(_ljGameTextureMgr::BackDC()
				, start + 12 * 6
				, start
				, SubSize().IntX()
				, SubSize().IntY()
				, mImage->ImageHDC()
				, mRect.Pos.IntX()
				, mRect.Pos.IntY()
				, mRect.Size.IntX()
				, mRect.Size.IntY()
				, mTransColor
			);
		}
		else
		{
			BOOM;
		}
	}
}

void _ljLevel::SetPlayer(_ljPlayer* player)
{
	mPlayer = player;
}
