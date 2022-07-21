#pragma once
#include <vector>
#include <_ljGameRenderer.h>

class _ljPlayer;
class _ljFog : public _ljGameRenderer
{
	class FogData
	{
	public:
		TileIndex mFogIndex;
		_ljVector mPos;
		_ljVector mSize;
		int mBF;
	};

public:
	_ljFog();
	~_ljFog();

	void Init(_ljPlayer* player);

	void Render() override;

private:
	std::vector<FogData*> mAllFog1;
	std::vector<FogData*> mAllFog2;

	_ljPlayer* mPlayer;

	int mRadius;
};

