#pragma once
#include "_ljGameBaseUpdater.h"
#include "_ljGameMath.h"


/* 
* Actor는 복수의 Renderer와 Collider를 가질 수 있다.

	[Actor] --------- Renderer x 여러개  
			--------- Collider x 여러개 
*/



class _ljGameActor;
class _ljGameActorSub : public _ljGameBaseUpdater
{
public:
	_ljVector CalPos();

	MyRect CalRect();

	void SubPos(_ljVector subPos)
	{
		mSubPos = subPos;
	}

	void SubSize(_ljVector subSize)
	{
		mSubSize = subSize;
	}

	_ljVector SubPos()
	{
		return mSubPos;
	}

	_ljVector SubSize()
	{
		return mSubSize;
	}

	_ljGameActor* Actor() { return mActor; }

	virtual bool IsUpdated() override;
	virtual bool IsDead() override;

	void CamOnOff();

protected:
	_ljGameActorSub();
	virtual ~_ljGameActorSub();

public:
	_ljVector GetPos() const;

protected:
	_ljGameActor* mActor = nullptr;
	_ljVector mSubPos;
	_ljVector mSubSize;
	bool mIsCam;

};

