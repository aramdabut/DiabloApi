#include "_ljColTile.h"
#include <_ljGameTextureMgr.h>
#include <_ljGameImage.h>
#include <_ljGameActor.h>
#include <_ljGameInput.h>
#include "_ljValueData.h"
#include "_ljMonster.h"
#include "_ljPlayer.h"


bool _ljColTile::mIsDebugging = false;


_ljColTile::_ljColTile()
	: mIsFog(false)
{
	_ljGameRenderer::TransColor(255, 255, 255);

	// SetBF(100);
}


_ljColTile::~_ljColTile()
{
}

void _ljColTile::SetPlayer(_ljPlayer* player)
{
	mPlayer = player;
}

void _ljColTile::SetActor(_ljMonster* actor)
{
	mMyActor = actor;
}



void _ljColTile::Render()
{

}


void _ljColTile::DebugRender()
{
	// m_TilePosSize 

	_ljVector renderPos = CalPos();

	MyRect rc;

	mRect = mImage->GetRect(0);

	rc.Size = { HALF_TILE_WIDTH, HALF_TILE_HEIGHT };

	rc.Pos.X = (mTileIndex.X * QUARTER_TILE_WIDTH) + (mTileIndex.Y * -QUARTER_TILE_WIDTH) + TILE_SUBOFFSETX - 32;
	rc.Pos.Y = (mTileIndex.X * QUARTER_TILE_HEIGHT) + (mTileIndex.Y * QUARTER_TILE_HEIGHT) + TILE_SUBOFFSETY - 10 - 64 - 32;
	rc.Pos.X += renderPos.IntX();
	rc.Pos.Y += renderPos.IntY();

	mPos = rc.Pos;

	if (false == mIsMovable)
	{
		Image(L"WallTile.bmp");
	}
	else if (nullptr != mMyActor)
	{
		Image(L"ActorTile.bmp");
	}
	else
	{
		Image(L"TileDebug.bmp");
	}

	TransparentBlt(_ljGameTextureMgr::BackDC()
		, rc.Pos.IntX()
		, rc.Pos.IntY()
		, rc.Size.IntX()
		, rc.Size.IntY()
		, mImage->ImageHDC()
		, mRect.Pos.IntX() // 이미지의 x에서부터
		, mRect.Pos.IntY() // 이미지의 y에서부터
		, mRect.Size.IntX()  // 여기까지의 x 픽셀
		, mRect.Size.IntY()
		, mTransColor
	);


}


void _ljColTile::Image(const wchar_t* name, int index)
{
	_ljGameRenderer::Image(name, index);
}

void _ljColTile::TileDebugSwitch()
{
}
