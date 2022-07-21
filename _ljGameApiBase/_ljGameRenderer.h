
#pragma once
#include "_ljGameActorSub.h"
#include "_ljGameScene.h"
#include "_ljGameGraphics.h"




enum RENDER_STYLE
{
	RS_NONE,
	RS_TRANS,
	RS_ALPHA,
	RS_BIT,
	RS_HP,
	RS_MP,
	RS_MAX
};

/* 
* Renderer에 대해서 ... 

	Actor를 생성하면 반드시 생성자에 Renderer를 할당하는 약속을 했다. 
	Renderer의 사용은 Scene에서 한다. 다만, 생성/소멸은 Actor가 담당한다(== 당연히 종속적일수밖에 없다.)
	Actor의 CreatRenderer()에서 생성된다. 
*/
class _ljGameActor;
class _ljGameScene;
class _ljGameImage;
class _ljGameRenderer : public _ljGameActorSub
{
	friend _ljGameActor;
	friend _ljGameScene;

protected:
	_ljGameRenderer();
	~_ljGameRenderer();
	virtual void Render();
	virtual void DebugRender() {}

protected:
	LEAGUE_ORDER mOrder;
	_ljGameImage* mImage;
	int mImageIndex;
	MyRect mRect;
	int mTransColor;

	BLENDFUNCTION BlendFunction;

private:
	RENDER_STYLE mStyle;
	float mHPRate;
	float mMPRate;

public:
	LEAGUE_ORDER Order() { return mOrder; }

	void ImageIndex(int index);
	int ImageIndex() { return mImageIndex; }

	virtual void Image(const wchar_t* name, int index = 0);
	_ljGameImage* Image() { return mImage; }

	void TransColor(int r, int g, int b)
	{
		mTransColor = _ljGameGraphics::ColorToInt(r, g, b, 0);
	}
	int TransColor() { return mTransColor; }

	void ImageOffset(int x, int y);

	void SetBF(int bf);
	BLENDFUNCTION GetBF() { return BlendFunction; }
	void SetRenderStyle(RENDER_STYLE rs);

	MyRect GetRect() { return mRect; }

	void SetHPRate(float rate) { mHPRate = rate; }
	void SetMPRate(float rate) { mMPRate = rate; }

};

