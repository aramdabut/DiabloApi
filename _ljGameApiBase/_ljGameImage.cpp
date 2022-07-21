#include "_ljGameImage.h"
#include "_ljGameMacro.h"

_ljGameImage::_ljGameImage()
{
}

_ljGameImage::~_ljGameImage()
{
}

void _ljGameImage::Cut(_ljGameTexture* texture, int x, int y)
{
	if (nullptr == texture ||
		1 > x ||
		1 > y)
	{
		BOOM;
	}

	mTexture = texture;
	mDC = mTexture->TextureDC();

	_ljVector cutSize = mTexture->Size();

	cutSize.X = cutSize.X / x;
	cutSize.Y = cutSize.Y / y;

	_ljVector startPos = _ljVector::ZERO;

	for (int i = 0; i < y; ++i)
	{
		for (int j = 0; j < x; ++j)
		{
			MyRect rc;

			rc.Pos = { startPos.X, startPos.Y };
			rc.Size = cutSize;

			mAllCutData.push_back(rc);

			startPos.X += cutSize.X;
		}
		startPos.X = 0.0f;
		startPos.Y += cutSize.Y;
	}

}
