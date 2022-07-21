#include "_ljGameMath.h"
#include "_ljGameTime.h"

_ljVector _ljVector::DLeft;
_ljVector _ljVector::DRight;
_ljVector _ljVector::DTop;
_ljVector _ljVector::DBottom;

const _ljVector _ljVector::ZERO = { 0,  0 };
const _ljVector _ljVector::LEFT = { -1,  0 };
const _ljVector _ljVector::LEFTDOWN = { -1,  1 };
const _ljVector _ljVector::DOWN = { 0 ,  1 };
const _ljVector _ljVector::DOWNRIGHT = { 1 ,  1 };
const _ljVector _ljVector::RIGHT = { 1 ,  0 };
const _ljVector _ljVector::RIGHTUP = { 1 , -1 };
const _ljVector _ljVector::UP = { 0 , -1 };
const _ljVector _ljVector::UPLEFT = { -1, -1 };

const _ljVector _ljVector::ARRDIR[8] = { _ljVector::LEFT, _ljVector::LEFTDOWN, _ljVector::DOWN, _ljVector::DOWNRIGHT
									 , _ljVector::RIGHT, _ljVector::RIGHTUP, _ljVector::UP, _ljVector::UPLEFT };

_ljVector _ljVector::DeltaDirArr[MD_MAX];

_ljGameMath::_ljGameMath()
{
}

_ljGameMath::~_ljGameMath()
{
}

void _ljVector::DirUpdate() 
{
	DeltaDirArr[L] = DLeft = LEFT * _ljGameTime::DeltaTime();
	DeltaDirArr[R] = DRight = RIGHT * _ljGameTime::DeltaTime();
	DeltaDirArr[T] = DTop = UP * _ljGameTime::DeltaTime();
	DeltaDirArr[B] = DBottom = DOWN * _ljGameTime::DeltaTime();
}

const _ljVector& _ljVector::DeltaDir(MONSTER_DIR dir)
{
	return DeltaDirArr[dir];
}

