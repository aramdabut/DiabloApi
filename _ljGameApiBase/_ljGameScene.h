#pragma once
#include <map>
#include <list>
#include <set>
#include "_ljGameMacro.h"
#include "_ljGameMath.h"
#include <string>



class _ljGameActor;
class _ljGameRenderer;
class _ljGameCollider;
class _ljGameScene
{
	friend _ljGameActor;

	// Auto Construct Destruct
	class StaticConDes
	{
	public:
		~StaticConDes();
	};

	friend StaticConDes;
	static StaticConDes mConDes;

public:
	virtual void Loading();
	virtual void SceneUpdate();
	virtual void Init();
	static void DebugUpdate();

	/* 
		액터의 업데이트는 자식들이 구현할 필요가 없다. 
	*/
	void ActorUpdate();
	void ActorRender();
	void ActorCollision();

	void Link(int src, int dest);

	void DebugRender();
	void ActorDebugRender();
	void ColDebugRender();

	void Release();

	virtual void MakeMap() {}

/* public static */
	template<typename T>
	static _ljGameScene* CreateScene(const wchar_t* sceneName)
	{
		_ljGameScene* newScene = new T();
		mLoadingScene = newScene;
		newScene->Loading();
		mLoadingScene = nullptr;
		mAllScene.insert(std::map<std::wstring, _ljGameScene*>::value_type(sceneName, newScene));
		return newScene;
	}

	static void SetCurScene(const wchar_t* sceneName);	// 이 씬을 현재 씬으로 설정

	static void Progress();	//  SCENE 실행 

	void ColDebugSwitch()
	{
		mIsColDebug = !mIsColDebug;
	}

	// ======================= CAMERA =======================

	void CamPos(_ljVector pos)
	{
		mCamera = pos;
		mCamera.X = floorf(mCamera.X);
		mCamera.Y = floorf(mCamera.Y);
	}

	_ljVector CamPos()
	{
		mCamera.X = floorf(mCamera.X);
		mCamera.Y = floorf(mCamera.Y);

		return mCamera;
	}

	void CamMove(_ljVector pos) 
	{
		mCamera += pos;
		mCamera.X = floorf(mCamera.X);
		mCamera.Y = floorf(mCamera.Y);
	}

	void SortOnOff(LEAGUE_ORDER index)
	{
		if (mSortOption.end() == mSortOption.find(index))
		{
			mSortOption.insert(index);
			return;
		}
		else
		{
			mSortOption.erase(index);
			return;
		}
	}

protected:
	_ljGameScene();
	virtual ~_ljGameScene();

private:
	static _ljGameScene* FindScene(const wchar_t* sceneName);
	static void AddActor(_ljGameActor* actor);
	void AddRenderer(_ljGameRenderer* renderer);

	void AddCollider(_ljGameCollider* col);

	void CheckLeagueCol(std::map<int, std::list<_ljGameCollider*>>::iterator& _Src) {};

	void CheckLeagueCol(std::map<int, std::list<_ljGameCollider*>>::iterator& _Src,
						std::map<int, std::list<_ljGameCollider*>>::iterator& _Other);

public:
	int mLevel = 1;
	int mChanging = false;

private:
	static std::map<std::wstring, _ljGameScene*> mAllScene;
	static _ljGameScene* mCurScene;
	static _ljGameScene* mLoadingScene;

	_ljVector mCamera;
	// std::set<int> mSortOption;

	// Actor
	std::list<_ljGameActor*> mAllActor;

	// Renderer
	std::map<int, std::list<_ljGameRenderer*>> mAllRendererLeague;

	// Iterators
	std::list<_ljGameActor*>::iterator mActorIter;
	std::list<_ljGameActor*>::iterator mActorEndIter;
	std::list<_ljGameRenderer*>::iterator mRenderIter;
	std::list<_ljGameRenderer*>::iterator mRenderEndIter;

	std::set<int> mSortOption;

	// Collider 
	static bool mIsDebug;
	static bool mIsColDebug;

	std::map<int, std::set<int>> mLinkData;
	std::map<int, std::set<int>>::iterator mLinkStart;
	std::map<int, std::set<int>>::iterator mLinkEnd;
	std::set<int>::iterator mOtherLinkStart;
	std::set<int>::iterator mOtherLinkEnd;

	std::map<int, std::list<_ljGameCollider*>> mAllColLeague;

	std::map<int, std::list<_ljGameCollider*>>::iterator mDebugStart;
	std::map<int, std::list<_ljGameCollider*>>::iterator mDebugEnd;

	std::map<int, std::list<_ljGameCollider*>>::iterator mSrc;
	std::map<int, std::list<_ljGameCollider*>>::iterator mOther;

	std::list<_ljGameCollider*>::iterator mDebugListStart;
	std::list<_ljGameCollider*>::iterator mDebugListEnd;

	std::list<_ljGameCollider*>::iterator mSrcStart;
	std::list<_ljGameCollider*>::iterator mSrcEnd;
	std::list<_ljGameCollider*>::iterator mOtherStart;
	std::list<_ljGameCollider*>::iterator mOtherEnd;

};

