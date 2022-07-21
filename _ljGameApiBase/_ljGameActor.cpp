#include "_ljGameActor.h"
#include "_ljGameScene.h"
#include "_ljGameWin.h"
#include "_ljGameRenderer.h"
#include "_ljGameAniRenderer.h"
#include "_ljGametexture.h"
#include "_ljGameTextureMgr.h"
#include "_ljGameCollider.h"

/* 외부 라이브러리를 추가한다. */
//#pragma comment(lib, "msimg32.lib")

_ljGameCollider* _ljGameActor::CreateCol(COL_TYPE _Type, COL_LEAGUE _League)
{
	_ljGameCollider* NewCol = new _ljGameCollider();

	NewCol->mActor = this;
	NewCol->mColType = _Type;
	NewCol->mLeague = _League;

	NewCol->Init();

	mScene->AddCollider(NewCol);

	mAllColList.push_back(NewCol);

	return NewCol;
}

_ljGameActor::_ljGameActor() : mIsDead(false)
{
	_ljGameScene::AddActor(this);
}


/*	
	랜더러의 삭제를 여기서 하는 것을 기억해야 한다. 
	약속이다. 
*/
_ljGameActor::~_ljGameActor()
{
	mRenderIter = mAllRenderList.begin();
	mRenderEndIter = mAllRenderList.end();

	for (; mRenderIter != mRenderEndIter; ++mRenderIter)
	{
		if (nullptr != (*mRenderIter))
		{
			delete (*mRenderIter);
			(*mRenderIter) = nullptr;
		}
	}

	mAllRenderList.clear();

	mColStartIter = mAllColList.begin();
	mColEndIter = mAllColList.end();

	for (; mColStartIter != mColEndIter; ++mColStartIter)
	{
		if (nullptr != (*mColStartIter))
		{
			delete (*mColStartIter);
			(*mColStartIter) = nullptr;
		}
	}

	mAllColList.clear();
}

void _ljGameActor::Release()
{
	mRenderIter = mAllRenderList.begin();
	mRenderEndIter = mAllRenderList.end();

	for (; mRenderIter != mRenderEndIter; )
	{
		if (true == (*mRenderIter)->IsDead())
		{
			delete (*mRenderIter);
			mRenderIter = mAllRenderList.erase(mRenderIter);
			continue;
		}

		++mRenderIter;
	}
}


void _ljGameActor::Update()
{

}

void _ljGameActor::DebugRender()
{
}


_ljGameAniRenderer* _ljGameActor::CreateAniRenderer(LEAGUE_ORDER order)
{
	_ljGameAniRenderer* newRender = new _ljGameAniRenderer();

	newRender->mActor = this;
	newRender->mOrder = order;
	mScene->AddRenderer(newRender);

	mAllRenderList.push_back(newRender);

	return newRender;
}

_ljVector _ljGameActor::CalPos()
{
	return Pos() - mScene->CamPos();
}

_ljVector _ljGameActor::CamPos()
{
	return mScene->CamPos();
}


