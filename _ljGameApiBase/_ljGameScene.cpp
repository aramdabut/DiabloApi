#include "_ljGameScene.h"
#include "_ljGameActor.h"
#include "_ljGameRenderer.h"
#include "_ljGameTextureMgr.h"
#include "_ljGameWin.h"
#include "_ljGameCollider.h"
#include "_ljGameInput.h"
#include "_ljGameBaseUpdater.h"


/* 
	>>> 개념
	static initialising
*/
std::map<std::wstring, _ljGameScene*> _ljGameScene::mAllScene;
_ljGameScene* _ljGameScene::mCurScene = nullptr;
_ljGameScene* _ljGameScene::mLoadingScene = nullptr;

bool _ljGameScene::mIsDebug = false;
bool _ljGameScene::mIsColDebug = false;

// ============== Auto Construct Destruct ==============
_ljGameScene::StaticConDes _ljGameScene::mConDes;

_ljGameScene::StaticConDes::~StaticConDes()
{
	std::map<std::wstring, _ljGameScene*>::iterator StartIter = _ljGameScene::mAllScene.begin();
	std::map<std::wstring, _ljGameScene*>::iterator EndIter = _ljGameScene::mAllScene.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	_ljGameScene::mAllScene.clear();
}
// ============== Auto Construct Destruct Over ==============


void _ljGameScene::Loading()
{
	CamPos(_ljVector(-320.f, -240.f + HALF_TILE_HEIGHT * 2));
}

void _ljGameScene::SceneUpdate()
{
}

void _ljGameScene::Init()
{
}

void _ljGameScene::DebugUpdate()
{
	if (true == _ljGameInput::Down(L"DEBUG"))
	{
		if (true == mIsDebug)
		{
			mIsDebug = false;
		}
		else
		{
			mIsDebug = true;
		}
	}

	if (true == _ljGameInput::Down(L"COLDEBUG"))
	{
		if (true == mIsColDebug)
		{
			mIsColDebug = false;
		}
		else
		{
			mIsColDebug = true;
		}
	}
}

// ======================== static public ========================


void _ljGameScene::Progress()	// Scene을 Render 하는 곳 
{

	DebugUpdate();

	mCurScene->SceneUpdate();
	mCurScene->ActorUpdate();

	// Render 전에 백버퍼 초기화
	Rectangle(_ljGameTextureMgr::BackDC(), 0, 0, _ljGameTextureMgr::BackDCSize().IntX(), _ljGameTextureMgr::BackDCSize().IntY());

	// 모든 Actor 렌더
	mCurScene->ActorRender();

	// Collider 디버그 렌더
	if (true == mIsColDebug)
	{
		mCurScene->ColDebugRender();
		mCurScene->DebugRender();
	}

	// 디버그 렌더
	if (true == mIsDebug)
	{
		mCurScene->ActorDebugRender();
	}

	// Render 후 윈도우에 한번만 찍는다.
	BitBlt(_ljGameWin::MainDC(), 0, 0, _ljGameTextureMgr::BackDCSize().IntX(), _ljGameTextureMgr::BackDCSize().IntY()
		, _ljGameTextureMgr::BackDC(), 0, 0, SRCCOPY);

	mCurScene->ActorCollision();

	mCurScene->Release();
}



_ljGameScene* _ljGameScene::FindScene(const wchar_t* sceneName)
{
	std::map<std::wstring, _ljGameScene*>::iterator findIter = mAllScene.find(sceneName);

	if (mAllScene.end() == findIter)
	{
		return nullptr;
	}

	return findIter->second;
}

// 모든 Actor은 자신의 Scene에 저장된다.
void _ljGameScene::AddActor(_ljGameActor* actor)
{
	if (nullptr != mLoadingScene)
	{
		actor->mScene = mLoadingScene;
		mLoadingScene->mAllActor.push_back(actor);
	}
	else if (nullptr != mCurScene)
	{
		actor->mScene = mCurScene;
		mCurScene->mAllActor.push_back(actor);
	}
}

// Actor가 가진 Renderer의 List는 
// Order에 따라 Map에 저장된다. 
void _ljGameScene::AddRenderer(_ljGameRenderer* renderer)
{
	// 나의 렌더러의 순서
	auto iter = mAllRendererLeague.find(renderer->Order());

	if (iter == mAllRendererLeague.end())
	{
		mAllRendererLeague.insert(
			std::map<LEAGUE_ORDER, std::list<_ljGameRenderer*>>::value_type(
				renderer->Order(),
				std::list<_ljGameRenderer*>()
			));

		iter = mAllRendererLeague.find(renderer->Order());
	}

	iter->second.push_back(renderer);
}

void _ljGameScene::AddCollider(_ljGameCollider* col)
{
	std::map<int, std::list<_ljGameCollider*>>::iterator FindIter = mAllColLeague.find(col->mLeague);

	if (FindIter == mAllColLeague.end())
	{
		mAllColLeague.insert(
			std::map<int, std::list<_ljGameCollider*>>::value_type(
				col->mLeague,
				std::list<_ljGameCollider*>()
			));

		FindIter = mAllColLeague.find(col->mLeague);
	}

	FindIter->second.push_back(col);
}

// 어떤 충돌체와 충돌할 수 있는지 저장
void _ljGameScene::Link(int src, int dest)
{
	std::map<int, std::set<int>>::iterator Find = mLinkData.find(src);

	if (mLinkData.end() == Find)
	{
		mLinkData.insert(std::map<int, std::set<int>>::value_type(src, std::set<int>()));
		Find = mLinkData.find(src);
	}

	std::set<int>::iterator FindDest = Find->second.find(dest);

	if (FindDest != Find->second.end())
	{
		BOOM;
	}

	Find->second.insert(dest);
}

// 충돌체 리그와 다른 충돌체 리그와 충돌했는지 확인
void _ljGameScene::CheckLeagueCol(std::map<int, std::list<_ljGameCollider*>>::iterator& _Src, std::map<int, std::list<_ljGameCollider*>>::iterator& _Other)
{
	mSrcStart = _Src->second.begin();
	mSrcEnd = _Src->second.end();

	for (; mSrcStart != mSrcEnd; ++mSrcStart)
	{
		mOtherStart = _Other->second.begin();
		mOtherEnd = _Other->second.end();

		// 최적화는 => 화면 바깥에 있는 애들은 충돌 안시키는 방법이 있다.
		for (; mOtherStart != mOtherEnd; ++mOtherStart)
		{
			if (false == (*mSrcStart)->IsUpdated())
			{
				continue;
			}

			(*mSrcStart)->CollisionCheck(*mOtherStart);
		}
	}
}



void _ljGameScene::ActorUpdate()
{
	mActorIter = mAllActor.begin();
	mActorEndIter = mAllActor.end();

	for (; mActorIter != mActorEndIter; ++mActorIter)
	{
		if (nullptr != *mActorIter)
		{
			if (false == (*mActorIter)->IsUpdated())
			{
				continue;
			}

			(*mActorIter)->Update();

		}
	}
}



bool YSort(_ljGameRenderer* left, _ljGameRenderer* right)
{
	return left->CalPos().Y < right->CalPos().Y;
}

//bool XSort(_ljGameRenderer * left, _ljGameRenderer * right)
//{
//	return left->GetTileIndex().X < right->GetTileIndex().X;
//}

// Actor가 가진 RendererList
void _ljGameScene::ActorRender()
{
	std::map<int, std::list<_ljGameRenderer*>>::iterator leagueIter = mAllRendererLeague.begin();
	std::map<int, std::list<_ljGameRenderer*>>::iterator leagueEndIter = mAllRendererLeague.end();

	for (; leagueIter != leagueEndIter; ++leagueIter)
	{
		// YYYYYYYYYYYYYYYYYY SSSSSSSSSSSSSS OOOOOOOOOOOOOOOOOOOOO RRRRRRRRRRRRRR TTTTTTTTTTTTTTTTT
		if (mSortOption.end() != mSortOption.find(leagueIter->first))
		{
			leagueIter->second.sort(YSort);
		}
		// YYYYYYYYYYYYYYYYYY SSSSSSSSSSSSSS OOOOOOOOOOOOOOOOOOOOO RRRRRRRRRRRRRR TTTTTTTTTTTTTTTTT

		mRenderIter = leagueIter->second.begin();
		mRenderEndIter = leagueIter->second.end();

		for (; mRenderIter != mRenderEndIter; ++mRenderIter)
		{
			if (false == (*mRenderIter)->IsUpdated())
			{
				continue;
			}

			(*mRenderIter)->Render();

		}
	}

	//mActorStartIter = mAllActor.begin();
	//mActorEndIter = mAllActor.end();

	//for (; mActorStartIter != mActorEndIter; ++mActorStartIter)
	//{
	//	if (nullptr != *mActorStartIter)
	//	{
	//		(*mActorStartIter)->Render();
	//	}
	//}
}

void _ljGameScene::DebugRender()
{
	std::map<int, std::list<_ljGameRenderer*>>::iterator leagueIter = mAllRendererLeague.begin();
	std::map<int, std::list<_ljGameRenderer*>>::iterator leagueEndIter = mAllRendererLeague.end();

	for (; leagueIter != leagueEndIter; ++leagueIter)
	{
		// YYYYYYYYYYYYYYYYYY SSSSSSSSSSSSSS OOOOOOOOOOOOOOOOOOOOO RRRRRRRRRRRRRR TTTTTTTTTTTTTTTTT
		if (mSortOption.end() != mSortOption.find(leagueIter->first))
		{
			leagueIter->second.sort(YSort);
		}
		// YYYYYYYYYYYYYYYYYY SSSSSSSSSSSSSS OOOOOOOOOOOOOOOOOOOOO RRRRRRRRRRRRRR TTTTTTTTTTTTTTTTT

		mRenderIter = leagueIter->second.begin();
		mRenderEndIter = leagueIter->second.end();

		for (; mRenderIter != mRenderEndIter; ++mRenderIter)
		{

			if (false == (*mRenderIter)->IsUpdated())
			{
				continue;
			}
			(*mRenderIter)->DebugRender();
		}
	}

	//mActorStartIter = mAllActor.begin();
	//mActorEndIter = mAllActor.end();

	//for (; mActorStartIter != mActorEndIter; ++mActorStartIter)
	//{
	//	if (nullptr != *mActorStartIter)
	//	{
	//		(*mActorStartIter)->Render();
	//	}
	//}
}




// 실제 충돌 처리
void _ljGameScene::ActorCollision()
{
	mLinkStart = mLinkData.begin();
	mLinkEnd = mLinkData.end();

	for (; mLinkStart != mLinkEnd; ++mLinkStart)
	{
		mOtherLinkStart = mLinkStart->second.begin();
		mOtherLinkEnd = mLinkStart->second.end();

		// 1번 충돌체 리그를 찾는다.
		mSrc = mAllColLeague.find(mLinkStart->first);

		// (MONSTER, MONSTERATT)
		for (; mOtherLinkStart != mOtherLinkEnd; ++mOtherLinkStart)
		{
			// 2번 충돌체 리그
			mOther = mAllColLeague.find((*mOtherLinkStart));

			// 찾는 2번 충돌체 리그가 없으면 다음...
			if (mOther == mAllColLeague.end())
			{
				continue;
			}

			if (mLinkStart->first != (*mOtherLinkStart))
			{
				// 1번과 2번 충돌체 리그 확인
				CheckLeagueCol(mSrc, mOther);
			}
			else
			{
				// 1번과 1번 충돌체 리그 확인
				CheckLeagueCol(mSrc);
			}
		}
	}
}

void _ljGameScene::ActorDebugRender()
{
	if (true == mIsDebug)
	{
		mActorIter = mAllActor.begin();
		mActorEndIter = mAllActor.end();

		for (; mActorIter != mActorEndIter; ++mActorIter)
		{
			if (nullptr != *mActorIter)
			{
				if (false == (*mActorIter)->IsUpdated())
				{
					continue;
				}
				(*mActorIter)->DebugRender();
			}
		}
	}
}



void _ljGameScene::ColDebugRender()
{

	if (true == mIsDebug)
	{
		mDebugStart = mAllColLeague.begin();
		mDebugEnd = mAllColLeague.end();

		for (; mDebugStart != mDebugEnd; ++mDebugStart)
		{
			mDebugListStart = mDebugStart->second.begin();
			mDebugListEnd = mDebugStart->second.end();

			for (; mDebugListStart != mDebugListEnd; ++mDebugListStart)
			{
				(*mDebugListStart)->DebugRender();
			}
		}
	}
}

void _ljGameScene::Release()
{
	std::map<int, std::list<_ljGameRenderer*>>::iterator StartLeague = mAllRendererLeague.begin();
	std::map<int, std::list<_ljGameRenderer*>>::iterator EndLeague = mAllRendererLeague.end();

	// 빠지나요??? 안빠진다.
	for (; StartLeague != EndLeague; ++StartLeague)
	{
		mRenderIter = StartLeague->second.begin();
		mRenderEndIter = StartLeague->second.end();

		for (; mRenderIter != mRenderEndIter; )
		{
			// 부모가 죽었거나
			// 부모님이(액터)가 나한테 자살하고 명령내렸을때.
			if (true == (*mRenderIter)->IsDead())
			{
				// 마음으로 정했다. 
				mRenderIter = StartLeague->second.erase(mRenderIter);
				continue;
			}

			++mRenderIter;
		}
	}

	mDebugStart = mAllColLeague.begin();
	mDebugEnd = mAllColLeague.end();

	for (; mDebugStart != mDebugEnd; ++mDebugStart)
	{
		mDebugListStart = mDebugStart->second.begin();
		mDebugListEnd = mDebugStart->second.end();

		for (; mDebugListStart != mDebugListEnd; )
		{
			(*mDebugListStart)->DebugRender();

			if (true == (*mDebugListStart)->IsDead())
			{
				// 마음으로 정했다. 
				mDebugListStart = mDebugStart->second.erase(mDebugListStart);
				continue;
			}

			++mDebugListStart;
		}
	}




	mActorIter = mAllActor.begin();
	mActorEndIter = mAllActor.end();

	for (; mActorIter != mActorEndIter; )
	{
		if (nullptr != *mActorIter &&
			true == (*mActorIter)->IsDead())
		{
			delete* mActorIter;
			mActorIter = mAllActor.erase(mActorIter);
			continue;
		}

		++mActorIter;
	}


}


void _ljGameScene::SetCurScene(const wchar_t* sceneName)
{
	mCurScene = FindScene(sceneName);

	if (nullptr == mCurScene)
	{
		BOOM;
	}

	mCurScene->Init();
}



_ljGameScene::_ljGameScene()
{
}


_ljGameScene::~_ljGameScene()
{
	mActorIter = mAllActor.begin();
	mActorEndIter = mAllActor.end();

	for (; mActorIter != mActorEndIter; ++mActorIter)
	{
		if (nullptr != *mActorIter)
		{
			delete* mActorIter;
			*mActorIter = nullptr;
		}
	}

	mAllActor.clear();
}

