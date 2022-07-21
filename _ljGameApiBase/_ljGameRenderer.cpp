#include "_ljGameRenderer.h"
#include "_ljGameTextureMgr.h"
#include "_ljGameActor.h"
#include "_ljGameMacro.h"
#include "_ljGameImage.h"

_ljGameRenderer::_ljGameRenderer()
{
	mHPRate = 0.f;
	mMPRate = 0.f;

	TransColor(255, 0, 255);

	BlendFunction.BlendOp = AC_SRC_OVER;
	BlendFunction.BlendFlags = 0;
	BlendFunction.SourceConstantAlpha = 255;
	BlendFunction.AlphaFormat = AC_SRC_ALPHA;
}


_ljGameRenderer::~_ljGameRenderer()
{
}

void _ljGameRenderer::Render()
{
	if (nullptr == mActor)
	{
		BOOM;
	}

	MyRect rc = CalRect();

	switch (mStyle)
	{
	case RS_NONE:
		break;
	case RS_TRANS:
		TransparentBlt(_ljGameTextureMgr::BackDC()
			, rc.IntLeft()
			, rc.IntTop()
			, rc.Size.IntX()
			, rc.Size.IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()
			, mRect.Pos.IntY()
			, mRect.Size.IntX()
			, mRect.Size.IntY()
			, mTransColor
		);
		break;
	case RS_ALPHA:
		AlphaBlend(_ljGameTextureMgr::BackDC()
			, rc.IntLeft()
			, rc.IntTop()
			, rc.Size.IntX()
			, rc.Size.IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()
			, mRect.Pos.IntY()
			, mRect.Size.IntX()
			, mRect.Size.IntY()
			, BlendFunction
		);
		break;
	case RS_BIT:
		BitBlt(_ljGameTextureMgr::BackDC()
			, rc.IntLeft()
			, rc.IntTop()
			, rc.Size.IntX()
			, rc.Size.IntY()
			, mImage->ImageHDC()
			, mRect.Pos.IntX()
			, mRect.Pos.IntY()
			, SRCCOPY
		);
		break;
	case RS_HP:
		TransparentBlt(_ljGameTextureMgr::BackDC()
			, 0
			, (int)(337 + 85 * (mHPRate))
			, (int)(640)
			, (int)(85 - 85 * (mHPRate))
			, mImage->ImageHDC()
			, (int)(0)
			, (int)(0 + 85 * (mHPRate))
			, (int)(640)
			, (int)(85 - 85 * (mHPRate))
			, mTransColor
		);
		break;
	case RS_MP:
		TransparentBlt(_ljGameTextureMgr::BackDC()
			, 0
			, (int)(337 + 85 * (mMPRate))
			, (int)(640)
			, (int)(85 - 85 * (mMPRate))
			, mImage->ImageHDC()
			, (int)(0)
			, (int)(0 + 85 * (mMPRate))
			, (int)(640)
			, (int)(85 - 85 * (mMPRate))
			, mTransColor
		);
		break;
	case RS_MAX:
		break;
	default:
		break;
	}
}

void _ljGameRenderer::SetRenderStyle(RENDER_STYLE rs)
{
	mStyle = rs;
}

void _ljGameRenderer::SetBF(int bf)
{
	int temp = bf;

	if (bf > 255)
	{
		temp = 255;
	}

	BlendFunction.SourceConstantAlpha = temp;
}

void _ljGameRenderer::Image(const wchar_t* name, int index /*= 0*/)
{
	mImage = _ljGameTextureMgr::Inst().FindImage(name);

	ImageIndex(index);

	return;
}

void _ljGameRenderer::ImageIndex(int index)
{
	mImageIndex = index;

	if (nullptr == mImage ||
		index >= mImage->CutCount())
	{
		BOOM;
	}

	mRect = mImage->GetRect(index);
}

void _ljGameRenderer::ImageOffset(int x, int y)
{
	mRect.Pos = mRect.Pos + _ljVector((float)x, (float)y);
}
