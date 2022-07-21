#pragma once
#include <_ljGameRenderer.h>

class _ljPlayer;
class _ljInvenBack : public _ljGameRenderer
{
public:
	_ljInvenBack();
	~_ljInvenBack();

	void SetPlayer(_ljPlayer* player) { mPlayer = player; }
	void Render() override;

private:
	_ljGameRenderer* mBack;
	_ljPlayer* mPlayer;

};

