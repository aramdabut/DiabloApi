#pragma once
#include <vector>


class _ljMonster;
class _ljMonsterMgr
{

public:
	static void Init();
	static void GenerateM1(
		int dlevel,
		const wchar_t* name,
		int level,
		int maxHp,
		int armor,
		int attack,
		int maxAttack,
		int toHit,
		int exp,
		wchar_t pixel
	);

	static _ljMonster* CloneM1(int index, _ljVector pos);
	static void Clear();
private:
	_ljMonsterMgr();
	~_ljMonsterMgr();


private:
	// static std::vector<_ljMonster*> mM1;
	// static std::vector<_ljMonster*> mM2;
	// static std::vector<_ljMonster*> mM3;
	// static int index;
};
