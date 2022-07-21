#pragma once
#include <_ljGameRenderer.h>

class _ljPlayer;
class _ljFont : public _ljGameRenderer
{
public:
	_ljFont();
	~_ljFont();

	void SetPlayer(_ljPlayer* player) { mPlayer = player; }
	void Render() override;
	void SetString(std::wstring string1);
	void SetString(std::wstring string1, std::wstring string2);
	void SetString(std::wstring string1, std::wstring string2, std::wstring string3);
private:
	_ljGameRenderer* mFont;
	_ljPlayer* mPlayer;

	std::wstring mString1;
	std::wstring mString2;
	std::wstring mString3;

	int mSizeY = 0;
	int mSizeX1 = 0;
	int mSizeX2 = 0;
	int mSizeX3 = 0;
	int mIndex = 0;
};