#pragma once
#include "_ljGameTime.h"
#include "_ljGameMacro.h"
#include <math.h>




class _ljVector
{
public:
	static void DirUpdate();

	_ljVector() : X(0.0f), Y(0.0f) {}
	_ljVector(float x, float y) : X(x), Y(y) {}
	_ljVector(int x, int y) : X((float)x), Y((float)y) {}

	float HalfX() const { return X * 0.5f; }
	float HalfY() const { return Y * 0.5f; }

	static const _ljVector& DeltaLeft() { return DLeft; }
	static const _ljVector& DeltaRight() { return DRight; }
	static const _ljVector& DeltaTop() { return DTop; }
	static const _ljVector& DeltaBottom() { return DBottom; }
	static const _ljVector& DeltaDir(MONSTER_DIR dir);

public:
	static const _ljVector ZERO;

	static const _ljVector LEFT;
	static const _ljVector LEFTDOWN;
	static const _ljVector DOWN;
	static const _ljVector DOWNRIGHT;
	static const _ljVector RIGHT;
	static const _ljVector RIGHTUP;
	static const _ljVector UP;
	static const _ljVector UPLEFT;

	static const _ljVector ARRDIR[8];

	float X;
	float Y;

private:
	static _ljVector DLeft;
	static _ljVector DRight;
	static _ljVector DTop;
	static _ljVector DBottom;

	static _ljVector DeltaDirArr[MD_MAX];

	/* operator overloading */
public:
	bool operator==(const _ljVector& _Pos) const
	{
		return X == _Pos.X && Y == _Pos.Y;
	}

	bool operator!=(const _ljVector& _Pos) const
	{
		return X != _Pos.X || Y != _Pos.Y;
	}

	bool operator>=(const _ljVector& _Pos) const
	{
		return X >= _Pos.X && Y >= _Pos.Y;
	}

	bool operator<=(const _ljVector& _Pos) const
	{
		return X <= _Pos.X && Y <= _Pos.Y;
	}

	_ljVector operator *(const float _Value) const
	{
		return { this->X * _Value, this->Y * _Value };
	}

	_ljVector operator /(const float _Value) const
	{
		return { this->X / _Value, this->Y / _Value };
	}

	_ljVector& operator *=(const float _Value)
	{
		this->X *= _Value;
		this->Y *= _Value;
		return *this;
	}

	_ljVector operator +(const _ljVector& other) const
	{
		return { this->X + other.X, this->Y + other.Y };
	}

	_ljVector operator +(const int other) const
	{
		return { this->X + other, this->Y + other };
	}

	_ljVector& operator +=(const _ljVector& other)
	{
		this->X += other.X;
		this->Y += other.Y;
		return *this;
	}

	_ljVector operator -(const _ljVector& other) const
	{
		return { this->X - other.X, this->Y - other.Y };
	}

	_ljVector& operator -=(const _ljVector& other)
	{
		this->X -= other.X;
		this->Y -= other.Y;
		return *this;
	}

	/* normal Fuction */
	inline int IntX() const { return (int)X; }
	inline int IntY() const { return (int)Y; }
	inline int IntHalfX() const { return (int)HalfX(); }
	inline int IntHalfY() const { return (int)HalfY(); }
	inline float Length() const { return sqrtf((X * X) + (Y * Y)); }

};

class MyRect
{
public:
	float Left()	const { return Pos.X - Size.HalfX(); }
	float Right()	const { return Pos.X + Size.HalfX(); }
	float Top()		const { return Pos.Y - Size.HalfY(); }
	float Bottom()	const { return Pos.Y + Size.HalfY(); }

	int IntLeft()	const { return (int)Left(); }
	int IntRight()	const { return (int)Right(); }
	int IntTop()	const { return (int)Top(); }
	int IntBottom() const { return (int)Bottom(); }

public:
	_ljVector Pos;
	_ljVector Size;
};


class _ljGameMath 
{

public:
	_ljGameMath();
	~_ljGameMath();

public:
	// v0 = start vector2, v1 = dest vector2, t = deltaTime
	static _ljVector Lerp(_ljVector v0, _ljVector v1, float t) 
	{
		if (1.f <= t)
		{
			t = 1.f;
		}

		return (v1 - v0) * t;
	}

	/*
		float lerp(float p1, float p2, float d1) 
		{
			return (1 - d1)*p1 + d1 * p2;
		}
	*/

	/* 
		static _ljVector Lerp(_ljVector start, _ljVector dest, float time) 
		{
			float tempTime = time;
		
			if (1.f <= tempTime)
			{
				tempTime = 1.f;
			}
		
			return  start * (1 - tempTime) + dest * tempTime;
			// return v0 + (v1 - v0) * t;
		}
	*/

	static bool RectToRect(_ljVector _LeftPos, _ljVector _LeftSize, _ljVector _RightPos, _ljVector _RightSize)
	{
		return RectToRect({ _LeftPos , _LeftSize }, { _RightPos , _RightSize });
	}

	static bool RectToCircle(_ljVector _LeftPos, _ljVector _LeftSize, _ljVector _RightPos, float _RightSize)
	{
		return false;
	}

	static bool RectToPoint(_ljVector _LeftPos, _ljVector _LeftSize, _ljVector _RightPos)
	{
		return false;
	}

	static bool CircleToCircle(_ljVector _LeftPos, float _LeftSize, _ljVector _RightPos, float _RightSize)
	{
		return false;
	}

	static bool CircleToRect(_ljVector _LeftPos, float _LeftSize, _ljVector _RightPos, _ljVector _RightSize)
	{
		return false;
	}

	static bool CircleToPoint(_ljVector _LeftPos, float _LeftSize, _ljVector _RightPos)
	{
		return false;
	}

	static bool PointToPoint(_ljVector _LeftPos, _ljVector _RightPos) 
	{
		return false;
	}

	static bool PointToRect(_ljVector _LeftPos, _ljVector _RightPos, _ljVector _RightSize) 
	{
		return false;
	}

	static bool PointToCircle(_ljVector _LeftPos, _ljVector _RightPos, float _RightSize) 
	{
		return false;
	}

	static bool __stdcall RectToRect(const MyRect& _Left, const MyRect& _Right)
	{
		if (_Left.Right() < _Right.Left())
		{
			return false;
		}

		if (_Left.Left() > _Right.Right())
		{
			return false;

		}

		if (_Left.Top() > _Right.Bottom())
		{
			return false;
		}

		if (_Left.Bottom() < _Right.Top())
		{
			return false;
		}

		return true;
	}

	static bool __stdcall RectToCircle(const MyRect& _Left, const MyRect& _Right)
	{
		return false;
	}

	static bool __stdcall RectToPoint(const MyRect& _Left, const MyRect& _Right)
	{
		return false;
	}

	static bool __stdcall CircleToCircle(const MyRect& _Left, const MyRect& _Right)
	{
		return false;
	}

	static bool __stdcall CircleToRect(const MyRect& _Left, const MyRect& _Right)
	{
		return false;
	}

	static bool __stdcall CircleToPoint(const MyRect& _Left, const MyRect& _Right)
	{
		return false;
	}

	static bool __stdcall PointToPoint(const MyRect& _Left, const MyRect& _Right)
	{
		return false;
	}

	static bool __stdcall PointToRect(const MyRect& _Left, const MyRect& _Right)
	{
		return false;
	}

	static bool __stdcall PointToCircle(const MyRect& _Left, const MyRect& _Right)
	{
		return false;
	}


};

