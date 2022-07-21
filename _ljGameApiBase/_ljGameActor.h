#pragma once
#include "_ljGameBaseUpdater.h"
#include <list>
#include "_ljGameMacro.h"
#include "_ljGameMath.h"
#include "_ljGameRenderer.h"



class _ljGameScene;
class _ljGameAniRenderer;
class _ljGameCollider;
class _ljGameActor : public _ljGameBaseUpdater
{
	friend _ljGameScene;

public:
	_ljGameActor();
	virtual ~_ljGameActor();

public:
	virtual void Update(); /* �����ϴ� �� */
	virtual void DebugRender();

/* 
 	Actor�� ��ӹ޴� ��� Ŭ������ �ݵ�� �����ڿ� _ljGameRenderer�� ������ �� 
	-> CreateRenderer() ����ؼ� �����Ѵ�. 
	ȭ�鿡 ����� �ʴ´ٸ� > �߰� ���Ѵ�. 
	Actor�� �����ϸ� �ݵ�� �����ڿ� _ljGameRenderer�� �Ҵ��ؾ� �Ѵ�. 
	Actor�� ���� Scene�� RendererLeague�� �־��ش�.
	Scene�� ������ League�� ������ �ִ�.
*/
	template<typename T>
	T* CreateRenderer(LEAGUE_ORDER order)
	{
		T* newRender = new T();

		newRender->mActor = this;
		newRender->mOrder = order;
		mScene->AddRenderer(newRender);

		mAllRenderList.push_back(newRender);

		return newRender;
	}

	_ljGameAniRenderer* CreateAniRenderer(LEAGUE_ORDER order = LO_BG);

	_ljGameScene* Scene() { return mScene; }
	void Scene(_ljGameScene* scene) { mScene = scene; }

	void Pos(const _ljVector& pos) { mRect.Pos = pos; }
	_ljVector Pos() const { return mRect.Pos; }
	// void Size(const _ljVector& size) { mRect.Size = size; }
	// _ljVector Size() const { return mRect.Size; }

	_ljVector CalPos();
	_ljVector CamPos();

	void Move(const _ljVector& pos) { mRect.Pos += pos; }

	void KillThis() { mIsDead = true; }
	bool IsDead() { return mIsDead; }

	virtual void ColStay(_ljGameCollider* _ThisCol, _ljGameCollider* _OtherCol) {}
	virtual void ColEnter(_ljGameCollider* _ThisCol, _ljGameCollider* _OtherCol) {}
	virtual void ColExit(_ljGameCollider* _ThisCol, _ljGameCollider* _OtherCol) {}

	_ljGameCollider* CreateCol(COL_TYPE _Type, COL_LEAGUE _League);

private:
	void Release();

protected:
	MyRect mRect;
	int mLevel;

private:
	_ljGameScene* mScene;

	bool mIsDead;

private:
	std::list<_ljGameRenderer*> mAllRenderList;
	std::list<_ljGameRenderer*>::iterator mRenderIter;
	std::list<_ljGameRenderer*>::iterator mRenderEndIter;

	std::list<_ljGameCollider*> mAllColList;
	std::list<_ljGameCollider*>::iterator mColStartIter;
	std::list<_ljGameCollider*>::iterator mColEndIter;


};


