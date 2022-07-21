#include "_ljRoom.h"
#include <_ljGameMath.h>



_ljRoom::_ljRoom()
{
}

_ljRoom::~_ljRoom()
{
}

_ljVector _ljRoom::LeftTop() const
{
	return Pos;
}

_ljVector _ljRoom::RightTop() const
{


	return Pos + _ljVector(Size.X + 2, 0.f);
}

_ljVector _ljRoom::LeftDown() const
{
	return Pos + _ljVector(0.f, Size.Y + 2);
}

_ljVector _ljRoom::RightDown() const
{
	return Pos + _ljVector(Size.X + 2, Size.Y + 2);
}
