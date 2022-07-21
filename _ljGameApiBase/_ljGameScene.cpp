#include "_ljGameScene.h"
#include "_ljGameActor.h"
#include "_ljGameRenderer.h"
#include "_ljGameTextureMgr.h"
#include "_ljGameWin.h"
#include "_ljGameCollider.h"
#include "_ljGameInput.h"
#include "_ljGameBaseUpdater.h"


/* 
	>>> ����
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


void _ljGameScene::Progress()	// Scene�� Render �ϴ� �� 
{

	DebugUpdate();

	mCurScene->SceneUpdate();
	mCurScene->ActorUpdate();

	// Render ���� ����� �ʱ�ȭ
	Rectangle(_ljGameTextureMgr::BackDC(), 0, 0, _ljGameTextureMgr::BackDCSize().IntX(), _ljGameTextureMgr::BackDCSize().IntY());

	// ��� Actor ����
	mCurScene->ActorRender();

	// Collider ����� ����
	if (true == mIsColDebug)
	{
		mCurScene->ColDebugRender();
		mCurScene->DebugRender();
	}

	// ����� ����
	if (true == mIsDebug)
	{
		mCurScene->ActorDebugRender();
	}

	// Render �� �����쿡 �ѹ��� ��´�.
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

// ��� Actor�� �ڽ��� Scene�� ����ȴ�.
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

// Actor�� ���� Renderer�� List�� 
// Order�� ���� Map�� ����ȴ�. 
void _ljGameScene::AddRenderer(_ljGameRenderer* renderer)
{
	// ���� �������� ����
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

// � �浹ü�� �浹�� �� �ִ��� ����
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

// �浹ü ���׿� �ٸ� �浹ü ���׿� �浹�ߴ��� Ȯ��
void _ljGameScene::CheckLeagueCol(std::map<int, std::list<_ljGameCollider*>>::iterator& _Src, std::map<int, std::list<_ljGameCollider*>>::iterator& _Other)
{
	mSrcStart = _Src->second.begin();
	mSrcEnd = _Src->second.end();

	for (; mSrcStart != mSrcEnd; ++mSrcStart)
	{
		mOtherStart = _Other->second.begin();
		mOtherEnd = _Other->second.end();

		// ����ȭ�� => ȭ�� �ٱ��� �ִ� �ֵ��� �浹 �Ƚ�Ű�� ����� �ִ�.
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

// Actor�� ���� RendererList
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




// ���� �浹 ó��
void _ljGameScene::ActorCollision()
{
	mLinkStart = mLinkData.begin();
	mLinkEnd = mLinkData.end();

	for (; mLinkStart != mLinkEnd; ++mLinkStart)
	{
		mOtherLinkStart = mLinkStart->second.begin();
		mOtherLinkEnd = mLinkStart->second.end();

		// 1�� �浹ü ���׸� ã�´�.
		mSrc = mAllColLeague.find(mLinkStart->first);

		// (MONSTER, MONSTERATT)
		for (; mOtherLinkStart != mOtherLinkEnd; ++mOtherLinkStart)
		{
			// 2�� �浹ü ����
			mOther = mAllColLeague.find((*mOtherLinkStart));

			// ã�� 2�� �浹ü ���װ� ������ ����...
			if (mOther == mAllColLeague.end())
			{
				continue;
			}

			if (mLinkStart->first != (*mOtherLinkStart))
			{
				// 1���� 2�� �浹ü ���� Ȯ��
				CheckLeagueCol(mSrc, mOther);
			}
			else
			{
				// 1���� 1�� �浹ü ���� Ȯ��
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

	// ��������??? �Ⱥ�����.
	for (; StartLeague != EndLeague; ++StartLeague)
	{
		mRenderIter = StartLeague->second.begin();
		mRenderEndIter = StartLeague->second.end();

		for (; mRenderIter != mRenderEndIter; )
		{
			// �θ� �׾��ų�
			// �θ����(����)�� ������ �ڻ��ϰ� ��ɳ�������.
			if (true == (*mRenderIter)->IsDead())
			{
				// �������� ���ߴ�. 
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
				// �������� ���ߴ�. 
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

