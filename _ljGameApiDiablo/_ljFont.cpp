#include "_ljFont.h"
#include <_ljGameTextureMgr.h>
#include <_ljGameImage.h>
#include <_ljGameTexture.h>

_ljFont::_ljFont()
{
	Image(L"NewFont.bmp");
	SetRenderStyle(RS_TRANS);
	SubPos({ 0.f, 425.f - 5 });
	SubSize({ 12.f, 12.f });
	CamOnOff();
	TransColor(255, 255, 255);
}


_ljFont::~_ljFont()
{
}

void _ljFont::Render()
{
	if (1 == mSizeY)
	{
		int start = 320 - mSizeX1 * 6;

		for (int i = 0; i < mSizeX1; ++i)
		{
			mIndex = (int)mString1[i] - 97;

			if (-65 == mIndex)
			{
				continue;
			}
			// -
			else if (-52 == mIndex)
			{
				mIndex = 37;
			}
			// :
			else if (-39 == mIndex)
			{
				mIndex = 38;
			}
			else if (-50 == mIndex)
			{
				mIndex = 39;
			}
			else if (mIndex < 0)
			{
				mIndex += 49 + 26;
			}

			ImageIndex(mIndex);
			TransparentBlt(_ljGameTextureMgr::BackDC()
				, start + i * 12
				, SubPos().IntY()
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
	}
	else if (2 == mSizeY)
	{
		int start = 320 - mSizeX1 * 6;

		for (int i = 0; i < mSizeX1; ++i)
		{
			mIndex = (int)mString1[i] - 97;

			if (-65 == mIndex)
			{
				continue;
			}
			// -
			else if (-52 == mIndex)
			{
				mIndex = 37;
			}
			// :
			else if (-39 == mIndex)
			{
				mIndex = 38;
			}
			else if (-50 == mIndex)
			{
				mIndex = 39;
			}
			else if (mIndex < 0)
			{
				mIndex += 49 + 26;
			}

			ImageIndex(mIndex);
			TransparentBlt(_ljGameTextureMgr::BackDC()
				, start + i * 12
				, SubPos().IntY() - 10
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

		start = 320 - mSizeX2 * 6;
		for (int i = 0; i < mSizeX2; ++i)
		{
			mIndex = (int)mString2[i] - 97;

			if (-65 == mIndex)
			{
				continue;
			}
			// -
			else if (-52 == mIndex)
			{
				mIndex = 37;
			}
			// :
			else if (-39 == mIndex)
			{
				mIndex = 38;
			}
			else if (-50 == mIndex)
			{
				mIndex = 39;
			}
			else if (mIndex < 0)
			{
				mIndex += 49 + 26;
			}

			ImageIndex(mIndex);
			TransparentBlt(_ljGameTextureMgr::BackDC()
				, start + i * 12
				, SubPos().IntY() + 10
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
	}
	else if (3 == mSizeY)
	{
		int start = 320 - mSizeX1 * 6;

		for (int i = 0; i < mSizeX1; ++i)
		{
			mIndex = (int)mString1[i] - 97;

			if (-65 == mIndex)
			{
				continue;
			}
			// -
			else if (-52 == mIndex)
			{
				mIndex = 37;
			}
			// :
			else if (-39 == mIndex)
			{
				mIndex = 38;
			}
			else if (-50 == mIndex)
			{
				mIndex = 39;
			}
			else if (mIndex < 0)
			{
				mIndex += 49 + 26;
			}

			ImageIndex(mIndex);
			TransparentBlt(_ljGameTextureMgr::BackDC()
				, start + i * 12
				, SubPos().IntY() - 18
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

		start = 320 - mSizeX2 * 6;
		for (int i = 0; i < mSizeX2; ++i)
		{
			mIndex = (int)mString2[i] - 97;

			if (-65 == mIndex)
			{
				continue;
			}
			// -
			else if (-52 == mIndex)
			{
				mIndex = 37;
			}
			// :
			else if (-39 == mIndex)
			{
				mIndex = 38;
			}
			else if (-50 == mIndex)
			{
				mIndex = 39;
			}
			else if (mIndex < 0)
			{
				mIndex += 49 + 26;
			}

			ImageIndex(mIndex);
			TransparentBlt(_ljGameTextureMgr::BackDC()
				, start + i * 12
				, SubPos().IntY()
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

		start = 320 - mSizeX3 * 6;
		for (int i = 0; i < mSizeX3; ++i)
		{
			mIndex = (int)mString3[i] - 97;
			if (-65 == mIndex)
			{
				continue;
			}
			// -
			else if (-52 == mIndex)
			{
				mIndex = 37;
			}
			// :
			else if (-39 == mIndex)
			{
				mIndex = 38;
			}
			else if (-50 == mIndex)
			{
				mIndex = 39;
			}
			else if (mIndex < 0)
			{
				mIndex += 49 + 26;
			}

			ImageIndex(mIndex);
			TransparentBlt(_ljGameTextureMgr::BackDC()
				, start + i * 12
				, SubPos().IntY() + 18
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
	}
}

void _ljFont::SetString(std::wstring string1)
{
	mString1 = string1;
	mSizeY = 1;
	mSizeX1 = string1.size();
}

void _ljFont::SetString(std::wstring string1, std::wstring string2)
{
	mString1 = string1;
	mString2 = string2;
	mSizeY = 2;
	mSizeX1 = string1.size();
	mSizeX2 = string2.size();

}

void _ljFont::SetString(std::wstring string1, std::wstring string2, std::wstring string3)
{
	mString1 = string1;
	mString2 = string2;
	mString3 = string3;
	mSizeY = 3;
	mSizeX1 = string1.size();
	mSizeX2 = string2.size();
	mSizeX3 = string3.size();
}
